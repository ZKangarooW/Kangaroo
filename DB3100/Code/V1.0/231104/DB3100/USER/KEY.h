#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

/**********宏定义************/
#define KEY_ON  1
#define KEY_OFF 2

/**********全局变量**********/
extern uint16_t run_mode;//运行模式
extern uint8_t Key_Status;//在操作按键时

/**********全局函数**********/
void Key_Handle(float dT);//按键功能
void Check_Key(void);//检测按键状态-1s

#endif
