#include "Ctrl_Motor.h"

/**********结构体************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val;

/*
*****************************************************************
 * 函数原型：void Motor_PID(void)
 * 功    能：电机控制PID系数
*****************************************************************
*/
void Motor_PID(void)
{
    Speed_Arg.Kp = 40 * 0.001f;
    Speed_Arg.Ki = 60 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/*
*****************************************************************
 * 函数原型：void Motor_Ctrl(float dT)
 * 功    能：电机控制
*****************************************************************
*/
void Motor_Ctrl(float dT)
{ 
    if(sys.Run_Status)//启动
    {
        if(Speed.Ctrl)
		{
            if(sys.Motor_Stop)
			{
				if(Speed_Val.Out)
					Speed_Val.Out -= (dT*2);//降速太慢*2
				if(Speed_Val.Out < 0)
					Speed_Val.Out = 0;
				PWM = Speed_Val.Out;//pid输出
			}
			else
			{
				AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,200,200);//电机PID控制
				PWM = Speed_Val.Out;//pid输出
			}
        }
    }
    else
    {
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm不输出
    }
}

/*
*****************************************************************
 * 函数原型：void Check_MotorStop(float dT)
 * 功    能：检测电机是否停止，停止后开盖
*****************************************************************
*/
float CW_Time;
void Check_MotorStop(float dT)
{
	static float T;
	if(sys.Motor_Stop)
	{
		if(Speed.Cw)//进入改变转向
		{
			if(sys.Run_Status)
			{
				if(Speed.Rel <= 40)
				{
					T += dT;
					CW_Time = ((float)Speed.Ctrl/100);
					if(T > CW_Time)
					{
						if(Speed.CwIcn) 
						{
							HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//逆时针
							Speed.ADDMode = 0;
							Speed.CwIcn = 0;
						}
						else 
						{
							HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//顺时针
							Speed.ADDMode = 0;
							Speed.CwIcn = 1;
						}
						Beep_Time = 0.1f;
						sys.Motor_Stop = 0;//电机停止清零
						Speed.Cw = 0;//改变转向清零
						Speed_Val.Integral = 16;//电机起步的PWM
						T = 0;
					}
				}
			}
			else
			{
				if(Speed.CwIcn) 
				{
					HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//逆时针
					Speed.ADDMode = 0;
					Speed.CwIcn = 0;
				}
				else 
				{
					HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//顺时针
					Speed.ADDMode = 0;
					Speed.CwIcn = 1;
				}
				sys.Motor_Stop = 0;//电机停止清零
				Speed.Cw = 0;//改变转向清零
			}
		}
		else
		{
			if(Speed.Rel <= 40)
			{
				T += dT;
				if(T > 1.0f)
				{
					TimeSet_Flag=1;
					sys.Run_Status = 0;//关闭
					sys.Motor_Stop = 0;//电机已经停止
					T = 0;
				}
			}
		}
	}
}
