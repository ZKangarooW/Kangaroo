#ifndef __CTRL_MOTOR_H__
#define __CTRL_MOTOR_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint16_t Speed_Val[111];
extern uint16_t Speed_PWM[111];
extern uint16_t xg_Val[111];
/**********ȫ�ֺ���**********/
void Motor_Ctrl(float dT);//�������
void Check_MotorStop(float dT);//������Ƿ�ֹͣ��ֹͣ�󿪸�

#endif
