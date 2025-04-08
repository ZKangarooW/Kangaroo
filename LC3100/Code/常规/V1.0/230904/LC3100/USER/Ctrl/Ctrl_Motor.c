#include "Ctrl_Motor.h"

/**********全局变量声明******/
float R;//离心率的半径

/*
*****************************************************************
 * 函数原型：void Xg_R(float dT)
 * 功    能：离心力半径
*****************************************************************
*/
void Xg_R(float dT)
{
	switch(Speed_Mode)
	{
		case 1:R = 11;//15ml*8
				Xg_Mode = 8;
				Xg_MAX = 1900;
				Speed_MAX = 12000;
			break;
		case 2:R = 11.6;//15ml*12
				Xg_Mode = 12;
				Xg_MAX = 2000;
				Speed_MAX = 4000;
			break;
		case 3:R = 12.2;//10ml*18
				Xg_Mode = 18;
				Xg_MAX = 2100;
				Speed_MAX = 4000;
			break;	
		case 4:R = 12.1;//10ml*24
				Xg_Mode = 24;
				Xg_MAX = 2100;
				Speed_MAX = 4000;
			break;	
		case 5:R = 12;//50ml*6
				Xg_Mode = 6;
				Xg_MAX = 2100;
				Speed_MAX = 4000;
			break;	
		case 6:R = 10.2;//50ml*6
				Xg_Mode = 9;
				Xg_MAX = 600;
				Speed_MAX = 2300;
			break;	
		default:
			break;
	}
}

/*
*****************************************************************
 * 函数原型： void Motor_Ctrl(float dT)
 * 功    能： 电机控制
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
	Xg_R(dT);//离心力半径
    if(sys.Run_Status == 1)//启动
    {
		if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//电磁锁1和2闭合时
		{
			if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)) && (Safe_Temp_Flag == 0))//速度大于0和定时器没有结束
			{
				if(sys.Motor_Stop)
				{
					HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
					PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
					PWM = Speed_Val.Out;//pid输出
				}
				else
				{
					HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
					if(Speed_Unit)	
						PID_Speed(1000 * My_Sqrt(Ctrl_Speed/(11.18*R)),Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制离心率
					else
						PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制转速
					PWM = Speed_Val.Out;//pid输出
				}
			}
			else
			{
				sys.Motor_Stop = 1;//电机已经停止
				if(sys.Motor_Stop)
				{
					PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
					PWM = Speed_Val.Out;//pid输出
				}
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
			}
		}
		else
		{
			sys.Run_Status = 0;//不启动
			SetOK_Flag = 1;//设置变量
		}
    }
    else
    {
        PWM = 0;//pwm不输出
		sys.Motor_Stop = 0;//电机已经停止
		Speed_Val.SumError = 0;//防止关闭再打开时速度一下子就冲到之前的速度	
		HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
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
		if(Rel_Speed <= 150)
		{
			T += dT;
			if(T> 1.0f)
			{
				PWM = 0;
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
				Lock1_Status = 1;//电磁锁1打开
				Lock2_Status = 1;//电磁锁2打开
				SetOK_Flag = 1;//设置变量
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
