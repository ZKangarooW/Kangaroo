#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Speed_MIN 100
#define Speed_MAX 1200
#define Time_MAX 86400

#define Type_Motor 1 //0:������ʾ200 5S  1����ʾ100 10S

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
    uint8_t SetMode_Option;//ѡ������ģʽ
    uint8_t Motor_Stop;//���ֹͣ
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
    int16_t Set;         // �趨�ٶ�
    int16_t Rel;         // ʵ���ٶ�
    int16_t Ctrl;        // �����ٶ�
    int16_t New;        // �����ٶ���ʾ�������
    int16_t Last;        // �����ٶ���ʾ����洢
    int16_t Display;//��ʾ�ٶ�
    int8_t IcnStep;// �ٶ�ͼ�����ж�������
    float Stop_Cnt;// ���ֹͣ����
    uint8_t ADDMode;// ��ʾ����ģʽ
} _Speed_;
extern _Speed_ Speed; // �ٶȽṹ

typedef struct
{
    int32_t Set;     // �趨ʱ��
    int32_t Rel;     // ʵ��ʱ��
    int32_t Ctrl;     // ����ʱ��
    int32_t Display; // ��ʾʱ��
    int8_t Icn;      // ʱ��ͼ��
} _Time_;
extern _Time_ Time; // ʱ��ṹ

#endif
