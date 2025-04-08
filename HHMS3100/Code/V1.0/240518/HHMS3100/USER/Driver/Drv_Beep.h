#ifndef __DRV_BEEP_H__
#define __DRV_BEEP_H__

#include "include.h"

/**********宏定义************/
#define Beep_ON HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_SET)//打开蜂鸣器
#define Beep_OFF HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_RESET)//关闭蜂鸣器

/**********结构体************/
/**********全局变量声明******/
extern float Beep_Time;//蜂鸣器响的时间
extern float Beep_Flash;//蜂鸣器响的次数

/**********全局函数***********/

void Buzzer_Status(float dT);
void Buzzer_Task(void *p);

#endif
