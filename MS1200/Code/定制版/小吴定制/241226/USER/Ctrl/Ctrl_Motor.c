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
		if(!sys.Motor_Stop)
		{
			HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//电机刹车打开
			/**********Speed_L1**********/
			AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,200,200);//电机PID控制
			if(Speed_Val.Out<0)
				Speed_Val.Out = 0;
			PWM = Speed_Val.Out;//pid输出
		}
		else
		{
			if(Speed_Val.Out)
				Speed_Val.Out -= 1;
			PWM = Speed_Val.Out;//pwm不输出
		}
    }
    else
    { 
		HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_RESET);//电机刹车打开
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm不输出
    }
}

/*
*****************************************************************
 * 函数原型：void Check_MotorStop(float dT)
 * 功    能：检测电机是否停止
*****************************************************************
*/
void Check_MotorStop(float dT)
{
	static float T,T1;
	if(sys.Motor_Stop)
	{
		if(Speed.Rel <= 800)//上一个保险
		{
			T1 += dT;
			if(T1 > 30.0f)
			{
				sys.Run_Status = 0;//关闭
				sys.Motor_Stop = 0;//电机已经停止
				T1 = 0;
			}
		}
		else
		{
			T = 0;
			T1 = 0;
		}
		
		if(Speed.Rel <= 220)//正常的
		{
			T += dT;
			if(T > 1.0f)
			{
				sys.Run_Status = 0;//关闭
				sys.Motor_Stop = 0;//电机已经停止
				T = 0;
			}
		}
		else
		{
			T = 0;
			T1 = 0;
		}
	}
	else
	{
		T = 0;
		T1 = 0;
	}
}
