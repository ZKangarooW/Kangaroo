#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Type 1//0:8孔 1：12孔

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))
    
#define Xg_MAX 1700//最大离心力
#define Speed_MAX 4000//最大转速

#if(Type == 0)
	#define Mode_R 10.35f//转子的半径
#elif(Type == 1)
	#define Mode_R 11.2f//转子的半径
#endif

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
	uint8_t Run_Status;//系统状态
	uint8_t DownTime_Status;//倒计时状态
	uint8_t SetMode_Option;//设置时当前设置的选项
	uint8_t Motor_Stop;//电机停止
	uint8_t Hardware_Damage;//硬件损坏
	uint8_t Lock_On;//盖子关闭
    uint8_t Lid_State;//开关盖子标志位
    uint8_t Run_Mode;//运行模式，0：正常，1：CGF，2：PrP，3:APrF
    uint8_t CGF_Step;//CGF步骤
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint8_t ADDMode;//显示处理的模式
	int16_t Set;//设置速度
	int16_t Ctrl;//控制速度（期望值）
	int16_t Rel;//实际速度
    uint8_t Unit;//速度单位
    
    uint8_t Icon_Step;//速度图标动画步骤
    
	int16_t Display_Rel;//用于显示实际速度
	int16_t Display_Set;//用于显示设置速度
    
	int16_t New;//当前的最大最小速度
	int16_t Last;//之前的速度
    
	float Stop_Cnt;//速度停止计数
}_Speed_;
extern _Speed_ Speed;//速度参数

typedef struct
{
	int32_t Set;//设置时间	
	int32_t Rel;//设置时间	
    int32_t Display_Rel;//用于显示实际时间
	int32_t Display_Set;//用于显示设置时间
}_Time_;
extern _Time_ Time;//时间参数

typedef struct
{
    uint16_t Set;//安全设定温度
    uint16_t Rel;//安全实际温度
    uint16_t Display;//显示安全温度
    
    uint8_t Flag;//安全温度报警
    uint8_t Twinkleg;//安全温度图标闪烁
}_SafeTemp_;
extern _SafeTemp_ SafeTemp;//安全温度参数

typedef struct
{
    uint8_t Option;//P模式数组选项
}_PMode_;
extern _PMode_ PMode;//P模式参数

#endif
