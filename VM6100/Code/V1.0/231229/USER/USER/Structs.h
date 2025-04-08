#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

//#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
//#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
//#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
//#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
    
#define Speed_MAX 3000//���ת��
#define Speed_MIN 500//��Сת��
#define Time_MAX 86400//ʱ���24Сʱ
#define Time_MIN  60//ʱ�����60S

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
	uint8_t Run_Status;//ϵͳ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
	uint8_t Motor_Stop;//���ֹͣ
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint8_t ADDMode;//��ʾ�����ģʽ
	int16_t Set;//�����ٶ�
	int16_t Ctrl;//�����ٶȣ�����ֵ��
	int16_t Rel;//ʵ���ٶ�
    
	int16_t Display_Rel;//������ʾʵ���ٶ�
	int16_t Display_Set;//������ʾ�����ٶ�
    
	int16_t New;//��ǰ�������С�ٶ�
	int16_t Last;//֮ǰ���ٶ�
    
	float Stop_Cnt;//�ٶ�ֹͣ����
}_Speed_;
extern _Speed_ Speed;//�ٶȲ���

typedef struct
{
	int32_t Set;//����ʱ��	
	int32_t Rel;//����ʱ��	
    int32_t Display_Rel;//������ʾʵ��ʱ��
	int32_t Display_Set;//������ʾ����ʱ��
}_Time_;
extern _Time_ Time;//ʱ�����

#endif
