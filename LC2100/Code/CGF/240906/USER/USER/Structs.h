#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))
	
#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xB1

#define Speed_Min 500 
#define Xg_Min 50
#define Time_MAX 3590//最长59分50秒
#define Time_Min 30//最少30s
extern uint16_t Speed_MAX;
extern uint16_t Xg_MAX;

typedef struct
{ 
	uint8_t Init_ok;//系统初始化是否完成，完成为1
	uint8_t Run_Status;//系统状态
	uint8_t DownTime_Status;//倒计时状态
	uint8_t SetMode_Option;//设置时当前设置的选项
	uint8_t Motor_Stop;//电机停止
	uint8_t Lock_On;//盖子关闭
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	int16_t Set;//设定速度
	int16_t Rel;//设定速度
	int16_t Cnt;//检测转速
	int16_t Ctrl;//控制速度（期望值）
	int16_t Display;//显示速度
	int16_t New;//用于速度显示处理更新
	int16_t Last;//用于速度显示处理存储
	int8_t Unit;//速度单位
	int8_t ADDMode;//用于判断速度时上升还是下降
}_Speed_;
extern _Speed_ Speed;//速度

typedef struct
{
	int32_t Set;//设定时间
	int32_t Ctrl;//控制时间（期望值）
	int32_t Display;//显示时间
}_Time_;
extern _Time_ Time;//时间

typedef struct
{
	uint8_t Mode;//是否在CGF得模式中
    uint8_t Option;//当前运行的数据
}_CGF_;
extern _CGF_ CGF;//时间

#endif
