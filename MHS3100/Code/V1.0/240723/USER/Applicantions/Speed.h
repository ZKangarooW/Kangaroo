#ifndef __SPEED_H__
#define __SPEED_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void Encoder_Init(void);//��������ʼ�� 
void Check_Speed(float dT);//����ٶ��Ƿ�ֹͣ
void Speed_Capture_Interrupt(TIM_HandleTypeDef *htim);//�ٶȲ����жϺ���

#endif
