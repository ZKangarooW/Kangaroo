#include "Drv_Infrared.h"

/**********�ṹ��************/
_Infrared_ Infrared[2];

/**********�ֲ���������*******/
uint32_t Infrared_Time = 0;//���͵�ʱ��
uint8_t Infrared_Step = 0;//���͵Ĳ���

/**
 * @brief ��ʱ�������ж�
 *
 */
//void Infrared_TIM_Interrupt(void)
//{
//	
//}


//һ���߼�0�Ĵ�����Ҫ 1.125ms��560us�ز�+560us���У���
static void NEC_Send_0(void)
{
	CARRIER_38KHz();//�Ƚ�ֵΪ1/3�ز�
	Delay_10us(50);
	NO_CARRIER();//���ز�
	Delay_10us(48);
}


//һ���߼�1������Ҫ2.25ms��560us�ز�+1680us���У�
static void NEC_Send_1(void)
{
	CARRIER_38KHz();//�Ƚ�ֵΪ1/3�ز�
	Delay_10us(50);
	NO_CARRIER();//���ز�
	Delay_10us(138);

}

//NECЭ���ʽ��//�����룺����һ��9ms�ز��������룬֮����4.5ms�Ŀ��У�
static void NEC_Send_Head(void)
{
	CARRIER_38KHz();
	Delay_10us(750);//ʵ��10.56ms    10usʵ��13us
	NO_CARRIER();//���ز�]0
	Delay_10us(380);//ʵ�ʽ���ʱ����5.24ms
}

//������(�Լ��ӵ�)
static void NEC_Send_Tail(void)
{
 
	CARRIER_38KHz();
	Delay_10us(20);
	NO_CARRIER();
	Delay_10us(30);    //   2.5<3ms<3.3ms
}

//����һ�ֽ�����
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
 
	if (count == 0)          //���û���ظ����ֱ���������ز�������ܽ��п���״̬
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
//����16λ��ַ�루18ms36ms����8λ�����루9ms18ms���Լ�8Ϊ���ݷ��롣
//���ڶ���108ms����������������ظ������ݣ������ȷ���9ms�ز�������2.5ms,
//�ٷ���0.56ms�ز����ɣ�ע��ÿ�η���ļ��ʱ�䡣
void NEC_Send(uint8_t addr, uint8_t value, uint8_t cnt)
{
	NEC_Send_Head();                //������ʼ��
	NEC_Send_BYTE(addr);            //���͵�ַ��H
	NEC_Send_BYTE(~addr);           //���͵�ַ��L
	NEC_Send_BYTE(value);           //����������H
	NEC_Send_BYTE(~value);          //����������L
	NEC_Send_Repeat(cnt);           //�����ظ���
}
