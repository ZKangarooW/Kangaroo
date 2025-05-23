/***********************************************************************
方案说明：
***********************************************************************/
/**********************************************************************/
/*修改说明*/

/**********************************************************************/
/*头文件*/
#include <cms.h>
#include "Touch_Kscan_Library.h"
#include "REL_Sender.h"
/**********************************************************************/
/*全局变量声明*/
/**********************************************************************/
volatile unsigned char tcount;
/**********************************************************************/
void Delay(unsigned int temp) 
{
	while(temp--);
}

/***********************************************************************
子函数功能：上电初始化系统寄存器
入口参数：
返回数据：
备注：
***********************************************************************/
void Init_ic (void)
{
	asm("clrwdt");
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	INTCON = 0x00;
	PIR1 = 0;
	PIR2 = 0;
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0B00000000;
	TRISD = 0x03;
	OPTION_REG = 0;
	OSCCON = 0x71;
	PIE1 = 0;
	PIE2 = 0;
	IOCB = 0;
	WPUA = 0;
	WPUB = 0;
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
	PR2 = 125;				//8M下将TMR2设置为125us中断
	T2CON = 5;				//使能定时器2
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
	WDTCON = 0x01;
	TRISA = 0B00000000;
	TRISB = 0B00000000;
	TRISC = 0B00000000;
	TRISD = 0B00000000;
	OPTION_REG = 0;
	PIE1 = 0B00000010;
	PR2 = 125;
	INTCON = 0XC0;
	if(5 != T2CON)
		T2CON = 5;
}

/***********************************************************************
//键处理函数
***********************************************************************/
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
	Delay(1000);													//上电延时
	Init_ram();														//上电给初值
	while(1)
	{
		OSCCON = 0x71;
		if(tcount >= 32)
		{
			tcount = 0;												//主程序循环4ms
			Sys_set();
			
			__CMS_CheckTouchKey();	//扫描按键
			#if (REL_SENDER_ENABLE == 1)//调试宏定义是否为1
				REL_SenderLoop();//发码子程序
			#endif
			Kscan();			//按键处理
			
		}
	}
}
/**********************************************************************/



