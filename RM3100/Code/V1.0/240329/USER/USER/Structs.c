#include "Structs.h"

_sys_ sys;//系统初始化检测

int32_t Speed;//临时速度
uint8_t Speed_Unit;//速度单位
uint32_t Ctrl_Speed;//控制速度（期望值）
int32_t Set_Speed;//设置速度
uint32_t Rel_Speed;//实际速度
uint32_t Speed_Cnt;//检测转速
uint32_t Speed_New;//用于速度显示处理更新
uint32_t Speed_Last;//用于速度显示处理存储
uint32_t Speed_ADDMode;//用于判断速度时上升还是下降
uint32_t Display_Speed;//显示速度

int32_t Ctrl_Time;//控制时间（期望值）
int32_t Set_Time;//设置时间
int32_t Display_Time;//显示控制时间
uint8_t DownTime_Over;//时间倒计时结束
