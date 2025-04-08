#include "Drv_GN1640.h"

/*
*****************************************************************
 * ����ԭ�ͣ�static void GN1640_Start(void)
 * ��    �ܣ���ʼ����
 * ��    �ã��ڲ����� 
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
 * ����ԭ�ͣ�static void GN1640_Stop(void)
 * ��    �ܣ�ֹͣ����
 * ��    �ã��ڲ����� 
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
 * ����ԭ�ͣ�static void GN1640_Write_Byte(uint8_t date)
 * ��    �ܣ�д��һ���ֽ�
 * ��    �룺date���ֽ�
 * ��    ����uint8_t date
 * ��    �ã��ڲ����� 
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
 * ����ԭ�ͣ�static void Write_Com(uint8_t date)
 * ��    �ܣ�����������
 * ��    �룺date�������ֽ�
 * ��    ����uint8_t date
 * ��    �ã��ڲ����� 
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
 * ����ԭ�ͣ�void GN1640_Init(void)
 * ��    �ܣ�GN1640��ʼ��
 * ��    �ã��ڲ����� 
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
	Write_Com(0x89); //������ʾ������ʾ��0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f�ֱ��Ӧ������Ϊ:				 		
	GN1640_Stop();	

	GN1640_ALL();//ȫ������
	HAL_Delay(900);
	GN1640_CLS();
}

/*
*****************************************************************
 * ����ԭ�ͣ�void GN1640_CLS(void)
 * ��    �ܣ���������
 * ��    �ã��ڲ����� 
*****************************************************************
*/
void GN1640_CLS(void)
{
	unsigned char i;	
	Write_Com(0x40);//������ַģʽ
	GN1640_Start();
	GN1640_Write_Byte(0xC0);
	for(i=0;i<16;i++)
		GN1640_Write_Byte(0x00);
	GN1640_Stop();
}

/*
*****************************************************************
 * ����ԭ�ͣ�void GN1640_ALL(void)
 * ��    �ܣ�ȫ������
 * ��    �ã��ڲ����� 
*****************************************************************
*/
void GN1640_ALL(void)
{
	unsigned char i;	
	Write_Com(0x40);//������ַģʽ
	GN1640_Start();
	GN1640_Write_Byte(0xC0);
	for(i=0;i<16;i++)
		GN1640_Write_Byte(0xFF);
	GN1640_Stop();
}


/*
*****************************************************************
 * ����ԭ�ͣ�void GN1640_Write_DATA(uint8_t add,uint8_t DATA)
 * ��    �ܣ�ָ����ַд������
 * ��    �룺uint8_t add,uint8_t DATA
 * ��    ����add����ַ��DATA������
 * ��    �ã��ڲ����� 
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
