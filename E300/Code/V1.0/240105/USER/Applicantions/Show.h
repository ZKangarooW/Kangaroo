#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********�궨��************/
#define ABS(x) ((x)>0?(x):-(x))

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float Temp_Twinkle_Time,Time_Twinkle_Time;//�¶���˸ʱ���ʱ����˸ʱ��

/**********ȫ�ֺ���**********/
void Show_Display(void);//��ʾ��Ļ����
void Twinkle(float dT);//��˸����
void Deal_Speed(void);//�ٶ���ʾ����

#endif
