#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"
#if (Key_Type == 0)
/**********�궨��************/
#define KEY1 HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)
#define KEY2 HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)
#define KEY3 HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)
#define KEY4 HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)

//����ʶ�𰴼����µ�״̬ʶ�� 
#define PRESS RESET//�͵�ƽʶ��

#define KEY_DOWN PRESS/*������*/
#define KEY_UP !PRESS/*������*/


/**********ȫ�ֱ�������******/
extern float Key_Status;//�������±�־

/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Key_Scan(float dT);//���󰴼�ɨ��
void Check_Press(float dT);//��ⰴ������״̬

#endif
#endif
