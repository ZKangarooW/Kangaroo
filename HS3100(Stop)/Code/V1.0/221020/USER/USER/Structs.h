#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Temp_MAX  2800//温度最大280度
#define Speed_MAX 1500//转速最大1500
#define Time_MAX  43200//时间最长12小时

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t SetMode_Option;//设置时当前设置的选项
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint8_t Temp_ADDMode;//显示处理的模式
	int16_t Ctrl_Temp;//控制温度（期望值）
	int16_t Set_Temp;//设置温度
	int16_t Rel_Temp;//实际温度
	int16_t Mesa_Temp;//台面温度
	int16_t Outside_Temp;//外部温度
	int16_t Display_RelTemp;//用于显示实际温度
	int16_t Display_SetTemp;//用于显示设置温度
	int16_t Temp_New;//当前的最大最小速度
	int16_t Temp_Last;//之前的速度
}_Temp_;
extern _Temp_ Temp;//温度参数

typedef struct
{
	uint8_t Speed_ADDMode;//显示处理的模式
	int16_t Set_Speed;//设置速度
	int16_t Ctrl_Speed;//控制速度（期望值）
	int16_t Rel_Speed;//实际速度
	int16_t Display_RelSpeed;//用于显示实际速度
	int16_t Display_SetSpeed;//用于显示设置速度
	int16_t Speed_New;//当前的最大最小速度
	int16_t Speed_Last;//之前的速度
}_Speed_;
extern _Speed_ Speed;//速度参数

typedef struct
{
	int32_t Ctrl_Time;//控制时间（期望值）
	int32_t Set_Time;//设置时间	
	int32_t Display_Time;//用于显示时间	
}_Time_;
extern _Time_ Time;//时间参数

#endif
