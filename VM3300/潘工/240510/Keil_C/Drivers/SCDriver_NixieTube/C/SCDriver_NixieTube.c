//************************************************************
//  Copyright (c) 
//	文件名称	: SCDriver_NixieTube.H
//	作者		: Andy
//	模块功能	: 数码管应用驱动库C实现文件
//  最后更正日期: 2019/1/16
// 	版本		: V0.1 
//  说明        ：  
//*************************************************************
#include "..\H\SCDriver_NixieTube.h"
#include "SC_Init.h"

#define  IO_NULL 		   0xFF00//空设置
#define  SCD_IO_PORT(IO)    (uint8_t)(IO>>8)
#define  SCD_IO_PIN(IO)	    (uint8_t)(IO)

unsigned char  SCD_NT_TimeCount;		 //#数码扫描计时变量#
unsigned char  SCD_NT_CurrentCOM = 0;	 //#数码管当前的扫描通道#
//#数码管显示缓存列表#
static unsigned char  SCD_ComNum[4]={0,0,0,0};
//#数码管SEG口扫描列表#
static unsigned int code SCD_SEG_BitList[]=
{
	SCD_NT_SEGA_INIT,
	SCD_NT_SEGB_INIT,
	SCD_NT_SEGC_INIT,
	SCD_NT_SEGD_INIT,
	SCD_NT_SEGE_INIT,
	SCD_NT_SEGF_INIT,
	SCD_NT_SEGG_INIT,
	SCD_NT_SEGDP_INIT
};
//#数码管COM口扫描列表#
static unsigned int code SCD_COM_List[]=
{
	SCD_NT_COM1_INIT,SCD_NT_COM2_INIT,SCD_NT_COM3_INIT,SCD_NT_COM4_INIT
};

#if(SCD_NT_TYPE==0x00)//共阴
unsigned char code SCD_NT_NumList[]=
{
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00
};
#endif
#if(SCD_NT_TYPE==0xFF)//共阳
unsigned char code SCD_NT_NumList[]=
{
	~0x3f,~0x06,~0x5b,~0x4f,~0x66,~0x6d,~0x7d,~0x07,~0x7f,~0x6f,0xFF
};
#endif
//{
//函数名  #SCD_NT_PinMode#
//函数功能#对应的数码管驱动脚输出高#
//输入参数#
//			unsigned int IO_Pxx, 			  选择需要配置的IO口
//			GPIO_Mode_TypeDef IO_Pxx_Mode 选择IO口的工作模式
//		  #
//输出参数#void#
//}
void SCD_NT_PinMode(unsigned int IO_Pxx, GPIO_Mode_TypeDef IO_Pxx_Mode)
{
	if(IO_Pxx != IO_NULL)
	{
		GPIO_Init(SCD_IO_PORT(IO_Pxx), SCD_IO_PIN(IO_Pxx), IO_Pxx_Mode);	
	}	
}
//{
//函数名  #SCD_NT_PinWriteHigh#
//函数功能#对应的数码管驱动脚输出高#
//输入参数#unsigned int IO_Pxx  选择数码管驱动脚#
//输出参数#void#
//}
void SCD_NT_PinWriteHigh(unsigned int IO_Pxx)
{
	if(IO_Pxx != IO_NULL)
	{
	   GPIO_WriteHigh(SCD_IO_PORT(IO_Pxx), SCD_IO_PIN(IO_Pxx));
	}
}
//{
//函数名  #SCD_NT_PinWriteLow#
//函数功能#对应的数码管驱动脚输出低#
//输入参数#unsigned int IO_Pxx  选择数码管驱动脚#
//输出参数#void#
//}
void SCD_NT_PinWriteLow(unsigned int IO_Pxx)
{
	if(IO_Pxx != IO_NULL)
	{
	   GPIO_WriteLow(SCD_IO_PORT(IO_Pxx), SCD_IO_PIN(IO_Pxx));
	}
}
//{
//函数名  #SCD_NT_Init#
//函数功能#该函数用于初始化数码管所需使用的GPIO口状态#
//输入参数#void#
//输出参数#void#
//}
void SCD_NT_Init(void)	//将数码管驱动口全部设置为强推输出模式
{
	unsigned char i;
	for(i=0;i<8;i++) 
	{
		if(SCD_SEG_BitList[i]!=IO_NULL)
		{
			SCD_NT_PinMode(SCD_SEG_BitList[i], GPIO_MODE_OUT_PP); //将IO口设置为强推挽输出
		}
	}
	//*******************熄灭所有的灯***************************
	for(i=0;i<4;i++) 
	{
		if(SCD_COM_List[i]!=IO_NULL)
		{
			SCD_NT_PinMode(SCD_COM_List[i], GPIO_MODE_OUT_PP);
			#if(SCD_NT_TYPE == 0)
				SCD_NT_PinWriteHigh(SCD_COM_List[i]);
			#endif
			#if(SCD_NT_TYPE == 0xff)
				SCD_NT_PinWriteLow(SCD_COM_List[i]);
			#endif
		}
	}
	//***********************************************************
}
//{
//函数名  #SCD_NT_Analysis#
//函数功能#数码管显示内容解析函数#
//输入参数#unsigned char SegData  数码管显示内容#
//输出参数#void#
//}

void SCD_NT_Analysis(unsigned char SegData)
{
	#if(SCD_NT_SEGA_INIT != IO_NULL)
		SCD_NT_SEGA=SegData&(0x01);
	#endif
	#if(SCD_NT_SEGB_INIT!= IO_NULL)
		SCD_NT_SEGB=SegData&(0x02);
		#endif
	#if(SCD_NT_SEGC_INIT!= IO_NULL)
		SCD_NT_SEGC=SegData&(0x04);
		#endif
	#if(SCD_NT_SEGD_INIT!= IO_NULL)
		SCD_NT_SEGD=SegData&(0x08);
		#endif
	#if(SCD_NT_SEGE_INIT!= IO_NULL)
		SCD_NT_SEGE=SegData&(0x10);
		#endif
	#if(SCD_NT_SEGF_INIT!= IO_NULL)
		SCD_NT_SEGF=SegData&(0x20);
		#endif
	#if(SCD_NT_SEGG_INIT!= IO_NULL)
		SCD_NT_SEGG=SegData&(0x40);
		#endif
	#if(SCD_NT_SEGDP_INIT!= IO_NULL)
		SCD_NT_SEGDP=SegData&(0x80);
		#endif
}
//{
//函数名  #SCD_NT_Scan#
//函数功能#该函数用于显示动态扫描，需要将该函数放于定时器中断中固定时间调用#
//输入参数#void#
//输出参数#void#
//}
 
void SCD_NT_Scan(void)
{
	unsigned char i;
	static unsigned char flag = 0;
	SCD_NT_TimeCount++;
	if(flag==0)	//判断是否初始化了
	{
	   flag = 1;
	   SCD_NT_Init();
	}
	if(SCD_NT_TimeCount>=SCD_NT_TIME)
	{
		SCD_NT_TimeCount = 0;
		if(SCD_COM_List[SCD_NT_CurrentCOM]!=IO_NULL)
		{
			#if(SCD_NT_TYPE == 0)
			{
				#if(SCD_NT_COM1_INIT!=IO_NULL)
				SCD_NT_COM1=1;
				#endif
				#if(SCD_NT_COM2_INIT!=IO_NULL)
				SCD_NT_COM2=1;
				#endif
				#if(SCD_NT_COM3_INIT!=IO_NULL)
				SCD_NT_COM3=1;
				#endif
				#if(SCD_NT_COM4_INIT!=IO_NULL)
				SCD_NT_COM4=1;//消隐
				#endif
				SCD_NT_Analysis(SCD_ComNum[SCD_NT_CurrentCOM]);
				SCD_NT_PinWriteLow(SCD_COM_List[SCD_NT_CurrentCOM]);//点亮对应的COM口
			}
			#endif
			#if(SCD_NT_TYPE == 0xff)
			{
				#if(SCD_NT_COM1_INIT!=IO_NULL)
				SCD_NT_COM1=0;
				#endif
				#if(SCD_NT_COM2_INIT!=IO_NULL)
				SCD_NT_COM2=0;
				#endif
				#if(SCD_NT_COM3_INIT!=IO_NULL)
				SCD_NT_COM3=0;
				#endif
				#if(SCD_NT_COM4_INIT!=IO_NULL)
				SCD_NT_COM4=0;//消隐
				#endif
				SCD_NT_Analysis(SCD_ComNum[SCD_NT_CurrentCOM]);
				SCD_NT_PinWriteHigh(SCD_COM_List[SCD_NT_CurrentCOM]);//点亮对应的COM口
			}
			#endif
		}
	
		i = 0;
		do
		{
			i++;
			SCD_NT_CurrentCOM++;//为下一次进入动态显示扫描做准备
			if(SCD_NT_CurrentCOM>=4)
			{
			   SCD_NT_CurrentCOM = 0;
			}
		}
		while((SCD_COM_List[SCD_NT_CurrentCOM]==IO_NULL)&&(i<=4));
		if(SCD_NT_CurrentCOM>=4)
		{
			SCD_NT_CurrentCOM = 0;
		}
	}
}
//{
//函数名  #SCD_NT_Display#
//函数功能#该函数用于显示更新，更新对应#
//输入参数#
//		   unsigned char Com1    Com1口显示的内容
//		   unsigned char Com2	   Com2口显示的内容
//		   unsigned char Com3	   Com3口显示的内容
//		   unsigned char Com4	   Com4口显示的内容
//		  #
//输出参数#void#
//}
void SCD_NT_Display(unsigned char Com1,unsigned char Com2,unsigned char Com3,unsigned char Com4)
{
	SCD_ComNum[0] = SCD_NT_NumList[Com1];
	SCD_ComNum[1] = SCD_NT_NumList[Com2];
	SCD_ComNum[2] = SCD_NT_NumList[Com3];
	SCD_ComNum[3] = SCD_NT_NumList[Com4];
}