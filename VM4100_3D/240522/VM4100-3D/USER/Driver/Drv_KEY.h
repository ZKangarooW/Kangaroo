#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********全局变量**********/
extern uint8_t Key_Status;//在操作按键时
extern uint8_t SetMode_Option;//选择设置模式

/**********全局函数**********/
void Key_Scan(float dT);//矩阵按键扫描
void Check_Key(void);//检测按键状态-1s

#endif
