#ifndef __DRV_KEY_H__
#define	__DRV_KEY_H__

#include "include.h"

/**********�궨��************/
#define ROW1_H HAL_GPIO_WritePin(ROW1_GPIO_Port,ROW1_Pin,GPIO_PIN_SET)//ROW1����
#define ROW1_L HAL_GPIO_WritePin(ROW1_GPIO_Port,ROW1_Pin,GPIO_PIN_RESET)//ROW1����
#define ROW2_H HAL_GPIO_WritePin(ROW2_GPIO_Port,ROW2_Pin,GPIO_PIN_SET)//ROW2����
#define ROW2_L HAL_GPIO_WritePin(ROW2_GPIO_Port,ROW2_Pin,GPIO_PIN_RESET)//ROW2����
#define ROW3_H HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW3_Pin,GPIO_PIN_SET)//ROW3����
#define ROW3_L HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW3_Pin,GPIO_PIN_RESET)//ROW3����

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern uint8_t Key_Status;//�������±�־

/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Key_Scan(float dT);//���󰴼�ɨ��
void Check_Press(float dT);//��ⰴ������״̬

#endif
