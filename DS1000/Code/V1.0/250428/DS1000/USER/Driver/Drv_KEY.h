#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********�궨��************/
#define KEY1 0x01
#define KEY2 0x02
#define KEY3 0x04
#define KEY4 0x08

/**********ȫ�ֱ�������******/
extern float Key_Status;//�������±�־

/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Key_Scan(float dT);//���󰴼�ɨ��
void Check_Press(float dT);//��ⰴ������״̬

#endif

