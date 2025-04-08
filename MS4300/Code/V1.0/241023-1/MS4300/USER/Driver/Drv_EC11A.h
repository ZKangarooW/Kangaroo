#ifndef __DRV_EC11A_H__
#define __DRV_EC11A_H__

#include "include.h"

/**********�궨��************/
#define EC11A_FastSpeed 20//��ť��ת��ֵ

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
	uint8_t EC11A_Fast;////��ť��ת��ֵ
	
	float EC11A_Speed;//��ת��ťʱ���ٶ�
	float EC11A_Cnt;//����ʱ�ģ�һȦ��20��
	float EC11A_Knob;//��������ťʱ
	
	float Key_Cnt;//����ʱ��
	uint8_t Key_Flag;//�������±�־
	uint8_t LongPress;//����������־
	
}_EC11A_;
extern _EC11A_ EC11A[2];//��ť����

/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/

void EC11A_Init(void);
void EC11AKey_Scan(float dT);
void Check_Press(float dT);
void EC11A_Speed(float dT);

#endif
