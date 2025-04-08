#include "Led.h"
#include "Key.h"
#include "Gpio.h"
#include "Buzzer.h"
#include "delay.h"
#include "time.h"
#include "cms80f731xx.h"
#include "temp.h"

//����������Ϣ
//�������ʾ��ֵ,Ĭ��--��DisplayNum[0]:ͨ��һ��ʾ��ֵ DisplayNum[1]:ͨ������ʾ��ֵ DisplayNum[2]:ͨ������ʾ��ֵ DisplayNum[3]:ͨ������ʾ��ֵ
int DisplayNum[4] = {0,0,0,0}; 	
int DisplayNum1 = 0;	//�趨�¶�
int Num1Valid = 0; 		//�趨�¶��Ƿ���Ч
int DisplayNum2 = 0;	//��ǰ�¶�

	//0, 		1,		2, 		3, 		4, 		5, 		6, 		7, 		8, 		9, 		10, 	
const int shownum[2][11] = {
	{0x5, 	0x4,	0x5, 	0x5, 	0x4, 	0x1, 	0x1, 	0x5, 	0x5, 	0x5, 	0x5}, 	//DATA1 SEG8/SEG10
	{0xB4, 	0x20, 0x54, 0x70, 0xE0, 0xF0, 0xF4, 0x20, 0xF4, 0xF0, 0xBC},	//DATA0 SEG2-SEG7
};

//0:led1	1:led2	2:led3	3:led4	4:led5	5:led6	6ȫ�� 7ȫ��	
const int showled[2][8] = {
	{0x4, 	0x1,		0x0, 		0, 			0, 			0, 			0, 		0x5}, 	//DATA1 SEG8/SEG10
	{0, 		0, 			0x80, 	0x4,		0x8, 		0x10, 	0, 		0x9C},	//DATA0 SEG2-SEG7
};

	//-, 		ȫ��,		ȫ��	
const int show_special_num[2][3] = {
	{0, 		0,			0x5,}, 	//DATA1 SEG8/SEG10
	{0x40, 	0, 			0xFC},	//DATA0 SEG2-SEG7
};


/***************************************************************************
�������ƣ�int GetData1(int Data1);
�������ܣ���ȡ��ǰ��ʾ�趨ֵ
���������
���������int Data
****************************************************************************/
int GetData1(void)
{
	int data1 = 0;
	//�趨ֵ���35���������ݷ���0
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
�������ƣ�int GetData2(int Data1);
�������ܣ���ȡ��ǰ��ʾ�¶�ֵ
���������
���������int Data
****************************************************************************/
int GetData2(void)
{
	int data2 = 0;
	//�趨ֵ���35���������ݷ���0
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
�������ƣ�void SetData1(int Data1);
�������ܣ����õ�һλ���������
���������int Data1		0, 	1,	2, 	3, 	4, 	5, 	6, 	7, 	8, 	9, 	10,
���������
****************************************************************************/
void SetData1(int Data1)
{
	DisplayNum[0] = Data1 / 10;
	DisplayNum[1] = Data1 % 10;
	if((Data1/10) == 10 ) DisplayNum[1] = 10;
	
	/*COM1�ڶ�Ӧ�������ʾ��1λ*/
	LEDC3DATA1 = shownum[0][DisplayNum[0]];			
	LEDC3DATA0 = shownum[1][DisplayNum[0]];

	/*COM1�ڶ�Ӧ�������ʾ��2λ*/
	LEDC4DATA1 = shownum[0][DisplayNum[1]];			
	LEDC4DATA0 = shownum[1][DisplayNum[1]];
	
}

/***************************************************************************
�������ƣ�void SetData2(int Data2);
�������ܣ����õڶ�λ���������
���������int Data2	0, 	1,	2, 	3, 	4, 	5, 	6, 	7, 	8, 	9, 	10,
���������
****************************************************************************/
void SetData2(int Data2)
{
	DisplayNum[2] = Data2 / 10;
	DisplayNum[3] = Data2 % 10;
	if((Data2/10) == 10 ) DisplayNum[3] = 10;
	
	/*COM1�ڶ�Ӧ�������ʾ��3λ*/
	LEDC1DATA1 = shownum[0][DisplayNum[2]];
	LEDC1DATA0 = shownum[1][DisplayNum[2]];

	/*COM1�ڶ�Ӧ�������ʾ��4λ*/
	LEDC2DATA1 = shownum[0][DisplayNum[3]];			
	LEDC2DATA0 = shownum[1][DisplayNum[3]];
}

/***************************************************************************
�������ƣ�void SetSpecialData1(int Data);
�������ܣ����õ�һλ�������������
���������int Data 0:- 1:ȫ�� 2:ȫ��
���������
****************************************************************************/
void SetSpecialData1(int Data)
{
	/*COM1�ڶ�Ӧ�������ʾ��1λ*/
	LEDC3DATA1 = show_special_num[0][Data];			
	LEDC3DATA0 = show_special_num[1][Data];

	/*COM1�ڶ�Ӧ�������ʾ��2λ*/
	LEDC4DATA1 = show_special_num[0][Data];			
	LEDC4DATA0 = show_special_num[1][Data];
}

/***************************************************************************
�������ƣ�void SetSpecialData2(int Data);
�������ܣ����õڶ�λ�������������
���������int Data  0:- 1:ȫ�� 2:ȫ��
���������
****************************************************************************/
void SetSpecialData2(int Data)
{
	/*COM1�ڶ�Ӧ�������ʾ��3λ*/
	LEDC1DATA1 = show_special_num[0][Data];
	LEDC1DATA0 = show_special_num[1][Data];

	/*COM1�ڶ�Ӧ�������ʾ��4λ*/
	LEDC2DATA1 = show_special_num[0][Data];			
	LEDC2DATA0 = show_special_num[1][Data];
}


/***************************************************************************
�������ƣ�void SetLed(int Data);
�������ܣ�����LED��Ч
���������int Data 0:led1	1:led2	2:led3	3:led4	4:led5	5:led6	6ȫ�� 7ȫ��
���������
****************************************************************************/
void SetLed(int Data)
{
	/*COM0�ڶ�Ӧ��ʾLED��*/
	LEDC0DATA1 = showled[0][Data]; 
	LEDC0DATA0 = showled[1][Data];
}

	
/****************************************************************************
�������ƣ�void UpdateDisplay2(void)
�������ܣ����µ�ǰ�¶���ʾ
���������void
****************************************************************************/
void UpdateDisplay2(void)
{
	static int PreTempState = 0; //��һ����ʾ�¶�
	static int count = 0;	//��ǰ��ʾ�¶ȱ仯����3s���ϼ���
	int TempValue = 0; //�¶Ȳ�ֵ
	int display1 = 0;	//��ǰ��ʾ�趨�¶�
	
	display1 = GetData1();
		
	if((Err == 0) && (State != PowerOn) && (State != SelfTest))
	{
		led1sValid = 1;  //�ѽ���1sledˢ����ʾ
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
		
	
		if(count > 3) //����3s���ϴ��¶�ֵ��ͬ��������һ���¶�
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
		//NTC����ʱ��ʾ--
		DisplayNum[2] = 11;
		DisplayNum[3] = 11;
		SetSpecialData2(0);
		PreTempState = 0;
	}
	
}
/****************************************************************************
�������ƣ�void Led_Config(void)
�������ܣ�����ܼ�led����Ϣ����
���������void
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
	
	//*****************����ΪCOM��****************
	
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
	
	LEDSEGEN0 = 0xFC;	//ʹ��SEG2~SEG7	
	LEDSEGEN1 = 0x05; //ʹ��SEF8,SEG10
	LEDCOMEN 	= 0x1F;		//ʹ��COM0~COM4
	/*
	(4)����SEG�ڵ���
	*/		
	LEDENL = 0xFC;			//ʹ��SEG2~SEG7�Ĺܽ�����
	LEDENH = 0x05;			//ʹ��SEG8,SEG10�Ĺܽ�����
	
	LEDSDRP1L = 0x03;		//8.1mA  	P10-P13
	LEDSDRP0H = 0x03;		//8.1mA 	P04-P07
	LEDSDRP1H = 0x03 ;	//8.1mA 	P14-P17

	
	
	
}
