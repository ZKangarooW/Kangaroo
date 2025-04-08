#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
extern uint16_t ADC_Val;//adc的值

/**********全局函数**********/
int Filter_ADC(void);//滑动平均值
void Read_Temp(float dT);//读取温度-10ms
uint16_t Get_Ntc_Temp(uint16_t value_adc);//计算出Ntc的温度
void Temp_Init(void);//开机显示温度

#endif
