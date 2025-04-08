#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f1xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xDD

#define Integration_TYPE 1//0���������� 1������

#define MAX_Time 71940

extern uint16_t MAX_Speed;

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
    int L0;//��λ
	int L1;//��λ1
    int L2;//��λ2
    int L3;//��λ3
    int L4;//��λ4
    int L5;//��λ5
    int L6;//��λ6
    int L7;//��λ7
    int L8;//��λ8
	int L9;//��λ9
}_Work_Num_;
extern _Work_Num_ Ctrl_Speed;//�����ٶȣ�����ֵ��
extern _Work_Num_ Set_Speed;//�����ٶ�
extern _Work_Num_ Display_Speed;//��ʾ�ٶ�
extern _Work_Num_ Rel_Speed;//ʵ���ٶ�
extern _Work_Num_ Speed;//��ʱ�洢�ٶ�
extern _Work_Num_ Speed_New;//�����ٶ���ʾ�������
extern _Work_Num_ Speed_Last;//�����ٶ���ʾ����洢
extern _Work_Num_ Speed_ADDMode;//�����ж��ٶ�ʱ���������½�
extern _Work_Num_ Display_RelSpeed;//������ʾ�ٶ�
extern uint8_t SpeedIcon_Step;//ת��ͼ��ת������

typedef struct
{
    int32_t L0;//��λ
	int32_t L1;//��λ1
    int32_t L2;//��λ2
    int32_t L3;//��λ3
    int32_t L4;//��λ4
    int32_t L5;//��λ5
    int32_t L6;//��λ6
    int32_t L7;//��λ7
    int32_t L8;//��λ8
	int32_t L9;//��λ9
}_Work_Num_long;
extern _Work_Num_long Ctrl_Time;//����ʱ�䣨����ֵ��
extern _Work_Num_long Set_Time;//����ʱ��
extern _Work_Num_long Display_Time;//��ʾʱ��
extern _Work_Num_long Rel_Time;//ʵ��ʱ��
extern _Work_Num_long Time;//��ʱ�洢ֵ

typedef struct
{
    uint8_t L0;//��λ1
	uint8_t L1;//��λ1
    uint8_t L2;//��λ2
    uint8_t L3;//��λ3
    uint8_t L4;//��λ4
    uint8_t L5;//��λ5
    uint8_t L6;//��λ6
    uint8_t L7;//��λ7
    uint8_t L8;//��λ8
	uint8_t L9;//��λ9
}_Work_Num_Flag;
extern _Work_Num_Flag SetTime_State;//ʱ���״̬
extern _Work_Num_Flag RelTime_State;//ʱ���״̬
extern _Work_Num_Flag DownTime_Over;//ʱ�䵹��ʱ����
extern _Work_Num_Flag Speed_Cnt;//���벶�����Ĵ���

extern uint8_t Time_unit;//ʱ�䵥λ
extern int Set_Temp;//�����¶�
extern int Ctrl_Temp;//�����¶ȣ�����ֵ��
extern int Ture_Temp;//����¶�
extern int Rel_Temp;//ʵ���¶�
extern int Display_Temp;//��ʾ�¶�
extern int Temp;//��ʱ�洢�¶�
extern uint8_t Temp_ADDMode;//�¶���ʾģʽ
extern uint8_t Temp_State;//�¶ȵ�״̬
extern int Temp_New,Temp_Last;//�����¶ȡ�֮ǰ�¶�
extern uint8_t ADD_Wait_Count;//������ʾ��������

#endif
