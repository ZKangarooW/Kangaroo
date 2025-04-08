#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Speed_MIN 200//ת����С200
#define Speed_MAX 2500//ת�����2500

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
	uint8_t Motor_Stop;//���ֹͣ
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	int16_t Set;//�����ٶ�
	int16_t Ctrl;//�����ٶȣ�����ֵ��
	int16_t Rel;//ʵ���ٶ�
	int16_t Display;//������ʾ�ٶ�
	int16_t New;//��ǰ�������С�ٶ�
	int16_t Last;//֮ǰ���ٶ�
	float Stop_Cnt;//������Ƿ�ֹͣ
	int8_t ADDMode;//��ʾ�����ģʽ
}_Speed_;
extern _Speed_ Speed;//�ٶȲ���

#endif
