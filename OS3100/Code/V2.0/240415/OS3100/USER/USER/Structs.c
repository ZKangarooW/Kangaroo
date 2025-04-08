#include "Structs.h"

_sys_ sys;//系统初始化检测

uint16_t Speed;//临时速度
uint16_t Rel_Speed;//实际速度
int16_t Set_Speed;//设定速度
uint16_t Ctrl_Speed;//控制速度
int16_t Display_Speed;//显示速度
uint8_t Speed_Cnt;//速度清零计数
uint8_t Speed_ADDMode;//速度显示模式
uint16_t Speed_New;//现在的速度
uint16_t Speed_Last;//上一次的速度

int32_t Time;//临时时间
int32_t Set_Time;//设定时间
int32_t Ctrl_Time;//控制时间
uint8_t Time_State;//时间的状态
int32_t Display_Time;//显示时间
uint8_t DownTime_Over;//倒计时结束
