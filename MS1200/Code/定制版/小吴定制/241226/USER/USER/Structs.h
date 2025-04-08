#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Speed_MIN 200//转速最小200
#define Speed_MAX 2500//转速最大2500

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t Motor_Stop;//电机停止
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	int16_t Set;//设置速度
	int16_t Ctrl;//控制速度（期望值）
	int16_t Rel;//实际速度
	int16_t Display;//用于显示速度
	int16_t New;//当前的最大最小速度
	int16_t Last;//之前的速度
	float Stop_Cnt;//检测电机是否停止
	int8_t ADDMode;//显示处理的模式
}_Speed_;
extern _Speed_ Speed;//速度参数

#endif
