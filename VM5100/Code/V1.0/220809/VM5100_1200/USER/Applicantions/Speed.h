#ifndef __SPEED_H__
#define __SPEED_H__

#include "include.h"

/**********ȫ�ֱ�������******/
extern uint8_t CAPTURE_Status;//����״̬
extern uint16_t TIM1CH1_CAPTURE_STA;//����������

/**********ȫ�ֺ���**********/
void Encoder_Init(void);//��������ʼ�� 
void Check_Speed(void);//����ٶ��Ƿ�ֹͣ
void Check_Status(void);//���״̬

#endif
