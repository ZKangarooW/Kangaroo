#ifndef __DRV_EC11A_H__
#define __DRV_EC11A_H__

#include "include.h"

/**********ȫ�ֱ�������******/
extern uint8_t EC11A_Knob;//��������ťʱ

/**********ȫ�ֺ���**********/
void EC11A_FlagCheak(uint16_t dT);//��ť��ʱ���
void Check_KeyState(void);//�������
void Check_Knob(void);//�����ť״̬

#endif
