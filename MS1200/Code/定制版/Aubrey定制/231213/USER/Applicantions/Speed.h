#ifndef __SPEED_H__
#define __SPEED_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint16_t TIM1CH3_CAPTURE_STA;//����������
extern uint32_t TIM1CH3_CAPTURE_VAL;//�������ֵ
extern uint32_t P_Status;//�������ڼ���״̬  1���� 0�ر�
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Encoder_Init(void);//��������ʼ�� 
void TIM1_Poll(void);//TIM3��ѵ״̬�л�
void Check_Speed(float dT);//����ٶ��Ƿ�ֹͣ

#endif
