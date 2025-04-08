#ifndef __Structs_H__
#define __Structs_H__

#include "stm32f0xx_hal.h"
#define ABS(x) ((x)>0?(x):-(x))
/**********结构体************/
typedef struct
{
	uint8_t Init_ok;//系统初始化是否完成，完成为1
	uint8_t SetMode_Option;//设置时当前设置哪个温度的选项
	uint8_t TempOption_Mun;//设置温度时当前设置的位数
	uint8_t TimeOption_Mun;//设置时间时当前设置的位数
	uint8_t Calibration;//是否进入校准
	uint8_t Calibration_Step;//校准步骤
	uint16_t Calibration_Temp1;//温度一
	uint16_t Calibration_Temp2;//温度二
}_sys_;
extern _sys_ sys;//系统初始化检测

typedef struct
{
	uint16_t Set_Temp;//设置温度
	uint16_t Ctrl_Temp;//控制温度
	int16_t Rel_Temp;//实际温度
	int16_t Display_Temp;//显示温度
	uint8_t ADDMode;//显示处理
}_Temp_;
extern _Temp_ Heat_Temp;//加热区域温度结构体
extern _Temp_ Cool_Temp;//制冷区域温度结构体

typedef struct
{
	uint16_t Count_Time;//正计时时间
	int16_t Set_Time;//倒计时设定时间
	uint16_t Ctrl_Time;//倒计时控制时间
    uint16_t Rel_Time;//倒计时实际时间
	int16_t Display_Time;//显示时间
	uint8_t TimeDisplay_Flag;//时间显示标志
	uint8_t CountDown_Start;//启动倒计时
	uint8_t Count_Start;//启动正计时
}_Time_;
extern _Time_ Time;//时间结构体

#endif
