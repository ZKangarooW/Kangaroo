#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#include "include.h"

/**********�궨��************/
#define LED1_ON  P00 = 1//�򿪵�Դ������
#define LED1_OFF P00 = 0//�رյ�Դ������

#define LED2_ON  P02 = 1//��ϵͳ���е�
#define LED2_OFF P02 = 0//�ر�ϵͳ���е�
/**********ȫ�ֱ���**********/

/**********ȫ�ֺ���**********/
void Drv_LED_Init(void);//LED������ʼ��

#endif
