#include "Interrupt.h"

/*
*****************************************************************
 * 函数原型：void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * 功    能：外部中断
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	EC11A_EXTI_Interrupt(GPIO_Pin);//EC11A旋钮中断函数
}

/*
*****************************************************************
 * 函数原型：void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * 功    能：输入捕获回调函数
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Speed_Capture_Interrupt(htim);//速度捕获中断函数
}
