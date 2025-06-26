#include "Structs.h"

uint16_t Speed_MAX;//最大转速
uint16_t Speed_MIN;//最小转速

_sys_ sys;//系统初始化检测

int Ctrl_Speed;//控制速度（期望值）
int Set_Speed;//设置速度
int Rel_Speed;//实际速度
int Display_SetSpeed;//用于显示设置速度
int Display_RelSpeed;//用于显示实际速度
int Speed;//临时存储速度
uint8_t Speed_Cnt;//输入捕获进入的次数
int Speed_New;//用于速度显示处理更新
int Speed_Last;//用于速度显示处理存储
int Speed_ADDMode;//用于判断速度时上升还是下降
uint8_t pwm_start = 8;

int32_t Ctrl_Time;//控制时间（期望值）
int32_t Set_Time;//设置时间
int32_t Display_SetTime;//显示时间
int32_t Display_CtrlTime;//显示时间
int32_t Time;//临时存储值
uint8_t Time_State;//时间的状态
uint8_t DownTime_Over;//时间倒计时结束


