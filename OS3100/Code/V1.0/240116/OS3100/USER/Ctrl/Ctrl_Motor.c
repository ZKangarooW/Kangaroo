#include "Ctrl_Motor.h"

/*
*****************************************************************
 * 函数原型： void Motor_Ctrl(void)
 * 功    能： 电机控制
*****************************************************************
*/
void Motor_Ctrl(void)
{   
    if(sys.Run_Status == 1)//启动
    {
		/**********Speed_L1**********/
		if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)))//速度大于0和定时器没有结束
		{
			if(sys.Motor_Stop)
			{
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
				if(Speed_Val.Out > 400) 
					Speed_Val.Out = 400;
				if(Speed_Val.Out)
					Speed_Val.Out--;
				PWM = Speed_Val.Out;//pid输出
			}
			else
			{
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
				PID_Speed(Ctrl_Speed*Tooth_Ratio,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
				PWM = Speed_Val.Out;//pid输出
			}
		}
		else
		{
			sys.Motor_Stop = 1;//电机已经停止
			HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
			if(Speed_Val.Out > 400) 
					Speed_Val.Out = 400;
			if(Speed_Val.Out)
					Speed_Val.Out--;
			PWM = Speed_Val.Out;//pid输出
		}
    }
    else
    {
        HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
        PWM = 0;//pwm不输出
		sys.Motor_Stop = 0;//电机已经停止
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
	if(sys.Motor_Stop)
	{
		if(Rel_Speed == 0)
		{
			T += dT;
			if(T > 1.0f)
			{
				PWM = 0;
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

/*
*****************************************************************
 * 函数原型： void Motor_Init(void)
 * 功    能： 电机初始化 
*****************************************************************
*/
void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道一
	HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
    HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,GPIO_PIN_SET);//高电平正转，低电平反转
}
