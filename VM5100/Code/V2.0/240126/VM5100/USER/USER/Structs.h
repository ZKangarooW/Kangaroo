#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xCC

#define Time_MAX  28800//ʱ���24Сʱ
#define Time_MIN  60//ʱ�����60S

extern uint16_t Speed_MAX;//���ת��
extern uint16_t Speed_MIN;//��Сת��

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
	uint8_t Run_Status;//ϵͳ����Ϊ1
	uint8_t Motor_Stop;//���ֹͣ
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

extern int Ctrl_Speed;//�����ٶȣ�����ֵ��
extern int Set_Speed;//�����ٶ�
extern int Rel_Speed;//ʵ���ٶ�
extern int Display_SetSpeed;//������ʾ�����ٶ�
extern int Display_RelSpeed;//������ʾʵ���ٶ�
extern int Speed;//��ʱ�洢�ٶ�
extern uint8_t Speed_Cnt;//���벶�����Ĵ���
extern int Speed_New;//�����ٶ���ʾ�������
extern int Speed_Last;//�����ٶ���ʾ����洢
extern int Speed_ADDMode;//�����ж��ٶ�ʱ���������½�
extern uint8_t pwm_start;
extern int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
extern int32_t Set_Time;//����ʱ��
extern int32_t Display_SetTime;//��ʾʱ��
extern int32_t Display_CtrlTime;//��ʾʱ��
extern int32_t Time;//��ʱ�洢ֵ
extern uint8_t Time_State;//ʱ���״̬
extern uint8_t DownTime_Over;//ʱ�䵹��ʱ����
//extern uint8_t Time_unit;//ʱ�䵥λ


#endif
