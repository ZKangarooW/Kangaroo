#ifndef __DRV_LOCK_H__
#define	__DRV_LOCK_H__

#include "include.h"

/**********�궨��************/
#define Lock1_ON HAL_GPIO_WritePin(UC_DCT1_GPIO_Port,UC_DCT1_Pin,GPIO_PIN_SET)//Lock1��
#define Lock1_OFF HAL_GPIO_WritePin(UC_DCT1_GPIO_Port,UC_DCT1_Pin,GPIO_PIN_RESET)//Lock1�ر�
#define Lock2_ON HAL_GPIO_WritePin(UC_DCT2_GPIO_Port,UC_DCT2_Pin,GPIO_PIN_SET)//Lock1��
#define Lock2_OFF HAL_GPIO_WritePin(UC_DCT2_GPIO_Port,UC_DCT2_Pin,GPIO_PIN_RESET)//Lock1�ر�

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint8_t Lock1_Status,Lock2_Status;//�������״̬

/**********ȫ�ֺ���**********/
void Ctrl_Lock(float dT);//���������

#endif
