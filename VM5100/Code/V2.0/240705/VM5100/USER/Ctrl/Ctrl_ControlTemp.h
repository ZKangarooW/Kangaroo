#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/
#if(Integration_TYPE <= 1)//设置成四联时
#define HEAT htim4.Instance->CCR4//加热模块PWM
#elif(Integration_TYPE == 2)//设置成六联和八联时
#define HEAT htim4.Instance->CCR4//加热模块PWM
#endif

/**********全局变量**********/
extern uint8_t Temp_Control;//温度控制开关
extern uint8_t Add_Ctrl;//温度补偿值
extern int Temp_Out;//温度pwm输出值

/**********全局函数**********/
void temp_Control(void);//温度加热控制

#endif
