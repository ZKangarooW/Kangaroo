#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "stm32f1xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xFF

#define Speed_MIN 100//���ת��100
#define Speed_MAX 1500//���ת��1500
#define Temp_MAX 3100//����¶�100�� ����0.1
#define Temp_MIN 0//����¶�0�� ����0���϶�
#define Time_MAX 86400//����趨ʱ��24Сʱ
#define Time_MIN 0//����趨ʱ��0S

typedef struct
{
    uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    
    uint8_t SetMode_Option;//�趨ģʽ
    
    uint8_t New_Work;//��ǰ��λ
} _sys_;
extern _sys_ sys; // ϵͳ��ʼ���ṹ

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
    int16_t Set;//�趨�¶�
    int16_t Rel;//ʵ���¶�
    int16_t Mesa;//̨���¶�
    int16_t Outside;//�ⲿ�¶�
    int16_t Ctrl;//�����¶�
    
    int16_t Display_Set;//��ʾ�趨�¶�
    int16_t Display_Rel;//��ʾʵ���¶�
    
    uint8_t Icon;//�¶�ͼ��
    uint8_t ADDMode;//��ʾ����ģʽ
    
    uint16_t New;//��ǰ�������С�ٶ�
	uint16_t Last;//֮ǰ���ٶ�
} _Temp_;

typedef struct
{
    int32_t Set;//�趨ʱ��
    int32_t Rel;//ʵ��ʱ��
    int32_t Ctrl;//�����ٶ�

    int32_t Display_Set;//��ʾ�趨ʱ��
    int32_t Display_Rel;//��ʾʵ��ʱ��
    
    int8_t Icon;//ʱ��ͼ��
} _Time_;

typedef struct
{
    uint8_t Motor_Stop;//���ֹͣ
    uint8_t Run_Status;//ϵͳ����Ϊ1
    _Speed_ Speed;
    _Temp_ Temp;
    _Time_ Time;
} _Work_Num_;
extern _Work_Num_ Work_Num[4];//��λ����

#endif
