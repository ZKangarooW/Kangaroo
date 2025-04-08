#include "Structs.h"

_sys_ sys;//系统初始化检测

int16_t Speed;//临时速度
int16_t Set_Speed;//设定速度
int16_t Ctrl_Speed;//控制速度
int16_t Rel_Speed;//实际速度
int16_t Display_Speed;//显示速度
int16_t Speed_Cnt;//没进入输入捕获的时间
uint8_t Speed_ADDMode;//用于判断速度时上升还是下降
int16_t Speed_New;//用于速度显示处理更新
int16_t Speed_Last;//用于速度显示处理存储


int16_t Time;//临时速度
int16_t Set_Time;//设定速度
int16_t Rel_Time;//实际速度
int16_t Display_Time;//显示时间
uint8_t Time_Unit;//时间分钟秒钟切换
uint8_t Time_State;//时间的状态
uint8_t DownTime_Over;//时间倒计时结束
