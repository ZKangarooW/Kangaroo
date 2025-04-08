#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********宏定义************/
#define COLD htim3.Instance->CCR1
#define HEAT htim3.Instance->CCR2
#define HEATGAI htim3.Instance->CCR3

/**********结构体************/
/**********全局变量声明*******/
/**********全局函数**********/

void HEAT_Init(void);
void HEAT_Duty(float dT, int16_t pwm);

#endif
