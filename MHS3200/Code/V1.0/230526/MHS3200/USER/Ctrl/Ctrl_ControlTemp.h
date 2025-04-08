#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/
#if(Integration_TYPE <= 1)//设置成四联和六联时
#define HEAT htim4.Instance->CCR4//加热模块PWM
#elif(Integration_TYPE == 2)//设置成九联时
#define HEAT htim4.Instance->CCR2//加热模块PWM
#endif

/**********全局变量**********/
extern int HEAT_Time;//温度pwm输出时间

/**********全局函数**********/
void temp_Control(float dT);//温度加热控制
void PID_Cap(float dT);//pid计算

#endif
