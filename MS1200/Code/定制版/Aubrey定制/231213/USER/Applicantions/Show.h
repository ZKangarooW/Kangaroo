#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********ȫ�ֱ�������******/
extern uint8_t Display_Flag;//������ʾˢ��
extern uint8_t Display_OFF;//����ʾ��Ļ
#define ABS(x) ((x)>0?(x):-(x))

/**********ȫ�ֺ���**********/
void Show_Display(void);//��ʾ��Ļ����
void Deal_Speed(void);//�ٶ���ʾ����
void Check_Display(float dT);//��ⲻ����ʱϨ��

#endif
