#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

/**********�궨��************/

/**********ȫ�ֱ���**********/
extern uint16_t run_mode;//����ģʽ
extern uint8_t Key_Status;//�ڲ�������ʱ

/**********ȫ�ֺ���**********/
void Key_Handle(float dT);//��������
void Check_Key(void);//��ⰴ��״̬-1s

#endif
