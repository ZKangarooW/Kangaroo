#ifndef __DRV_EC11A_H__
#define __DRV_EC11A_H__

#include "include.h"

/**********全局变量声明******/
extern uint8_t EC11A_Knob;//在旋动旋钮时

/**********全局函数**********/
void EC11A_FlagCheak(uint16_t dT);//旋钮延时检测
void Check_KeyState(void);//按键检测
void Check_Knob(void);//检测旋钮状态

#endif
