#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "stm32f0xx_hal.h"

#define Type 0 // 0是4齿比100Pro  1是2齿比50Pro

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#if (Type == 0)
#define Speed_MAX 1200 // 最高转速
#define Speed_MIN 50   // 最低转速
#define Tooth_Ratio 4
#elif (Type == 1)
#define Speed_MAX 2000 // 最高转速
#define Speed_MIN 100  // 最低转速
#define Tooth_Ratio 2
#endif

#define Temp_MAX 2800  // 最高温度280℃
#define Temp_MIN -100  // 最低温度-10℃
#define Time_MAX 86400 // 最高设定时间24小时
#define Time_MIN 0     // 最低设定时间0S

typedef struct
{
    uint8_t Init_ok;        // 系统初始化是否完成，完成为1
    uint8_t SetMode_Option; // 设定模式
    uint8_t Run_Status;     // 系统启动为1
} _sys_;
extern _sys_ sys; // 系统初始化结构

typedef struct
{
    uint16_t Set;         // 设定速度
    uint16_t Rel;         // 实际速度
    uint16_t Ctrl;        // 控制速度
    uint16_t Display_Set; // 显示设定速度
    uint16_t Display_Rel; // 显示实际速度
    uint8_t IcnStep;      // 速度图标运行动画步骤
    float Stop_Cnt;       // 电机停止计数
    uint8_t ADDMode;      // 显示处理模式
    int16_t N_Val;        // 扭力值
    uint16_t Display_N;   // 扭力显示
} _Speed_;
extern _Speed_ Speed; // 速度结构

typedef struct
{
    int16_t Set;            // 设定温度
    int16_t Rel;            // 实际温度
    int16_t Ctrl;           // 控制温度
    int16_t Display;        // 显示温度
    uint8_t Safe_Mode;      // 安全模式
    uint8_t Safe_Temp_Flag; // 安全温度超量
    uint8_t Icn;            // 安全温度图标
} _Temp_;
extern _Temp_ Temp; // 温度结构

typedef struct
{
    int32_t Set;      // 设定时间
    uint32_t Rel;     // 实际时间
    uint32_t Display; // 显示时间
    uint8_t Icn;      // 时间图标
} _Time_;
extern _Time_ Time; // 时间结构

#endif
