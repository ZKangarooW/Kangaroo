#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********�궨��************/
#define PWM htim3.Instance->CCR1//motor PWM��� ��0~400��

/**********ȫ�ֺ���**********/
void Motor_Ctrl(void);//�������
void Motor_Init(void);//�����ʼ��
void Motor_Check(float dT);//���ֹͣ���
void Check_MotorStop(float dT);//������Ƿ�ֹͣ��ֹͣ�󿪸�

#endif
