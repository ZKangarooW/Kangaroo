#ifndef __DRV_KEY_H__
#define	__DRV_KEY_H__

#include "include.h"

/**********�궨��************/
#define Key1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)//��KEY1�ĵ�ƽ
#define Key2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)//��KEY2�ĵ�ƽ
#define Key3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)//��KEY3�ĵ�ƽ
#define Key4 HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)//��KEY4�ĵ�ƽ
#define Key5 HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)//��KEY4�ĵ�ƽ

#define Key_Down 0//����
#define Key_Up 1//�ſ�

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float Key_Status;//�������±�־

/**********ȫ�ֺ���**********/
void Key_Scan(float dT);//����ɨ��
void Check_Press(float dT);//��ⰴ������״̬

#endif
