#ifndef __DRV_HEAT_H__
#define	__DRV_HEAT_H__

#include "include.h"

/**********�궨��************/
#define HEAT htim3.Instance->CCR2//HEAT���� PWM��� ��0~1000��

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void HEAT_Init(void);//��ʼ������

#endif
