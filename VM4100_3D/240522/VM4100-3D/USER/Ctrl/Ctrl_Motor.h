#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********�궨��************/
#define Motor1 htim1.Instance->CCR1//motor1 PWM��� ��0~200��

/**********ȫ�ֺ���**********/
void Motor_Ctrl(void);//�������
void Motor_Init(void);//�����ʼ��

#endif
