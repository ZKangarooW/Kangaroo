#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Temp_MAX  2800//�¶����280��
#define Speed_MAX 1500//ת�����1500
#define Time_MAX  43200//ʱ���12Сʱ

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint8_t Temp_ADDMode;//��ʾ�����ģʽ
	int16_t Ctrl_Temp;//�����¶ȣ�����ֵ��
	int16_t Set_Temp;//�����¶�
	int16_t Rel_Temp;//ʵ���¶�
	int16_t Mesa_Temp;//̨���¶�
	int16_t Outside_Temp;//�ⲿ�¶�
	int16_t Display_RelTemp;//������ʾʵ���¶�
	int16_t Display_SetTemp;//������ʾ�����¶�
	int16_t Temp_New;//��ǰ�������С�ٶ�
	int16_t Temp_Last;//֮ǰ���ٶ�
}_Temp_;
extern _Temp_ Temp;//�¶Ȳ���

typedef struct
{
	uint8_t Speed_ADDMode;//��ʾ�����ģʽ
	int16_t Set_Speed;//�����ٶ�
	int16_t Ctrl_Speed;//�����ٶȣ�����ֵ��
	int16_t Rel_Speed;//ʵ���ٶ�
	int16_t Display_RelSpeed;//������ʾʵ���ٶ�
	int16_t Display_SetSpeed;//������ʾ�����ٶ�
	int16_t Speed_New;//��ǰ�������С�ٶ�
	int16_t Speed_Last;//֮ǰ���ٶ�
}_Speed_;
extern _Speed_ Speed;//�ٶȲ���

typedef struct
{
	int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
	int32_t Set_Time;//����ʱ��	
	int32_t Display_Time;//������ʾʱ��	
}_Time_;
extern _Time_ Time;//ʱ�����

#endif
