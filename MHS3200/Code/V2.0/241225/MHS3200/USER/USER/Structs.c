#include "Structs.h"

uint16_t MAX_Speed;

_sys_ sys;//系统初始化检测

_Work_Num_ Ctrl_Speed;//控制速度（期望值）
_Work_Num_ Set_Speed;//设置速度
_Work_Num_ Display_Speed;//显示速度
_Work_Num_ Rel_Speed;//实际速度
_Work_Num_ Speed;//临时存储速度
_Work_Num_ Speed_New;//用于速度显示处理更新
_Work_Num_ Speed_Last;//用于速度显示处理存储
_Work_Num_ Speed_ADDMode;//用于判断速度时上升还是下降
_Work_Num_ Display_RelSpeed;//用于显示实际速度

_Work_Num_long Ctrl_Time;//控制时间（期望值）
_Work_Num_long Set_Time;//设置时间
_Work_Num_long Display_Time;//显示时间
_Work_Num_long Rel_Time;//实际时间
_Work_Num_long Time;//临时存储值
_Work_Num_Flag SetTime_State;//设置时间的状态
_Work_Num_Flag RelTime_State;//实际时间的状态
_Work_Num_Flag DownTime_Over;//时间倒计时结束
uint8_t Time_unit;//时间单位
_Work_Num_Flag Speed_Cnt;//输入捕获进入的次数
uint8_t SpeedIcon_Step;//转速图标转动步骤

int Set_Temp;//设置温度
int Ctrl_Temp;//控制温度（期望值）
int Ture_Temp;//测得温度
int Rel_Temp;//实际温度
int Temp;//临时存储温度
uint8_t Temp_ADDMode;//温度显示模式
uint8_t Temp_State;//温度的状态
int Temp_New,Temp_Last;//现在温度、之前温度
uint8_t ADD_Wait_Count;//升温显示缓慢上升
