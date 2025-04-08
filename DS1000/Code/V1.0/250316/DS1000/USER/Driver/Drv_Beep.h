#ifndef __DRV_BEEP_H__
#define __DRV_BEEP_H__

#include "include.h"

/**********宏定义************/
#define Beep_ON  BUZ_EnableBuzzer()//打开蜂鸣器
#define Beep_OFF BUZ_DisableBuzzer()//关闭蜂鸣器

/**********全局变量**********/
extern float Beep_Time;//蜂鸣器响的时间
extern float Beep_Flash;//蜂鸣器响的次数

/**********全局函数**********/
void Drv_BUZZER_Init(void);//蜂鸣器驱动初始化
void Buzzer_Status(float dT);//蜂鸣器的状态检测

#endif
