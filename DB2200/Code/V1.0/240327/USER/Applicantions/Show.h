#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********ȫ�ֱ�������******/
extern uint16_t Twinkle_Time;//��˸ʱ���ȫ����λ����ʱ��˸�Ĺ�λʱ��
#define ABS(x) ((x)>0?(x):-(x))

/**********ȫ�ֺ���**********/
void LCD_Display(void);//��ʾ��Ļ����
void Check_ShowFlag(uint16_t dT);//��˸���
void ADD_Show(uint16_t dT);
void Circle_Go(void);
void Check_Show_PModeFlag(float dT);
void time_icn(float dT);//����ʱʱ��ͼ����˸ 
//void CtrlTemp_Error(float dT);

#endif
