#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xFF

#define Speed_MAX 1500//��ģ��1500  ��ģ��800  ����100
#define Speed_MIN 100
#define Temp_MAX 1000//100��  ����0.1
#define Temp_MIN 0//��������-5�棬����0��
#define Time_MAX 86400//24Сʱ
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
	int16_t Set;//�趨�ٶ�
	int16_t Rel;//ʵ���ٶ�
	int16_t Ctrl;//�����ٶ�
	int16_t Display_Set;//��ʾ�趨�ٶ�
	int16_t Display_Rel;//��ʾʵ���ٶ�
	int8_t IcnStep;//�ٶ�ͼ�����ж�������
	float Stop_Cnt;//���ֹͣ����
	uint8_t DisplayMode;//��ʾģʽ
}_Speed_;
extern _Speed_ Speed;//�ٶȽṹ

typedef struct
{
	int16_t Set;//�趨�¶�
	int16_t Rel;//ʵ���¶�
	int16_t HEAT_GAI;//�����¶�
	int16_t Ctrl;//�����¶�
	int16_t Display_Set;//��ʾ�趨�¶�
	int16_t Display_Rel;//��ʾʵ���¶�
	int8_t Icn;//�¶�ͼ��
	float Rel_Speed;//��ʵ�ٶ�
	float Alarm_Speed;//�����ٶ�
	uint8_t DisplayMode;//��ʾģʽ
}_Temp_;
extern _Temp_ Temp;//�¶Ƚṹ

typedef struct
{
	uint32_t Set;//�趨ʱ��
	uint32_t Rel;//ʵ��ʱ��
	uint32_t Display;//��ʾʱ��
	uint8_t Icn;//ʱ��ͼ��
}_Time_;
extern _Time_ Time;//ʱ��ṹ

#endif
