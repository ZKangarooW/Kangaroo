#include "Drv_IIC.h"

static GPIO_InitTypeDef GPIO_InitStruct;

/**
 * @brief SDA引脚转变为 OUT输出模式(输出模式给停止 开始信号) 
 *
 */
void IIC_SDA_Mode_OUT(void)
{
	GPIO_InitStruct.Pin = SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief SDA引脚转变为 输入模式(输入模式传输具体的数据) 
 *
 */
void IIC_SDA_Mode_IN(void)
{
	GPIO_InitStruct.Pin = SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief IIC开始信号
 *
 */
void IIC_Start(void)
{
	//设置为输出模式
	IIC_SDA_Mode_OUT();

	//空闲状态两个引脚是高电平
	SDA_OUT(1);
	SCL_OUT(1) ;
	Delay_us(5);

	//拉低数据线
	SDA_OUT(0);
	Delay_us(5);

	//再拉低时钟线
	SCL_OUT(0) ;
	Delay_us(5);
}

/**
 * @brief IIC停止信号
 * 
 */
void IIC_Stop(void)
{
	//设置为输出模式
	IIC_SDA_Mode_OUT();

	//拉低
	SDA_OUT(0);
	SCL_OUT(0);
	Delay_us(5);
	
	//时钟线先拉高
	SCL_OUT(1);
	Delay_us(5);
	
	//再把数据线拉高
	SDA_OUT(1);
	Delay_us(5);
}

/**
 * @brief 主机发送8位数据给从机MSB 高位先发
 * 
 * @param d 发送的数据
 */
void IIC_Send_Byte(uint8_t d)
{
	uint8_t i = 0;
	//设置为输出模式
	IIC_SDA_Mode_OUT();
	
	SDA_OUT(0);
	SCL_OUT(0);
	Delay_us(5);
	for(i=0;i<8;i++)
	{
		if(d & (0x1<<(7-i)))//表示数据是1
			SDA_OUT(1)
		else
			SDA_OUT(0);
		
		Delay_us(5);
		SCL_OUT(1);//拉高时钟线，告诉对方你可以读了
		
		Delay_us(5);
		SCL_OUT(0);//拉低时钟线，告诉对方你暂时别读，我在准备数据
	}
}

/**
 * @brief 等待从机给主机应答或者不应答
 * 
 * @return uint8_t 从机应答的数据
 */
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ack = 0;
	//设置为输入模式
	IIC_SDA_Mode_IN();
	
	//时钟线拉高,时钟线为高电平期间，不管是数据还是ack都是有效的
	SCL_OUT(1);
	Delay_us(5);
	
	if( SDA_IN  == 1)
		ack = 1;//无效ACK，就是无效应答
	else
		ack = 0;//有效ACK，就是有效应答
	
	SCL_OUT(0);
    
	Delay_us(5);
	return ack;
}

/**
 * @brief 读取从机发送的8位数据
 * 
 * @return uint8_t 读取到的数据
 */
uint8_t IIC_Read_Byte(void)
{
	uint8_t i =0;
	uint8_t data = 0;
	//设置为输入模式
	IIC_SDA_Mode_IN();
	//先拉低时钟线，准备数据
	SCL_OUT(0);
	Delay_us(5);
	
	for(i=0;i<8;i++)
	{
		SCL_OUT(1);//时钟线为高电平期间数据才是有效的
		Delay_us(5);
		if(SDA_IN == 1)
			data |= (0x1<<(7-i));//数据就是1
		else
			data &= ~(0x1<<(7-i));//数据就是0
		
		SCL_OUT (0);//告诉对方此时准备数据，先别读写
		Delay_us(5);
	}
	return data;
}

/**
 * @brief 主机发送应答或者不应答给从机
 * 
 * @param ack 发送的应答
 */
void IIC_Ack(uint8_t ack)
{
	//设置为输出模式
	IIC_SDA_Mode_OUT();
	
	SDA_OUT(0);
	SCL_OUT(0);
	Delay_us(5);
	
	SDA_OUT(ack) ;//发送高/低电平--->发送不应答/应答
	Delay_us(5);
	
	SCL_OUT(1);//告诉从机我已经准备好数据，你可以读取了
	Delay_us(5);
	
	SCL_OUT (0);//拉低时钟线，发送ack结束
	Delay_us(5);
}
