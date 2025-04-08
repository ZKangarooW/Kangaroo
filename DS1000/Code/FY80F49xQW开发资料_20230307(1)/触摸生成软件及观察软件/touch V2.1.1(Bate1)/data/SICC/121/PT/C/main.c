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
	INTCON = 0;				//禁止中断
	OSCCON = 0X71;			//配置振荡为8M
	OPTION_REG = 0;
	
	WDTCON = 0x01;
	asm("clrwdt");
	//延时等待电源电压稳定
	//DelayXms(200);
	TRISA = 0x65;
	TRISD = 0;
	PORTA = 0;
	PORTD = 0;	
	
	PIE2 = 0;
	PIE1 = 0x02;
	PR2 = 250;				//8M下将TMR2设置为125us中断
	T2CON = 4;				//使能定时器2
	
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
	//均为数字口
//	ANSEL = 0;
//	ANSELH = 0;
	
	TRISA = 0;//x65;
	TRISB = 0xFF;
	TRISC = 0xFF;
	TRISD = 0;
	
	SSPCON = 0;
	EECON1 = 0;
	
	OPTION_REG = 0;
	WDTCON = 0x01;
	
	
	//刷新中断相关控制寄存器
	PIE2 = 0;
	PIE1 = 0x02;
	PR2 = 250;
	INTCON = 0XC0;
	if(4 != T2CON)
		T2CON = 4;
}


/***********************************************************
键处理函数
***********************************************************/
void Kscan()
{
	static unsigned int KeyOldFlag = 0;
	unsigned int i = (unsigned int)((KeyFlag[1]<<8) | KeyFlag[0]);
	if(i)
	{
		KeyOldFlag ^= i;
		if(KeyOldFlag)
		{
			if((0x1&KeyOldFlag) && (0x1&i)){}
			if((0x2&KeyOldFlag) && (0x2&i)){}
			if((0x4&KeyOldFlag) && (0x4&i)){}
			if((0x8&KeyOldFlag) && (0x8&i)){}
			if((0x10&KeyOldFlag) && (0x10&i)){}
			if((0x20&KeyOldFlag) && (0x20&i)){}
			if((0x40&KeyOldFlag) && (0x40&i)){}
			if((0x80&KeyOldFlag) && (0x80&i)){}
			if((0x100&KeyOldFlag) && (0x100&i)){}
			if((0x200&KeyOldFlag) && (0x200&i)){}
			if((0x400&KeyOldFlag) && (0x400&i)){}
			if((0x800&KeyOldFlag) && (0x800&i)){}
			
		}
		
		KeyOldFlag = i;
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
		if(++MainTime >= 32)	//25
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
			CLRWDT();
			Refurbish_Sfr();
			
			CheckTouchKey();
			#if (REL_SENDER_ENABLE == 1)//调试宏定义是否为1
				REL_SenderLoop();//发码子程序
			#endif
			
			Kscan();
		}
	}
}