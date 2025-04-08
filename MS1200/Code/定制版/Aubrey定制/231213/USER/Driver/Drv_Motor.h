#ifndef __DRV_MOTOR_H__
#define	__DRV_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define PWM htim1.Instance->CCR1//motor PWM输出（0~200）

/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void Motor_Init(void);//电机初始化

#endif
