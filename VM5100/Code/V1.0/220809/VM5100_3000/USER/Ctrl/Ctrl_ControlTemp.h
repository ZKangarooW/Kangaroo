#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/
#if(Integration_TYPE <= 1)//���ó�����ʱ
#define HEAT htim4.Instance->CCR4//����ģ��PWM
#elif(Integration_TYPE == 2)//���ó������Ͱ���ʱ
#define HEAT htim4.Instance->CCR4//����ģ��PWM
#endif

/**********ȫ�ֱ���**********/
extern uint8_t Temp_Control;//�¶ȿ��ƿ���
extern uint8_t Add_Ctrl;//�¶Ȳ���ֵ
extern int Temp_Out;//�¶�pwm���ֵ

/**********ȫ�ֺ���**********/
void temp_Control(void);//�¶ȼ��ȿ���

#endif
