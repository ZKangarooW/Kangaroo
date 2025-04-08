#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Tab[] = {0xF5,0x05,0xD3,0x97,0x27,0xB6,0xF6,0x15,0xF7,0xB7};//0��9
uint8_t Tab1[] = {0x5F,0x06,0x6B,0x2F,0x36,0x3D,0x7D,0x07,0x7F,0x3F,0x20,0x73};//0��9 10:- 11:P
uint8_t Tab2[] = {0x5F,0x06,0x3D,0x2F,0x66,0x6B,0x7B,0x0E,0x7F,0x6F};//0��9
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
	
	/***********�趨�¶ȼ���**********/
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
	
	/***********ʵ���¶ȼ���**********/
	if(dis_rel_temp > 999)//����999ʱ
	{
		Val=dis_rel_temp/1000;//ȡ��ǧλ
		Temp_QU = Tab[Val];
	}
	else
	{
		Temp_QU = 0x00;//����ʾ
	}
	if(dis_rel_temp > 99)//����99ʱ
	{
		Val=dis_rel_temp/100;//ȡ����λ
		if(dis_rel_temp > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		Temp_BU = Tab[Val];
	}
	else
	{
		Temp_BU = 0x00;//����ʾ
	}
	if(dis_rel_temp > 9)//����9ʱ
	{
		Val=dis_rel_temp/10;//ȡ��ʮλ
		if(dis_rel_temp > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		Temp_SU = Tab[Val];
	}
	else
	{
		Temp_SU = Tab[0];//����ʾ0
	}
	Val=dis_rel_temp%10;//ȡ����λ
	Temp_GU = Tab[Val];
	
//	/*************����ͼ��*************/
//	seg1 &= 0x7f;seg1 |= 0x80;//L6
//	seg2 &= 0x7f;seg2 |= 0x80;//L7
//	seg3 &= 0x7f;seg3 |= 0x80;//L8
//	seg4 &= 0x7f;seg4 |= 0x80;//L9
//	seg5 &= 0x7f;seg5 |= 0x80;//L10
//	
	/*************�¶�С�����ͼ��*******/
	seg6 &= 0xf7;seg6 |= 0x08;//ʵ���¶�С����
	seg7 &= 0x7f;seg7 |= 0x80;//�趨�¶�С����
	
	/****************��******************/
	seg8 &= 0x7F;seg8 |= 0x80;//��
	
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
	Write_Addr_Dat_N(0, seg1,1);
	Write_Addr_Dat_N(2, seg2,1);
	Write_Addr_Dat_N(4, seg3,1);
	Write_Addr_Dat_N(6, seg4,1);
	Write_Addr_Dat_N(8, seg5,1);
	Write_Addr_Dat_N(10, seg6,1);
	Write_Addr_Dat_N(12, seg7,1);
	Write_Addr_Dat_N(14, seg8,1);
}
/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
 * ��    �ܣ���ʾת��
 * ��    ��: dis_set_speed �趨ת��  dis_rel_speed ʵ��ת��
 * ��    ����int16_t dis_set_speed,int16_t dis_rel_speed
*****************************************************************
*/
void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
{
	uint8_t seg9,seg10,seg11,seg12,seg13,seg14,seg15,seg16,seg17;
	seg9=0;seg10=0;seg11=0;seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;
	uint8_t Speed_QU,Speed_BU,Speed_SU,Speed_GU;//ʵ���ٶȵļ���λ��ȡֵ
	uint8_t Speed_QD,Speed_BD,Speed_SD,Speed_GD;//�趨�ٶȵļ���λ��ȡֵ
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	if(Speed_ShowFlag == 0)
	{
		/***********�趨ת�ټ���**********/
		if(dis_set_speed > 999)//����999ʱ
		{
			Val=dis_set_speed/1000;//ȡ��ǧλ
			Speed_QD = Tab1[Val];
		}
		else
		{
			Speed_QD = Tab1[0];//��ʾ0
		}
		if(dis_set_speed > 99)//����99ʱ
		{
			Val=dis_set_speed/100;//ȡ����λ
			if(dis_set_speed > 999)//����999ʱ
				Val=Val%10;//ȡ����λ
			Speed_BD = Tab1[Val];
		}
		else
		{
			Speed_BD = Tab1[0];//��ʾ0
		}
		if(dis_set_speed > 9)//����9ʱ
		{
			Val=dis_set_speed/10;//ȡ��ʮλ
			if(dis_set_speed > 99)//����99ʱ
				Val=Val%10;//ȡ��ʮλ
			Speed_SD = Tab1[Val];
		}
		else
		{
			Speed_SD = Tab1[0];//��ʾ0
		}
		Val=dis_set_speed%10;//ȡ����λ
		Speed_GD = Tab1[Val];
	}
	else
	{
		Speed_QD = 0x00;//����ʾ�趨�ٶ�
		Speed_BD = 0x00;//����ʾ�趨�ٶ�
		Speed_SD = 0x00;//����ʾ�趨�ٶ�
		Speed_GD = 0x00;//����ʾ�趨�ٶ�
	}
	
	/***********ʵ��ת�ټ���**********/
	if(dis_rel_speed > 999)//����999ʱ
	{
		Val=dis_rel_speed/1000;//ȡ��ǧλ
		Speed_QU = Tab[Val];
	}
	else
	{
		Speed_QU = Tab[0];//��ʾ0
	}
	if(dis_rel_speed > 99)//����99ʱ
	{
		Val=dis_rel_speed/100;//ȡ����λ
		if(dis_rel_speed > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		Speed_BU = Tab[Val];
	}
	else
	{
		Speed_BU = Tab[0];//��ʾ0
	}
	if(dis_rel_speed > 9)//����9ʱ
	{
		Val=dis_rel_speed/10;//ȡ��ʮλ
		if(dis_rel_speed > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		Speed_SU = Tab[Val];
	}
	else
	{
		Speed_SU = Tab[0];//��ʾ0
	}
	Val=dis_rel_speed%10;//ȡ����λ
	Speed_GU = Tab[Val];
	
//	/*************���ȵ�ͼ��*************/
//	seg9 &= 0xFE;seg9 |= 0x01;//����ͼ��
//	
//	/*************�����ͼ��*************/
//	seg9 &= 0xFD;seg9 |= 0x02;//����ͼ��
//	
//	/*************ʱ���ͼ��*************/
//	seg9 &= 0xFB;seg9 |= 0x04;//ʱ��ͼ��
//	
//	/*************�ϸǵ�ͼ��*************/
//	seg9 &= 0xF7;seg9 |= 0x08;//�ϸ�ͼ��
//	
//	/*************��ģ���ͼ��***********/
//	seg9 &= 0xEF;seg9 |= 0x10;//��ģ��ͼ��
//	
//	/*************��ģ���ͼ��***********/
//	seg9 &= 0xDF;seg9 |= 0x20;//��ģ��ͼ��
//	
//	/*************�ײ�ģ���ͼ��*********/
//	seg9 &= 0xBF;seg9 |= 0x40;//�ײ�ģ��ͼ��
//	
//	/*************L11��ͼ��**************/
//	seg9 &= 0x7F;seg9 |= 0x80;//L11ͼ��
//	
//	/*************ת�ٵ�ͼ��*************/
//	seg10 &= 0x7F;seg10 |= 0x80;//S5ͼ��
//	seg11 &= 0x7F;seg11 |= 0x80;//S3ͼ��
//	
//	/*************ʱ�䵥λ��ͼ��*********/
//	seg12 &= 0x7F;seg12 |= 0x80;//secͼ��
//	
//	/*************ʱ�䵥λ��ͼ��*********/
//	seg15 &= 0x7F;seg15 |= 0x80;//minͼ��
//	
//	/*************ʱ��ð�ŵ�ͼ��*********/
//	seg13 &= 0xFE;seg13 |= 0x01;//�趨ת���ϵ�ð��
//	seg14 &= 0x7F;seg14 |= 0x80;//�趨ת���ϵ�ð��
//	
//	/*************ʱ�䵥λ��ͼ��*********/
//	seg16 &= 0x7F;seg16 |= 0x80;//�趨ת��minͼ��
//	
//	/*************ת�ٵ�λ��ͼ��*********/
//	seg17 &= 0x7F;seg17 |= 0x80;//�趨ת��rpmͼ��
	
	/*************���ݲ��***************/
	seg11 &= 0xF8;seg11 |= (Speed_QU & 0x07);
	seg10 &= 0xF0;seg10 |= (Speed_QU >>4) & 0x0F;
	seg11 &= 0x87;seg11 |= ((Speed_QD<<3)&0x70)|((Speed_QD<<3)&0x08);
	seg10 &= 0x8F;seg10 |= (Speed_QD&0x70);
	
	seg13 &= 0x1F;seg13 |= ((Speed_BU<<1) & 0x0E);
	seg12 &= 0xF0;seg12 |= (Speed_BU >>4) & 0x0F;
	seg13 &= 0x0F;seg13 |= Speed_BD<<4;
	seg12 &= 0x8F;seg12 |= (Speed_BD&0x70);
	
	seg15 &= 0xF8;seg15 |= (Speed_SU & 0x07);
	seg14 &= 0xF0;seg14 |= (Speed_SU >>4) & 0x0F;
	seg15 &= 0x87;seg15 |= ((Speed_SD<<3)&0x70)|((Speed_SD<<3)&0x08);
	seg14 &= 0x8F;seg14 |= (Speed_SD&0x70);
	
	seg17 &= 0xF8;seg17 |= (Speed_GU & 0x07);
	seg16 &= 0xF0;seg16 |= (Speed_GU >>4) & 0x0F;
	seg17 &= 0x87;seg17 |= ((Speed_GD<<3)&0x70)|((Speed_GD<<3)&0x08);
	seg16 &= 0x8F;seg16 |= (Speed_GD&0x70);
	
	/*************��������***************/	
	Write_Addr_Dat_N(16, seg9,1);
	Write_Addr_Dat_N(18, seg10,1);
	Write_Addr_Dat_N(20, seg11,1);
	Write_Addr_Dat_N(22, seg12,1);
	Write_Addr_Dat_N(24, seg13,1);
	Write_Addr_Dat_N(26, seg14,1);
	Write_Addr_Dat_N(28, seg15,1);
	Write_Addr_Dat_N(30, seg16,1);	
	Write_Addr_Dat_N(32, seg17,1);	
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Time(int32_t dis_time)
 * ��    �ܣ���ʾʱ��
 * ��    ��: dis_time ʱ��
 * ��    ����int32_t dis_time
*****************************************************************
*/
void Display_Time(int32_t dis_time)
{
	uint8_t seg18,seg19,seg20,seg21,seg22,seg23,seg24,seg25;
	seg18=0;seg19=0;seg20=0;seg21=0;seg22=0;seg23=0;seg24=0;seg25=0;
	uint8_t Time_Q,Time_B,Time_S,Time_G;//ʱ��ļ���λ��ȡֵ
	uint8_t P_B,P_S,P_G;//pģʽ����е�λ��ȡֵ
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
	
	if(Time.Set)//�����趨ʱ�����0
	{
		/**************ʱ�����*************/
		 if(Time.Set < 3600)
		{
			SH=dis_time%3600/60/10;//����ʮλ��λ�ķ�����
			H=dis_time%3600/60%10;//�����λ��λ�ķ�����
			SM=dis_time%60/10;//����ʮ��λ��λ��������
			M=dis_time%60%10;//����ʮ��λ��λ��������
		}
		else
		{
			SH=dis_time/3600/10;//����ʮλ��λ��Сʱ��
			H=dis_time/3600%10;//�����λ��λ��Сʱ��
			SM=dis_time%3600/60/10;//����ʮ��λ��λ�ķ�����
			M=dis_time%3600/60%10;//�������λ��λ�ķ�����
		}
		Time_Q = Tab2[SH];
		Time_B = Tab2[H];
		Time_S = Tab2[SM];
		Time_G = Tab2[M];
	}
	else
	{
		Time_Q = 0x20;//��ʾ"-"
		Time_B = 0x20;//��ʾ"-"
		Time_S = 0x20;//��ʾ"-"
		Time_G = 0x20;//��ʾ"-"
	}
	P_B = Tab1[11];
	P_S = Tab1[10];
	P_G = Tab1[2];
	
	
//	/*************ת�ٵ�ͼ��*************/
//	seg19 &= 0xF7;seg19 |= 0x08;//S4ͼ��
//	seg19 &= 0x7F;seg19 |= 0x80;//S6ʱ��L��ͼ��
//	
//	/*************L12��ͼ��**************/
//	seg19 &= 0x8F;seg19 |= 0x40;//L12ͼ��
//	
//	/*************L1��ͼ��***************/
//	seg20 &= 0xEF;seg20 |= 0x10;//L1ͼ��
//	
//	/*************L2��ͼ��***************/
//	seg22 &= 0xEF;seg22 |= 0x10;//L2ͼ��
//	
//	/*************L3��ͼ��***************/
//	seg23 &= 0xF7;seg23 |= 0x08;//L3ͼ��
//	
//	/*************L4��ͼ��***************/
//	seg24 &= 0xEF;seg24 |= 0x10;//L4ͼ��
//	
//	/*************L5��ͼ��***************/
//	seg25 &= 0xF7;seg25 |= 0x08;//L5ͼ��
//	
//	/*************��ʱ��ð�ŵ�ͼ��*******/
//	seg21 &= 0xFE;seg21 |= 0x01;//ð�ŵ�ͼ��
	
	/*************���ݲ��***************/
	seg18 &= 0xF0;seg18 |= (Time_Q&0x0F);
	seg19 &= 0xF8;seg19 |= ((Time_Q>>4)&0x07);
	
	seg20 &= 0xF0;seg20 |= (Time_B&0x0F);
	seg21 &= 0xF1;seg21 |= ((Time_B>>3)&0x0E);
	seg20 &= 0x1F;seg20 |= ((P_B<<1)&0xE0);
	seg21 &= 0x0F;seg21 |= ((P_B <<4)&0xF0);
	
	seg22 &= 0xF0;seg22 |= (Time_S&0x0F);
	seg23 &= 0xF8;seg23 |= ((Time_S>>4)&0x07);
	seg22 &= 0x1F;seg22 |= ((P_S<<1)&0xE0);
	seg23 &= 0x0F;seg23 |= ((P_S <<4)&0xF0);
	
	seg24 &= 0xF0;seg24 |= (Time_G&0x0F);
	seg25 &= 0xF8;seg25 |= ((Time_G>>4)&0x07);
	seg24 &= 0x1F;seg24 |= ((P_G<<1)&0xE0);
	seg25 &= 0x0F;seg25 |= ((P_G <<4)&0xF0);
	
	/*************��������***************/	
	Write_Addr_Dat_N(34, seg18,1);
	Write_Addr_Dat_N(36, seg19,1);
	Write_Addr_Dat_N(38, seg20,1);
	Write_Addr_Dat_N(40, seg21,1);
	Write_Addr_Dat_N(42, seg22,1);
	Write_Addr_Dat_N(44, seg23,1);
	Write_Addr_Dat_N(46, seg24,1);
	Write_Addr_Dat_N(48, seg25,1);	
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Show_Display(void)
 * ��    �ܣ���ʾ��Ļ����
*****************************************************************
*/
void Show_Display(void)
{
	Temp.Display_Set = Temp.Set;//��ʾ�趨�¶�
	Temp.Display_Rel = Temp.Rel;//��ʾ�趨�¶�
	
	Speed.Display_Rel = Speed.Rel;//��ʾ�趨ת��
	Speed.Display_Set = Speed.Set;//��ʾ�趨ת��
	
	Time.Display = Time.Set;//��ʾ�趨ʱ��
    Display_Temp(Temp.Display_Set,Temp.Display_Rel);
	Display_Speed(Speed.Display_Rel,Speed.Display_Set);
	Display_Time(Time.Display);
}
