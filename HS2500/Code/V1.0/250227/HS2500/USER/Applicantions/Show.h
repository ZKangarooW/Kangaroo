#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float Speed_Twinkle_Time,Temp_Twinkle_Time,Time_Twinkle_Time,Pmode_Twinkle_Time;//�ٶ���˸ʱ�䡢�¶���˸ʱ���ʱ����˸ʱ��
#define ABS(x) ((x)>0?(x):-(x))

/**********ȫ�ֺ���**********/
void Show_Display(void);//��ʾ��Ļ����
void Twinkle(float dT);//��˸����
void Deal_Speed(float dT);//�ٶ���ʾ����
void Deal_Temp(float dT);//�¶���ʾ����

#endif
