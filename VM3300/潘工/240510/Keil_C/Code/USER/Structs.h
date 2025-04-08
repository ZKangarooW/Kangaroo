#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "sc95f.H"

typedef struct
{
    uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t SetMode_Option;//设定模式
    uint8_t Run_Status;//系统启动为1
	uint8_t flag;
} _sys_;
extern _sys_ sys;//系统初始化结构

typedef struct
{
    int16_t Set;//设定速度
    int16_t Rel;//实际速度
    int16_t Ctrl;//控制速度

    int16_t Display;//显示速度
    float Stop_Cnt;//电机停止计数
    uint8_t ADDMode;//显示处理模式
} _Speed_;
extern _Speed_ Speed;//速度结构

#endif
