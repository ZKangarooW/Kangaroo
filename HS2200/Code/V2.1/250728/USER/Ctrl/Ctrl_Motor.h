#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void Motor_PID(void);//电机控制PID系数
void Motor_Ctrl(float dT);//电机控制
void Check_MotorStop(float dT);

#endif
