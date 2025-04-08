#include "Drv_TM1650.h"

//显示参数
#define TM1650_BRIGHT1       0x11   /*一级亮度，打开LED显示*/
#define TM1650_BRIGHT2       0x21   /*二级亮度，打开LED显示*/
#define TM1650_BRIGHT3       0x31   /*三级亮度，打开LED显示*/
#define TM1650_BRIGHT4       0x41   /*四级亮度，打开LED显示*/
#define TM1650_BRIGHT5       0x51   /*五级亮度，打开LED显示*/
#define TM1650_BRIGHT6       0x61   /*六级亮度，打开LED显示*/
#define TM1650_BRIGHT7       0x71   /*七级亮度，打开LED显示*/
#define TM1650_BRIGHT8       0x01   /*八级亮度，打开LED显示*/
#define TM1650_DSP_OFF       0x00   /*关闭LED显示*/
 
//数码管位选
#define TM1650_DIG1     0
#define TM1650_DIG2     1
#define TM1650_DIG3     2
#define TM1650_DIG4     3

/*
*****************************************************************
 * 函数原型： static void BH1750_Delay_us(int32_t time)
 * 功    能： 使用水滴计时器不准，于是 采用粗略计时
 * 输    入:  time:时间
 * 参    数： int32_t time
 * 调    用： 内部调用
*****************************************************************
*/
static void TM1650_delay_us(int32_t time)
{
   uint16_t i=0;  
   while(time--)
   {
      i=10;  //自己定义
      while(i--) ;    
   }
}

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
	TM1650_delay_us(10);
	TM1650_SDA_L;
	TM1650_delay_us(10);
	TM1650_SCL_L;
	TM1650_delay_us(10);
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
	TM1650_SCL_L;
	TM1650_delay_us(10);
	TM1650_SCL_H;
	TM1650_delay_us(10);
	TM1650_SDA_H;
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
	
	for(i=0;i<8;i++)
	{
		TM1650_SCL_L;
		TM1650_delay_us(10);
		if(Temp&0x01)
		{	
			TM1650_SDA_H;
		}
		else
		{
			TM1650_SDA_L;
		}
		TM1650_delay_us(10);
		TM1650_SCL_H;
		TM1650_delay_us(10);
		TM1650_SCL_L;
		Temp = Temp >> 1;
	}
}

uint8_t TM1650_IIC_wait_ack(void)
{
	uint8_t ack_signal = 0;
	
	TM1650_SDA_H;    //SDA=1
	TM1650_delay_us(10);
	TM1650_SCL_H;
	TM1650_delay_us(10);
	SDA_IN();
	if(TM1650_SDA_RD()) ack_signal = 1;   //如果读取到的是NACK信号
	TM1650_SCL_L;
	TM1650_delay_us(10);
	SDA_OUT();
	return ack_signal;
}

void TM1650_cfg_display(uint8_t param)
{
	TM1650_Start();
	TM1650_Write_Byte(0x48);  TM1650_IIC_wait_ack();     //固定命令
	TM1650_Write_Byte(param); TM1650_IIC_wait_ack();    //参数值
	TM1650_Stop();
}

void TM1650_print(uint8_t dig,uint8_t seg_data)
{
	TM1650_Start();
	TM1650_Write_Byte(dig*2+0x68); TM1650_IIC_wait_ack();  //显存起始地址为0x68
	TM1650_Write_Byte(seg_data); TM1650_IIC_wait_ack();    //发送段码
	TM1650_Stop();
}

//将显存数据全部刷为0，清空显示
void TM1650_clear(void)
{
	uint8_t dig;
	for(dig = TM1650_DIG1 ; dig<= TM1650_DIG4 ;dig++)
	{
		TM1650_print(dig,0);   //将显存数据刷为0
	}
}


/*
*****************************************************************
 * 函数原型：void TM1650_Init(void)
 * 功    能：TM1650初始化
*****************************************************************
*/
void TM1650_Init(void)
{
	TM1650_cfg_display(TM1650_BRIGHT1);   //初始化为5级亮度，打开显示
//	TM1650_clear();
//	TM1650_print(TM1650_DIG1,0X33);
}
