#ifndef __DRV_NTC_H__
#define __DRV_NTC_H__

#include "include.h"

/**********全局变量**********/
extern uint16_t ADC_Val1, ADC_Val2;

/**********全局函数**********/

void ADCDMA_Init(void);
int Filter_ADC(void);
void Read_Temp(float dT);
uint16_t Get_Ntc_Temp(uint16_t value_adc);
uint16_t Get_ADCVal(uint16_t temp);

#endif
