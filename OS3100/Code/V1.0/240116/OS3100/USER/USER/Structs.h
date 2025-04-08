#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define Type 0 //0是30 pro
			   //1是15 pro 

#if(Type == 0)
#define MIN_Speed 50
#define MAX_Speed 1200
#define Tooth_Ratio 4
#elif(Type == 1)
#define MIN_Speed 100
#define MAX_Speed 2000
#define Tooth_Ratio 2
#endif

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
    uint8_t SetMode_Option;//选择设置模式
	uint8_t Motor_Stop;//电机停止
}_sys_;
extern _sys_ sys;//系统初始化检测

extern uint16_t Speed;//临时速度
extern uint16_t Rel_Speed;//实际速度
extern int16_t Set_Speed;//设定速度
extern uint16_t Ctrl_Speed;//控制速度
extern int16_t Display_Speed;//显示速度
extern uint8_t Speed_Cnt;//速度清零计数
extern uint8_t Speed_ADDMode;//速度显示模式
extern uint16_t Speed_New;//现在的速度
extern uint16_t Speed_Last;//上一次的速度

extern int32_t Time;//临时时间
extern int32_t Set_Time;//设定时间
extern int32_t Ctrl_Time;//控制时间
extern uint8_t Time_State;//时间的状态
extern int32_t Display_Time;//显示时间
extern uint8_t DownTime_Over;//倒计时结束

extern uint8_t Display_OFF;//不显示屏幕

#endif
