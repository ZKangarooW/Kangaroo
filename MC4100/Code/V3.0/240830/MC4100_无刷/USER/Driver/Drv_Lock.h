#ifndef __DRV_LOCK_H__
#define	__DRV_LOCK_H__

#include "include.h"

/**********�궨��************/
#define Lock_ON HAL_GPIO_WritePin(UC_DCT_GPIO_Port,UC_DCT_Pin,GPIO_PIN_SET)//Lock1��
#define Lock_OFF HAL_GPIO_WritePin(UC_DCT_GPIO_Port,UC_DCT_Pin,GPIO_PIN_RESET)//Lock1�ر�

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint8_t Lock_Status;//�������״̬

/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Ctrl_Lock(float dT);//���������

#endif
