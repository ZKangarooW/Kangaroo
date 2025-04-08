#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xCC

#define Speed_MAX 1500//转速最大1500
#define Speed_MIN 50//转速最小50  5转  开机默认一百转
#define Time_MAX  86400//时间最长24小时
#define Time_MIN  0//时间最短0

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t SetMode_Option;//设置时当前设置的选项
    uint8_t Motor_Stop;//电机停止
}_sys_;
extern _sys_ sys;//系统初始化检测

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
    
    uint8_t Cw;//改变转向标志
    uint8_t CwIcn;//转向图标
}_Speed_;
extern _Speed_ Speed;//速度参数

typedef struct
{
	int32_t Set;//设置时间	
	int32_t Rel;//设置时间	
    int32_t Display_Rel;//用于显示实际时间
	int32_t Display_Set;//用于显示设置时间
}_Time_;
extern _Time_ Time;//时间参数

#endif
