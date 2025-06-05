#include "Drv_Motor.h"

/*
*****************************************************************
 * 函数原型：void Drv_Motor_Init(void)
 * 功    能：Motor驱动初始化
*****************************************************************
*/
void Drv_Motor_Init(void)
{
    GPIO_SET_MUX_MODE(P20CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_0);
    
    Motor_OFF;//关闭电机
}
