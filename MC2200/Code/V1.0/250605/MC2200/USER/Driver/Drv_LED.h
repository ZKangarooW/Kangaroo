#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "include.h"

/**********宏定义************/
#define LED1_ON  P00 = 1//打开电源报警灯
#define LED1_OFF P00 = 0//关闭电源报警灯

#define LED2_ON  P02 = 1//打开系统运行灯
#define LED2_OFF P02 = 0//关闭系统运行灯
/**********全局变量**********/

/**********全局函数**********/
void Drv_LED_Init(void);//LED驱动初始化

#endif
