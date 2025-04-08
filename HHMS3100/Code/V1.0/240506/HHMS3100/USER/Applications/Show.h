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
#define ABS(x) ((x) > 0 ? (x) : -(x)) 

/**********结构体************/
/**********全局变量声明******/
extern float Twinkle_Time;

/**********全局函数**********/
void Show_Display(void);
void Twinkle(float dT);
void Deal_Speed(float dT);
void Deal_Temp(float dT);

#endif
