#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 1//0为5PRO，1为7PRO
#if(Type==1)
#define Speed_MAX 7000//转速最大7000
#define Rcf_MAX 12//离心力最大标格12
#elif(Type==0)
#define Speed_MAX 5000//转速最大5000
#define Rcf_MAX 8//离心力最大标格8
#endif
#define Speed_MIN 1000//转速最小1000
#define Time_MAX 5940//最大99分钟
#define Time_MIN 10//最小10s

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
	uint8_t Run_Status;//系统状态
	uint8_t DownTime_Status;//倒计时状态
	uint8_t SetMode_Option;//设置时当前设置的选项
	uint8_t Lock_On;//盖子关闭
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint32_t Ctrl_Speed;//控制速度（期望值）
	uint8_t Speed_Mode;//速度模式
	uint8_t Speed_Unit;//速度单位
	uint8_t Speed_Rcf;//离心力
	int32_t Set_Speed;//设置速度
	uint32_t Rel_Speed;//实际速度
	uint32_t Display_Speed;//显示速度
}_Speed_;
extern _Speed_ Speed;//系统初始化检测

typedef struct
{
	int32_t Ctrl_Time;//控制时间（期望值）
	int32_t Set_Time;//设置时间
	int32_t Display_Time;//显示控制时间
	uint8_t Time_Unit;//时间单位
	uint8_t DownTime_Over;//时间倒计时结束
}_Time_;
extern _Time_ Time;//系统初始化检测

#endif
