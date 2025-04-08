#ifndef __DRV_HEAT_H__
#define	__DRV_HEAT_H__

#include "include.h"

/**********宏定义************/
#define HEAT htim1.Instance->CCR1//HEAT加热 PWM输出 （0~1200）

/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void Temp_Init(void);//温度初始化

#endif
