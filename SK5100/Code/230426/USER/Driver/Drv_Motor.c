#include "Drv_Motor.h"

/*
*****************************************************************
 * 函数原型：void Motor_Init(void)
 * 功    能：电机初始化起步电压25
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//使能电机
	HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//逆时针
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//开启tim1通道一
}
