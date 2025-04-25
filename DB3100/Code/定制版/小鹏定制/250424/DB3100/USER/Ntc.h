#ifndef __NTC_H__
#define __NTC_H__

#include "main.h"

/**********全局变量**********/
extern int rel_temp;//实际温度
extern int set_temp;//设定温度
extern int ctrl_temp;//设定温度
extern uint16_t val;//ADC读到的值
extern uint8_t res;//读取温度所获得的状态

/**********全局函数**********/
int filter(void);//滑动平均值
void Read_Temp(void);//读取温度-10ms
uint16_t func_get_ntc_temp(uint16_t value_adc);//计算出Ntc的温度
uint16_t Get_ADCVal(int16_t temp);//计算当前温度的adc值

#endif
