#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

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
	uint8_t Motor_Stop;//电机停止
}_sys_;
extern _sys_ sys;//系统初始化检测

extern int32_t Speed;//临时速度
extern uint32_t Ctrl_Speed;//控制速度（期望值）
extern int32_t Set_Speed;//设置速度
extern uint32_t Speed_Cnt;//检测转速
extern uint32_t Rel_Speed;//实际速度
extern uint32_t Speed_New;//用于速度显示处理更新
extern uint32_t Speed_Last;//用于速度显示处理存储
extern uint32_t Speed_ADDMode;//用于判断速度时上升还是下降
extern uint32_t Display_Speed;//显示速度

extern int32_t Ctrl_Time;//控制时间（期望值）
extern int32_t Set_Time;//设置时间
extern int32_t Display_Time;//显示控制时间
extern uint8_t DownTime_Over;//时间倒计时结束

#endif
