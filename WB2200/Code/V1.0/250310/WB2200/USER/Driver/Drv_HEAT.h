#ifndef __DRV_HEAT_H__
#define	__DRV_HEAT_H__

#include "include.h"

/**********宏定义************/
#define HEAT htim3.Instance->CCR2//HEAT加热 PWM输出 （0~1000）

/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
void HEAT_Init(void);//初始化加热

#endif
