#include "Show_9.h"

/**********ȫ�ֱ�������******/
uint16_t Twinkle_Time;//��˸ʱ��
uint8_t Tab[] = {0x77,0x12,0x6B,0x5B,0x1E,0x5D,0x7D,0x13,0x7F,0x5F};//0��9
uint8_t Tab1[] = {0xEE,0x48,0xD6,0xDA,0x78,0xBA,0xBE,0xC8,0xFE,0xFA};//0��9

/**********�ֲ���������******/
uint8_t seg15_Flag;//������ʾ��ʵ���ٶ����һλ�м��б�ܸ����������̫Զ
uint8_t Speed_ShowFlag,Temp_ShowFlag,Time_ShowFlag;//�ٶȡ��¶ȡ�ʱ����ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t Work_All_Time;//ȫ����λ����ʱ��˸�Ĺ�λʱ��
uint8_t Speed_Icn,Run_Flag;//������˸ͼ��

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_ShowFlag(uint16_t dT)
 * ��    �ܣ� ��˸���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Check_ShowFlag(uint16_t dT)
{
    if(Work_All)//����ȫ������
        Work_All_Time = ~Work_All_Time;//ѡ�й�λ����˸
    if(Run_Status)//����ʱ
	{
		Speed_Icn++;
		if(Speed_Icn>3)
			Speed_Icn = 1;
        Run_Flag = ~Run_Flag;//����ʱ��˸
	}
	else
	{
		Run_Flag = 0;
		Speed_Icn = 0;
	}
    if(SetMode_Option == 0)//���û������ѡ���У��򶼵���������˸
    {
        Speed_ShowFlag = 0;//����
        Temp_ShowFlag = 0;//����
        Time_ShowFlag = 0;//����
        Twinkle_Time = 0;//��˸��ʱ����
        return;
    }
    if(Twinkle_Time && EC11A_Knob==0)//��˸��û�в�����ťʱ
    {
        Twinkle_Time -= dT;//��˸��ʱ
        if(SetMode_Option == 1)//�����ٶ�
        {
            Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
            Temp_ShowFlag = 0;//�¶ȳ���
            Time_ShowFlag = 0;//ʱ�䳣��
        }
        else if(SetMode_Option == 2)//�����¶�
        {
            Speed_ShowFlag = 0;//�ٶȳ���
            Temp_ShowFlag = ~Temp_ShowFlag;//�¶���˸
            Time_ShowFlag = 0;//ʱ�䳣��
        }
        else if(SetMode_Option == 3)//����ʱ��
        {
            Speed_ShowFlag = 0;//�ٶȳ���
            Temp_ShowFlag = 0;//�¶ȳ���
            Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
        }
        if(Twinkle_Time == 0)//�����˸����
        {
            SetMode_Option = 0;//ģʽѡ������
        }        
    }
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
        case 0 :__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0); break ;//�����pwm    
        case 1 :
            HAL_GPIO_WritePin(LED_KEY_GPIO_Port, LED_KEY_Pin, GPIO_PIN_RESET);//���ͱ����ƽ�ź�
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 105);//�����pwm
            break ;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Speed_One(uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3)
 * ��    �ܣ���ʾ��һ�е��趨�ٶȺ��»��ߺ��м��ͼ��
 * ��    ��: Speed_L1 L1���ٶ� Speed_L2 L2���ٶ� Speed_L3 L3���ٶ�
 * ��    ����uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3
*****************************************************************
*/
void Display_Speed_One(uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9,seg10;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;seg10=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	/***********L1ת�ټ���**********/
	/***********Llǧλ***********/
	if(Speed_L1 > 999)//����999ʱ
	{		
		seg3&=0x7F;seg3|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg3&=0x7F;seg3|=0x00;//����ʾ
    }
	/***********Ll��λ***********/
	if(Speed_L1 > 99)//����99ʱ
	{
		Val=Speed_L1/100;//ȡ����λ������
		if(Speed_L1 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg3&=0x80;seg3|=Tab[Val];//����	
	}
	else
	{
		seg3&=0x80;seg3|=Tab[0];//����0	
	}
	/***********Llʮλ***********/
	if(Speed_L1 > 9)//����9ʱ
	{
		Val=Speed_L1/10;//ȡ��ʮλ������
		if(Speed_L1 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg4&=0x80;seg4|=Tab[Val];//����	
	}
	else
	{
		seg4&=0x80;seg4|=Tab[0];//����0
	}
	/***********L1��λ***********/
	seg4&=0x7F;seg4|=0x80;//����0
	
	/***********L2ת�ټ���**********/
	/***********L2ǧλ***********/
	if(Speed_L2 > 999)//����999ʱ
	{		
		seg5&=0x7F;seg5|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg5&=0x7F;seg5|=0x00;//����ʾ
    }
	/***********L2��λ***********/
	if(Speed_L2 > 99)//����99ʱ
	{
		Val=Speed_L2/100;//ȡ����λ������
		if(Speed_L2 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg5&=0x80;seg5|=Tab[Val];//����	
	}
	else
	{
		seg5&=0x80;seg5|=Tab[0];//����0
	}
	/***********L2ʮλ***********/
	if(Speed_L2 > 9)//����9ʱ
	{
		Val=Speed_L2/10;//ȡ��ʮλ������
		if(Speed_L2 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg6&=0x80;seg6|=Tab[Val];//����	
	}
	else
	{
		seg6&=0x80;seg6|=Tab[0];//����0
	}
	/***********L2��λ***********/
	seg6&=0x7F;seg6|=0x80;//����0
	
	/***********L3ת�ټ���**********/
	/***********L3ǧλ***********/
	if(Speed_L3 > 999)//����999ʱ
	{		
		seg7&=0x7F;seg7|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg7&=0x7F;seg7|=0x00;//����ʾ
    }
	/***********L3��λ***********/
	if(Speed_L3 > 99)//����99ʱ
	{
		Val=Speed_L3/100;//ȡ����λ������
		if(Speed_L3 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg7&=0x80;seg7|=Tab[Val];//����	
	}
	else
	{
		seg7&=0x80;seg7|=Tab[0];//����0
	}
	/***********L3ʮλ***********/
	if(Speed_L3 > 9)//����9ʱ
	{
		Val=Speed_L3/10;//ȡ��ʮλ������
		if(Speed_L3 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg8&=0x80;seg8|=Tab[Val];//����
	}
	else
	{
		seg8&=0x80;seg8|=Tab[0];//����0
	}
	/***********L3��λ***********/
	seg8&=0x7F;seg8|=0x80;//����0
	
	if(Work_All)//��ȫ������ʱ
    {
		seg10&=0x1F;seg10|=0xE0;//L1��L2��L3���»��ߵ���
		seg2&=0xF8;seg2|=0x07;//L4��L5��L6���»��ߵ���
        seg1&=0xF8;seg1|=0x07;//L7��L8��L9���»��ߵ���
        if(Work_All_Time)//��ȫ��������ѡ�й�λ��˸
        {        
            switch(Work_Option)
            {
                case 1:seg10&=0x1F;seg10|=0xC0;//L1�»���Ϩ��
                    break;
				case 2:seg10&=0x1F;seg10|=0xA0;//L2�»���Ϩ��
                    break;
				case 3:seg10&=0x1F;seg10|=0x60;//L3�»���Ϩ��
                    break;
                case 4:seg2&=0xF8;seg2|=0x06;//L4�»���Ϩ��
                    break;
                case 5:seg2&=0xF8;seg2|=0x05;//L5�»���Ϩ��
                    break;
				case 6:seg2&=0xF8;seg2|=0x03;//L6�»���Ϩ��
                    break;
				case 7:seg1&=0xF8;seg1|=0x06;//L7�»���Ϩ��
                    break;
                case 8:seg1&=0xF8;seg1|=0x05;//L8�»���Ϩ��
                    break;
				case 9:seg1&=0xF8;seg1|=0x03;//L9�»���Ϩ��
                    break;
                default:
					seg10&=0x1F;seg10|=0xE0;//L1��L2��L3���»��ߵ���
					seg2&=0xF8;seg2|=0x07;//L4��L5��L6���»��ߵ���
					seg1&=0xF8;seg1|=0x07;//L7��L8��L9���»��ߵ���
                    break;
            }
        }
    }
    else
    {		 		 
        switch(Work_Option)//��λ��ѡ��
        {
            case 1: seg10&=0x1F;seg10|=0x20;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x00;//��ʾL1������»���
                break;
            case 2: seg10&=0x1F;seg10|=0x40;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x00;//��ʾL2������»���
                break;
            case 3: seg10&=0x1F;seg10|=0x80;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x00;//��ʾL3������»���
					break;
			case 4: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x01;
					seg1&=0xF8;seg1|=0x00;//��ʾL4����»���
					break;
			case 5: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x02;
					seg1&=0xF8;seg1|=0x00;//��ʾL5����»���
					break;
			case 6: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x04;
					seg1&=0xF8;seg1|=0x00;//��ʾL6����»���
					break;
			case 7: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x01;//��ʾL7����»���
					break;
			case 8: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x02;//��ʾL8����»���
					break;
			case 9: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x04;//��ʾL9����»���
					break;
            default:     
                break;
        }
    }	
	if(Run_Status==1 && Speed_Icn > 0 && Set_Speed.L0 > 0 && Rel_Speed.L0)  //����ʱ
    {
        if(Speed_Icn == 1)
		{
			seg9&=0xF8;seg9|=0x03;
		}
		else if(Speed_Icn == 2)
		{
			seg9&=0xF8;seg9|=0x06;
		}
		else if(Speed_Icn == 3)
		{
			seg9&=0xF8;seg9|=0x05;
		}  
    }
	else
	{
		seg9&=0xF8;seg9|=0x07;
	}
	#if(Temp_TYPE == 1)//���ó�Ϊ���ȿ�
	seg9&=0xE7;seg9|=0x18;//�¶�ͼ��
	if(Run_Status == 1 && Temp_State == 1 && Run_Flag > 1)//����ʱ
    {
        seg9&=0xE7;seg9|=0x00;//�¶�ͼ����ʧ
    }
	#endif
	seg9&=0xDF;seg9|=0x20;//ʱ��ͼ��
	if(Run_Status == 1 && Run_Flag > 1 && DownTime_Over.L0 == 0 && RelTime_State.L0 == 1)//����ʱ
    {
        seg9&=0xDF;seg9|=0x00;//ʱ��ͼ����ʧ
    }
	Write_Addr_Dat_N(0, seg1, 1);
	Write_Addr_Dat_N(1, seg2, 1);
	Write_Addr_Dat_N(2, seg3, 1);
	Write_Addr_Dat_N(3, seg4, 1);
	Write_Addr_Dat_N(4, seg5, 1);
	Write_Addr_Dat_N(5, seg6, 1);
	Write_Addr_Dat_N(6, seg7, 1);
	Write_Addr_Dat_N(7, seg8, 1);
	Write_Addr_Dat_N(8, seg9, 1);
	Write_Addr_Dat_N(25, seg10, 1);//L1\L2\L3���»���
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Speed_Two(uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6)
 * ��    �ܣ���ʾ�ڶ��е��趨�ٶ�
 * ��    ��: Speed_L4 L4���ٶ� Speed_L5 L5���ٶ� Speed_L6 L6���ٶ�
 * ��    ����uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6
*****************************************************************
*/
void Display_Speed_Two(uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	/***********L4ת�ټ���**********/
	/***********L4ǧλ***********/
	if(Speed_L4 > 999)//����999ʱ
	{		
		seg1&=0xFE;seg1|=0x01;//��ʾ1
	}
	else//С��999ʱ
    {
        seg1&=0xFE;seg1|=0x00;//����ʾ
    }
	/***********L4��λ***********/
	if(Speed_L4 > 99)//����99ʱ
	{
		Val=Speed_L4/100;//ȡ����λ������
		if(Speed_L4 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg1&=0x01;seg1|=Tab1[Val];//����
	}
	else
	{
		seg1&=0x01;seg1|=Tab1[0];//����0
	}
	/***********L4ʮλ***********/
	if(Speed_L4 > 9)//����9ʱ
	{
		Val=Speed_L4/10;//ȡ��ʮλ������
		if(Speed_L4 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg2&=0x01;seg2|=Tab1[Val];//����	
	}
	else
	{
		seg2&=0x01;seg2|=Tab1[0];//����0	
	}
	/***********L4��λ***********/
	seg2&=0xFE;seg2|=0x01;//����0
	
	/***********L5ת�ټ���**********/
	/***********L5ǧλ***********/
	if(Speed_L5 > 999)//����999ʱ
	{		
		seg3&=0xFE;seg3|=0x01;//��ʾ1
	}
	else//С��999ʱ
    {
        seg3&=0xFE;seg3|=0x00;//����ʾ
    }
	/***********L5��λ***********/
	if(Speed_L5 > 99)//����99ʱ
	{
		Val=Speed_L5/100;//ȡ����λ������
		if(Speed_L5 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg3&=0x01;seg3|=Tab1[Val];//����
	}
	else
	{
		seg3&=0x01;seg3|=Tab1[0];//����0
	}
	/***********L5ʮλ***********/
	if(Speed_L5 > 9)//����9ʱ
	{
		Val=Speed_L5/10;//ȡ��ʮλ������
		if(Speed_L5 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg4&=0x01;seg4|=Tab1[Val];//����
	}
	else
	{
		seg4&=0x01;seg4|=Tab1[0];//����0
	}
	/***********L5��λ***********/
	seg4&=0xFE;seg4|=0x01;//����0
	
	/***********L6ת�ټ���**********/
	/***********L6ǧλ***********/
	if(Speed_L6 > 999)//����999ʱ
	{		
		seg5&=0xFE;seg5|=0x01;//��ʾ1
	}
	else//С��999ʱ
    {
        seg5&=0xFE;seg5|=0x00;//����ʾ
    }
	/***********L6��λ***********/
	if(Speed_L6 > 99)//����99ʱ
	{
		Val=Speed_L6/100;//ȡ����λ������
		if(Speed_L6 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg5&=0x01;seg5|=Tab1[Val];//����
	}
	else
	{
		seg5&=0x01;seg5|=Tab1[0];//����0
	}
	/***********L6ʮλ***********/
	if(Speed_L6 > 9)//����9ʱ
	{
		Val=Speed_L6/10;//ȡ��ʮλ������
		if(Speed_L6 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg6&=0x01;seg6|=Tab1[Val];//����	
	}
	else
	{
		seg6&=0x01;seg6|=Tab1[0];//����0
	}
	/***********L6��λ***********/
	seg6&=0xFE;seg6|=0x01;//����0
	
	Write_Addr_Dat_N(26, seg1, 1);
	Write_Addr_Dat_N(27, seg2, 1);
	Write_Addr_Dat_N(28, seg3, 1);
	Write_Addr_Dat_N(29, seg4, 1);
	Write_Addr_Dat_N(30, seg5, 1);
	Write_Addr_Dat_N(31, seg6, 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Speed_Three(uint16_t Speed_L7,uint16_t Speed_L8,uint16_t Speed_L9)
 * ��    �ܣ���ʾ�����е��趨�ٶ�
 * ��    ��: Speed_L7 L7���ٶ� Speed_L8 L8���ٶ� Speed_L9 L9���ٶ�
 * ��    ����uint16_t Speed_L7,uint16_t Speed_L8,uint16_t Speed_L9
*****************************************************************
*/
void Display_Speed_Three(uint16_t Speed_L7,uint16_t Speed_L8,uint16_t Speed_L9)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	/***********L7ת�ټ���**********/
	/***********L7ǧλ***********/
	if(Speed_L7 > 999)//����999ʱ
	{		
		seg1&=0xFE;seg1|=0x01;//��ʾ1
	}
	else//С��999ʱ
    {
        seg1&=0xFE;seg1|=0x00;//����ʾ
    }
	/***********L7��λ***********/
	if(Speed_L7 > 99)//����99ʱ
	{
		Val=Speed_L7/100;//ȡ����λ������
		if(Speed_L7 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg1&=0x01;seg1|=Tab1[Val];//����
	}
	else
	{
		seg1&=0x01;seg1|=Tab1[0];//����0
	}
	/***********L7ʮλ***********/
	if(Speed_L7 > 9)//����9ʱ
	{
		Val=Speed_L7/10;//ȡ��ʮλ������
		if(Speed_L7 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg2&=0x01;seg2|=Tab1[Val];//����
	}
	else
	{
		seg2&=0x01;seg2|=Tab1[0];//����0
	}	
	/***********L7��λ***********/
	seg2&=0xFE;seg2|=0x01;//����0
	
	/***********L8ת�ټ���**********/
	/***********L8ǧλ***********/
	if(Speed_L8 > 999)//����999ʱ
	{		
		seg3&=0xFE;seg3|=0x01;//��ʾ1
	}
	else//С��999ʱ
    {
        seg3&=0xFE;seg3|=0x00;//����ʾ
    }
	/***********L8��λ***********/
	if(Speed_L8 > 99)//����99ʱ
	{
		Val=Speed_L8/100;//ȡ����λ������
		if(Speed_L8 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg3&=0x01;seg3|=Tab1[Val];//����
	}
	else
	{
		seg3&=0x01;seg3|=Tab1[0];//����0
	}
	/***********L8ʮλ***********/
	if(Speed_L8 > 9)//����9ʱ
	{
		Val=Speed_L8/10;//ȡ��ʮλ������
		if(Speed_L8 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg4&=0x01;seg4|=Tab1[Val];//����
	}
	else
	{
		seg4&=0x01;seg4|=Tab1[0];//����0
	}
	/***********L8��λ***********/
	seg4&=0xFE;seg4|=0x01;//����0
	
	/***********L9ת�ټ���**********/
	/***********L9ǧλ***********/
	if(Speed_L9 > 999)//����999ʱ
	{		
		seg5&=0xFE;seg5|=0x01;//��ʾ1
	}
	else//С��999ʱ
    {
        seg5&=0xFE;seg5|=0x00;//����ʾ
    }
	/***********L9��λ***********/
	if(Speed_L9 > 99)//����99ʱ
	{
		Val=Speed_L9/100;//ȡ����λ������
		if(Speed_L9 > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg5&=0x01;seg5|=Tab1[Val];//����
	}
	else
	{
		seg5&=0x01;seg5|=Tab1[0];//����0
	}
	/***********L9ʮλ***********/
	if(Speed_L9 > 9)//����9ʱ
	{
		Val=Speed_L9/10;//ȡ��ʮλ������
		if(Speed_L9 > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg6&=0x01;seg6|=Tab1[Val];//����
	}
	else
	{
		seg6&=0x01;seg6|=Tab1[0];//����0
	}
	/***********L9��λ***********/
	seg6&=0xFE;seg6|=0x01;//����0
	
	Write_Addr_Dat_N(32, seg1, 1);
	Write_Addr_Dat_N(33, seg2, 1);
	Write_Addr_Dat_N(34, seg3, 1);
	Write_Addr_Dat_N(35, seg4, 1);
	Write_Addr_Dat_N(36, seg5, 1);
	Write_Addr_Dat_N(37, seg6, 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Speed_Val(uint16_t dis_speed_rel,uint16_t dis_speed_set)
 * ��    �ܣ���ʾ��ǰ��λ��ʵ���ٶȺ��趨�ٶ�
 * ��    ��: dis_speed_rel ʵ���ٶ�  dis_speed_set �趨�ٶ�
 * ��    ����uint16_t dis_speed_rel,uint16_t dis_speed_set
*****************************************************************
*/
void Display_Speed_Val(uint16_t dis_speed_rel,uint16_t dis_speed_set)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	/***********speed_relת�ټ���**********/
	/***********speed_relǧλ***********/
	if(dis_speed_rel > 999)//����999ʱ
	{		
		seg1&=0x7F;seg1|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg1&=0x7F;seg1|=0x00;//����ʾ
    }
	/***********speed_rel��λ***********/
	if(dis_speed_rel > 99)//����99ʱ
	{
		Val=dis_speed_rel/100;//ȡ����λ������
		if(dis_speed_rel > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg1&=0x80;seg1|=Tab[Val];//����
	}
	else
	{
		seg1&=0x80;seg1|=Tab[0];//����0
	}
	/***********speed_relʮλ***********/
	if(dis_speed_rel > 9)//����9ʱ
	{
		Val=dis_speed_rel/10;//ȡ��ʮλ������
		if(dis_speed_rel > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg2&=0x80;seg2|=Tab[Val];//����
	}
	else
	{
		seg2&=0x80;seg2|=Tab[0];//����0
	}
	/***********speed_rel��λ***********/
	seg2&=0x7F;seg2|=0x80;//����0
	
	/***********speed_setת�ټ���**********/
	/***********speed_setǧλ***********/
	if(dis_speed_set > 999)//����999ʱ
	{		
		seg3&=0x7F;seg3|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg3&=0x7F;seg3|=0x00;//����ʾ
    }
	/***********speed_set��λ***********/
	if(dis_speed_set > 99)//����99ʱ
	{
		Val=dis_speed_set/100;//ȡ����λ������
		if(dis_speed_set > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg3&=0x80;seg3|=Tab[Val];//����
	}
	else
	{
		seg3&=0x80;seg3|=Tab[0];//����0
	}
	/***********speed_setʮλ***********/
	if(dis_speed_set > 9)//����9ʱ
	{
		Val=dis_speed_set/10;//ȡ��ʮλ������
		if(dis_speed_set > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg4&=0x80;seg4|=Tab[Val];//����
	}
	else
	{
		seg4&=0x80;seg4|=Tab[0];//����0
	}
	/***********speed_set��λ***********/
	seg4&=0x7F;seg4|=0x80;//����0
	
	if(SetMode_Option == 1)
    {
        if(Speed_ShowFlag && EC11A_Knob == 0)//ʱ�䵽����ť�޲���ʱ
        {
            seg3&=0x00;seg3|=0x00;seg4&=0x00;seg4|=0x00;
        }
    }  
	
	Write_Addr_Dat_N(9, seg1, 1);
	Write_Addr_Dat_N(10, seg2, 1);
	Write_Addr_Dat_N(11, seg3, 1);
	Write_Addr_Dat_N(12, seg4, 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Temp_Val(int dis_temp_rel,int dis_temp_set)
 * ��    �ܣ���ʾ��ǰ��λ��ʵ���¶Ⱥ��趨�¶�
 * ��    ��: dis_temp_rel ʵ���¶�  dis_temp_set �趨�¶�
 * ��    ����int dis_temp_rel,int dis_temp_set
*****************************************************************
*/
void Display_Temp_Val(int dis_temp_rel,int dis_temp_set)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	
	/***********temp_rel�¶ȼ���**********/
	/***********temp_relǧλ***********/
	if(dis_temp_rel > 999)//����999ʱ
	{		
		seg1&=0x7F;seg1|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg1&=0x7F;seg1|=0x00;//����ʾ
    }
	/***********temp_rel��λ***********/
	if(dis_temp_rel > 99)//����99ʱ
	{
		Val=dis_temp_rel/100;//ȡ����λ������
		if(dis_temp_rel > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg1&=0x80;seg1|=Tab[Val];//����	
	}
	else
	{
		seg1&=0x80;seg1|=0x00;//����ʾ
	}
	/***********temp_relʮλ***********/
	if(dis_temp_rel > 9)//����9ʱ
	{
		Val=dis_temp_rel/10;//ȡ��ʮλ������
		if(dis_temp_rel > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg2&=0x80;seg2|=Tab[Val];//����	
	}
	else
	{
		seg2&=0x80;seg2|=Tab[0];//����0
	}
	/***********temp_rel��λ***********/
	if(dis_temp_rel > 9)//����9ʱ
	{
		Val=dis_temp_rel%10;//ȡ����λ
		seg3&=0x80;seg3|=Tab[Val];//����
	}
	else
	{
		seg3&=0x80;seg3|=Tab[0];//����0
	}
	
	/***********temp_set�¶ȼ���**********/
	/***********temp_setǧλ***********/
	if(dis_temp_set > 999)//����999ʱ
	{		
		seg4&=0x7F;seg4|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg4&=0x7F;seg4|=0x00;//����ʾ
    }
	/***********temp_set��λ***********/
	if(dis_temp_set > 99)//����99ʱ
	{
		Val=dis_temp_set/100;//ȡ����λ������
		if(dis_temp_set > 999)//����999ʱ
			Val=Val%10;//ȡ����λ
		seg4&=0x80;seg4|=Tab[Val];//����	
	}
	else
	{
		seg4&=0x80;seg4|=0x00;//����ʾ
	}
	/***********temp_setʮλ***********/
	if(dis_temp_set > 9)//����9ʱ
	{
		Val=dis_temp_set/10;//ȡ��ʮλ������
		if(dis_temp_set > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ
		seg5&=0x80;seg5|=Tab[Val];//����	
	}
	else
	{
		seg5&=0x80;seg5|=Tab[0];//����0	
	}
	
	/***********temp_set��λ***********/
	if(dis_temp_set > 9)//����9ʱ
	{
		Val=dis_temp_set%10;//ȡ����λ
		seg6&=0x80;seg6|=Tab[Val];//����
	}
	else
	{
		seg6&=0x80;seg6|=Tab[0];//����0
	}
	seg2&=0x7F;seg2|=0x80;//ʵ���¶ȵ�С����
	seg3&=0x7F;seg3|=0x80;//��ʾrpm
	seg5&=0x7F;seg5|=0x80;//�趨�¶ȵ�С����
	seg6&=0x7F;seg6|=0x80;//��ʾ��
	
	if(Temp_State == 0)//�¶����ô���0ʱ
    {
		/*�¶�û����ʱ----*/	
		seg4&=0x00;seg4|=0x08;seg5&=0x80;seg5|=0x08;seg6&=0x80;seg6|=0x08;//����0
    }        
    if(SetMode_Option == 2)//���趨�¶�ʱ
    {
        if(Temp_ShowFlag && EC11A_Knob == 0)//ʱ�䵽����ť�޲���ʱ
        {
            seg4&=0x00;seg4|=0x00;seg5&=0x80;seg5|=0x00;seg6&=0x80;seg6|=0x00;//����0
		}
    }
	
	#if(Temp_TYPE == 0)//���ó�������ͨ��ʱ
        seg1&=0x00;seg1|=0x00;seg2&=0x00;seg2|=0x00;seg3&=0x80;seg3|=0x00;seg4&=0x00;seg4|=0x00;seg5&=0x00;seg5|=0x00;seg6&=0x00;seg6|=0x00;//�����¶������
    #endif
	
	Write_Addr_Dat_N(13, seg1, 1);
	Write_Addr_Dat_N(14, seg2, 1);
	Write_Addr_Dat_N(15, seg3, 1);
	Write_Addr_Dat_N(16, seg4, 1);
	Write_Addr_Dat_N(17, seg5, 1);
	Write_Addr_Dat_N(18, seg6, 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Time_Val(uint32_t dis_time_rel,uint32_t dis_time_set)
 * ��    �ܣ���ʾ��ǰ��λ��ʵ��ʱ����趨ʱ��
 * ��    ��: dis_time_rel ʵ��ʱ��  dis_time_set �趨ʱ��
 * ��    ����uint32_t dis_time_rel,uint32_t dis_time_set
*****************************************************************
*/
void Display_Time_Val(uint32_t dis_time_rel,uint32_t dis_time_set)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ

	/***********time_relʱ�����**********/
	SH=dis_time_rel/3600/10;//����ʮλ��λ��Сʱ��
	H=dis_time_rel/3600%10;//�����λ��λ��Сʱ��
	SM=dis_time_rel%3600/60/10;//����ʮ��λ��λ�ķ�����
	M=dis_time_rel%3600/60%10;//�������λ��λ�ķ�����
	/***********time_rel��һλλ***********/
	if(SH)//���ڵ���10Сʱʱ ����9Сʱ59��59��
	{		
		seg1&=0x7F;seg1|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg1&=0x7F;seg1|=0x00;//����ʾ
    }
	/***********time_rel�ڶ�λ***********/
	seg1&=0x80;seg1|=Tab[H];//����	
	
	/***********time_relʮλ***********/
	seg2&=0x80;seg2|=Tab[SM];//����	
	
	/***********time_rel��λ***********/
	seg3&=0x80;seg3|=Tab[M];//����	
	
	/***********time_setת�ټ���**********/
	SH=dis_time_set/3600/10;//����ʮλ��λ��Сʱ��
	H=dis_time_set/3600%10;//�����λ��λ��Сʱ��
	SM=dis_time_set%3600/60/10;//����ʮ��λ��λ�ķ�����
	M=dis_time_set%3600/60%10;//�������λ��λ�ķ�����
	/***********time_setǧλ***********/
	if(SH)//���ڵ���10Сʱʱ ����9Сʱ59��59��
	{		
		seg4&=0x7F;seg4|=0x80;//��ʾ1
	}
	else//С��999ʱ
    {
        seg4&=0x7F;seg4|=0x00;//����ʾ
    }
	/***********time_set��λ***********/
	seg4&=0x80;seg4|=Tab[H];//����	
	
	/***********time_setʮλ***********/
	seg5&=0x80;seg5|=Tab[SM];//����	
	
	/***********time_set��λ***********/
	seg6&=0x80;seg6|=Tab[M];//����	
	
	seg2&=0x7F;seg2|=0x80;//ʵ��ʱ���ð��
	if(Run_Status == 1 && Run_Flag > 1 && DownTime_Over.L0 == 0 && RelTime_State.L0 == 1)//����ʱ
    {
        seg2&=0x7F;seg2|=0x00;//ʵ��ʱ���ð����ʧ
    }
	seg5&=0x7F;seg5|=0x80;//�趨ʱ���ð��
	seg6&=0x7F;seg6|=0x80;//��ʾmin
	
	if(SetTime_State.L0 == 0)//û������ʱ��
    {
        //ʱ����ʾ��ܡ�----��
        seg1&=0x00;seg1|=0x08;seg2&=0x80;seg2|=0x08;seg3&=0x80;seg3|=0x08;
		seg4&=0x00;seg4|=0x08;seg5&=0x80;seg5|=0x08;seg6&=0x80;seg6|=0x08;
    }
    if(SetMode_Option == 3)
    {
        if(Time_ShowFlag && EC11A_Knob == 0)//ʱ�䵽����ť�޲���ʱ
        {
            seg4&=0x00;seg4|=0x00;seg5&=0x80;seg5|=0x00;seg6&=0x80;seg6|=0x00;
        }		
    }
	Write_Addr_Dat_N(24, seg1, 1);
	Write_Addr_Dat_N(23, seg2, 1);
	Write_Addr_Dat_N(22, seg3, 1);
	Write_Addr_Dat_N(21, seg4, 1);
	Write_Addr_Dat_N(20, seg5, 1);
	Write_Addr_Dat_N(19, seg6, 1);
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
    if(Run_Status == 1)//�����������
    {
        if(Speed_ADDMode.L1 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L1 >= Display_RelSpeed.L1)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L1 =0;//���ڵ��ٶ�����
                Speed_Last.L1 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L1 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L1 < Display_RelSpeed.L1)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L1=0;//���ڵ��ٶ�����
                Speed_Last.L1 = Display_RelSpeed.L1;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L1 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L1==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L1 >= Ctrl_Speed.L1)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L1 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L1 = Rel_Speed.L1;//��¼��ǰ�ٶ�
            if(Speed_New.L1 > Speed_Last.L1)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L1 = Speed_New.L1;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L1 = Speed_Last.L1;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L1 = Speed_Last.L1;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L1 = Speed_New.L1;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L1 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L1 <= Ctrl_Speed.L1)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L1 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L1 = Rel_Speed.L1;//��¼��ǰ�ٶ�
            if(Speed_New.L1 < Speed_Last.L1)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L1 = Speed_New.L1;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L1 = Speed_Last.L1;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L1 = Speed_Last.L1;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L1 = Speed_New.L1;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L1 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L1 = Ctrl_Speed.L1;//��ʾ�����ٶ�
        }
        else if(Speed_ADDMode.L1 == 4)//����ʱ����
        {
            Display_RelSpeed.L1 = Rel_Speed.L1;//��ʾ�����ٶ�
        }
        /**********SpeedL2_ADD_Mode**********/
        if(Speed_ADDMode.L2 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L2 >= Display_RelSpeed.L2)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L2 =0;//���ڵ��ٶ�����
                Speed_Last.L2 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L2 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L2 < Display_RelSpeed.L2)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L2=0;//���ڵ��ٶ�����
                Speed_Last.L2 = Display_RelSpeed.L2;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L2 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L2==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L2 >= Ctrl_Speed.L2)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L2 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L2 = Rel_Speed.L2;//��¼��ǰ�ٶ�
            if(Speed_New.L2 > Speed_Last.L2)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L2 = Speed_New.L2;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L2 = Speed_Last.L2;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L2 = Speed_Last.L2;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L2 = Speed_New.L2;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L2 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L2 <= Ctrl_Speed.L2)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L2 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L2 = Rel_Speed.L2;//��¼��ǰ�ٶ�
            if(Speed_New.L2 < Speed_Last.L2)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L2 = Speed_New.L2;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L2 = Speed_Last.L2;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L2 = Speed_Last.L2;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L2 = Speed_New.L2;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L2 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L2 = Ctrl_Speed.L2;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode.L2 == 4)//����ʱ����
        {
            Display_RelSpeed.L2 = Rel_Speed.L2;//��ʾ�����ٶ�
        }
        /**********SpeedL3_ADD_Mode**********/
        if(Speed_ADDMode.L3 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L3 >= Display_RelSpeed.L3)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L3 =0;//���ڵ��ٶ�����
                Speed_Last.L3 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L3 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L3 < Display_RelSpeed.L3)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L3=0;//���ڵ��ٶ�����
                Speed_Last.L3 = Display_RelSpeed.L3;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L3 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L3==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L3 >= Ctrl_Speed.L3)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L3 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L3 = Rel_Speed.L3;//��¼��ǰ�ٶ�
            if(Speed_New.L3 > Speed_Last.L3)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L3 = Speed_New.L3;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L3 = Speed_Last.L3;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L3 = Speed_Last.L3;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L3 = Speed_New.L3;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L3 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L3 <= Ctrl_Speed.L3)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L3 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L3 = Rel_Speed.L3;//��¼��ǰ�ٶ�
            if(Speed_New.L3 < Speed_Last.L3)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L3 = Speed_New.L3;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L3 = Speed_Last.L3;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L3 = Speed_Last.L3;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L3 = Speed_New.L3;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L3 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L3 = Ctrl_Speed.L3;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode.L3 == 4)//����ʱ����
        {
            Display_RelSpeed.L3 = Rel_Speed.L3;//��ʾ�����ٶ�
        }
        /**********SpeedL4_ADD_Mode**********/
        if(Speed_ADDMode.L4 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L4 >= Display_RelSpeed.L4)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L4 =0;//���ڵ��ٶ�����
                Speed_Last.L4 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L4 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L4 < Display_RelSpeed.L4)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L4=0;//���ڵ��ٶ�����
                Speed_Last.L4 = Display_RelSpeed.L4;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L4 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L4==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L4 >= Ctrl_Speed.L4)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L4 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L4 = Rel_Speed.L4;//��¼��ǰ�ٶ�
            if(Speed_New.L4 > Speed_Last.L4)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L4 = Speed_New.L4;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L4 = Speed_Last.L4;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L4 = Speed_Last.L4;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L4 = Speed_New.L4;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L4 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L4 <= Ctrl_Speed.L4)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L4 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L4 = Rel_Speed.L4;//��¼��ǰ�ٶ�
            if(Speed_New.L4 < Speed_Last.L4)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L4 = Speed_New.L4;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L4 = Speed_Last.L4;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L4 = Speed_Last.L4;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L4 = Speed_New.L4;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L4 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L4 = Ctrl_Speed.L4;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode.L4 == 4)//����ʱ����
        {
            Display_RelSpeed.L4 = Rel_Speed.L4;//��ʾ�����ٶ�
        }
        /**********SpeedL5_ADD_Mode**********/
        if(Speed_ADDMode.L5 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L5 >= Display_RelSpeed.L5)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L5 =0;//���ڵ��ٶ�����
                Speed_Last.L5 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L5 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L5 < Display_RelSpeed.L5)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L5=0;//���ڵ��ٶ�����
                Speed_Last.L5 = Display_RelSpeed.L5;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L5 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L5==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L5 >= Ctrl_Speed.L5)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L5 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L5 = Rel_Speed.L5;//��¼��ǰ�ٶ�
            if(Speed_New.L5 > Speed_Last.L5)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L5 = Speed_New.L5;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L5 = Speed_Last.L5;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L5 = Speed_Last.L5;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L5 = Speed_New.L5;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L5 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L5 <= Ctrl_Speed.L5)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L5 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L5 = Rel_Speed.L5;//��¼��ǰ�ٶ�
            if(Speed_New.L5 < Speed_Last.L5)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L5 = Speed_New.L5;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L5 = Speed_Last.L5;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L5 = Speed_Last.L5;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L5 = Speed_New.L5;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L5 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L5 = Ctrl_Speed.L5;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode.L5 == 4)//����ʱ����
        {
            Display_RelSpeed.L5 = Rel_Speed.L5;//��ʾ�����ٶ�
        }
        /**********SpeedL6_ADD_Mode**********/
        if(Speed_ADDMode.L6 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L6 >= Display_RelSpeed.L6)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L6 =0;//���ڵ��ٶ�����
                Speed_Last.L6 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L6 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L6 < Display_RelSpeed.L6)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L6=0;//���ڵ��ٶ�����
                Speed_Last.L6 = Display_RelSpeed.L6;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L6 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L6==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L6 >= Ctrl_Speed.L6)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L6 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L6 = Rel_Speed.L6;//��¼��ǰ�ٶ�
            if(Speed_New.L6 > Speed_Last.L6)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L6 = Speed_New.L6;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L6 = Speed_Last.L6;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L6 = Speed_Last.L6;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L6 = Speed_New.L6;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L6 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L6 <= Ctrl_Speed.L6)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L6 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L6 = Rel_Speed.L6;//��¼��ǰ�ٶ�
            if(Speed_New.L6 < Speed_Last.L6)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L6 = Speed_New.L6;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L6 = Speed_Last.L6;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L6 = Speed_Last.L6;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L6 = Speed_New.L6;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L6 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L6 = Ctrl_Speed.L6;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode.L6 == 4)//����ʱ����
        {
            Display_RelSpeed.L6 = Rel_Speed.L6;//��ʾ�����ٶ�
        }
        /**********SpeedL7_ADD_Mode**********/
        if(Speed_ADDMode.L7 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L7 >= Display_RelSpeed.L7)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L7 =0;//���ڵ��ٶ�����
                Speed_Last.L7 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L7 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L7 < Display_RelSpeed.L7)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L7=0;//���ڵ��ٶ�����
                Speed_Last.L7 = Display_RelSpeed.L7;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L7 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L7==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L7 >= Ctrl_Speed.L7)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L7 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L7 = Rel_Speed.L7;//��¼��ǰ�ٶ�
            if(Speed_New.L7 > Speed_Last.L7)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L7 = Speed_New.L7;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L7 = Speed_Last.L7;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L7 = Speed_Last.L7;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L7 = Speed_New.L7;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L7 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L7 <= Ctrl_Speed.L7)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L7 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L7 = Rel_Speed.L7;//��¼��ǰ�ٶ�
            if(Speed_New.L7 < Speed_Last.L7)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L7 = Speed_New.L7;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L7 = Speed_Last.L7;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L7 = Speed_Last.L7;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L7 = Speed_New.L7;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L7 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L7 = Ctrl_Speed.L7;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode.L7 == 4)//����ʱ����
        {
            Display_RelSpeed.L7 = Rel_Speed.L7;//��ʾ�����ٶ�
        }
        /**********SpeedL8_ADD_Mode**********/
        if(Speed_ADDMode.L8 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L8 >= Display_RelSpeed.L8)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L8 =0;//���ڵ��ٶ�����
                Speed_Last.L8 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L8 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L8 < Display_RelSpeed.L8)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L8=0;//���ڵ��ٶ�����
                Speed_Last.L8 = Display_RelSpeed.L8;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L8 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L8==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L8 >= Ctrl_Speed.L8)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L8 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L8 = Rel_Speed.L8;//��¼��ǰ�ٶ�
            if(Speed_New.L8 > Speed_Last.L8)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L8 = Speed_New.L8;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L8 = Speed_Last.L8;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L8 = Speed_Last.L8;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L8 = Speed_New.L8;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L8 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L8 <= Ctrl_Speed.L8)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L8 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L8 = Rel_Speed.L8;//��¼��ǰ�ٶ�
            if(Speed_New.L8 < Speed_Last.L8)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L8 = Speed_New.L8;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L8 = Speed_Last.L8;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L8 = Speed_Last.L8;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L8 = Speed_New.L8;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L8 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L8 = Ctrl_Speed.L8;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode.L8 == 4)//����ʱ����
        {
            Display_RelSpeed.L8 = Rel_Speed.L8;//��ʾ�����ٶ�
        }
		/**********SpeedL9_ADD_Mode**********/
        if(Speed_ADDMode.L9 == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Ctrl_Speed.L9 >= Display_RelSpeed.L9)//�����ٶȴ���ʵ���ٶ�
            {
                Speed_New.L9 =0;//���ڵ��ٶ�����
                Speed_Last.L9 = 0;//֮ǰ���ٶ�����
                Speed_ADDMode.L9 = 1;//�������ģʽ��
            }
            else if(Ctrl_Speed.L9 < Display_RelSpeed.L9)//�����ٶ�С��ʵ���ٶ�
            {
                Speed_New.L9=0;//���ڵ��ٶ�����
                Speed_Last.L9 = Display_RelSpeed.L9;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed_ADDMode.L9 = 2;//�������ģʽ��
            }
        }
        if(Speed_ADDMode.L9==1)//�ڽ������ģʽ��
        { 
            if(Rel_Speed.L9 >= Ctrl_Speed.L9)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L9 = 3;//�����ȶ�ģʽ
                return;
            }
            Speed_New.L9 = Rel_Speed.L9;//��¼��ǰ�ٶ�
            if(Speed_New.L9 > Speed_Last.L9)//��ǰ�ٶȴ�����һ���ٶ�
                Display_RelSpeed.L8 = Speed_New.L9;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶ�С����һ���ٶ�
            {
                Display_RelSpeed.L9 = Speed_Last.L9;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                Speed_New.L9 = Speed_Last.L9;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L9 = Speed_New.L9;//����ǰ�ٶȱ���    
        }
        else if(Speed_ADDMode.L9 == 2)//�ٶ��½�ģʽ��
        {
            if(Rel_Speed.L9 <= Ctrl_Speed.L9)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
            {
                Speed_ADDMode.L9 = 3;//�ȶ�ģʽ
                return;
            }
            Speed_New.L9 = Rel_Speed.L9;//��¼��ǰ�ٶ�
            if(Speed_New.L9 < Speed_Last.L9)//��ǰ�ٶ�С����һ���ٶ�
                Display_RelSpeed.L9 = Speed_New.L9;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Display_RelSpeed.L9 = Speed_Last.L9;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed_New.L9 = Speed_Last.L9;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed_Last.L9 = Speed_New.L9;//����ǰ�ٶȱ���
            
        }
        else if(Speed_ADDMode.L9 == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_RelSpeed.L9 = Ctrl_Speed.L9;//��ʾ�����ٶ�
        }
		else if(Speed_ADDMode.L9 == 4)//����ʱ����
        {
            Display_RelSpeed.L9 = Rel_Speed.L9;//��ʾ�����ٶ�
        }
    }
    else
    {
        SetALL_int(0,&Speed_ADDMode);//�ٶ���ʾģʽ����
        SetALL_int(0,&Speed_New);//��ǰ��¼�ٶ�����
        SetALL_int(0,&Speed_Last);//��һ���ٶ�����
        SetALL_SpeedOver(&Display_RelSpeed,&Rel_Speed);//��ʵ���ٶ���ʾ
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Deal_Temp(void)
 * ��    �ܣ� �¶���ʾ����
*****************************************************************
*/
void Deal_Temp(void)
{
    if(Run_Status == 0 || Temp_State == 0)//û������û���õ������
    {
		Rel_Temp = Ture_Temp;//��ʾʵ�ʲ���¶�
    }
    else
    {
        if(Temp_ADDMode == 0)//�ж����ݴ�����ʾ
        {
			if(Ture_Temp < Ctrl_Temp)//ʵ���¶ȴ��ڿ����¶�
			{	
				Temp_ADDMode = 1;//����
			}
			else
			{
				Temp_ADDMode = 2;//����
			}
		}
        else if(Temp_ADDMode == 1)//�ڼ���ģʽ��
        {
            Temp_New = Ture_Temp;//��¼��ǰ�¶�
            if(Temp_New > Temp_Last)//��ǰ�¶ȴ�����һ���¶�
                Rel_Temp = Temp_New;//��ʾ��ǰ�¶�
            else//��ǰ�¶�С�ڵ�����һ���¶�
            {
                Rel_Temp = Temp_Last;//��ʾ��һ���¶ȣ������¶�С�ڵ�ǰ�¶ȡ����������¶ȵ�����
                Temp_New = Temp_Last;//����һ���¶ȸ�ֵ����ǰ�¶�
            }
            Temp_Last = Temp_New;//����ǰ�¶ȱ���
            if(Rel_Temp >= Ctrl_Temp)//������ʾֵ���ڵ����趨ֵ
            {
                Temp_ADDMode = 3;//�����ȶ�ģʽ
            }
        }
        else if(Temp_ADDMode == 2)
        {
            Temp_New = Ture_Temp;//��¼��ǰ�¶�
            if(Temp_New < Temp_Last)//��ǰ�¶�С����һ���¶�
                Rel_Temp = Temp_New;//��ʾ��ǰ�¶�
            else//��ǰ�¶ȴ�����һ���¶�
            {
                Rel_Temp = Temp_Last;//��ʾ��һ���¶ȣ������¶ȴ��ڵ�ǰ�¶ȡ������½��¶ȵ�����
                Temp_New = Temp_Last;//����һ���¶ȸ�ֵ����ǰ�¶�
            }
            Temp_Last = Temp_New;//����ǰ�ٶȱ���
            if(Rel_Temp <= Ctrl_Temp)//������ʾֵС�ڵ����趨ֵ
            {
                Temp_ADDMode = 3;//�����ȶ�ģʽ
            }
        }
        else if(Temp_ADDMode == 3)//�ȶ�ģʽ��
        {
            Rel_Temp = Ctrl_Temp;//��ʾ�����¶�
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
	Deal_Speed();//�ٶ���ʾ����
    Deal_Temp();//�¶���ʾ����
	switch(Work_Option)
    {
        case 1://��λ1              
            Set_Speed.L0 = Set_Speed.L1;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L1;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L1;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L1;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L1;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L1;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L1;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L1;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
        case 2://��λ2
            Set_Speed.L0 = Set_Speed.L2;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L2;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L2;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L2;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L2;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L2;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L2;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L2;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
        case 3://��λ3
            Set_Speed.L0 = Set_Speed.L3;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L3;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L3;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L3;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L3;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L3;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L3;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L3;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
        case 4://��λ4
            Set_Speed.L0 = Set_Speed.L4;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L4;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L4;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L4;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L4;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L4;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L4;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L4;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
        case 5://��λ5
            Set_Speed.L0 = Set_Speed.L5;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L5;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L5;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L5;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L5;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L5;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L5;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L5;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
        case 6://��λ6
            Set_Speed.L0 = Set_Speed.L6;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L6;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L6;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L6;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L6;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L6;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L6;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L6;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
        case 7://��λ7
            Set_Speed.L0 = Set_Speed.L7;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L7;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L7;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L7;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L7;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L7;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L7;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L7;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
        case 8://��λ8
            Set_Speed.L0 = Set_Speed.L8;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L8;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L8;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L8;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L8;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L8;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L8;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L8;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
		case 9://��λ9
            Set_Speed.L0 = Set_Speed.L9;//����λ���ٶȸ�ֵ���趨�ٶ���ʾ
            Rel_Speed.L0 = Display_RelSpeed.L9;//����ȡ��ʵ���ٶȸ�ֵ��ʾ
        
            Set_Time.L0 = Set_Time.L9;//��ʱ����ʾ
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L9;//ʵ��ʱ������趨ʱ����ʾ
            else
                Rel_Time.L0 = Ctrl_Time.L9;//ʵ��ʱ��������ʱ����ʾ
            SetTime_State.L0 = SetTime_State.L9;//ȥ�趨��ʾʱ��
            RelTime_State.L0 = RelTime_State.L9;//ȥʵ����ʾʱ��
            DownTime_Over.L0 = DownTime_Over.L9;//ʱ�䵹��ʱ����ͼ����˸��ʾ
            break;
        default:
            break;
    }
    Display_Speed_One(Display_Speed.L1,Display_Speed.L2,Display_Speed.L3);
	Display_Speed_Two(Display_Speed.L4,Display_Speed.L5,Display_Speed.L6);
	Display_Speed_Three(Display_Speed.L7,Display_Speed.L8,Display_Speed.L9);
	Display_Speed_Val(Rel_Speed.L0,Set_Speed.L0);
	Display_Temp_Val(Rel_Temp,Set_Temp);
	Display_Time_Val(Rel_Time.L0+59,Set_Time.L0);
}

