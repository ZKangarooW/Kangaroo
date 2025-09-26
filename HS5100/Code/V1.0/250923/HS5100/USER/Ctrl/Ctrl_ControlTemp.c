#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;
_PID_Arg_ Temp_Speed_Arg;
_PID_Val_ Temp_Speed_Val;
_PID_Arg_ Temp_Out_Arg;
_PID_Val_ Temp_Out_Val;

/**********局部变量声明******/
uint8_t Out_Enable;//积分运算的开关
uint8_t Temp_type;//温度类型
int Heat;//各个加热盘的pwm值

/*
*****************************************************************
 * 函数原型：static void Set_Heating_Power(float pwm)
 * 功    能：设置加热盘功率
 * 输    入: 加热的pwm功率 
 * 参    数：float control_signal
*****************************************************************
*/
static void Set_Heating_Power(float pwm)
{
    // 根据PID输出控制加热盘功率
    int power = (int)pwm;  // 将控制信号转为功率（范围0-255）
    if (power < 0) power = 0;  // 限制功率为0
    if (power > 399) power = 399;  // 限制功率为255
    // 根据功率值控制硬件（具体的控制方法根据硬件而定）
    HEAT = power;
}

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
	Temp_Arg.Kp = 800*0.001f;
	Temp_Arg.Ki = 40*0.001f;//18
	Temp_Arg.Kd = 160*0.001f;;//控台面
    
    Temp_Speed_Arg.Kp = 350;
	Temp_Speed_Arg.Ki = 400*0.001f;//18
	Temp_Speed_Arg.Kd = 40*0.001f;;//控台面

	Temp_Out_Arg.Kp = 200*0.001f;
	Temp_Out_Arg.Ki = 24*0.001f;//40
	Temp_Out_Arg.Kd = 90*0.001f;;//控台面
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制temp_c:控温的倍数
*****************************************************************
*/
static void Mesa_Ctrl(float dT,int32_t Ctrl_temp)
{
    static float T;
    static float T1;
	static float last_isum;
	if(Ctrl_temp > Temp_MAX) Ctrl_temp = Temp_MAX;//最高加热Temp_MAX度
	if (Temp.Mesa < Ctrl_temp - 150)//达到目标温度-15℃前全速加热
	{
		Heat = 399;
	}
	else if ((Ctrl_temp <= 2000)&&Temp.Mesa < Ctrl_temp - 100)//达到目标温度-10℃前全速加热
	{
		T += dT;
		if(T <3.0f)
			Heat = 250;
		else if(T >= 3.0f && T < 5.0f)
			Heat = 0;
		else
			 T = 0;
	}
	else if ((Ctrl_temp > 2000)&&Temp.Mesa < Ctrl_temp)//达到目标温度-0.5℃前全速加热
	{
		Heat = 399;
	}
	else    //PID控制
	{   //设定加热周期为1000ms，1000分之PID_Para.pid_result毫秒开加热器
		if((Ctrl_temp - Temp.Mesa > -50 && Ctrl_temp -Temp.Mesa < 50) && Temp.Speed_Mesa <= 2)
		{
			Out_Enable = 1;//打开积分计算
			Temp_Val.Integral = last_isum;
		}
		else
		{
			if(Out_Enable == 1)
				last_isum = Temp_Val.Integral*0.4;
			
			Out_Enable = 0;//关闭积分计算
			Temp_Val.Integral = last_isum;
		}
		
		AltPID_Calculation(dT, Ctrl_temp,Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 100);
		if(Temp_Val.Out < 0)
			Temp_Val.Out = 0;
		if(Temp_Val.Out > 100)
			Temp_Val.Out = 100;
		last_isum = Temp_Val.Integral;
		if(Ctrl_temp > Temp.Mesa)
		{
			AltPID_Calculation(dT, 1, Temp.Speed_Mesa, &Temp_Speed_Arg, &Temp_Speed_Val, 250, 50);
			if(Temp_Speed_Val.Out < 0)
				Temp_Speed_Val.Out = 0;
			if(Temp_Speed_Val.Out > 250)
				Temp_Speed_Val.Out = 250;
		}
		else
		{
			Temp_Speed_Val.Out = 0;
		}
		
		if (Temp.Mesa > Ctrl_temp) //超出设置值1℃时全关
		{
			Heat = 0;
			T1 = 0;
		}
		else
		{
			T1 += dT;
			if (T1 <= (float)(Temp_Val.Out/10))
			{
				Heat =Temp_Speed_Val.Out;
			}
			else
			{
				Heat =0;
			}
			if(T1 > 10.0f)
				T1 = 0;
		}
	}
}


/*
*****************************************************************
 * 函数原型：static void Outside_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：外部温度控制temp_c:控温的倍数
*****************************************************************
*/
static void Outside_Ctrl(float dT, int32_t Ctrl_temp)
{
	static float T;
	static uint8_t pid_active = 0;   
	static float last_good_temp = 0;  
	
    float error = Ctrl_temp - Temp.Outside;
	float final_output;
	float base_output = 0;
	float pid_output = 0;
	
	if(Temp.Up_Speed == 1)//快速
    {
		Temp_Out_Arg.Kp = 400*0.001f;
		Temp_Out_Arg.Ki = 140*0.001f;//40
		Temp_Out_Arg.Kd = 160*0.001f;//控台面
	}
	else if(Temp.Up_Speed == 2)//慢速
    {
		Temp_Out_Arg.Kp = 200*0.001f;
		Temp_Out_Arg.Ki = 24*0.001f;//40
		Temp_Out_Arg.Kd = 90*0.001f;//控台面
	}
	else
	{
		Temp_Out_Arg.Kp = 400*0.001f;
		Temp_Out_Arg.Ki = 70*0.001f;//40
		Temp_Out_Arg.Kd = 90*0.001f;//控台面
	}		
	// 基础分段控制
    if(error >= 150) base_output = Ctrl_temp * 3.1f;
    else if(error >= 100) base_output = Ctrl_temp * 2.8f;
    else if(error >= 50) base_output = Ctrl_temp * 2.5f;
    else if(error >= 20) base_output = Ctrl_temp * 2.0f;
    else if(error >= 5) base_output = Ctrl_temp * 1.6f;
    else if(error > 0) base_output = Ctrl_temp * 1.1f;
    else base_output = 0;
	
	if(error < 30.0f && Temp.Outside < 500)
	{
		base_output = Ctrl_temp * 0.7f;
	}

	// 智能判断是否需要PID
    if (error > 1.0f && error < 60.0f) 
	{
        // 检测温度是否有进展
        if (Temp.Outside > last_good_temp + 1.0f) 
		{
            T = 0;
            last_good_temp = Temp.Rel;
            pid_active = 0;// 有进展，不用PID
        } 
		else 
		{
            T+=dT;
        }
        
        // 如果10秒没有进展，启用PID
        if (T > 10.0f) 
		{
            pid_active = 1;
        }
    } 
	else 
	{
        T = 0;
		
        pid_active = 0;
    }
	
	// PID计算
    if (pid_active) {
        AltPID_Calculation(dT, Ctrl_temp, Temp.Outside, &Temp_Out_Arg, &Temp_Out_Val, 2500, Ctrl_temp*2.5);
        pid_output = Temp_Out_Val.Out;
    }
    
    final_output = base_output + pid_output;
    
    // 达到目标后重置
    if (error <= 0) {
        T = 0;
        pid_active = 0;
        Temp_Out_Val.Integral = 0;
        final_output = 0;
    }
	Mesa_Ctrl(dT, final_output);
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if(sys.Run_Status && PT_VALUE_1_TEMP >= 2200)//启动系统控制台面
	{
		if(Temp_type == 1)//如果是外部探头切换过来
		{
			Temp.ADDMode = 0;
			Temp_type = 0;
		}
		if(Temp.Ctrl)
		{
			Mesa_Ctrl(dT, Temp.Ctrl);
		}
		else
		{
			Heat = 0;//pwm不输出
		}
	}
	else if(sys.Run_Status && PT_VALUE_1_TEMP < 2200)//启动系统控制水温
	{
		if(Temp.Ctrl)
		{
			if(Temp_type == 0)//如果是台面探头切换过来
			{
				Temp.ADDMode = 0;
				Temp_type = 1;
			}
			Outside_Ctrl(dT, Temp.Ctrl);
		}
		else
		{
			Heat = 0;//pwm不输出
		}
	}
	else
	{ 
		Heat = 0;//pwm不输出
	}

    Set_Heating_Power(Heat);
}

void Temp_UpSpeed(float dT)
{
	static float T;

	T++;
	if(T >= 2.0)
	{
		Temp.Speed_Mesa = Temp.Mesa - Temp.Old_Mesa;
		Temp.Old_Mesa = Temp.Mesa;
		T = 0;
	}
}
