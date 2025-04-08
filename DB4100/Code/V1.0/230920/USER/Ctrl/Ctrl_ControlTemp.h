#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
void Temp_PID(void);//温度控制PID系数
void Temp_Control(float dT);//温度加热控制
void Check_Temp_Time(float dT);//后台检测加热的时间

#endif
