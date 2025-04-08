#ifndef __DRV_BEEP_H__
#define __DRV_BEEP_H__

#include "include.h"

/**********宏定义************/
#define Beep_ON GPIO_WriteHigh(GPIO0, GPIO_PIN_2)// 打开蜂鸣器
#define Beep_OFF GPIO_WriteLow(GPIO0, GPIO_PIN_2)// 关闭蜂鸣器

/**********结构体************/
/**********全局变量声明******/
extern float Beep_Time;  // 蜂鸣器响的时间
extern float Beep_Flash; // 蜂鸣器响的次数

/**********全局函数***********/

void Buzzer_Status(float dT);

#endif
