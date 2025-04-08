#include "Structs.h"

_sys_ sys;//系统初始化检测

uint8_t Speed_Unit;//速度单位
uint8_t Speed_Mode;//速度模式
uint8_t SpeedIcon_Step;//转速图标转动步骤
uint32_t Ctrl_Speed;//控制速度（期望值）
int32_t Set_Speed;//设置速度
uint32_t Rel_Speed;//实际速度
uint32_t Speed_Cnt;//检测转速
uint32_t Speed;//临时存储速度
uint32_t Speed_New;//用于速度显示处理更新
uint32_t Speed_Last;//用于速度显示处理存储
uint32_t Speed_ADDMode;//用于判断速度时上升还是下降
uint32_t Display_Speed;//显示速度

int32_t Ctrl_Time;//控制时间（期望值）
int32_t Set_Time;//设置时间
int32_t Display_Time;//显示控制时间
int32_t Time;//临时存储值
uint8_t Time_Unit;//时间单位
uint8_t DownTime_Over;//时间倒计时结束
uint8_t Time_State;//时间状态

uint8_t Start_Flag;//开始按键标志
