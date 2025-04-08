#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Time_ShowFlag,Speed_ShowFlag,Temp_ShowFlag;//ʱ�䡢�ٶȡ��¶���ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t Lock_ShowFlag,TimeIcn_ShowFlag,CGF_ShowFlag,SafeTemp_ShowFlag;//����ͼ���ʱ��ͼ����˸��CGF��˸�Ͱ�ȫ�¶�ͼ����˸

/*
*****************************************************************
 * ����ԭ�ͣ�static void Time_Twinkle(float dT)
 * ��    �ܣ�ʱ��ͼ����˸
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Time_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status)
	{
		T += dT;
		if(T >= 0.5f)
		{
			TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//ʱ��ͼ����˸;
			T = 0;
		}
	}
	else
	{
		TimeIcn_ShowFlag = 0;//��ʾʱ��ͼ��
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Lock(float dT)
 * ��    �ܣ�����ͼ����˸���
*****************************************************************
*/
void Check_Lock(float dT)
{
	static float T;
	if(sys.Lock_On == 0)
	{
		Lock_ShowFlag = 0;
		return;
	}
	T += dT;
	if(T >= 0.5f)
	{
		Lock_ShowFlag = ~Lock_ShowFlag;//����ͼ����˸;
		T = 0;
	}
	if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin) == 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin) == 1))//�����1�͵����2���պ�ʱ
		sys.Lock_On = 0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Start_SpeedRun(float dT)
 * ��    �ܣ�ת�ٶ���
*****************************************************************
*/
void Start_SpeedRun(float dT)
{
	static float T;

	if(sys.Run_Status == 0)
	{
		Speed.Icon_Step = 0;
		T = 0;
		return;
	}
	T += dT;
	if(T >= 0.5)
	{
		Speed.Icon_Step++;
		if(Speed.Icon_Step > 3)
			Speed.Icon_Step = 1;
		T = 0;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Check_Safe_Mode(float dT)
 * ��    �ܣ���ȫ�¶�ͼ����˸���
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Check_Safe_Mode(float dT)
{
	static float T;
	if(SafeTemp.Twinkleg)
	{
		T += dT;
		if(T >= 0.5f)
		{
			SafeTemp_ShowFlag = ~SafeTemp_ShowFlag;//��ȫ�¶�ͼ����˸
			T = 0;
		}
	}
	else
	{
		if(sys.SetMode_Option == 3)
			SafeTemp_ShowFlag = 1;
		else
			SafeTemp_ShowFlag = 0;
	}		
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Check_ShowFlag(float dT)
 * ��    �ܣ���˸���
 * ��    ��: dT:ִ������
 * ��    ����float dT
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Check_ShowFlag(float dT)
{
	static float T;
    if(sys.SetMode_Option == 0)//���û������ѡ���У��򶼵���������˸
    {
        Speed_ShowFlag = 0;//����
        Temp_ShowFlag = 0;//����
        Time_ShowFlag = 0;//����
        Twinkle_Time = 0;//��˸��ʱ����
        return;
    }
    if(Twinkle_Time && Key_Status==0)//��˸��û�в�������ʱ
    {
		T += dT;
		if(T >= 0.5f)
		{
			Twinkle_Time -= 0.5;//��˸��ʱ
			if(sys.SetMode_Option == 1)//����ʱ��
			{
				Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
				Speed_ShowFlag = 0;//�ٶȳ���
				Temp_ShowFlag = 0;//�¶ȳ��� 					
			}
			else if(sys.SetMode_Option == 2)//�����ٶ�
			{ 
				Time_ShowFlag = 0;//ʱ�䳣��
				Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
				Temp_ShowFlag = 0;//�¶ȳ���
			}
			else if(sys.SetMode_Option == 3)//�����¶�
			{
				Speed_ShowFlag = 0;//�ٶȳ���
				Time_ShowFlag = 0;//ʱ�䳣��
				Temp_ShowFlag = ~Temp_ShowFlag;//�¶���˸
			}
			if(Twinkle_Time == 0)//�����˸����
			{
				sys.SetMode_Option = 0;//ģʽѡ������
			} 
			T = 0;			
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//����
        Temp_ShowFlag = 0;//����
        Time_ShowFlag = 0;//����
		T = 0;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Twinkle(float dT)
 * ��    �ܣ���˸����
*****************************************************************
*/
void Twinkle(float dT)
{
	Time_Twinkle(dT);//ʱ��ͼ����˸
	Check_Lock(dT);//����ͼ����˸���
	Check_Safe_Mode(dT);//��ȫ�¶�ͼ����˸���
	Start_SpeedRun(dT);//ת�ٶ���
	Check_ShowFlag(dT);//��˸���
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Time(int32_t dis_set_time,int32_t dis_rel_time)
 * ��    �ܣ���ʾʱ��
 * ��    ��: dis_set_time���趨ʱ�䣬dis_rel_time��ʵ��ʱ��
 * ��    ����int32_t dis_set_time,int32_t dis_rel_time
*****************************************************************
*/
void Display_Time(int32_t dis_set_time,int32_t dis_rel_time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
	
	/***********�趨ʱ�����**********/
    if(dis_set_time > 3599)//����趨ʱ�����59.59����ʱ
    {
        SH=dis_set_time/3600/10;//����ʮλ��λ��Сʱ��
        H=dis_set_time/3600%10;//�����λ��λ��Сʱ��
        SM=dis_set_time%3600/60/10;//����ʮ��λ��λ�ķ�����
        M=dis_set_time%3600/60%10;//�������λ��λ�ķ�����
    }
    else
    {
        SH=dis_set_time%3600/60/10;//����ʮλ��λ�ķ�����
        H=dis_set_time%3600/60%10;//�����λ��λ�ķ�����
        SM=dis_set_time%60/10;//����ʮ��λ��λ��������
        M=dis_set_time%60%10;//����ʮ��λ��λ��������
    }
    
	if(Time_ShowFlag == 0)//����ʱ����˸
	{
		/***********set_timeʮСʱλ***********/
		switch(SH)
		{
			case 0:seg2&=0x0F;seg3&=0x8F;seg2|=0xF0;seg3|=0x50;//����0
				break;
			case 1:seg2&=0x0F;seg3&=0x8F;seg2|=0x00;seg3|=0x50;//����1
				break;
			case 2:seg2&=0x0F;seg3&=0x8F;seg2|=0xD0;seg3|=0x30;//����2
				break;
			case 3:seg2&=0x0F;seg3&=0x8F;seg2|=0x90;seg3|=0x70;//����3
				break;	
			case 4:seg2&=0x0F;seg3&=0x8F;seg2|=0x20;seg3|=0x70;//����4
				break;	
			case 5:seg2&=0x0F;seg3&=0x8F;seg2|=0xB0;seg3|=0x60;//����5
				break;	
			case 6:seg2&=0x0F;seg3&=0x8F;seg2|=0xF0;seg3|=0x60;//����6
				break;	
			case 7:seg2&=0x0F;seg3&=0x8F;seg2|=0x10;seg3|=0x50;//����7
				break;	
			case 8:seg2&=0x0F;seg3&=0x8F;seg2|=0xF0;seg3|=0x70;//����8
				break;	
			case 9:seg2&=0x0F;seg3&=0x8F;seg2|=0xB0;seg3|=0x70;//����9
				break;
			default:
				break;
		}	
		/***********set_timeСʱλ***********/
		switch(H)
		{
			case 0:seg4&=0x0F;seg5&=0x8F;seg4|=0xF0;seg5|=0x50;//����0
				break;
			case 1:seg4&=0x0F;seg5&=0x8F;seg4|=0x00;seg5|=0x50;//����1
				break;
			case 2:seg4&=0x0F;seg5&=0x8F;seg4|=0xD0;seg5|=0x30;//����2
				break;
			case 3:seg4&=0x0F;seg5&=0x8F;seg4|=0x90;seg5|=0x70;//����3
				break;	
			case 4:seg4&=0x0F;seg5&=0x8F;seg4|=0x20;seg5|=0x70;//����4
				break;	
			case 5:seg4&=0x0F;seg5&=0x8F;seg4|=0xB0;seg5|=0x60;//����5
				break;	
			case 6:seg4&=0x0F;seg5&=0x8F;seg4|=0xF0;seg5|=0x60;//����6
				break;	
			case 7:seg4&=0x0F;seg5&=0x8F;seg4|=0x10;seg5|=0x50;//����7
				break;	
			case 8:seg4&=0x0F;seg5&=0x8F;seg4|=0xF0;seg5|=0x70;//����8
				break;	
			case 9:seg4&=0x0F;seg5&=0x8F;seg4|=0xB0;seg5|=0x70;//����9
				break;
			default:
				break;
		}	
		
		/***********set_timeʮ��λ***********/
		switch(SM%10)
		{
			case 0:seg6&=0x0F;seg7&=0x8F;seg6|=0xF0;seg7|=0x50;//����0
				break;
			case 1:seg6&=0x0F;seg7&=0x8F;seg6|=0x00;seg7|=0x50;//����1
				break;
			case 2:seg6&=0x0F;seg7&=0x8F;seg6|=0xD0;seg7|=0x30;//����2
				break;
			case 3:seg6&=0x0F;seg7&=0x8F;seg6|=0x90;seg7|=0x70;//����3
				break;	
			case 4:seg6&=0x0F;seg7&=0x8F;seg6|=0x20;seg7|=0x70;//����4
				break;	
			case 5:seg6&=0x0F;seg7&=0x8F;seg6|=0xB0;seg7|=0x60;//����5
				break;	
			case 6:seg6&=0x0F;seg7&=0x8F;seg6|=0xF0;seg7|=0x60;//����6
				break;	
			case 7:seg6&=0x0F;seg7&=0x8F;seg6|=0x10;seg7|=0x50;//����7
				break;	
			case 8:seg6&=0x0F;seg7&=0x8F;seg6|=0xF0;seg7|=0x70;//����8
				break;	
			case 9:seg6&=0x0F;seg7&=0x8F;seg6|=0xB0;seg7|=0x70;//����9
				break;
			default:
				break;
		}		
		
		/***********set_time��λ***********/
		switch(M%10)
		{
			case 0:seg8&=0x0F;seg9&=0x8F;seg8|=0xF0;seg9|=0x50;//����0
				break;
			case 1:seg8&=0x0F;seg9&=0x8F;seg8|=0x00;seg9|=0x50;//����1
				break;
			case 2:seg8&=0x0F;seg9&=0x8F;seg8|=0xD0;seg9|=0x30;//����2
				break;
			case 3:seg8&=0x0F;seg9&=0x8F;seg8|=0x90;seg9|=0x70;//����3
				break;	
			case 4:seg8&=0x0F;seg9&=0x8F;seg8|=0x20;seg9|=0x70;//����4
				break;	
			case 5:seg8&=0x0F;seg9&=0x8F;seg8|=0xB0;seg9|=0x60;//����5
				break;	
			case 6:seg8&=0x0F;seg9&=0x8F;seg8|=0xF0;seg9|=0x60;//����6
				break;	
			case 7:seg8&=0x0F;seg9&=0x8F;seg8|=0x10;seg9|=0x50;//����7
				break;	
			case 8:seg8&=0x0F;seg9&=0x8F;seg8|=0xF0;seg9|=0x70;//����8
				break;	
			case 9:seg8&=0x0F;seg9&=0x8F;seg8|=0xB0;seg9|=0x70;//����9
				break;
			default:
				break;
		}			
	}
	else
	{
		seg2&=0x0F;seg3&=0x8F;seg2|=0x00;seg3|=0x00;//����ʾ
		seg4&=0x0F;seg5&=0x8F;seg4|=0x00;seg5|=0x00;//����ʾ
		seg6&=0x0F;seg7&=0x8F;seg6|=0x00;seg7|=0x00;//����ʾ
		seg8&=0x0F;seg9&=0x8F;seg8|=0x00;seg9|=0x00;//����ʾ
	}
    
	/***********ʵ��ʱ�����**********/
	if(dis_set_time > 3599)//����趨ʱ�����59.59����ʱ
	{
		SH=dis_rel_time/3600/10;//����ʮλ��λ��Сʱ��
		H=dis_rel_time/3600%10;//�����λ��λ��Сʱ��
		SM=dis_rel_time%3600/60/10;//����ʮ��λ��λ�ķ�����
		M=dis_rel_time%3600/60%10;//�������λ��λ�ķ�����
	}
	else
	{
		SH=dis_rel_time%3600/60/10;//����ʮλ��λ�ķ�����
		H=dis_rel_time%3600/60%10;//�����λ��λ�ķ�����
		SM=dis_rel_time%60/10;//����ʮ��λ��λ��������
		M=dis_rel_time%60%10;//����ʮ��λ��λ��������
	}
    
	/***********dis_rel_timeʮСʱλ***********/
	switch(SH)
	{
		case 0:seg1&=0xF0;seg2&=0xF1;seg1|=0x0F;seg2|=0x0A;//����0
			break;
		case 1:seg1&=0xF0;seg2&=0xF1;seg1|=0x00;seg2|=0x0A;//����1
			break;
		case 2:seg1&=0xF0;seg2&=0xF1;seg1|=0x0D;seg2|=0x06;//����2
			break;
		case 3:seg1&=0xF0;seg2&=0xF1;seg1|=0x09;seg2|=0x0E;//����3
			break;	
		case 4:seg1&=0xF0;seg2&=0xF1;seg1|=0x02;seg2|=0x0E;//����4
			break;	
		case 5:seg1&=0xF0;seg2&=0xF1;seg1|=0x0B;seg2|=0x0D;//����5
			break;	
		case 6:seg1&=0xF0;seg2&=0xF1;seg1|=0x0F;seg2|=0x0D;//����6
			break;	
		case 7:seg1&=0xF0;seg2&=0xF1;seg1|=0x01;seg2|=0x0A;//����7
			break;	
		case 8:seg1&=0xF0;seg2&=0xF1;seg1|=0x0F;seg2|=0x0E;//����8
			break;	
		case 9:seg1&=0xF0;seg2&=0xF1;seg1|=0x0B;seg2|=0x0E;//����9
			break;
		default:
			break;
	}	

	/***********dis_rel_timeСʱλ***********/
	switch(H)
	{
		case 0:seg3&=0xF0;seg4&=0xF1;seg3|=0x0F;seg4|=0x0A;//����0
			break;
		case 1:seg3&=0xF0;seg4&=0xF1;seg3|=0x00;seg4|=0x0A;//����1
			break;
		case 2:seg3&=0xF0;seg4&=0xF1;seg3|=0x0D;seg4|=0x06;//����2
			break;
		case 3:seg3&=0xF0;seg4&=0xF1;seg3|=0x09;seg4|=0x0E;//����3
			break;	
		case 4:seg3&=0xF0;seg4&=0xF1;seg3|=0x02;seg4|=0x0E;//����4
			break;	
		case 5:seg3&=0xF0;seg4&=0xF1;seg3|=0x0B;seg4|=0x0D;//����5
			break;	
		case 6:seg3&=0xF0;seg4&=0xF1;seg3|=0x0F;seg4|=0x0D;//����6
			break;	
		case 7:seg3&=0xF0;seg4&=0xF1;seg3|=0x01;seg4|=0x0A;//����7
			break;	
		case 8:seg3&=0xF0;seg4&=0xF1;seg3|=0x0F;seg4|=0x0E;//����8
			break;	
		case 9:seg3&=0xF0;seg4&=0xF1;seg3|=0x0B;seg4|=0x0E;//����9
			break;
		default:
			break;
	}	
	
	/***********dis_rel_timeʮ��λ***********/
	switch(SM%10)
	{
		case 0:seg5&=0xF0;seg6&=0xF1;seg5|=0x0F;seg6|=0x0A;//����0
			break;
		case 1:seg5&=0xF0;seg6&=0xF1;seg5|=0x00;seg6|=0x0A;//����1
			break;
		case 2:seg5&=0xF0;seg6&=0xF1;seg5|=0x0D;seg6|=0x06;//����2
			break;
		case 3:seg5&=0xF0;seg6&=0xF1;seg5|=0x09;seg6|=0x0E;//����3
			break;	
		case 4:seg5&=0xF0;seg6&=0xF1;seg5|=0x02;seg6|=0x0E;//����4
			break;	
		case 5:seg5&=0xF0;seg6&=0xF1;seg5|=0x0B;seg6|=0x0D;//����5
			break;	
		case 6:seg5&=0xF0;seg6&=0xF1;seg5|=0x0F;seg6|=0x0D;//����6
			break;	
		case 7:seg5&=0xF0;seg6&=0xF1;seg5|=0x01;seg6|=0x0A;//����7
			break;	
		case 8:seg5&=0xF0;seg6&=0xF1;seg5|=0x0F;seg6|=0x0E;//����8
			break;	
		case 9:seg5&=0xF0;seg6&=0xF1;seg5|=0x0B;seg6|=0x0E;//����9
			break;
		default: 
			break;
	}		
	
	/***********dis_rel_time��λ***********/
	switch(M%10)
	{
		case 0:seg7&=0xF0;seg8&=0xF1;seg7|=0x0F;seg8|=0x0A;//����0
			break;
		case 1:seg7&=0xF0;seg8&=0xF1;seg7|=0x00;seg8|=0x0A;//����1
			break;
		case 2:seg7&=0xF0;seg8&=0xF1;seg7|=0x0D;seg8|=0x06;//����2
			break;
		case 3:seg7&=0xF0;seg8&=0xF1;seg7|=0x09;seg8|=0x0E;//����3
			break;	
		case 4:seg7&=0xF0;seg8&=0xF1;seg7|=0x02;seg8|=0x0E;//����4
			break;	
		case 5:seg7&=0xF0;seg8&=0xF1;seg7|=0x0B;seg8|=0x0D;//����5
			break;	
		case 6:seg7&=0xF0;seg8&=0xF1;seg7|=0x0F;seg8|=0x0D;//����6
			break;	
		case 7:seg7&=0xF0;seg8&=0xF1;seg7|=0x01;seg8|=0x0A;//����7
			break;	
		case 8:seg7&=0xF0;seg8&=0xF1;seg7|=0x0F;seg8|=0x0E;//����8
			break;	
		case 9:seg7&=0xF0;seg8&=0xF1;seg7|=0x0B;seg8|=0x0E;//����9
			break;
		default:
			break;
	}
		
	/*************ʱ��ð��ͼ��***************/
	seg4&=0xFE; seg4|=0x01;//ʵ��ʱ��ð��
	seg5&=0x7F; seg5|=0x80;//�趨ʱ��ð��
	
    if(dis_set_time > 3599)//����趨ʱ�����59.59����ʱ
    {
        seg9&=0xF7;seg9|=0x08;//��ʾmin
    }
    else
    {
        seg7&=0x7F;seg7|=0x80;//��ʾsec
    }
	
	
	/*************�رո���ͼ��***************/
	if(Lock_ShowFlag == 0)//���ӵײ�(��Ϊ�رղ��ᴥ������������û�м���˸)
	{
		seg9&=0xFD;seg9|=0x02;//��ʾ���ӵײ�
	}
	else
	{
		seg9&=0xFD;seg9|=0x00;//����ʾ���ӵײ�
	}
	if(sys.Lid_State == 0)
	{
		seg9&=0xFE;seg9|=0x01;//�رո���ͼ��
	}
	else
	{
		seg9&=0xFE;seg9|=0x00;//�رո���ͼ�겻��ʾ
	}
	
	/****************************************/
	
	/*************ʱ��ͼ��***************/	
	if(TimeIcn_ShowFlag == 0)
	{
		seg9&=0xFB;seg9|=0x04;//��ʾ
	}
	else
	{
		seg9&=0xFB;seg9|=0x00;//����ʾ
	}
	
	/************************************/
	Write_Addr_Dat_N(0, seg1,1);//SEG29
	Write_Addr_Dat_N(2, seg2,1);//SEG28
	Write_Addr_Dat_N(4, seg3,1);//SEG27
	Write_Addr_Dat_N(6, seg4,1);//SEG26
	Write_Addr_Dat_N(8, seg5,1);//SEG25
	Write_Addr_Dat_N(10, seg6,1);//SEG24
	Write_Addr_Dat_N(12, seg7,1);//SEG23
	Write_Addr_Dat_N(14, seg8,1);//SEG22
	Write_Addr_Dat_N(16, seg9,1);//SEG21
}


/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
 * ��    �ܣ���ʾת��
 * ��    ��: dis_set_speed���趨ת�٣�dis_rel_speed��ʵ��ת��
 * ��    ����int16_t dis_set_speed,int16_t dis_rel_speed
*****************************************************************
*/
void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
{
	uint8_t seg10,seg11,seg12,seg13,seg14,seg15,seg16,seg17,seg18,seg19,seg20,seg21;
	seg10=0;seg11=0;seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;seg18=0;seg19=0;seg20=0;seg21=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	/***********�趨ת�ټ���**********/
    if(sys.Run_Mode == 0)//����ģʽ��
    {
        if(Speed_ShowFlag == 0)
        {
            /***********dis_set_speedǧλ***********/
            if(dis_set_speed > 9999)//����9999ʱ
            {
                seg20&=0x7F;seg20|=0x80;//��ʾ1		
            }
            else//С��9999ʱ
            {
                seg20&=0x7F;seg20|=0x00;//����ʾ
            }
            
            /***********dis_set_speedǧλ***********/
            if(dis_set_speed > 999)//����999ʱ
            {
                Val=dis_set_speed/1000;//ȡ��ǧλ
                if(dis_set_speed > 9999)//����9999ʱ
                    Val=Val%10;//ȡ��ǧλ
                switch(Val)
                {
                    case 0:seg20&=0x8F;seg21&=0x0F;seg20|=0x50;seg21|=0xF0;//����0
                        break;
                    case 1:seg20&=0x8F;seg21&=0x0F;seg20|=0x50;seg21|=0x00;//����1
                        break;
                    case 2:seg20&=0x8F;seg21&=0x0F;seg20|=0x30;seg21|=0xD0;//����2
                        break;
                    case 3:seg20&=0x8F;seg21&=0x0F;seg20|=0x70;seg21|=0x90;//����3
                        break;	
                    case 4:seg20&=0x8F;seg21&=0x0F;seg20|=0x70;seg21|=0x20;//����4
                        break;	
                    case 5:seg20&=0x8F;seg21&=0x0F;seg20|=0x60;seg21|=0xB0;//����5
                        break;	
                    case 6:seg20&=0x8F;seg21&=0x0F;seg20|=0x60;seg21|=0xF0;//����6
                        break;	
                    case 7:seg20&=0x8F;seg21&=0x0F;seg20|=0x50;seg21|=0x10;//����7
                        break;	
                    case 8:seg20&=0x8F;seg21&=0x0F;seg20|=0x70;seg21|=0xF0;//����8
                        break;	
                    case 9:seg20&=0x8F;seg21&=0x0F;seg20|=0x70;seg21|=0xB0;//����9
                        break;
                    default:
                        break;
                }			
            }
            else
            {
                seg20&=0x8F;seg21&=0x0F;seg20|=0x00;seg21|=0x00;//����ʾ
            }

            /***********dis_set_speed��λ***********/
            if(dis_set_speed > 99)//����99ʱ
            {
                Val=dis_set_speed/100;//ȡ����λ
                if(dis_set_speed > 999)//����999ʱ
                    Val=Val%10;//ȡ����λ
                switch(Val)
                {
                    case 0:seg15&=0x8F;seg14&=0x0F;seg15|=0x50;seg14|=0xF0;//����0
                        break;
                    case 1:seg15&=0x8F;seg14&=0x0F;seg15|=0x50;seg14|=0x00;//����1
                        break;
                    case 2:seg15&=0x8F;seg14&=0x0F;seg15|=0x30;seg14|=0xD0;//����2
                        break;
                    case 3:seg15&=0x8F;seg14&=0x0F;seg15|=0x70;seg14|=0x90;//����3
                        break;
                    case 4:seg15&=0x8F;seg14&=0x0F;seg15|=0x70;seg14|=0x20;//����4
                        break;	
                    case 5:seg15&=0x8F;seg14&=0x0F;seg15|=0x60;seg14|=0xB0;//����5
                        break;
                    case 6:seg15&=0x8F;seg14&=0x0F;seg15|=0x60;seg14|=0xF0;//����6
                        break;	
                    case 7:seg15&=0x8F;seg14&=0x0F;seg15|=0x50;seg14|=0x10;//����7
                        break;	
                    case 8:seg15&=0x8F;seg14&=0x0F;seg15|=0x70;seg14|=0xF0;//����8
                        break;	
                    case 9:seg15&=0x8F;seg14&=0x0F;seg15|=0x70;seg14|=0xB0;//����9
                        break;
                    default:
                        break;
                }			
            }
            else
            {
                seg15&=0x8F;seg14&=0x0F;seg15|=0x00;seg14|=0x00;//����ʾ
            }
            /***********dis_set_speedʮλ***********/
            if(dis_set_speed > 9)//����9ʱ
            {
                Val=dis_set_speed/10;//ȡ��ʮλ
                if(dis_set_speed > 99)//����99ʱ
                    Val=Val%10;//ȡ��ʮλ
                switch(Val)
                {
                    case 0:seg17&=0x8F;seg16&=0x0F;seg17|=0x50;seg16|=0xF0;//����0
                        break;
                    case 1:seg17&=0x8F;seg16&=0x0F;seg17|=0x50;seg16|=0x00;//����1
                        break;
                    case 2:seg17&=0x8F;seg16&=0x0F;seg17|=0x30;seg16|=0xD0;//����2
                        break;
                    case 3:seg17&=0x8F;seg16&=0x0F;seg17|=0x70;seg16|=0x90;//����3
                        break;
                    case 4:seg17&=0x8F;seg16&=0x0F;seg17|=0x70;seg16|=0x20;//����4
                        break;	
                    case 5:seg17&=0x8F;seg16&=0x0F;seg17|=0x60;seg16|=0xB0;//����5
                        break;
                    case 6:seg17&=0x8F;seg16&=0x0F;seg17|=0x60;seg16|=0xF0;//����6
                        break;	
                    case 7:seg17&=0x8F;seg16&=0x0F;seg17|=0x50;seg16|=0x10;//����7
                        break;	
                    case 8:seg17&=0x8F;seg16&=0x0F;seg17|=0x70;seg16|=0xF0;//����8
                        break;	
                    case 9:seg17&=0x8F;seg16&=0x0F;seg17|=0x70;seg16|=0xB0;//����9
                        break;
                    default:
                        break;
                }			
            }
            else
            {
                seg17&=0x8F;seg16&=0x0F;seg17|=0x00;seg16|=0x00;//����ʾ
            }
            /***********dis_set_speed��λ***********/
            Val=dis_set_speed%10;//ȡ����λ
            switch(Val)
            {
                case 0:seg19&=0x8F;seg18&=0x0F;seg19|=0x50;seg18|=0xF0;//����0
                    break;
                case 1:seg19&=0x8F;seg18&=0x0F;seg19|=0x50;seg18|=0x00;//����1
                    break;
                case 2:seg19&=0x8F;seg18&=0x0F;seg19|=0x30;seg18|=0xD0;//����2
                    break;
                case 3:seg19&=0x8F;seg18&=0x0F;seg19|=0x70;seg18|=0x90;//����3
                    break;
                case 4:seg19&=0x8F;seg18&=0x0F;seg19|=0x70;seg18|=0x20;//����4
                    break;	
                case 5:seg19&=0x8F;seg18&=0x0F;seg19|=0x60;seg18|=0xB0;//����5
                    break;
                case 6:seg19&=0x8F;seg18&=0x0F;seg19|=0x60;seg18|=0xF0;//����6
                    break;	
                case 7:seg19&=0x8F;seg18&=0x0F;seg19|=0x50;seg18|=0x10;//����7
                    break;	
                case 8:seg19&=0x8F;seg18&=0x0F;seg19|=0x70;seg18|=0xF0;//����8
                    break;	
                case 9:seg19&=0x8F;seg18&=0x0F;seg19|=0x70;seg18|=0xB0;//����9
                    break;
                default:
                    break;
            }	
        }
        else
        {		
            seg20&=0x7F;seg20|=0x00;//����ʾ
            seg20&=0x8F;seg21&=0x0F;seg20|=0x00;seg21|=0x00;//����ʾ
            seg15&=0x8F;seg14&=0x0F;seg15|=0x00;seg14|=0x00;//����ʾ
            seg17&=0x8F;seg16&=0x0F;seg17|=0x00;seg16|=0x00;//����ʾ
            seg19&=0x8F;seg18&=0x0F;seg19|=0x00;seg18|=0x00;//����ʾ
        }
        
        /***********ʵ��ת�ټ���**********/
        /***********dis_rel_speed��λ***********/
        if(dis_rel_speed > 9999)//����9999ʱ
        {
            Val=dis_rel_speed/10000;//ȡ����λ
            switch(Val)
            {
                case 0:seg12&=0xF0;seg13&=0xF1;seg12|=0x0F;seg13|=0x0A;//����0
                    break;
                case 1:seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x0A;//����1
                    break;
                case 2:seg12&=0xF0;seg13&=0xF1;seg12|=0x0D;seg13|=0x06;//����2
                    break;
                case 3:seg12&=0xF0;seg13&=0xF1;seg12|=0x09;seg13|=0x0E;//����3
                    break;	
                case 4:seg12&=0xF0;seg13&=0xF1;seg12|=0x02;seg13|=0x0E;//����4
                    break;	
                case 5:seg12&=0xF0;seg13&=0xF1;seg12|=0x0B;seg13|=0x0C;//����5
                    break;	
                case 6:seg12&=0xF0;seg13&=0xF1;seg12|=0x0F;seg13|=0x0C;//����6
                    break;	
                case 7:seg12&=0xF0;seg13&=0xF1;seg12|=0x01;seg13|=0x0A;//����7
                    break;	
                case 8:seg12&=0xF0;seg13&=0xF1;seg12|=0x0F;seg13|=0x0E;//����8
                    break;	
                case 9:seg12&=0xF0;seg13&=0xF1;seg12|=0x0B;seg13|=0x0E;//����9
                    break;
                default:
                    break;
            }
        }
        else//С��9999ʱ
        {
            seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x00;//����ʾ
        }
        /***********dis_rel_speedǧλ***********/
        if(dis_rel_speed > 999)//����999ʱ
        {
            Val=dis_rel_speed/1000;//ȡ��ǧλ
            if(dis_rel_speed > 9999)//����9999ʱ
                Val=Val%10;//ȡ��ǧλ
            switch(Val)
            {
                case 0:seg21&=0xF0;seg20&=0xF1;seg21|=0x0F;seg20|=0x0A;//����0
                    break;
                case 1:seg21&=0xF0;seg20&=0xF1;seg21|=0x00;seg20|=0x0A;//����1
                    break;
                case 2:seg21&=0xF0;seg20&=0xF1;seg21|=0x0D;seg20|=0x06;//����2
                    break;
                case 3:seg21&=0xF0;seg20&=0xF1;seg21|=0x09;seg20|=0x0E;//����3
                    break;	
                case 4:seg21&=0xF0;seg20&=0xF1;seg21|=0x02;seg20|=0x0E;//����4
                    break;	
                case 5:seg21&=0xF0;seg20&=0xF1;seg21|=0x0B;seg20|=0x0C;//����5
                    break;	
                case 6:seg21&=0xF0;seg20&=0xF1;seg21|=0x0F;seg20|=0x0C;//����6
                    break;	
                case 7:seg21&=0xF0;seg20&=0xF1;seg21|=0x01;seg20|=0x0A;//����7
                    break;
                case 8:seg21&=0xF0;seg20&=0xF1;seg21|=0x0F;seg20|=0x0E;//����8
                    break;	
                case 9:seg21&=0xF0;seg20&=0xF1;seg21|=0x0B;seg20|=0x0E;//����9
                    break;
                default:
                    break;
            }
        }
        else//С��999ʱ
        {
            seg21&=0xF0;seg20&=0xF1;seg21|=0x00;seg20|=0x00;//����ʾ
        }
        /***********dis_rel_speed��λ***********/
        if(dis_rel_speed > 99)//����99ʱ
        {
            Val=dis_rel_speed/100;//ȡ����λ
            if(dis_rel_speed > 999)//����999ʱ
                Val=Val%10;//ȡ����λ
            switch(Val)
            {
                case 0:seg14&=0xF0;seg15&=0xF1;seg14|=0x0F;seg15|=0x0A;//����0
                    break;
                case 1:seg14&=0xF0;seg15&=0xF1;seg14|=0x00;seg15|=0x0A;//����1
                    break;
                case 2:seg14&=0xF0;seg15&=0xF1;seg14|=0x0D;seg15|=0x06;//����2
                    break;
                case 3:seg14&=0xF0;seg15&=0xF1;seg14|=0x09;seg15|=0x0E;//����3
                    break;	
                case 4:seg14&=0xF0;seg15&=0xF1;seg14|=0x02;seg15|=0x0E;//����4
                    break;	
                case 5:seg14&=0xF0;seg15&=0xF1;seg14|=0x0B;seg15|=0x0C;//����5
                    break;	
                case 6:seg14&=0xF0;seg15&=0xF1;seg14|=0x0F;seg15|=0x0C;//����6
                    break;	
                case 7:seg14&=0xF0;seg15&=0xF1;seg14|=0x01;seg15|=0x0A;//����7
                    break;
                case 8:seg14&=0xF0;seg15&=0xF1;seg14|=0x0F;seg15|=0x0E;//����8
                    break;	
                case 9:seg14&=0xF0;seg15&=0xF1;seg14|=0x0B;seg15|=0x0E;//����9
                    break;
                default:
                    break;
            }
        }
        else//С��99ʱ
        {
            seg14&=0xF0;seg15&=0xF1;seg14|=0x00;seg15|=0x00;//����ʾ
        }
        /***********dis_rel_speedʮλ***********/
        if(dis_rel_speed > 9)//����9ʱ
        {
            Val=dis_rel_speed/10;//ȡ��ʮλ
            if(dis_rel_speed > 99)//����999ʱ
                Val=Val%10;//ȡ��ʮλ
            switch(Val)
            {
                case 0:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0A;//����0
                    break;
                case 1:seg16&=0xF0;seg17&=0xF1;seg16|=0x00;seg17|=0x0A;//����1
                    break;
                case 2:seg16&=0xF0;seg17&=0xF1;seg16|=0x0D;seg17|=0x06;//����2
                    break;
                case 3:seg16&=0xF0;seg17&=0xF1;seg16|=0x09;seg17|=0x0E;//����3
                    break;	
                case 4:seg16&=0xF0;seg17&=0xF1;seg16|=0x02;seg17|=0x0E;//����4
                    break;	
                case 5:seg16&=0xF0;seg17&=0xF1;seg16|=0x0B;seg17|=0x0C;//����5
                    break;	
                case 6:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0C;//����6
                    break;	
                case 7:seg16&=0xF0;seg17&=0xF1;seg16|=0x01;seg17|=0x0A;//����7
                    break;
                case 8:seg16&=0xF0;seg17&=0xF1;seg16|=0x0F;seg17|=0x0E;//����8
                    break;	
                case 9:seg16&=0xF0;seg17&=0xF1;seg16|=0x0B;seg17|=0x0E;//����9
                    break;
                default:
                    break;
            }
        }
        else//С��9ʱ
        {
            seg16&=0xF0;seg17&=0xF1;seg16|=0x00;seg17|=0x00;//����ʾ
        }
        /***********dis_rel_speed��λ***********/
        Val=dis_rel_speed%10;//ȡ����λ
        switch(Val)
        {
            case 0:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0A;//����0
                break;
            case 1:seg18&=0xF0;seg19&=0xF1;seg18|=0x00;seg19|=0x0A;//����1
                break;
            case 2:seg18&=0xF0;seg19&=0xF1;seg18|=0x0D;seg19|=0x06;//����2
                break;
            case 3:seg18&=0xF0;seg19&=0xF1;seg18|=0x09;seg19|=0x0E;//����3
                break;	
            case 4:seg18&=0xF0;seg19&=0xF1;seg18|=0x02;seg19|=0x0E;//����4
                break;	
            case 5:seg18&=0xF0;seg19&=0xF1;seg18|=0x0B;seg19|=0x0C;//����5
                break;	
            case 6:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0C;//����6
                break;	
            case 7:seg18&=0xF0;seg19&=0xF1;seg18|=0x01;seg19|=0x0A;//����7
                break;
            case 8:seg18&=0xF0;seg19&=0xF1;seg18|=0x0F;seg19|=0x0E;//����8
                break;	
            case 9:seg18&=0xF0;seg19&=0xF1;seg18|=0x0B;seg19|=0x0E;//����9
                break;
            default:
                break;
        }
        /*************xg&rpm**************/
        if(Speed.Unit)//�ٶȵ�λ
        {
            seg19&=0x7F;seg19|=0x80;//xg
        }
        else
        {
            seg17&=0x7F;seg17|=0x80;//rpm
        }
    }
    else if(sys.Run_Mode == 1)//��CGFģʽ�£��趨��ʾ��-----����ʵ���ٶ���ʾ��CGF��
    {
        seg20&=0x7F;seg20|=0x00;//����ʾ
        seg20&=0x8F;seg21&=0x0F;seg20|=0x00;seg21|=0x00;//��ʾ��-��
        seg15&=0x8F;seg14&=0x0F;seg15|=0x00;seg14|=0x00;//��ʾ��-��
        seg17&=0x8F;seg16&=0x0F;seg17|=0x00;seg16|=0x00;//��ʾ��-��
        seg19&=0x8F;seg18&=0x0F;seg19|=0x00;seg18|=0x00;//��ʾ��-��
        
        seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x00;//��ʾ��-��
        seg21&=0xF0;seg20&=0xF1;seg21|=0x0F;seg20|=0x00;//��ʾ��C��
        seg14&=0xF0;seg15&=0xF1;seg14|=0x0F;seg15|=0x0C;//��ʾ��G��
        seg16&=0xF0;seg17&=0xF1;seg16|=0x07;seg17|=0x04;//��ʾ��F��
        seg18&=0xF0;seg19&=0xF1;seg18|=0x00;seg19|=0x00;//��ʾ�� ��
        seg19&=0x7F;seg19|=0x00;//����ʾ��xg��
        seg17&=0x7F;seg17|=0x00;//����ʾ��rpm��
    }
    else if(sys.Run_Mode == 2)//��PRPģʽ�£��趨��ʾ��-----����ʵ���ٶ���ʾ��PrP��
    {
        seg20&=0x7F;seg20|=0x00;//����ʾ
        seg20&=0x8F;seg21&=0x0F;seg20|=0x00;seg21|=0x00;//��ʾ��-��
        seg15&=0x8F;seg14&=0x0F;seg15|=0x00;seg14|=0x00;//��ʾ��-��
        seg17&=0x8F;seg16&=0x0F;seg17|=0x00;seg16|=0x00;//��ʾ��-��
        seg19&=0x8F;seg18&=0x0F;seg19|=0x00;seg18|=0x00;//��ʾ��-��
        
        seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x00;//��ʾ��-��
        seg21&=0xF0;seg20&=0xF1;seg21|=0x07;seg20|=0x06;//��ʾ��P��
        seg14&=0xF0;seg15&=0xF1;seg14|=0x06;seg15|=0x04;//��ʾ��r��
        seg16&=0xF0;seg17&=0xF1;seg16|=0x07;seg17|=0x06;//��ʾ��P��
        seg18&=0xF0;seg19&=0xF1;seg18|=0x00;seg19|=0x00;//��ʾ�� ��
        seg19&=0x7F;seg19|=0x00;//����ʾ��xg��
        seg17&=0x7F;seg17|=0x00;//����ʾ��rpm��
    }
    else if(sys.Run_Mode == 3)//��APRFģʽ�£��趨��ʾ��-----����ʵ���ٶ���ʾ��APRF��
    {
        seg20&=0x7F;seg20|=0x00;//����ʾ
        seg20&=0x8F;seg21&=0x0F;seg20|=0x00;seg21|=0x00;//��ʾ��-��
        seg15&=0x8F;seg14&=0x0F;seg15|=0x00;seg14|=0x00;//��ʾ��-��
        seg17&=0x8F;seg16&=0x0F;seg17|=0x00;seg16|=0x00;//��ʾ��-��
        seg19&=0x8F;seg18&=0x0F;seg19|=0x00;seg18|=0x00;//��ʾ��-��
        
        seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x00;//��ʾ��-��
        seg21&=0xF0;seg20&=0xF1;seg21|=0x07;seg20|=0x0E;//��ʾ��A��
        seg14&=0xF0;seg15&=0xF1;seg14|=0x07;seg15|=0x06;//��ʾ��P��
        seg16&=0xF0;seg17&=0xF1;seg16|=0x06;seg17|=0x04;//��ʾ��r��
        seg18&=0xF0;seg19&=0xF1;seg18|=0x07;seg19|=0x04;//��ʾ��F��
        seg19&=0x7F;seg19|=0x00;//����ʾ��xg��
        seg17&=0x7F;seg17|=0x00;//����ʾ��rpm��
    }
    else if(sys.Run_Mode == 4)//��IPRFģʽ�£��趨��ʾ��-----����ʵ���ٶ���ʾ��IPRF��
    {
        seg20&=0x7F;seg20|=0x00;//����ʾ
        seg20&=0x8F;seg21&=0x0F;seg20|=0x00;seg21|=0x00;//��ʾ��-��
        seg15&=0x8F;seg14&=0x0F;seg15|=0x00;seg14|=0x00;//��ʾ��-��
        seg17&=0x8F;seg16&=0x0F;seg17|=0x00;seg16|=0x00;//��ʾ��-��
        seg19&=0x8F;seg18&=0x0F;seg19|=0x00;seg18|=0x00;//��ʾ��-��
        
        seg12&=0xF0;seg13&=0xF1;seg12|=0x00;seg13|=0x00;//��ʾ��-��
        seg21&=0xF0;seg20&=0xF1;seg21|=0x06;seg20|=0x00;//��ʾ��I��
        seg14&=0xF0;seg15&=0xF1;seg14|=0x07;seg15|=0x06;//��ʾ��P��
        seg16&=0xF0;seg17&=0xF1;seg16|=0x06;seg17|=0x04;//��ʾ��r��
        seg18&=0xF0;seg19&=0xF1;seg18|=0x07;seg19|=0x04;//��ʾ��F��
        seg19&=0x7F;seg19|=0x00;//����ʾ��xg��
        seg17&=0x7F;seg17|=0x00;//����ʾ��rpm��
    }
    
	/*****************���Ӵ�******************/
	if(sys.Lid_State && (Lock_ShowFlag == 0))
	{
		seg10&=0xFE;seg10|=0x01;//����
	}
	else
	{
		seg10&=0xFE;seg10|=0x00;//���ǲ���ʾ
	}
	
	/*******************************************/
	
	/*****************ת��ͼ��******************/
	switch(Speed.Icon_Step)
	{
		case 0:seg10&=0xF1;seg11&=0xF1;seg10|=0x0E;seg11|=0x0E;//����
			break;
		case 1:seg11&=0xF1;seg11|=0x06;seg10&=0xF1;seg10|=0x0C;//S5&S6&S8&S9
			break;
		case 2:seg10&=0xF1;seg11&=0xF1;seg10|=0x0A;seg11|=0x0A;//S10&S5&S7&S8
			break;
		case 3:seg11&=0xF1;seg11|=0x0C;seg10&=0xF1;seg10|=0x06;//S6&S7&S9&S10
			break;
		default:
			break;
	}
	
	/******************************************/
	
	/*************��&�Hͼ��**************/
//	seg12&=0xEF;seg12|=0x10;//���϶�
	seg13&=0xEF;seg13|=0x10;//���϶�
	/******************************************/
	
	Write_Addr_Dat_N(18, seg10,1);//SEG20
	Write_Addr_Dat_N(20, seg11,1);//SEG19
	Write_Addr_Dat_N(22, seg12,1);//SEG18
	Write_Addr_Dat_N(24, seg13,1);//SEG17
	Write_Addr_Dat_N(26, seg14,1);//SEG16
	Write_Addr_Dat_N(28, seg15,1);//SEG15
	Write_Addr_Dat_N(30, seg16,1);//SEG14
	Write_Addr_Dat_N(32, seg17,1);//SEG13
	Write_Addr_Dat_N(34, seg18,1);//SEG12
	Write_Addr_Dat_N(36, seg19,1);//SEG11
	Write_Addr_Dat_N(38, seg20,1);//SEG10
	Write_Addr_Dat_N(40, seg21,1);//SEG9
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_RunMode(uint16_t temp)
 * ��    �ܣ���ʾ��ȫ�¶Ⱥͼ���ģʽ
 * ��    ��: temp����ȫ�¶�
 * ��    ����uint16_t temp
*****************************************************************
*/
void Display_RunMode(uint16_t temp)
{
	uint8_t seg22,seg23,seg24,seg25,seg26,seg27,seg28,seg29;
	seg22=0;seg23=0;seg24=0;seg25=0;seg26=0;seg27=0;seg28=0;seg29=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	if(Temp_ShowFlag == 0)
	{
		/***********tempǧλ***********/
		if(temp > 999)//����999ʱ
		{
			Val=temp/1000;//ȡ��ǧλ
			switch(Val)
			{
				case 0:seg29&=0xF0;seg28&=0xF8;seg29|=0x0F;seg28|=0x05;//����0
					break;
				case 1:seg29&=0xF0;seg28&=0xF8;seg29|=0x00;seg28|=0x05;//����1
					break;
				case 2:seg29&=0xF0;seg28&=0xF8;seg29|=0x0D;seg28|=0x03;//����2
					break;
				case 3:seg29&=0xF0;seg28&=0xF8;seg29|=0x09;seg28|=0x07;//����3
					break;	
				case 4:seg29&=0xF0;seg28&=0xF8;seg29|=0x02;seg28|=0x07;//����4
					break;	
				case 5:seg29&=0xF0;seg28&=0xF8;seg29|=0x0B;seg28|=0x06;//����5
					break;	
				case 6:seg29&=0xF0;seg28&=0xF8;seg29|=0x0F;seg28|=0x06;//����6
					break;	
				case 7:seg29&=0xF0;seg28&=0xF8;seg29|=0x01;seg28|=0x05;//����7
					break;
				case 8:seg29&=0xF0;seg28&=0xF8;seg29|=0x0F;seg28|=0x07;//����8
					break;	
				case 9:seg29&=0xF0;seg28&=0xF8;seg29|=0x0B;seg28|=0x07;//����9
					break;
				default:
					break;
			}
		}
		else//С��999ʱ
		{
			seg29&=0xF0;seg28&=0xF8;seg29|=0x00;seg28|=0x00;//����ʾ
		}

		/***********temp��λ***********/
		if(temp > 99)//����99ʱ
		{
			Val=temp/100;//ȡ����λ
			if(temp > 999)//����999ʱ
				Val=Val%10;//ȡ����λ
			switch(Val)
			{
				case 0:seg27&=0xF0;seg26&=0xF8;seg27|=0x0F;seg26|=0x05;//����0
					break;
				case 1:seg27&=0xF0;seg26&=0xF8;seg27|=0x00;seg26|=0x05;//����1
					break;
				case 2:seg27&=0xF0;seg26&=0xF8;seg27|=0x0D;seg26|=0x03;//����2
					break;
				case 3:seg27&=0xF0;seg26&=0xF8;seg27|=0x09;seg26|=0x07;//����3
					break;	
				case 4:seg27&=0xF0;seg26&=0xF8;seg27|=0x02;seg26|=0x07;//����4
					break;	
				case 5:seg27&=0xF0;seg26&=0xF8;seg27|=0x0B;seg26|=0x06;//����5
					break;	
				case 6:seg27&=0xF0;seg26&=0xF8;seg27|=0x0F;seg26|=0x06;//����6
					break;	
				case 7:seg27&=0xF0;seg26&=0xF8;seg27|=0x01;seg26|=0x05;//����7
					break;
				case 8:seg27&=0xF0;seg26&=0xF8;seg27|=0x0F;seg26|=0x07;//����8
					break;
				case 9:seg27&=0xF0;seg26&=0xF8;seg27|=0x0B;seg26|=0x07;//����9
					break;
				default:
					break;
			}
		}
		else//С��99ʱ
		{
			seg27&=0xF0;seg26&=0xF8;seg27|=0x00;seg26|=0x00;//����ʾ
		}
		
		/***********tempʮλ***********/
		if(temp > 9)//����9ʱ
		{
			Val=temp/10;//ȡ��ʮλ
			if(temp > 99)//����999ʱ
				Val=Val%10;//ȡ��ʮλ
			switch(Val)
			{
				case 0:seg25&=0xF0;seg24&=0xF8;seg25|=0x0F;seg24|=0x05;//����0
					break;
				case 1:seg25&=0xF0;seg24&=0xF8;seg25|=0x00;seg24|=0x05;//����1
					break;
				case 2:seg25&=0xF0;seg24&=0xF8;seg25|=0x0D;seg24|=0x03;//����2
					break;
				case 3:seg25&=0xF0;seg24&=0xF8;seg25|=0x09;seg24|=0x07;//����3
					break;	
				case 4:seg25&=0xF0;seg24&=0xF8;seg25|=0x02;seg24|=0x07;//����4
					break;	
				case 5:seg25&=0xF0;seg24&=0xF8;seg25|=0x0B;seg24|=0x06;//����5
					break;	
				case 6:seg25&=0xF0;seg24&=0xF8;seg25|=0x0F;seg24|=0x06;//����6
					break;	
				case 7:seg25&=0xF0;seg24&=0xF8;seg25|=0x01;seg24|=0x05;//����7
					break;
				case 8:seg25&=0xF0;seg24&=0xF8;seg25|=0x0F;seg24|=0x07;//����8
					break;	
				case 9:seg25&=0xF0;seg24&=0xF8;seg25|=0x0B;seg24|=0x07;//����9
					break;
				default:
					break;
			}
		}
		else//С��9ʱ
		{
			seg25&=0xF0;seg24&=0xF8;seg25|=0x0F;seg24|=0x05;//����0
		}

        /***********temp��λ***********/
		Val=temp%10;//ȡ����λ
		switch(Val)
		{
			case 0:seg23&=0xF0;seg22&=0xF8;seg23|=0x0F;seg22|=0x05;//����0
				break;
			case 1:seg23&=0xF0;seg22&=0xF8;seg23|=0x00;seg22|=0x05;//����1
				break;
			case 2:seg23&=0xF0;seg22&=0xF8;seg23|=0x0D;seg22|=0x03;//����2
				break;
			case 3:seg23&=0xF0;seg22&=0xF8;seg23|=0x09;seg22|=0x07;//����3
				break;	
			case 4:seg23&=0xF0;seg22&=0xF8;seg23|=0x02;seg22|=0x07;//����4
				break;	
			case 5:seg23&=0xF0;seg22&=0xF8;seg23|=0x0B;seg22|=0x06;//����5
				break;	
			case 6:seg23&=0xF0;seg22&=0xF8;seg23|=0x0F;seg22|=0x06;//����6
				break;	
			case 7:seg23&=0xF0;seg22&=0xF8;seg23|=0x01;seg22|=0x05;//����7
				break;
			case 8:seg23&=0xF0;seg22&=0xF8;seg23|=0x0F;seg22|=0x07;//����8
				break;	
			case 9:seg23&=0xF0;seg22&=0xF8;seg23|=0x0B;seg22|=0x07;//����9
				break;
			default:
				break;
		}
	}
	else
	{
		seg25&=0xF0;seg24&=0xF8;seg25|=0x00;seg24|=0x00;//����ʾ
		seg27&=0xF0;seg26&=0xF8;seg27|=0x00;seg26|=0x00;//����ʾ
		seg29&=0xF0;seg28&=0xF8;seg29|=0x00;seg28|=0x00;//����ʾ
		seg23&=0xF0;seg22&=0xF8;seg23|=0x00;seg22|=0x00;//����ʾ
	}
	
	/*********�¶�С����*********/
	seg24&=0xF7;seg24|=0x08;
		
	/*********��ʾ"SAFE"*********/
	if(SafeTemp_ShowFlag)
	{
		seg22&=0x7F;seg22|=0x80;//��ʾ"SAFE"
	}	
	else
	{
		seg22&=0x7F;seg22|=0x00;//����ʾ
	}

    seg28&=0x0F;seg27&=0x8F;seg28|=0x00;seg27|=0x00;//C����ʾ
    seg26&=0x0F;seg25&=0x8F;seg26|=0x00;seg25|=0x00;//G����ʾ
    seg24&=0x0F;seg23&=0x8F;seg24|=0x00;seg23|=0x00;//F����ʾ
    seg29&=0x0F;seg27&=0x7F;seg26&=0xF7;seg29|=0x00;seg27|=0x00;seg26|=0x00;
    seg25&=0x7F;seg23&=0x7F;seg22&=0x87;seg25|=0x00;seg23|=0x00;seg22|=0x00;//���ȫ����
	
	/**********************************************/
	Write_Addr_Dat_N(42, seg22,1);//SEG8
	Write_Addr_Dat_N(44, seg23,1);//SEG7
	Write_Addr_Dat_N(46, seg24,1);//SEG6
	Write_Addr_Dat_N(48, seg25,1);//SEG5
	Write_Addr_Dat_N(50, seg26,1);//SEG4
	Write_Addr_Dat_N(52, seg27,1);//SEG3
	Write_Addr_Dat_N(54, seg28,1);//SEG2
	Write_Addr_Dat_N(56, seg29,1);//SEG1
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Speed(float dT)
 * ��    �ܣ��ٶ���ʾ����
*****************************************************************
*/
float Speed_Xg;
void Deal_Speed(float dT)
{
    if(sys.Run_Status == 1)//�����������
    {
        if(Speed.Unit)
        {
            Speed_Xg = 11.18f * ((float)Speed.Rel/1000.0f) * ((float)Speed.Rel/1000.0f) * 9.6f;//���㵱ǰ��ʾ���������ٶ�
        }
        else
        {
            Speed_Xg = Speed.Rel;//��ʾ�ٶ�
        }
        
        if(Speed.ADDMode == 0)//�ڵ�������У��ٶ�δ����
        {
			Speed.Display_Rel = 0;
			Speed.New =0;//���ڵ��ٶ�����
			Speed.Last = 0;//֮ǰ���ٶ�����
			Speed.ADDMode = 1;//�������ģʽ��
        }
        else if(Speed.ADDMode==1)//�ڽ������ģʽ��
        { 
            Speed.New = Speed_Xg;//��¼��ǰ�ٶ�
            if(Speed.New > Speed.Display_Rel)//��ǰ�ٶȴ�����ʾ�ٶ�
			{
				if(Speed.Display_Rel < Speed.New)
					Speed.Display_Rel += 1;//��ʾ��ǰ�ٶ�
			}
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Speed.Display_Rel = Speed.Display_Rel;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
            }  
			if(sys.Motor_Stop == 0)
			{
				if(Speed.Display_Rel >= Speed.Ctrl)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
				{
					Speed.ADDMode = 3;//�����ȶ�ģʽ
					return;
				}
			}
        }
		else if(Speed.ADDMode==2)//�ڽ������ģʽ��
        { 
			Speed.New = Speed_Xg;//��¼��ǰ�ٶ�
            
            if(Speed.New < Speed.Display_Rel)//��ǰ�ٶ�С����һ���ٶ�
			{
				if(Speed.Display_Rel > Speed.New)
					Speed.Display_Rel -= 1;//��ʾ��ǰ�ٶ�
			}
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Speed.Display_Rel = Speed.Display_Rel;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
            }
			if(sys.Motor_Stop == 0)
			{
				if(Speed.Display_Rel <= Speed.Ctrl)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
				{
					Speed.ADDMode = 3;//�����ȶ�ģʽ
					return;
				}
			}
        }
        else if(Speed.ADDMode == 3)//�ٶ��ȶ�ģʽ��
        {
            Speed.Display_Rel = Speed.Ctrl;//��ʾ�����ٶ�
        }
	}
    else
	{
		Speed.Display_Rel = 0;//û��ʼת����ʾΪ0
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Show_Display(void)
 * ��    �ܣ���ʾ��Ļ����
*****************************************************************
*/
void Show_Display(void)
{	
    Time.Display_Rel = Time.Rel;
    Time.Display_Set = Time.Set;
    Speed.Display_Set = Speed.Set;
    if(sys.SetMode_Option == 3)
	{
		SafeTemp.Display = SafeTemp.Set;
	}
	else
	{
		SafeTemp.Display = SafeTemp.Rel;
	}
    
    
    Display_Time(Time.Display_Set,Time.Display_Rel);
    Display_Speed(Speed.Display_Set,Speed.Display_Rel);
    Display_RunMode(SafeTemp.Display);
}
