#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 1//0为老款，1为新款

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
}_sys_;
extern _sys_ sys;//系统初始化检测

extern int16_t Speed;//临时速度
extern int16_t Set_Speed;//设定速度
extern int16_t Rel_Speed;//实际速度
extern int16_t Ctrl_Speed;//控制速度
extern int16_t Display_Speed;//显示速度
extern int16_t Speed_Cnt;//没进入输入捕获的时间
extern uint8_t Speed_ADDMode;//用于判断速度时上升还是下降
extern int16_t Speed_New;//用于速度显示处理更新
extern int16_t Speed_Last;//用于速度显示处理存储

extern int16_t Time;//临时时间
extern int16_t Set_Time;//设定时间
extern int16_t Rel_Time;//实际时间
extern int16_t Display_Time;//显示时间
extern uint8_t Time_Unit;//时间分钟秒钟切换
extern uint8_t Time_State;//时间的状态
extern uint8_t DownTime_Over;//时间倒计时结束



#endif
