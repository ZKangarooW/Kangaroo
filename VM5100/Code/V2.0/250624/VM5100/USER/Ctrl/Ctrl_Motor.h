#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define PWM htim1.Instance->CCR1//motor1 PWM输出 （0~200）

/**********全局函数**********/
void Motor_Ctrl(void);//电机控制
void Motor_Init(void);//电机初始化
void Check_MotorStop(float dT);//检测电机是否停止

#endif
