#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Temp_MAX 1000//�¶����100��
#define Temp_MIN 0//�¶����0��
#define Time_MAX  86400//ʱ���24Сʱ
#define Time_MIN  0//ʱ�����0

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint8_t ADDMode;//��ʾ�����ģʽ
	int16_t Ctrl;//�����¶ȣ�����ֵ��
	int16_t Set;//�����¶�
	int16_t Rel;//ʵ���¶�
	int16_t Display_Rel;//������ʾʵ���¶�
	int16_t Display_Set;//������ʾ�����¶�
	int16_t New;//��ǰ�������С�¶�
	int16_t Last_Set;//��¼����ʱ���趨�¶�
	uint8_t Last_Mode;//��¼����ʱ����ʾģʽ
	float ADD_Wait_Count;//��������ʱ��
}_Temp_;
extern _Temp_ Temp;//�¶Ȳ���

typedef struct
{
	int32_t Set;//����ʱ��	
	int32_t Rel;//����ʱ��	
    int32_t Display_Rel;//������ʾʵ��ʱ��
	int32_t Display_Set;//������ʾ����ʱ��
}_Time_;
extern _Time_ Time;//ʱ�����

typedef struct
{
    uint8_t Show_Circle;//��ʾ����P-��ģʽ
    uint8_t Option;//Pģʽ����ѡ��
}_PMode_;
extern _PMode_ PMode;//Pģʽ����

#endif
