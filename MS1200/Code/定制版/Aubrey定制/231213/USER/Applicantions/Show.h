#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********全局变量声明******/
extern uint8_t Display_Flag;//用于显示刷新
extern uint8_t Display_OFF;//不显示屏幕
#define ABS(x) ((x)>0?(x):-(x))

/**********全局函数**********/
void Show_Display(void);//显示屏幕内容
void Deal_Speed(void);//速度显示处理
void Check_Display(float dT);//检测不操作时熄屏

#endif
