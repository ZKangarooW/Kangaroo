#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t DownTime_Status;//倒计时状态
	uint8_t SetMode_Option;//设置时当前设置的选项
	uint8_t CtrlTemp_Mode;//控温模式
	uint8_t SetP_Mode_Option;//设置P模式当前设置的选项
}_sys_;
extern _sys_ sys;//系统初始化检测

extern int32_t Ctrl_Time;//控制时间（期望值）
extern int32_t Set_Time;//设置时间
extern int32_t Display_CtrlTime;//显示控制时间
extern int32_t Display_SetTime;//显示设置时间
extern int32_t Time;//临时存储值
extern uint8_t Time_Unit;//时间单位
extern uint8_t Time_State;//时间的状态
extern uint8_t DownTime_Over;//时间倒计时结束

extern int Set_Temp;//设置温度
extern int Ctrl_Temp;//控制温度（期望值）
extern int Ture_Temp;//测得温度
extern int Rel_Temp;//实际温度
extern int Display_RelTemp;//显示实际温度
extern int Display_CtrlTemp;//显示控制温度
extern int Temp;//临时存储温度
extern uint8_t Temp_ADDMode;//温度显示模式
extern int Temp_New,Temp_Last;//现在温度、之前温度
extern uint8_t HEAT_ICO;//加热图标
extern int ADD_Wait_Count;//升温降温的时间

extern uint8_t Display_Circle;//P模式外圈
extern uint8_t Circle_Run;//跑圈的标志位
extern uint8_t Show_Circle;//P模式外圈显示
extern uint8_t PMode_Status;//P模式状态
extern uint8_t PMode_Mode;//P模式的梯度和记忆切换
extern uint8_t PMode_Option;//P模式选项
extern uint8_t PMode_P1;//P模式P1值
extern uint8_t PMode_P2;//P模式P2值

#endif
