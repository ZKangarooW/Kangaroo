#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/

/**********全局变量声明******/
extern bool tuning_complete;//自动调参标志位
extern float last_peak_time;//上一个周期
extern int oscillation_count;//震荡周期

/**********全局函数**********/
void Temp_PID(void);//温度控制PID系数
void Temp_Control(float dT);//温度加热控制

#endif
