#include "Drv_Motor.h"
uint8_t flag;
uint8_t time;
#define PWM1 htim3.Instance->CCR1
/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1); // 开启tim16通道一 14值起来
}
/*
*****************************************************************
 * 函数原型：void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 功    能：定时器计数中断
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim6.Instance) 
	{
		if(!flag)
		{
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // 开启tim16通道一 14值起来
			PWM1 = 79;
			flag = 1;
		}
		else
		{
			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1); // 开启tim16通道一 14值起来
			PWM1 = 0;
			time ++;
			if(time >= 10)
			{
				flag = 0;
				time = 0;
			}
		}
	}
}
