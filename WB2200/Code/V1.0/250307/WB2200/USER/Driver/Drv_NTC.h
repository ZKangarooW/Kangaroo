#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint16_t ADC_Val;//adc��ֵ

/**********ȫ�ֺ���**********/
void Read_Temp(float dT);//��ȡ�¶�-10ms
void Temp_Init(void);//������ʾ�¶�

#endif
