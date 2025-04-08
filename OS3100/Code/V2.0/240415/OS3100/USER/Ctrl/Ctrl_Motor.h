#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define PWM htim3.Instance->CCR1//motor PWM输出 （0~400）

/**********全局函数**********/
void Motor_Ctrl(void);//电机控制
void Motor_Init(void);//电机初始化
void Motor_Check(float dT);//电机停止检测
void Check_MotorStop(float dT);//检测电机是否停止，停止后开盖

#endif
