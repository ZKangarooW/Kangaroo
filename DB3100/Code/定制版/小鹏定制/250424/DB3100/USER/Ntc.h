#ifndef __NTC_H__
#define __NTC_H__

#include "main.h"

/**********ȫ�ֱ���**********/
extern int rel_temp;//ʵ���¶�
extern int set_temp;//�趨�¶�
extern int ctrl_temp;//�趨�¶�
extern uint16_t val;//ADC������ֵ
extern uint8_t res;//��ȡ�¶�����õ�״̬

/**********ȫ�ֺ���**********/
int filter(void);//����ƽ��ֵ
void Read_Temp(void);//��ȡ�¶�-10ms
uint16_t func_get_ntc_temp(uint16_t value_adc);//�����Ntc���¶�
uint16_t Get_ADCVal(int16_t temp);//���㵱ǰ�¶ȵ�adcֵ

#endif
