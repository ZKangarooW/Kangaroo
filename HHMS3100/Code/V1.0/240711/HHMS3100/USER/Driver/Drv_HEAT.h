#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********�궨��************/
#define HEAT2 htim4.Instance->CCR1 // HEAT PWM��� ��0~200��
#define HEAT0 htim4.Instance->CCR2 // HEAT PWM��� ��0~200��
#define HEAT3 htim4.Instance->CCR3 // HEAT PWM��� ��0~200��
#define HEAT1 htim4.Instance->CCR4 // HEAT PWM��� ��0~200��

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void HEAT_Init(void);//��ʼ������

#endif
