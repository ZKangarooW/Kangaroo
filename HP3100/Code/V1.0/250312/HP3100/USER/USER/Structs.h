#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xA4

#define Temp_MAX  3100//温度最大310度
#define Time_MAX  43200//时间最长12小时

enum
{
	C1=0,
	C2
};

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
    uint8_t Motor_Stop;//电机停止
	uint8_t SetMode_Option;//设置时当前设置的选项
    uint8_t DownTime_Type;//倒计时类型，默认C1，温度到了后倒计时，C2启动就倒计时
    uint8_t DownTime_Mode;//进入倒计时模式切换
    
    uint8_t Lock;//锁定按键
    float Lock_Alarm;//锁定误触报警
    uint8_t Display;//系统显示开关
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
}_Temp_;
extern _Temp_ Temp;//温度参数

typedef struct
{
	int32_t Set;//设置时间	
	int32_t Rel;//设置时间	
    int32_t Ctrl;//控制时间
	int32_t Display_Rel;//用于显示实际时间	
    int32_t Display_Set;//用于显示设置时间	
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
