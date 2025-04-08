#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 0 //0��30 pro
			   //1��15 pro 

#if(Type == 0)
#define MIN_Speed 50
#define MAX_Speed 1200
#define Tooth_Ratio 4
#elif(Type == 1)
#define MIN_Speed 100
#define MAX_Speed 2000
#define Tooth_Ratio 2
#endif

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
    uint8_t SetMode_Option;//ѡ������ģʽ
	uint8_t Motor_Stop;//���ֹͣ
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

extern uint16_t Speed;//��ʱ�ٶ�
extern uint16_t Rel_Speed;//ʵ���ٶ�
extern int16_t Set_Speed;//�趨�ٶ�
extern uint16_t Ctrl_Speed;//�����ٶ�
extern int16_t Display_Speed;//��ʾ�ٶ�
extern uint8_t Speed_Cnt;//�ٶ��������
extern uint8_t Speed_ADDMode;//�ٶ���ʾģʽ
extern uint16_t Speed_New;//���ڵ��ٶ�
extern uint16_t Speed_Last;//��һ�ε��ٶ�

extern int32_t Time;//��ʱʱ��
extern int32_t Set_Time;//�趨ʱ��
extern int32_t Ctrl_Time;//����ʱ��
extern uint8_t Time_State;//ʱ���״̬
extern int32_t Display_Time;//��ʾʱ��
extern uint8_t DownTime_Over;//����ʱ����

extern uint8_t Display_OFF;//����ʾ��Ļ

#endif
