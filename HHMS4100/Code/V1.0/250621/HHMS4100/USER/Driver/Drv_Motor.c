#include "Drv_Motor.h"

/**********全局变量声明*******/
uint16_t Motor_PWM[Motor_Num];
uint16_t Time_Val;

/**
 * @brief 电机全速打开
 *
 */
void Motor_AllON(void)
{
    MO1_ON; 
    MO2_ON; 
    MO3_ON; 
    MO4_ON; 
    MO5_ON; 
    MO6_ON; 
}

/**
 * @brief 电机全速关闭
 *
 */
void Motor_AllOFF(void)
{
    MO1_OFF; 
    MO2_OFF; 
    MO3_OFF; 
    MO4_OFF; 
    MO5_OFF; 
    MO6_OFF; 
}

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
	Motor_AllON();
	HAL_TIM_Base_Start_IT(&htim5);//开始定时器
	HAL_TIM_Base_Start_IT(&htim6);//开始定时器
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//需要30起来
{
    if(htim->Instance==TIM5)
    {
        Time_Val++;
        if(Time_Val >= 200)
            Time_Val = 0;
    }
    if(htim->Instance==TIM6)
    {
        if(Time_Val > Motor_PWM[0])
        {
            MO4_OFF;
        }
        else
        {
            MO4_ON;
        }
	
        if(Time_Val > Motor_PWM[1])
        {
            MO3_OFF;
        }
        else
        {
            MO3_ON;
        }
		if(Time_Val > Motor_PWM[2])
        {
            MO5_OFF;
        }
        else
        {
            MO5_ON;
        }
		if(Time_Val > Motor_PWM[3])
        {
            MO2_OFF;
        }
        else
        {
            MO2_ON;
        }
		if(Time_Val > Motor_PWM[4])
        {
            MO6_OFF;
        }
        else
        {
            MO6_ON;
        }
		if(Time_Val > Motor_PWM[5])
        {
            MO1_OFF;
        }
        else
        {
            MO1_ON;
        }
    }
}
