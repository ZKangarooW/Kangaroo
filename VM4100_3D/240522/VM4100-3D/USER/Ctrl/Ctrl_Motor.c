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
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//motor PWM输出
        /**********Speed_L1**********/
        if(Ctrl_Speed&& (DownTime_Over == 0))//速度大于0和定时器没有结束
        {
            PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
            Motor1 = Speed_Val.Out;//pid输出
        }
        else
        {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//motor PWM输出
            Rel_Speed = 0;
            Motor1 = 0;//pwm不输出
        }
    }
    else
    {      
        Motor1 = 0;//pwm不输出 
        Rel_Speed = 0;
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//motor PWM输出
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
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//motor PWM输出
}
