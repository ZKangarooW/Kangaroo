#ifndef __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define Motor_ON  P20 = 1//打开电机电源
#define Motor_OFF P20 = 0//关闭电机电源

/**********全局变量**********/

/**********全局函数**********/
void Drv_Motor_Init(void);//Motor驱动初始化

#endif
