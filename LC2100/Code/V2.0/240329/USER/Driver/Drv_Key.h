#ifndef __DRV_KEY_H__
#define	__DRV_KEY_H__

#include "include.h"

/**********�궨��************/
#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define KEY3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)
#define KEY4 HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)
#define KEY5 HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint8_t Key_Status;//�������±�־

/**********ȫ�ֺ���**********/
void Key_Scan(float dT);//���󰴼�ɨ��
void Check_Press(float dT);//��ⰴ������״̬

#endif
