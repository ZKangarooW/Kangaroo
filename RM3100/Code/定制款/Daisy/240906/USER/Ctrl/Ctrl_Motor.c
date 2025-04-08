#include "Ctrl_Motor.h"

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
		if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)))//速度大于0和定时器没有结束
		{
			if(sys.Motor_Stop)//在停止减速模式下
			{			
				if(Speed_Val.Out)
				{
					Speed_Val.Out -= (dT*6);
				}
				PWM = Speed_Val.Out;//PID输出
			}
			else
			{	
				PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
//				if(Speed_Val.Out < 100)
//					Speed_Val.Out = 100;
				PWM = Speed_Val.Out;//PID输出
			}
		}
		else
		{
			sys.Motor_Stop = 1;//检测电机
			if(sys.Motor_Stop)//在停止减速模式下
			{
				if(Speed_Val.Out)
				{
					Speed_Val.Out -= (dT*6);
				}
				PWM = Speed_Val.Out;//PID输出
			}
		}
    }
    else
    {
        PWM = 0;//PWM不输出
		Speed_Val.SumError = 0;//防止关闭再打开时速度一下子就冲到之前的速度	
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
	if(sys.Motor_Stop)//在停止减速模式下
	{
		if(Rel_Speed <= 15)//速度为15
		{
			SetOK_Flag = 1;//设置参数置一
			sys.Run_Status = 0;//关闭
			sys.Motor_Stop = 0;//电机已经停止
		}
	}
}
