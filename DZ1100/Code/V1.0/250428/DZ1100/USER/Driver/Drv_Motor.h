#ifndef __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "include.h"

/**********�궨��************/
#define Motor_Vcc_ON  P12 = 1//�򿪵����Դ
#define Motor_Vcc_OFF P12 = 0//�رյ����Դ
#define Motor_Gnd_ON  P11 = 1//�򿪵����Դ
#define Motor_Gnd_OFF P11 = 0//�رյ����Դ
#define Motor_En_ON  P13 = 1//�򿪵����Դ
#define Motor_En_OFF P13 = 0//�رյ����Դ

/**********ȫ�ֱ���**********/

/**********ȫ�ֺ���**********/
void Drv_Motor_Init(void);//Motor������ʼ��
void Motor_BrakeCheck(float dT);

#endif
