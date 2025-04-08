#include "Drv_WS2812.h"

/**********�ṹ��************/
_WS2812_RGB_ WS2812 = {0,0,0,0,0,0,0};
_WS2812_ WS2812_Status = {0,0,0};

/**********�ֲ���������******/
uint8_t WS2812_Buf[RGB_NUM * 24] = {0};//��ŵ�����
uint16_t Memaddr = 0;//����ĵ�ֵַ

/**
 * @brief ���õڼ����Ƶ���ɫ
 *
 * @param num Ҫ���õĵڼ�����
 * @param r ��ɫ��ɫֵ
 * @param g ��ɫ��ɫֵ
 * @param b ��ɫ��ɫֵ
 */
void WS2812_SetColor(uint8_t num, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t cnt = 0;
	uint8_t i = 0;
	WS2812_Status.Number = num;//�Ƶ����

	WS2812.Red_Out = WS2812.Red = r;//��ɫ��ֵ
	WS2812.Green_Out = WS2812.Green = g;
	WS2812.Blue_Out = WS2812.Blue = b;

	if (WS2812_Status.Number == 0xFF)//ͬʱ�ı����еƵ���ɫ
	{
		Memaddr = 0;// ��ͷ��ֵ
		while (cnt < RGB_NUM) // һ��һ����
		{
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X80;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X40;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X20;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0x10;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X08;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X04;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X02;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X01;//���趨ֵ��ַ���������
			
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X80;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X40;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X20;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0x10;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X08;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X04;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X02;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X01;//���趨ֵ��ַ���������
			
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X80;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X40;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X20;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0x10;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X08;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X04;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X02;//���趨ֵ��ַ���������
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X01;//���趨ֵ��ַ���������
			cnt++;
		}
	}
	else if (WS2812_Status.Number <= RGB_NUM)//ֻ�ı�ָ����ŵƵ���ɫ����RGB_NUM��ֵ
	{
		Memaddr = WS2812_Status.Number * 24;
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X80;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X40;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X20;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0x10;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X08;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X04;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X02;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X01;//���趨ֵ��ַ���������
		
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X80;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X40;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X20;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0x10;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X08;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X04;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X02;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X01;//���趨ֵ��ַ���������
		
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X80;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X40;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X20;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0x10;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X08;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X04;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X02;//���趨ֵ��ַ���������
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X01;//���趨ֵ��ַ���������
	}
	WS2812_Status.Update = 1;//������ʾ
}

/**
 * @brief �������ݿ������ŵ�ƽ�任
 *
 * @param data_bit ����1���ݻ���0����
 */
void WS2812_Bit(bit data_bit)
{
	if(data_bit)
	{
		WS2812B_H;
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		WS2812B_L;	
	}
	else
	{
		WS2812B_H;
		_nop_();_nop_();_nop_();
		WS2812B_L;	
	}
}

/**
 * @brief ����50us�ĵ͵�ƽ���֡
 *
 */
void WS2812_Reset(void)
{
	u16 i;
	WS2812B_L;
	for(i=0;i<90;i++){
		_nop_();_nop_();
	}
}

/**
 * @brief ���͵Ƶ�����
 *
 * @param pData ��������
 *
 * @param Length ���鳤��
 */
void WS2812_SendBuf(const uint8_t *pData,uint16_t Length)
{
	uint16_t i;
	
	for(i = 0;i<Length;i++)//ѭ������
	{
		WS2812_Bit(pData[i]);
	}
	
	WS2812_Reset();//�ȴ�50us
}

/**
 * @brief ����Ŀǰ�Ƶ�״̬
 *
 */
void WS2812_Update(void)
{
	if (WS2812_Status.Update)
	{
		WS2812_SendBuf(&WS2812_Buf,RGB_NUM * 24);//��ʼ�����ֽ�����
		WS2812_Status.Update = 0;//������ɣ���־λ����
	}
}


/**
 * @brief WS2812��ʾ����
 *
 * @param dT ��������
 */
void WS2812_Duty(float dT)
{
	static uint16_t time = 0;
	static uint8_t led_check = 1;
	static uint32_t time1 = 0;
	uint8_t step;
	uint8_t step1;
	uint8_t val1,val2;
	if (led_check) //�����ƹ��Լ�
	{
		time += 20;
		step = (time / 500) % 3;
		if (step == 0)
			WS2812_SetColor(0xFF, 0xFF, 0, 0);
		else if (step == 1)
			WS2812_SetColor(0xFF, 0, 0xFF, 0);
		else
			WS2812_SetColor(0xFF, 0, 0, 0xFF), led_check = 0, WS2812_Status.Mode = 1;
	}
	else
	{
		switch (WS2812_Status.Mode)
		{
			case 1:
				WS2812_SetColor(0xFF, 0x30, 0x30, 0x30);
				time1 += 20;
				step1 = (time1 / 100) % 24+3;
				val1 = step1;
				if(val1 > 26) val1 = 3;
				WS2812_SetColor(val1, 0xFF, 0xFF, 0xFF);
				val2 = val1+1;
				if(val2 > 26) val2 = 3;
				WS2812_SetColor(val2, 0xFF, 0xFF, 0xFF);	
			break;
		}
	}
}
