#ifndef _BUZZER_H_
#define _BUZZER_H_

extern unsigned long xdata BeepTime;
extern unsigned char xdata BeepTimes;


extern void Buzzer_Config(void);
extern void BuzzerBeep(void);
extern void BeepSet(unsigned int SetBeepTime,unsigned char SetBeepTimes);


#endif