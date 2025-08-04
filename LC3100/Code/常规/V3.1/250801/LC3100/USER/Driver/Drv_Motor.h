#ifndef __DRV_MOTOR_H__
#define	__DRV_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define PWM htim3.Instance->CCR4//motor PWM输出 （0~400）
#define COLD_ON  HAL_GPIO_WritePin(COLD_GPIO_Port,COLD_Pin,GPIO_PIN_SET)//风扇打开
#define COLD_OFF HAL_GPIO_WritePin(COLD_GPIO_Port,COLD_Pin,GPIO_PIN_RESET)//风扇关闭

/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void Motor_Init(void);//电机初始化

#endif
