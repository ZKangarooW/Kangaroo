//************************************************************
//  Copyright (c) 
//	文件名称	: SCDriver_IR_Decode.c
//	作者		: Andy
//	模块功能	: 红外通信解码应用驱动库源文件
//  最后更正日期: 2020/3/2
// 	版本		: V0.1 
//  说明
//*************** 红外通信解码驱动说明*********************************
//  基于NEC协议，红外接收探头（如1838B）管脚需选择有外部中断的IO
//  解码可得 客户码（16位）+数据码（8位）+数据码反码（8位）+重复码（8位）
//*********************************************************************
//*************************************************************
#include"..\H\SCDriver_IR_Decode.h"
#include"SC_Init.h"

#define  SCD_IO_PORT(IO)    (unsigned char)(IO>>8)
#define  SCD_IO_PIN(IO)	    (unsigned char)(IO)

unsigned int SCD_IR_Count = 0;	//红外基准时间计数
// SCD_IR_DecodeValue[0][1]	表示16位客户码
// SCD_IR_DecodeValue[2] 表示数据码
// SCD_IR_DecodeValue[3] 表示数据码反码
// SCD_IR_DecodeValue[4] 表示接收到的重复码的个数，当收到新的一帧数据时，该字节清0
unsigned char SCD_IR_DecodeValue[5] = {0,0,0,0,0};  //红外接收数组，当SCD_IR_OK_Flag为1时该位才有效
bit SCD_IR_Flag = 1;        //红外接收标志位，
bit SCD_IR_OK_Flag=0;		//标识接收是否完成。
unsigned char SCD_IR_GetReceiveFlag()
{
	if(SCD_IR_OK_Flag)
	{
	   SCD_IR_OK_Flag = 0;
	   return 1;
	}
	return 0;
}

//{
//函数名  #SCD_IR_Decode_Init#
//函数功能#该函数用于红外接收管脚的初始化，包括外部中断与IO模式的初始化#
//输入参数#void#
//输出参数#void#
//}
void SCD_IR_Decode_Init(void)
{
	unsigned char INTx = SCD_IO_PORT(SCD_IR_DECODE_INIT);
	unsigned char INTxy = SCD_IO_PIN(SCD_IR_DECODE_INIT);
	GPIO_Init(SCD_IO_PORT(SCD_IR_DECODE_INIT), SCD_IO_PIN(SCD_IR_DECODE_INIT), GPIO_MODE_IN_PU);
	if(INTx == INT0)
	{
		INT0_SetTriggerMode(INTxy, INT_TRIGGER_FALL_ONLY);
		INT0_ITConfig(ENABLE, LOW);
	}
	else if(INTx == INT1)
	{
		INT1_SetTriggerMode(INTxy, INT_TRIGGER_FALL_ONLY);
		INT1_ITConfig(ENABLE, LOW);
	}
	else if(INTx == INT2)
	{
		INT2_SetTriggerMode(INTxy, INT_TRIGGER_FALL_ONLY);
		INT2_ITConfig(ENABLE, LOW);
	}
	enableInterrupts(); 
}

//{
//函数名  #SCD_IR_BaseTime#
//函数功能#该函数用于红外信号计时，每隔50us调用一次，建议放在中断服务程序中#
//输入参数#void#
//输出参数#void#
//}
void SCD_IR_BaseTime(void)
{
	SCD_IR_Count++;	
}

//{
//函数名  #SCD_IR_Decode#
//函数功能#该函数用于红外数据解码，必须放在外部中断服务程序中#
//输入参数#void#
//输出参数#void#
//}
void SCD_IR_Decode(void)
{
	static unsigned char  i = 0,j = 0;            
	if(SCD_IR_Count<=600 && SCD_IR_Count>=1) //引导码，9ms+4.5ms=270个
	{
		i = 0;
		j = 0;							  	   //数组重新接收
		SCD_IR_DecodeValue[4] = 0;
		SCD_IR_Flag = 0;              		   //接收到正确的引导码,开始接收数据
		Infrared[0].Someone = 1;
		Speed.Set =SCD_IR_Count;
		SCD_IR_Count = 0;
	}
	
//	if(SCD_IR_Count<=600 && SCD_IR_Count>=400)
//	{
//		SCD_IR_DecodeValue[4]++;			   //接收到的重复码个数
//		SCD_IR_OK_Flag=1;		  		 		//接收成功标志
//	}
//	
//	
//	
//	if(SCD_IR_Flag == 1)//过滤干扰
//	{
//		SCD_IR_Count = 0;
//	}
//	else
//	{            
//		if(SCD_IR_Count<=27 && SCD_IR_Count>=18) //1.120ms,22.4
//		{
//			SCD_IR_DecodeValue[i] >>= 1;
//			SCD_IR_DecodeValue[i] &= 0x7f;
//			j++;
//		}
//		if(SCD_IR_Count<=49 && SCD_IR_Count>=41) //2.240ms,44.8
//		{
//			SCD_IR_DecodeValue[i] >>= 1;
//			SCD_IR_DecodeValue[i] |= 0x80;
//			j++;
//		}

//		SCD_IR_Count = 0;
//		if(j == 8)
//		{
//			j = 0;
//			i++;
//			if(i > 3)						  
//			{
//				i = 0;
//				SCD_IR_Flag = 1;//接收完成		
//				SCD_IR_OK_Flag=1;//接收成功标志
//			}
//		}
//	}		
}

//获得对应的接收值
//入参输入值
// 0 表示16位客户码高8位
// 1 表示16位客户码低8位
// 2 表示数据码
// 3 表示数据码反码
// 4 表示接收到的重复码的个数，当收到新的一帧数据时，该字节清0
unsigned char SCD_IR_Decode_ReadValue(unsigned char i)
{
	return SCD_IR_DecodeValue[i];
}
 


