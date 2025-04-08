#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f1xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC1

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
    int16_t Set;//�趨�ٶ�
    int16_t Rel;//ʵ���ٶ�
    int16_t Ctrl;//�����ٶ�

    int16_t Display_Set;//��ʾ�趨�ٶ�
    int16_t Display_Rel;//��ʾʵ���ٶ�
    
    int8_t IconStep;//�ٶ�ͼ�����ж�������
    
    float Stop_Cnt;//���ֹͣ����
    uint8_t ADDMode;//��ʾ����ģʽ
} _Speed_;

typedef struct
{
    uint8_t Motor_Stop;//���ֹͣ
    uint8_t Run_Status;//ϵͳ����Ϊ1
    _Speed_ Speed;
} _Work_Num_;
extern _Work_Num_ Work_Num[15];//��λ����

#endif
