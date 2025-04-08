#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Temp_MAX 1000//100℃
#define Temp_MIN 0
#define Time_MAX 86400//24小时
#define Time_MIN 0

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
	uint8_t SetMode_Option;//设定模式
	uint8_t Run_Status;//系统启动为1
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
    uint8_t ADDMode;//显示处理的模式
	int16_t Set;//设定温度
	int16_t Rel;//实际温度
	int16_t Ctrl;//控制温度
	int16_t Display_Set;//显示设定温度
	int16_t Display_Rel;//显示实际温度
    int16_t New;//当前的最大最小温度
	uint8_t Icn;//温度图标
}_Temp_;
extern _Temp_ Temp;//温度结构

typedef struct
{
	int32_t Set;//设定时间
	int32_t Rel;//实际时间
	int32_t Display_Set;//显示设定时间
	int32_t Display_Rel;//显示实际时间
	uint8_t Icn;//时间图标
}_Time_;
extern _Time_ Time;//时间结构

#endif
