#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********ȫ�ֺ���**********/
void Motor_PID(void);//�������PIDϵ��
void Motor_Ctrl(float dT);//�������
void Check_MotorStop(float dT);//������Ƿ�ֹͣ��ֹͣ�󿪸�

#endif
