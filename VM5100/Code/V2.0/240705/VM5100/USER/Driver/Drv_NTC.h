#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********ȫ�ֱ���**********/
extern uint8_t NTC_Res;//��ȡ�¶�����õ�״̬

/**********ȫ�ֺ���**********/
int Filter_ADC(void);//����ƽ��ֵ
void Read_Temp(void);//��ȡ�¶�-10ms
uint16_t Get_Ntc_Temp(uint16_t value_adc);//�����Ntc���¶�

#endif
