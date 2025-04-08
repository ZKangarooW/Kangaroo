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
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "cms80f731xx.h"
#include "include.h"
/****************************************************************************/
/*	Local pre-processor symbols('#define')
*****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
*****************************************************************************/

/****************************************************************************/
/*	Local type definitions('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
*****************************************************************************/

/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/

uint32_t Systemclock = 48000000;//48MHz

/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/

/****************************************************************************
 ** \brief	 main
 **
 ** \param [in]  none   
 **
 ** \return 0
*****************************************************************************/
volatile uint8_t temp12=0;
volatile uint16_t addr=0;
volatile uint16_t Dtemp=0;
int main(void)
{	
    uint16_t i;
	temp12 =0;
	addr =0;
	Dtemp=8;	
	
    
    System_Init();
    GPIO_SET_MUX_MODE(P05CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5);
    P05 = 0;
    IRQ_ALL_DISABLE();
    FLASH_UnLock();
    
	addr=0xFF00;
	FLASH_Erase(FLASH_CODE,addr);
	for(i = 0 ;i< 256 ;i++)  //����256 bytes��д�ȴ�Flashִ�����
	{   
		FLASH_Write(FLASH_CODE,0x2FFF, 0xFF); //д��ַʹ�����ĵ�ַ(�����ַ�����ԣ�������ʹ�ý��ٵĵ�ַ)
	}
	for(addr = 0xFF00 ;addr< 0xFF10 ;addr++)
	{			
		FLASH_Write(FLASH_CODE,addr, Dtemp++);					
	}
	FLASH_Lock();	
    IRQ_ALL_ENABLE();

	IRQ_ALL_DISABLE();
	FLASH_UnLock();	
	for(addr = 0xFF00 ;addr< 0xFF10 ;addr++)
	{			
		temp12 = FLASH_Read(FLASH_CODE,addr);					
	}
	FLASH_Lock();
    IRQ_ALL_ENABLE();	
	while(1);
}





















