#ifndef __SHOW_9_H__
#define __SHOW_9_H__

#include "include.h"

/**********宏定义************/
#define LCD_ON  1//打开背光
#define LCD_OFF 0//关闭背光

/**********全局变量声明******/
extern uint16_t Twinkle_Time;//闪烁时间和全部工位设置时闪烁的工位时间

/**********全局函数**********/
void LCD_Light(short LCD_Status);//打开和关闭背光显示
void Show_Display(void);//显示屏幕内容
void Check_ShowFlag(uint16_t dT);//闪烁检测

#endif
