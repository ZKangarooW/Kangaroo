#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明*******/
/**********全局函数**********/

void Motor_PID(void);
void Motor_Ctrl(float dT);
void Check_MotorStop(float dT);//检测电机是否停止，停止后开盖

#endif
