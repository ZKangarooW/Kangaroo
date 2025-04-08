#include "Show.h"

/**********ȫ�ֱ�������******/
uint16_t Twinkle_Time1,Twinkle_Time2;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Run_Flag;//������˸ͼ��
uint8_t Speed_ShowFlag,Time_ShowFlag;//�ٶȡ�ʱ����ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t DOWNL_Tab[]={0x77,0X24,0x5d,0x6d,0x2e,0x6b,0x7b,0x25,0x7f,0x6f};
uint8_t UP_Tab[]={0xee,0x24,0xba,0xb6,0x74,0xd6,0xde,0xa4,0xfe,0xf6};
uint8_t DOWNR_Tab[]={0xee,0x48,0xba,0xda,0x5c,0xd6,0xf6,0x4a,0xfe,0xde};

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_ShowFlag(float dT)
 * ��    �ܣ� ��˸���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Check_ShowFlag(float dT)
{
    if(sys.Run_Status)//����ʱ
        Run_Flag = ~Run_Flag;//����ʱ��˸
	
	if(Twinkle_Time1 && EC11A[1].EC11A_Knob==0)//��˸��û�в�����ťʱ
    {
        Twinkle_Time1 -= 0.5f;//��˸��ʱ
		Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
        if(Twinkle_Time1 == 0)//�����˸����
        {
			SpeedSet_Flag = 1;
			Beep_Time = 0.1;
        }
    }
	else
		Speed_ShowFlag = 0;//�ٶ���˸����

	if(Twinkle_Time2 && EC11A[0].EC11A_Knob==0)//��˸��û�в�����ťʱ
    {
        Twinkle_Time2 -= 0.5f;//��˸��ʱ
		Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
        if(Twinkle_Time2 == 0)//�����˸����
        {
			TimeSet_Flag = 1;
            Beep_Time = 0.1;
        }        
    }
	else
		Time_ShowFlag = 0;//ʱ����˸����
}

/*
*****************************************************************
 * ����ԭ�ͣ� void LCD_Light(short LCD_Status) 
 * ��    �ܣ� �򿪺͹رձ�����ʾ
 * ��    ��:  LCD_Status��1���򿪱��� 0���رձ���
 * ��    ���� short LCD_Status
*****************************************************************
*/
void LCD_Light(short LCD_Status)
{
    switch(LCD_Status)
    {
        case 0 :
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);//�����pwm
            break ;
        case 1 :
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 45);//�����pwm
            break ;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Display_Set_Time(uint32_t dis_set_time)
 * ��    �ܣ� д����ߵ��趨ʱ��
 * ��    ��:  dis_set_time ����������ʱ��
 * ��    ���� uint32_t dis_set_time
*****************************************************************
*/
void Display_Set_Time(uint32_t dis_set_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
	
	SH=dis_set_time/3600/10;//����ʮλ��λ��Сʱ��
	H=dis_set_time/3600%10;//�����λ��λ��Сʱ��
	SM=dis_set_time%3600/60/10;//����ʮ��λ��λ�ķ�����
	M=dis_set_time%3600/60%10;//�������λ��λ�ķ�����
	
	seg1 = DOWNL_Tab[SH];//ʱ��ʮλ��λ��Сʱ��
	seg2 = DOWNL_Tab[H];//ʱ���λ��λ��Сʱ��
	seg3 = DOWNL_Tab[SM];//ʱ��ʮ��λ��λ�ķ�����
	seg4 = DOWNL_Tab[M];//ʱ�����λ��λ�ķ�����

	seg2 = seg2|0x80;//�趨ʱ��ð�ţ����棩
//	seg3 = seg3|0x80;//�趨ʱ��С���㣨���棩
	seg4 = seg4|0x80;//�趨ʱ��min�ı���ʾ
	
	if(Time_State == 0)//û������ʱ��,��ʾ��--:--��
	{
		seg1=(seg1&0x80)|0x08;
		seg2=(seg2&0x80)|0x08;
		seg3=(seg3&0x80)|0x08;
		seg4=(seg4&0x00)|0x08;//0x00����λ"min"ȥ��
	}
	
	if(Time_ShowFlag && EC11A[0].EC11A_Knob == 0 && Time_State == 1)//ʱ�䵽����ť�޲���ʱ
	{
		seg1&=0x00;
		seg2&=0x00;
		seg3&=0x00;
		seg4&=0x80;
	}
	
	Write_Addr_Dat_N(0, seg1,1);
	Write_Addr_Dat_N(2, seg2,1);
 	Write_Addr_Dat_N(4, seg3,1);
	Write_Addr_Dat_N(6, seg4,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Display_Rel_Time(uint32_t dis_rel_time)
 * ��    �ܣ� д����ߵ��趨ʱ��
 * ��    ��:  dis_rel_time ����������ʱ��
 * ��    ���� uint32_t dis_rel_time
*****************************************************************
*/
void Display_Rel_Time(uint32_t dis_rel_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
	
	SH=dis_rel_time/3600/10;//����ʮλ��λ��Сʱ��
	H=dis_rel_time/3600%10;//�����λ��λ��Сʱ��
	SM=dis_rel_time%3600/60/10;//����ʮ��λ��λ�ķ�����
	M=dis_rel_time%3600/60%10;//�������λ��λ�ķ�����
	
	seg1 = UP_Tab[SH];//ʱ��ʮλ��λ��Сʱ��
	seg2 = UP_Tab[H];//ʱ���λ��λ��Сʱ��
	seg3 = UP_Tab[SM];//ʱ��ʮ��λ��λ�ķ�����
	seg4 = UP_Tab[M];//ʱ�����λ��λ�ķ�����
	
//	seg1 = seg1|0x01;//�¶ȷ��š��桱ͼ�꣨���棩
	seg2 = seg2|0x01;//ʵ��ʱ��ð�ţ����棩
//	seg3 = seg3|0x01;//ʵ��ʱ��С���㣨���棩
	seg4 = seg4|0x01;//ʱ��ͼ�꣨���棩
	
	if(Time_State == 0)//û������ʱ��,��ʾ��--:--��
	{
		seg1=(seg1&0x01)|0x10;
		seg2=(seg2&0x01)|0x10;
		seg3=(seg3&0x01)|0x10;
		seg4=(seg4&0x01)|0x10;
	}
    if(sys.Run_Status == 1 && Run_Flag > 1 && DownTime_Over == 0 && Time_State == 1)//����ʱ
    {
		seg2&=0xFE;//ʵ��ʱ��ð�ţ����棩��ʧ
		seg4&=0xFE;//ʱ��ͼ�꣨���棩��ʧ
	}
	Write_Addr_Dat_N(54, seg1,1);
	Write_Addr_Dat_N(52, seg2,1);
 	Write_Addr_Dat_N(50, seg3,1);
	Write_Addr_Dat_N(48, seg4,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Display_SetSpeed(uint16_t dis_set_speed)
 * ��    �ܣ� д���ұߵ��趨�ٶ�
 * ��    ��:  dis_set_speed �ұ���������ٶ�
 * ��    ���� uint16_t dis_set_speed
*****************************************************************
*/
void Display_Set_Speed(uint16_t dis_set_speed)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	
	//�趨�ٶ�
	if(dis_set_speed>999)
	{	
		seg1=DOWNR_Tab[dis_set_speed/1000]; 
		seg2=DOWNR_Tab[dis_set_speed/100%10]; 
		seg3=DOWNR_Tab[dis_set_speed/10%10]; 
		seg4=DOWNR_Tab[dis_set_speed%10];
	}	
	else if(dis_set_speed >99)
	{
		seg1=DOWNR_Tab[0]; 
		seg2=DOWNR_Tab[dis_set_speed/100];
		seg3=DOWNR_Tab[dis_set_speed/10%10];
		seg4=DOWNR_Tab[dis_set_speed%10];
	}
	else if(dis_set_speed >9)
	{
		seg1=DOWNR_Tab[0]; 
		seg2=DOWNR_Tab[0];
		seg3=DOWNR_Tab[dis_set_speed/10];
		seg4=DOWNR_Tab[dis_set_speed%10];
	}	
	else
	{
		seg1=DOWNR_Tab[0]; 
		seg2=DOWNR_Tab[0];
		seg3=DOWNR_Tab[0];
		seg4=DOWNR_Tab[dis_set_speed%10];
	}	
	
	if(Speed_ShowFlag && EC11A[1].EC11A_Knob == 0)//ʱ�䵽����ť�޲���ʱ
	{
		seg1&=0x00;
		seg2&=0x00;
		seg3&=0x00;
		seg4&=0x01;
	}
	seg4 = seg4|0x01;//rpm�ı���ʾ
  
	Write_Addr_Dat_N(26, seg1,1);
	Write_Addr_Dat_N(28, seg2,1);
 	Write_Addr_Dat_N(30, seg3,1);
	Write_Addr_Dat_N(32, seg4,1);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Display_RelSpeed(uint16_t dis_rel_speed)
 * ��    �ܣ� д���ұߵ�ʵ���ٶ�
 * ��    ��:  dis_rel_speed �ұ���������ٶ�
 * ��    ���� uint16_t dis_rel_speed
*****************************************************************
*/
void Display_Rel_Speed(uint16_t dis_rel_speed)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;;
	
	//�趨�ٶ�
	if(dis_rel_speed>999)
	{	
		seg1=UP_Tab[dis_rel_speed/1000]; 
		seg2=UP_Tab[dis_rel_speed/100%10]; 
		seg3=UP_Tab[dis_rel_speed/10%10]; 
		seg4=UP_Tab[dis_rel_speed%10];
	}	
	else if(dis_rel_speed >99)
	{
		seg1=UP_Tab[0]; 
		seg2=UP_Tab[dis_rel_speed/100];
		seg3=UP_Tab[dis_rel_speed/10%10];
		seg4=UP_Tab[dis_rel_speed%10];
	}
	else if(dis_rel_speed >9)
	{
		seg1=UP_Tab[0]; 
		seg2=UP_Tab[0];
		seg3=UP_Tab[dis_rel_speed/10];
		seg4=UP_Tab[dis_rel_speed%10];
	}	
	else
	{
		seg1=UP_Tab[0]; 
		seg2=UP_Tab[0];
		seg3=UP_Tab[0];
		seg4=UP_Tab[dis_rel_speed%10];
	}	
	seg1 = seg1|0x01;//Բͼ���β��
//	seg2 = seg2|0x01;//˳ʱ���������
	seg3 = seg3|0x01;//��ʱ���������
//	seg4 = seg4|0x01;//����ͼ��
//	if(sys.Run_Status == 1 && Run_Flag > 1 && Set_Speed > 0 && Rel_Speed)//����ʱ
	if(sys.Run_Status == 1 && Run_Flag > 1 )//����ʱ
    {
        seg1&=0xfe;//Բͼ���β����ʧ
//	seg2&=0xfe;//˳ʱ�����������ʧ
        seg3&=0xfe;//��ʱ�����������ʧ
    }
	Write_Addr_Dat_N(46, seg1,1);
	Write_Addr_Dat_N(44, seg2,1);
 	Write_Addr_Dat_N(42, seg3,1);
	Write_Addr_Dat_N(40, seg4,1);
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
            if(Ctrl_Speed >= Display_RelSpeed)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New =0;//���ڵ��ٶ�����
                Speed_Last = 0;//֮ǰ���ٶ�����
                Speed_ADDMode = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed < Display_RelSpeed)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New=0;//���ڵ��ٶ�����
                Speed_Last = Display_RelSpeed;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode==1)//�ڽ������ģʽ��
        { 
			if(sys.Motor_Stop == 0)
			{
				if(Rel_Speed >= Ctrl_Speed)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
				{
					Speed_ADDMode = 3;//�����ȶ�ģʽ
					return;
				}
			}
            Speed_New = Rel_Speed;//��¼��ǰ�ٶ�
            if(Speed_New > Speed_Last)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed = Speed_New;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed = Speed_Last;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New = Speed_Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last = Speed_New;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode == 2)//�ٶ��½�ģʽ��
        {
			if(sys.Motor_Stop == 0)
			{
				if(Param.type==0)
				{
					if(Rel_Speed-500 <= Ctrl_Speed)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
					{
						Speed_ADDMode = 3;//�ȶ�ģʽ
						return;
					}
				}
				else if(Param.type == 1)
				{
					if(Rel_Speed <= Ctrl_Speed)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
					{
						Speed_ADDMode = 3;//�ȶ�ģʽ
						return;
					}
				}
			}
			if(Param.type==0)
			{
				Speed_New = Rel_Speed-500;//��¼��ǰ�ٶ�
			}
			else if(Param.type == 1)
			{
				Speed_New = Rel_Speed;//��¼��ǰ�ٶ�
			}
            if(Speed_New < Speed_Last)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed = Speed_New;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed = Speed_Last;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New = Speed_Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last = Speed_New;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed = Ctrl_Speed;//��ʾ�����ٶ�
        }
	}
	else
	{
		Speed_New =0;//���ڵ��ٶ�����
		Speed_Last = 0;//֮ǰ���ٶ�����
		Speed_ADDMode = 0;
		Display_RelSpeed = 0;
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
	Deal_Speed();
	Display_SetSpeed = Set_Speed;
	Display_SetTime = Set_Time;//��ʾ�趨ʱ��
	Display_CtrlTime = Ctrl_Time+59;//��ʾʵ��ʱ��

	
    Display_Set_Time(Display_SetTime);
	Display_Rel_Time(Display_CtrlTime);
	Display_Set_Speed(Display_SetSpeed);
	Display_Rel_Speed(Display_RelSpeed);
}
