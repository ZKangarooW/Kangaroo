#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Time_ShowFlag,Temp_ShowFlag;//ʱ�䡢�¶���ʾ�ı�־λ 0:���� 1��Ϩ��
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
                Temp_ShowFlag = 0;//����
                Time_ShowFlag = 0;//����
            } 
            if(sys.SetMode_Option == 1)//�����¶�
			{
				Time_ShowFlag = 0;//ʱ�䳣��
				Temp_ShowFlag = ~Temp_ShowFlag;//�¶���˸
			}
			else if(sys.SetMode_Option == 2)//����ʱ��
			{
				Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
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
        Temp_ShowFlag = 0;//����
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
static void Time_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Time.Icn = ~Time.Icn;//ʱ��ͼ����˸;
			T = 0;
		}
	}
	else
	{
		Time.Icn = 0;//��ʾʱ��ͼ��
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Temp_Twinkle(float dT)
 * ��    �ܣ��¶�ͼ����˸
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Temp_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Temp.Icn = ~Temp.Icn;//�¶�ͼ����˸;
			T = 0;
		}
	}
	else
	{
		Temp.Icn = 0;//��ʾ�¶�ͼ��
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Protect_Twinkle(float dT)
 * ��    �ܣ���������˸
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Protect_Twinkle(float dT)
{
	static float T;
	if(Protect == 1)
	{
		T += dT;
		if(T >= 0.5f)
		{
			Protect_ShowFlag = ~Protect_ShowFlag;//������ͼ����˸;
			T = 0;
		}
	}
	else
	{
		Protect_ShowFlag = 0;//��ʾ������ͼ��
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
    Time_Twinkle(dT);//ʱ��ͼ����˸
	Temp_Twinkle(dT);//�¶�ͼ����˸
    Protect_Twinkle(dT);//��������˸
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_RelVal(int16_t temp_rel, int32_t time_ctrl)
 * ��    �ܣ���ʾʵ�ʵ�ֵ
 * ��    ��: temp_rel����ʾʵ���¶�;time_ctrl����ʾ���Ƶ�ʱ��
 * ��    ����int16_t temp_rel, int32_t time_ctrl
*****************************************************************
*/
void Display_RelVal(int16_t temp_rel, int32_t time_ctrl)
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
    seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
    uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
    
    /*****************ʵ���¶���ֵ******************/
    /***********temp_rel��λ***********/
    if(temp_rel > 999)//����999ʱ
    {
        Val=temp_rel/1000;//����1000
        if(temp_rel > 9)//�������9����ô˵������1000������λ��
            Val=Val%10;//����10ȡ�࣬�ó�ǧλ�ϵ���
        seg1&=0x80;seg1|=Tab[Val];
    }
    else
    {
        seg1&=0x80;seg1|=0x00;
    }

    /***********temp_relʮλ***********/
    if(temp_rel > 99)//����99ʱ
    {
        Val=temp_rel/100;//����100
        if(temp_rel > 9)//�������9����ô˵������100������λ��
            Val=Val%10;//����10ȡ�࣬�ó���λ�ϵ���
        seg2&=0x80;seg2|=Tab[Val];
    }
    else
    {
        seg2&=0x80;seg2|=0x00;
    }

    /***********temp_rel��λ***********/
    if(temp_rel > 9)//����9ʱ
    {
        Val=temp_rel/10;//����10
        if(temp_rel > 9)//�������9����ô˵������10������λ��
            Val=Val%10;//����10ȡ�࣬�ó�ʮλ�ϵ���
        seg3&=0x80;seg3|=Tab[Val];
    }
    else
    {
        seg3&=0x80;seg3|=Tab[0];
    }

    /***********temp_relС��λ***********/
    Val=temp_rel%10;//ȡ����λ
    seg4&=0x80;seg4|=Tab[Val];
    
    /*****************����ʱ����ֵ******************/
    if(time_ctrl == 0)//��ʾ��----��
    {
        seg5 = 0x08;
        seg6 = 0x08;
        seg7 = 0x08;
        seg8 = 0x08;
    }
    else
    {
        if(time_ctrl < 3600)
        {
            SH = time_ctrl/60/10;//����ʮλ��λ��Сʱ��
            H  = time_ctrl/60%10;//�����λ��λ��Сʱ��
            SM = time_ctrl%60/10;//����ʮ��λ��λ�ķ�����
            M  = time_ctrl%60%10;//�������λ��λ�ķ�����
        }
        else
        {
            SH = time_ctrl/3600/10;//����ʮλ��λ��Сʱ��
            H  = time_ctrl/3600%10;//�����λ��λ��Сʱ��
            SM = time_ctrl%3600/60/10;//����ʮ��λ��λ�ķ�����
            M  = time_ctrl%3600/60%10;//�������λ��λ�ķ�����
        }
        seg5&=0x80;seg5|=Tab[SH];
        seg6&=0x80;seg6|=Tab[H];
        seg7&=0x80;seg7|=Tab[SM];
        seg8&=0x80;seg8|=Tab[M];
    }
    if(!Temp.Icn)seg4 = seg4 | 0x80;//����ͼ��
    else seg4 = seg4 | 0x00;//����ͼ��
    
    seg3 = seg3 | 0x80;//ʵ���¶ȵ�С����
    seg1 = seg1 | 0x80;//�����¶ȵġ����
    
    if(Time.Rel  && Temp.ADDMode == 3)
    {
        if(!Time.Icn)seg7 = seg7 | 0x80;//ʵʱʱ��ð��
        else seg7 = seg7 | 0x00;//ʵʱʱ��ð��
    }
    else
    {
        seg7 = seg7 | 0x80;
    }
    
    if(Protect)
    {
        if(Protect_ShowFlag)
        {
            seg1 = 0xFF;
            seg2 = 0x7F;
            seg3 = 0xFF;
            seg4 = 0xFF;   
            seg5 = 0x7F;
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
 * ����ԭ�ͣ�void Display_SetVal(int16_t temp_set, int32_t time_set)
 * ��    �ܣ���ʾ�趨��ֵ
 * ��    ��: temp_set����ʾ�趨�¶�;time_set����ʾ�趨ʱ��
 * ��    ����int16_t temp_set, int32_t time_set
*****************************************************************
*/
void Display_SetVal(int16_t temp_set, int32_t time_set)
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
    seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
    uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
    
    /*****************�趨�¶���ֵ******************/
    /***********temp_set��λ***********/
    if(!Temp_ShowFlag)
    {
        if(temp_set > 999)//����999ʱ
        {
            Val=temp_set/1000;//����1000
            if(temp_set > 9)//�������9����ô˵������1000������λ��
                Val=Val%10;//����10ȡ�࣬�ó�ǧλ�ϵ���
            seg1&=0x80;seg1|=Tab2[Val];
        }
        else
        {
            seg1&=0x80;seg1|=0x00;
        }

        /***********temp_setʮλ***********/
        if(temp_set > 99)//����99ʱ
        {
            Val=temp_set/100;//����100
            if(temp_set > 9)//�������9����ô˵������100������λ��
                Val=Val%10;//����10ȡ�࣬�ó���λ�ϵ���
            seg2&=0x80;seg2|=Tab2[Val];
        }
        else
        {
            seg2&=0x80;seg2|=0x00;
        }

        /***********temp_set��λ***********/
        if(temp_set > 9)//����9ʱ
        {
            Val=temp_set/10;//����10
            if(temp_set > 9)//�������9����ô˵������10������λ��
                Val=Val%10;//����10ȡ�࣬�ó�ʮλ�ϵ���
            seg3&=0x80;seg3|=Tab2[Val];
        }
        else
        {
            seg3&=0x80;seg3|=Tab2[0];
        }

        /***********temp_setС��λ***********/
        Val=temp_set%10;//ȡ����λ
        seg4&=0x80;seg4|=Tab2[Val];
    }
    else
    {
        seg1 = 0x00;
        seg2 = 0x00;
        seg3 = 0x00;
        seg4 = 0x00;
    }
    
    /*****************�趨ʱ����ֵ******************/
    if(!Time_ShowFlag)
    {
        if(time_set == 0)//��ʾ��----��
        {
            seg5 = 0x08;
            seg6 = 0x08;
            seg7 = 0x08;
            seg8 = 0x08;
        }
        else
        {
            if(time_set < 3600)
            {
                SH = time_set/60/10;//����ʮλ��λ��Сʱ��
                H  = time_set/60%10;//�����λ��λ��Сʱ��
                SM = time_set%60/10;//����ʮ��λ��λ�ķ�����
                M  = time_set%60%10;//�������λ��λ�ķ�����
            }
            else
            {
                SH = time_set/3600/10;//����ʮλ��λ��Сʱ��
                H  = time_set/3600%10;//�����λ��λ��Сʱ��
                SM = time_set%3600/60/10;//����ʮ��λ��λ�ķ�����
                M  = time_set%3600/60%10;//�������λ��λ�ķ�����
            }
            seg5&=0x80;seg5|=Tab1[SH];
            seg6&=0x80;seg6|=Tab1[H];
            seg7&=0x80;seg7|=Tab1[SM];
            seg8&=0x80;seg8|=Tab1[M];
        }
    }
    else
    {
        seg5 = 0x00; 
        seg6 = 0x00; 
        seg7 = 0x00; 
        seg8 = 0x00; 
    }

    if(time_set < 3600) seg7 = seg7 | 0x80;//�뵥λ��ʾ
    else seg8 = seg8 | 0x80;//���ӵ�λ��ʾ
   
    seg3 = seg3 | 0x01;//�����¶ȵ�С����
    
    seg6 = seg6 | 0x80;//ʵʱʱ��ð��
    
    if(Protect)
    {
        if(Protect_ShowFlag)
        {
            seg1 = 0xFF;
            seg2 = 0xFE;
            seg3 = 0xFF;
            seg4 = 0xFE;   
            seg5 = 0x7F;
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
            
    Write_Addr_Dat_N(38,seg1,1);
    Write_Addr_Dat_N(36,seg2,1);
    Write_Addr_Dat_N(34,seg3,1);
    Write_Addr_Dat_N(32,seg4,1);
    Write_Addr_Dat_N(22,seg5,1);
    Write_Addr_Dat_N(20,seg6,1);
    Write_Addr_Dat_N(18,seg7,1);
    Write_Addr_Dat_N(16,seg8,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Temp(float dT)
 * ��    �ܣ��¶���ʾ����
*****************************************************************
*/
void Deal_Temp(float dT)
{
    static float T;
    if(sys.Run_Status == 0)//û�����������
    {
		Temp.ADDMode = 0;
		Temp.Display_Rel = Temp.Rel;
        Temp_Arg.Kp = 2;
        T = 0;
    }
    else if(sys.Run_Status == 1)//�����������
    {
        if(Temp.ADDMode == 0)//�ж����ݴ�����ʾ
        {     
		   if(Temp.Ctrl > Temp.Display_Rel)//�趨�¶ȴ�����ʾ�¶�
		   { 
				Temp.ADDMode = 1;//�������ģʽ��
			}
		   else
		   {
				Temp.ADDMode = 2;//���뽵��ģʽ��
			}
        }
        if(Temp.ADDMode == 1)//�ڼ���ģʽ��
        {
            if(Temp.Rel > Temp.Display_Rel && Temp.Display_Rel <= Temp.Ctrl)
                Temp.Display_Rel++;
            else//��ǰ�¶�С����һ���¶�
            {
                Temp.Display_Rel = Temp.Display_Rel;
            }
            if(Temp.Display_Rel >= Temp.Ctrl)
            {
                Temp.ADDMode = 3;//�����ȶ�ģʽ
                Temp_Val.Integral = 0;//��������
            }
            if(Temp.Rel <= Temp.Display_Rel)
            {
                T +=dT;
                if(T > 10.0f)
                {
                    Temp.Display_Rel ++;
                    LIMIT_Val += 50;
                    if(LIMIT_Val > 1000)
                    {
                        LIMIT_Val = 1000;
                    }
                    T = 0;
                }
            }
            else T = 0;
            
            if(ABS(Temp.Display_Rel - Temp.Rel) > 100)
            {
                Temp.Display_Rel = Temp.Rel;
                Temp.ADDMode = 0;
            }   
        }
		else if(Temp.ADDMode == 2)//����ģʽ��
        {
             T = 0;
            if(Temp.Rel < Temp.Display_Rel && Temp.Display_Rel >= Temp.Ctrl)//��ǰ�¶�С����һ���¶�
                Temp.Display_Rel --;//��ʾ��ǰ�¶�
            else//��ǰ�¶ȴ�����һ���¶�
            {
                Temp.Display_Rel = Temp.Display_Rel;//��ʾ��һ���¶ȣ������¶ȴ��ڵ�ǰ�¶ȡ������½��¶ȵ�����
            }
            if(Temp.Display_Rel <= Temp.Ctrl)
            {
                Temp.ADDMode = 3;//�����ȶ�ģʽ
            }
            if(ABS(Temp.Display_Rel - Temp.Rel) > 100)
            {
                Temp.Display_Rel = Temp.Rel;
                Temp.ADDMode = 0;
            } 
            Temp_Val.Integral = 0;//��������            
        }  	
        else if(Temp.ADDMode == 3)//�¶��ȶ�ģʽ��
        {
			Temp.Display_Rel = Temp.Ctrl;//��ʾ��ǰ��ʾ�¶�
            Temp_Arg.Kp = 60; 
            T = 0;
        }  
        if(ABS(Temp.Display_Rel - Temp.Rel) > 100)
        {
            Temp.Display_Rel = Temp.Rel;
            Temp.ADDMode = 0;
        }         
    }
    else if(sys.Run_Status == 2)
    {
        T +=dT;
        if(T > 5.0f)
        {
            if(Temp.Rel < Temp.Display_Rel)
                Temp.Display_Rel --;//��ʾ��ǰ�¶�
            else if(Temp.Rel > Temp.Display_Rel)
                Temp.Display_Rel ++;//��ʾ��ǰ�¶�   
            else
                sys.Run_Status = 0;
            T = 0;
        }
        if(ABS(Temp.Display_Rel - Temp.Rel) > 150)
        {
            sys.Run_Status = 0;
        }
        Temp_Arg.Kp = 2;
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
    
    Time.Display_Rel = Time.Rel;
    Time.Display_Set = Time.Set;
    
    Display_RelVal(Temp.Display_Rel, Time.Display_Rel);
    Display_SetVal(Temp.Display_Set, Time.Display_Set);
}
