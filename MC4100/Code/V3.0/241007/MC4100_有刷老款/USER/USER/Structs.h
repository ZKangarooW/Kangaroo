#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

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
	uint8_t Lock_On;//盖子关闭
}_sys_;
extern _sys_ sys;//系统初始化检测

extern uint8_t Speed_Unit;//速度单位
extern uint8_t Speed_Mode;//速度模式,离心力1-5
extern uint8_t SpeedIcon_Step;//转速图标转动步骤
extern uint32_t Ctrl_Speed;//控制速度（期望值）
extern int32_t Set_Speed;//设置速度
extern int8_t  Val_Speed;//速度数组
extern int8_t  Val_xg;//离心力数组
extern uint32_t Speed_Cnt;//检测转速
extern uint32_t Rel_Speed;//实际速度
extern uint32_t Speed_New;//用于速度显示处理更新
extern uint32_t Speed_Last;//用于速度显示处理存储
extern uint32_t Display_RelSpeed;//用于显示速度
extern uint32_t Display_SetSpeed;//显示速度
extern uint16_t Speed_MAX;//最大速度

extern int32_t Ctrl_Time;//控制时间（期望值）
extern int32_t Set_Time;//设置时间
extern int32_t Display_CtrlTime;//显示控制时间
extern int32_t Display_SetTime;//显示设置时间
extern uint8_t Time_Unit;//时间单位
extern uint8_t DownTime_Over;//时间倒计时结束

extern uint8_t PModeIcon_Step;//记忆模式图标转动步骤
extern uint8_t PMode_Option;//P模式选项
extern uint8_t Circle_Run;//跑圈的标志位
extern uint8_t Show_Circle;//P模式外圈显示

extern uint8_t Safe_Mode;//安全模式
extern uint8_t Safe_Temp_Flag;//安全温度超量
extern uint8_t Safe_Temp_Twinkleg;//安全温度图标闪烁
extern int16_t Safe_Set_Temp;//安全设定温度
extern int16_t Safe_Rel_Temp;//安全实际温度
extern int16_t Display_SafeTemp;//显示安全温度
extern uint8_t Lid_State;//盖子状态

#endif
