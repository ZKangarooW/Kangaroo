#ifndef __Structs_H__
#define __Structs_H__

#include "cms80f731xx.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xFF

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{	
	int16_t Rel;//设置时间	
}_Time_;
extern _Time_ Time;//时间参数

#endif
