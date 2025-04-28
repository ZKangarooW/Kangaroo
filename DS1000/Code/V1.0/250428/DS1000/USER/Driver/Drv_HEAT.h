#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********�궨��************/
#define Heater_SCR_IO P20

#define On 0//��
#define Off 1//��

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF

/**********�ṹ��************/
typedef struct 
{
	uint8_t SCROn;//�Ƿ�������
	uint8_t SCRCnt;//��ʱ
	uint8_t SCROnTimeSet;//������ʱ��
	uint8_t SCRFullTimeSet;//������ʱ��
    uint8_t PWM;//��ֵ������ʱ��
}Heater_t;
extern Heater_t Heater;//�ع���

/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void HEAT_Init(void);//��ʼ������
void GPIO_Interrupt(void);//�������������ж�������
void Timer1_IRQ(void);//��ʱ��1�ж�������

#endif
