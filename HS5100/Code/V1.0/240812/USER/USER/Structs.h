#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xA2

#define Speed_MAX 1500//转速最大1500 50-1500
#define Speed_MIN 50//转速最低 50
#define Temp_MAX  3500//温度最大350度
#define Time_MAX  43200//时间最长12小时

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t SetMode_Option;//设置时当前设置的选项
	uint8_t Motor_Stop;//电机停止
	uint8_t Lock;//锁定按键
    float Lock_Alarm;//锁定误触报警
    uint8_t Display;//系统显示开关
    
    uint8_t Setting;//设置界面
    uint8_t Setting_Option;//设置界面的选项
    
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint8_t ADDMode;//显示处理的模式
	int16_t Ctrl;//控制温度（期望值）
	int16_t Set;//设置温度
	int16_t Rel;//实际温度
	int16_t Mesa;//台面温度
	int16_t Outside;//外部温度
	int16_t Display_Rel;//用于显示实际温度
	int16_t Display_Set;//用于显示设置温度
	int16_t New;//当前的最大最小速度
	int16_t Last;//之前的速度
	int16_t Old;//老的速度
	int16_t Speed;//老的速度

	uint8_t Unit;//温度单位
    
    uint8_t Up_Speed;//上升速度
    int16_t Safe_Temp;//安全温度
}_Temp_;
extern _Temp_ Temp;//温度参数

typedef struct
{
	uint8_t ADDMode;//显示处理的模式
	int16_t Set;//设置速度
	uint16_t Ctrl;//控制速度（期望值）
	uint16_t Rel;//实际速度
	uint16_t Display_Rel;//用于显示实际速度
	uint16_t Display_Set;//用于显示设置速度
	uint16_t New;//当前的最大最小速度
	uint16_t Last;//之前的速度
	float Stop_Cnt;//速度停止计数
	
	uint8_t Cw;//改变转向标志
    uint8_t CwIcn;//转向图标
	uint8_t CwShow;//转向图标改动后动画显示
    uint8_t Up_Speed;//上升速度
}_Speed_;
extern _Speed_ Speed;//速度参数

typedef struct
{
	int32_t Set;//设置时间	
	uint32_t Rel;//设置时间	
	uint32_t Display;//用于显示时间	
}_Time_;
extern _Time_ Time;//时间参数

typedef struct
{
    uint8_t Mode;        // P模式中的模式 0：P记忆模式。1：梯度模式
    uint8_t Status;      // P模式开关 1:显示P模式和外框 2:梯度模式
    uint8_t P1;          // 第一个数
    uint8_t P2;          // 第二个数
    uint8_t Circle_Step; // 外框动画步骤
    uint16_t Light_BIT;  // 外框点亮的字节
    uint8_t Option;      // 当前的P模式值
} _PMode_;
extern _PMode_ PMode; // P模式参数

#endif
