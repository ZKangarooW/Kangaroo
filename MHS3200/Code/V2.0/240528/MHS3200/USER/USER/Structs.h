#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f1xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xDD

#define Integration_TYPE 1//0：四联六联 1：九联

#define MAX_Time 71940

extern uint16_t MAX_Speed;

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
    int L0;//工位
	int L1;//工位1
    int L2;//工位2
    int L3;//工位3
    int L4;//工位4
    int L5;//工位5
    int L6;//工位6
    int L7;//工位7
    int L8;//工位8
	int L9;//工位9
}_Work_Num_;
extern _Work_Num_ Ctrl_Speed;//控制速度（期望值）
extern _Work_Num_ Set_Speed;//设置速度
extern _Work_Num_ Display_Speed;//显示速度
extern _Work_Num_ Rel_Speed;//实际速度
extern _Work_Num_ Speed;//临时存储速度
extern _Work_Num_ Speed_New;//用于速度显示处理更新
extern _Work_Num_ Speed_Last;//用于速度显示处理存储
extern _Work_Num_ Speed_ADDMode;//用于判断速度时上升还是下降
extern _Work_Num_ Display_RelSpeed;//用于显示速度
extern uint8_t SpeedIcon_Step;//转速图标转动步骤

typedef struct
{
    int32_t L0;//工位
	int32_t L1;//工位1
    int32_t L2;//工位2
    int32_t L3;//工位3
    int32_t L4;//工位4
    int32_t L5;//工位5
    int32_t L6;//工位6
    int32_t L7;//工位7
    int32_t L8;//工位8
	int32_t L9;//工位9
}_Work_Num_long;
extern _Work_Num_long Ctrl_Time;//控制时间（期望值）
extern _Work_Num_long Set_Time;//设置时间
extern _Work_Num_long Display_Time;//显示时间
extern _Work_Num_long Rel_Time;//实际时间
extern _Work_Num_long Time;//临时存储值

typedef struct
{
    uint8_t L0;//工位1
	uint8_t L1;//工位1
    uint8_t L2;//工位2
    uint8_t L3;//工位3
    uint8_t L4;//工位4
    uint8_t L5;//工位5
    uint8_t L6;//工位6
    uint8_t L7;//工位7
    uint8_t L8;//工位8
	uint8_t L9;//工位9
}_Work_Num_Flag;
extern _Work_Num_Flag SetTime_State;//时间的状态
extern _Work_Num_Flag RelTime_State;//时间的状态
extern _Work_Num_Flag DownTime_Over;//时间倒计时结束
extern _Work_Num_Flag Speed_Cnt;//输入捕获进入的次数

extern uint8_t Time_unit;//时间单位
extern int Set_Temp;//设置温度
extern int Ctrl_Temp;//控制温度（期望值）
extern int Ture_Temp;//测得温度
extern int Rel_Temp;//实际温度
extern int Display_Temp;//显示温度
extern int Temp;//临时存储温度
extern uint8_t Temp_ADDMode;//温度显示模式
extern uint8_t Temp_State;//温度的状态
extern int Temp_New,Temp_Last;//现在温度、之前温度
extern uint8_t ADD_Wait_Count;//升温显示缓慢上升

#endif
