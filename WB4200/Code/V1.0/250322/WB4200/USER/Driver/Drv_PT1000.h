#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********�궨��************/
#define ALPHA 0.1f  // ƽ�����ӣ�������Ӧ�ٶ�
#define V_IN 3.3f  // ��Դ��ѹ
#define OP_Value	6.2//�Ŵ�ϵ��
#define Vref		2.494//�ο���ѹ
#define K1			0.2327367//�����׼ϵ��
#define AD_LEN 2//DMA��ȡ����

/**********ȫ�ֱ���**********/
extern float PT_VALUE_1_TEMP;//�ⲿ̽ͷ��ֵ
extern float PT_VALUE_2_TEMP;//̨��̽ͷ��ֵ

/**********ȫ�ֺ���**********/
void ADCDMA_Init(void);//ADC��DMA�ĳ�ʼ��
void Read_Temp(float dT);//��ȡ�¶�-10ms
float CelsiusToFahrenheit(uint8_t type,int16_t celsius) ;

#endif
