#ifndef __DRV_MOTOR_H__
#define	__DRV_MOTOR_H__

#include "include.h"

/**********�궨��************/
#define PWM htim1.Instance->CCR1//motor PWM��� ��0~400��
#define MO_ON()  HAL_GPIO_WritePin(MO_GPIO_Port,MO_Pin,GPIO_PIN_SET);//�򿪵��
#define MO_OFF() HAL_GPIO_WritePin(MO_GPIO_Port,MO_Pin,GPIO_PIN_RESET);//�رյ��

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Motor_Init(void);//�����ʼ��

#endif
