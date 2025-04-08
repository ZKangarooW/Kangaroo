#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Temp_MAX 1000//100��
#define Temp_MIN 0
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
    uint8_t ADDMode;//��ʾ�����ģʽ
	int16_t Set;//�趨�¶�
	int16_t Rel;//ʵ���¶�
	int16_t Ctrl;//�����¶�
	int16_t Display_Set;//��ʾ�趨�¶�
	int16_t Display_Rel;//��ʾʵ���¶�
    int16_t New;//��ǰ�������С�¶�
	uint8_t Icn;//�¶�ͼ��
}_Temp_;
extern _Temp_ Temp;//�¶Ƚṹ

typedef struct
{
	int32_t Set;//�趨ʱ��
	int32_t Rel;//ʵ��ʱ��
	int32_t Display_Set;//��ʾ�趨ʱ��
	int32_t Display_Rel;//��ʾʵ��ʱ��
	uint8_t Icn;//ʱ��ͼ��
}_Time_;
extern _Time_ Time;//ʱ��ṹ

#endif
