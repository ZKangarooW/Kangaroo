#include "Ctrl_ControlTemp.h"

#if(Integration_TYPE == 0)//设置成四联和六联时
/**********全局变量声明******/
int HEAT_Time;//温度pwm输出值
int PWM_Out;//pid输出值

/*
*****************************************************************
 * 函数原型：void temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void temp_Control(float dT)
{ 
    if(Run_Status == 1 && Temp_State == 1)//启动和设置了温度和温度控制
    { 
		if(Ctrl_Temp - Ture_Temp<=10)//控制温度减去实际温度小于5摄氏度时
		{
			HEAT_Time += dT;
			if(HEAT_Time < PWM_Out)
			{
				HEAT = 100;
			}
			else
			{
				HEAT = 0;
			}
		}
    }
    else
    {
        HEAT = 0;//加热不工作
        Temp_ADDMode = 0;//显示模式为零
    }
}

/*
*****************************************************************
 * 函数原型：void PID_Cap(float dT)
 * 功    能：PID计算，是加热时间
*****************************************************************
*/
void PID_Cap(float dT)
{
	static float T;
	if(Run_Status == 1 && Temp_State == 1)//启动和设置了温度和温度控制
    { 
		if(Ctrl_Temp - Ture_Temp > 10)
		{
			HEAT = 100;
			PWM_Out = 0;
		}
		else if(Ctrl_Temp - Ture_Temp<=10)//控制温度减去实际温度小于5摄氏度时
		{
			T += dT;
			if(T < 2.0f)
			{
				HEAT = 0;
				PWM_Out = 0;
			}
			if(T == 2.0f)
			{
				PID_Calc(Ture_Temp,Ctrl_Temp);
				PWM_Out = (int)Temp_Val.Out;//pid值赋值
				HEAT_Time = 0;
				T = 0;
			}
		}
	}
	else
	{
		Temp_Val.SumError = 0;
		PWM_Out = 0;
	}
}
#endif
