#include "Ctrl_Motor.h"

/*
*****************************************************************
 * 函数原型：void Motor_Ctrl(float dT)
 * 功    能：电机控制
*****************************************************************
*/
uint16_t Ctrl_Val;
void Motor_Ctrl(float dT)
{   
    if(sys.Run_Status == 1)//启动
    {
		if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)))//速度大于0和定时器没有结束
		{
			if(sys.Motor_Stop)//在停止减速模式下
			{			
				PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed_Val.Out);
			}
			else
			{	
                if(Ctrl_Speed >= 2200)
                    Ctrl_Val = 2600-(3000 - Ctrl_Speed)/2;
                else
                    Ctrl_Val = Ctrl_Speed;
				PID_Speed(Ctrl_Val,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制转速
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed_Val.Out);
			}
		}
		else
		{
			sys.Motor_Stop = 1;//检测电机
			if(sys.Motor_Stop)//在停止减速模式下
			{
				PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed_Val.Out);
			}
		}
    }
    else
    {
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
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
	static float T;
	if(sys.Motor_Stop)//在停止减速模式下
	{
		if(Rel_Speed < 10)
		{
			T += dT;//时间加dT
			if(T>0.5f)//速度为零时间持续1S时
			{
				SetOK_Flag = 1;//设置参数置一
				sys.Run_Status = 0;//关闭
				sys.Motor_Stop = 0;//电机已经停止
				Time_State = 0;//时间显示
				T = 0;//时间清零
			}
		}
	}
	else
	{
		T = 0;//时间清零
	}
}
