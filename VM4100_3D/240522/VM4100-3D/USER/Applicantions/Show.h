#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********全局变量声明******/
extern uint32_t Twinkle_Time;//闪烁时间和全部工位设置时闪烁的工位时间

/**********全局函数**********/
void Show_Display(void);//显示屏幕内容
void Check_ShowFlag(float dT);//闪烁检测

#endif
