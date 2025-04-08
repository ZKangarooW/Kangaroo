#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f1xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC1

#define Speed_MIN 50//最低转速100
#define Speed_MAX 1500//最高转速1500
#define Time_MAX 86400//最高设定时间24小时
#define Time_MIN 0//最低设定时间0S

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t SetMode_Option;//设定模式
    uint8_t New_Work;//当前工位
    uint8_t Sync;//同步
}_sys_;
extern _sys_ sys;// 系统初始化结构

typedef struct
{
    int16_t Set;//设定速度
    int16_t Rel;//实际速度
    int16_t Ctrl;//控制速度

    int16_t Display_Set;//显示设定速度
    int16_t Display_Rel;//显示实际速度
    
    int8_t IconStep;//速度图标运行动画步骤
    
    float Stop_Cnt;//电机停止计数
    uint8_t ADDMode;//显示处理模式
} _Speed_;

typedef struct
{
    int32_t Set;//设定时间
    int32_t Rel;//实际时间
    int32_t Ctrl;//控制速度

    int32_t Display_Set;//显示设定时间
    int32_t Display_Rel;//显示实际时间
    
    int8_t Icon;//时间图标
} _Time_;

typedef struct
{
    uint8_t Motor_Stop;//电机停止
    uint8_t Run_Status;//系统启动为1
    _Speed_ Speed;
    _Time_ Time;
} _Work_Num_;
extern _Work_Num_ Work_Num[4];//工位参数

#endif
