#ifndef __DRV_PT1000_H__
#define __DRV_PT1000_H__

#include "include.h"

/**********全局变量**********/
#define AD_LEN 2                 // DMA获取长度
extern float PT_VALUE_1_TEMP;    // 外部探头阻值
extern uint16_t ADC_Val[AD_LEN]; // adc的值 0:外部探头。 1：电机电压

/**********全局函数**********/

void ADCDMA_Init(void);         // ADC和DMA的初始化
void Read_Temp(float dT);       // 读取温度-10ms
float Get_ADCVal(int16_t temp); // 查表读ADC值

#endif
