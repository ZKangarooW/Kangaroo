#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC7

#define Key_Type 0//0:������5pro 1����ť��5c

#define Speed_MAX 1500//ת�����1500


#if(Key_Type == 0)
	#define Temp_MAX  3100//�¶����310��
    #define Time_MAX  43200//ʱ���12Сʱ
#elif(Key_Type == 1)
	#define	Temp_MAX  2800//�¶����280��
    #define Time_MAX  0//ʱ���0Сʱ
#endif

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
	int16_t Mesa;//̨���¶�
	int16_t Outside;//�ⲿ�¶�
	int16_t Display_Rel;//������ʾʵ���¶�
	int16_t Display_Set;//������ʾ�����¶�
	int16_t New;//��ǰ�������С�ٶ�
	int16_t Last;//֮ǰ���ٶ�
	int16_t Old;//�ϵ��ٶ�
	int16_t Speed;//�ϵ��ٶ�
}_Temp_;
extern _Temp_ Temp;//�¶Ȳ���

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
	int32_t Display;//������ʾʱ��	
}_Time_;
extern _Time_ Time;//ʱ�����

#endif
