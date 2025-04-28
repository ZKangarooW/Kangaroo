#ifndef __DRV_BEEP_H__
#define __DRV_BEEP_H__

#include "include.h"

/**********�궨��************/
#define Beep_ON  BUZ_EnableBuzzer()//�򿪷�����
#define Beep_OFF BUZ_DisableBuzzer()//�رշ�����

/**********ȫ�ֱ���**********/
extern float Beep_Time;//���������ʱ��
extern float Beep_Flash;//��������Ĵ���

/**********ȫ�ֺ���**********/
void Drv_BUZZER_Init(void);//������������ʼ��
void Buzzer_Status(float dT);//��������״̬���

#endif
