#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********全局变量声明******/
extern uint8_t Key_Status;//按键按下标志

/**********局部变量声明******/
/**********全局函数**********/
void Key_Scan(float dT);//矩阵按键扫描
void Check_Press(float dT);//检测按键按下状态

#endif
