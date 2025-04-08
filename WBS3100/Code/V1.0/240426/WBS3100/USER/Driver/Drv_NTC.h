#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********全局变量**********/
extern uint16_t ADC_Val1,ADC_Val2;

/**********全局函数**********/
void ADCDMA_Init(void);//ADC和DMA的初始化
int Filter_ADC(void);//滑动平均值
void Read_Temp(float dT);//读取温度-10ms
uint16_t Get_Ntc_Temp(uint16_t value_adc);//计算出Ntc的温度
uint16_t Get_ADCVal(uint16_t temp);//计算当前温度的adc值

#endif
