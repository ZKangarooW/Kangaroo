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
    GPIO_SET_MUX_MODE(P05CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5);
    LED_ON;//打开灯
}
