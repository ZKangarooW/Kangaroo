#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Time_MAX  43200//时间最长12小时
#define Temp_MAX  600//温度最大60度

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
    uint8_t Time_Status;//倒计时状态
	uint8_t SetMode_Option;//设置时当前设置的选项
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint8_t ADDMode;//显示处理的模式
	int16_t Ctrl;//控制温度（期望值）
	int16_t Set;//设置温度
	int16_t Rel;//实际温度
	int16_t Display_Rel;//用于显示实际温度
	int16_t Display_Set;//用于显示设置温度
	int16_t New;//当前的最大最小温度
	int16_t Last;//之前的温度
}_Temp_;
extern _Temp_ Temp;//温度参数

typedef struct
{
	int32_t Set;//设置时间	
	int32_t Rel;//设置时间	
	int32_t Display_Set;//用于显示设定时间
    int32_t Display_Rel;//用于显示实际时间	
}_Time_;
extern _Time_ Time;//时间参数

#endif
