#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))
	
#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xB1

#define Speed_Min 500 
#define Xg_Min 50
#define Time_MAX 3590//�59��50��
#define Time_Min 30//����30s
extern uint16_t Speed_MAX;
extern uint16_t Xg_MAX;

typedef struct
{ 
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
	uint8_t Run_Status;//ϵͳ״̬
	uint8_t DownTime_Status;//����ʱ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
	uint8_t Motor_Stop;//���ֹͣ
	uint8_t Lock_On;//���ӹر�
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	int16_t Set;//�趨�ٶ�
	int16_t Rel;//�趨�ٶ�
	int16_t Cnt;//���ת��
	int16_t Ctrl;//�����ٶȣ�����ֵ��
	int16_t Display;//��ʾ�ٶ�
	int16_t New;//�����ٶ���ʾ�������
	int16_t Last;//�����ٶ���ʾ����洢
	int8_t Unit;//�ٶȵ�λ
	int8_t ADDMode;//�����ж��ٶ�ʱ���������½�
}_Speed_;
extern _Speed_ Speed;//�ٶ�

typedef struct
{
	int32_t Set;//�趨ʱ��
	int32_t Ctrl;//����ʱ�䣨����ֵ��
	int32_t Display;//��ʾʱ��
}_Time_;
extern _Time_ Time;//ʱ��

typedef struct
{
	uint8_t Mode;//�Ƿ���CGF��ģʽ��
    uint8_t Option;//��ǰ���е�����
}_CGF_;
extern _CGF_ CGF;//ʱ��

#endif
