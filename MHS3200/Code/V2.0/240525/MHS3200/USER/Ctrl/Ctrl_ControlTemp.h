#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

#if(Integration_TYPE == 0)//���ó�����������ʱ
/**********�궨��************/
#define HEAT htim4.Instance->CCR4//����ģ��PWM

/**********ȫ�ֱ���**********/
extern int HEAT_Time;//�¶�pwm���ʱ��

/**********ȫ�ֺ���**********/
void temp_Control(float dT);//�¶ȼ��ȿ���
void PID_Cap(float dT);//pid����

#endif

#endif
