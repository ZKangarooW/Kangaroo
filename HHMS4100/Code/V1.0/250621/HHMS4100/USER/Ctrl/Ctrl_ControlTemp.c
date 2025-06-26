#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val[Motor_Num];
_PID_Arg_ Temp_Speed_Arg;
_PID_Val_ Temp_Speed_Val[Motor_Num];
_PID_Arg_ Temp_Out_Arg;
_PID_Val_ Temp_Out_Val[Motor_Num];

/**********局部变量声明******/
uint8_t Out_Enable[Motor_Num];//积分运算的开关
float adc_val[Motor_Num],ctrl_val[Motor_Num];
uint8_t water_type[Motor_Num],step[Motor_Num];//判断是油还是水0：水，1油
uint8_t Temp_type[Motor_Num];//温度类型
int Heat[Motor_Num];//各个加热盘的pwm值

void Heat_Out(int Heat[Motor_Num])
{
    HEAT5 = (int8_t)Heat[0];
    HEAT0 = (int8_t)Heat[1];
    HEAT4 = (int8_t)Heat[2];
    HEAT2 = (int8_t)Heat[3];
	HEAT1 = (int8_t)Heat[4];
    HEAT3 = (int8_t)Heat[5];
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
static void Mesa_Ctrl(float dT, uint8_t i,int32_t Ctrl_temp)
{
    static float T[Motor_Num];
    static float T1[Motor_Num];

	if(Ctrl_temp > Temp_MAX) Ctrl_temp = Temp_MAX;//最高加热Temp_MAX度
    if (Work_Num[i].Temp.Mesa < Ctrl_temp - 150)//达到目标温度-15℃前全速加热
    {
        Heat[i] = 399;
    }
    else if ((Ctrl_temp <= 2000)&&Work_Num[i].Temp.Mesa < Ctrl_temp - 100)//达到目标温度-10℃前全速加热
    {
        T[i] += dT;
        if(T[i] <3.0f)
            Heat[i] = 250;
        else if(T[i] >= 3.0f && T[i] < 5.0f)
            Heat[i] = 0;
        else
             T[i] = 0;
    }
    else if ((Ctrl_temp > 2000)&&Work_Num[i].Temp.Mesa < Ctrl_temp)//达到目标温度-0.5℃前全速加热
    {
        Heat[i] = 399;
    }
    else    //PID控制
    {   //设定加热周期为1000ms，1000分之PID_Para.pid_result毫秒开加热器
        if((Ctrl_temp - Work_Num[i].Temp.Mesa > -50 && Ctrl_temp - Work_Num[i].Temp.Mesa < 50))
            Out_Enable[i] = 1;//打开积分计算
        else
            Out_Enable[i] = 0;//关闭积分计算
        
        AltPID_Calculation(dT, Ctrl_temp, Work_Num[i].Temp.Mesa, &Temp_Arg, &Temp_Val[i], 100, Out_Enable[i] * 100);
        if(Temp_Val[i].Out < 0)
            Temp_Val[i].Out = 0;
        if(Temp_Val[i].Out > 100)
            Temp_Val[i].Out = 100;
        
        if(Ctrl_temp > Work_Num[i].Temp.Mesa)
        {
            AltPID_Calculation(dT, 0.5, Work_Num[i].Temp.Speed, &Temp_Speed_Arg, &Temp_Speed_Val[i], 250, 50);
            if(Temp_Speed_Val[i].Out < 0)
                Temp_Speed_Val[i].Out = 0;
            if(Temp_Speed_Val[i].Out > 250)
                Temp_Speed_Val[i].Out = 250;
        }
        else
        {
            Temp_Speed_Val[i].Out = 0;
        }
        
        if (Work_Num[i].Temp.Mesa > Ctrl_temp) //超出设置值1℃时全关
        {
            Heat[i] = 0;
            T1[i] = 0;
        }
        else
        {
            T1[i] += dT;
            if (T1[i] <= (float)(Temp_Val[i].Out/10))
            {
                Heat[i] =Temp_Speed_Val[i].Out;
            }
            else
            {
                Heat[i] =0;
            }
            if(T1[i] > 10.0f)
                T1[i] = 0;
        }
    }
}

/*
*****************************************************************
 * 函数原型：static void Outside_Ctrl(float dT, int32_t Ctrl_temp)
* 功    能：外部温度控制temp_c:控温的倍数
*****************************************************************
*/
static void Outside_Ctrl(float dT, uint8_t i,int32_t Ctrl_temp)
{
    if (Work_Num[i].Temp.Outside < Ctrl_temp - 150)//达到目标温度-15℃前全速加热
    {
        Mesa_Ctrl(dT, i, 3100);
    }
    else if (Work_Num[i].Temp.Outside < Ctrl_temp - 100)//达到目标温度-10℃前全速加热
    {
        Mesa_Ctrl(dT, i, Ctrl_temp*3.1f);
    }
    else//PID控制
    {//设定加热周期为1000ms，1000分之PID_Para.pid_result毫秒开加热器
        if(Ctrl_temp>700)
        {
            AltPID_Calculation(dT, Ctrl_temp, Work_Num[i].Temp.Outside, &Temp_Out_Arg, &Temp_Out_Val[i], 2500, Ctrl_temp*3.1);
            if(Temp_Out_Val[i].Out < 0)
                Temp_Out_Val[i].Out = 0;
            if(Temp_Out_Val[i].Out > Ctrl_temp * 3.1f)
                Temp_Out_Val[i].Out = Ctrl_temp * 3.1f;
        }
        else
        {
            AltPID_Calculation(dT, Ctrl_temp, Work_Num[i].Temp.Outside, &Temp_Out_Arg, &Temp_Out_Val[i], 2500, Ctrl_temp*1.5);
            if(Temp_Out_Val[i].Out < 0)
                Temp_Out_Val[i].Out = 0;
            if(Temp_Out_Val[i].Out > Ctrl_temp * 1.5f)
                Temp_Out_Val[i].Out = Ctrl_temp * 1.5f;
        }
        if (Work_Num[i].Temp.Outside >= Ctrl_temp) //超出设置值1℃时全关
        {
            Mesa_Ctrl(dT, i, 0);
        }
        else
        {
            Mesa_Ctrl(dT, i, Ctrl_temp+Temp_Out_Val[i].Out);
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
    for(uint8_t i = 0;i<Motor_Num;i++)
    {
        if(Work_Num[i].Run_Status && PT_VALUE_1_TEMP[i] >= 2200)//启动系统控制台面
        {
            if(Temp_type[i] == 1)//如果是外部探头切换过来
            {
                Work_Num[i].Temp.ADDMode = 0;
                Temp_type[i] = 0;
            }
            if(Work_Num[i].Temp.Ctrl)
            {
                Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl);
            }
            else
            {
                water_type[i] = 0;
                Heat[i] = 0;//pwm不输出
                step[i] = 0;
            }
        }
        else if(Work_Num[i].Run_Status && PT_VALUE_1_TEMP[i] < 2200)//启动系统控制水温
        {
            if(Work_Num[i].Temp.Ctrl)
            {
                if(Temp_type[i] == 0)//如果是台面探头切换过来
                {
                    Work_Num[i].Temp.ADDMode = 0;
                    Temp_type[i] = 1;
                }
                Outside_Ctrl(dT, i, Work_Num[i].Temp.Ctrl);
            }
            else
            {
                water_type[i] = 0;
                Heat[i] = 0;//pwm不输出
                step[i] = 0;
            }
        }
        else
        {
            water_type[i] = 0;
            Heat[i] = 0;//pwm不输出
            step[i] = 0;
        }
    }
    Heat_Out(Heat);
}

void Temp_UpSpeed(float dT)
{
    static float T[Motor_Num];
    for(uint8_t i = 0;i<Motor_Num;i++)
    {
        T[i] += dT;
        if(T[i] > 1.0f)
        {
            Work_Num[i].Temp.Speed = Work_Num[i].Temp.Mesa - Work_Num[i].Temp.Old;
            Work_Num[i].Temp.Old = Work_Num[i].Temp.Mesa;
            T[i] = 0;
        }
    }
}

/**
 * @brief 温度任务
 * 
 */
void Temp_Task(void *p)
{
    TickType_t xLastWakeTime;//刚开始唤醒的时间
    xLastWakeTime = xTaskGetTickCount ();
    
    Temp_PID();
    
    while(1)
    {
        Temp_UpSpeed(0.01f);
        Temp_Control(0.01f);
        vTaskDelayUntil(&xLastWakeTime, 10);
    }
}

