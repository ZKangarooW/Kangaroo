#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "stm32f0xx_hal.h"

#define Speed_MIN 40  // 最低转速40
#define Speed_MAX 200 // 最高转速200
#define Time_MAX 86400// 最高设定时间24小时
#define Time_MIN 60   // 最低设定时间60S

typedef struct
{
    uint8_t Init_ok;        // 系统初始化是否完成，完成为1
    uint8_t SetMode_Option; // 设定模式
    uint8_t Run_Status;     // 系统启动为1
    uint8_t Motor_Stop;//电机停止
} _sys_;
extern _sys_ sys; // 系统初始化结构

typedef struct
{
    int16_t Set;         // 设定速度
    int16_t Rel;         // 实际速度
    int16_t Ctrl;        // 控制速度

    int16_t Display; // 显示速度
    float Stop_Cnt;      // 电机停止计数
    uint8_t ADDMode;     // 显示处理模式
    int16_t New;//当前的最大最小速度
	int16_t Last;//之前的速度
} _Speed_;
extern _Speed_ Speed; // 速度结构

typedef struct
{
    int32_t Set;     // 设定时间
    int32_t Rel;     // 实际时间
    int32_t Ctrl;     // 实际时间
    int32_t Display; // 显示时间
    int8_t Icn;      // 时间图标
} _Time_;
extern _Time_ Time; // 时间结构

#endif
