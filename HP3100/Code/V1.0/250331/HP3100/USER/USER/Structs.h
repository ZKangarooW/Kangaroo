#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xA4

#define Temp_MAX  3100//�¶����310��
#define Time_MAX  43200//ʱ���12Сʱ

enum
{
	C1=0,
	C2
};

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
    uint8_t Motor_Stop;//���ֹͣ
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
    uint8_t DownTime_Type;//����ʱ���ͣ�Ĭ��C1���¶ȵ��˺󵹼�ʱ��C2�����͵���ʱ
    uint8_t DownTime_Mode;//���뵹��ʱģʽ�л�
    
    uint8_t Lock;//��������
    float Lock_Alarm;//�����󴥱���
    uint8_t Display;//ϵͳ��ʾ����
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
    uint8_t Unit;//�¶ȵ�λ
}_Temp_;
extern _Temp_ Temp;//�¶Ȳ���

typedef struct
{
	int32_t Set;//����ʱ��	
	int32_t Rel;//����ʱ��	
    int32_t Ctrl;//����ʱ��
	int32_t Display_Rel;//������ʾʵ��ʱ��	
    int32_t Display_Set;//������ʾ����ʱ��	
}_Time_;
extern _Time_ Time;//ʱ�����

typedef struct
{
    uint8_t Mode;        // Pģʽ�е�ģʽ 0��P����ģʽ��1���ݶ�ģʽ
    uint8_t Status;      // Pģʽ���� 1:��ʾPģʽ����� 2:�ݶ�ģʽ
    uint8_t P1;          // ��һ����
    uint8_t P2;          // �ڶ�����
    uint8_t Circle_Step; // ��򶯻�����
    uint16_t Light_BIT;  // ���������ֽ�
    uint8_t Option;      // ��ǰ��Pģʽֵ
} _PMode_;
extern _PMode_ PMode; // Pģʽ����

#endif
