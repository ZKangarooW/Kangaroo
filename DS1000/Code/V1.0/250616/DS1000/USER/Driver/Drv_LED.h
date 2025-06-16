#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "include.h"

/**********宏定义************/
#define LED_ON  P05 = 0//打开蜂鸣器
#define LED_OFF P05 = 1//关闭蜂鸣器

/**********全局变量**********/

/**********全局函数**********/
void Drv_LED_Init(void);//LED驱动初始化

#endif
