#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 1//0：10L&15L 1:30L 2:50L

#define FLASH_CHECK_START 0xAA

#if(Type == 0)
#define Speed_MAX 1500//转速最快1500
#define FLASH_CHECK_END 0xBB//校验类别
#define POLE_NUMBER 2//电机极数
#elif(Type == 1)
#define Speed_MAX 5000//转速最快1300
#define FLASH_CHECK_END 0xBB//校验类别
#define POLE_NUMBER 5//电机极数
#elif(Type == 2)
#define Speed_MAX 1100//转速最快1100
#define FLASH_CHECK_END 0xDD//校验类别
#define POLE_NUMBER 5//电机极数
#endif

#define Speed_MIN 50//转速最慢50
#define Time_MAX  86400//时间最长24小时
#define Time_MIN  60//时间最短60S

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
	uint8_t Run_Status;//系统启动为1
	uint8_t Motor_Stop;//电机停止
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint8_t ADDMode;//显示处理的模式
	uint8_t Cw;//改变转向标志
	uint8_t CwIcn;//转向图标
	int16_t Set;//设置速度
	int16_t Ctrl;//控制速度（期望值）
	int16_t Rel;//实际速度
	int16_t Display_Rel;//用于显示实际速度
	int16_t Display_Set;//用于显示设置速度
	int16_t New;//当前的最大最小速度
	float Stop_Cnt;//速度停止计数
}_Speed_;
extern _Speed_ Speed;//速度参数

typedef struct
{
	int32_t Set;//设置时间	
	int32_t Rel;//实际时间	
	int32_t Display_Set;//用于显示设定时间
	int32_t Display_Rel;//用于显示实际时间
}_Time_;
extern _Time_ Time;//时间参数


#endif
