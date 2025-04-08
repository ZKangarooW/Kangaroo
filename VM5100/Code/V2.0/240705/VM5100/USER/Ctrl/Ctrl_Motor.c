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
			if(Param.type==0)
			{
				PID_Speed(Ctrl_Speed+500,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
			}
			else if(Param.type == 1)
			{
				PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
			}
			PWM = Speed_Val.Out;//pid输出
        }
        else
        {
			SpeedSet_Flag = TimeSet_Flag = 1;//设置变量
			sys.Run_Status = 0;//关闭
			PWM = 0;//pid输出
        }
    }
    else
    { 
		Speed_Val.SumError = 0;
		Speed_Val.Out = 0;
        PWM = 0;//pwm不输出
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
//	static float T;
//	if(sys.Motor_Stop)
//	{
//		if(Rel_Speed == 0)
//		{
//			T += dT;
//			if(T > 1.0f)
//			{
//				PWM = 0;
//				SpeedSet_Flag = TimeSet_Flag = 1;//设置变量
//				sys.Run_Status = 0;//关闭
//				sys.Motor_Stop = 0;//电机已经停止
//				T = 0;
//			}
//		}
//	}
}

/*
*****************************************************************
 * 函数原型： void Motor_Init(void)
 * 功    能： 电机初始化 
*****************************************************************
*/
void Motor_Init(void)
{
    HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//使能电机
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//motor PWM输出
}
