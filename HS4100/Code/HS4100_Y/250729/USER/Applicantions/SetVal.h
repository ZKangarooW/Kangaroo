#ifndef __SETVAL_H__
#define __SETVAL_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
extern uint8_t SpeedSet_Flag,TempSet_Flag,TimeSet_Flag;//速度设置，温度设置，时间设置

/**********全局函数**********/
void Check_Set(float dT);//检测设置

#endif
