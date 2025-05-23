#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********宏定义************/
#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004
#define BIT3 0x0008
#define BIT4 0x0010
#define BIT5 0x0020
#define BIT6 0x0040
#define BIT7 0x0080
#define BIT8 0x0100
#define BIT9 0x0200
#define BIT10 0x0400
#define BIT11 0x0800
#define BIT12 0x1000
#define BIT13 0x2000
#define BIT14 0x4000
#define BIT15 0x8000

/**********结构体************/
/**********全局变量声明******/
extern float Pmode_Twinkle_Time,Speed_Twinkle_Time,Temp_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间、温度闪烁时间和时间闪烁时间
extern float PModeP1_Twinkle_Time, PModeP2_Twinkle_Time;
#define ABS(x) ((x)>0?(x):-(x))

/**********全局函数**********/
void Show_Display(void);//显示屏幕内容
void Twinkle(float dT);//闪烁函数
void Deal_Speed(float dT);//速度显示处理
void Deal_Temp(float dT);//温度显示处理

#endif
