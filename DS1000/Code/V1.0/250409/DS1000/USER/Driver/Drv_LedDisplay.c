#include "Drv_LedDisplay.h"

/*
*****************************************************************
 * 函数原型： void Drv_LedDisplay_Init(void)
 * 功    能： 数码管驱动初始化
*****************************************************************
*/
void Drv_LedDisplay_Init(void)
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
	LEDC0DATA0 = 0x00;			/*1*/
    LEDC0DATA1 = 0x00;			/*1*/
    LEDC1DATA0 = 0x00;			/*2*/
    LEDC1DATA1 = 0x00;			/*2*/
	LEDC2DATA0 = 0x00;			/*3*/
    LEDC2DATA1 = 0x00;			/*3*/
	LEDC3DATA0 = 0x00;			/*4*/
    LEDC3DATA1 = 0x00;			/*4*/
    LEDC4DATA0 = 0x00;          /*5*/
    LEDC4DATA1 = 0x00;			/*5*/
    
	/*
	(7)开启LED矩阵模式
	*/
	LED_StartMatrix();
}
