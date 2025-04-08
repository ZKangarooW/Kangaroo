#ifndef __BEEP_H__
#define __BEEP_H__

#include "main.h"

/**********宏定义************/
#define Beep_ON  HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_SET)//打开蜂鸣器
#define Beep_OFF HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_RESET)//关闭蜂鸣器

/**********全局变量**********/
extern float Beep_Time;//蜂鸣器响的时间

/**********全局函数**********/
void Buzzer_Status(float dT);//蜂鸣器的状态检测

#endif
