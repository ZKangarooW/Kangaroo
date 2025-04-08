#include "Drv_Heat.h"

/*
*****************************************************************
 * 函数原型：void Temp_Init(void)
 * 功    能：温度初始化
*****************************************************************
*/
void Temp_Init(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//开启tim1通道1的PWM
}
