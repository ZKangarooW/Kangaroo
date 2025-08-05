#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********宏定义************/
#define HEAT htim15.Instance->CCR1//加热模块PWM
#define HEAT_ON()  HAL_GPIO_WritePin(HEAT_GPIO_Port,HEAT_Pin,GPIO_PIN_SET);//打开加热模块
#define HEAT_OFF() HAL_GPIO_WritePin(HEAT_GPIO_Port,HEAT_Pin,GPIO_PIN_RESET);//关闭加热模块

/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void HEAT_Init(void);//初始化加热

#endif
