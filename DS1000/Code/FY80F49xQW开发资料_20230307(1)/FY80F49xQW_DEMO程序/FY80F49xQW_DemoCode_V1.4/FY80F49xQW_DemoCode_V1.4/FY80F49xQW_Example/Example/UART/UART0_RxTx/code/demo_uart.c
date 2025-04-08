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
/** \file demo_uart.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "demo_uart.h"

/****************************************************************************/
/*	Local pre-processor symbols('#define')
****************************************************************************/


/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
****************************************************************************/

uint32_t Systemclock = 24000000;

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
 ** \brief	 UART0_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void UART0_Config(void)
{

	 uint16_t  BRTValue = 0;
	 uint32_t  BaudRateVlue = 9600;
	 
	 /*
	 (1)����UARTx������ģʽ
	 */
	 UART_ConfigRunMode(UART0,UART_MOD_ASY_8BIT, UART_BAUD_BRT);
	 UART_EnableReceive(UART0);
	 /*
	 (2)����UARTx�Ĳ�����
	 */
	 UART_ConfigBRTClk(BRT_CLK_DIV_1);	
	
	 UART_EnableDoubleFrequency(UART0); 							/*������ʹ�ܱ�Ƶ��SMOD =1*/
	
  #ifdef USE_FORMULA			//ʹ�ù�ʽ���㶨ʱ���ļ���ֵ(��Ҫ��Systemclock��ֵ(main.c))��USE_FORMULA �� ѡ��Option->C51->Preporcessor Symbols->Define�ж���
	 BRTValue = UART_ConfigBaudRate(UART0, BaudRateVlue) ;
  #else 
	 BRTValue = 65380; 				//ʹ���ֲ����Ƽ��ļ���ֵ(BRT�½�),��Ӧ��ϵͳʱ�ӣ�24MHz
  #endif
 
	 UART_ConfigBRTPeriod(BRTValue);							/*������װֵ*/
	 UART_EnableBRT();										/*ʹ�ܶ�ʱ��*/
	 /*
	 (3)����IO��
	 */ 
	 GPIO_SET_MUX_MODE(P04CFG,GPIO_P04_MUX_TXD0);			/*TXD0*/
	 GPIO_SET_MUX_MODE(P05CFG,GPIO_P05_MUX_RXD0);	 		/*RXD0*/
	 GPIO_SET_PS_MODE(PS_RXD0, GPIO_P05);					/*RXD0����ѡ��P05*/
	 /*
	 (4)����UART�ж�
	 */
	 UART_EnableInt(UART0);
	 IRQ_SET_PRIORITY(IRQ_UART0,IRQ_PRIORITY_LOW);

}



/******************************************************************************
 ** \brief	 putchar
 ** \param [in] data
 **            	
 ** \return  none
 ** \note   <stdio.h>����Ҫ�ĺ���
 ******************************************************************************/
char putchar (char ch)
{
	SBUF0 = ch;
	while( !(SCON0 & (1<<1)));
	SCON0 &=~(1<<1);		
	return 0;
}

/******************************************************************************
 ** \brief	 putchar
 ** \param [in] none
 **            	
 ** \return  data
 ** \note   <stdio.h>����Ҫ�ĺ���
 ******************************************************************************/
char getchar (void)
{
	while(!(SCON0 & (1<<0)));
	SCON0 &=~(1<<0);
	return  SBUF0;	
}
/********************************************************************************
 ** \brief	 puts 
 **
 ** \param [in]  bytes addr for sending
 **
 ** \return  <stdio.h>����Ҫ�ĺ���
 ******************************************************************************/
int  puts( const char  * s)
{
	while(*(s ++))
		putchar(*s);
	return 0;
}






