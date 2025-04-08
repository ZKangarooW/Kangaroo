#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********�궨��************/
#define N           100//�����˲��ɼ�100��
#define ALPHA       0.1f//ƽ�����ӣ�������Ӧ�ٶ�

#define Vref		1.2f//�ڲ��ο���ѹ
#define OP_Value	6.8f//�Ŵ�ϵ��
#define R_3K        3.0f//��ѹ����3k
#define R_910R      0.91f//��ѹ����910��

#define AD_LEN      3//DMA��ȡ����

/**********ȫ�ֱ���**********/
extern float PT_VALUE_1_TEMP;//̨��̽ͷ��ֵ

/**********ȫ�ֺ���**********/
void ADCDMA_Init(void);//ADC��DMA�ĳ�ʼ��
void Read_Temp(float dT);//��ȡ�¶�-10ms
float CelsiusToFahrenheit(uint8_t type,int16_t celsius);//���϶�ת���϶�

#endif
