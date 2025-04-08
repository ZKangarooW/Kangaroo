#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Speed_MIN 100
#define Speed_MAX 1200
#define Time_MAX 86400

#define Type_Motor 1 //0:开机显示200 5S  1：显示100 10S

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
    uint8_t SetMode_Option;//选择设置模式
    uint8_t Motor_Stop;//电机停止
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
    int16_t Set;         // 设定速度
    int16_t Rel;         // 实际速度
    int16_t Ctrl;        // 控制速度
    int16_t New;        // 用于速度显示处理更新
    int16_t Last;        // 用于速度显示处理存储
    int16_t Display;//显示速度
    int8_t IcnStep;// 速度图标运行动画步骤
    float Stop_Cnt;// 电机停止计数
    uint8_t ADDMode;// 显示处理模式
} _Speed_;
extern _Speed_ Speed; // 速度结构

typedef struct
{
    int32_t Set;     // 设定时间
    int32_t Rel;     // 实际时间
    int32_t Ctrl;     // 控制时间
    int32_t Display; // 显示时间
    int8_t Icn;      // 时间图标
} _Time_;
extern _Time_ Time; // 时间结构

#endif
