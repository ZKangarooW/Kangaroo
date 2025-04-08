#ifndef __Structs_H__
#define __Structs_H__

#include "cms80f731xx.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xA4

#define Time_MAX  7200//ʱ���2Сʱ

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF

#define On 0
#define Off 1

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
	uint8_t SetMode_Option;//����ʱ��ǰ���õ�ѡ��
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{
	int32_t Set;//����ʱ��	
	int32_t Rel;//����ʱ��	
    int32_t Ctrl;//����ʱ��
	int32_t Display;//������ʾʱ��	
}_Time_;
extern _Time_ Time;//ʱ�����

#endif
