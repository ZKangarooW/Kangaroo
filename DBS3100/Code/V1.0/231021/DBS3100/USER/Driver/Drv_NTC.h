#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********ȫ�ֱ���**********/
extern uint16_t ADC_Val1,ADC_Val2;

/**********ȫ�ֺ���**********/
void ADCDMA_Init(void);//ADC��DMA�ĳ�ʼ��
int Filter_ADC(void);//����ƽ��ֵ
void Read_Temp(float dT);//��ȡ�¶�-10ms
uint16_t Get_Ntc_Temp(uint16_t value_adc);//�����Ntc���¶�
uint16_t Get_ADCVal(uint16_t temp);//���㵱ǰ�¶ȵ�adcֵ

#endif
