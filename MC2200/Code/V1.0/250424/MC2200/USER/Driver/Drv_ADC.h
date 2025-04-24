#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include "include.h"

/**********宏定义************/
#define N       100//互动滤波采集100次
#define AD_LEN 1//ADC通道数
#define V_IN 3.0f //电源电压

/**********全局变量**********/
/**********全局函数**********/
void Drv_ADC_Init(void);//ADC驱动初始化
void Get_ADC_Value(float dT);//获取ADC的值
void Check_Power(float dT);//检测电池点亮并报警
    
#endif
