#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include "include.h"

/**********�궨��************/
#define N       100//�����˲��ɼ�100��
#define AD_LEN 1//ADCͨ����
#define V_IN 3.0f //��Դ��ѹ

/**********ȫ�ֱ���**********/
/**********ȫ�ֺ���**********/
void Drv_ADC_Init(void);//ADC������ʼ��
void Get_ADC_Value(float dT);//��ȡADC��ֵ
void Check_Power(float dT);//����ص���������
    
#endif
