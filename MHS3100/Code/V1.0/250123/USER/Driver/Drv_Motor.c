#include "Drv_Motor.h"

/*
*****************************************************************
 * 函数原型：void Motor_Init(void)
 * 功    能：电机初始化起步电压25
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_RESET);//不使能电机
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//开启tim1通道一
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//开启tim1通道二
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);//开启tim1通道三
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);//开启tim1通道四
}
