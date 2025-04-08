#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 0//0:单加热  1：加热磁力款
#define Key_Type 0//0：薄膜款 1：按键款

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xFF

#define Speed_MAX 1200
#define Speed_MIN 100
#define Temp_MAX 1000//100℃
#define Temp_MIN 0
#define Time_MAX 86340//23小时59分钟
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
	uint16_t Set;//设定速度
	uint16_t Rel;//实际速度
	uint16_t Ctrl;//控制速度
	uint16_t Display_Set;//显示设定速度
	uint16_t Display_Rel;//显示实际速度
	uint8_t IcnStep;//速度图标运行动画步骤
	float Stop_Cnt;//电机停止计数
	uint8_t DisplayMode;//显示模式
}_Speed_;
extern _Speed_ Speed;//速度结构

typedef struct
{
	uint16_t Set;//设定温度
	uint16_t Rel;//实际温度
	uint16_t Ctrl;//控制温度
	uint16_t Alarm;//报警温度
	uint16_t Display_Set;//显示设定温度
	uint16_t Display_Rel;//显示实际温度
	uint8_t Icn;//温度图标
	float Rel_Speed;//真实速度
	float Alarm_Speed;//报警速度
	uint8_t DisplayMode;//显示模式
}_Temp_;
extern _Temp_ Temp;//温度结构

typedef struct
{
	uint32_t Set;//设定时间
	uint32_t Rel;//实际时间
	uint32_t Display_Set;//显示设定时间
	uint32_t Display_Rel;//显示实际时间
	uint8_t Icn;//时间图标
}_Time_;
extern _Time_ Time;//时间结构

#endif
