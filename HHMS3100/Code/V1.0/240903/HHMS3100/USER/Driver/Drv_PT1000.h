#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********�궨��************/
#define AD_LEN 8//DMA��ȡ����

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float PT_VALUE_1_TEMP[4];//�ⲿ̽ͷ��ֵ
extern float PT_VALUE_2_TEMP[4];//�ⲿ̽ͷ��ֵ

/**********ȫ�ֺ���**********/

void ADCDMA_Init(void);
float Get_ADCVal(int16_t temp);
void PT1000_Task(void *p);

#endif
