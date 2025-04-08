#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

#if(Integration_TYPE == 0)//设置成四联和六联时
/**********宏定义************/
#define HEAT htim4.Instance->CCR4//加热模块PWM

/**********全局变量**********/
extern int HEAT_Time;//温度pwm输出时间

/**********全局函数**********/
void temp_Control(float dT);//温度加热控制
void PID_Cap(float dT);//pid计算

#endif

#endif
