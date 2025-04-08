#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xCC

#define Time_MAX  28800//时间最长24小时
#define Time_MIN  60//时间最短60S

extern uint16_t Speed_MAX;//最大转速
extern uint16_t Speed_MIN;//最小转速

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
	uint8_t Run_Status;//系统启动为1
	uint8_t Motor_Stop;//电机停止
}_sys_;
extern _sys_ sys;//系统初始化检测

extern int Ctrl_Speed;//控制速度（期望值）
extern int Set_Speed;//设置速度
extern int Rel_Speed;//实际速度
extern int Display_SetSpeed;//用于显示设置速度
extern int Display_RelSpeed;//用于显示实际速度
extern int Speed;//临时存储速度
extern uint8_t Speed_Cnt;//输入捕获进入的次数
extern int Speed_New;//用于速度显示处理更新
extern int Speed_Last;//用于速度显示处理存储
extern int Speed_ADDMode;//用于判断速度时上升还是下降
extern uint8_t pwm_start;
extern int32_t Ctrl_Time;//控制时间（期望值）
extern int32_t Set_Time;//设置时间
extern int32_t Display_SetTime;//显示时间
extern int32_t Display_CtrlTime;//显示时间
extern int32_t Time;//临时存储值
extern uint8_t Time_State;//时间的状态
extern uint8_t DownTime_Over;//时间倒计时结束
//extern uint8_t Time_unit;//时间单位


#endif
