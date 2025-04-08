#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 0//0:������  1�����ȴ�����
#define Key_Type 0//0����Ĥ�� 1��������

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xFF

#define Speed_MAX 1200
#define Speed_MIN 100
#define Temp_MAX 1000//100��
#define Temp_MIN 0
#define Time_MAX 86340//23Сʱ59����
#define Time_MIN 0

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
	uint8_t SetMode_Option;//�趨ģʽ
	uint8_t Run_Status;//ϵͳ����Ϊ1
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint16_t Set;//�趨�ٶ�
	uint16_t Rel;//ʵ���ٶ�
	uint16_t Ctrl;//�����ٶ�
	uint16_t Display_Set;//��ʾ�趨�ٶ�
	uint16_t Display_Rel;//��ʾʵ���ٶ�
	uint8_t IcnStep;//�ٶ�ͼ�����ж�������
	float Stop_Cnt;//���ֹͣ����
	uint8_t DisplayMode;//��ʾģʽ
}_Speed_;
extern _Speed_ Speed;//�ٶȽṹ

typedef struct
{
	uint16_t Set;//�趨�¶�
	uint16_t Rel;//ʵ���¶�
	uint16_t Ctrl;//�����¶�
	uint16_t Alarm;//�����¶�
	uint16_t Display_Set;//��ʾ�趨�¶�
	uint16_t Display_Rel;//��ʾʵ���¶�
	uint8_t Icn;//�¶�ͼ��
	float Rel_Speed;//��ʵ�ٶ�
	float Alarm_Speed;//�����ٶ�
	uint8_t DisplayMode;//��ʾģʽ
}_Temp_;
extern _Temp_ Temp;//�¶Ƚṹ

typedef struct
{
	uint32_t Set;//�趨ʱ��
	uint32_t Rel;//ʵ��ʱ��
	uint32_t Display_Set;//��ʾ�趨ʱ��
	uint32_t Display_Rel;//��ʾʵ��ʱ��
	uint8_t Icn;//ʱ��ͼ��
}_Time_;
extern _Time_ Time;//ʱ��ṹ

#endif
