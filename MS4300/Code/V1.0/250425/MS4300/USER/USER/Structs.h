#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC8

#define Speed_MIN 50//转速最慢50
#define Time_MAX  86400//时间最长24小时
#define Time_MIN  60//时间最短60S
#define Speed_MAX 1200//转速最慢50

typedef struct
{
    uint8_t Init_ok;//系统初始化是否完成，完成为1
	uint8_t Run_Status;//系统启动为1
	uint8_t Motor_Stop;//电机停止
    float Lock_Alarm;//锁定误触报警
}_sys_;
extern _sys_ sys;// 系统初始化结构

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
    int32_t Ctrl;//控制时间
	int32_t Display_Set;//用于显示设定时间
	int32_t Display_Rel;//用于显示实际时间
}_Time_;
extern _Time_ Time;//时间参数

typedef struct
{
    uint8_t Mode;        // P模式中的模式 0：P记忆模式。1：梯度模式
    uint8_t Status;      // P模式开关 1:显示P模式和外框
    uint8_t P1;          // 第一个数
    uint8_t P2;          // 第二个数
    uint8_t Circle_Step; // 外框动画步骤
    uint16_t Light_BIT;  // 外框点亮的字节
    uint8_t Option;      // 当前的P模式值
} _PMode_;
extern _PMode_ PMode; // P模式参数

#endif
