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
    Speed_Arg.Kp = 20 * 0.001f;
    Speed_Arg.Ki = 20 * 0.001f;
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
    if(sys.Run_Status == 1)//启动
    {
		if((HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1))//电磁锁闭合时
		{
			if(Speed.Ctrl)//速度大于0
			{
				if(sys.Motor_Stop)
				{			
					if(Speed_Val.Out)
                        Speed_Val.Out -= (dT*4);//降速太慢*2
                    if(Speed_Val.Out < 0)
                        Speed_Val.Out = 0;
                    PWM = Speed_Val.Out;//pid输出
				}
				else
				{	
					if(Speed.Unit)
						AltPID_Calculation(dT,1000 * My_Sqrt(Speed.Ctrl/(11.18*9.6)),Speed.Rel,&Speed_Arg,&Speed_Val,350,400);//电机PID控制离心率
					else
						AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,350,400);//电机PID控制转速
                    PWM = Speed_Val.Out;//pid输出
                }
			}
		}
		else
		{
			sys.Run_Status = 0;//不启动
            PWM = 0;
		}
    }
    else
    {
        PWM = 0;//pwm不输出
		Speed_Val.Integral = 0;//防止关闭再打开时速度一下子就冲到之前的速度	
    } 
}

/*
*****************************************************************
 * 函数原型：void Check_MotorStop(float dT)
 * 功    能：检测电机是否停止，停止后开盖
*****************************************************************
*/
void Check_MotorStop(float dT)
{
	static float T;
	if(sys.Motor_Stop)
	{
		if(Speed.Rel <= 340)
		{
			T += dT;
			if(T > 2)
			{
				Lock_Status = 1;//电磁锁打开
				SetOK_Flag = 1;//设置参数置一
				sys.Run_Status = 0;//关闭
				sys.Motor_Stop = 0;//电机已经停止
				T = 0;
			}
		}
		else
		{
			T = 0;
		}
	}
	else
	{
		T = 0;
	}
}
