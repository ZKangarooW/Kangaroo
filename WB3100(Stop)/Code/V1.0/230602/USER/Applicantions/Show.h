#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
extern float Twinkle_Time;//闪烁时间

/**********全局函数**********/
void Show_Display(void);//显示屏幕内容
void Twinkle(float dT);//闪烁函数
void Deal_Temp(float dT);//温度显示处理

#endif
