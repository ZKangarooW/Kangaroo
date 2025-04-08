#include "Drv_Motor.h"
uint8_t flag;
uint32_t time;
#define PWM1 htim3.Instance->CCR2
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
uint8_t step;
void Motor_TIM_Interrupt(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim6.Instance) 
	{
		if(step == 0)
		{
			PWM1 = 79;
			time++;
			if(time >= 900)
			{
				step = 1;
				time = 0;
			}
		}
		if(step == 1)
		{
			PWM1 = 0;
			time++;
			if(time >= 225)
			{
				step = 2;
				time = 0;
			}
		}
		if(step == 2)
		{
			PWM1 = 79;
			time++;
			if(time >= 56)
			{
				step = 3;
				time = 0;
			}
		}
		if(step == 3)
		{
			PWM1 = 0;
			time++;
			if(time >= 9819)
			{
				step = 0;
				time = 0;
			}
		}
	}
}
