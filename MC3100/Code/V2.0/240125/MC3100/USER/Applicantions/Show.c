#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Time_ShowFlag,Speed_ShowFlag,Lock_ShowFlag;//ʱ�䡢�ٶ���ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t TimeIcn_ShowFlag;//ʱ��ͼ����˸
uint8_t Tab[] = {0x5F,0x06,0x3D,0x2F,0x66,0x6B,0x7B,0x0E,0x7F,0x6F};//0��9

/*
*****************************************************************
 * ����ԭ�ͣ�static void Check_Lock(float dT)
 * ��    �ܣ�����ͼ����˸���
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Check_Lock(float dT)
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
	if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)== 1)//������պ�ʱ
		sys.Lock_On = 0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Check_ShowFlag(float dT)
 * ��    �ܣ���˸���
 * ��    ��: dT:ִ������
 * ��    ����float dT
*****************************************************************
*/
static void Check_ShowFlag(float dT)
{
	static float T,T1;
    if(sys.Run_Status == 1)//ϵͳ������
	{
		T1 += dT;//��˸��ʱ
		if(T1 >= 0.5f)//����0.5S��
		{
			TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//������˸
			T1 = 0;//��ʱ����
		}
	}
    else//û�����������
	{
        TimeIcn_ShowFlag = 0;//ʱ��ð��ͼ�곣��
		T1 = 0;//��ʱ����
	}
    if(sys.SetMode_Option == 0 || Key_Status)//���û������ѡ���л��߰���������£��򶼵���������˸
    {
        Speed_ShowFlag = 0;//����
        Time_ShowFlag = 0;//����
		T = 0;//��ʱ����
        return;
    }
    if(Twinkle_Time && Key_Status==0)//��˸��û�в�����ťʱ
    {
        T += dT;//��˸��ʱ
		if(T >= 0.5f)//����0.5S��
		{
			Twinkle_Time -= 0.5;//��˸��ʱ
			if(sys.SetMode_Option == 1)//�����ٶ�
			{
				Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
				Time_ShowFlag = 0;//ʱ�䳣��
			}
			else if(sys.SetMode_Option == 2)//����ʱ��
			{
				Speed_ShowFlag = 0;//�ٶȳ���
				Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
			}
			if(Twinkle_Time == 0)//�����˸����
			{
				sys.SetMode_Option = 0;//ģʽѡ������
			}  
			T = 0;//��ʱ����		
		}		
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
	Check_Lock(dT);//����ͼ����˸���
	Check_ShowFlag(dT);//��˸���
}


/*
*****************************************************************
 * ����ԭ�ͣ� void Display(int16_t speed,int32_t time)
 * ��    �ܣ� ��ʾ�ٶȺ�ʱ��
*****************************************************************
*/
void Display(int16_t speed,int32_t time)
{
	uint8_t seg,seg1,seg2,seg3,seg4,seg5,seg6;
	seg = 0;seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	uint8_t SM,M;//ʱ��ĵ�λȡֵ
	
	/***********�趨ת�ټ���**********/
	if(Speed_ShowFlag == 0)//����ʱ��˸
	{
		/***********speed��λ***********/
		if(speed > 99)//����99ʱ
		{
			Val=speed/100;//ȡ����λ
			if(speed > 999)//����999ʱ
				Val=Val%10;//ȡ����λ
			seg1&=0x80;seg1|=Tab[Val];//����	
		}
		else
		{
			seg1&=0x80;seg1|=0x00;//����ʾ
		}
		/***********speedʮλ***********/
		if(speed > 9)//����9ʱ
		{
			Val=speed/10;//ȡ��ʮλ
			if(speed > 99)//����99ʱ
				Val=Val%10;//ȡ��ʮλ
			seg2&=0x80;seg2|=Tab[Val];//����	
		}
		else
		{
			seg2&=0x80;seg2|=0x00;//����ʾ
		}
		
		/***********speed��λ***********/
		Val=speed%10;//ȡ����λ
		seg3&=0x80;seg3|=Tab[Val];//����
	}
	else//����ʾ
	{
		seg1&=0x80;seg1|=0x00;//����ʾ
		seg2&=0x80;seg2|=0x00;//����ʾ
		seg3&=0x80;seg3|=0x00;//����ʾ
	}
	
	/***********ʱ�����**********/
	if(time >= 60)//����趨ʱ�����60��ʱ
        Time.Time_Unit=1;//��λ��ɷ�
    else
        Time.Time_Unit=0;//��Ȼ������
	
	if(Time.Time_Unit == 1)//ʱ�䵥λΪ����ʱ
	{
		SM=time/60/10;//����ʮλ��λ�ķ�����
		M=time/60%10;//�����λ��λ�ķ�����
	}
	else//ʱ�䵥λΪ��ʱ
	{
		SM=time%60/10;//����ʮ��λ��λ��������
		M=time%60%10;//����ʮ��λ��λ��������
	}
	
	if(Time_ShowFlag == 0)//ʱ������ʱ��˸
	{
		/***********set_time��һλ***********/
		seg4&=0x80;seg4|=Tab[SM];//����	
	
		/***********set_time�ڶ�λ***********/
		seg&=0x80;seg|=Tab[M];//����			
	}
	else//ʱ����˸
	{
		seg4&=0x80;seg4|=0x00;//����ʾ
		seg&=0x80;seg|=0x00;//����ʾ
	}
	
	/*************���ݲ��*******************/
	seg5 = seg&0xF0;
	seg6 = (seg<<4)&0XF0;
	
	/*************xg&rpm*********************/
	if(TimeIcn_ShowFlag == 0)//ת�ٵ�λͼ����˸
	{
		if(Speed.Speed_Unit)
		{
			seg1&=0x7F;seg1|=0x80;//��ʾrcf
		}
		else
		{
			seg4&=0x7F;seg4|=0x80;//��ʾrpm
		}
	}
	else
	{
		seg1&=0x7F;seg1|=0x00;//����ʾrcf
		seg4&=0x7F;seg4|=0x00;//����ʾrpm
	}
	
	/*************ʱ�䵥λͼ��***************/
	if(TimeIcn_ShowFlag == 0)//ʱ�䵥λͼ����˸
	{
		if(Time.Time_Unit)//ʱ�䵥λΪ����ʱ
		{
			seg5&=0xF5;seg5|=0x08;//��ʾmin
		}
		else//ʱ�䵥λΪ��ʱ
		{
			seg5&=0xF5;seg5|=0x01;//��ʾsec
		}
	}
	else
	{
		seg5&=0xF5;seg5|=0x00;//����ʾʱ�䵥λͼ��
	}
	
	/*************����ͼ��*******************/
	if(Lock_ShowFlag == 0)
	{
		if(Lock_Status)
		{
			seg2&=0x7F;seg2|=0x80;//����ͼ��
		}
		else
		{
			seg3&=0x7F;seg3|=0x80;//�ظ�ͼ��
		}
		seg5&=0x7F;seg5|=0x80;//���ӵײ�ͼ��
	}
	else
	{
		seg2&=0x7F;seg2|=0x00;//����ͼ��
		seg3&=0x7F;seg3|=0x00;//�ظ�ͼ��
		seg5&=0x7F;seg5|=0x00;//���ӵײ�ͼ��
	}
	
	Write_Addr_Dat_N(0,seg1,1);//SEG9
	Write_Addr_Dat_N(2,seg2,1);//SEG10
	Write_Addr_Dat_N(4,seg3,1);//SEG11
	Write_Addr_Dat_N(6,seg4,1);//SEG12
	Write_Addr_Dat_N(8,seg5,1);//SEG13
	Write_Addr_Dat_N(10,seg6,1);//SEG14
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Show_Display(void)
 * ��    �ܣ� ��ʾ��Ļ����
*****************************************************************
*/
void Show_Display(void)
{	
	if(sys.Run_Status == 0)//������
    {
		if(Speed.Rel_Speed)
		{
			Speed.Display_Speed  = Speed.Rel_Speed;//��ʾʵ���ٶ�
            Time.Display_Time = Time.Set_Time; //��ʾ�趨ʱ�� 
		}
		else
		{
			Speed.Display_Speed  = Speed.Set_Speed;//��ʾ�趨�ٶ�
			Time.Display_Time  = Time.Set_Time;//��ʾ�趨ʱ��
		}
    }
    else//������
    {
		Speed.Display_Speed  = Speed.Rel_Speed;//��ʾʵ���ٶ�
		Time.Display_Time = Time.Ctrl_Time;//��ʾʵ��ʱ��
    }
	Display(Speed.Display_Speed/10,Time.Display_Time);//��ʾ��Ļ
}
