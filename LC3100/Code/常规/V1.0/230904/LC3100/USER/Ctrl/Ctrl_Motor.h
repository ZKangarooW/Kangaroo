#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********全局变量声明******/
extern float R;//离心率的半径

/**********全局函数**********/
void Motor_Ctrl(float dT);//电机控制
void Check_MotorStop(float dT);//检测电机是否停止，停止后开盖

#endif
