#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********�궨��************/
#define HEAT htim15.Instance->CCR1//����ģ��PWM
#define HEAT_ON()  HAL_GPIO_WritePin(HEAT_GPIO_Port,HEAT_Pin,GPIO_PIN_SET);//�򿪼���ģ��
#define HEAT_OFF() HAL_GPIO_WritePin(HEAT_GPIO_Port,HEAT_Pin,GPIO_PIN_RESET);//�رռ���ģ��

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void HEAT_Init(void);//��ʼ������

#endif
