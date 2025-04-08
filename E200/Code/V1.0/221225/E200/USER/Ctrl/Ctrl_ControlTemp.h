#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/
#define UC_HEAT htim1.Instance->CCR2//������ģ��PWM
#define COLD htim3.Instance->CCR2//����ģ��PWM
#define HEAT htim3.Instance->CCR1//����ģ��PWM

#define WIND_ON		HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_SET)
#define WIND_OFF	HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_RESET)

/**********ȫ�ֱ���**********/
extern uint16_t Temp_P[3][2];
extern int Temp_Out;//�¶�pwm���ֵ
extern uint8_t Cold_Step;
extern float Cold_Time;
extern float HEAT_Time;
/**********ȫ�ֺ���**********/
void Temp_Iint(void);//�¶ȳ�ʼ��
void Temp_Control(float dT);//�¶ȼ��ȿ���

#endif
