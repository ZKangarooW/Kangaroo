#include "Drv_HEAT.h"

/*
*****************************************************************
 * 函数原型：void HEAT_Init(void)
 * 功    能：初始化加热
*****************************************************************
*/
void HEAT_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道2的PWM
}
