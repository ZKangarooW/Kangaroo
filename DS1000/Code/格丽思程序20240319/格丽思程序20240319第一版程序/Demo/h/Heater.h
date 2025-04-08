#ifndef _HEATER_H_
#define _HEATER_H_

#define ZeroCrossState P20
#define Heater_SCR_IO P15

typedef struct 
{
	unsigned char UseRly;
	unsigned char RlyOn;
	
	unsigned char UseSCR;
	unsigned char SCROn;
	unsigned char SCRCnt;
	unsigned char SCROnTimeSet;
	unsigned char SCRFullTimeSet;
}Heater_t;
extern Heater_t Heater;

extern void Heater_Config(void);
void CtrlHeater_SCR(void);
void CtrlHeater(void);

#endif