#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********宏定义************/
#define ABS(x) ((x) > 0 ? (x) : -(x)) // 取绝对值

/**********结构体************/
/**********全局变量声明******/
extern float Twinkle_Time;//闪烁时间
extern uint8_t Temp_ShowFlag;
/**********全局函数**********/
void Show_Display(void);//显示屏幕内容
void Twinkle(float dT);//闪烁函数
void Deal_Temp(float dT);//温度显示处理

#endif
