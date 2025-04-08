#include "Structs.h"

_sys_ sys;//系统初始化检测

uint8_t Speed_Unit;//速度单位
uint8_t Speed_Mode;//速度模式
uint8_t SpeedIcon_Step;//转速图标转动步骤
uint32_t Ctrl_Speed;//控制速度（期望值）
int32_t Set_Speed;//设置速度
int8_t  Val_Speed;//速度数组
int8_t  Val_xg;//离心力数组
uint32_t Rel_Speed;//实际速度
uint32_t Speed_Cnt;//检测转速
uint32_t Speed;//临时存储速度
uint32_t Speed_New;//用于速度显示处理更新
uint32_t Speed_Last;//用于速度显示处理存储
uint32_t Display_RelSpeed;//用于显示速度
uint32_t Display_SetSpeed;//显示速度
uint16_t Speed_MAX;//最大速度

int32_t Ctrl_Time;//控制时间（期望值）
int32_t Set_Time;//设置时间
int32_t Display_CtrlTime;//显示控制时间
int32_t Display_SetTime;//显示设置时间
int32_t Time;//临时存储值
uint8_t Time_Unit;//时间单位
uint8_t DownTime_Over;//时间倒计时结束

uint8_t PModeIcon_Step;//记忆模式图标转动步骤
uint8_t PMode_Option;//P模式选项
uint8_t Circle_Run;//跑圈的标志位
uint8_t Show_Circle;//P模式外圈显示

uint8_t Safe_Mode;//安全模式
uint8_t Safe_Temp_Flag;//安全温度超量
uint8_t Safe_Temp_Twinkleg;//安全温度图标闪烁
int16_t Safe_Set_Temp;//安全设定温度
int16_t Safe_Rel_Temp;//安全实际温度
int16_t Display_SafeTemp;//显示安全温度
uint8_t Lid_State;//盖子状态
