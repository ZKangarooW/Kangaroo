#include <cms.h>
#include "Touch_Kscan_Library.h"
#include "REL_Sender.h"

volatile unsigned char MainTime;
volatile bit	B_MainLoop;

//系统初始化
void Init_System()
{
	asm("nop");
	asm("clrwdt");
	
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	INTCON = 0x00;
	PIR1 = 0;
	PIR2 = 0;
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	
	OPTION_REG = 0;
	OSCCON = 0x72;
	PIE1 = 0;
	PIE2 = 0;
	//IOCA = 0;
	//IOCB = 0;
	WPUA = 0;
	WPUB = 0;
	WPUC = 0;
	
	PIE2 = 0;
	PIE1 = 0B00000010;
	PR2 = 125;				//16M下将TMR2设置为125us中断
	T2CON = 5;				//使能定时器2
	INTCON = 0XC0;			//使能中断
}


/**********************************************************
函数名称：Refurbish_Sfr
函数功能：刷新一些特殊功能寄存器
入口参数：无
出口参数：无 
备    注：每隔一定时间刷新一次SFR可增强抗干扰能力
**********************************************************/
void Refurbish_Sfr()
{
	asm("clrwdt");
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	OPTION_REG = 0;
	OSCCON = 0x72;
	PIE1 = 0B00000010;
	PR2 = 125;
	INTCON = 0XC0;
	if(5 != T2CON)
		T2CON = 5;
}


/***********************************************************
键处理函数
***********************************************************/
void Kscan()
{
	static unsigned int KeyOldFlag = 0;
	unsigned int i = (unsigned int)((_CMS_KeyFlag[1]<<8) | _CMS_KeyFlag[0]);
	if(i)
	{
		if(i != KeyOldFlag)
		{
			KeyOldFlag = i;
		}
	}
	else
	{
		KeyOldFlag = 0;
	}
}

/***********************************************************
中断服务函数
***********************************************************/
void interrupt Isr_Timer()
{
	if(TMR2IF)				//若只使能了一个中断源,可以略去判断
	{
		TMR2IF = 0;
		if(++MainTime >= 20)
		{
			MainTime = 0;
			B_MainLoop = 1;
		}
	}
}

/***********************************************************
主循环
***********************************************************/
void main()
{
	Init_System();
	while(1)
	{
		if(B_MainLoop)
		{
			B_MainLoop = 0;
			Refurbish_Sfr();
			Kscan();
			__CMS_CheckTouchKey();
			#if (REL_SENDER_ENABLE == 1)//调试宏定义是否为1
				REL_SenderLoop();//发码子程序
			#endif
		}
	}
}