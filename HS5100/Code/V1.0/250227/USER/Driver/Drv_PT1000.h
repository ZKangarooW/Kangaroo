#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********全局变量**********/
extern float PT_VALUE_1_TEMP;//外部探头阻值
extern float PT_VALUE_2_TEMP;//台面探头阻值

/**********全局函数**********/
void ADCDMA_Init(void);//ADC和DMA的初始化
void Read_Temp(float dT);//读取温度-10ms
float celsiusToFahrenheit(uint8_t type,int16_t celsius) ;

#endif
