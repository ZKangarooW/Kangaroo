#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "stm32f1xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xFF

#define Speed_MIN 100  // 最低转速100
#define Temp_MAX 1000  // 最高温度100℃ 步进0.1
#define Temp_MIN -50   // 最低温度-5℃ 加热0摄氏度
#define Time_MAX 86400 // 最高设定时间24小时
#define Time_MIN 5     // 最低设定时间5S

typedef struct
{
    uint8_t Init_ok;        // 系统初始化是否完成，完成为1
    uint8_t SetMode_Option; // 设定模式
    uint8_t Run_Status;     // 系统启动为1
} _sys_;
extern _sys_ sys; // 系统初始化结构

typedef struct
{
    int16_t Set;         // 设定速度
    int16_t Rel;         // 实际速度
    int16_t Ctrl;        // 控制速度
	int16_t MAX; // 最高转速1500 高模块800 步进100   控制最高转速还没写

    int16_t Display_Set; // 显示设定速度
    int16_t Display_Rel; // 显示实际速度
    int8_t IcnStep;      // 速度图标运行动画步骤
    float Stop_Cnt;      // 电机停止计数
    uint8_t ADDMode;     // 显示处理模式
} _Speed_;
extern _Speed_ Speed; // 速度结构

typedef struct
{
    int16_t Set;         // 设定温度
    int16_t Rel;         // 实际温度
    int16_t HEAT_GAI;    // 热盖温度
    int16_t Ctrl;        // 控制温度
    int16_t Display_Set; // 显示设定温度
    int16_t Display_Rel; // 显示实际温度
    uint8_t Mode;        // 0：加热，1：制冷
    uint8_t Icon;        // 温度图标
    uint8_t ADDMode;     // 显示处理模式
    uint8_t Base_Err;    // 模块错误报警
} _Temp_;
extern _Temp_ Temp; // 温度结构

typedef struct
{
    int32_t Set;     // 设定时间
    int32_t Rel;     // 实际时间
    int32_t Display; // 显示时间
    int8_t Icn;      // 时间图标
} _Time_;
extern _Time_ Time; // 时间结构

#endif
