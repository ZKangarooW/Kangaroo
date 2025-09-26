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
    
    if(Param.type == 0)//10L15L
        HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//顺时针
    else if(Param.type >= 1)//30L50L
        HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//顺时针
	
	Speed.CwIcn = 1;//顺时针图标
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//开启tim1通道一
}
