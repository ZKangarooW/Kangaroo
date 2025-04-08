#include "Drv_Infrared.h"

/**********结构体************/
_Infrared_ Infrared[2];

/**********局部变量声明*******/
uint32_t Infrared_Time = 0;//发送的时间
uint8_t Infrared_Step = 0;//发送的步骤

/**
 * @brief 定时器计数中断
 *
 */
//void Infrared_TIM_Interrupt(void)
//{
//	
//}


//一个逻辑0的传输需要 1.125ms（560us载波+560us空闲）。
static void NEC_Send_0(void)
{
	CARRIER_38KHz();//比较值为1/3载波
	Delay_10us(50);
	NO_CARRIER();//不载波
	Delay_10us(48);
}


//一个逻辑1传输需要2.25ms（560us载波+1680us空闲）
static void NEC_Send_1(void)
{
	CARRIER_38KHz();//比较值为1/3载波
	Delay_10us(50);
	NO_CARRIER();//不载波
	Delay_10us(138);

}

//NEC协议格式：//引导码：发送一个9ms载波的引导码，之后是4.5ms的空闲，
static void NEC_Send_Head(void)
{
	CARRIER_38KHz();
	Delay_10us(750);//实际10.56ms    10us实际13us
	NO_CARRIER();//不载波]0
	Delay_10us(380);//实际接收时间在5.24ms
}

//结束码(自己加的)
static void NEC_Send_Tail(void)
{
 
	CARRIER_38KHz();
	Delay_10us(20);
	NO_CARRIER();
	Delay_10us(30);    //   2.5<3ms<3.3ms
}

//发送一字节数据
static void NEC_Send_BYTE(uint8_t value)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		if (value & 0x80)
		{
			NEC_Send_1();
		}
		else
		{
			NEC_Send_0();
		}
		value <<= 1;
	}
}

static void NEC_Send_Repeat(uint8_t count)
{
	uint8_t i = 0;
 
	if (count == 0)          //如果没有重复码就直接设置无载波，发射管进行空闲状态
	{
		NEC_Send_Tail();
	}
	else
	{
		for (i; i < count; i++)
		{
			CARRIER_38KHz();
			Delay_10us(750);
			NO_CARRIER();
			Delay_10us(200);
		}
 
	}
 
 
}
//后发送16位地址码（18ms36ms）、8位数据码（9ms18ms）以及8为数据反码。
//（第二个108ms）如果接下来发射重复的数据，可以先发送9ms载波，空闲2.5ms,
//再发射0.56ms载波即可，注意每次发射的间隔时间。
void NEC_Send(uint8_t addr, uint8_t value, uint8_t cnt)
{
	NEC_Send_Head();                //发送起始码
	NEC_Send_BYTE(addr);            //发送地址码H
	NEC_Send_BYTE(~addr);           //发送地址码L
	NEC_Send_BYTE(value);           //发送命令码H
	NEC_Send_BYTE(~value);          //发送命令码L
	NEC_Send_Repeat(cnt);           //发送重复码
}
