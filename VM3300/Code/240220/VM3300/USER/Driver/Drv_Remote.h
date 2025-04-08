#ifndef __DRV_REMOTE_H__
#define __DRV_REMOTE_H__

#include "include.h"

/**********�궨��************/
//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0    		 
#define IR_IN HAL_GPIO_ReadPin(IR2_GPIO_Port, IR2_Pin)
extern uint8_t Remote_Flag;
/**********�ṹ��************/
/**********ȫ�ֱ�������*******/
/**********ȫ�ֺ���**********/
uint8_t Remote_Scan(void);
void Drv_Remote_Init(void);
void Remote_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void Check_Remote(float dT);
#endif
