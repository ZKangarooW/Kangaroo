#include "Drv_TM1650.h"

/*
*****************************************************************
 * 函数原型：void TM1650_Start(void)
 * 功    能：TM1650开始函数
*****************************************************************
*/
void TM1650_Start(void)
{
    TM1650_SCL_H;
    TM1650_SDA_H;
	Delay_us(10);
	TM1650_SDA_L;
	Delay_us(10);
	TM1650_SCL_L;
	Delay_us(10);
}

/*
*****************************************************************
 * 函数原型：void TM1650_Stop(void)
 * 功    能：TM1650结束函数
*****************************************************************
*/
void TM1650_Stop(void)
{
    TM1650_SDA_L;
	TM1650_SCL_H;
	Delay_us(10);
	TM1650_SDA_H;
	Delay_us(10);
}

/*
*****************************************************************
 * 函数原型：void TM1650_Write_Byte(uint8_t date)
 * 功    能：写入一个byte
 * 输    入：date：写入的数据
 * 参    数：uint8_t date
*****************************************************************
*/
void TM1650_Write_Byte(uint8_t date)
{
	uint8_t i;
	uint8_t Temp;
	Temp=date;
	TM1650_SCL_L;
    TM1650_SDA_L;
	for(i=0;i<8;i++)
	{
		TM1650_SCL_L;
		Delay_us(2);
		if(Temp&0x01)
		{	
			TM1650_SDA_H;
			Delay_us(10);
		}
		else
		{
			TM1650_SDA_L;
			Delay_us(10);
		}
		TM1650_SCL_H;
		Delay_us(1);
		Temp = Temp >> 1;
	}
    TM1650_SCL_L;
    TM1650_SDA_L;
}

/*
*****************************************************************
 * 函数原型：void TM1650_Write_Com(uint8_t date)
 * 功    能：发送命令字
 * 输    入：date：写入的命令字
 * 参    数：uint8_t date
*****************************************************************
*/
void TM1650_Write_Com(uint8_t date)
{
	TM1650_Start();
	TM1650_Write_Byte(date);
	TM1650_Stop();
}

/*
*****************************************************************
 * 函数原型：void TM1650_Write_DATA(uint8_t add,uint8_t DATA)
 * 功    能：指定地址写入数据
 * 输    入：add：地址值，DATA：写入的数据
 * 参    数：uint8_t add,uint8_t DATA
*****************************************************************
*/
void TM1650_Write_DATA(uint8_t add,uint8_t DATA)//add到15
{
	TM1650_Write_Com(0x44);
	TM1650_Start();
	TM1650_Write_Byte(0xc0|add);
	TM1650_Write_Byte(DATA);
	TM1650_Stop();
}

/*
*****************************************************************
 * 函数原型：void TM1650_Clr(void)
 * 功    能：TM1650清屏函数
*****************************************************************
*/
void TM1650_Clr(void)
{
	uint8_t i;	
	TM1650_Write_Com(0x40);//连续地址模式
	TM1650_Start();
	TM1650_Write_Byte(0xc0);
	for(i=0;i<4;i++)
		TM1650_Write_Byte(0x00);
	TM1650_Stop();
}

/*
*****************************************************************
 * 函数原型：void TM1650_All(void)
 * 功    能：TM1650全显示函数
*****************************************************************
*/
void TM1650_All(void)
{
    uint8_t i;	
	TM1650_Write_Com(0x40);//连续地址模式
	TM1650_Start();
	TM1650_Write_Byte(0xc0);
	for(i=0;i<5;i++)
		TM1650_Write_Byte(0xFF);
	TM1650_Stop();
}

/*
*****************************************************************
 * 函数原型：void TM1650_Init(void)
 * 功    能：TM1650初始化
*****************************************************************
*/
void TM1650_Init(void)
{
	TM1650_All();
	TM1650_Write_Com(0x8b);//亮度选择(默认最低) 0x88,0x89,0x8a,0x8b,0x8c,x8d,x8e,8x8f x0X(这里X代表十六进制的任意值
                                              /*1/16,2/16,4/16,10/16,11/16,12/16,13/16,14/16，关灯*/
    TM1650_Clr();
}
