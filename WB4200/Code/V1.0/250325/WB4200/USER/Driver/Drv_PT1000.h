#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********宏定义************/
#define ALPHA 0.1f  // 平滑因子，调整响应速度
#define V_IN 3.3f  // 电源电压
#define OP_Value	6.2//放大系数
#define Vref		2.494//参考电压
#define K1			0.2327367//电阻基准系数
#define AD_LEN 2//DMA获取长度

/**********全局变量**********/
extern float PT_VALUE_1_TEMP;//外部探头阻值
extern float PT_VALUE_2_TEMP;//台面探头阻值

/**********全局函数**********/
void ADCDMA_Init(void);//ADC和DMA的初始化
void Read_Temp(float dT);//读取温度-10ms
float CelsiusToFahrenheit(uint8_t type,int16_t celsius) ;

#endif
