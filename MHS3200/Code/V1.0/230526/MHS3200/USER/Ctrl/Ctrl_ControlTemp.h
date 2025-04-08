#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/
#if(Integration_TYPE <= 1)//���ó�����������ʱ
#define HEAT htim4.Instance->CCR4//����ģ��PWM
#elif(Integration_TYPE == 2)//���óɾ���ʱ
#define HEAT htim4.Instance->CCR2//����ģ��PWM
#endif

/**********ȫ�ֱ���**********/
extern int HEAT_Time;//�¶�pwm���ʱ��

/**********ȫ�ֺ���**********/
void temp_Control(float dT);//�¶ȼ��ȿ���
void PID_Cap(float dT);//pid����

#endif
