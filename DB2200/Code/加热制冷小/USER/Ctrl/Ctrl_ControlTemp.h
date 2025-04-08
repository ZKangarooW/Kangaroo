#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/
#define COLD htim3.Instance->CCR1//制冷模块PWM
#define HEAT htim3.Instance->CCR2//加热模块PWM

/**********全局变量**********/
extern uint16_t Temp_P[3][2];
extern int Temp_Out;//温度pwm输出值

/**********全局函数**********/
void Temp_Control(float dT);//温度加热控制
void PID_Init(void);//PID参数初始化

#endif
