#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********�궨��************/
#define AD_LEN 1//DMA��ȡ����
#define ALPHA 0.1f  // ƽ�����ӣ�������Ӧ�ٶ�
#define R_REF 100000.0f  // �ο����� 5.1k��
#define V_IN 3.3f  // ��Դ��ѹ

/**********�ṹ��************/
/**********ȫ�ֱ�������******/

/**********ȫ�ֺ���**********/
void Read_Temp(float dT);//��ȡ�¶�-10ms
void Temp_Init(void);//������ʾ�¶�

#endif
