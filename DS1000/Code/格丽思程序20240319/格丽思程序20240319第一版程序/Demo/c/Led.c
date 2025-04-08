#include "Led.h"
#include "Key.h"
#include "Gpio.h"
#include "Buzzer.h"
#include "delay.h"
#include "time.h"
#include "cms80f731xx.h"
#include "temp.h"

//数码管相关信息
//数码管显示数值,默认--。DisplayNum[0]:通道一显示数值 DisplayNum[1]:通道二显示数值 DisplayNum[2]:通道三显示数值 DisplayNum[3]:通道四显示数值
int DisplayNum[4] = {0,0,0,0}; 	
int DisplayNum1 = 0;	//设定温度
int Num1Valid = 0; 		//设定温度是否有效
int DisplayNum2 = 0;	//当前温度

	//0, 		1,		2, 		3, 		4, 		5, 		6, 		7, 		8, 		9, 		10, 	
const int shownum[2][11] = {
	{0x5, 	0x4,	0x5, 	0x5, 	0x4, 	0x1, 	0x1, 	0x5, 	0x5, 	0x5, 	0x5}, 	//DATA1 SEG8/SEG10
	{0xB4, 	0x20, 0x54, 0x70, 0xE0, 0xF0, 0xF4, 0x20, 0xF4, 0xF0, 0xBC},	//DATA0 SEG2-SEG7
};

//0:led1	1:led2	2:led3	3:led4	4:led5	5:led6	6全关 7全开	
const int showled[2][8] = {
	{0x4, 	0x1,		0x0, 		0, 			0, 			0, 			0, 		0x5}, 	//DATA1 SEG8/SEG10
	{0, 		0, 			0x80, 	0x4,		0x8, 		0x10, 	0, 		0x9C},	//DATA0 SEG2-SEG7
};

	//-, 		全关,		全开	
const int show_special_num[2][3] = {
	{0, 		0,			0x5,}, 	//DATA1 SEG8/SEG10
	{0x40, 	0, 			0xFC},	//DATA0 SEG2-SEG7
};


/***************************************************************************
函数名称：int GetData1(int Data1);
函数功能：获取当前显示设定值
输入参数：
输出参数：int Data
****************************************************************************/
int GetData1(void)
{
	int data1 = 0;
	//设定值最低35，则无内容返回0
	if(DisplayNum[0] < 10)
	{
		data1 = DisplayNum[0]*10 + DisplayNum[1];
	}else if(DisplayNum[0] < 11){
		data1 = 100;
	}else{
		data1 = 0;
	}
		
	return data1;
}

/***************************************************************************
函数名称：int GetData2(int Data1);
函数功能：获取当前显示温度值
输入参数：
输出参数：int Data
****************************************************************************/
int GetData2(void)
{
	int data2 = 0;
	//设定值最低35，则无内容返回0
	if(DisplayNum[2] < 10)
	{
		data2 = DisplayNum[2]*10 + DisplayNum[3];
	}else if(DisplayNum[2] < 11){
		data2 = 100;
	}else{
		data2 = 0;
	}
		
	return data2;
}

/***************************************************************************
函数名称：void SetData1(int Data1);
函数功能：设置第一位数码管数据
输入参数：int Data1		0, 	1,	2, 	3, 	4, 	5, 	6, 	7, 	8, 	9, 	10,
输出参数：
****************************************************************************/
void SetData1(int Data1)
{
	DisplayNum[0] = Data1 / 10;
	DisplayNum[1] = Data1 % 10;
	if((Data1/10) == 10 ) DisplayNum[1] = 10;
	
	/*COM1口对应数码管显示第1位*/
	LEDC3DATA1 = shownum[0][DisplayNum[0]];			
	LEDC3DATA0 = shownum[1][DisplayNum[0]];

	/*COM1口对应数码管显示第2位*/
	LEDC4DATA1 = shownum[0][DisplayNum[1]];			
	LEDC4DATA0 = shownum[1][DisplayNum[1]];
	
}

/***************************************************************************
函数名称：void SetData2(int Data2);
函数功能：设置第二位数码管数据
输入参数：int Data2	0, 	1,	2, 	3, 	4, 	5, 	6, 	7, 	8, 	9, 	10,
输出参数：
****************************************************************************/
void SetData2(int Data2)
{
	DisplayNum[2] = Data2 / 10;
	DisplayNum[3] = Data2 % 10;
	if((Data2/10) == 10 ) DisplayNum[3] = 10;
	
	/*COM1口对应数码管显示第3位*/
	LEDC1DATA1 = shownum[0][DisplayNum[2]];
	LEDC1DATA0 = shownum[1][DisplayNum[2]];

	/*COM1口对应数码管显示第4位*/
	LEDC2DATA1 = shownum[0][DisplayNum[3]];			
	LEDC2DATA0 = shownum[1][DisplayNum[3]];
}

/***************************************************************************
函数名称：void SetSpecialData1(int Data);
函数功能：设置第一位数码管特殊数据
输入参数：int Data 0:- 1:全关 2:全开
输出参数：
****************************************************************************/
void SetSpecialData1(int Data)
{
	/*COM1口对应数码管显示第1位*/
	LEDC3DATA1 = show_special_num[0][Data];			
	LEDC3DATA0 = show_special_num[1][Data];

	/*COM1口对应数码管显示第2位*/
	LEDC4DATA1 = show_special_num[0][Data];			
	LEDC4DATA0 = show_special_num[1][Data];
}

/***************************************************************************
函数名称：void SetSpecialData2(int Data);
函数功能：设置第二位数码管特殊数据
输入参数：int Data  0:- 1:全关 2:全开
输出参数：
****************************************************************************/
void SetSpecialData2(int Data)
{
	/*COM1口对应数码管显示第3位*/
	LEDC1DATA1 = show_special_num[0][Data];
	LEDC1DATA0 = show_special_num[1][Data];

	/*COM1口对应数码管显示第4位*/
	LEDC2DATA1 = show_special_num[0][Data];			
	LEDC2DATA0 = show_special_num[1][Data];
}


/***************************************************************************
函数名称：void SetLed(int Data);
函数功能：设置LED灯效
输入参数：int Data 0:led1	1:led2	2:led3	3:led4	4:led5	5:led6	6全关 7全开
输出参数：
****************************************************************************/
void SetLed(int Data)
{
	/*COM0口对应显示LED灯*/
	LEDC0DATA1 = showled[0][Data]; 
	LEDC0DATA0 = showled[1][Data];
}

	
/****************************************************************************
函数名称：void UpdateDisplay2(void)
函数功能：更新当前温度显示
输入参数：void
****************************************************************************/
void UpdateDisplay2(void)
{
	static int PreTempState = 0; //上一个显示温度
	static int count = 0;	//当前显示温度变化持续3s以上计数
	int TempValue = 0; //温度差值
	int display1 = 0;	//当前显示设定温度
	
	display1 = GetData1();
		
	if((Err == 0) && (State != PowerOn) && (State != SelfTest))
	{
		led1sValid = 1;  //已进入1sled刷新显示
		if(PreTempState != DisplayNum2)
		{
			count++;
		}else{
			count = 0;
		}
		
		if(DisplayNum2 == display1)
		{
			SetData2(DisplayNum2);
		}
	
		if(count == 0)
		{
			SetData2(DisplayNum2);
			PreTempState = DisplayNum2;
		}
		else 
		{
			if(PreTempState == 0)
			{
				SetData2(DisplayNum2);
			}
			else
			{
				SetData2(PreTempState);
			}
			
		}
		
	
		if(count > 3) //连续3s和上次温度值不同，更新上一次温度
		{
			count = 0;
			TempValue = PreTempState - display1;
			if((TempValue <= 1) && (TempValue >= -1))
			{
				PreTempState = display1;
			}else{
				PreTempState = DisplayNum2;
			}
		}
			
	}else{
		//NTC故障时显示--
		DisplayNum[2] = 11;
		DisplayNum[3] = 11;
		SetSpecialData2(0);
		PreTempState = 0;
	}
	
}
/****************************************************************************
函数名称：void Led_Config(void)
函数功能：数码管及led的信息配置
输入参数：void
****************************************************************************/	
void Led_Config(void)
{
	/*
	COM1: 	P04 COM4
	COME2:	P03 COM3
	COME3:	P02 COM2
	COME4:	P01 COM1
	COME5:  P00 COM0
	B:	P16
	A:	P14
	F:	P13
	G:	P12
	C:	P11
	D:	P10
	H:	P07
	E:	P06
	*/
	
	LEDMODE = 0x55;
	
	LEDCON = 0xA0;
	
	LEDCLKL =  (uint8_t)59;
	LEDCLKH = (uint8_t)(59>>8);
	
	LEDCOMTIME = (uint8_t)7;
	
	GPIO_SET_MUX_MODE(P04CFG, GPIO_MUX_GPIO);	//COM4
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_4);
	
	GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO);	//COM3
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3);
	
	GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO);	//COM2
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2);
	
	GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_GPIO);	//COM1
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_1);
	
	GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_GPIO);	//COM0
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_0);
	
	//*****************以上为COM口****************
	
	GPIO_SET_MUX_MODE(P16CFG, GPIO_MUX_GPIO); //SEG10
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_6);
	
	GPIO_SET_MUX_MODE(P14CFG, GPIO_MUX_GPIO);	//SEG8
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_4);
	
	GPIO_SET_MUX_MODE(P13CFG, GPIO_MUX_GPIO);	//SEG7
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_3);
	
	GPIO_SET_MUX_MODE(P12CFG, GPIO_MUX_GPIO);	//SEG6
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_2);
	
	GPIO_SET_MUX_MODE(P11CFG, GPIO_MUX_GPIO);	//SEG5
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_1);
	
	GPIO_SET_MUX_MODE(P10CFG, GPIO_MUX_GPIO);	//SEG4
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_0);
	
	GPIO_SET_MUX_MODE(P07CFG, GPIO_MUX_GPIO);	//SEG3
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_7);
	
	GPIO_SET_MUX_MODE(P06CFG, GPIO_MUX_GPIO);	//SEG2
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_6);
	
	LEDSEGEN0 = 0xFC;	//使能SEG2~SEG7	
	LEDSEGEN1 = 0x05; //使能SEF8,SEG10
	LEDCOMEN 	= 0x1F;		//使能COM0~COM4
	/*
	(4)设置SEG口电流
	*/		
	LEDENL = 0xFC;			//使能SEG2~SEG7的管脚驱动
	LEDENH = 0x05;			//使能SEG8,SEG10的管脚驱动
	
	LEDSDRP1L = 0x03;		//8.1mA  	P10-P13
	LEDSDRP0H = 0x03;		//8.1mA 	P04-P07
	LEDSDRP1H = 0x03 ;	//8.1mA 	P14-P17

	
	
	
}
