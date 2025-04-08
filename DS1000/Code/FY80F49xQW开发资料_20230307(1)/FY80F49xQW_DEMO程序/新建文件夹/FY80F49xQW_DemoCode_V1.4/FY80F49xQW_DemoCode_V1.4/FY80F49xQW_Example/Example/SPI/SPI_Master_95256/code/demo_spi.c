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
/** \file demo_spi.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "demo_spi.h"

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
/*****************************************************************************
 ** \brief	SPI_M95256_Start		
 ** \param [in] none
 ** \return  none
 ** \note	
*****************************************************************************/
void SPI_M95256_Start(void)
{
	SSCR &= ~(0x01);
}
/*****************************************************************************
 ** \brief	SPI_M95256_Stop
 ** \param [in] none
 ** \return  none
 ** \note	 
*****************************************************************************/
void SPI_M95256_Stop(void)
{
	SSCR |= 0x01;
}
/*****************************************************************************
 ** \brief	SPI_Transmit
 **			
** \param [in] SendData: ���͵�ֵ
 ** \return  16bit ��ȡ��ֵ
 ** \note	
*****************************************************************************/
uint8_t  SPI_Transmit(uint8_t  Data)
{	
	SPDR = Data;
	while(!SPI_GetTransferIntFlag());
	return (SPDR);				
}
/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
****************************************************************************/
/******************************************************************************
 ** \brief	 SPI_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void SPI_Config(void)
{
	/*
	(1)����SPIʱ��
	*/
	SPI_ConfigClk(SPI_CLK_DIV_64);									/*����ʱ��*/
	/*
	(2)����SPI����ģʽ
	*/
	SPI_ConfigRunMode(SPI_CLK_CPOL_LOW, SPI_CLK_CPHA_0, SPI_NSS_SSCR_CONTROL);/*����SPI ����ʱʱ��Ϊ�͵�ƽ����λѡ��CPHA = 0 */
																	/*����SPI NSSx�ź���SSCR�е����ݿ���*/																							
	/*
	(3)����IO�ڸ���
	*/
	GPIO_SET_MUX_MODE(P00CFG,GPIO_P00_MUX_SCLK);		/*SCLK*/
	GPIO_SET_MUX_MODE(P01CFG,GPIO_P01_MUX_MOSI);		/*MOSI*/
	GPIO_SET_MUX_MODE(P02CFG,GPIO_P02_MUX_MISO);		/*MISO*/
	GPIO_SET_MUX_MODE(P03CFG,GPIO_P03_MUX_NSSO0);		/*CS*/	
	GPIO_SET_PS_MODE(PS_MISO,GPIO_P02);
	GPIO_SET_PS_MODE(PS_MOSI,GPIO_P01);
	GPIO_SET_PS_MODE(PS_SCLK,GPIO_P00);
	GPIO_SET_PS_MODE(PS_NSS,GPIO_P03);
	
	/*
	(4)����SPI
	*/
	SPI_Start();
	/*
	(5)����SPI����or�ӻ�ģʽ
	*/
	SPI_EnableMasterMode();
}

/***************************************************************************
 ** \brief	 SPI_M95256_Write
 **			 
 ** \param [in]  addr: 
 **				 buf:
 ** \return 
 ** \note
***************************************************************************/
void SPI_M95256_Write(uint32_t addr, uint8_t buf)
{
	uint8_t temp;
	
	SPI_M95256_Start();
	SPI_Transmit(M95256_WREN);
	SPI_M95256_Stop();			
	for(temp=2;temp>0;temp--);	
	
	SPI_M95256_Start();
	SPI_Transmit(M95256_WRITE);	
	SPI_Transmit(addr>>8);
	SPI_Transmit(addr);		
	SPI_Transmit(buf);	
	SPI_M95256_Stop();	

	for(temp=2;temp>0;temp--);	
	SPI_M95256_Start();
	SPI_Transmit(M95256_WRDI);
	SPI_M95256_Stop();		

}
/***************************************************************************
 ** \brief	 SPI_M95256_Read_Data
 **			
** \param [in]  addr :   
 ** \return 8bit Data
 ** \note
***************************************************************************/
uint8_t SPI_M95256_Read_Data(uint32_t addr)
{
	uint8_t temp;
	SPI_M95256_Start();
	SPI_Transmit(M95256_READ);	
	SPI_Transmit(addr>>8);
	SPI_Transmit(addr);
	temp = SPI_Transmit(0x00);		
	SPI_M95256_Stop();
	return temp;
}

/***************************************************************************
 ** \brief	 SPI_M95256_Read_SFR
 **			
 ** \param [in]  cmd:	
 ** \return 8bit Data
 ** \note
***************************************************************************/
uint8_t  SPI_M95256_Read_SFR(uint8_t cmd)
{
	uint8_t temp;
	SPI_M95256_Start();
	SPI_Transmit(cmd);
	temp = SPI_Transmit(0x00);
	SPI_M95256_Stop();	
	return temp;	
}







