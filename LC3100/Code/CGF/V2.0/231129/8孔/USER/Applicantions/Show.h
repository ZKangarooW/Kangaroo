#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float Twinkle_Time;//��˸ʱ���ȫ����λ����ʱ��˸�Ĺ�λʱ��
#define ABS(x) ((x)>0?(x):-(x))

/**********ȫ�ֺ���**********/
void Show_Display(void);//��ʾ��Ļ����
void Twinkle(float dT);//��˸����
void Deal_Speed(float dT);//�ٶ���ʾ����

#endif
