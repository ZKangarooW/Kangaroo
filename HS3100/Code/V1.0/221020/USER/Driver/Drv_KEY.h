#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********ȫ�ֱ�������******/
extern uint8_t Key_Status;//�������±�־

/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Key_Scan(float dT);//���󰴼�ɨ��
void Check_Press(float dT);//��ⰴ������״̬

#endif
