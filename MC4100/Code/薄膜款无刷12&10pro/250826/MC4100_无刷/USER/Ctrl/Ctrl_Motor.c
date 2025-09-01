#include "Ctrl_Motor.h"

/*
*****************************************************************
 * 函数原型： void Motor_Ctrl(float dT)
 * 功    能： 电机控制
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
	static float T;
    if(sys.Run_Status == 1)//启动
    {
		if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//电磁锁闭合时
		{
			if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)) && (Safe_Temp_Flag == 0))//速度大于0和定时器没有结束
			{
				if(sys.Motor_Stop)
				{			
					PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
					PWM = Speed_Val.Out;//pid输出
					T = 0;
				}
				else
				{	
					if(Speed_Mode)	
						PID_Speed(1000 * My_Sqrt(Ctrl_Speed/(11.18*6)),Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制离心率
					else
						PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制转速
					PWM = Speed_Val.Out;//pid输出
					T = 0;
				}
			}
			else
			{
				sys.Motor_Stop = 1;//检测电机
				T = 0;
				if(sys.Motor_Stop)
				{
					PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
					PWM = Speed_Val.Out;//pid输出
				}
			}
		}
		else
		{
			T += dT;
			if(T > 0.5f)
			{	
				T = 0;
				sys.Run_Status = 0;//不启动
			}
		}
    }
    else
    {
		T = 0;
        PWM = 0;//pwm不输出
		Speed_Val.SumError = 0;//防止关闭再打开时速度一下子就冲到之前的速度	
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
		if(Rel_Speed <= 500)
		{
			T += dT;
			if(T>1.0f)
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
