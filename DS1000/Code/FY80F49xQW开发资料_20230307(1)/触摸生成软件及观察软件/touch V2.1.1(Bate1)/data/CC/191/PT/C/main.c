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
	SYS_GEN = 0;				//禁止中断,禁止AD
	OPTION_REG = 0;
	
	P0CL = 0B10101010;			//初始化IO口功能
	P0CH = 0B10101010;
	
	P1CL = 0B10101010;
	P1CH = 0B10010010;
	
	P2C = 0B10010010;
	
	P0 = 0B00000000;			//初始化输出
	P1 = 0B00000000;
	P2 = 0B00000000;
		

	//TMR2定时中断125us
	T2DATA = 250;				//设置TMR2溢出时间
	T2CON = 0x30;				//设置TMR2时钟
	
	INT_FLAG = 0;				//清零TMR2中断请求标志
	INT_EN = 0x04;				//使能TMR2中断
	
	SYS_GEN = 0x01;				//总中断使能
	T2_CLR = 1;					//TMR2计时器开始工作
			
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
	P0CL = 0B10011010;			//刷新IO口功能
	P0CH = 0B00000001;
	
	P1CL = 0B10101010;
	P1CH = 0B10010010;
	
	P2C = 0B10010010;


	OPTION_REG = 0;
								//刷新中断相关控制寄存器
	T2DATA = 250;				
	INT_EN = 0x04;				
	SYS_GEN = 0x01;				
	if(0x31 != T2CON)
		T2CON = 0x31;
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
		if(i != KeyOldFlag)
		{
			KeyOldFlag = i;
			switch(i)
			{
				case 1:
				case 2:
				case 4:
				case 8:
				default:break;
			}
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
	if(F_T2)				//若只使能了一个中断源,可以略去判断
	{
		F_T2 = 0;
		if(++MainTime >= 32)
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