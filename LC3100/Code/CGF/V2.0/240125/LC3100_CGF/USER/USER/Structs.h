#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Type 1//0:8�� 1��12��

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
    
#define Xg_MAX 1700//���������
#define Speed_MAX 4000//���ת��

#if(Type == 0)
	#define Mode_R 10.35f//ת�ӵİ뾶
#elif(Type == 1)
	#define Mode_R 11.2f//ת�ӵİ뾶
#endif

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
	uint8_t Run_Status;//ϵͳ״̬
	uint8_t DownTime_Status;//����ʱ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
	uint8_t Motor_Stop;//���ֹͣ
	uint8_t Hardware_Damage;//Ӳ����
	uint8_t Lock_On;//���ӹر�
    uint8_t Lid_State;//���ظ��ӱ�־λ
    uint8_t Run_Mode;//����ģʽ��0��������1��CGF��2��PrP��3:APrF
    uint8_t CGF_Step;//CGF����
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint8_t ADDMode;//��ʾ�����ģʽ
	int16_t Set;//�����ٶ�
	int16_t Ctrl;//�����ٶȣ�����ֵ��
	int16_t Rel;//ʵ���ٶ�
    uint8_t Unit;//�ٶȵ�λ
    
    uint8_t Icon_Step;//�ٶ�ͼ�궯������
    
	int16_t Display_Rel;//������ʾʵ���ٶ�
	int16_t Display_Set;//������ʾ�����ٶ�
    
	int16_t New;//��ǰ�������С�ٶ�
	int16_t Last;//֮ǰ���ٶ�
    
	float Stop_Cnt;//�ٶ�ֹͣ����
}_Speed_;
extern _Speed_ Speed;//�ٶȲ���

typedef struct
{
	int32_t Set;//����ʱ��	
	int32_t Rel;//����ʱ��	
    int32_t Display_Rel;//������ʾʵ��ʱ��
	int32_t Display_Set;//������ʾ����ʱ��
}_Time_;
extern _Time_ Time;//ʱ�����

typedef struct
{
    uint16_t Set;//��ȫ�趨�¶�
    uint16_t Rel;//��ȫʵ���¶�
    uint16_t Display;//��ʾ��ȫ�¶�
    
    uint8_t Flag;//��ȫ�¶ȱ���
    uint8_t Twinkleg;//��ȫ�¶�ͼ����˸
}_SafeTemp_;
extern _SafeTemp_ SafeTemp;//��ȫ�¶Ȳ���

typedef struct
{
    uint8_t Option;//Pģʽ����ѡ��
}_PMode_;
extern _PMode_ PMode;//Pģʽ����

#endif
