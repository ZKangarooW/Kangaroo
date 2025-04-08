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
/** \file demo_adc.c
**
**  
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "demo_adc.h"

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
 ** \brief	 ADC_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void ADC_Config(void)
{
	//����ADC������ģʽ
	ADC_ConfigRunMode(ADC_CLK_DIV_128, ADC_RESULT_LEFT);	//����ADCʱ��Ϊϵͳʱ�ӵ�128��Ƶ��ADC���Ϊ����룬���ж�ADCʱ���в�����ο�"��΢8051оƬADCģ��Ӧ�ñʼ�"
	
	//����ADCת��ͨ��
	ADC_EnableChannel(ADC_CH_0);	
	GPIO_SET_MUX_MODE(P00CFG, GPIO_P00_MUX_AN0);	
	
	//����ADC LDO
	ADC_EnableLDO();
	ADC_ConfigADCVref(ADC_VREF_3V);		//ADC_VREF_1P2V, ADC_VREF_2V, ADC_VREF_2P4V, ADC_VREF_3V	
	
	//����ADC�ж�
	ADC_EnableInt();
	IRQ_SET_PRIORITY(IRQ_ADC,IRQ_PRIORITY_HIGH);	
	IRQ_ALL_ENABLE();
	
	//����ADC
	ADC_Start();
}




