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
/** \file time.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "time.h"
#include "Key.h"
#include "Temp.h"
#include "led.h"
#include "Heater.h"

//*******************************全局变量************************************

Cnt_t Cnt;
int led1sValid = 0;

/****************************************************************************/
/*	Local pre-processor symbols('#define')
****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
****************************************************************************/

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
** \brief	 TMR0_Config
** \param [in] 
**            	
** \return  none
** \note  
******************************************************************************/
void TMR0_Config(void)
{
	
	PT0 = 1;
	TMOD |= 0X01;//16bit
//	CKCON |= 0x00;//TMR_CLK_DIV_12
	TH0 = 0xfe;
	TL0 = 0x0b;
	IP |= 0x02;
	IE |= 0x82;
	TCON |= 0x10;
	
}


/******************************************************************************
** \brief	 TMR1_Config
** \param [in] 
**            	
** \return  none
** \note  
******************************************************************************/
void TMR1_Config(void)
{
	PT1 = 1;
	TMOD |= 0x10;//16bit
	CKCON |= 0x00;//TMR_CLK_DIV_12
	//	TH1 = 0xfe;	//0xFFFF-0xFE0B = 500;  1/(48MHz/12)*500= 125us
	//	TL1 = 0x0b;   
	IP |= 0x08;
	IE |= 0x88;
	//	TCON |= 0x40;
	TCON |=0x80;
}

/*****************************************************************************
函数名称：void Timer1TriggerDelay(unsigned int us)
函数功能：重新设定定时器1的定时时长
输入参数：us:所需设定的时长单位us
输出参数：
******************************************************************************/
void Timer1TriggerDelay(unsigned int us)
{
	unsigned int TimeBuf;
	TimeBuf = 0xFFFF-(us<<2);
	
	TH1 = (TimeBuf>>8)&0xFF;	//0xFFFF-0xFE0B = 500;  1/(48MHz/12)*500= 125us
	TL1 = TimeBuf&0xFF;  
	TCON |= 0x40;
}

/*
* 定时器1ms
*/
void Timer1msProcess(void)
{
		if(Cnt.TimeTo1ms< 8)
		{
			return;
		}
		Cnt.TimeTo1ms = 0;
		
		Cnt.TimeTo1s = (Cnt.TimeTo1s<U16_MAX)?Cnt.TimeTo1s+1:U16_MAX;
		Cnt.TimeTo100ms = (Cnt.TimeTo100ms<U8_MAX)?Cnt.TimeTo100ms+1:U8_MAX;
		
		Gettemp();
		CtrlHeater();
		
}


/*
* 定时器100ms
*/
void Timer100msProcess(void) //100ms?
{
		if(Cnt.TimeTo100ms < 100)
		{
			return;
		}
		
		Cnt.TimeTo100ms = 0;
		
		Cnt.TimeTo3s = (Cnt.TimeTo3s<U16_MAX)?Cnt.TimeTo3s+1:U16_MAX;
		//100ms任务
		LongPress();
		KeyProcess();
		SelfTestProcess();
	
		AD2Temp();	

		
}

/*
* 定时器1s
*/
void Timer1sProcess(void)
{
		
	if(Cnt.TimeTo1s<1000)
	{
		return;
	}
	Cnt.TimeTo1s = 0;
		
	if(State != SelfTest)
	{
		//1s更新一次当前温度
		UpdateDisplay2();
	}
	
}