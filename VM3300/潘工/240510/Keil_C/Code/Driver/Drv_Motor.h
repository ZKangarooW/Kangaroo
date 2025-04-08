#ifndef  __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "include.h"

/**********宏定义*************/
#define CW   GPIO_WriteHigh(GPIO0, GPIO_PIN_6)//顺时针
#define CCW GPIO_WriteLow(GPIO0, GPIO_PIN_6)//逆时针
#define MO_ON   GPIO_WriteHigh(GPIO0, GPIO_PIN_5)//打开电机电源
#define MO_OFF GPIO_WriteLow(GPIO0, GPIO_PIN_5)//关闭电机电源

/**********结构体*************/
/**********全局变量声明*****/
/**********全局函数**********/

void Drv_Motor_Init(void);

#endif
