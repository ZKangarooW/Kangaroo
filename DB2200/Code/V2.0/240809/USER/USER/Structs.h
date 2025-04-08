#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
	uint8_t DownTime_Status;//����ʱ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
	uint8_t CtrlTemp_Mode;//����ģʽ
	uint8_t SetP_Mode_Option;//����Pģʽ��ǰ���õ�ѡ��
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

extern int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
extern int32_t Set_Time;//����ʱ��
extern int32_t Display_CtrlTime;//��ʾ����ʱ��
extern int32_t Display_SetTime;//��ʾ����ʱ��
extern int32_t Time;//��ʱ�洢ֵ
extern uint8_t Time_Unit;//ʱ�䵥λ
extern uint8_t Time_State;//ʱ���״̬
extern uint8_t DownTime_Over;//ʱ�䵹��ʱ����

extern int Set_Temp;//�����¶�
extern int Ctrl_Temp;//�����¶ȣ�����ֵ��
extern int Ture_Temp;//����¶�
extern int Rel_Temp;//ʵ���¶�
extern int Display_RelTemp;//��ʾʵ���¶�
extern int Display_CtrlTemp;//��ʾ�����¶�
extern int Temp;//��ʱ�洢�¶�
extern uint8_t Temp_ADDMode;//�¶���ʾģʽ
extern int Temp_New,Temp_Last;//�����¶ȡ�֮ǰ�¶�
extern uint8_t HEAT_ICO;//����ͼ��
extern int ADD_Wait_Count;//���½��µ�ʱ��

extern uint8_t Display_Circle;//Pģʽ��Ȧ
extern uint8_t Circle_Run;//��Ȧ�ı�־λ
extern uint8_t Show_Circle;//Pģʽ��Ȧ��ʾ
extern uint8_t PMode_Status;//Pģʽ״̬
extern uint8_t PMode_Mode;//Pģʽ���ݶȺͼ����л�
extern uint8_t PMode_Option;//Pģʽѡ��
extern uint8_t PMode_P1;//PģʽP1ֵ
extern uint8_t PMode_P2;//PģʽP2ֵ

#endif
