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
/** \file main.c
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
#include "demo_scm.h"

/****************************************************************************/
/*	Local pre-processor symbols('#define')
*****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
*****************************************************************************/
uint32_t  Systemclock = 24000000;

/****************************************************************************/
/*	Local type definitions('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
*****************************************************************************/

/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/


/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/

/*****************************************************************************
 ** \brief	 main
 **
 ** \param [in]  none   
 **
 ** \return 0
 *****************************************************************************/

int main(void)
{	
	uint8_t  SysClkFlag=0;
	uint16_t i;
	
	//在config选项中将晶振口选择(HSELSE_SEL)设置为HSE
	
	if(SYS_ConfigSystemClk(SYS_CLK_HSE))			//使用外部8Mhz晶振
	{		
		SysClkFlag =1;					//时钟切换成功
		SYS_SET_SYSTEM_CLK(SYS_CLK_DIV_1);
		Systemclock = 8000000;
	}
	else
	{	
		SysClkFlag =0;			//时钟切换失败
	}
		
	SCM_Config();				//开启晶振检测功能

	GPIO_SET_MUX_MODE(P10CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_0);
	P10 =0;	
	
	GPIO_SET_MUX_MODE(P12CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_2);
	P12 =0;

	
	GPIO_SET_MUX_MODE(P17CFG, GPIO_P17_MUX_CLO);	//输出系统时钟 64分频
	
	while(1)
	{		
		for(i=3000;i>0;i--);
		if(SysClkFlag)
		{
			P10 = ~P10;	
		}
		else
		{
			P10 =0;			
		}
	}		
}






















