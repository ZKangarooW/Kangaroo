#ifndef __DRV_MOTOR_H__
#define	__DRV_MOTOR_H__

#include "include.h"

/**********�궨��************/
#define PWM htim3.Instance->CCR4//motor PWM��� ��0~400��
#define COLD_ON  HAL_GPIO_WritePin(COLD_GPIO_Port,COLD_Pin,GPIO_PIN_SET)//���ȴ�
#define COLD_OFF HAL_GPIO_WritePin(COLD_GPIO_Port,COLD_Pin,GPIO_PIN_RESET)//���ȹر�

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Motor_Init(void);//�����ʼ��

#endif
