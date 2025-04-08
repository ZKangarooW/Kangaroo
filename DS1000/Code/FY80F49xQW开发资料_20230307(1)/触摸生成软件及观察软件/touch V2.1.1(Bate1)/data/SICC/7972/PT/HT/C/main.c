/***********************************************************************
方案说明：
***********************************************************************/
/**********************************************************************/
/*修改说明*/
/*
20210707：触摸休眠程序Sleep_Set，当出现触摸检测异常时做限时恢复处理
，例如手指直接触摸按键导致触摸基准值更新到过大过小异常数据
*/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/*头文件*/
#include <cms.h>
#include "main.h"
#include "delay.h"
#include "mytype.h"
#include "Touch_Kscan_Library.h"
#include "REL_Sender.h"
/**********************************************************************/
/*全局变量声明*/
/**********************************************************************/
static volatile unsigned char LPKEYCON @ 0x189;//唤醒标志寄存器


volatile unsigned int SleepTimec;
volatile unsigned char tcount;
/**********************************************************************/
/**********************************************************************/
/***********************************************************************
子函数功能：上电初始化系统寄存器
入口参数：
返回数据：
备注：
***********************************************************************/
void Init_ic (void)
{
	asm("clrwdt");
	OPTION_REG = 0;
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	INTCON = 0x00;
	PIR1 = 0;
	PIR2 = 0;
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0x00;
	OSCCON = 0x71;
	PIE1 = 0;
	PIE2 = 0;
	IOCB = 0;
	WPUA = 0;
	WPUB = 0;
	WPUC = 0;
}

/***********************************************************************
函数功能：初始上电RAM赋值
入口参数：
返回数据：
备注：
***********************************************************************/
void Init_ram (void)
{
	asm("clrwdt");
	PIE2 = 0;
	PIE1 = 0B00000010;
	PR2 = 250;				//8M下将TMR2设置为125us中断
	T2CON = 4;				//使能定时器2
	INTCON = 0XC0;			//使能中断
}

/***********************************************************************
函数功能：系统寄存器刷新
入口参数：
返回数据：
备注：
***********************************************************************/
void Sys_set (void)
{
	asm("clrwdt");
	OPTION_REG = 0;
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0x00;
	PIE1 = 0B00000010;
	PR2 = 250;
	INTCON = 0XC0;
	if(4 != T2CON)
		T2CON = 4;
}

/***********************************************************************
函数功能：休眠系统寄存器刷新
入口参数：
返回数据：
备注：
***********************************************************************/
void Sys_set_SL (void)
{
	PIR1 = 0;
	PIR2 = 0;
	PIE1 = 0B00000000;
	PIE2 = 0B01000000;
	asm("nop");
	INTCON = 0x40;
	INTCON = 0x40;
	asm("clrwdt");
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0B00000000;
	OPTION_REG |= 0X07;
	TMR0 = 0;
	OPTION_REG |= 0X08;
	asm("clrwdt");
	OPTION_REG = 0B00001010;
	asm("clrwdt");
	OSCCON = 0x71;
}

/***********************************************************************
函数功能：Sleep_On
***********************************************************************/
void Sleep_On(void)
{
	PORTA = 0x00;
	PORTB = 0;
	PORTC = 0;
	PIR1 = 0;
	PIR2 = 0;
	PIE1 = 0B00000000;
	PIE2 = 0B00000000;
	INTCON = 0x00;
	INTCON = 0x00;
	INTCON = 0x00;
	asm("clrwdt");
	OPTION_REG |= 0X07;
	TMR0 = 0;
	OPTION_REG |= 0X08;
	asm("clrwdt");
	OPTION_REG = 0B00001010;
	asm("clrwdt");
	OSCCON = 0x71;
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0x00;
	asm("clrwdt");
	asm("sleep");
	asm("nop");
	asm("nop");
	asm("clrwdt");
}

/***********************************************************************
函数功能：Sleep_Set
***********************************************************************/
void Sleep_Set(void)
{
	unsigned char KeySLFst = 0;
	static unsigned int timelmt = 0;
	/******************************************************************/
	if(++SleepTimec >= 500)
	{
		SleepTimec = 0;
		_CMS_SleepTimeOnf = 1;//设置休眠模式扫键
		while(1)
		{
			if(KeySLFst == 0)
			{
				Sys_set();
				Delay(100);
				__CMS_CheckTouchKey();	//扫描按键
				if(_CMS_KeyOnceOver)//第一次需要将之前的按键扫描完一轮，防止有些寄存器参数未刷新
				{
					_CMS_KeyOnceOver = 0;
					KeySLFst = 1;
				}
			}
			else
			{
				Sys_set_SL();
				__CMS_CheckTouchKey_SL();	//扫描按键
				if(_CMS_KeyOnceOver)
				{
					_CMS_KeyOnceOver = 0;
					timelmt = 0;
					if(!_CMS_KeyOnceHave)
					{
						//RA4 = 0;
						Sleep_On();
						if(LPKEYCON & 0x20)
						{
							_CMS_SleepTimeOnf= 0;
							Sys_set();
							break;
						}
						//RA4 = 1;
					}
					else
					{
						_CMS_KeyOnceHave = 0;
						_CMS_SleepTimeOnf= 0;
						Sys_set();
						break;
					}
				}
				else if(++timelmt >= 150)//当出现触摸检测异常时，做限时恢复处理，根据实际情况可做调整
				{
					timelmt = 0;
					KeySLFst = 0;
				}
			}
		}
	}
}

/***********************************************************
键处理函数
***********************************************************/
void Kscan()
{
	static unsigned int KeyFlagPT,KeyFlagPT_Old;
	static unsigned char KeyFlagYP,position_old;
	
	KeyFlagYP = _CMS_KeyFlag[0] & 0x0f;
	KeyFlagPT = (unsigned int)(_CMS_KeyFlag[0] >> 4);
	KeyFlagPT |= (unsigned int)(_CMS_KeyFlag[1] << 4);

	if(KeyFlagPT)//普通按键处理
	{
		SleepTimec = 0;
		KeyFlagPT_Old ^= KeyFlagPT;
		if(KeyFlagPT_Old)
		{
			if(0x01 & KeyFlagPT_Old) {}
			else if(0x02 & KeyFlagPT_Old) {}
			else if(0x04 & KeyFlagPT_Old) {}
			else if(0x08 & KeyFlagPT_Old) {}
			else if(0x10 & KeyFlagPT_Old) {}
			else if(0x20 & KeyFlagPT_Old) {}
			else if(0x40 & KeyFlagPT_Old) {}
			else if(0x80 & KeyFlagPT_Old) {}
		}
		KeyFlagPT_Old = KeyFlagPT;
	}
	else
		KeyFlagPT_Old = 0;
	
	if(KeyFlagYP)//圆盘/滑条位置处理
	{
		SleepTimec = 0;
		
		if(position_old != _CMS_position)
		{
			position_old = _CMS_position;
		}
	}
	else
		position_old = 0;
}

/***********************************************************************
函数功能：中断入口函数
***********************************************************************/
void interrupt time0(void)
{
	if(TMR2IF)
	{
		TMR2IF = 0;
		tcount ++;
		__CMS_GetTouchKeyValue();
	}
}

/***********************************************************************
main主函数
***********************************************************************/
void main(void)
{
	/******************************************************************/
	Init_ic();
	Delay_nms(200);
	Init_ram();//上电给初值
	while(1)
	{
		OSCCON = 0x71;
		if(tcount >= 32)
		{
			tcount = 0;//主程序循环4ms
			Sys_set();
			Kscan();
			#if (REL_SENDER_ENABLE == 1)//调试宏定义是否为1
				REL_SenderLoop();//发码子程序
			#endif
			__CMS_CheckTouchKey();	//扫描按键
			//Sleep_Set();
		}
	}
}
/**********************************************************************/



