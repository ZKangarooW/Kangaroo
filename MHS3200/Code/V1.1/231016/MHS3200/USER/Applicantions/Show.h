#ifndef __SHOW_H__
#define __SHOW_H__

#include "include.h"

/**********�궨��************/
#define LCD_ON  1//�򿪱���
#define LCD_OFF 0//�رձ���

/**********ȫ�ֱ�������******/
extern uint16_t Twinkle_Time;//��˸ʱ���ȫ����λ����ʱ��˸�Ĺ�λʱ��
extern uint8_t TempDown_FLag;//ʱ�������ʾ�¶��½�
extern uint8_t TempAdd_FLag;//ʱ�������ʾ�¶�����
extern uint8_t TempSlowDown_FLag;//ʱ�������ʾ�¶Ȼ����½�

/**********ȫ�ֺ���**********/
void LCD_Light(short LCD_Status);//�򿪺͹رձ�����ʾ
void Show_Display(void);//��ʾ��Ļ����
void Check_ShowFlag(uint16_t dT);//��˸���
void ADD_Show(float dT);
void Start_SpeedRun(float dT);//ת�ٶ���

#endif
