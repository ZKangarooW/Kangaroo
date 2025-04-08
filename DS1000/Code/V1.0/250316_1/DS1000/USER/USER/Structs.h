#ifndef __Structs_H__
#define __Structs_H__

#include "cms80f731xx.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xA4

#define Time_MAX  7200//时间最长2小时

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF

#define On 0
#define Off 1

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t SetMode_Option;//设置时当前设置的选项
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	int32_t Set;//设置时间	
	int32_t Rel;//设置时间	
    int32_t Ctrl;//控制时间
	int32_t Display;//用于显示时间	
}_Time_;
extern _Time_ Time;//时间参数

#endif
