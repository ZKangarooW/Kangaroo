//************************************************************
//  Copyright (c) 
//	�ļ�����	: SCDriver_IR_Decode.c
//	����		: Andy
//	ģ�鹦��	: ����ͨ�Ž���Ӧ��������Դ�ļ�
//  ����������: 2020/3/2
// 	�汾		: V0.1 
//  ˵��
//*************** ����ͨ�Ž�������˵��*********************************
//  ����NECЭ�飬�������̽ͷ����1838B���ܽ���ѡ�����ⲿ�жϵ�IO
//  ����ɵ� �ͻ��루16λ��+�����루8λ��+�����뷴�루8λ��+�ظ��루8λ��
//*********************************************************************
//*************************************************************
#include"..\H\SCDriver_IR_Decode.h"
#include"SC_Init.h"

#define  SCD_IO_PORT(IO)    (unsigned char)(IO>>8)
#define  SCD_IO_PIN(IO)	    (unsigned char)(IO)

unsigned int SCD_IR_Count = 0;	//�����׼ʱ�����
// SCD_IR_DecodeValue[0][1]	��ʾ16λ�ͻ���
// SCD_IR_DecodeValue[2] ��ʾ������
// SCD_IR_DecodeValue[3] ��ʾ�����뷴��
// SCD_IR_DecodeValue[4] ��ʾ���յ����ظ���ĸ��������յ��µ�һ֡����ʱ�����ֽ���0
unsigned char SCD_IR_DecodeValue[5] = {0,0,0,0,0};  //����������飬��SCD_IR_OK_FlagΪ1ʱ��λ����Ч
bit SCD_IR_Flag = 1;        //������ձ�־λ��
bit SCD_IR_OK_Flag=0;		//��ʶ�����Ƿ���ɡ�
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
//������  #SCD_IR_Decode_Init#
//��������#�ú������ں�����չܽŵĳ�ʼ���������ⲿ�ж���IOģʽ�ĳ�ʼ��#
//�������#void#
//�������#void#
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
//������  #SCD_IR_BaseTime#
//��������#�ú������ں����źż�ʱ��ÿ��50us����һ�Σ���������жϷ��������#
//�������#void#
//�������#void#
//}
void SCD_IR_BaseTime(void)
{
	SCD_IR_Count++;	
}

//{
//������  #SCD_IR_Decode#
//��������#�ú������ں������ݽ��룬��������ⲿ�жϷ��������#
//�������#void#
//�������#void#
//}
void SCD_IR_Decode(void)
{
	static unsigned char  i = 0,j = 0;            
	if(SCD_IR_Count<=600 && SCD_IR_Count>=1) //�����룬9ms+4.5ms=270��
	{
		i = 0;
		j = 0;							  	   //�������½���
		SCD_IR_DecodeValue[4] = 0;
		SCD_IR_Flag = 0;              		   //���յ���ȷ��������,��ʼ��������
		Infrared[0].Someone = 1;
		Speed.Set =SCD_IR_Count;
		SCD_IR_Count = 0;
	}
	
//	if(SCD_IR_Count<=600 && SCD_IR_Count>=400)
//	{
//		SCD_IR_DecodeValue[4]++;			   //���յ����ظ������
//		SCD_IR_OK_Flag=1;		  		 		//���ճɹ���־
//	}
//	
//	
//	
//	if(SCD_IR_Flag == 1)//���˸���
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
//				SCD_IR_Flag = 1;//�������		
//				SCD_IR_OK_Flag=1;//���ճɹ���־
//			}
//		}
//	}		
}

//��ö�Ӧ�Ľ���ֵ
//�������ֵ
// 0 ��ʾ16λ�ͻ����8λ
// 1 ��ʾ16λ�ͻ����8λ
// 2 ��ʾ������
// 3 ��ʾ�����뷴��
// 4 ��ʾ���յ����ظ���ĸ��������յ��µ�һ֡����ʱ�����ֽ���0
unsigned char SCD_IR_Decode_ReadValue(unsigned char i)
{
	return SCD_IR_DecodeValue[i];
}
 


