#ifndef __DRV_MOTOR_H__
#define	__DRV_MOTOR_H__

#include "include.h"

/**********�궨��************/
#define PWM htim1.Instance->CCR1//motor PWM�����0~200��

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Motor_Init(void);//�����ʼ��

#endif
