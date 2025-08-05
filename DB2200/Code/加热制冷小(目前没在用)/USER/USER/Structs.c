#include "Structs.h"

_sys_ sys;//系统初始化检测

int32_t Ctrl_Time;//控制时间（期望值）
int32_t Set_Time;//设置时间
int32_t Display_CtrlTime;//显示控制时间
int32_t Display_SetTime;//显示设置时间
int32_t Time;//临时存储值
uint8_t Time_Unit;//时间单位
uint8_t Time_State;//时间的状态
uint8_t DownTime_Over;//时间倒计时结束

int Set_Temp;//设置温度
int Ctrl_Temp;//控制温度（期望值）
int Ture_Temp;//测得温度
int Rel_Temp;//实际温度
int Display_RelTemp;//显示实际温度
int Display_CtrlTemp;//显示控制温度
int Temp;//临时存储温度
uint8_t Temp_ADDMode;//温度显示模式
int Temp_New,Temp_Last;//现在温度、之前温度
uint8_t HEAT_ICO;//加热图标
int ADD_Wait_Count;//升温降温的时间

uint8_t Display_Circle;//P模式外圈
uint8_t Circle_Run;//跑圈的标志位
uint8_t Show_Circle;//P模式外圈显示
uint8_t PMode_Status;//P模式状态
uint8_t PMode_Mode;//P模式的梯度和记忆切换
uint8_t PMode_Option;//P模式选项
uint8_t PMode_P1;//P模式P1值
uint8_t PMode_P2;//P模式P2值
