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
/*Bit7 bit6 bit5 bit4 bit3 bit2 bit1 bit0*/
/* a    b    c     d    e   f    g    dp  共阴*/
/* 7 	6	 5	   4    3   2    1    0   SEG*/

#define  SEG_A		0x1
#define  SEG_B		0x2
#define  SEG_C		0x4
#define  SEG_D		0x8
#define  SEG_E		0x10
#define  SEG_F		0x20
#define  SEG_G		0x40
#define  SEG_DP		0x80

#define  ALL_OFF	(0x00)
#define  ALL_ON		(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G|SEG_DP)

#define  FOUNT_0	 (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E)
#define  FOUNT_1	 (SEG_B|SEG_C)
#define  FOUNT_2	 (SEG_A|SEG_B|SEG_D|SEG_E|SEG_G)
#define  FOUNT_3	 (SEG_A|SEG_B|SEG_C|SEG_D|SEG_G)
#define  FOUNT_4	 (SEG_B|SEG_C|SEG_F|SEG_G)
#define  FOUNT_5	 (SEG_A|SEG_C|SEG_D|SEG_F|SEG_G)
#define  FOUNT_6	 (SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define  FOUNT_7	 (SEG_A|SEG_B|SEG_C)
#define  FOUNT_8	 (SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define  FOUNT_9	 (SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G)
#define  FOUNT_a	 (SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G)
#define  FOUNT_b	 (SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define  FOUNT_c	 (SEG_D|SEG_E|SEG_G)
#define  FOUNT_d	 (SEG_B|SEG_C|SEG_D|SEG_E|SEG_G)
#define  FOUNT_e	 (SEG_A|SEG_D|SEG_E|SEG_F|SEG_G)
#define  FOUNT_f	 (SEG_A|SEG_E|SEG_F|SEG_G)

const uint8_t FontTable[18] ={
	FOUNT_0,FOUNT_1,FOUNT_2,FOUNT_3,FOUNT_4,FOUNT_5,
	FOUNT_6,FOUNT_7,FOUNT_8,FOUNT_9,FOUNT_a,FOUNT_b,
	FOUNT_c,FOUNT_d,FOUNT_e,FOUNT_f};



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
	LED_EnableMatrixMode();				//开启矩阵模式
	LED_ConfigMatrixMode(LED_CLK_FSYS,LED_DUTY_5,LED_COM_CATHODE);		
	
	/*设置扫描周期为 100HZ   
	 -> T = 4 * (COM有效时间 + 2*Tled)
	 -> T = 4 * ((ComTime +1) + 2)*Tled
	*/
	LED_ConfigMatrixClkDiv(11999);			//Fsys=48Mhz，LED = 4Khz; ->250us
	LED_ConfigMatrixComTime(7);		    	//ComTime => 2ms
	
	/*
	(2)设置COM口
	*/
	GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_GPIO);	
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_0);
    
	GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_1);	
    
	GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2);
    
	GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO);	
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3);  
    
	GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_GPIO);	
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_4);
    
	LEDCOMEN = 0x1F;		//使能COM0~COM4
		
	/*
	(3)设置SEG口
	*/	
	GPIO_SET_MUX_MODE(P11CFG, GPIO_MUX_GPIO);	//SEG0	->a
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_1);
    
	GPIO_SET_MUX_MODE(P12CFG, GPIO_MUX_GPIO);	//SEG1	->b
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_2);
    
	GPIO_SET_MUX_MODE(P13CFG, GPIO_MUX_GPIO);	//SEG2	->c	
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_3);
    
	GPIO_SET_MUX_MODE(P14CFG, GPIO_MUX_GPIO);	//SEG3	->d	
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_4);
    
	GPIO_SET_MUX_MODE(P15CFG, GPIO_MUX_GPIO);	//SEG4	->e	
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_5);
    
	GPIO_SET_MUX_MODE(P16CFG, GPIO_MUX_GPIO);	//SEG5	->f	
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_6);
    
	GPIO_SET_MUX_MODE(P10CFG, GPIO_MUX_GPIO);	//SEG6	->g	
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_0);
    
	GPIO_SET_MUX_MODE(P07CFG, GPIO_MUX_GPIO);	//SEG7	->dp	
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_7);
    
	LEDSEGEN0 = 0xF8;	//使能SEG3~SEG7	
	LEDSEGEN1 = 0x07;   //使能SEG8~SEG10	
    
	/*
	(4)设置SEG口电流
	*/		
	LEDENL = 0xF8;			//使能SEG3~SEG7的管脚驱动
	LEDENH = 0x07;			//使能SEG8~SEG10的管脚驱动
	
	LEDSDRP1L = 0x03;		//8.1mA     P00-P03
	LEDSDRP0H = 0x03;		//8.1mA     P10-P13
    LEDSDRP1H = 0x03 ;	    //8.1mA 	P14-P17
    
	/*
	(5)设置COM口电流
	*/	
	P0DR = 0x0f;			// 150mA

	/*
	(6)设置SEG口数据
	*/
	LEDC0DATA0 = ALL_OFF;			/*1*/
    LEDC0DATA1 = ALL_OFF;			/*1*/
    LEDC1DATA0 = ALL_ON;			/*2*/
    LEDC1DATA1 = ALL_ON;			/*2*/
	LEDC2DATA0 = ALL_ON;			/*3*/
    LEDC2DATA1 = ALL_ON;			/*3*/
	LEDC3DATA0 = ALL_ON;			/*4*/
    LEDC3DATA1 = ALL_ON;			/*4*/
    LEDC4DATA0 = ALL_ON;            /*5*/
    LEDC4DATA1 = ALL_ON;			/*5*/
    
	/*
	(7)开启LED矩阵模式
	*/
	LED_StartMatrix();
}


















