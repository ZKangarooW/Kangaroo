#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Time_ShowFlag,Speed_ShowFlag;//ʱ�䡢�ٶ���ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t TimeIcn_ShowFlag,SpeedIcn_ShowFlag;//ʱ��ͼ����˸,�ٶȵ�λͼ����˸
uint8_t Tab[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x6F};//0��9

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_ShowFlag(float dT)
 * ��    �ܣ� ��˸���
 * ��    ��:  dT:ִ������
 * ��    ���� float dT
*****************************************************************
*/  
void Check_ShowFlag(float dT)
{
	static float T,T1;
    if(sys.Run_Status == 1)//ϵͳ������
	{
		T1 += dT;//��˸��ʱ
		if(T1 >= 0.5f)//����0.5S��
		{
			if(Set_Time > 0)//ֻ���趨ʱ�����0����˸
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//������˸
			else
				TimeIcn_ShowFlag = 0;//ʱ��ð��ͼ�곣��
			SpeedIcn_ShowFlag = ~SpeedIcn_ShowFlag;//�ٶȵ�λ������˸
			T1 = 0;//��ʱ����
		}
	}
    else//û�����������
	{
		SpeedIcn_ShowFlag = 0;//�ٶȵ�λͼ�곣��
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
 * ����ԭ�ͣ� void Display(int16_t speed,int32_t time)
 * ��    �ܣ� ��ʾ�ٶȺ�ʱ��
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
	SH=time/3600/10;//����ʮλ��λ��Сʱ��
	H=time/3600%10;//�����λ��λ��Сʱ��
	SM=time%3600/60/10;//����ʮ��λ��λ�ķ�����
	M=time%3600/60%10;//�������λ��λ�ķ�����
	
	if(Time_ShowFlag == 0)//ʱ������ʱ��˸
	{
		if(Set_Time > 0)//����ʱ�������ʱ��ʾʱ��
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
		seg4&=0x7F;seg4|=0x80;//��ʾrpm
	}
	else
	{
		seg4&=0x7F;seg4|=0x00;//����ʾrpm
	}
	/*************ʱ��ð��ͼ��***************/
	if(TimeIcn_ShowFlag == 0)//ʱ��ð����˸
	{
		seg6&=0x7F;seg6|=0x80;//��ʾʱ��ð��
	}
	else
	{
		seg6&=0x7F;seg6|=0x00;//����ʾʱ��ð��
	}
	/*************ʱ�䵥λͼ��***************/
	seg8&=0x7F;seg8|=0x80;//��ʾmin
	
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
 * ����ԭ�ͣ� void Deal_Speed(void)
 * ��    �ܣ� �ٶ���ʾ����
*****************************************************************
*/
void Deal_Speed(void)
{
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//�����������
    {
        if(Speed_ADDMode == 0)//�ڵ�������У��ٶ�δ����
        {
			Display_Speed = Speed;
            if(Ctrl_Speed > Rel_Speed)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_ADDMode = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed <= Display_Speed)//�����ٶ�С����ʾ�ٶ�
            {
                Speed_ADDMode = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode==1)//�ڽ������ģʽ��
        { 
			if(Display_Speed< Rel_Speed)
				Display_Speed++;
            if(Display_Speed >= Ctrl_Speed)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode = 3;//�����ȶ�ģʽ
                return;
            }
        }
        else if(Speed_ADDMode == 2)//�ٶ��½�ģʽ��
        {
			if(Display_Speed>Rel_Speed)
				Display_Speed--;
            if(Rel_Speed <= Ctrl_Speed)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode = 3;//�ȶ�ģʽ
                return;
            }
        }
        else if(Speed_ADDMode == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_Speed = Ctrl_Speed;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode == 4)//�ٶ��½�ֹͣģʽ��
        {
			if(Display_Speed>Rel_Speed)
				Display_Speed--;
            if(Rel_Speed <= 0)//ʵ���ٶ�С�ڵ���0
            {
                Speed_ADDMode = 3;//�ȶ�ģʽ
                return;
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
	if(sys.Run_Status == 0)//������
    {
        Display_Speed  = Set_Speed;//��ʾ�趨�ٶ�
        Display_Time  = Set_Time;//��ʾ�趨ʱ��
    }
    else//������
    {
        if(sys.SetMode_Option == 1)//�������ٶ�ģʽ��
        {
            Display_Speed  = Set_Speed;//��ʾ�趨�ٶ�
            Display_Time = Ctrl_Time+59;//��ʾʵ��ʱ��
        }
        else if(sys.SetMode_Option == 2)//������ʱ��ģʽ��
        {
            Deal_Speed();//�ٶ���ʾ����
            Display_Time = Set_Time;//��ʾ�趨ʱ�� 
        }            
        else//�ڲ�����ģʽ��
        {
            Deal_Speed();//�ٶ���ʾ���� 
            Display_Time = Ctrl_Time+59;//��ʾʵ��ʱ��
        }
    }
	Display(Display_Speed,Display_Time);//��ʾ��Ļ
}
