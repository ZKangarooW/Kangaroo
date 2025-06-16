#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********宏定义************/
#define KEY1 0x01
#define KEY2 0x02
#define KEY3 0x04
#define KEY4 0x08

/**********全局变量声明******/
extern float Key_Status;//按键按下标志

/**********局部变量声明******/
/**********全局函数**********/
void Key_Scan(float dT);//矩阵按键扫描
void Check_Press(float dT);//检测按键按下状态

#endif

