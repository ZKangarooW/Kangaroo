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
	Temp_Arg.Kp = 1600*0.001f;
	Temp_Arg.Ki = 8*0.001f;//18
	Temp_Arg.Kd = 90*0.001f;;//控台面
    
    Temp_Speed_Arg.Kp = 350;
	Temp_Speed_Arg.Ki = 400*0.001f;//18
	Temp_Speed_Arg.Kd = 0*0.001f;;//控台面

	Temp_Out_Arg.Kp = 2500*0.001f;
	Temp_Out_Arg.Ki = 20*0.001f;//40
	Temp_Out_Arg.Kd = 0*0.001f;;//控台面
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
        if((Ctrl_temp - Temp.Mesa > -50 && Ctrl_temp -Temp.Mesa < 50))
            Out_Enable = 1;//打开积分计算
        else
            Out_Enable = 0;//关闭积分计算
        
        AltPID_Calculation(dT, Ctrl_temp,Temp.Mesa, &Temp_Arg, &Temp_Val, 100, Out_Enable * 100);
        if(Temp_Val.Out < 0)
            Temp_Val.Out = 0;
        if(Temp_Val.Out > 100)
            Temp_Val.Out = 100;
        
        if(Ctrl_temp > Temp.Mesa)
        {
            AltPID_Calculation(dT, 0.5, Temp.Speed, &Temp_Speed_Arg, &Temp_Speed_Val, 250, 50);
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
    if (Temp.Outside < Ctrl_temp - 250)//达到目标温度-15℃前全速加热
    {
        Mesa_Ctrl(dT, 3100);
    }
    else if (Temp.Outside < Ctrl_temp - 180)//达到目标温度-10℃前全速加热
    {
        Mesa_Ctrl(dT, Ctrl_temp*2.3f);
    }
	else if (Temp.Outside < Ctrl_temp - 100)//达到目标温度-10℃前全速加热
    {
        Mesa_Ctrl(dT, Ctrl_temp*2.2f);
    }
    else//PID控制
    {//设定加热周期为1000ms，1000分之PID_Para.pid_result毫秒开加热器
        if(Ctrl_temp>700)
        {
            AltPID_Calculation(dT, Ctrl_temp, Temp.Outside, &Temp_Out_Arg, &Temp_Out_Val, 2500, Ctrl_temp*3.1);
            if(Temp_Out_Val.Out < 0)
                Temp_Out_Val.Out = 0;
            if(Temp_Out_Val.Out > Ctrl_temp * 3.1f)
                Temp_Out_Val.Out = Ctrl_temp * 3.1f;
        }
        else
        {
            AltPID_Calculation(dT, Ctrl_temp, Temp.Outside, &Temp_Out_Arg, &Temp_Out_Val, 2500, Ctrl_temp*1.2);
            if(Temp_Out_Val.Out < 0)
                Temp_Out_Val.Out = 0;
            if(Temp_Out_Val.Out > Ctrl_temp * 1.5f)
                Temp_Out_Val.Out = Ctrl_temp * 1.5f;
        }
        if (Temp.Outside >= Ctrl_temp) //超出设置值1℃时全关
        {
            Mesa_Ctrl(dT, 0);
        }
        else
        {
            Mesa_Ctrl(dT, Ctrl_temp+Temp_Out_Val.Out);
        }
    }
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
	Temp.Speed = Temp.Mesa - Temp.Old;
	Temp.Old = Temp.Mesa;
}
