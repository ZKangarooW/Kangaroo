#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********ȫ�ֱ���**********/
extern float PT_VALUE_1_TEMP;//�ⲿ̽ͷ��ֵ
extern float PT_VALUE_2_TEMP;//̨��̽ͷ��ֵ

/**********ȫ�ֺ���**********/
void ADCDMA_Init(void);//ADC��DMA�ĳ�ʼ��
void Read_Temp(float dT);//��ȡ�¶�-10ms
float celsiusToFahrenheit(uint8_t type,int16_t celsius) ;

#endif
