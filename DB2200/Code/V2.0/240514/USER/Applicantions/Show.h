#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********全局变量声明******/
extern uint16_t Twinkle_Time;//闪烁时间和全部工位设置时闪烁的工位时间
#define ABS(x) ((x)>0?(x):-(x))

/**********全局函数**********/
void LCD_Display(void);//显示屏幕内容
void Check_ShowFlag(uint16_t dT);//闪烁检测
void ADD_Show(uint16_t dT);
void Circle_Go(void);
void Check_Show_PModeFlag(float dT);
void time_icn(float dT);//启动时时间图标闪烁 
//void CtrlTemp_Error(float dT);

#endif
