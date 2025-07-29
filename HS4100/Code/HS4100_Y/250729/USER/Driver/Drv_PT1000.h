#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********宏定义************/
#define N 100//采集100次
#define OP_Value	6.8//放大系数
#define Vref_3V3	3.30f//3.3V电压
#define K1			0.2327367//电阻基准系数
#define Vref		2.497//参考电压
#define R_3K        3.0f//分压电阻3k
#define R_910R      0.91f//分压电阻910Ω

#define AD_LEN      2//DMA获取长度

/**********全局变量**********/
extern float PT_VALUE_1_TEMP;//外部探头阻值
extern float PT_VALUE_2_TEMP;//台面探头阻值

/**********全局函数**********/
void ADCDMA_Init(void);//ADC和DMA的初始化
void Read_Temp(float dT);//读取温度-10ms
float CelsiusToFahrenheit(uint8_t type,int16_t celsius);//摄氏度转华氏度

#endif
