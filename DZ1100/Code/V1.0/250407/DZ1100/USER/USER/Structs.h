#ifndef __Structs_H__
#define __Structs_H__

#include "cms80f731xx.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xFF

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status;//ϵͳ״̬
}_sys_;
extern _sys_ sys;//ϵͳ��ʼ�����

typedef struct
{	
	int16_t Rel;//����ʱ��	
}_Time_;
extern _Time_ Time;//ʱ�����

#endif
