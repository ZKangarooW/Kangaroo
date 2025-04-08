#include "Drv_LedDisplay.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Drv_LedDisplay_Init(void)
 * ��    �ܣ� �����������ʼ��
*****************************************************************
*/
void Drv_LedDisplay_Init(void)
{
	/*
	(1)����LEDģ������ģʽ
	*/
	LED_EnableMatrixMode();				//��������ģʽ
	LED_ConfigMatrixMode(LED_CLK_FSYS,LED_DUTY_5,LED_COM_CATHODE);		
	
	/*����ɨ������Ϊ 100HZ   
	 -> T = 4 * (COM��Чʱ�� + 2*Tled)
	 -> T = 4 * ((ComTime +1) + 2)*Tled
	*/
	LED_ConfigMatrixClkDiv(11999);			//Fsys=48Mhz��LED = 4Khz; ->250us
	LED_ConfigMatrixComTime(7);		    	//ComTime => 2ms
	
	/*
	(2)����COM��
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
    
	LEDCOMEN = 0x1F;		//ʹ��COM0~COM4
		
	/*
	(3)����SEG��
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
    
	LEDSEGEN0 = 0xF8;	//ʹ��SEG3~SEG7	
	LEDSEGEN1 = 0x07;   //ʹ��SEG8~SEG10	
    
	/*
	(4)����SEG�ڵ���
	*/		
	LEDENL = 0xF8;			//ʹ��SEG3~SEG7�Ĺܽ�����
	LEDENH = 0x07;			//ʹ��SEG8~SEG10�Ĺܽ�����
	
	LEDSDRP1L = 0x03;		//8.1mA     P00-P03
	LEDSDRP0H = 0x03;		//8.1mA     P10-P13
    LEDSDRP1H = 0x03 ;	    //8.1mA 	P14-P17
    
	/*
	(5)����COM�ڵ���
	*/	
	P0DR = 0x0f;			// 150mA

	/*
	(6)����SEG������
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
	(7)����LED����ģʽ
	*/
	LED_StartMatrix();
}
