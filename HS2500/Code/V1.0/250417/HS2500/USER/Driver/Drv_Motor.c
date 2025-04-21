#include "Drv_Motor.h"

/*
*****************************************************************
 * 函数原型：void Motor_Init(void)
 * 功    能：电机初始化
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);//开启tim14通道一
	HAL_GPIO_WritePin(CW_GPIO_Port,CW_Pin,GPIO_PIN_SET);//SET：逆时针。RESET：顺时针
}
