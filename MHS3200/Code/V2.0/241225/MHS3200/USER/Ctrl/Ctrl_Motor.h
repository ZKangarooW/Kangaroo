#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********�궨��************/
#if (Integration_TYPE == 0)
    #define PWM_L1 htim4.Instance->CCR2//motor1 PWM��� ��0~200��
    #define PWM_L2 htim4.Instance->CCR1//motor2 PWM��� ��0~200��
    #define PWM_L3 htim2.Instance->CCR1//motor3 PWM��� ��0~200��
    #define PWM_L4 htim2.Instance->CCR4//motor4 PWM��� ��0~200��
    #define PWM_L5 htim2.Instance->CCR2//motor5 PWM��� ��0~200��
    #define PWM_L6 htim2.Instance->CCR3//motor6 PWM��� ��0~200��
#elif (Integration_TYPE == 1)   
	#define PWM_L1 htim3.Instance->CCR3//motor5 PWM��� ��0~200��
	#define PWM_L2 htim3.Instance->CCR4//motor6 PWM��� ��0~200��
	#define PWM_L3 htim3.Instance->CCR1//motor7 PWM��� ��0~200��
	#define PWM_L4 htim5.Instance->CCR4//motor4 PWM��� ��0~200��
	#define PWM_L5 htim5.Instance->CCR3//motor3 PWM��� ��0~200��
	#define PWM_L6 htim3.Instance->CCR2//motor8 PWM��� ��0~200��
	#define PWM_L7 htim5.Instance->CCR2//motor2 PWM��� ��0~200��
    #define PWM_L8 htim5.Instance->CCR1//motor1 PWM��� ��0~200��
    #define PWM_L9 htim4.Instance->CCR1//motor9 PWM��� ��0~200��
#endif

/**********ȫ�ֺ���**********/
void Motor_Ctrl(void);//�������
void Motor_Init(void);//�����ʼ��
void Motor_Check(float dT);//���ֹͣ���
#endif
