#include "Buzzer.h"
#include "cms80f731xx.h"
#include "Gpio.h"

unsigned int xdata BeepCnt;
unsigned long xdata BeepTime;
unsigned char xdata BeepTimes;
void Buzzer_Config(void)
{
		GPIO_SET_MUX_MODE(P23CFG, GPIO_MUX_GPIO);
		GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3);
}

void BuzzerBeep(void)
{
	if(BeepTimes >= 1)
	{
		BeepCnt++;
		
		if(BeepCnt < BeepTime)
		{
			P23 ^= 1;
		}
		else if(BeepCnt < BeepTime + 400)
		{
			P23 = 0;
		}
		else
		{
			BeepCnt=0;
			BeepTimes--;
		}
	}
}

void BeepSet(unsigned int SetBeepTime,unsigned char SetBeepTimes)
{
	BeepTime = (unsigned long)(SetBeepTime)<<3;
	BeepTimes += SetBeepTimes;
}


