#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********ȫ�ֱ���**********/
extern float  Calibration_Temp;

/**********ȫ�ֺ���**********/
void ADCDMA_Init(void);//ADC��DMA�ĳ�ʼ��
int Filter_ADC(void);//����ƽ��ֵ
void Read_Temp(float dT);//��ȡ�¶�-10ms
void Calibration(uint16_t temp,uint16_t temp1);//�¶�У׼����

#endif
