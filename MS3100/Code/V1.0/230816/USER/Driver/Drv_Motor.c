#include "Drv_Motor.h"

/*
*****************************************************************
 * 函数原型：void Motor_Init(void)
 * 功    能：电机初始化
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//打开电机供电
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//开启tim3通道四
    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//逆时针
}
