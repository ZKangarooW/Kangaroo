#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********ȫ�ֱ���**********/
extern uint8_t Key_Status;//�ڲ�������ʱ
extern uint8_t SetMode_Option;//ѡ������ģʽ

/**********ȫ�ֺ���**********/
void Key_Scan(float dT);//���󰴼�ɨ��
void Check_Key(void);//��ⰴ��״̬-1s

#endif
