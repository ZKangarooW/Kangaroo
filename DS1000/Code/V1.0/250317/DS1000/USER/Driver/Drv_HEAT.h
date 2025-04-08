#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********宏定义************/
#define Heater_SCR_IO P20

typedef struct 
{
	uint8_t SCROn;
	uint8_t SCRCnt;
	uint8_t SCROnTimeSet;
	uint8_t SCRFullTimeSet;
    uint8_t PWM;
}Heater_t;
extern Heater_t Heater;

/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void HEAT_Init(void);//初始化加热
void CtrlHeater_SCR(void);
void Timer1_IRQ(void);
void GPIO_Interrupt(void);
    
#endif
