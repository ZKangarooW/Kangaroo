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
	//����PWM����ģʽ
	PWM_ConfigRunMode(PWM_WFG_COMPLEMENTARY|PWM_OC_INDEPENDENT); //����ģʽ+�������ģʽ
	//����PWM����ʱ��	
	PWM_ConfigChannelClk(PWM0, PWM_CLK_DIV_1);		
	PWM_ConfigChannelClk(PWM2, PWM_CLK_DIV_1);
	PWM_ConfigChannelClk(PWM4, PWM_CLK_DIV_1);
	//����PWM �����Լ�ռ�ձ�	
	PWM_ConfigChannelPeriod(PWM0, 0x12C0);
	PWM_ConfigChannelPeriod(PWM2, 0x12C0);
	PWM_ConfigChannelPeriod(PWM4, 0x12C0);

	PWM_ConfigChannelDuty(PWM0, 0x0960);
	PWM_ConfigChannelDuty(PWM2, 0x0960);
	PWM_ConfigChannelDuty(PWM4, 0x0960);


	//����PWM�ļ��ط�ʽΪ�Զ�����
	PWM_EnableAutoLoadMode(PWM_CH_4_MSK|PWM_CH_2_MSK|PWM_CH_0_MSK);
	//����PWM���������
	PWM_DisableReverseOutput(PWM_CH_0_MSK|PWM_CH_1_MSK|PWM_CH_2_MSK|PWM_CH_3_MSK|PWM_CH_4_MSK|PWM_CH_5_MSK); //�رշ������
	//����PWM���
	PWM_EnableOutput(PWM_CH_0_MSK|PWM_CH_1_MSK|PWM_CH_2_MSK|PWM_CH_3_MSK|PWM_CH_4_MSK|PWM_CH_5_MSK);		//�������
	//����PWM����
	PWM_DisableDeadZone(PWM0);
	PWM_DisableDeadZone(PWM2);
	PWM_DisableDeadZone(PWM4);
	
	//����PWM�ж�
	PWM_EnableZeroInt(PWM_CH_0_MSK);				//����PWM����ж�
	PWM_AllIntEnable();							//����PWM���ж�
	IRQ_SET_PRIORITY(IRQ_PWM,IRQ_PRIORITY_HIGH);
	IRQ_ALL_ENABLE();								//�������ж�

	//����PWM���IO����
	GPIO_SET_MUX_MODE(P00CFG, GPIO_P00_MUX_PG0);
	GPIO_SET_MUX_MODE(P01CFG, GPIO_P01_MUX_PG1);
	GPIO_SET_MUX_MODE(P02CFG, GPIO_P02_MUX_PG2);
	GPIO_SET_MUX_MODE(P03CFG, GPIO_P03_MUX_PG3);
	GPIO_SET_MUX_MODE(P04CFG, GPIO_P04_MUX_PG4);
	GPIO_SET_MUX_MODE(P05CFG, GPIO_P05_MUX_PG5);

	//����PWM					
	PWM_Start(PWM_CH_4_MSK|PWM_CH_2_MSK|PWM_CH_0_MSK);
}


