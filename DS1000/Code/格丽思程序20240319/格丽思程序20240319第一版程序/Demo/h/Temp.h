#ifndef _Temp_H_
#define _Temp_H_

extern unsigned int   xdata U16_AdcValueNew;

extern unsigned int code TemADC[75]; // 各温度对应的AD值

extern unsigned char  xdata NTC_Bad_Cnt;
extern unsigned char  xdata NTC_Good_Cnt;
extern unsigned char  xdata Err;


void Gettemp(void);
void AD2Temp(void);

#endif