#ifndef __SETVAL_H__
#define __SETVAL_H__

#include "include.h"

/**********全局变量声明******/
extern uint8_t SetOK_Flag,CtrlMode;//检测是否波动旋钮和设置标志位

/**********全局函数**********/
void Check_Set(void);//检测设置
void Check_CtrlTemp_Mode(void);
#endif
