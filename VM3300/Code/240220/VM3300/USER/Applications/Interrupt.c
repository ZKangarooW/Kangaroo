#include "Interrupt.h"

/*
*****************************************************************
 * 函数原型：void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 功    能：定时器计数回调函数
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Motor_TIM_Interrupt(htim);//EC11A旋钮定时计数中断函数
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Remote_IC_CaptureCallback(htim);
}
