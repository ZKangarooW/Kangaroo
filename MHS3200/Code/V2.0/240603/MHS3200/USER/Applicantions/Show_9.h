#ifndef __SHOW_9_H__
#define __SHOW_9_H__

#include "include.h"

/**********�궨��************/
#define LCD_ON  1//�򿪱���
#define LCD_OFF 0//�رձ���

/**********ȫ�ֱ�������******/
extern uint16_t Twinkle_Time;//��˸ʱ���ȫ����λ����ʱ��˸�Ĺ�λʱ��

/**********ȫ�ֺ���**********/
void LCD_Light(short LCD_Status);//�򿪺͹رձ�����ʾ
void Show_Display(void);//��ʾ��Ļ����
void Check_ShowFlag(uint16_t dT);//��˸���

#endif
