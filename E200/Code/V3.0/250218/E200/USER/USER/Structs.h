#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"
#define ABS(x) ((x)>0?(x):-(x))
/**********�ṹ��************/
typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
	uint8_t SetMode_Option;//����ʱ��ǰ�����ĸ��¶ȵ�ѡ��
	uint8_t TempOption_Mun;//�����¶�ʱ��ǰ���õ�λ��
	uint8_t TimeOption_Mun;//����ʱ��ʱ��ǰ���õ�λ��
	uint8_t Calibration;//�Ƿ����У׼
	uint8_t Calibration_Step;//У׼����
	uint16_t Calibration_Temp1;//�¶�һ
	uint16_t Calibration_Temp2;//�¶ȶ�
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint16_t Set_Temp;//�����¶�
	uint16_t Ctrl_Temp;//�����¶�
	int16_t Rel_Temp;//ʵ���¶�
	int16_t Display_Temp;//��ʾ�¶�
	uint8_t ADDMode;//��ʾ����
}_Temp_;
extern _Temp_ Heat_Temp;//���������¶Ƚṹ��
extern _Temp_ Cool_Temp;//���������¶Ƚṹ��

typedef struct
{
	uint16_t Count_Time;//����ʱʱ��
	int16_t Set_Time;//����ʱ�趨ʱ��
	uint16_t Ctrl_Time;//����ʱ����ʱ��
    uint16_t Rel_Time;//����ʱʵ��ʱ��
	int16_t Display_Time;//��ʾʱ��
	uint8_t TimeDisplay_Flag;//ʱ����ʾ��־
	uint8_t CountDown_Start;//��������ʱ
	uint8_t Count_Start;//��������ʱ
}_Time_;
extern _Time_ Time;//ʱ��ṹ��

#endif
