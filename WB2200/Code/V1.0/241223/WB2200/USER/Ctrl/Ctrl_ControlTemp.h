#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/

/**********全局变量声明******/

/**********全局函数**********/
void Temp_PID(void);//温度控制PID系数
void Temp_Control(float dT);//温度加热控制

#endif
