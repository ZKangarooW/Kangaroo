#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};//0��9
uint8_t HeatTemp_ShowFlag,CoolTemp_ShowFlag,Time_ShowFlag;//�����¶���˸,�����¶���˸��ʱ����˸
uint8_t HeatTemp_XSDFlag,CoolTemp_XSDFlag;//������С������˸������С������˸

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
	if(sys.Calibration)
	{
		if(T == 0)
		{
			T += dT;
			if(sys.SetMode_Option == 4)//����CoolTempʱ
			{
				HeatTemp_ShowFlag = 0;//�����¶ȳ���
				CoolTemp_ShowFlag = !CoolTemp_ShowFlag;//�����¶���˸
				Time_ShowFlag = 0;//ʱ�䳣��
			}
		}
		else
		{
			T += dT;
			if(T >=0.5f)
				T = 0;	
		}
	}
	else
	{
		if(LongPress == 1)
		{
			if(sys.SetMode_Option == 1)//����HeatTempʱ
			{
				HeatTemp_ShowFlag = 1;//�����¶ȳ���
				CoolTemp_ShowFlag = 0;//�����¶ȳ���
				Time_ShowFlag = 0;//ʱ�䳣��
			}
			else if(sys.SetMode_Option == 2)//����CoolTempʱ
			{
				HeatTemp_ShowFlag = 0;//�����¶ȳ���
				CoolTemp_ShowFlag = 1;//�����¶ȳ���
				Time_ShowFlag = 0;//ʱ�䳣��
			}
			else if(sys.SetMode_Option == 3)//����CoolTempʱ
			{
				HeatTemp_ShowFlag = 0;//�����¶ȳ���
				CoolTemp_ShowFlag = 0;//�����¶ȳ���
				Time_ShowFlag = 1;//ʱ�䳣��
			}
			return;
		}
		if(Twinkle_Time && Key_Status==0)//��˸��û�в�������ʱ
		{
			if(T == 0)
			{
				T += dT;
				Twinkle_Time -= 0.5;//��˸��ʱ
				if(Twinkle_Time == 0)//�����˸����
				{
					sys.TempOption_Mun = 0;//�¶�����λ����λ
					sys.TimeOption_Mun = 0;//ʱ������λ����λ
					sys.SetMode_Option = 0;//ģʽѡ������
				} 
				if(sys.SetMode_Option == 1)//����HeatTempʱ
				{
					HeatTemp_ShowFlag = !HeatTemp_ShowFlag;//�����¶���˸
					CoolTemp_ShowFlag = 0;//�����¶ȳ���
					Time_ShowFlag = 0;//ʱ�䳣��
				}
				else if(sys.SetMode_Option == 2)//����CoolTempʱ
				{
					HeatTemp_ShowFlag = 0;//�����¶ȳ���
					CoolTemp_ShowFlag = !CoolTemp_ShowFlag;//�����¶���˸
					Time_ShowFlag = 0;//ʱ�䳣��
				}
				else if(sys.SetMode_Option == 3)//����Timeʱ
				{
					HeatTemp_ShowFlag = 0;//�����¶ȳ���
					CoolTemp_ShowFlag = 0;//�����¶ȳ���
					Time_ShowFlag = !Time_ShowFlag;//ʱ����˸
				}
			}
			else
			{
				T += dT;
				if(T >=0.5f)
					T = 0;	
			}
		}
		else
		{
			HeatTemp_ShowFlag = 0;//�����¶ȳ���
			CoolTemp_ShowFlag = 0;//�����¶ȳ���
			Time_ShowFlag = 0;//ʱ�䳣��
			T = 0;
		}
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Heating_Twinkle(float dT)
 * ��    �ܣ�С������˸���
 * ��    ��: dT:ִ������
 * ��    ����float dT
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Heating_Twinkle(float dT)
{
	static float T,T1;
	if(Heat_Temp.ADDMode == 0)
	{
		T += dT;
		if(T >= 0.5f)
		{
			T = 0;
			HeatTemp_XSDFlag = !HeatTemp_XSDFlag;//������С������˸
		}
	}
	else
	{
		T = 0;
		HeatTemp_XSDFlag = 0;//����
	}
	
	if(Cool_Temp.ADDMode == 0)
	{
		T1 += dT;
		if(T1 >= 0.5f)
		{
			T1 = 0;
			CoolTemp_XSDFlag = !CoolTemp_XSDFlag;//������С������˸
		}
	}
	else
	{
		T1 = 0;
		CoolTemp_XSDFlag = 0;//����
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
	Check_ShowFlag(dT);//��˸���
	Heating_Twinkle(dT);//С������˸
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_HeatTemp(int16_t temp)
 * ��    �ܣ���ʾ���������¶�
 * ��    ��: temp������������¶�
 * ��    ����int16_t temp
*****************************************************************
*/
void Display_HeatTemp(int16_t temp)
{
	uint8_t seg1,seg2,seg3;
	seg1=0;seg2=0;seg3=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	if(temp >= 0)
	{
		/***********temp��λ***********/
		if(sys.TempOption_Mun == 1 && HeatTemp_ShowFlag)//������λ��Ϊ��λ�����¶�����˸
			seg1 = 0x00;//����ʾ
		else
		{
			if(temp > 99)//����99ʱ
			{
				Val=temp/100;//ȡ����λ
				if(temp > 999)//����999ʱ
					Val=Val%10;//ȡ����λ
				seg1 = Tab[Val];
			}
		}
		
		/***********tempʮλ***********/
		if(sys.TempOption_Mun == 0 && HeatTemp_ShowFlag)//������λ��Ϊʮλ�����¶�����˸
			seg2 = 0x00;//����ʾ
		else
		{
			if(temp > 9)//����9ʱ
			{
				Val=temp/10;//ȡ��ʮλ
				if(temp > 99)//����999ʱ
					Val=Val%10;//ȡ��ʮλ
				seg2 = Tab[Val];
			}
		}
		
		/***********tempС��λ***********/
		if(sys.TempOption_Mun == 2 && HeatTemp_ShowFlag)//������λ��ΪС��λ�����¶�����˸
			seg3 = 0x00;//����ʾ
		else
		{
			Val=temp%10;//ȡ����λ
			seg3 = Tab[Val];
		}
	}
	else
	{
		/***********temp����***********/
		seg1 = 0x40;
		
		/***********tempʮλ***********/
		if((-temp) > 9)//����9ʱ
		{
			Val=(-temp)/10;//ȡ��ʮλ
			if((-temp) > 99)//����999ʱ
				Val=Val%10;//ȡ��ʮλ
			seg2 = Tab[Val];
		}
		
		/***********tempС��λ***********/
		Val=(-temp)%10;//ȡ����λ
		seg3 = Tab[Val];
	}
	
	/***********tempС����*********/
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3 || sys.SetMode_Option == 4) && HeatTemp_XSDFlag)//�����ڼ��ȵ�����£�����С������˸
	{
		seg2&=0x7F;seg2|=0x00;//����ʾ
	}
	else
	{
		seg2&=0x7F;seg2|=0x80;
	}
	
	/************************************/
	GN1640_Write_DATA(0, seg1);
	GN1640_Write_DATA(1, seg2);
	GN1640_Write_DATA(2, seg3);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_CoolTemp(int16_t temp)
 * ��    �ܣ���ʾ���������¶�
 * ��    ��: temp������������¶�
 * ��    ����int16_t temp
*****************************************************************
*/
void Display_CoolTemp(int16_t temp)
{
	uint8_t seg1,seg2,seg3;
	seg1=0;seg2=0;seg3=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	if(temp >= 0)
	{
		/***********temp��λ***********/
		if(sys.TempOption_Mun == 1 && CoolTemp_ShowFlag)//������λ��Ϊ��λ�����¶�����˸
			seg1 = 0x00;//����ʾ
		else
		{
			if(temp > 99)//����99ʱ
			{
				Val=temp/100;//ȡ����λ
				if(temp > 999)//����999ʱ
					Val=Val%10;//ȡ����λ
				seg1 = Tab[Val];
			}
		}
		
		/***********tempʮλ***********/
		if(sys.TempOption_Mun == 0 && CoolTemp_ShowFlag)//������λ��Ϊʮλ�����¶�����˸
			seg2 = 0x00;//����ʾ
		else
		{
			if(temp > 9)//����9ʱ
			{
				Val=temp/10;//ȡ��ʮλ
				if(temp > 99)//����999ʱ
					Val=Val%10;//ȡ��ʮλ
				seg2 = Tab[Val];
			}
		}
		
		/***********tempС��λ***********/
		if(sys.TempOption_Mun == 2 && CoolTemp_ShowFlag)//������λ��ΪС��λ�����¶�����˸
			seg3 = 0x00;//����ʾ
		else
		{
			Val=temp%10;//ȡ����λ
			seg3 = Tab[Val];
		}
	}
	else
	{
		/***********temp��λ***********/
		seg1 = 0x40;
		
		/***********tempʮλ***********/
		if((-temp) > 9)//����9ʱ
		{
			Val=(-temp)/10;//ȡ��ʮλ
			if((-temp) > 99)//����999ʱ
				Val=Val%10;//ȡ��ʮλ
			seg2 = Tab[Val];
		}
		
		/***********tempС��λ***********/
		Val=(-temp)%10;//ȡ����λ
		seg3 = Tab[Val];
	}

	/***********tempС����*********/
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && CoolTemp_XSDFlag)//�����ڼ��ȵ�����£�����С������˸
	{
		seg2&=0x7F;seg2|=0x00;//����ʾ
	}
	else
	{
		seg2&=0x7F;seg2|=0x80;
	}

	/************************************/
	GN1640_Write_DATA(3, seg1);
	GN1640_Write_DATA(4, seg2);
	GN1640_Write_DATA(5, seg3);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Time(uint8_t flag,int16_t time)
 * ��    �ܣ���ʾʱ��
 * ��    ��: flag���Ƿ���У׼���� time��ʱ��
 * ��    ����uint8_t flag,int16_t time
*****************************************************************
*/
void Display_Time(uint8_t flag,int16_t time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint8_t SM,M,SS,S;//ʱ��ĵ�λȡֵ
	
	if(flag)
	{
		seg1 = 0x77;//A
		seg2 = 0x5E;//d
		seg3 = 0x0E;//j
		seg4 = 0x78;//t
	}
	else
	{
		/***********�趨ʱ��***********/
		SM=time/60/10;//����ʮλ��λ�ķ�����
		M=time/60%10;//�����λ��λ�ķ�����
		SS=time%60/10;//����ʮ��λ��λ��������
		S=time%60%10;//����ʮ��λ��λ��������
		
		/***********ʮ��ʱ��***********/
		if(sys.TimeOption_Mun == 1 && Time_ShowFlag)//������λ��Ϊʮ�ֲ���ʱ������˸
			seg1 = 0x00;//����ʾ
		else
		{
			seg1 = Tab[SM];
		}
		
		/***********����ʱ��***********/
		if(sys.TimeOption_Mun == 0 && Time_ShowFlag)//������λ��Ϊ�ֲ���ʱ������˸
			seg2 = 0x00;//����ʾ
		else
		{
			seg2 = Tab[M];
		}
		
		/***********ʮ��ʱ��***********/
		if(sys.TimeOption_Mun == 3 && Time_ShowFlag)//������λ��Ϊʮ��ֲ���ʱ������˸
			seg3 = 0x00;//����ʾ
		else
		{
			seg3 = Tab[SS];
		}
		/***********����ʱ��***********/
		if(sys.TimeOption_Mun == 2 && Time_ShowFlag)//������λ��Ϊ�벢��ʱ������˸
			seg4 = 0x00;//����ʾ
		else
		{
			seg4 = Tab[S];
		}
		
		/***********timeð��***********/
		seg2&=0x7F;seg2|=0x80;
	}

	/************************************/
	GN1640_Write_DATA(6, seg1);
	GN1640_Write_DATA(7, seg2);
	GN1640_Write_DATA(8, seg3);
	GN1640_Write_DATA(9, seg4);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Temp(float dT)
 * ��    �ܣ��¶ȴ���
*****************************************************************
*/
void Deal_Temp(float dT)
{
	static float T,T1;
    if(ABS(Heat_Temp.Rel_Temp - Heat_Temp.Ctrl_Temp)<=1)
    {
        if(!Heat_Temp.ADDMode)
            T += dT;
        if(T >= 2.0f)
        {
            T = 0;
            Heat_Temp.ADDMode = 1;
        }
    }
    else if(Heat_Temp.Ctrl_Temp - Heat_Temp.Rel_Temp > 5 || Heat_Temp.Ctrl_Temp - Heat_Temp.Rel_Temp < -5 )
    {
        if(Heat_Temp.ADDMode)
            T += dT;
        if(T >= 2.0f)
        {
            T = 0;
            Heat_Temp.ADDMode = 0;
        }
    }

	if(sys.Calibration)
	{
		if(sys.Calibration_Step == 0)
		{
			if(ABS(Cool_Temp.Rel_Temp - 260)<=1)
			{
				if(!Cool_Temp.ADDMode)
					T += dT;
				if(T >= 2.0f)
				{
					T = 0;
					Cool_Temp.ADDMode = 1;
				}
			}
			else if(260 - Cool_Temp.Rel_Temp > 5 || 260 - Cool_Temp.Rel_Temp < -5 )
			{
				if(Cool_Temp.ADDMode)
					T += dT;
				if(T >= 2.0f)
				{
					T = 0;
					Cool_Temp.ADDMode = 0;
				}
			}
		}
		else
		{
			if(ABS(Cool_Temp.Rel_Temp - 400)<=1)
			{
				if(!Cool_Temp.ADDMode)
					T += dT;
				if(T >= 2.0f)
				{
					T = 0;
					Cool_Temp.ADDMode = 1;
				}
			}
			else if(400 - Cool_Temp.Rel_Temp > 5 || 400 - Cool_Temp.Rel_Temp < -5 )
			{
				if(Cool_Temp.ADDMode)
					T += dT;
				if(T >= 2.0f)
				{
					T = 0;
					Cool_Temp.ADDMode = 0;
				}
			}
		}
	}
	else
	{
        if(ABS(Cool_Temp.Rel_Temp - Cool_Temp.Ctrl_Temp)<=1)
        {
            if(!Cool_Temp.ADDMode)
                T1 += dT;
            if(T1 >= 2.0f)
            {
                T1= 0;
                Cool_Temp.ADDMode = 1;
            }
        }
        else if(Cool_Temp.Ctrl_Temp - Cool_Temp.Rel_Temp > 8 || Cool_Temp.Ctrl_Temp - Cool_Temp.Rel_Temp < -8 )
        {
            if(Cool_Temp.ADDMode)
                T1 += dT;
            if(T1 >= 2.0f)
            {
                T1= 0;
                Cool_Temp.ADDMode = 0;
            }
        }
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Show_Display(void)
 * ��    �ܣ� ��ʾ��Ļ����
*****************************************************************
*/
void Show_Display(void)
{	
	static uint8_t flag = 0;
	
	if(sys.SetMode_Option >0 && sys.SetMode_Option < 3 && sys.Calibration==0)
	{
		Heat_Temp.Display_Temp = Heat_Temp.Set_Temp;
		Cool_Temp.Display_Temp = Cool_Temp.Set_Temp;
	}
	else
	{
		if(sys.Calibration)
		{
			if(Cool_Temp.ADDMode == 0)
				Heat_Temp.Display_Temp = Cool_Temp.Rel_Temp;
			else
			{
				if(sys.Calibration_Step == 0)
					Heat_Temp.Display_Temp = 260;
				else
					Heat_Temp.Display_Temp = 400;
			}
			
			if(sys.Calibration_Step == 0)
				Cool_Temp.Display_Temp = sys.Calibration_Temp1;
			else if(sys.Calibration_Step == 1)
				Cool_Temp.Display_Temp = sys.Calibration_Temp2;
		}
		else
		{
			if(Heat_Temp.ADDMode == 0)
				Heat_Temp.Display_Temp = Heat_Temp.Rel_Temp;
			else
				Heat_Temp.Display_Temp = Heat_Temp.Ctrl_Temp;
			
			if(Cool_Temp.ADDMode == 0)
				Cool_Temp.Display_Temp = Cool_Temp.Rel_Temp;
			else
				Cool_Temp.Display_Temp = Cool_Temp.Ctrl_Temp;
		}
	}

	if(Time.TimeDisplay_Flag)//����ʱ
	{
		Time.Display_Time = Time.Count_Time;
	}
	else//����ʱ
	{
		if(sys.SetMode_Option == 3)
			Time.Display_Time = Time.Set_Time;
		else
			Time.Display_Time = Time.Ctrl_Time;
		if(sys.Calibration)
			flag = 1;
		else
			flag = 0;
	}
	Display_HeatTemp(Heat_Temp.Display_Temp);
	Display_CoolTemp(Cool_Temp.Display_Temp);
	Display_Time(flag,Time.Display_Time);
}
