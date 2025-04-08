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
extern bool tuning_complete;//�Զ����α�־λ
extern float last_peak_time;//��һ������
extern int oscillation_count;//������
extern bool tuning_complete1;//�Զ����α�־λ
extern float last_peak_time1;//��һ������
extern int oscillation_count1;//������
/**********ȫ�ֺ���**********/
void Temp_Iint(void);//�¶ȳ�ʼ��
void Temp_Control(float dT);//�¶ȼ��ȿ���
void PID_Init(void);
void Cool_Temp_Control(float dT);
#endif
