#include "Drv_LED.h"

/**********全局变量**********/

/*
*****************************************************************
 * 函数原型：void Drv_LED_Init(void)
 * 功    能：LED驱动初始化
*****************************************************************
*/
void Drv_LED_Init(void)
{
    GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_0);
    
    GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2);
    
    LED1_OFF;//关闭灯
    LED2_OFF;//关闭灯
}
