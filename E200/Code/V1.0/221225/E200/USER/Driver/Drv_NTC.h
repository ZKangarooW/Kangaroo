#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********全局变量**********/
extern uint8_t NTC_Res;//读取温度所获得的状态
extern const uint16_t R100K_TAB[];
extern uint16_t ADC_Val1,ADC_Val2;
extern float  Calibration_Temp;

/**********全局函数**********/
void ADCDMA_Init(void);//ADC和DMA的初始化
int Filter_ADC(void);//滑动平均值
void Read_Temp(float dT);//读取温度-10ms
uint16_t Get_Ntc_Temp(uint16_t value_adc);//计算出Ntc的温度
uint16_t Get_ADCVal(uint16_t temp);//计算当前温度的adc值
void Calibration(uint16_t temp,uint16_t temp1);//温度校准计算

#endif
