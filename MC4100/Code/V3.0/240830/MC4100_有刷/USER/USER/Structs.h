#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

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

extern uint8_t Speed_Unit;//�ٶȵ�λ
extern uint8_t Speed_Mode;//�ٶ�ģʽ,������1-5
extern uint8_t SpeedIcon_Step;//ת��ͼ��ת������
extern uint32_t Ctrl_Speed;//�����ٶȣ�����ֵ��
extern int32_t Set_Speed;//�����ٶ�
extern int8_t  Val_Speed;//�ٶ�����
extern int8_t  Val_xg;//����������
extern uint32_t Speed_Cnt;//���ת��
extern uint32_t Rel_Speed;//ʵ���ٶ�
extern uint32_t Speed_New;//�����ٶ���ʾ�������
extern uint32_t Speed_Last;//�����ٶ���ʾ����洢
extern uint32_t Display_RelSpeed;//������ʾ�ٶ�
extern uint32_t Display_SetSpeed;//��ʾ�ٶ�
extern uint16_t Speed_MAX;//����ٶ�

extern int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
extern int32_t Set_Time;//����ʱ��
extern int32_t Display_CtrlTime;//��ʾ����ʱ��
extern int32_t Display_SetTime;//��ʾ����ʱ��
extern uint8_t Time_Unit;//ʱ�䵥λ
extern uint8_t DownTime_Over;//ʱ�䵹��ʱ����

extern uint8_t PModeIcon_Step;//����ģʽͼ��ת������
extern uint8_t PMode_Option;//Pģʽѡ��
extern uint8_t Circle_Run;//��Ȧ�ı�־λ
extern uint8_t Show_Circle;//Pģʽ��Ȧ��ʾ

extern uint8_t Safe_Mode;//��ȫģʽ
extern uint8_t Safe_Temp_Flag;//��ȫ�¶ȳ���
extern uint8_t Safe_Temp_Twinkleg;//��ȫ�¶�ͼ����˸
extern int16_t Safe_Set_Temp;//��ȫ�趨�¶�
extern int16_t Safe_Rel_Temp;//��ȫʵ���¶�
extern int16_t Display_SafeTemp;//��ʾ��ȫ�¶�
extern uint8_t Lid_State;//����״̬

#endif
