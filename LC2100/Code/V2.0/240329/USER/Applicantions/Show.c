#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Time_ShowFlag,Speed_ShowFlag;//ʱ�䡢�ٶ���ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t Lock_ShowFlag,TimeIcn_ShowFlag,SpeedIcn_ShowFlag;//����ͼ���ʱ��ͼ����˸���ٶȵ�λͼ����˸
uint8_t Tab[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x6F};//0��9

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
			if(sys.SetMode_Option == 1)//����ʱ�ٶ�
			{
				Speed_ShowFlag = ~Speed_ShowFlag;//�ٶȳ���
				Time_ShowFlag = 0;//ʱ�䳣��
			}
			else if(sys.SetMode_Option == 2)//����ʱ��
			{
				Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
				Speed_ShowFlag = 0;//�ٶȳ���			
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
        Time_ShowFlag = 0;//����
		T = 0;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Time_Twinkle(float dT)
 * ��    �ܣ�ʱ��ͼ����˸
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status)
	{
		T += dT;
		if(T >= 0.5f)
		{
			TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//ʱ��ͼ����˸;
			SpeedIcn_ShowFlag = ~SpeedIcn_ShowFlag;//�ٶ�ͼ����˸;
			T = 0;
		}
	}
	else
	{
		TimeIcn_ShowFlag = 0;//��ʾʱ��ͼ��
		SpeedIcn_ShowFlag = 0;//��ʾ�ٶ�ͼ��;
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
	if(HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1)//�����1�͵����2���պ�ʱ
		sys.Lock_On = 0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Twinkle(float dT)
 * ��    �ܣ���˸����
*****************************************************************
*/
void Twinkle(float dT)
{
	Check_ShowFlag(dT);//��˸���
	Icn_Twinkle(dT);//ͼ����˸
	Check_Lock(dT);//����ͼ����˸
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display(int16_t speed,int32_t time)
 * ��    �ܣ���ʾ�ٶȺ�ʱ��
*****************************************************************
*/
void Display(int16_t speed,int32_t time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
	
	/***********�趨ת�ټ���**********/
	if(Speed_ShowFlag == 0)//����ʱ��˸
	{
		/***********speedǧλ***********/
		if(speed > 999)//����999ʱ
		{
			Val = speed/1000;//ȡ��ǧλ
			seg1&=0x80;seg1|=Tab[Val];//����		
		}
		else
		{
			seg1&=0x80;seg1|=0x00;//����ʾ
		}

		/***********speed��λ***********/
		if(speed > 99)//����99ʱ
		{
			Val=speed/100;//ȡ����λ
			if(speed > 999)//����999ʱ
				Val=Val%10;//ȡ����λ
			seg2&=0x80;seg2|=Tab[Val];//����	
		}
		else
		{
			seg2&=0x80;seg2|=0x00;//����ʾ
		}
		/***********speedʮλ***********/
		if(speed > 9)//����9ʱ
		{
			Val=speed/10;//ȡ��ʮλ
			if(speed > 99)//����99ʱ
				Val=Val%10;//ȡ��ʮλ
			seg3&=0x80;seg3|=Tab[Val];//����	
		}
		else
		{
			seg3&=0x80;seg3|=0x00;//����ʾ
		}
		
		/***********speed��λ***********/
		Val=speed%10;//ȡ����λ
		seg4&=0x80;seg4|=Tab[Val];//����
	}
	else//����ʾ
	{
		seg1&=0x80;seg1|=0x00;//����ʾ
		seg2&=0x80;seg2|=0x00;//����ʾ
		seg3&=0x80;seg3|=0x00;//����ʾ
		seg4&=0x80;seg4|=0x00;//����ʾ
	}
	
	/***********ʱ�����**********/
	SH=time%3600/60/10;//����ʮλ��λ�ķ�����
	H=time%3600/60%10;//�����λ��λ�ķ�����
	SM=time%60/10;//����ʮ��λ��λ��������
	M=time%60%10;//����ʮ��λ��λ��������
	
	if(Time_ShowFlag == 0)//ʱ������ʱ��˸
	{
		if(Time.Set > 0)//����ʱ�������ʱ��ʾʱ��
		{
			/***********set_timeʮСʱλ***********/
			seg5&=0x80;seg5|=Tab[SH];//����	
		
			/***********set_timeСʱλ***********/
			seg6&=0x80;seg6|=Tab[H];//����	
			
			/***********set_timeʮ��λ***********/
			seg7&=0x80;seg7|=Tab[SM%10];//����	
			
			/***********set_time��λ***********/
			seg8&=0x80;seg8|=Tab[M%10];//����		
		}
		else//����ʱ��С�ڵ���0ʱ��ʾ��-- --��
		{
			seg5&=0x80;seg5|=0x08;//"-"
			seg6&=0x80;seg6|=0x08;//"-"
			seg7&=0x80;seg7|=0x08;//"-"
			seg8&=0x80;seg8|=0x08;//"-"
		}	
	}
	else//ʱ����˸
	{
		seg5&=0x80;seg5|=0x00;//����ʾ
		seg6&=0x80;seg6|=0x00;//����ʾ
		seg7&=0x80;seg7|=0x00;//����ʾ
		seg8&=0x80;seg8|=0x00;//����ʾ
	}
	/*************xg&rpm*********************/
	if(SpeedIcn_ShowFlag == 0)//�ٶȵ�λ��˸
	{
		if(Speed.Unit)
		{
			seg5&=0x7F;seg5|=0x80;//��ʾxg
		}
		else
		{
			seg4&=0x7F;seg4|=0x80;//��ʾrpm
		}
	}
	else
	{
		seg4&=0x7F;seg4|=0x00;//����ʾrpm
		seg5&=0x7F;seg5|=0x00;//����ʾxg
	}
	/*************ʱ��ð��ͼ��***************/
	if(TimeIcn_ShowFlag == 0)//ʱ��ð����˸
	{
		seg6&=0x7F;seg6|=0x80;//��ʾʱ��ð��
		seg7&=0x7F;seg7|=0x80;//��ʾsec
	}
	else
	{
		seg6&=0x7F;seg6|=0x00;//����ʾʱ��ð��
		seg7&=0x7F;seg7|=0x00;//��ʾsec
	}
	/*************ʱ�䵥λͼ��***************/
	seg7&=0x7F;seg7|=0x80;//��ʾsec
	
	/*************���ǹظ�ͼ��***************/
	if(Lid_State == 0)
	{
		seg2&=0x7F;seg2|=0x80;//��ʾ�ײ�����
		seg3&=0x7F;seg3|=0x80;//��ʾ�ظ�
	}
	else
	{
		if(Lock_ShowFlag == 0)//���ӵײ�
		{
			seg1&=0x7F;seg1|=0x80;//��ʾ����
			seg2&=0x7F;seg2|=0x80;//��ʾ���ӵײ�
		}
		else
		{
			seg1&=0x7F;seg1|=0x00;//����ʾ����
			seg2&=0x7F;seg2|=0x00;//����ʾ���ӵײ�
		}
	}
	
	Write_Addr_Dat_N(0,seg1,1);//SEG9
	Write_Addr_Dat_N(2,seg2,1);//SEG10
	Write_Addr_Dat_N(4,seg3,1);//SEG11
	Write_Addr_Dat_N(6,seg4,1);//SEG12
	Write_Addr_Dat_N(8,seg5,1);//SEG13
	Write_Addr_Dat_N(10,seg6,1);//SEG14
	Write_Addr_Dat_N(12,seg7,1);//SEG15
	Write_Addr_Dat_N(14,seg8,1);//SEG16
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
            Speed_Xg = 11.18f * ((float)Speed.Rel/1000.0f) * ((float)Speed.Rel/1000.0f) * 9.6f;
        }
        else
        {
            Speed_Xg = Speed.Rel;
        }
        
        if(Speed.ADDMode == 0)//�ڵ�������У��ٶ�δ����
        {
			Speed.Display = 0;
			Speed.New =0;//���ڵ��ٶ�����
			Speed.Last = 0;//֮ǰ���ٶ�����
			Speed.ADDMode = 1;//�������ģʽ��
        }
        else if(Speed.ADDMode==1)//�ڽ������ģʽ��
        { 
            Speed.New = Speed_Xg;//��¼��ǰ�ٶ�
            if(Speed.New > Speed.Display)//��ǰ�ٶȴ�����ʾ�ٶ�
			{
				if(Speed.Display < Speed.New)
//                    Speed.Display = Speed.New;//��ʾ��ǰ�ٶ�
					Speed.Display += 1;//��ʾ��ǰ�ٶ�
			}
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Speed.Display = Speed.Display;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
            }  
			if(sys.Motor_Stop == 0)
			{
				if(Speed.Display >= Speed.Ctrl)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
				{
					Speed.ADDMode = 3;//�����ȶ�ģʽ
					return;
				}
			}
        }
		else if(Speed.ADDMode==2)//�ڽ������ģʽ��
        { 
			Speed.New = Speed_Xg;//��¼��ǰ�ٶ�
            
            if(Speed.New < Speed.Display)//��ǰ�ٶ�С����һ���ٶ�
			{
				if(Speed.Display > Speed.New)
					Speed.Display -= 1;//��ʾ��ǰ�ٶ�
//                    Speed.Display = Speed.New;//��ʾ��ǰ�ٶ�
			}
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Speed.Display = Speed.Display;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
            }
			if(sys.Motor_Stop == 0)
			{
				if(Speed.Display <= Speed.Ctrl)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
				{
					Speed.ADDMode = 3;//�����ȶ�ģʽ
					return;
				}
			}
        }
        else if(Speed.ADDMode == 3)//�ٶ��ȶ�ģʽ��
        {
            Speed.Display = Speed.Ctrl;//��ʾ�����ٶ�
        }
	}
	else
	{
		Speed.Display = Speed.Set;
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
	if(sys.Run_Status == 0)
	{
		Time.Display = Time.Set;
	}
	else
	{
		Time.Display = Time.Ctrl;
	}
	Display(Speed.Display,Time.Display);//��ʾ�ٶȺ�ʱ��
}
