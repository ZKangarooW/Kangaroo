#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint16_t ADC_Val;//adc��ֵ

/**********ȫ�ֺ���**********/
int Filter_ADC(void);//����ƽ��ֵ
void Read_Temp(float dT);//��ȡ�¶�-10ms
uint16_t Get_Ntc_Temp(uint16_t value_adc);//�����Ntc���¶�
void Temp_Init(void);//������ʾ�¶�

#endif
