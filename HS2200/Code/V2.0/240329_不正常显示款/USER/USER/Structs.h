#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC7

#define Key_Type 0//0:按键款5pro 1：旋钮款5c

#define Speed_MAX 1500//转速最大1500


#if(Key_Type == 0)
	#define Temp_MAX  3100//温度最大310度
    #define Time_MAX  43200//时间最长12小时
#elif(Key_Type == 1)
	#define	Temp_MAX  2800//温度最大280度
    #define Time_MAX  0//时间最长0小时
#endif

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t SetMode_Option;//设置时当前设置的选项
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint8_t ADDMode;//显示处理的模式
	int16_t Ctrl;//控制温度（期望值）
	int16_t Set;//设置温度
	int16_t Rel;//实际温度
	int16_t Mesa;//台面温度
	int16_t Outside;//外部温度
	int16_t Display_Rel;//用于显示实际温度
	int16_t Display_Set;//用于显示设置温度
	int16_t New;//当前的最大最小速度
	int16_t Last;//之前的速度
	int16_t Old;//老的速度
	int16_t Speed;//老的速度
}_Temp_;
extern _Temp_ Temp;//温度参数

typedef struct
{
	uint8_t ADDMode;//显示处理的模式
	int16_t Set;//设置速度
	int16_t Ctrl;//控制速度（期望值）
	int16_t Rel;//实际速度
	int16_t Display_Rel;//用于显示实际速度
	int16_t Display_Set;//用于显示设置速度
	int16_t New;//当前的最大最小速度
	int16_t Last;//之前的速度
	float Stop_Cnt;//速度停止计数
}_Speed_;
extern _Speed_ Speed;//速度参数

typedef struct
{
	int32_t Set;//设置时间	
	int32_t Rel;//设置时间	
	int32_t Display;//用于显示时间	
}_Time_;
extern _Time_ Time;//时间参数

#endif
