#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
extern uint16_t Speed_Val[111];
extern uint16_t Speed_PWM[111];
extern uint16_t xg_Val[111];
/**********全局函数**********/
void Motor_Ctrl(float dT);//电机控制
void Check_MotorStop(float dT);//检测电机是否停止，停止后开盖

#endif
