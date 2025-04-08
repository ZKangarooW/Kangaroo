#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Tab[] = {0xF5,0x05,0xD3,0x97,0x27,0xB6,0xF6,0x15,0xF7,0xB7};//0��9
uint8_t Tab1[] = {0x5F,0x06,0x6B,0x2F,0x36,0x3D,0x7D,0x07,0x7F,0x3F};//0��9
uint8_t Time_ShowFlag,Speed_ShowFlag,Temp_ShowFlag;//ʱ�䡢�ٶȡ��¶���ʾ�ı�־λ 0:���� 1��Ϩ��

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
 * ��    �ܣ���ʾ�¶�
 * ��    ��: dis_set_temp �趨�¶�  dis_rel_temp ʵ���¶�
 * ��    ����int16_t dis_set_temp,int16_t dis_rel_temp
*****************************************************************
*/
void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint8_t Temp_QU,Temp_BU,Temp_SU,Temp_GU;//ʵ���¶ȵļ���λ��ȡֵ
	uint8_t Temp_QD,Temp_BD,Temp_SD,Temp_GD;//�趨�¶ȵļ���λ��ȡֵ
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	if(dis_set_temp > 0)
	{
		if(dis_set_temp > 999)//����999ʱ
		{
			Val=dis_set_temp/1000;//ȡ��ǧλ
			Temp_QD = Tab1[Val];
		}
		else
		{
			Temp_QD = 0x00;//����ʾ
		}
		if(dis_set_temp > 99)//����99ʱ
		{
			Val=dis_set_temp/100;//ȡ����λ
			if(dis_set_temp > 999)//����999ʱ
				Val=Val%10;//ȡ����λ
			Temp_BD = Tab1[Val];
		}
		else
		{
			Temp_BD = 0x00;//����ʾ
		}
		if(dis_set_temp > 9)//����9ʱ
		{
			Val=dis_set_temp/10;//ȡ��ʮλ
			if(dis_set_temp > 99)//����99ʱ
				Val=Val%10;//ȡ��ʮλ
			Temp_SD = Tab1[Val];
		}
		else
		{
			Temp_SD = Tab1[0];//����ʾ0
		}
		Val=dis_set_temp%10;//ȡ����λ
		Temp_GD = Tab1[Val];
	}
	else
	{
		Temp_QD = 0x20;//��ʾ"-"
		Temp_BD = 0x20;//��ʾ"-"
		Temp_SD = 0x20;//��ʾ"-"
		Temp_GD = 0x20;//��ʾ"-"
	}
	
	Temp_QU = Tab[0];
	Temp_BU = Tab[0];
	Temp_SU = Tab[0];
	Temp_GU = Tab[0];
//	Temp_QD = Tab1[7];
//	Temp_BD = Tab1[7];
//	Temp_SD = Tab1[7];
//	Temp_GD = Tab1[7];
	/*************���ݲ��***************/	
	seg2 &= 0xF8;seg2 |= (Temp_QU & 0x07);
	seg1 &= 0xF0;seg1 |= (Temp_QU >>4) & 0x0F;
	seg2 &= 0x87;seg2 |= ((Temp_QD<<3)&0x70)|((Temp_QD<<3)&0x08);
	seg1 &= 0x8F;seg1 |= (Temp_QD&0x70);
	
	seg4 &= 0xF8;seg4 |= (Temp_BU & 0x07);
	seg3 &= 0xF0;seg3 |= (Temp_BU >>4) & 0x0F;
	seg4 &= 0x87;seg4 |= ((Temp_BD<<3)&0x70)|((Temp_BD<<3)&0x08);
	seg3 &= 0x8F;seg3 |= (Temp_BD&0x70);
	
	seg6 &= 0xF8;seg6 |= (Temp_SU & 0x07);
	seg5 &= 0xF0;seg5 |= (Temp_SU >>4) & 0x0F;
	seg6 &= 0x0F;seg6 |= Temp_SD<<4;
	seg5 &= 0x8F;seg5 |= (Temp_SD&0x70);
	
	seg8 &= 0xF8;seg8 |= (Temp_GU & 0x07);
	seg7 &= 0xF0;seg7 |= (Temp_GU >>4) & 0x0F;
	seg8 &= 0x87;seg8 |= ((Temp_GD<<3)&0x70)|((Temp_GD<<3)&0x08);
	seg7 &= 0x8F;seg7 |= (Temp_GD&0x70);
	
	/*************��������***************/	
	Write_Addr_Dat_N(0, seg1,1);//SEG27
	Write_Addr_Dat_N(2, seg2,1);//SEG26
	Write_Addr_Dat_N(4, seg3,1);//SEG25
	Write_Addr_Dat_N(6, seg4,1);//SEG24
	Write_Addr_Dat_N(8, seg5,1);//SEG23
	Write_Addr_Dat_N(10, seg6,1);//SEG22
	Write_Addr_Dat_N(12, seg7,1);//SEG21
	Write_Addr_Dat_N(14, seg8,1);//SEG20
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Show_Display(void)
 * ��    �ܣ���ʾ��Ļ����
*****************************************************************
*/
void Show_Display(void)
{
    Display_Temp(12,654);
}
