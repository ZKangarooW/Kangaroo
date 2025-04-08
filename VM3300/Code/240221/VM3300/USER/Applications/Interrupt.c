#include "Interrupt.h"

/*
*****************************************************************
 * 函数原型：void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * 功    能：定时器计数回调函数
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Infrared_TIM_Interrupt(htim);//红外发送定时计数中断函数
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Infrared_IC_CaptureCallback(htim);
}
