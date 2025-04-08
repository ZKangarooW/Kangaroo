#ifndef __SPEED_H__
#define __SPEED_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/

void Speed_Capture_Interrupt(void);
void Check_Status(void);
void Check_Speed(float dT);

#endif
