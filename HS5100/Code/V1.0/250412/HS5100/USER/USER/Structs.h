#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xA8

#define Speed_MAX 1500//ת�����1500 50-1500
#define Speed_MIN 50//ת����� 50
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
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
	uint8_t Motor_Stop;//���ֹͣ
	uint8_t Lock;//��������
    float Lock_Alarm;//�����󴥱���
    uint8_t Display;//ϵͳ��ʾ����
    
    uint8_t Setting;//���ý���
    uint8_t Setting_Option;//���ý����ѡ��
    
    uint8_t DownTime_Type;//����ʱ���ͣ�Ĭ��C1���¶ȵ��˺󵹼�ʱ��C2�����͵���ʱ
    uint8_t DownTime_Mode;//���뵹��ʱģʽ�л�
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint8_t ADDMode;//��ʾ������ģʽ
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
    
    uint8_t Up_Speed;//�����ٶ�
    int16_t Safe_Temp;//��ȫ�¶�
}_Temp_;
extern _Temp_ Temp;//�¶Ȳ���

typedef struct
{
	uint8_t ADDMode;//��ʾ������ģʽ
	int16_t Set;//�����ٶ�
	uint16_t Ctrl;//�����ٶȣ�����ֵ��
	uint16_t Rel;//ʵ���ٶ�
	uint16_t Display_Rel;//������ʾʵ���ٶ�
	uint16_t Display_Set;//������ʾ�����ٶ�
	uint16_t New;//��ǰ�������С�ٶ�
	uint16_t Last;//֮ǰ���ٶ�
	float Stop_Cnt;//�ٶ�ֹͣ����
	
	uint8_t Cw;//�ı�ת���־
    uint8_t CwIcn;//ת��ͼ��
	uint8_t CwShow;//ת��ͼ��Ķ��󶯻���ʾ
    uint8_t Up_Speed;//�����ٶ�
}_Speed_;
extern _Speed_ Speed;//�ٶȲ���

typedef struct
{
	int32_t Set;//����ʱ��	
	uint32_t Rel;//����ʱ��	
	uint32_t Display;//������ʾʱ��	
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
