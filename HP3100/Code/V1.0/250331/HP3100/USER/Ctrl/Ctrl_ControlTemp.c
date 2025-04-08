#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

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
    if(Temp.Rel>Temp.Mesa)
    {
        HEAT = 0;
        HEAT_OFF;
    }
    else if (power < 0)
    {
        power = 0;  // 限制功率为0
        HEAT = power;//功率小于300用PWM控制
        HEAT_OFF;
    }
    else if (power < 100)
    {
        HEAT = power;//功率小于300用PWM控制
        HEAT_OFF;
    }
    
    else//如果功率大于300并且不小于0，用继电器开启
    {
        power = 0;//限制功率为0
        HEAT = power;//功率小于300用PWM控制
        HEAT_ON;
    }
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
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    AltPID_Calculation(dT, Ctrl_temp, Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 300);
    Set_Heating_Power(Temp_Val.Out);
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    if(sys.Run_Status)//启动系统控制台面
	{
        if(Temp.Ctrl)
        {
            Mesa_Ctrl(dT, Temp.Ctrl);
        }
        else
        {
            HEAT = 0;//pwm不输出
            HEAT_OFF;
        }
	}
    else
	{
		HEAT = 0;//pwm不输出
        HEAT_OFF;
	}
}
