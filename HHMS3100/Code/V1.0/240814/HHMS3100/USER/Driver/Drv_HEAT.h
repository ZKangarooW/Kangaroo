#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********宏定义************/
#define HEAT2 htim4.Instance->CCR1 // HEAT PWM输出 （0~200）
#define HEAT0 htim4.Instance->CCR2 // HEAT PWM输出 （0~200）
#define HEAT3 htim4.Instance->CCR3 // HEAT PWM输出 （0~200）
#define HEAT1 htim4.Instance->CCR4 // HEAT PWM输出 （0~200）

/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
void HEAT_Init(void);//初始化加热

#endif
