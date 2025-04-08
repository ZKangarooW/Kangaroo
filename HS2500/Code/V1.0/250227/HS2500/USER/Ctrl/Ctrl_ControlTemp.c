#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;
_PID_Arg_ W_Temp_Arg;
_PID_Val_ W_Temp_Val;

/**********局部变量声明******/
uint8_t Temp_type;//温度类型

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
	Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 8*0.001f;//18
	Temp_Arg.Kd = 90*0.001f;;//控台面
    
    W_Temp_Arg.Kp = 20000*0.001f;
    W_Temp_Arg.Ki = 80*0.001f;//18
	W_Temp_Arg.Kd = 900*0.001f;;//控台面
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    float control_signal;
    float final_control_signal;
    AltPID_Calculation(dT, Ctrl_temp, Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 300);
    final_control_signal = (control_signal/1000) + Temp_Val.Out;
    Set_Heating_Power(final_control_signal);
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：控制台面得温度
*****************************************************************
*/
void set_Mesa_power(float dT,float control_signal) 
{
    // 根据输入温度控制加热盘功率
    int power = (int)control_signal;  // 将控制信号转为功率（范围0-255）
    if (power < Temp.Ctrl) power = Temp.Ctrl;  // 限制功率为0
    if (power > Temp_MAX) power = Temp_MAX;  // 限制功率为255
    // 根据功率值控制硬件（具体的控制方法根据硬件而定）
    if(Temp.Rel>Temp.Ctrl)
    {
        HEAT = 0;
    }
    else
    {
        Mesa_Ctrl(dT, power);
    }
}

/*
*****************************************************************
 * 函数原型：static void Water_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：控制水温
*****************************************************************
*/
static void Water_Ctrl(float dT, int32_t Ctrl_temp)
{
    if(Temp.Rel<Temp.Ctrl-100)
    {
        set_Mesa_power(dT,Temp.Ctrl*3.5);
    } 
    else if(Temp.Rel<Temp.Ctrl-60)
    {
        set_Mesa_power(dT,Temp.Ctrl*3.0);
    } 
    else if(Temp.Rel<Temp.Ctrl-30)
    {
        set_Mesa_power(dT,Temp.Ctrl*2.5);
        IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
    } 
    else
    {
        IncPID_Calculation(dT, Ctrl_temp, Temp.Outside, &W_Temp_Arg, &W_Temp_Val,10, 300);
        set_Mesa_power(dT,Ctrl_temp+W_Temp_Val.Out);
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
    if(sys.Run_Status && PT_VALUE_1_TEMP >= 2400)//启动系统控制台面
	{
        if(Temp.Ctrl)
        {
            if(Temp_type == 1)//如果是外部探头切换过来
            {
                Temp.ADDMode = 0;
                Temp_type = 0;
            }
            Mesa_Ctrl(dT, Temp.Ctrl);
        }
        else
        {
            HEAT = 0;//pwm不输出
        }
	}
    else if(sys.Run_Status && PT_VALUE_1_TEMP < 2400)//启动系统控制水温
	{
        if(Temp.Ctrl)
		{	
            if(Temp_type == 0)//如果是台面探头切换过来
			{
				Temp.ADDMode = 0;
				Temp_type = 1;
			}
            Water_Ctrl(dT, Temp.Ctrl);
        }
        else
		{
			HEAT = 0;//pwm不输出
		}
    }
    else
	{
		HEAT = 0;//pwm不输出
	}
}
