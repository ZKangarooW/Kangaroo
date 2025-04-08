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
/** \file demo_pwm.c
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "demo_pwm.h"

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


/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
****************************************************************************/

/******************************************************************************
** \brief	 PWM_Config (complementary, no dead time)
** \param [in] 
**            	
** \return  none
** \note  
******************************************************************************/
void PWM_Config(void)
{
	//设置PWM运行模式
	PWM_ConfigRunMode(PWM_WFG_COMPLEMENTARY|PWM_OC_INDEPENDENT); //互补模式+输出独立模式
	//设置PWM运行时钟	
	PWM_ConfigChannelClk(PWM0, PWM_CLK_DIV_1);		
	PWM_ConfigChannelClk(PWM2, PWM_CLK_DIV_1);
	PWM_ConfigChannelClk(PWM4, PWM_CLK_DIV_1);
	//设置PWM 周期以及占空比	
	PWM_ConfigChannelPeriod(PWM0, 0x12C0);
	PWM_ConfigChannelPeriod(PWM2, 0x12C0);
	PWM_ConfigChannelPeriod(PWM4, 0x12C0);

	PWM_ConfigChannelDuty(PWM0, 0x0960);
	PWM_ConfigChannelDuty(PWM2, 0x0960);
	PWM_ConfigChannelDuty(PWM4, 0x0960);


	//设置PWM的加载方式为自动加载
	PWM_EnableAutoLoadMode(PWM_CH_4_MSK|PWM_CH_2_MSK|PWM_CH_0_MSK);
	//设置PWM的输出极性
	PWM_DisableReverseOutput(PWM_CH_0_MSK|PWM_CH_1_MSK|PWM_CH_2_MSK|PWM_CH_3_MSK|PWM_CH_4_MSK|PWM_CH_5_MSK); //关闭反向输出
	//设置PWM输出
	PWM_EnableOutput(PWM_CH_0_MSK|PWM_CH_1_MSK|PWM_CH_2_MSK|PWM_CH_3_MSK|PWM_CH_4_MSK|PWM_CH_5_MSK);		//开启输出
	//设置PWM死区
	PWM_DisableDeadZone(PWM0);
	PWM_DisableDeadZone(PWM2);
	PWM_DisableDeadZone(PWM4);
	
	//设置PWM中断
	PWM_EnableZeroInt(PWM_CH_0_MSK);				//开启PWM零点中断
	PWM_AllIntEnable();							//开启PWM总中断
	IRQ_SET_PRIORITY(IRQ_PWM,IRQ_PRIORITY_HIGH);
	IRQ_ALL_ENABLE();								//开启总中断

	//设置PWM输出IO复用
	GPIO_SET_MUX_MODE(P00CFG, GPIO_P00_MUX_PG0);
	GPIO_SET_MUX_MODE(P01CFG, GPIO_P01_MUX_PG1);
	GPIO_SET_MUX_MODE(P02CFG, GPIO_P02_MUX_PG2);
	GPIO_SET_MUX_MODE(P03CFG, GPIO_P03_MUX_PG3);
	GPIO_SET_MUX_MODE(P04CFG, GPIO_P04_MUX_PG4);
	GPIO_SET_MUX_MODE(P05CFG, GPIO_P05_MUX_PG5);

	//开启PWM					
	PWM_Start(PWM_CH_4_MSK|PWM_CH_2_MSK|PWM_CH_0_MSK);
}


