#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 1//0Ϊ�Ͽ1Ϊ�¿�

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

extern int16_t Speed;//��ʱ�ٶ�
extern int16_t Set_Speed;//�趨�ٶ�
extern int16_t Rel_Speed;//ʵ���ٶ�
extern int16_t Ctrl_Speed;//�����ٶ�
extern int16_t Display_Speed;//��ʾ�ٶ�
extern int16_t Speed_Cnt;//û�������벶���ʱ��
extern uint8_t Speed_ADDMode;//�����ж��ٶ�ʱ���������½�
extern int16_t Speed_New;//�����ٶ���ʾ�������
extern int16_t Speed_Last;//�����ٶ���ʾ����洢

extern int16_t Time;//��ʱʱ��
extern int16_t Set_Time;//�趨ʱ��
extern int16_t Rel_Time;//ʵ��ʱ��
extern int16_t Display_Time;//��ʾʱ��
extern uint8_t Time_Unit;//ʱ����������л�
extern uint8_t Time_State;//ʱ���״̬
extern uint8_t DownTime_Over;//ʱ�䵹��ʱ����



#endif
