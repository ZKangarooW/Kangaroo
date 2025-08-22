#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/
#define ABS(x) ((x)>0?(x):-(x))

/**********全局变量声明******/
extern uint8_t Protect;//防干烧
extern uint16_t LIMIT_Val;//积分限制

/**********全局函数**********/
void Temp_PID(void);//温度控制PID系数
void Temp_Control(float dT);//温度加热控制

#endif
