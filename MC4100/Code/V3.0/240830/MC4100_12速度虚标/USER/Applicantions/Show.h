#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********�궨��************/
#define ABS(x) ((x) > 0 ? (x) : -(x)) // ȡ����ֵ

/**********ȫ�ֱ�������******/
extern float Twinkle_Time;//��˸ʱ���ȫ����λ����ʱ��˸�Ĺ�λʱ��

/**********ȫ�ֺ���**********/
void Show_Display(void);//��ʾ��Ļ����
void Twinkle(float dT);//��˸����
void Deal_Speed(void);

#endif
