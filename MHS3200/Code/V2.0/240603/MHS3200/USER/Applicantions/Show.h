#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********宏定义************/
#define LCD_ON  1//打开背光
#define LCD_OFF 0//关闭背光

/**********全局变量声明******/
extern uint16_t Twinkle_Time;//闪烁时间和全部工位设置时闪烁的工位时间
extern uint8_t TempDown_FLag;//时间控制显示温度下降
extern uint8_t TempAdd_FLag;//时间控制显示温度上升
extern uint8_t TempSlowDown_FLag;//时间控制显示温度缓慢下降

/**********全局函数**********/
void LCD_Light(short LCD_Status);//打开和关闭背光显示
void Show_Display(void);//显示屏幕内容
void Check_ShowFlag(uint16_t dT);//闪烁检测
void ADD_Show(float dT);
void Start_SpeedRun(float dT);//转速动画

#endif
