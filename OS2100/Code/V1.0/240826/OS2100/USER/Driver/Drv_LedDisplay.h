#ifndef __DRV_LEDDISPLAY_H__
#define	__DRV_LEDDISPLAY_H__

#include "include.h"

/**********�궨��************/
#define DIG9_OFF HAL_GPIO_WritePin(DIG9_GPIO_Port, DIG9_Pin, GPIO_PIN_SET);
#define DIG9_ON HAL_GPIO_WritePin(DIG9_GPIO_Port, DIG9_Pin, GPIO_PIN_RESET);
#define DIG10_OFF HAL_GPIO_WritePin(DIG10_GPIO_Port, DIG10_Pin, GPIO_PIN_SET);
#define DIG10_ON HAL_GPIO_WritePin(DIG10_GPIO_Port, DIG10_Pin, GPIO_PIN_RESET);

/**********ȫ�ֱ�������******/
extern float Twinkle_Time;//��˸ʱ��

/**********ȫ�ֺ���**********/
void Display_Show(float dT);//��ʾ��Ļ
void Check_ShowFlag(float dT);//��˸���
void Deal_Speed(void);//�ٶ���ʾ����


#endif
