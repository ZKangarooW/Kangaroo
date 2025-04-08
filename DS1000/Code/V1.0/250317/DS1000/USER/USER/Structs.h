#ifndef __Structs_H__
#define __Structs_H__

#include "cms80f731xx.h"

#define FLASH_CHECK_START 0xCC
#define FLASH_CHECK_END 0xBB

#define Time_MAX  7200//时间最长2小时

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF

#define On 0
#define Off 1

#define Low_Temp 0
#define High_Temp 1

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t SetMode_Option;//设置时当前设置的选项
    uint8_t dataa[10];
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint8_t Ctrl;//控制挡位
	uint8_t Set;//设置挡位
}_Temp_;
extern _Temp_ Temp;//温度参数

typedef struct
{
	int16_t Set;//设置时间	
	int16_t Rel;//设置时间	
    int16_t Ctrl;//控制时间
	int16_t Display;//用于显示时间	
}_Time_;
extern _Time_ Time;//时间参数

#endif
