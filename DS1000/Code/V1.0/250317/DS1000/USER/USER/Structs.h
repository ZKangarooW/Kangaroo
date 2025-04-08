#ifndef __Structs_H__
#define __Structs_H__

#include "cms80f731xx.h"

#define FLASH_CHECK_START 0xCC
#define FLASH_CHECK_END 0xBB

#define Time_MAX  7200//ʱ���2Сʱ

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF

#define On 0
#define Off 1

#define Low_Temp 0
#define High_Temp 1

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
    uint8_t dataa[10];
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	uint8_t Ctrl;//���Ƶ�λ
	uint8_t Set;//���õ�λ
}_Temp_;
extern _Temp_ Temp;//�¶Ȳ���

typedef struct
{
	int16_t Set;//����ʱ��	
	int16_t Rel;//����ʱ��	
    int16_t Ctrl;//����ʱ��
	int16_t Display;//������ʾʱ��	
}_Time_;
extern _Time_ Time;//ʱ�����

#endif
