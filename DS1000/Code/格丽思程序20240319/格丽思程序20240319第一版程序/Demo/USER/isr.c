/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/****************************************************************************/
/** \file isr.c
**
** 
**
**	History:
**		
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "cms80f731xx.h"
#include "main.h"

#include "Buzzer.h"
#include "Gpio.h"
#include "Led.h"
#include "time.h"
#include "Key.h"
#include "adc.h"
#include "Heater.h"
/****************************************************************************/
/*	Local pre-processor symbols('#define')
****************************************************************************/


/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
****************************************************************************/
u8 g_mainTime;
/****************************************************************************/
/*	Local type definitions('typedef')
****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
****************************************************************************/


/****************************************************************************/
/*	Local function prototypes('static')
****************************************************************************/


/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
****************************************************************************/


/******************************************************************************
 ** \brief	 Timer 0 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/
//#define	TMR0_VECTOR	1
 
void Timer0_IRQHandler(void)  interrupt TMR0_VECTOR 
{
	TH0 = 0xfe;//125uS定时器
	TL0 += 0x0b;
	
	g_mainTime++;
	Cnt.TimeTo1ms = (Cnt.TimeTo1ms <U8_MAX)?Cnt.TimeTo1ms+1:U8_MAX;
	

	BuzzerBeep();
	Timer1msProcess();
	
}

/******************************************************************************
 ** \brief	 Timer 1 interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
******************************************************************************/ 
void Timer1_IRQHandler(void)  interrupt TMR1_VECTOR 
{
	TCON &= ~0x40;	//关闭定时器1
	TH1 = 0xfe;
	TL1 += 0x0b;
	
	Heater_SCR_IO = Off;
}

/**
* @fn void GPIO_P2_INT_ISR() interrupt P2EI_VECTOR 
* @brief GPIO外部中断2中断子函数
* @param 无
* @retval 无
*/
void GPIO_P2_INT_ISR() interrupt P2EI_VECTOR 
{
if(GPIO_GetIntFlag(GPIO2,GPIO_PIN_0))
	{
		GPIO_ClearIntFlag(GPIO2,GPIO_PIN_0);
		//市电50Hz， 10ms进入一次中断
		CtrlHeater_SCR();
		Timer1TriggerDelay(800/*500*/);	//SCR导通时间
	}
}

/******************************************************************************
 ** \brief	 ADC interrupt service function
 **
 ** \param [in]  none   
 **
 ** \return none
 ******************************************************************************/
void ADC_IRQHandler(void)  interrupt ADC_VECTOR 
{
	if(ADC_GetIntFlag())
	{
		ADC_ClearIntFlag();
	}	
}

