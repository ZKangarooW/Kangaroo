#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********�궨��************/
#define LCD_ON  1//�򿪱���
#define LCD_OFF 0//�رձ���

/**********ȫ�ֱ�������******/
extern uint16_t Twinkle_Time1,Twinkle_Time2;//��˸ʱ��

/**********ȫ�ֺ���**********/
void LCD_Light(short LCD_Status);//�򿪺͹رձ�����ʾ
void Show_Display(void);//��ʾ��Ļ����
void Check_ShowFlag(float dT);//��˸���

#endif
