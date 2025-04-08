#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 1//0��10L&15L 1:30L 2:50L

#define FLASH_CHECK_START 0xAA

#if(Type == 0)
#define Speed_MAX 1500//ת�����1500
#define FLASH_CHECK_END 0xBB//У�����
#define POLE_NUMBER 2//�������
#elif(Type == 1)
#define Speed_MAX 5000//ת�����1300
#define FLASH_CHECK_END 0xBB//У�����
#define POLE_NUMBER 5//�������
#elif(Type == 2)
#define Speed_MAX 1100//ת�����1100
#define FLASH_CHECK_END 0xDD//У�����
#define POLE_NUMBER 5//�������
#endif

#define Speed_MIN 50//ת������50
#define Time_MAX  86400//ʱ���24Сʱ
#define Time_MIN  60//ʱ�����60S

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
	uint8_t Run_Status;//ϵͳ����Ϊ1
	uint8_t Motor_Stop;//���ֹͣ
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint8_t ADDMode;//��ʾ�����ģʽ
	uint8_t Cw;//�ı�ת���־
	uint8_t CwIcn;//ת��ͼ��
	int16_t Set;//�����ٶ�
	int16_t Ctrl;//�����ٶȣ�����ֵ��
	int16_t Rel;//ʵ���ٶ�
	int16_t Display_Rel;//������ʾʵ���ٶ�
	int16_t Display_Set;//������ʾ�����ٶ�
	int16_t New;//��ǰ�������С�ٶ�
	float Stop_Cnt;//�ٶ�ֹͣ����
}_Speed_;
extern _Speed_ Speed;//�ٶȲ���

typedef struct
{
	int32_t Set;//����ʱ��	
	int32_t Rel;//ʵ��ʱ��	
	int32_t Display_Set;//������ʾ�趨ʱ��
	int32_t Display_Rel;//������ʾʵ��ʱ��
}_Time_;
extern _Time_ Time;//ʱ�����


#endif
