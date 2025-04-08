#include "Drv_TM1650.h"

//��ʾ����
#define TM1650_BRIGHT1       0x11   /*һ�����ȣ���LED��ʾ*/
#define TM1650_BRIGHT2       0x21   /*�������ȣ���LED��ʾ*/
#define TM1650_BRIGHT3       0x31   /*�������ȣ���LED��ʾ*/
#define TM1650_BRIGHT4       0x41   /*�ļ����ȣ���LED��ʾ*/
#define TM1650_BRIGHT5       0x51   /*�弶���ȣ���LED��ʾ*/
#define TM1650_BRIGHT6       0x61   /*�������ȣ���LED��ʾ*/
#define TM1650_BRIGHT7       0x71   /*�߼����ȣ���LED��ʾ*/
#define TM1650_BRIGHT8       0x01   /*�˼����ȣ���LED��ʾ*/
#define TM1650_DSP_OFF       0x00   /*�ر�LED��ʾ*/
 
//�����λѡ
#define TM1650_DIG1     0
#define TM1650_DIG2     1
#define TM1650_DIG3     2
#define TM1650_DIG4     3

/*
*****************************************************************
 * ����ԭ�ͣ� static void BH1750_Delay_us(int32_t time)
 * ��    �ܣ� ʹ��ˮ�μ�ʱ����׼������ ���ô��Լ�ʱ
 * ��    ��:  time:ʱ��
 * ��    ���� int32_t time
 * ��    �ã� �ڲ�����
*****************************************************************
*/
static void TM1650_delay_us(int32_t time)
{
   uint16_t i=0;  
   while(time--)
   {
      i=10;  //�Լ�����
      while(i--) ;    
   }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TM1650_Start(void)
 * ��    �ܣ�TM1650��ʼ����
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
 * ����ԭ�ͣ�void TM1650_Stop(void)
 * ��    �ܣ�TM1650��������
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
 * ����ԭ�ͣ�void TM1650_Write_Byte(uint8_t date)
 * ��    �ܣ�д��һ��byte
 * ��    �룺date��д�������
 * ��    ����uint8_t date
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
	if(TM1650_SDA_RD()) ack_signal = 1;   //�����ȡ������NACK�ź�
	TM1650_SCL_L;
	TM1650_delay_us(10);
	SDA_OUT();
	return ack_signal;
}

void TM1650_cfg_display(uint8_t param)
{
	TM1650_Start();
	TM1650_Write_Byte(0x48);  TM1650_IIC_wait_ack();     //�̶�����
	TM1650_Write_Byte(param); TM1650_IIC_wait_ack();    //����ֵ
	TM1650_Stop();
}

void TM1650_print(uint8_t dig,uint8_t seg_data)
{
	TM1650_Start();
	TM1650_Write_Byte(dig*2+0x68); TM1650_IIC_wait_ack();  //�Դ���ʼ��ַΪ0x68
	TM1650_Write_Byte(seg_data); TM1650_IIC_wait_ack();    //���Ͷ���
	TM1650_Stop();
}

//���Դ�����ȫ��ˢΪ0�������ʾ
void TM1650_clear(void)
{
	uint8_t dig;
	for(dig = TM1650_DIG1 ; dig<= TM1650_DIG4 ;dig++)
	{
		TM1650_print(dig,0);   //���Դ�����ˢΪ0
	}
}


/*
*****************************************************************
 * ����ԭ�ͣ�void TM1650_Init(void)
 * ��    �ܣ�TM1650��ʼ��
*****************************************************************
*/
void TM1650_Init(void)
{
	TM1650_cfg_display(TM1650_BRIGHT1);   //��ʼ��Ϊ5�����ȣ�����ʾ
//	TM1650_clear();
//	TM1650_print(TM1650_DIG1,0X33);
}
