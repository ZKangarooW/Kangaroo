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
	uint16_t i;
	
	/*ϵͳʱ�Ӽܹ��ɲο��ֲ�4.1�½�"ϵͳʱ�ӽṹ"*/
	/*(1)ͨ��ѡ��Options->Debug->Seting������ʱ��Foscʱ��
	    Fosc ��ѡ��:
		(1) HSI(48Mhz)(��ѡ��Ƶ��1��2��3��6)
		(2) HSE(���پ���:8Mhz��16Mhz)
		(3) LSE(���پ���:32.768Khz)	
		(4) LSI(125Khz)	
	*/
	// Fosc = HSI/2 = 24Mhz;
	
	/*(2)ͨ��ѡ��Options->Debug->Seting������ʱ��Fsys_preʱ��
	   Fsys_pre = Fosc/SYS_PRESCALE(ϵͳʱ��Ԥ��Ƶ: 1��2��4��8)*/
	
	// Fsys_pre = Fosc/1 = 24Mhz;
	
	/*(3)ͨ���Ĵ���CLKDIV����Fsys(ϵͳʱ��): Fsys = Fsys_pre/��Ƶ*/
		
	SYS_SET_SYSTEM_CLK(SYS_CLK_DIV_1);
	Systemclock = 24000000;	
	
	/*(4)����CLO��ϵͳʱ��64��Ƶ��������ϵͳʱ��*/
	GPIO_SET_MUX_MODE(P17CFG, GPIO_P17_MUX_CLO);	//���ϵͳʱ�� 64��Ƶ
	
	
	GPIO_SET_MUX_MODE(P10CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_0);
	P10 =0;	
		
	while(1)
	{		
		for(i=3000;i>0;i--);
		P10 = ~P10;	
	}		
}






















