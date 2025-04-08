#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Time_MAX  43200//ʱ���12Сʱ
#define Temp_MAX  600//�¶����60��

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
    uint8_t Time_Status;//����ʱ״̬
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
	int16_t Last;//֮ǰ���¶�
}_Temp_;
extern _Temp_ Temp;//�¶Ȳ���

typedef struct
{
	int32_t Set;//����ʱ��	
	int32_t Rel;//����ʱ��	
	int32_t Display_Set;//������ʾ�趨ʱ��
    int32_t Display_Rel;//������ʾʵ��ʱ��	
}_Time_;
extern _Time_ Time;//ʱ�����

#endif
