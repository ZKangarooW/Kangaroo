#ifndef __BEEP_H__
#define __BEEP_H__

#include "main.h"

/**********�궨��************/
#define Beep_ON  HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_SET)//�򿪷�����
#define Beep_OFF HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin,GPIO_PIN_RESET)//�رշ�����

/**********ȫ�ֱ���**********/
extern float Beep_Time;//���������ʱ��

/**********ȫ�ֺ���**********/
void Buzzer_Status(float dT);//��������״̬���

#endif
