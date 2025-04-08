#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xBB

#define Temp_MAX 1000//温度最高100℃
#define Temp_MIN 0//温度最低0℃
#define Time_MAX  86400//时间最长24小时
#define Time_MIN  0//时间最短0

typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status;//系统状态
	uint8_t SetMode_Option;//设置时当前设置的选项
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint8_t ADDMode;//显示处理的模式
	int16_t Ctrl;//控制温度（期望值）
	int16_t Set;//设置温度
	int16_t Rel;//实际温度
	int16_t Display_Rel;//用于显示实际温度
	int16_t Display_Set;//用于显示设置温度
	int16_t New;//当前的最大最小温度
	int16_t Last_Set;//记录启动时的设定温度
	uint8_t Last_Mode;//记录启动时的显示模式
	float ADD_Wait_Count;//缓慢升温时间
}_Temp_;
extern _Temp_ Temp;//温度参数

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
    uint8_t Show_Circle;//显示外框和P-几模式
    uint8_t Option;//P模式数组选项
}_PMode_;
extern _PMode_ PMode;//P模式参数

#endif
