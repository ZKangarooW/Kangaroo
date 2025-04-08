#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/
#define COLD htim3.Instance->CCR1//����ģ��PWM
#define HEAT htim3.Instance->CCR2//����ģ��PWM

/**********ȫ�ֱ���**********/
extern uint16_t Temp_P[3][2];
extern int Temp_Out;//�¶�pwm���ֵ

/**********ȫ�ֺ���**********/
void Temp_Control(float dT);//�¶ȼ��ȿ���
void PID_Init(void);//PID������ʼ��

#endif
