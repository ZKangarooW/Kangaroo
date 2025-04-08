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
/** \file demo_led.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "demo_led.h"

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
 ** \brief	 LED_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void LED_Config(void)
{	
	/*
	(1)设置LED模块运行模式
	*/
	LED_EnableLatticeMode();				//开启点阵模式
	LED_ConfigLatticeMode(LED_CLK_FSYS,LED_LATTICE_8X8,LED_SCAN_LOOP);
	
	/*-----------------------------------------------------------------
	若选择LSE作为时钟源：
	(1)Config中晶振口选择OSCON/OSCOUT AS LSE
	(2)LSE_EnableLSE();  开启LSE模块
	------------------------------------------------------------------*/
	/*
	(2)设置时钟
	*/
	LED_ConfigLatticeClkDiv(23);		//24MHz  -> 1Mhz
	LED_ConfigLatticePeriod1(99);		//0.1ms	
	LED0SEL = 0x00;			/*选择使用周期1*/
	LED1SEL = 0x00;	
	LED2SEL = 0x00;	
	LED3SEL = 0x00;	
	LED4SEL = 0x00;	
	LED5SEL = 0x00;	
	LED6SEL = 0x00;	
	LED7SEL = 0x00;		
	
	/*
	(3)设置IO口
	*/
	GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_GPIO);	
	GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_GPIO);	
	GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO);
	GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO);	
	GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_GPIO);	
	GPIO_SET_MUX_MODE(P05CFG, GPIO_MUX_GPIO);	
	GPIO_SET_MUX_MODE(P06CFG, GPIO_MUX_GPIO);	
	GPIO_SET_MUX_MODE(P07CFG, GPIO_MUX_GPIO);
	GPIO_SET_MUX_MODE(P10CFG, GPIO_MUX_GPIO);		

	LEDENL = 0xFF;
	LEDENH = 0x1;	
	
	/*
	(4)设置电流
	*/		
	LEDSDRP0L = 0xf;		//40.5mA
	LEDSDRP0H = 0xf;		//40.5mA	

	/*
	(5)设置数据
	*/
	LED0DATA = 0x00;
	LED1DATA = 0x00;
	LED2DATA = 0x00;
	LED3DATA = 0x00;
	LED4DATA = 0x00;	
	LED5DATA = 0x00;
	LED6DATA = 0x00;
	LED7DATA = 0x00;
	/*
	(7)开启LED点阵模式
	*/
	LED_StartLattice();
}

/******************************************************************************
 ** \brief	 LED_Display
 ** \param [in] Led : (1) 1~64 
 **					  (2) 0xff  ： ALL_LED 
 **				status: LED_ON(1) / LED_OFF(0)
 ** \return  none
 ** \note  
 ******************************************************************************/
void LED_Display(uint8_t led,uint8_t status)
{
	uint8_t ledcon, leddat;
	
	if((led<1) || ((led>64) && (led !=0xff)))
	{
		return;
	}
		
	if(led == 0xFF)		//选择全部
	{
		if(status)
		{
			LED0DATA = 0xff;
			LED1DATA = 0xff;
			LED2DATA = 0xff;
			LED3DATA = 0xff;
			LED4DATA = 0xff;	
			LED5DATA = 0xff;
			LED6DATA = 0xff;
			LED7DATA = 0xff;				
		}
		else
		{
			LED0DATA = 0x00;
			LED1DATA = 0x00;
			LED2DATA = 0x00;
			LED3DATA = 0x00;
			LED4DATA = 0x00;	
			LED5DATA = 0x00;
			LED6DATA = 0x00;
			LED7DATA = 0x00;		
		}
	}
	else
	{
		led = led -1;
		
		ledcon = led/8;
		leddat = led%8;
		
		switch(ledcon)
		{
			case 0:
				if(status)
					LED0DATA |= (1<<leddat);
				else
					LED0DATA &= ~(1<<leddat);			
			break;
				
			case 1:
				if(status)
					LED1DATA |= (1<<leddat);
				else
					LED1DATA &= ~(1<<leddat);			
			break;
			case 2:
				if(status)
					LED2DATA |= (1<<leddat);
				else
					LED2DATA &= ~(1<<leddat);			
			break;
			case 3:
				if(status)
					LED3DATA |= (1<<leddat);
				else
					LED3DATA &= ~(1<<leddat);			
			break;
			case 4:
				if(status)
					LED4DATA |= (1<<leddat);
				else
					LED4DATA &= ~(1<<leddat);			
			break;
			case 5:
				if(status)
					LED5DATA |= (1<<leddat);
				else
					LED5DATA &= ~(1<<leddat);			
			break;
			case 6:
				if(status)
					LED6DATA |= (1<<leddat);
				else
					LED6DATA &= ~(1<<leddat);			
			break;
			case 7:
				if(status)
					LED7DATA |= (1<<leddat);
				else
					LED7DATA &= ~(1<<leddat);			
			break;					
		}	
	}
}
















