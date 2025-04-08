#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/
#define ABS(x) ((x)>0?(x):-(x))

/**********全局变量**********/
extern uint8_t Protect,Display_Res;//防干烧保护和加水后显示

/**********全局函数**********/
void Temp_PID(void);//温度控制PID系数
void Temp_Control(float dT);//温度加热控制
void Check_FGS(float dT);//检测防干烧
void Check_AddWater(float dT);//检测加水
void Check_TempStop(float dT);//检测温度是否停止上升
#endif
