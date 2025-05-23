#include "Drv_Motor.h"

/*
*****************************************************************
 * 函数原型：void Motor_Init(void)
 * 功    能：电机初始化
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//开启tim3通道四
	HAL_GPIO_WritePin(CW_GPIO_Port,CW_Pin,GPIO_PIN_RESET);//SET：逆时针。RESET：顺时针
}
