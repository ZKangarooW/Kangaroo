#ifndef __DRV_MOTOR_H__
#define	__DRV_MOTOR_H__

#include "include.h"

/**********�궨��************/
#define PWM0 htim1.Instance->CCR1//motor PWM��� ��0~200��
#define PWM1 htim1.Instance->CCR2//motor PWM��� ��0~200��
#define PWM2 htim1.Instance->CCR3//motor PWM��� ��0~200��
#define PWM3 htim1.Instance->CCR4//motor PWM��� ��0~200��

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void Motor_Init(void);//�����ʼ��

#endif
