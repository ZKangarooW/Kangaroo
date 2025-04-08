#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Time_ShowFlag,Speed_ShowFlag,Temp_ShowFlag;//ʱ�䡢�ٶȡ��¶���ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t Protect_ShowFlag;//������ͼ��
uint8_t Tab[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x6F};//0��9
uint8_t Tab1[] = {0x77,0x12,0x5D,0x5B,0x3A,0x6B,0x6F,0x52,0x7F,0x7B};//0��9
uint8_t Tab2[] = {0xEE,0x24,0xBA,0xB6,0x74,0xD6,0xDE,0xA4,0xFE,0xF6};//0��9

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
        if(T == 0)
		{
            T += dT;
            Twinkle_Time -= 0.5f;//��˸��ʱ
            if(Twinkle_Time == 0)//�����˸����
            {
                sys.SetMode_Option = 0;//ģʽѡ������
                Speed_ShowFlag = 0;//����
                Temp_ShowFlag = 0;//����
                Time_ShowFlag = 0;//����
            } 
            if(sys.SetMode_Option == 1)//�����¶�
			{
				Speed_ShowFlag = 0;//�ٶȳ���
				Time_ShowFlag = 0;//ʱ�䳣��
				Temp_ShowFlag = ~Temp_ShowFlag;//�¶���˸
			}
			else if(sys.SetMode_Option == 2)//�����ٶ�
			{ 
                #if(Type == 0)
                Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
				Speed_ShowFlag = 0;//�ٶȳ���
				Temp_ShowFlag = 0;//�¶ȳ��� 
                #elif(Type == 1)
                Time_ShowFlag = 0;//ʱ�䳣��
				Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
				Temp_ShowFlag = 0;//�¶ȳ���
                #endif	
			}
			else if(sys.SetMode_Option == 3)//����ʱ��
			{
				Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
				Speed_ShowFlag = 0;//�ٶȳ���
				Temp_ShowFlag = 0;//�¶ȳ��� 			
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
		Speed_ShowFlag = 0;//����
        Temp_ShowFlag = 0;//����
        Time_ShowFlag = 0;//����
		T = 0;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Start_SpeedRun(float dT)
 * ��    �ܣ�ת�ٶ���
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Start_SpeedRun(float dT)
{
	static float T;
	if(!sys.Run_Status || !Speed.Ctrl)
	{
		Speed.IcnStep = 0;
		T = 0;
		return;
	}
	T += dT;
	if(T >= 0.5)
	{
		Speed.IcnStep++;
		if(Speed.IcnStep > 3)
			Speed.IcnStep = 1;
		T = 0;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Icn_Twinkle(float dT)
 * ��    �ܣ�ͼ����˸
 * ��    ��: dT:ִ������
 * ��    ����float dT
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
			Temp.Icn = ~Temp.Icn;//�¶�ͼ����˸
			if(Time.Rel && (Temp.Icn != Time.Icn) && (Temp.Set == 0 || Temp.DisplayMode == 3))
				Time.Icn = ~Time.Icn;//ʱ��ͼ����˸;
			else
			{
				Time.Icn = 0;
			}
			T = 0;
		}
	}
	else
	{
		Temp.Icn = 0;//����ʾ�ٶ�ͼ��
		Time.Icn = 0;//����ʾʱ��ͼ��
	}
}


/*
*****************************************************************
 * ����ԭ�ͣ�static void Protect_Twinkle(float dT)
 * ��    �ܣ�������ͼ����˸
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Protect_Twinkle(float dT)
{
	static float T;
	if(Protect)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Protect_ShowFlag = ~Protect_ShowFlag;//�¶�ͼ����˸;
			T = 0;
		}
	}
	else
	{
		Protect_ShowFlag = 0;//��ʾ�¶�ͼ��
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
	Check_ShowFlag(dT);//ʱ��ͼ����˸
    Start_SpeedRun(dT);//ת�ٶ���
	Icn_Twinkle(dT);//ͼ����˸
	Protect_Twinkle(dT);//������ͼ����˸
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_RelVal(uint16_t val1, uint32_t val2, uint16_t val3)
 * ��    �ܣ���ʾʵ�ʵ�ֵ
 * ��    ��: val1����ʾ��ߵ���ֵ;val2����ʾ�м����ֵ;val3����ʾ�ұߵ���ֵ
 * ��    ����uint16_t val1, uint32_t val2, uint16_t val3
*****************************************************************
*/
void Display_RelVal(uint16_t val1, uint32_t val2, uint16_t val3)
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
    seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������

    /*****************��Ļ�趨�����ֵ******************/
    /***********val1��λ***********/
    if(val1 > 999)//����999ʱ
    {
        Val=val1/1000;//����1000
        if(val1 > 9)//�������9����ô˵������1000������λ��
            Val=Val%10;//����10ȡ�࣬�ó�ǧλ�ϵ���
        seg1&=0x80;seg1|=Tab[Val];
    }
    else
    {
        seg1&=0x80;seg1|=0x00;
    }

    /***********val1ʮλ***********/
    if(val1 > 99)//����99ʱ
    {
        Val=val1/100;//����100
        if(val1 > 9)//�������9����ô˵������100������λ��
            Val=Val%10;//����10ȡ�࣬�ó���λ�ϵ���
        seg2&=0x80;seg2|=Tab[Val];
    }
    else
    {
        seg2&=0x80;seg2|=0x00;
    }

    /***********val1��λ***********/
    if(val1 > 9)//����9ʱ
    {
        Val=val1/10;//����10
        if(val1 > 9)//�������9����ô˵������10������λ��
            Val=Val%10;//����10ȡ�࣬�ó�ʮλ�ϵ���
        seg3&=0x80;seg3|=Tab[Val];
    }
    else
    {
        seg3&=0x80;seg3|=Tab[0];
    }

    /***********val1С��λ***********/
    Val=val1%10;//ȡ����λ
    seg4&=0x80;seg4|=Tab[Val];
    seg4&=0x7F;seg4|=0x80;//��ʾ�¶ȵ�С����

#if(Type == 0)
    uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
    if(val2 && Time.Set != 0)
    {
        SH=val2/3600/10;//����ʮλ��λ��Сʱ��
        H=val2/3600%10;//�����λ��λ��Сʱ��
        SM=val2%3600/60/10;//����ʮ��λ��λ�ķ�����
        M=val2%3600/60%10;//�������λ��λ�ķ�����
        seg5&=0x80;seg5|=Tab[SH];
        seg6&=0x80;seg6|=Tab[H];
        seg7&=0x80;seg7|=Tab[SM];
        seg8&=0x80;seg8|=Tab[M];
    }
    else
    {
        seg5&=0x80;seg5|=0x08;
        seg6&=0x80;seg6|=0x08;
        seg7&=0x80;seg7|=0x08;
        seg8&=0x80;seg8|=0x08;
    }
    /*****************ʱ��ð��******************/
    seg7&=0x7f;seg7|=0x80;
#elif(Type == 1)
    /*****************��Ļ�趨�ұ���ֵ******************/
    /***********val3ǧλ***********/
    if(val3 > 999)//����999ʱ
    {
        Val=val3/1000;//����1000
        if(val3 > 9)//�������9����ô˵������1000������λ��
            Val=Val%10;//����10ȡ�࣬�ó�ǧλ�ϵ���
        seg5&=0x80;seg5|=Tab[Val];
    }
    else
    {
        seg5&=0x80;seg5|=0x00;
    }

    /***********val3��λ***********/
    if(val3 > 99)//����99ʱ
    {
        Val=val3/100;//����100
        if(val3 > 9)//�������9����ô˵������100������λ��
            Val=Val%10;//����10ȡ�࣬�ó���λ�ϵ���
        seg6&=0x80;seg6|=Tab[Val];
    }
    else
    {
        seg6&=0x80;seg6|=0x00;
    }

    /***********val3ʮλ***********/
    if(val3 > 9)//����9ʱ
    {
        Val=val3/10;//����10
        if(val3 > 9)//�������9����ô˵������10������λ��
            Val=Val%10;//����10ȡ�࣬�ó�ʮλ�ϵ���
        seg7&=0x80;seg7|=Tab[Val];
    }
    else
    {
        seg7&=0x80;seg7|=0x00;
    }

    /***********val3��λ***********/
    Val=val3%10;//ȡ����λ
    seg8&=0x80;seg8|=Tab[Val];

    /*****************ת��ͼ��******************/
	switch(Speed.IcnStep)
	{
		case 0:seg5&=0x7F;seg5|=0x80;seg6&=0x7F;seg6|=0x80;seg8&=0x7F;seg8|=0x80;//����
			break;
		case 1:seg5&=0x7F;seg5|=0x80;seg6&=0x7F;seg6|=0x80;seg8&=0x7F;seg8|=0x00;//����
			break;
		case 2:seg5&=0x7F;seg5|=0x80;seg6&=0x7F;seg6|=0x00;seg8&=0x7F;seg8|=0x80;//����
			break;
		case 3:seg5&=0x7F;seg5|=0x00;seg6&=0x7F;seg6|=0x80;seg8&=0x7F;seg8|=0x80;//����
			break;
		default:
			break;
	}
#endif

    /*****************�¶�ͼ��******************/
    if(!Temp.Icn || !Temp.Ctrl)
    {
        seg2&=0x7F;seg2|=0x80;seg3&=0x7F;seg3|=0x80;
    }
    else
    {
        seg2&=0x7F;seg2|=0x00;seg3&=0x7F;seg3|=0x00;
    }

    /*****************ʱ��ͼ��******************/
    if(!Time.Icn || !Time.Rel)
    {
        seg1&=0x7f;seg1|=0x80;
    }
    else
    {
        seg1&=0x7f;seg1|=0x00;
    }

	if(Protect)
	{
		if(Protect_ShowFlag)
		{
			seg1 = 0xFF;
			seg2 = 0xFF;
			seg3 = 0xFF;
			seg4 = 0xFF;
			seg5 = 0xFF;
			seg6 = 0xFF;
			seg7 = 0xFF;
			seg8 = 0xFF;
		}
		else
		{
			seg1 = 0x00;
			seg2 = 0x00;
			seg3 = 0x00;
			seg4 = 0x00;
			seg5 = 0x00;
			seg6 = 0x00;
			seg7 = 0x00;
			seg8 = 0x00;
		}
	}
    Write_Addr_Dat_N(0,seg1,1);
    Write_Addr_Dat_N(2,seg2,1);
    Write_Addr_Dat_N(4,seg3,1);
    Write_Addr_Dat_N(6,seg4,1);
    Write_Addr_Dat_N(8,seg5,1);
    Write_Addr_Dat_N(10,seg6,1);
    Write_Addr_Dat_N(12,seg7,1);
    Write_Addr_Dat_N(14,seg8,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_SetVal(uint16_t val1, uint32_t val2, uint16_t val3)
 * ��    �ܣ���ʾ�趨��ֵ
 * ��    ��: val1����ʾ��ߵ���ֵ;val2����ʾ�ұߵ���ֵ;val3����ʾ�ұߵ���ֵ
 * ��    ����uint16_t val1, uint32_t val2, uint16_t val3
*****************************************************************
*/
void Display_SetVal(uint16_t val1, uint32_t val2, uint16_t val3)
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9,seg10,seg11,seg12;
    seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;seg10=0;seg11=0;seg12=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
    uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ

    /*****************��Ļ�趨�����ֵ******************/
    /***********val1��λ***********/
	seg3&=0x7F;seg3|=0x80;//�¶ȵ�λͼ��
    seg4&=0xFE;seg4|=0x01;//�¶�С����
    if(!Temp_ShowFlag)
    {
		if(val1)
		{
			if(val1 > 999)//����999ʱ
			{
				Val=val1/1000;//����1000
				if(val1 > 9)//�������9����ô˵������1000������λ��
					Val=Val%10;//����10ȡ�࣬�ó�ǧλ�ϵ���
				seg1&=0x80;seg1|=Tab1[Val];
			}
			else
			{
				seg1&=0x80;seg1|=0x00;
			}

			/***********val1ʮλ***********/
			if(val1 > 99)//����99ʱ
			{
				Val=val1/100;//����100
				if(val1 > 9)//�������9����ô˵������100������λ��
					Val=Val%10;//����10ȡ�࣬�ó���λ�ϵ���
				seg2&=0x80;seg2|=Tab1[Val];
			}
			else
			{
				seg2&=0x80;seg2|=0x00;
			}

			
			/***********val1��λ***********/
			if(val1 > 9)//����9ʱ
			{
				Val=val1/10;//����10
				if(val1 > 9)//�������9����ô˵������10������λ��
					Val=Val%10;//����10ȡ�࣬�ó�ʮλ�ϵ���
				seg3&=0x80;seg3|=Tab1[Val];
			}
			else
			{
				seg3&=0x80;seg3|=Tab1[0];
			}
			
			/***********val1С��λ***********/
			Val=val1%10;//ȡ����λ
			seg4&=0x01;seg4|=Tab2[Val];
		}
		else//��ʾ��----��
		{
			seg1&=0x80;seg1|=0x08;
            seg2&=0x80;seg2|=0x08;
            seg3&=0x80;seg3|=0x08;
            seg4&=0x80;seg4|=0x10;
		}
    }
    else//��˸����ʾ
    {
        seg1&=0x80;seg1|=0x00;
        seg2&=0x80;seg2|=0x00;
        seg3&=0x80;seg3|=0x00;
        seg4&=0x00;seg4|=0x00;
    } 

#if(Type == 0)
    /*****************��Ļ�趨�ұ���ֵ******************/
    if(!Time_ShowFlag)
    {
        if(val2)
        {
            SH=val2/3600/10;//����ʮλ��λ��Сʱ��
            H=val2/3600%10;//�����λ��λ��Сʱ��
            SM=val2%3600/60/10;//����ʮ��λ��λ�ķ�����
            M=val2%3600/60%10;//�������λ��λ�ķ�����
            seg9&=0x80;seg9|=Tab1[SH];
            seg10&=0x80;seg10|=Tab1[H];
            seg11&=0x80;seg11|=Tab1[SM];
            seg12&=0x80;seg12|=Tab1[M];
        }
        else
        {
            seg9&=0x80;seg9|=0x08;//��ʾ��-��
            seg10&=0x80;seg10|=0x08;//��ʾ��-��
            seg11&=0x80;seg11|=0x08;//��ʾ��-��
            seg12&=0x80;seg12|=0x08;//��ʾ��-��
        }
    }
    else
    {
        seg9&=0x80;seg9|=0x00;
        seg10&=0x80;seg10|=0x00;
        seg11&=0x80;seg11|=0x00;
        seg12&=0x80;seg12|=0x00;
    }
    /*****************ʱ��ð��******************/
    seg10&=0x7f;seg10|=0x80;
    /*****************ʱ�䵥λ******************/
    seg12&=0x7f;seg12|=0x80;//��ʾmin

#elif(Type == 1)
    /*****************��Ļ�趨�м���ֵ******************/
    if(Time.Set || sys.SetMode_Option == 3)//�趨ʱ�����0�����趨ʱ�����˸��
	{
        if(!Time_ShowFlag)
        {
            if(Time.Set)//�����趨ʱ�����0
            {
                SH=val2/3600/10;//����ʮλ��λ��Сʱ��
                H=val2/3600%10;//�����λ��λ��Сʱ��
                SM=val2%3600/60/10;//����ʮ��λ��λ�ķ�����
                M=val2%3600/60%10;//�������λ��λ�ķ�����
                seg5&=0x80;seg5|=Tab1[SH];
                seg6&=0x80;seg6|=Tab1[H];
                seg7&=0x80;seg7|=Tab1[SM];
                seg8&=0x80;seg8|=Tab1[M];
            }
            else
            {
                seg5&=0x80;seg5|=0x08;//��ʾ��-��
                seg6&=0x80;seg6|=0x08;//��ʾ��-��
                seg7&=0x80;seg7|=0x08;//��ʾ��-��
                seg8&=0x80;seg8|=0x08;//��ʾ��-��
            }
        }
        else//�趨ʱ�����0
	    {
            seg5&=0x80;seg5|=0x00;
            seg6&=0x80;seg6|=0x00;
            seg7&=0x80;seg7|=0x00;
            seg8&=0x80;seg8|=0x00;
	    }
	}
	else//�趨ʱ�����0
    {
        seg5&=0x80;seg5|=0x00;
        seg6&=0x80;seg6|=0x00;
        seg7&=0x80;seg7|=0x00;
        seg8&=0x80;seg8|=0x00;
    }

	if(Time.Set > 0 || sys.SetMode_Option == 3)
	{
		/*****************ʱ��ð��******************/
        seg6&=0x7f;seg6|=0x80;
        /*****************ʱ�䵥λ******************/
        // seg8&=0x7f;seg8|=0x80;//��ʾsec
        seg7&=0x7f;seg7|=0x80;//��ʾmin
	}
	else
	{
		seg6&=0x7f;seg6|=0x00;
        seg7&=0x7f;seg7|=0x00;
	}

    /*****************��Ļ�趨�ұ���ֵ******************/
    if(!Speed_ShowFlag)
    {
        if(Speed.Set)
        {
            /***********val3ǧλ***********/
            if(val3 > 999)//����999ʱ
            {
                Val=val3/1000;//����1000
                if(val3 > 9)//�������9����ô˵������1000������λ��
                    Val=Val%10;//����10ȡ�࣬�ó�ǧλ�ϵ���
                seg9&=0x80;seg9|=Tab1[Val];
            }
            else
            {
                seg9&=0x80;seg9|=0x00;
            }

            /***********val3��λ***********/
            if(val3 > 99)//����99ʱ
            {
                Val=val3/100;//����100
                if(val3 > 9)//�������9����ô˵������100������λ��
                    Val=Val%10;//����10ȡ�࣬�ó���λ�ϵ���
                seg10&=0x80;seg10|=Tab1[Val];
            }
            else
            {
                seg10&=0x80;seg10|=0x00;
            }

            /***********val3ʮλ***********/
            if(val3 > 9)//����9ʱ
            {
                Val=val3/10;//����10
                if(val3 > 9)//�������9����ô˵������10������λ��
                    Val=Val%10;//����10ȡ�࣬�ó�ʮλ�ϵ���
                seg11&=0x80;seg11|=Tab1[Val];
            }
            else
            {
                seg11&=0x80;seg11|=0x00;
            }

            /***********val3��λ***********/
            Val=val3%10;//ȡ����λ
            seg12&=0x80;seg12|=Tab1[Val];
        }
        else
        {
            seg9&=0x80;seg9|=0x08;
            seg10&=0x80;seg10|=0x08;
            seg11&=0x80;seg11|=0x08;
            seg12&=0x80;seg12|=0x08;
        }
    }
    else
    {
        seg9&=0x80;seg9|=0x00;
        seg10&=0x80;seg10|=0x00;
        seg11&=0x80;seg11|=0x00;
        seg12&=0x80;seg12|=0x00;
    }
    /*****************�ٶȵ�λ******************/
    seg11&=0x7F;seg11|=0x80;
#endif
	if(Protect)
	{
		if(Protect_ShowFlag)
		{
			seg1 = 0xFF;
			seg2 = 0xFF;
			seg3 = 0xFF;
			seg4 = 0xFF;
			seg5 = 0xFF;
			seg6 = 0xFF;
			seg7 = 0xFF;
			seg8 = 0xFF;
			seg9 = 0xFF;
			seg10 = 0xFF;
			seg11 = 0xFF;
			seg12 = 0xFF;
		}
		else
		{
			seg1 = 0x00;
			seg2 = 0x00;
			seg3 = 0x00;
			seg4 = 0x00;
			seg5 = 0x00;
			seg6 = 0x00;
			seg7 = 0x00;
			seg8 = 0x00;
			seg9 = 0x00;
			seg10 = 0x00;
			seg11 = 0x00;
			seg12 = 0x00;
		}
	}
	
    Write_Addr_Dat_N(38,seg1,1);
    Write_Addr_Dat_N(36,seg2,1);
    Write_Addr_Dat_N(34,seg3,1);
    Write_Addr_Dat_N(32,seg4,1);
    Write_Addr_Dat_N(30,seg5,1);
    Write_Addr_Dat_N(28,seg6,1);
    Write_Addr_Dat_N(26,seg7,1);
    Write_Addr_Dat_N(24,seg8,1);
    Write_Addr_Dat_N(22,seg9,1);
    Write_Addr_Dat_N(20,seg10,1);
    Write_Addr_Dat_N(18,seg11,1);
    Write_Addr_Dat_N(16,seg12,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Judge_SpeedMode(void)
 * ��    �ܣ��ж��ٶ���ʾ��ģʽ
*****************************************************************
*/
void Judge_SpeedMode(void)
{
    if(!Speed.Set)
    {
        Speed.DisplayMode = 0;
    }
    else if(Speed.Set > Speed.Rel)//����
    {
        Speed.DisplayMode = 1;
    }
    else//����
    {
        Speed.DisplayMode = 2;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Judge_TempMode(void)
 * ��    �ܣ��ж��¶���ʾ��ģʽ
*****************************************************************
*/
void Judge_TempMode(void)
{
	if(!Temp.Ctrl)
		Temp.DisplayMode = 0;
	else if(Temp.Ctrl > Temp.Rel)
		Temp.DisplayMode = 1;//����
	else if(Temp.Ctrl < Temp.Rel)
		Temp.DisplayMode = 2;//����
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Speed(float dT)
 * ��    �ܣ��ٶ���ʾ����
*****************************************************************
*/
void Deal_Speed(float dT)
{
	switch(Speed.DisplayMode)
	{
		case 0:Speed.Display_Rel = 0;
			break;
		case 1://����ʱ
				if(Speed.Display_Rel < Speed.Rel && !sys.SetMode_Option)
					Speed.Display_Rel ++;
				if(Speed.Ctrl == 1200 && Speed.Rel > 1140)
					Speed.Display_Rel ++;
				if(Speed.Display_Rel >= Speed.Ctrl)
					Speed.DisplayMode = 3;
			break;
		case 2://����ʱ
				if(Speed.Display_Rel > Speed.Rel && !sys.SetMode_Option)
					Speed.Display_Rel --;
				if(sys.Run_Status && (Speed.Display_Rel <= Speed.Ctrl))
					Speed.DisplayMode = 3;
			break;
		case 3: Speed.Display_Rel = Speed.Ctrl;
			break;
	}
}
				
/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Temp(float dT)
 * ��    �ܣ��¶���ʾ����
*****************************************************************
*/
void Deal_Temp(float dT)
{
	if(sys.Run_Status && !Display_Res && Temp.Set != 0)//ϵͳ���������ȹ��ܿ���
	{	
		if(Temp.DisplayMode == 0)
		{
			Temp.Display_Rel = Temp.Rel;
		}
		else if(Temp.DisplayMode == 1)
		{
			if(Temp.Display_Rel <= Temp.Rel)
			{
				Temp.Display_Rel ++;
			}
			if(Temp.Display_Rel >= Temp.Ctrl)
			{
				Temp.DisplayMode = 3;
			}
		}
		else if(Temp.DisplayMode == 2)
		{
			if(Temp.Display_Rel >= Temp.Rel)
			{
				Temp.Display_Rel --;
			}
			if(Temp.Display_Rel <= Temp.Ctrl)
			{
				Temp.DisplayMode = 3;
			}
		}
		else if(Temp.DisplayMode == 3)
		{
			Temp.Display_Rel = Temp.Ctrl;
		}
	}
	else
	{
		Temp.Display_Rel = Temp.Rel;
		Temp.DisplayMode = 0;
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
    Temp.Display_Set = Temp.Set;
    Speed.Display_Set = Speed.Set;

#if(Type == 0)
    Time.Display_Set = Time.Set;
    if(sys.Run_Status)
        Time.Display_Rel = Time.Rel+59;
    else
        Time.Display_Rel = Time.Rel;
#elif(Type == 1)
    if(sys.Run_Status && !sys.SetMode_Option)
        Time.Display_Set = Time.Rel+59;
    else
        Time.Display_Set = Time.Set;
#endif
	if(Temp.Display_Rel > 1000)
		Temp.Display_Rel = 1000;
    Display_RelVal(Temp.Display_Rel,Time.Display_Rel,Speed.Display_Rel);
    Display_SetVal(Temp.Display_Set,Time.Display_Set,Speed.Display_Set);
}
