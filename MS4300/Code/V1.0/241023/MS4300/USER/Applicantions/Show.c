#include "Show.h"

/**********ȫ�ֱ�������******/
float Speed_Twinkle_Time,Time_Twinkle_Time,Pmode_Twinkle_Time;//�ٶ���˸ʱ���ʱ����˸ʱ��

/**********�ֲ���������******/
uint8_t TimeIcn_ShowFlag,SpeedIcn_ShowFlag,Pmode_ShowFlag;//ʱ��ͼ����˸���ٶ�ͼ����˸
uint8_t Speed_ShowFlag,Time_ShowFlag,Lock_ShowFlag;//�ٶȡ�ʱ����ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t DOWNL_Tab[]={0x77,0X24,0x5d,0x6d,0x2e,0x6b,0x7b,0x25,0x7f,0x6f};//0��9
uint8_t UP_Tab[]={0xee,0x24,0xba,0xb6,0x74,0xd6,0xde,0xa4,0xfe,0xf6};//0��9
uint8_t DOWNR_Tab[]={0xee,0x48,0xba,0xda,0x5c,0xd6,0xf6,0x4a,0xfe,0xde};//0��9

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
			SpeedIcn_ShowFlag = ~SpeedIcn_ShowFlag;//ת��ͼ����˸;
			if(Time.Rel && (SpeedIcn_ShowFlag != TimeIcn_ShowFlag))
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//ʱ��ͼ����˸;
			else
			{
				TimeIcn_ShowFlag = 0;
			}
			T = 0;
		}
	}
	else
	{
		SpeedIcn_ShowFlag = 0;//����ʾ�ٶ�ͼ��
		TimeIcn_ShowFlag = 0;//����ʾʱ��ͼ��
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
	static float Speed_T,Time_T,Pmode_T;
	if(Speed_Twinkle_Time && EC11A[1].EC11A_Knob<=0)//�ٶ���˸��û�в�������ʱ
    {
		Speed_T += dT;
		if(Speed_T >= 0.5f)
		{
			Speed_Twinkle_Time -= 0.5;//��˸��ʱ
			Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
			if(Speed_Twinkle_Time == 0)//�����˸����
			{
				SpeedSet_Flag = 1;//�����ٶ��趨
//				Beep_Time = 0.1;//��������0.1S
			} 
			Speed_T = 0;		
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//����
		Speed_T = 0;
	}
	
	if(Time_Twinkle_Time && EC11A[0].EC11A_Knob<=0)//ʱ����˸��û�в�������ʱ
    {
		Time_T += dT;
		if(Time_T >= 0.5f)
		{
			Time_Twinkle_Time -= 0.5;//��˸��ʱ
			Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
			if(Time_Twinkle_Time == 0)//�����˸����
			{
				TimeSet_Flag = 1;//����ʱ���趨
//				Beep_Time = 0.1;//��������0.1S
			} 
			Time_T = 0;			
		}			
    }
	else
	{
		Time_ShowFlag = 0;//����
		Time_T = 0;
	}
    
    if(Pmode_Twinkle_Time && (EC11A[1].EC11A_Knob<=0 && EC11A[0].EC11A_Knob<=0))//ʱ����˸��û�в�������ʱ
    {
		Pmode_T += dT;
		if(Pmode_T >= 0.5f)
		{
			Pmode_Twinkle_Time -= 0.5;//��˸��ʱ
			Pmode_ShowFlag = ~Pmode_ShowFlag;//ʱ����˸
			if(Pmode_Twinkle_Time == 0)//�����˸����
			{
                SpeedSet_Flag = TimeSet_Flag=1;//��������
			} 
			Pmode_T = 0;
		}			
    }
	else
	{
		Pmode_ShowFlag = 0;//����
		Pmode_T = 0;
	}
}

/**
 * @brief ������ͼ����˸���
 *
 * @param dT ��������
 */
void Check_Lock(float dT)
{
    static float T;
	if (sys.Lock_Alarm)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Lock_ShowFlag = ~Lock_ShowFlag;//��ȫ�¶�ͼ����˸
            sys.Lock_Alarm -= 0.5f;
			T = 0;
		}
	}
    else
    {
        Lock_ShowFlag = 0;
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
	Icn_Twinkle(dT);//ͼ����˸
    Check_Lock(dT);//������ͼ����˸���
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Set_Time(int32_t dis_set_time)
 * ��    �ܣ�д����ߵ��趨ʱ��
 * ��    �룺dis_set_time:����������ʱ��
 * ��    ����int32_t dis_set_time
*****************************************************************
*/
void Display_Set_Time(int32_t dis_set_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
	
	if(!Time_ShowFlag)//��ʾʱ���ʾΪ0
	{
		if(dis_set_time)//�趨ʱ�����0
		{
			SH=dis_set_time/3600/10;//����ʮλ��λ��Сʱ��
			H=dis_set_time/3600%10;//�����λ��λ��Сʱ��
			SM=dis_set_time%3600/60/10;//����ʮ��λ��λ�ķ�����
			M=dis_set_time%3600/60%10;//�������λ��λ�ķ�����
			seg1 = DOWNL_Tab[SH];//ʱ��ʮλ��λ��Сʱ��
			seg2 = DOWNL_Tab[H];//ʱ���λ��λ��Сʱ��
			seg3 = DOWNL_Tab[SM];//ʱ��ʮ��λ��λ�ķ�����
			seg4 = DOWNL_Tab[M];//ʱ�����λ��λ�ķ�����
		}
		else//û������ʱ��,��ʾ��--:--��
		{
			seg1=(seg1&0x80)|0x08;
			seg2=(seg2&0x80)|0x08;
			seg3=(seg3&0x80)|0x08;
			seg4=(seg4&0x00)|0x08;//0x00����ѵ�λ"min"ȥ��
		}
	}
	else
	{
		seg1&=0x00;//����ʾʱ��
		seg2&=0x00;//����ʾʱ��
		seg3&=0x00;//����ʾʱ��
		seg4&=0x80;//����ʾʱ��
	}

	seg2 = seg2|0x80;//�趨ʱ��ð�ţ����棩
//	seg3 = seg3|0x80;//�趨ʱ��С���㣨���棩
	seg4 = seg4|0x80;//�趨ʱ��min�ı���ʾ
	
	Write_Addr_Dat_N(0, seg1,1);
	Write_Addr_Dat_N(2, seg2,1);
 	Write_Addr_Dat_N(4, seg3,1);
	Write_Addr_Dat_N(6, seg4,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Rel_Time(int32_t dis_rel_time)
 * ��    �ܣ�д����ߵ�ʵ��ʱ��
 * ��    �룺dis_rel_time:����������ʱ��
 * ��    ����int32_t dis_rel_time
*****************************************************************
*/
void Display_Rel_Time(int32_t dis_rel_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
	
	if(Time.Rel || Time.Set)//��ʾʱ���ʾΪ0
	{
		SH=dis_rel_time/3600/10;//����ʮλ��λ��Сʱ��
		H=dis_rel_time/3600%10;//�����λ��λ��Сʱ��
		SM=dis_rel_time%3600/60/10;//����ʮ��λ��λ�ķ�����
		M=dis_rel_time%3600/60%10;//�������λ��λ�ķ�����
		seg1 = UP_Tab[SH];//ʱ��ʮλ��λ��Сʱ��
		seg2 = UP_Tab[H];//ʱ���λ��λ��Сʱ��
		seg3 = UP_Tab[SM];//ʱ��ʮ��λ��λ�ķ�����
		seg4 = UP_Tab[M];//ʱ�����λ��λ�ķ�����
	
	}
	else//û������ʱ��,��ʾ��--:--��
	{
		seg1=(seg1&0x01)|0x10;
		seg2=(seg2&0x01)|0x10;
		seg3=(seg3&0x01)|0x10;
		seg4=(seg4&0x01)|0x10;
	}
	
	
//	seg1 = seg1|0x01;//�¶ȷ��š��桱ͼ�꣨���棩
	seg2 = seg2|0x01;//ʵ��ʱ��ð�ţ����棩
//	seg3 = seg3|0x01;//ʵ��ʱ��С���㣨���棩
	seg4 = seg4|0x01;//ʱ��ͼ�꣨���棩
	
    if(sys.Run_Status && TimeIcn_ShowFlag)//����ʱ
    {
		seg2&=0xFE;//ʵ��ʱ��ð�ţ����棩��ʧ
		seg4&=0xFE;//ʱ��ͼ�꣨���棩��ʧ
	}
	
	Write_Addr_Dat_N(36, seg1,1);
	Write_Addr_Dat_N(38, seg2,1);
 	Write_Addr_Dat_N(40, seg3,1);
	Write_Addr_Dat_N(42, seg4,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_SetSpeed(int16_t dis_set_speed)
 * ��    �ܣ�д���ұߵ��趨�ٶ�
 * ��    �룺dis_set_speed:�ұ���������ٶ�
 * ��    ����int16_t dis_set_speed
*****************************************************************
*/
void Display_Set_Speed(int16_t dis_set_speed)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	/***********�趨ת�ټ���**********/
	if(!Speed_ShowFlag)//��˸��־Ϊ0
	{
		if(dis_set_speed>999)
		{	
			Val=dis_set_speed/1000;//ȡ��ǧλ
			seg1 = DOWNR_Tab[Val];
		}
		else
		{
			seg1 = DOWNR_Tab[0];//��ʾ0
		}	
		if(dis_set_speed > 99)//����99ʱ
		{
			Val=dis_set_speed/100;//ȡ����λ
			if(dis_set_speed > 999)//����999ʱ
				Val=Val%10;//ȡ����λ
			seg2 = DOWNR_Tab[Val];
		}
		else
		{
			seg2 = DOWNR_Tab[0];//��ʾ0
		}
		if(dis_set_speed > 9)//����9ʱ
		{
			Val=dis_set_speed/10;//ȡ��ʮλ
			if(dis_set_speed > 99)//����99ʱ
				Val=Val%10;//ȡ��ʮλ
			seg3 = DOWNR_Tab[Val];
		}
		else
		{
			seg3 = DOWNR_Tab[0];//��ʾ0
		}
		Val=dis_set_speed%10;//ȡ����λ
		seg4 = DOWNR_Tab[Val];
	}
	else
	{
		seg1&=0x00;
		seg2&=0x00;
		seg3&=0x00;
		seg4&=0x01;//0x00�����rpm��λȥ��
	}
	seg4 = seg4|0x01;//rpm�ı���ʾ

	Write_Addr_Dat_N(26, seg1,1);
	Write_Addr_Dat_N(28, seg2,1);
 	Write_Addr_Dat_N(30, seg3,1);
	Write_Addr_Dat_N(32, seg4,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_RelSpeed(int16_t dis_rel_speed)
 * ��    �ܣ�д���ұߵ�ʵ���ٶ�
 * ��    �룺dis_rel_speed:�ұ���������ٶ�
 * ��    ����int16_t dis_rel_speed
*****************************************************************
*/
void Display_Rel_Speed(int16_t dis_rel_speed)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	/***********ʵ��ת�ټ���**********/
	if(dis_rel_speed>999)
	{	
		Val=dis_rel_speed/1000;//ȡ��ǧλ
		seg1 = UP_Tab[Val];
	}
	else
	{
		seg1 = UP_Tab[0];//��ʾ0
	}	
	if(dis_rel_speed > 99)//����99ʱ
	{
		Val=dis_rel_speed/100;//ȡ����λ
		if(dis_rel_speed > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg2 = UP_Tab[Val];
	}
	else
	{
		seg2 = UP_Tab[0];//��ʾ0
	}
	if(dis_rel_speed > 9)//����9ʱ
	{
		Val=dis_rel_speed/10;//ȡ��ʮλ
		if(dis_rel_speed > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg3 = UP_Tab[Val];
	}
	else
	{
		seg3 = UP_Tab[0];//��ʾ0
	}
	Val=dis_rel_speed%10;//ȡ����λ
	seg4 = UP_Tab[Val];
	
	seg1 = seg1|0x01;//Բͼ���β��
	if(Speed.CwIcn)
		seg2 = seg2|0x01;//˳ʱ���������
	else
		seg3 = seg3|0x01;//��ʱ���������
//	seg4 = seg4|0x01;//����ͼ��
	if(SpeedIcn_ShowFlag)//����ʱ
    { 
		seg1&=0xfe;//Բͼ���β����ʧ
		seg2&=0xfe;//˳ʱ�����������ʧ
		seg3&=0xfe;//��ʱ�����������ʧ
    }
	
	Write_Addr_Dat_N(44, seg1,1);
	Write_Addr_Dat_N(46, seg2,1);
 	Write_Addr_Dat_N(48, seg3,1);
	Write_Addr_Dat_N(50, seg4,1);
}

void Display_P_Mode()
{
    uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;

    /**********��P��**********/
    if (PMode.Status) // ����PMode
    {
        if (!Pmode_ShowFlag)
        {
            seg1 = 0x3f;//P
            seg2 = 0x10;//-
            seg3 = DOWNR_Tab[PMode.Option];//��ʾ0
        }
        else
        {
            seg1 = 0x00;//����ʾ
            seg2 = 0x00;//����ʾ
            seg3 = 0x00;//����ʾ
        }
        seg5 = 0xff;//����ʾ
        seg6 = 0xff;//����ʾ
    }
    else // ������Pģʽ����ʾ
    {
        seg1 = 0x00;//����ʾ
        seg2 = 0x00;//����ʾ
        seg3 = 0x00;//����ʾ
        seg5 = 0x00;//����ʾ
        seg6 = 0x00;//����ʾ
    }
    /**********����ͼ��**********/
    if(Lock_Switch && !Lock_ShowFlag)
    {
        seg4 = 0x01;//����
    }
    else
    {
        seg4 = 0x00;//����ʾ����
    }
   
    Write_Addr_Dat_N(8, seg5,1);
    Write_Addr_Dat_N(16, seg6,1);
    Write_Addr_Dat_N(10, seg1,1);
	Write_Addr_Dat_N(12, seg2,1);
 	Write_Addr_Dat_N(14, seg3,1);
    Write_Addr_Dat_N(18, seg4,1);
}


/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Speed(float dT)
 * ��    �ܣ��ٶ���ʾ����
*****************************************************************
*/
void Deal_Speed(float dT)
{
    if(sys.Run_Status)//�����������
	{
		if(Speed.ADDMode==0)//�ڵ�������У��ٶ�δ����
		{ 
			if(Speed.Ctrl >= Speed.Display_Rel)//�����ٶȴ���ʵ���ٶ�
            {
                Speed.ADDMode = 1;//�������ģʽ��
            }
            else if(Speed.Ctrl < Speed.Display_Rel)//�����ٶ�С��ʵ���ٶ�
            {
                Speed.ADDMode = 2;//�������ģʽ��
            }
		}
		if(Speed.ADDMode==1)//�ڽ������ģʽ��
		{
			Speed.New = Speed.Rel;//��¼��ǰ�ٶ�
            if(Speed.New > Speed.Display_Rel)//��ǰ�ٶȴ�����ʾ�ٶ�
			{
				if(Speed.Display_Rel < Speed.New)
					Speed.Display_Rel+=1;//��ʾ��ǰ�ٶ�
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
		if(Speed.ADDMode == 2)//�ٶ��½�ģʽ��
        {
            Speed.New = Speed.Rel;//��¼��ǰ�ٶ�
            
            #if(Type == 0)//10L15L
            if(Speed.Ctrl < 80)//����80ת��ʾ����
                Speed.New = 80 - 30;
            #endif
            
            if(Speed.New < Speed.Display_Rel)//��ǰ�ٶ�С����һ���ٶ�
			{
				if(Speed.Display_Rel > Speed.New)
					Speed.Display_Rel -=1;//��ʾ��ǰ�ٶ�
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
		Speed.Display_Rel = 0;//ʵ���ٶ���ʾΪ��
		Speed.New =0;//���ڵ��ٶ�����
		Speed.ADDMode = 0;//�����ʾ����
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
	Speed.Display_Set = Speed.Set;//��ʾ�趨�ٶ�
	Time.Display_Set = Time.Set;//��ʾ�趨ʱ��
	Time.Display_Rel = Time.Rel + 59;//��ʾʵ��ʱ��+59s
    
    Display_P_Mode();
    Display_Set_Time(Time.Display_Set);
	Display_Rel_Time(Time.Display_Rel);
	Display_Set_Speed(Speed.Display_Set);
	Display_Rel_Speed(Speed.Display_Rel);
}
