#ifndef __DRV_EC11A_H__
#define __DRV_EC11A_H__

#include "include.h"

/**********�궨��************/
#define EC11A_Tim_1 htim6//��ť1�Ķ�ʱ��
#define EC11A_Fast_1 40//��ť��ת��ֵ

//����ʶ�𰴼����µ�״̬ʶ�� 
#define PRESS RESET//�͵�ƽʶ��

#define KEY_DOWN PRESS/*������*/
#define KEY_UP  !PRESS/*������*/

/**********�ṹ��************/
typedef struct
{
	uint16_t EXTI_Pin;//EC11A��ť�ж�����
	uint16_t EC11A_Pin;//EC11A��ť��������
	GPIO_TypeDef* EC11A_GPIO;//EC11A��ť����GPIO�˿�
	uint16_t Key_Pin;//EC11A������������
	GPIO_TypeDef* Key_GPIO;//EC11A��������GPIO�˿�
	TIM_HandleTypeDef *Tim;//ѡ�õĶ�ʱ��
	uint8_t EC11A_Fast;////��ť��ת��ֵ
	
	float EC11A_Speed;//��ת��ťʱ���ٶ�
	uint16_t EC11A_Cnt;//����ʱ�ģ�һȦ��20��
	uint8_t EC11A_Knob;//��������ťʱ
	uint8_t TIM_Cnt;//��ʱ������
	
	float Key_Cnt;//����ʱ��
	uint8_t Key_Flag;//�������±�־
	uint8_t LongPress;//����������־
	
}_EC11A_;
extern _EC11A_ EC11A[1];//��ť����

/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void EC11A_Init(void);//EC11A��ʼ����ʱ��
void EC11A_Speed(float dT);//EC11A��ť�ٶȼ���
void EC11AKey_Scan(float dT);//EC11A����ɨ��
void Check_Knob(float dT);//�����ť״̬

#endif
