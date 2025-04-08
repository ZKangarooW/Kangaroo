#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********全局变量**********/
extern float  Calibration_Temp;

/**********全局函数**********/
void ADCDMA_Init(void);//ADC和DMA的初始化
int Filter_ADC(void);//滑动平均值
void Read_Temp(float dT);//读取温度-10ms
void Calibration(uint16_t temp,uint16_t temp1);//温度校准计算

#endif
