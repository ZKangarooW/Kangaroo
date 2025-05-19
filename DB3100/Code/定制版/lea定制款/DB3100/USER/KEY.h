#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

/**********�궨��************/
#define Key1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)//��KEY1�ĵ�ƽ
#define Key2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)//��KEY2�ĵ�ƽ
#define Key3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)//��KEY3�ĵ�ƽ
#define Key4 HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)//��KEY4�ĵ�ƽ
#define Key5 HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)//��KEY5�ĵ�ƽ

/**********ȫ�ֱ���**********/
extern uint16_t run_mode;//����ģʽ
extern uint8_t Key_Status;//�ڲ�������ʱ

/**********ȫ�ֺ���**********/
void Key_Handle(float dT);//��������
void Check_Key(void);//��ⰴ��״̬-1s

#endif
