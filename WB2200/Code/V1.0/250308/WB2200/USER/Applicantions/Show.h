#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********�궨��************/
#define ABS(x) ((x) > 0 ? (x) : -(x)) // ȡ����ֵ

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float Twinkle_Time;//��˸ʱ��
extern uint8_t Temp_ShowFlag;
/**********ȫ�ֺ���**********/
void Show_Display(void);//��ʾ��Ļ����
void Twinkle(float dT);//��˸����
void Deal_Temp(float dT);//�¶���ʾ����

#endif
