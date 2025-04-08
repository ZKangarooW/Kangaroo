#ifndef __Drv_WS2812_H__
#define __Drv_WS2812_H__

#include "include.h"

/**********宏定义************/
#define WS2812B_H P40=1//拉高
#define WS2812B_L P40=0//拉低
#define RGB_NUM 27//灯珠数量
#define BREATH_TIME 2500//呼吸灯的时间
#define COLORFUL_TIME 3000//七彩变换的时间

/**********结构体************/
typedef struct
{
	uint8_t Red;//红色数值
	uint8_t Green;//绿色数值
	uint8_t Blue;//蓝色数值

	uint8_t Red_Out;//红色输出的数值
	uint8_t Green_Out;//绿色输出的数值
	uint8_t Blue_Out;//蓝色输出的数值

	float brightness;
} _WS2812_RGB_;
extern _WS2812_RGB_ WS2812;

typedef struct
{
	uint8_t Number;//GRB的位置
	uint8_t Mode;//显示模式
	uint8_t Update;//开始更新
} _WS2812_;
extern _WS2812_ WS2812_Status;

/**********全局变量声明*******/
/**********全局函数**********/
void WS2812_SetColor(uint8_t num, uint8_t r, uint8_t g, uint8_t b);
void WS2812_Duty(float dT);
void WS2812_Update(void);
	
#endif
