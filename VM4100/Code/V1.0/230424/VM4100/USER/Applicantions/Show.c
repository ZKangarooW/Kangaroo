#include "Show.h"
#if(Type)
/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Time_ShowFlag,Speed_ShowFlag;//ʱ�䡢�ٶ���ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t TimeIcn_ShowFlag;//ʱ��ͼ����˸
uint8_t Tab[] = {0xF5,0x05,0xB6,0x97,0x47,0xD3,0xF3,0x85,0xF7,0xD7};//0��9
uint8_t Tab1[] = {0x5f,0x50,0x6B,0x79,0x74,0x3D,0x3F,0x58,0x7F,0x7D};//0��9

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
 * ����ԭ�ͣ� void Display(int16_t speed,int32_t time)
 * ��    �ܣ� ��ʾ�ٶȺ�ʱ��
*****************************************************************
*/
void Display(int16_t speed,int32_t time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	uint8_t SM,M;//ʱ��ĵ�λȡֵ	
	
	/***********�趨ת�ټ���**********/
	if(Speed_ShowFlag == 0)//����ʱ��˸
	{
		/***********speedǧλ***********/
		if(speed > 999)//����999ʱ
		{
			Val=speed/1000;//ȡ��ǧλ
			seg6&=0x80;seg6|=Tab1[Val];//����	
		}
		else
		{
			seg6&=0x80;seg6|=0x00;//����ʾ
		}
		
		/***********speed��λ***********/
		if(speed > 99)//����99ʱ
		{
			Val=speed/100;//ȡ����λ
			if(speed > 999)//����999ʱ
				Val=Val%10;//ȡ����λ
			seg5&=0x80;seg5|=Tab1[Val];//����	
		}
		else
		{
			seg5&=0x80;seg5|=0x00;//����ʾ
		}
		/***********speedʮλ***********/
		if(speed > 9)//����9ʱ
		{
			Val=speed/10;//ȡ��ʮλ
			if(speed > 99)//����99ʱ
				Val=Val%10;//ȡ��ʮλ
			seg4&=0x80;seg4|=Tab1[Val];//����	
		}
		else
		{
			seg4&=0x80;seg4|=0x00;//����ʾ
		}
		
		/***********speed��λ***********/
		seg1&=0xD0;seg1|=0x20;//����
	}
	else//����ʾ
	{
		seg1&=0xD0;seg1|=0x00;//����ʾ
		seg4&=0x80;seg2|=0x00;//����ʾ
		seg5&=0x80;seg3|=0x00;//����ʾ
		seg6&=0x80;seg1|=0x00;//����ʾ
	}
	
	/***********ʱ�����**********/
	if(time >= 3600)//����趨ʱ�����3600��ʱ
        Time_Unit=1;//��λ���Сʱ
    else
        Time_Unit=0;//��Ȼ���Ƿ�
	
	if(Time_Unit == 1)//ʱ�䵥λΪСʱʱ
	{
		SM=time/3600/10;//����ʮλ��λ��Сʱ��
		M=time/3600%10;//�����λ��λ��Сʱ��
	}
	else//ʱ�䵥λΪ��ʱ
	{
		SM=time/60/10;//����ʮ��λ��λ������
		M=time/60%10;//����ʮ��λ��λ������
	}
	
	if(Time_ShowFlag == 0)//ʱ������ʱ��˸
	{
		if(Set_Time > 0 && Time_State==0)//����ʱ�������ʱ��ʾʱ��
		{
			/***********set_time��һλ***********/
			seg2&=0x08;seg2|=Tab[SM];//����	
		
			/***********set_time�ڶ�λ***********/
			seg3&=0x08;seg3|=Tab[M];//����		
		}
		else//����ʱ��С�ڵ���0ʱ��ʾ��-- --��
		{
			seg2&=0x08;seg2|=0x02;//"-"
			seg3&=0x08;seg3|=0x02;//"-"
		}	
	}
	else//ʱ����˸
	{
		seg2&=0x08;seg2|=0x00;//����ʾ
		seg3&=0x08;seg3|=0x00;//����ʾ
	}

	/*************ģ����ʾͼ��*************/
	if(Set_Speed <= 800)
	{
		seg5&=0x7F;seg5|=0x80;//��ʾ����
		seg6&=0x7F;seg6|=0x80;//��ʾ԰
	}
	else if(Set_Speed > 800 && Set_Speed <= 1500)
	{
		seg5&=0x7F;seg5|=0x80;//��ʾ����
		seg6&=0x7F;seg6|=0x00;//����ʾ԰
	}
	else if(Set_Speed > 1500)
	{
		seg5&=0x7F;seg5|=0x00;//����ʾ����
		seg6&=0x7F;seg6|=0x00;//����ʾ԰
	}	
	
	/*************rpm*********************/
	if(TimeIcn_ShowFlag == 0)//ת�ٵ�λͼ����˸
	{
		seg1&=0xEF;seg1|=0x10;//��ʾrpm
	}
	else
	{
		seg1&=0xEF;seg1|=0x00;//����ʾrpm
	}
		
	/*************ʱ�䵥λͼ��***************/
	if(TimeIcn_ShowFlag == 0 && Set_Time >0 && Time_State == 0)//ʱ�䵥λͼ����˸
	{
		if(Time_Unit)//ʱ�䵥λΪСʱʱ
		{
			seg2&=0xF7;seg2|=0x08;//��ʾH
		}
		else//ʱ�䵥λΪ��ʱ
		{
			seg3&=0xF7;seg3|=0x08;//��ʾmin
		}
	}
	else
	{
		seg2&=0xF7;seg2|=0x00;//����ʾʱ�䵥λͼ��
		seg3&=0xF7;seg3|=0x00;//����ʾʱ�䵥λͼ��
	}
	
	/*************����ģʽͼ��***************/	
	if(Speed_Mode == 0)//�춯ģʽͼ��
	{
		seg1&=0x3F;seg1|=0xC0;//��ʾ+TOUCH
		seg4&=0x7F;seg4|=0x80;//��ʾRUN
	}
	else//����ģʽͼ��
	{
		seg1&=0x3F;seg1|=0x00;//����ʾ+TOUCH
		seg4&=0x7F;seg4|=0x80;//����ʾRUN
	}
	
	Write_Addr_Dat_N(0,seg1,1);//SEG9
	Write_Addr_Dat_N(1,seg2,1);//SEG10
	Write_Addr_Dat_N(3,seg3,1);//SEG11
	Write_Addr_Dat_N(5,seg4,1);//SEG12
	Write_Addr_Dat_N(7,seg5,1);//SEG13
	Write_Addr_Dat_N(9,seg6,1);//SEG14
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Deal_Speed(void)
 * ��    �ܣ� �ٶ���ʾ����
*****************************************************************
*/
uint16_t Rel_Val;
void Deal_Speed(void)
{
	if(Rel_Speed >= 2200)
		Rel_Val = 3000-(2600 - Rel_Speed)*2;
	else
		Rel_Val = Rel_Speed;
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//�����������
    {
        if(Speed_ADDMode == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed > Rel_Val)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New =0;//���ڵ��ٶ�����
                Speed_Last = 0;//֮ǰ���ٶ�����
                Speed_ADDMode = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed <= Display_Speed)//�����ٶ�С����ʾ�ٶ�
            {
                Speed_New=0;//���ڵ��ٶ�����
                Speed_Last = Rel_Val;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode==1)//�ڽ������ģʽ��
        { 
			if(Rel_Val >= Ctrl_Speed)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
			{
				Speed_ADDMode = 3;//�����ȶ�ģʽ
				return;
			}
			Speed_New = Rel_Val;//��¼��ǰ�ٶ�
			if(Speed_New > Speed_Last)//��ǰ�ٶȴ�����һ���ٶ�
				Display_Speed = Speed_New;//��ʾ��ǰ�ٶ�
			else//��ǰ�ٶ�С����һ���ٶ�
			{
				Display_Speed = Speed_Last;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
				Speed_New = Speed_Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
			}
			Speed_Last = Speed_New;//����ǰ�ٶȱ��� 				
        }
        else if(Speed_ADDMode == 2)//�ٶ��½�ģʽ��
        {
			if(Rel_Val <= Ctrl_Speed)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
			{
				Speed_ADDMode = 3;//�ȶ�ģʽ
				return;
			}
			Speed_New = Rel_Val;//��¼��ǰ�ٶ�
			if(Speed_New < Speed_Last)//��ǰ�ٶ�С����һ���ٶ�
				Display_Speed = Speed_New;//��ʾ��ǰ�ٶ�
			else//��ǰ�ٶȴ�����һ���ٶ�
			{
				Display_Speed = Speed_Last;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
				Speed_New = Speed_Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
			}
			Speed_Last = Speed_New;//����ǰ�ٶȱ���
        }
        else if(Speed_ADDMode == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_Speed = Ctrl_Speed;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode == 4)//�ٶ��½�ֹͣģʽ��
        {
            Speed_New = Rel_Val;//��¼��ǰ�ٶ�
            if(Speed_New < Speed_Last)//��ǰ�ٶ�С����һ���ٶ�
                Display_Speed = Speed_New;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_Speed = Speed_Last;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New = Speed_Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last = Speed_New;//����ǰ�ٶȱ���
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
            Display_Time = Set_Time; //��ʾ�趨ʱ�� 
        }            
        else//�ڲ�����ģʽ��
        {
            Deal_Speed();//�ٶ���ʾ���� 
            Display_Time = Ctrl_Time+59;//��ʾʵ��ʱ��
        }
    }
	Display(Display_Speed,Display_Time);//��ʾ��Ļ
}
#elif(Type == 0)
/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Time_ShowFlag,Speed_ShowFlag;//ʱ�䡢�ٶ���ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t TimeIcn_ShowFlag;//ʱ��ͼ����˸
uint8_t Tab[] = {0x5F,0x06,0x3D,0x2F,0x66,0x6B,0x7B,0x0E,0x7F,0x6F};//0��9

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
        Time_Unit=1;//��λ��ɷ�
    else
        Time_Unit=0;//��Ȼ������
	
	if(Time_Unit == 1)//ʱ�䵥λΪ����ʱ
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
		if(Set_Time > 0 && Time_State==0)//����ʱ�������ʱ��ʾʱ��
		{
			/***********set_time��һλ***********/
			seg4&=0x80;seg4|=Tab[SM];//����	
		
			/***********set_time�ڶ�λ***********/
			seg&=0x80;seg|=Tab[M];//����		
		}
		else//����ʱ��С�ڵ���0ʱ��ʾ��-- --��
		{
			seg4&=0x80;seg4|=0x20;//"-"
			seg&=0x80;seg|=0x20;//"-"
		}	
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
		seg4&=0x7F;seg4|=0x80;//��ʾrpm
	}
	else
	{
		seg4&=0x7F;seg4|=0x00;//����ʾrpm
	}
		
	
	/*************ʱ�䵥λͼ��***************/
	if(TimeIcn_ShowFlag == 0 && Set_Time >0 && Time_State == 0)//ʱ�䵥λͼ����˸
	{
		if(Time_Unit)//ʱ�䵥λΪ����ʱ
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
	
	/*************����ģʽͼ��***************/	
	if(Speed_Mode == 0)//�㶯ģʽͼ��
	{
		seg5&=0xF9;seg5|=0x06;//��ʾ�������������
	}
	else//����ģʽͼ��
	{
		seg5&=0xF9;seg5|=0x04;//��ʾ�����������
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
 * ����ԭ�ͣ� void Deal_Speed(void)
 * ��    �ܣ� �ٶ���ʾ����
*****************************************************************
*/
uint16_t Rel_Val;
void Deal_Speed(void)
{
	if(Rel_Speed >= 2200)
		Rel_Val = 3000-(2600 - Rel_Speed)*2;
	else
		Rel_Val = Rel_Speed;
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//�����������
    {
        if(Speed_ADDMode == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed > Rel_Val)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New =0;//���ڵ��ٶ�����
                Speed_Last = 0;//֮ǰ���ٶ�����
                Speed_ADDMode = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed <= Display_Speed)//�����ٶ�С����ʾ�ٶ�
            {
                Speed_New=0;//���ڵ��ٶ�����
                Speed_Last = Rel_Val;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode==1)//�ڽ������ģʽ��
        { 
			if(Rel_Val >= Ctrl_Speed)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
			{
				Speed_ADDMode = 3;//�����ȶ�ģʽ
				return;
			}
			Speed_New = Rel_Val;//��¼��ǰ�ٶ�
			if(Speed_New > Speed_Last)//��ǰ�ٶȴ�����һ���ٶ�
				Display_Speed = Speed_New;//��ʾ��ǰ�ٶ�
			else//��ǰ�ٶ�С����һ���ٶ�
			{
				Display_Speed = Speed_Last;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
				Speed_New = Speed_Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
			}
			Speed_Last = Speed_New;//����ǰ�ٶȱ��� 				
        }
        else if(Speed_ADDMode == 2)//�ٶ��½�ģʽ��
        {
			if(Rel_Val <= Ctrl_Speed)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
			{
				Speed_ADDMode = 3;//�ȶ�ģʽ
				return;
			}
			Speed_New = Rel_Val;//��¼��ǰ�ٶ�
			if(Speed_New < Speed_Last)//��ǰ�ٶ�С����һ���ٶ�
				Display_Speed = Speed_New;//��ʾ��ǰ�ٶ�
			else//��ǰ�ٶȴ�����һ���ٶ�
			{
				Display_Speed = Speed_Last;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
				Speed_New = Speed_Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
			}
			Speed_Last = Speed_New;//����ǰ�ٶȱ���
        }
        else if(Speed_ADDMode == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_Speed = Ctrl_Speed;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode == 4)//�ٶ��½�ֹͣģʽ��
        {
            Speed_New = Rel_Val;//��¼��ǰ�ٶ�
            if(Speed_New < Speed_Last)//��ǰ�ٶ�С����һ���ٶ�
                Display_Speed = Speed_New;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_Speed = Speed_Last;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New = Speed_Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last = Speed_New;//����ǰ�ٶȱ���
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
            Display_Time = Ctrl_Time;//��ʾʵ��ʱ��
        }
        else if(sys.SetMode_Option == 2)//������ʱ��ģʽ��
        {
            Deal_Speed();//�ٶ���ʾ����
            Display_Time = Set_Time; //��ʾ�趨ʱ�� 
        }            
        else//�ڲ�����ģʽ��
        {
            Deal_Speed();//�ٶ���ʾ���� 
            Display_Time = Ctrl_Time;//��ʾʵ��ʱ��
        }
    }
	Display(Display_Speed/10,Display_Time);//��ʾ��Ļ
}

#endif
