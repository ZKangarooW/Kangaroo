#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********宏定义************/
#define Heater_SCR_IO P20

#define On 0//开
#define Off 1//关

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF

/**********结构体************/
typedef struct 
{
	uint8_t SCROn;//是否开启功率
	uint8_t SCRCnt;//计时
	uint8_t SCROnTimeSet;//开启的时间
	uint8_t SCRFullTimeSet;//满功率时间
    uint8_t PWM;//赋值开启的时间
}Heater_t;
extern Heater_t Heater;//控功率

/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void HEAT_Init(void);//初始化加热
void GPIO_Interrupt(void);//交流电过零检测的中断任务函数
void Timer1_IRQ(void);//定时器1中断任务函数

#endif
