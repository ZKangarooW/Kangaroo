#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********宏定义************/
#if (Integration_TYPE == 0)
    #define PWM_L1 htim4.Instance->CCR2//motor1 PWM输出 （0~200）
    #define PWM_L2 htim4.Instance->CCR1//motor2 PWM输出 （0~200）
    #define PWM_L3 htim2.Instance->CCR1//motor3 PWM输出 （0~200）
    #define PWM_L4 htim2.Instance->CCR4//motor4 PWM输出 （0~200）
    #define PWM_L5 htim2.Instance->CCR2//motor5 PWM输出 （0~200）
    #define PWM_L6 htim2.Instance->CCR3//motor6 PWM输出 （0~200）
#elif (Integration_TYPE == 1)   
	#define PWM_L1 htim3.Instance->CCR3//motor5 PWM输出 （0~200）
	#define PWM_L2 htim3.Instance->CCR4//motor6 PWM输出 （0~200）
	#define PWM_L3 htim3.Instance->CCR1//motor7 PWM输出 （0~200）
	#define PWM_L4 htim5.Instance->CCR4//motor4 PWM输出 （0~200）
	#define PWM_L5 htim5.Instance->CCR3//motor3 PWM输出 （0~200）
	#define PWM_L6 htim3.Instance->CCR2//motor8 PWM输出 （0~200）
	#define PWM_L7 htim5.Instance->CCR2//motor2 PWM输出 （0~200）
    #define PWM_L8 htim5.Instance->CCR1//motor1 PWM输出 （0~200）
    #define PWM_L9 htim4.Instance->CCR1//motor9 PWM输出 （0~200）
#endif

/**********全局函数**********/
void Motor_Ctrl(void);//电机控制
void Motor_Init(void);//电机初始化
void Motor_Check(float dT);//电机停止检测
#endif
