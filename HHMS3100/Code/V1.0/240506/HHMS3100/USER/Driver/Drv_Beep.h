#ifndef __DRV_BEEP_H__
#define __DRV_BEEP_H__

#include "include.h"

/**********�궨��************/
#define Beep_ON HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_SET)//�򿪷�����
#define Beep_OFF HAL_GPIO_WritePin(Beep_GPIO_Port, Beep_Pin, GPIO_PIN_RESET)//�رշ�����

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float Beep_Time;//���������ʱ��
extern float Beep_Flash;//��������Ĵ���

/**********ȫ�ֺ���***********/

void Buzzer_Status(float dT);
void Buzzer_Task(void *p);

#endif
