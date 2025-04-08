#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********�궨��************/
#define Heater_SCR_IO P20

typedef struct 
{
	unsigned char SCROn;
	unsigned char SCRCnt;
	unsigned char SCROnTimeSet;
	unsigned char SCRFullTimeSet;
}Heater_t;
extern Heater_t Heater;

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void HEAT_Init(void);//��ʼ������
void CtrlHeater_SCR(void);
void Timer1_IRQ(void);
void GPIO_Interrupt(void);
    
#endif
