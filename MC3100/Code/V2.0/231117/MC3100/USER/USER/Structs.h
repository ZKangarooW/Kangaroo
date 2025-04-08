#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 1//0Ϊ5PRO��1Ϊ7PRO
#if(Type==1)
#define Speed_MAX 7000//ת�����7000
#define Rcf_MAX 12//�����������12
#elif(Type==0)
#define Speed_MAX 5000//ת�����5000
#define Rcf_MAX 8//�����������8
#endif
#define Speed_MIN 1000//ת����С1000
#define Time_MAX 5940//���99����
#define Time_MIN 10//��С10s

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
	uint8_t Run_Status;//ϵͳ״̬
	uint8_t DownTime_Status;//����ʱ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
	uint8_t Lock_On;//���ӹر�
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint32_t Ctrl_Speed;//�����ٶȣ�����ֵ��
	uint8_t Speed_Mode;//�ٶ�ģʽ
	uint8_t Speed_Unit;//�ٶȵ�λ
	uint8_t Speed_Rcf;//������
	int32_t Set_Speed;//�����ٶ�
	uint32_t Rel_Speed;//ʵ���ٶ�
	uint32_t Display_Speed;//��ʾ�ٶ�
}_Speed_;
extern _Speed_ Speed;//ϵͳ��ʼ�����

typedef struct
{
	int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
	int32_t Set_Time;//����ʱ��
	int32_t Display_Time;//��ʾ����ʱ��
	uint8_t Time_Unit;//ʱ�䵥λ
	uint8_t DownTime_Over;//ʱ�䵹��ʱ����
}_Time_;
extern _Time_ Time;//ϵͳ��ʼ�����

#endif
