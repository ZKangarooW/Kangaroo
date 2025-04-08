#ifndef __DRV_TOUCH_H__
#define __DRV_TOUCH_H__

#include "include.h"

/**********宏定义************/
#define Key1 0x00000002
#define Key2 0x00000004
#define Key3 0x00000008

/**********结构体************/
/**********全局变量声明******/
extern float Key_Status;//按键按下标志

/**********全局函数***********/

void Drv_Touch_Init(void);
void Touch_Scan(float dT);
void Check_Press(float dT);

#endif