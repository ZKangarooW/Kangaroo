#include "Drv_GN1640.h"

/*
*****************************************************************
 * 函数原型：static void GN1640_Start(void)
 * 功    能：开始传输
 * 调    用：内部调用 
*****************************************************************
*/
static void GN1640_Start(void)
{
	GN1640_CLK_H;
	GN1640_DATA_H;
	Delay_us(10);
	GN1640_DATA_L;
	Delay_us(10);
	GN1640_CLK_L;
	Delay_us(10);
}

/*
*****************************************************************
 * 函数原型：static void GN1640_Stop(void)
 * 功    能：停止传输
 * 调    用：内部调用 
*****************************************************************
*/
static void GN1640_Stop(void)
{
	GN1640_DATA_L;
	GN1640_CLK_H;
	Delay_us(10);
	GN1640_DATA_H;
	Delay_us(10);
}

/*
*****************************************************************
 * 函数原型：static void GN1640_Write_Byte(uint8_t date)
 * 功    能：写入一个字节
 * 输    入：date：字节
 * 参    数：uint8_t date
 * 调    用：内部调用 
*****************************************************************
*/
static void GN1640_Write_Byte(uint8_t date)
{
	uint8_t i;
	uint8_t Temp;
	Temp=date;
	GN1640_CLK_L;
	GN1640_DATA_L;
	for(i=0;i<8;i++)
	{
		GN1640_CLK_L;
		Delay_us(2);
		if(Temp&0x01)
		{	
			GN1640_DATA_H;
			Delay_us(10);
		}
		else
		{
			GN1640_DATA_L;
			Delay_us(10);
		}
		GN1640_CLK_H;
		Delay_us(1);
		Temp = Temp >> 1;
	}
	GN1640_CLK_L;
	GN1640_DATA_L;
}

/*
*****************************************************************
 * 函数原型：static void Write_Com(uint8_t date)
 * 功    能：发送命令字
 * 输    入：date：命令字节
 * 参    数：uint8_t date
 * 调    用：内部调用 
*****************************************************************
*/
static void Write_Com(uint8_t date)
{
	GN1640_Start();
	GN1640_Write_Byte(date);
	GN1640_Stop();
}

/*
*****************************************************************
 * 函数原型：void GN1640_Init(void)
 * 功    能：GN1640初始化
 * 调    用：内部调用 
*****************************************************************
*/
void GN1640_Init(void)
{
	GN1640_DATA_H;
	GN1640_CLK_H;
	GN1640_Start();
	Write_Com(0x44);
	GN1640_Stop();
	GN1640_Start();
	Write_Com(0x89); //控制显示，开显示，0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f分别对应脉冲宽度为:				 		
	GN1640_Stop();	

	GN1640_ALL();//全屏函数
	HAL_Delay(900);
	GN1640_CLS();
}

/*
*****************************************************************
 * 函数原型：void GN1640_CLS(void)
 * 功    能：清屏函数
 * 调    用：内部调用 
*****************************************************************
*/
void GN1640_CLS(void)
{
	unsigned char i;	
	Write_Com(0x40);//连续地址模式
	GN1640_Start();
	GN1640_Write_Byte(0xC0);
	for(i=0;i<16;i++)
		GN1640_Write_Byte(0x00);
	GN1640_Stop();
}

/*
*****************************************************************
 * 函数原型：void GN1640_ALL(void)
 * 功    能：全屏函数
 * 调    用：内部调用 
*****************************************************************
*/
void GN1640_ALL(void)
{
	unsigned char i;	
	Write_Com(0x40);//连续地址模式
	GN1640_Start();
	GN1640_Write_Byte(0xC0);
	for(i=0;i<16;i++)
		GN1640_Write_Byte(0xFF);
	GN1640_Stop();
}


/*
*****************************************************************
 * 函数原型：void GN1640_Write_DATA(uint8_t add,uint8_t DATA)
 * 功    能：指定地址写入数据
 * 输    入：uint8_t add,uint8_t DATA
 * 参    数：add：地址，DATA：数据
 * 调    用：内部调用 
*****************************************************************
*/
void GN1640_Write_DATA(uint8_t add,uint8_t DATA)
{
	Write_Com(0x44);
	GN1640_Start();
	GN1640_Write_Byte(0xc0|add);
	GN1640_Write_Byte(DATA);
	GN1640_Stop();
}
