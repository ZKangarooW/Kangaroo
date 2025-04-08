#ifndef _TIME_H_
#define _TIME_H_
#include "cms80f731xx.h"

typedef struct
{

    unsigned char LockFree;
    unsigned int Time1s;
    unsigned char Time1h;
	
		unsigned char TimeTo1ms;
		unsigned char TimeTo10ms;
		unsigned char TimeTo100ms;
	
		unsigned int TimeTo1s;
		//unsigned char TimeTo20s;
		unsigned int TimeTo3s;	//保温加热计时
	
		unsigned char SelfCheck;
		unsigned char SelfCheckSCR;
}Cnt_t;

extern Cnt_t Cnt;

extern int led1sValid;

extern void TMR0_Config(void);
extern void TMR1_Config(void);
extern void Timer1TriggerDelay(unsigned int us);
extern void Timer1msProcess(void);
extern void Timer100msProcess(void);
extern void Timer1sProcess(void);

#endif
