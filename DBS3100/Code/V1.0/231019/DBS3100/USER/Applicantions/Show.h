#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Show_Display(void);//��ʾ��Ļ����
void Twinkle(float dT);//��˸����
void Judge_SpeedMode(void);//�ж��ٶ���ʾ��ģʽ
void Judge_TempMode(void);//�ж��¶���ʾ��ģʽ
void Deal_Speed(float dT);//�ٶ���ʾ����
void Deal_Temp(float dT);//�¶���ʾ����

#endif
