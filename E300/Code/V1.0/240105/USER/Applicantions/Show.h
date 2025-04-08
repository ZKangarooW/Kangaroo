#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********宏定义************/
#define ABS(x) ((x)>0?(x):-(x))

/**********结构体************/
/**********全局变量声明******/
extern float Temp_Twinkle_Time,Time_Twinkle_Time;//温度闪烁时间和时间闪烁时间

/**********全局函数**********/
void Show_Display(void);//显示屏幕内容
void Twinkle(float dT);//闪烁函数
void Deal_Speed(void);//速度显示处理

#endif
