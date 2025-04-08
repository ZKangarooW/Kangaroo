#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f1xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC1

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
}_sys_;
extern _sys_ sys;//系统初始化检测

#endif
