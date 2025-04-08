#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********全局变量**********/
extern uint8_t NTC_Res;//读取温度所获得的状态

/**********全局函数**********/
int Filter_ADC(void);//滑动平均值
void Read_Temp(void);//读取温度-10ms
uint16_t Get_Ntc_Temp(uint16_t value_adc);//计算出Ntc的温度

#endif
