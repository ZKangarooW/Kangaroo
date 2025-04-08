#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

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
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

extern int32_t Speed;//��ʱ�ٶ�
extern uint32_t Ctrl_Speed;//�����ٶȣ�����ֵ��
extern int32_t Set_Speed;//�����ٶ�
extern uint32_t Speed_Cnt;//���ת��
extern uint32_t Rel_Speed;//ʵ���ٶ�
extern uint32_t Speed_New;//�����ٶ���ʾ�������
extern uint32_t Speed_Last;//�����ٶ���ʾ����洢
extern uint32_t Speed_ADDMode;//�����ж��ٶ�ʱ���������½�
extern uint32_t Display_Speed;//��ʾ�ٶ�

extern int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
extern int32_t Set_Time;//����ʱ��
extern int32_t Display_Time;//��ʾ����ʱ��
extern uint8_t DownTime_Over;//ʱ�䵹��ʱ����

#endif
