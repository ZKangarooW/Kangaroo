#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/


/**********全局函数**********/

void Read_Temp(float dT);//读取温度-10ms
uint16_t Get_Ntc_Temp(uint16_t value_adc);//计算出Ntc的温度
int16_t Get_ADCVal(int16_t temp);//计算当前温度的adc值
void Temp_Init(void);//开机显示温度

#endif
