#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********�궨��************/
#define HEAT htim3.Instance->CCR2//����ģ��PWM
#define HEAT_ON  HAL_GPIO_WritePin(HEAT_GPIO_Port,HEAT_Pin,GPIO_PIN_SET)//�򿪼̵�������
#define HEAT_OFF HAL_GPIO_WritePin(HEAT_GPIO_Port,HEAT_Pin,GPIO_PIN_RESET)//�رռ̵�������

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void HEAT_Init(void);//��ʼ������

#endif
