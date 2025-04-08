#include "Show.h"

/**********ȫ�ֱ�������******/
uint16_t Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t seg15_Flag;//������ʾ��ʵ���ٶ����һλ�м��б�ܸ����������̫Զ
uint8_t Speed_ShowFlag,Temp_ShowFlag,Time_ShowFlag;//�ٶȡ��¶ȡ�ʱ����ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t Work_All_Time;//ȫ����λ����ʱ��˸�Ĺ�λʱ��
uint8_t Run_Flag;//������˸ͼ��
uint8_t Data[10]  = {0x77,0x12,0x6B,0x5B,0x1E,0x5D,0x7D,0x13,0x7F,0x5F};
uint8_t Data1[10] = {0xEE,0x48,0xD6,0xDA,0x78,0xBA,0xBE,0xC8,0xFE,0xFA};

/*
*****************************************************************
 * ����ԭ�ͣ�void Start_SpeedRun(float dT)
 * ��    �ܣ�ת�ٶ���
*****************************************************************
*/
void Start_SpeedRun(float dT)
{
	static float T;
	if(Run_Status==1 && Set_Speed.L0 > 0 && Rel_Speed.L0)//����ʱ
	{
		T += dT;
		if(T >= 0.5f)
		{
			SpeedIcon_Step++;
			if(SpeedIcon_Step > 3)
				SpeedIcon_Step = 1;
			T = 0;
		}
	}
	else
	{
		SpeedIcon_Step = 0;
		T = 0;
	}
}

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
        Run_Flag = ~Run_Flag;//����ʱ��˸
    if(SetMode_Option == 0 && Twinkle_Time==0)//���û������ѡ���У��򶼵���������˸
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
        if(SetMode_Option == 0)//�����ٶ�
        {
            Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
            Temp_ShowFlag = 0;//�¶ȳ���
            Time_ShowFlag = 0;//ʱ�䳣��
        }
        else if(SetMode_Option == 1)//�����¶�
        {
            Speed_ShowFlag = 0;//�ٶȳ���
            Temp_ShowFlag = ~Temp_ShowFlag;//�¶���˸
            Time_ShowFlag = 0;//ʱ�䳣��
        }
        else if(SetMode_Option == 2)//����ʱ��
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
        case 0 :
            HAL_GPIO_WritePin(LED_KEY_GPIO_Port, LED_KEY_Pin, GPIO_PIN_SET);//���߱����ƽ�ź�
			if(Param.type == 0 || Param.type == 2)//����
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);//�����pwm
			}
			else if(Param.type == 1 || Param.type == 3)//����
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);//�����pwm
			}
            break ;
        case 1 :
            HAL_GPIO_WritePin(LED_KEY_GPIO_Port, LED_KEY_Pin, GPIO_PIN_RESET);//���ͱ����ƽ�ź�
			if(Param.type == 0 || Param.type == 2)//����
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 15);//�����pwm
			}
			else if(Param.type == 1 || Param.type == 3)//����
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 15);//�����pwm
			}
            break ;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_WorkSpeed(uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3,uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6)
 * ��    �ܣ���ʾ��λ�ٶ�
 * ��    ��: Speed_L1��λһ���ٶ�, Speed_L2��λ�����ٶ�, Speed_L3��λ�����ٶ�, Speed_L4��λ�ĵ��ٶ�, Speed_L5��λ����ٶ�, Speed_L6��λ�����ٶ�
 * ��    ����uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3,uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6
*****************************************************************
*/
void Display_WorkSpeed(uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3,uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6,uint16_t dis_rel_rpm,uint16_t dis_set_rpm,int dis_rel_temp,int dis_set_temp,uint32_t dis_rel_time,uint32_t dis_set_time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9,seg10,
	seg11,seg12,seg13,seg14,seg15,seg16,seg17,seg18,seg19,seg20,
	seg21,seg22,seg23,seg24,seg25,seg26,seg27,seg28,seg29,seg30,
	seg31,seg32;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;seg10=0;
	seg11=0;seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;seg18=0;seg19=0;seg20=0;
	seg21=0;seg22=0;seg23=0;seg24=0;seg25=0;seg26=0;seg27=0;seg28=0;seg29=0;seg30=0;
	seg31=0;seg32=0;
    uint8_t Val;//���ڰ�ʮ��ȡ����������
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
	
	/*********************Speed_L1*********************/
	/***********L1ǧλ***********/
	if(Speed_L1 > 999)//����999ʱ
	{		
		seg21&=0xFE;seg21|=0x01;//��ʾ1
		seg1&=0xFD;seg1|=0x00;//��ʾ1
	}
	else//С��999ʱ
    {
        seg21&=0xFE;seg21|=0x01;//��ʾ0
		seg1&=0xFD;seg1|=0x02;//��ʾ0
    }
	
	/***********L1��λ***********/
	if(Speed_L1 > 99)//����99ʱ
	{
		Val=Speed_L1/100;//ȡ����λ������
		if(Speed_L1 > 999)//�������999ʱ
            Val=Val%10;//ȡ����λ������
		seg21&=0x01;seg21|=Data1[Val];//��ʾ��λ
	}
	else
	{
		seg21&=0x01;seg21|=Data1[0];//��ʾ��λ
	}
	
	/***********L1ʮλ***********/
	if(Speed_L1 > 9)//����9ʱ
	{
		Val=Speed_L1/10;//ȡ��ʮλ������
		if(Speed_L1 > 99)//����99ʱ
            Val=Val%10;//ȡ��ʮλ������
		seg22&=0x01;seg22|=Data1[Val];//��ʾʮλ
	}
	else
	{
		seg22&=0x01;seg22|=Data1[0];//��ʾ��λ
	}
	
	/***********L1��λ***********/
    seg22&=0xFE;seg22|=0x01;//��ʾ1
	
	/*********************Speed_L2*********************/
	/***********L2ǧλ***********/
	if(Speed_L2 > 999)//����999ʱ
	{		
		seg23&=0xFE;seg23|=0x01;//��ʾ1
		seg1&=0xFE;seg1|=0x00;//��ʾ1
	}
	else//С��999ʱ
    {
        seg23&=0xFE;seg23|=0x01;//��ʾ0
		seg1&=0xFE;seg1|=0x01;//��ʾ0
    }
	
	/***********L2��λ***********/
	if(Speed_L2 > 99)//����99ʱ
	{
		Val=Speed_L2/100;//ȡ����λ������
		if(Speed_L2 > 999)//�������999ʱ
            Val=Val%10;//ȡ����λ������
		seg23&=0x01;seg23|=Data1[Val];//��ʾ��λ
	}
	else
	{
		seg23&=0x01;seg23|=Data1[0];//��ʾ��λ
	}
	
	/***********L2ʮλ***********/
	if(Speed_L2 > 9)//����9ʱ
	{
		Val=Speed_L2/10;//ȡ��ʮλ������
		if(Speed_L2> 99)//����99ʱ
            Val=Val%10;//ȡ��ʮλ������
		seg24&=0x01;seg24|=Data1[Val];//��ʾʮλ
	}
	else
	{
		seg24&=0x01;seg24|=Data1[0];//��ʾ��λ
	}
	
	/***********L2��λ***********/
    seg24&=0xFE;seg24|=0x01;//��ʾ1
	
	/*********************Speed_L3*********************/
	/***********L3ǧλ***********/
	if(Speed_L3 > 999)//����999ʱ
	{		
		seg11&=0x7F;seg11|=0x80;//��ʾ1
		seg2&=0xBF;seg2|=0x00;//��ʾ1
	}
	else//С��999ʱ
    {
        seg11&=0x7F;seg11|=0x80;//��ʾ0
		seg2&=0xBF;seg2|=0x40;//��ʾ0
    }
	
	/***********L3��λ***********/
	if(Speed_L3 > 99)//����99ʱ
	{
		Val=Speed_L3/100;//ȡ����λ������
		if(Speed_L3 > 999)//�������999ʱ
            Val=Val%10;//ȡ����λ������
		seg11&=0x80;seg11|=Data[Val];//��ʾ��λ
	}
	else
	{
		seg11&=0x80;seg11|=Data[0];//��ʾ��λ
	}
	
	/***********L3ʮλ***********/
	if(Speed_L3 > 9)//����9ʱ
	{
		Val=Speed_L3/10;//ȡ��ʮλ������
		if(Speed_L3 > 99)//����99ʱ
            Val=Val%10;//ȡ��ʮλ������
		seg10&=0x80;seg10|=Data[Val];//��ʾʮλ
	}
	else
	{
		seg10&=0x80;seg10|=Data[0];//��ʾ��λ
	}
	
	/***********L3��λ***********/
    seg10&=0x7F;seg10|=0x80;//��ʾʮλ
	
	/*********************Speed_L4*********************/
	/***********L4ǧλ***********/
	if(Speed_L4 > 999)//����999ʱ
	{		
		seg9&=0x7F;seg9|=0x80;//��ʾ1
		seg2&=0x7F;seg2|=0x00;//��ʾ1
	}
	else//С��999ʱ
    {
        seg9&=0x7F;seg9|=0x80;//��ʾ0
		seg2&=0x7F;seg2|=0x80;//��ʾ0
    }
	
	/***********L4��λ***********/
	if(Speed_L4 > 99)//����99ʱ
	{
		Val=Speed_L4/100;//ȡ����λ������
		if(Speed_L4 > 999)//�������999ʱ
            Val=Val%10;//ȡ����λ������
		seg9&=0x80;seg9|=Data[Val];//��ʾ��λ
	}
	else
	{
		seg9&=0x80;seg9|=Data[0];//��ʾ��λ
	}
	
	/***********L4ʮλ***********/
	if(Speed_L4 > 9)//����9ʱ
	{
		Val=Speed_L4/10;//ȡ��ʮλ������
		if(Speed_L4 > 99)//����99ʱ
            Val=Val%10;//ȡ��ʮλ������
		seg8&=0x80;seg8|=Data[Val];//��ʾʮλ
	}
	else
	{
		seg8&=0x80;seg8|=Data[0];//��ʾ��λ
	}
	
	/***********L4��λ***********/
    seg8&=0x7F;seg8|=0x80;//��ʾʮλ
	
	/*********************Speed_L5*********************/
	/***********L5ǧλ***********/
	if(Speed_L5 > 999)//����999ʱ
	{		
		seg7&=0x7F;seg7|=0x80;//��ʾ1
		seg3&=0xBF;seg3|=0x00;//��ʾ1
	}
	else//С��999ʱ
    {
        seg7&=0x7F;seg7|=0x80;//��ʾ0
		seg3&=0xBF;seg3|=0x40;//��ʾ0
    }
	
	/***********L5��λ***********/
	if(Speed_L5 > 99)//����99ʱ
	{
		Val=Speed_L5/100;//ȡ����λ������
		if(Speed_L5 > 999)//�������999ʱ
            Val=Val%10;//ȡ����λ������
		seg7&=0x80;seg7|=Data[Val];//��ʾ��λ
	}
	else
	{
		seg7&=0x80;seg7|=Data[0];//��ʾ��λ
	}
	
	/***********L5ʮλ***********/
	if(Speed_L5 > 9)//����9ʱ
	{
		Val=Speed_L5/10;//ȡ��ʮλ������
		if(Speed_L5 > 99)//����99ʱ
            Val=Val%10;//ȡ��ʮλ������
		seg6&=0x80;seg6|=Data[Val];//��ʾʮλ
	}
	else
	{
		seg6&=0x80;seg6|=Data[0];//��ʾ��λ
	}
	
	/***********L5��λ***********/
    seg6&=0x7F;seg6|=0x80;//��ʾʮλ
	
	/*********************Speed_L6*********************/
	/***********L6ǧλ***********/
	if(Speed_L6 > 999)//����999ʱ
	{		
		seg5&=0x7F;seg5|=0x80;//��ʾ1
		seg3&=0x7F;seg3|=0x00;//��ʾ1
	}
	else//С��999ʱ
    {
        seg5&=0x7F;seg5|=0x80;//��ʾ0
		seg3&=0x7F;seg3|=0x80;//��ʾ0
    }
	
	/***********L6��λ***********/
	if(Speed_L6 > 99)//����99ʱ
	{
		Val=Speed_L6/100;//ȡ����λ������
		if(Speed_L6 > 999)//�������999ʱ
            Val=Val%10;//ȡ����λ������
		seg5&=0x80;seg5|=Data[Val];//��ʾ��λ
	}
	else
	{
		seg5&=0x80;seg5|=Data[0];//��ʾ��λ
	}
	
	/***********L6ʮλ***********/
	if(Speed_L6 > 9)//����9ʱ
	{
		Val=Speed_L6/10;//ȡ��ʮλ������
		if(Speed_L6 > 99)//����99ʱ
            Val=Val%10;//ȡ��ʮλ������
		seg4&=0x80;seg4|=Data[Val];//��ʾʮλ
	}
	else
	{
		seg4&=0x80;seg4|=Data[0];//��ʾ��λ
	}
	
	/***********L6��λ***********/
    seg4&=0x7F;seg4|=0x80;//��ʾʮλ
	
	/*********************�м�ͼ��*******************/
	/***********ת��ͼ��***********/
	/*****************ת��ͼ��******************/
	switch(SpeedIcon_Step)
	{
		case 0:seg25&=0xC7;seg25|=0x38;//����
			break;
		case 1:seg25&=0xC7;seg25|=0x18;//ת��S37
			break;
		case 2:seg25&=0xC7;seg25|=0x28;//ת��S38
			break;
		case 3:seg25&=0xC7;seg25|=0x30;//ת��S39
			break;
		default:
			break;
	}
	
	/***********�¶�ͼ��***********/
	seg25&=0xF9;seg25|=0x06;//�¶�ͼ��
	if(Run_Status == 1 && Temp_State == 1 && Run_Flag > 1)//����ʱ
    {
		seg25&=0xF9;seg25|=0x00;//�¶�ͼ��
    }
	
	/***********ʱ��ͼ��***********/
	seg25&=0xFE;seg25|=0x01;//ʱ��ͼ��
	if(Run_Status == 1 && Run_Flag > 1 && DownTime_Over.L0 == 0 && RelTime_State.L0 == 1)//����ʱ
    {
        seg25&=0xFE;seg25|=0x00;//ʱ��ͼ����ʧ
    }
	
	/*********************Rel_Speed*********************/
	/***********Rel_Speedǧλ***********/
	if(dis_rel_rpm > 999)//����999ʱ
	{		
		seg25&=0x3F;seg25|=0x40;//��ʾ1
	}
	else//С��999ʱ
	{
		seg25&=0x3F;seg25|=0xC0;//��ʾ0
	}
	
	/***********Rel_Speed��λ***********/
	if(dis_rel_rpm > 99)//����99ʱ
	{
		Val=dis_rel_rpm/100;//ȡ����λ������
		if(dis_rel_rpm > 999)//�������999ʱ
			Val=Val%10;//ȡ����λ������
		seg26&=0x01;seg26|=Data1[Val];//��ʾ��λ
	}
	else
	{
		seg26&=0x01;seg26|=Data1[0];//��ʾ0
	}
	
	/***********Rel_Speedʮλ***********/
	if(dis_rel_rpm > 9)//����9ʱ
	{
		Val=dis_rel_rpm/10;//ȡ��ʮλ������
		if(dis_rel_rpm > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ������
		seg27&=0x01;seg27|=Data1[Val];//��ʾʮλ
	}
	else
	{
		seg27&=0x01;seg27|=Data1[0];//��ʾ0
	}
	
	/***********Rel_Speed��λ***********/
	seg26&=0xFE;seg26|=0x01;//��ʾʮλ
	
	/*********************Set_Speed*********************/
	/***********Set_Speedǧλ***********/
	if(dis_set_rpm > 999)//����999ʱ
	{		
		seg27&=0xFE;seg27|=0x00;//��ʾ1
		seg28&=0xFE;seg28|=0x01;//��ʾ1
	}
	else//С��999ʱ
	{
		seg27&=0xFE;seg27|=0x01;//��ʾ1
		seg28&=0xFE;seg28|=0x01;//��ʾ0
	}
	
	/***********Set_Speed��λ***********/
	if(dis_set_rpm > 99)//����99ʱ
	{
		Val=dis_set_rpm/100;//ȡ����λ������
		if(dis_set_rpm > 999)//�������999ʱ
			Val=Val%10;//ȡ����λ������
		seg28&=0x01;seg28|=Data1[Val];//��ʾ��λ
	}
	else
	{
		seg28&=0x01;seg28|=Data1[0];//��ʾ0
	}
	
	/***********Set_Speedʮλ***********/
	if(dis_set_rpm > 9)//����9ʱ
	{
		Val=dis_set_rpm/10;//ȡ��ʮλ������
		if(dis_set_rpm > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ������
		seg29&=0x01;seg29|=Data1[Val];//��ʾʮλ
	}
	else
	{
		seg29&=0x01;seg29|=Data1[0];//��ʾ0
	}
	
	/***********Set_Speed��λ***********/
	seg29&=0xFE;seg29|=0x01;//��ʾʮλ
	/*��˸*/
	if(Speed_ShowFlag && EC11A_Knob == 0)//ʱ�䵽����ť�޲���ʱ
	{
		seg27&=0xFE;seg27|=0x00;//����ʾ��ʾ
		seg28&=0x00;//����ʾ��ʾ
		seg29&=0x00;//����ʾ��ʾ
	}
    seg3&=0xFC;seg3|=0x04;//��ʾ��rpm��
	
	/*********************Rel_Temp*********************/
	/***********Rel_Tempǧλ***********/
    if(dis_rel_temp > 999)//����999ʱ
    {
		seg3&=0xFD;seg3|=0x00;//��ʾ1
		seg30&=0xFE;seg30|=0x01;//��ʾ1
    }
    else//С��999ʱ
    {
		seg3&=0xFD;seg3|=0x02;//��ʾ0
		seg30&=0xFE;seg30|=0x01;//��ʾ0
    }
	
	/***********Rel_Temp��λ***********/
	if(dis_rel_temp > 99)//����99ʱ
	{
		Val=dis_rel_temp/100;//ȡ����λ������
		if(dis_rel_temp > 999)//�������999ʱ
			Val=Val%10;//ȡ����λ������
		seg30&=0x01;seg30|=Data1[Val];//��ʾ��λ
	}
	else
	{
		seg30&=0x01;seg30|=Data1[0];//��ʾ0
	}
	
	/***********Rel_Tempʮλ***********/
	if(dis_rel_temp > 9)//����9ʱ
	{
		Val=dis_rel_temp/10;//ȡ��ʮλ������
		if(dis_rel_temp > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ������
		seg31&=0x01;seg31|=Data1[Val];//��ʾʮλ
	}
	else
	{
		seg31&=0x01;seg31|=Data1[0];//��ʾ0
	}
	
	/***********Rel_Temp��λ***********/
	Val = dis_rel_temp % 10;//ȡ����λ
	if(Val > 4)//����4ʱ
    {
		seg32&=0x01;seg32|=Data1[5];//��ʾ5
    }
    else//С��4ʱ
    {
		seg32&=0x01;seg32|=Data1[0];//��ʾ0
	}	
	/***********�¶�С����**************/
	seg31&=0xFE;seg31|=0x01;//��ʾʵ���¶�С����
	
	/*********************Set_Temp*********************/
	/***********Set_Tempǧλ***********/
    if(dis_set_temp > 999)//����999ʱ
    {
		seg32&=0xFE;seg32|=0x00;//��ʾ1
		seg12&=0xFE;seg12|=0x01;//��ʾ1
    }
    else//С��999ʱ
    {
		seg32&=0xFE;seg32|=0x01;//��ʾ0
		seg12&=0xFE;seg12|=0x01;//��ʾ0
    }
	
	/***********Set_Temp��λ***********/
	if(dis_set_temp > 99)//����99ʱ
	{
		Val=dis_set_temp/100;//ȡ����λ������
		if(dis_set_temp > 999)//�������999ʱ
			Val=Val%10;//ȡ����λ������
		seg12&=0x01;seg12|=Data1[Val];//��ʾ��λ
	}
	else
	{
		seg12&=0x01;seg12|=Data1[0];//��ʾ0
	}
	
	/***********Set_Tempʮλ***********/
	if(dis_set_temp > 9)//����9ʱ
	{
		Val=dis_set_temp/10;//ȡ��ʮλ������
		if(dis_set_temp > 99)//����99ʱ
			Val=Val%10;//ȡ��ʮλ������
		seg13&=0x01;seg13|=Data1[Val];//��ʾʮλ
	}
	else
	{
		seg13&=0x01;seg13|=Data1[0];//��ʾ0
	}
	
	/***********Set_Temp��λ***********/
	Val = dis_set_temp % 10;//ȡ����λ
	if(Val > 4)//����4ʱ
    {
		seg14&=0x01;seg14|=Data1[5];//��ʾ5
    }
    else//С��4ʱ
    {
		seg14&=0x01;seg14|=Data1[0];//��ʾ0
	}
	if(Temp_State == 0)//�¶����ô���0ʱ
    {
		seg32&=0xFE;seg32|=0x00;//����ʾ
		seg12&=0xFE;seg12|=0x00;//����ʾ
		seg12&=0x01;seg12|=0x10;//��ʾ��-��
		seg13&=0x01;seg13|=0x10;//��ʾ��-��
		seg14&=0x01;seg14|=0x10;//��ʾ��-��
	}
	if(Temp_ShowFlag && EC11A_Knob == 0)//ʱ�䵽����ť�޲���ʱ
    {
		seg32&=0xFE;seg32|=0x00;//����ʾ
		seg12&=0xFE;seg12|=0x00;//����ʾ
		seg12&=0x01;seg12|=0x00;//��ʾ��-��
		seg13&=0x01;seg13|=0x00;//��ʾ��-��
		seg14&=0x01;seg14|=0x00;//��ʾ��-��
	}
	/***********�¶�С����**************/
	seg13&=0xFE;seg13|=0x01;//��ʾ�趨�¶�С����
	/***********�¶ȵ�λͼ��************/
	seg14&=0xFE;seg14|=0x01;//��ʾ�¶ȵ�λͼ��
	
	/*********************Rel_Time*********************/
	SH=dis_rel_time/3600/10;//����ʮλ��λ��Сʱ��
	H=dis_rel_time/3600%10;//�����λ��λ��Сʱ��
	SM=dis_rel_time%3600/60/10;//����ʮ��λ��λ�ķ�����
	M=dis_rel_time%3600/60%10;//�������λ��λ�ķ�����
       
	/***********Rel_Time��һλ***********/
	if(SH == 0)
	{
		seg3&=0xFE;seg3|=0x01;//��ʾʵ��ʱ���һλ
		seg15&=0xFE;seg15|=0x01;//��ʾʵ��ʱ���һλ
	}
	else
	{
		seg3&=0xFE;seg3|=0x00;//��ʾʵ��ʱ���һλ
		seg15&=0xFE;seg15|=0x01;//��ʾʵ��ʱ���һλ
	}
	
	/***********Rel_Time�ڶ�λ***********/
	seg15&=0x01;seg15|=Data1[H];//��ʾʵ��ʱ��ڶ�λ
	/***********Rel_Time����λ***********/
	seg16&=0x01;seg16|=Data1[SM];//��ʾʵ��ʱ�����λ
	/***********Rel_Time����λ***********/
	seg17&=0x01;seg17|=Data1[M];//��ʾʵ��ʱ�����λ
	/***********Rel_Timeð��ͼ��*********/
	seg16&=0xFE;seg16|=0x01;//��ʾʵ��ʱ��ð��
	if(RelTime_State.L0 == 0)//û������ʱ��
    {
		seg3&=0xFE;seg3|=0x00;//����ʾʵ��ʱ���һλ
		seg15&=0xFE;seg15|=0x00;//����ʾʵ��ʱ���һλ
		seg15&=0x01;seg15|=0x10;//��ʾʵ��ʱ��ڶ�λ
		seg16&=0x01;seg16|=0x10;//��ʾʵ��ʱ�����λ
		seg17&=0x01;seg17|=0x10;//��ʾʵ��ʱ�����λ
	}
	if(Run_Status == 1 && Run_Flag > 1 && DownTime_Over.L0 == 0 && RelTime_State.L0 == 1)//����ʱ
    {
        seg16&=0xFE;seg16|=0x00;//ʱ��ð����ʧ
    }
	
	/*********************Set_Time*********************/
	/***********Set_Timeǧλ***********/
	SH=dis_set_time/3600/10;//����ʮλ��λ��Сʱ��
	H=dis_set_time/3600%10;//�����λ��λ��Сʱ��
	SM=dis_set_time%3600/60/10;//����ʮ��λ��λ�ķ�����
	M=dis_set_time%3600/60%10;//�������λ��λ�ķ�����

	/***********Set_Time��һλ***********/
	if(SH == 0)
	{
		seg17&=0xFE;seg17|=0x01;//��ʾʵ��ʱ���һλ
		seg18&=0xFE;seg18|=0x01;//��ʾʵ��ʱ���һλ
	}
	else
	{
		seg17&=0xFE;seg17|=0x00;//��ʾʵ��ʱ���һλ
		seg18&=0xFE;seg18|=0x01;//��ʾʵ��ʱ���һλ
	}
	/***********Set_Time�ڶ�λ***********/
	seg18&=0x01;seg18|=Data1[H%10];//��ʾ�趨ʱ��ڶ�λ
	/***********Set_Time����λ***********/
	seg19&=0x01;seg19|=Data1[SM%10];//��ʾ�趨ʱ�����λ
	/***********Set_Time����λ***********/
	seg20&=0x01;seg20|=Data1[M%10];//��ʾ�趨ʱ�����λ
	/***********Set_Timeð��ͼ��*********/
	seg19&=0xFE;seg19|=0x01;//��ʾ�趨ʱ��ð��
	/***********Set_Time��λͼ��*********/
	seg20&=0xFE;seg20|=0x01;//��ʾʱ�䵥λͼ��
	
	if(SetTime_State.L0 == 0)//û������ʱ��
    {
		seg17&=0xFE;seg17|=0x00;//��ʾ�趨ʱ���һλ��-��
		seg18&=0x00;seg18|=0x10;//��ʾ�趨ʱ��ڶ�λ��-��
		seg19&=0x01;seg19|=0x10;//��ʾ�趨ʱ�����λ��-��
		seg20&=0x01;seg20|=0x10;//��ʾ�趨ʱ�����λ��-��
	}
	if(Time_ShowFlag && EC11A_Knob == 0)//ʱ�䵽����ť�޲���ʱ
    {
		seg17&=0xFE;seg17|=0x00;//����ʾ�趨ʱ���һλ
		seg18&=0x00;seg18|=0x00;//����ʾ�趨ʱ��ڶ�λ
		seg19&=0x01;seg19|=0x00;//����ʾ�趨ʱ�����λ
		seg20&=0x01;seg20|=0x00;//����ʾ�趨ʱ�����λ
	}
	
	/*********************�»���*********************/
	if(Work_All)//��ȫ������ʱ
    {
        seg1&=0x03;seg1|=0xFC;//L5��L6������»���  
        if(Work_All_Time)//ѡ�й�λ1��Ϩ���»���ʱ
        {        
            switch(Work_Option)
            {
				case 1:seg1&=0x03;seg1|=0xF4;//L5�»���Ϩ��
                    break;
                case 2:seg1&=0x03;seg1|=0xF8;//L6�»���Ϩ��
                    break;
				case 3:seg1&=0x03;seg1|=0xEC;//L4�»���Ϩ��
                    break;
                case 4:seg1&=0x03;seg1|=0xDC;//L3�»���Ϩ��
                    break;
                case 5:seg1&=0x03;seg1|=0x7C;//L1�»���Ϩ��
                    break;
                case 6:seg1&=0x03;seg1|=0xBC;//L2�»���Ϩ��
                    break;
                default:
                    break;      
            }
        }
    }
    else
    {		 		 
        switch(Work_Option)//��λ��ѡ��
        {
			case 1:seg1&=0x03;seg1|=0x08;//��ʾL5������»���
                    break;
            case 2:seg1&=0x03;seg1|=0x04;//��ʾL6������»���
                    break;
			case 3:seg1&=0x03;seg1|=0x10;//��ʾL4������»���
                    break;
			case 4:seg1&=0x03;seg1|=0x20;//��ʾL3������»���
                    break;
            case 5:seg1&=0x03;seg1|=0x80;//��ʾL1������»���
                    break;
            case 6:seg1&=0x03;seg1|=0x40;//��ʾL2������»���
                    break;
            default:     
                break;
        }
    }
	
	if(Param.type == 0 || Param.type == 2)//����Ϊ����ʱL3��L4����ʾ
	{
		seg1&=0xCF;
		seg2&=0x3F;
		seg8&=0x00;
		seg9&=0x00;
		seg10&=0x00;
		seg11&=0x00;
	}
	
	if(Param.type <= 1)//���óɼ��ȿ�
	{
		seg3&=0xFD;seg3|=0x00;
		seg30&=0x00;
		seg31&=0x00;
		seg32&=0x00;
		seg12&=0x00;
		seg13&=0x00;
		seg14&=0x00;
		seg25&=0xF9;seg25|=0x00;
    }
	
	Write_Addr_Dat_N(0, seg1,1);
	Write_Addr_Dat_N(2, seg2,1);
	Write_Addr_Dat_N(4, seg3,1);
	Write_Addr_Dat_N(6, seg4,1);
	Write_Addr_Dat_N(8, seg5,1);
	Write_Addr_Dat_N(10, seg6,1);
	Write_Addr_Dat_N(12, seg7,1);
	Write_Addr_Dat_N(14, seg8,1);
	Write_Addr_Dat_N(16, seg9,1);
	Write_Addr_Dat_N(18, seg10,1);
	Write_Addr_Dat_N(20, seg11,1);
	Write_Addr_Dat_N(22, seg12,1);
	Write_Addr_Dat_N(24, seg13,1);
	Write_Addr_Dat_N(26, seg14,1);
	Write_Addr_Dat_N(28, seg15,1);
	Write_Addr_Dat_N(30, seg16,1);
	Write_Addr_Dat_N(32, seg17,1);
	Write_Addr_Dat_N(34, seg18,1);
	Write_Addr_Dat_N(36, seg19,1);
	Write_Addr_Dat_N(38, seg20,1);
	Write_Addr_Dat_N(40, seg21,1);
	Write_Addr_Dat_N(42, seg22,1);
	Write_Addr_Dat_N(44, seg23,1);
	Write_Addr_Dat_N(46, seg24,1);
	Write_Addr_Dat_N(48, seg25,1);
	Write_Addr_Dat_N(50, seg26,1);
	Write_Addr_Dat_N(52, seg27,1);
	Write_Addr_Dat_N(54, seg28,1);
	Write_Addr_Dat_N(56, seg29,1);
	Write_Addr_Dat_N(58, seg30,1);
	Write_Addr_Dat_N(60, seg31,1);
	Write_Addr_Dat_N(62, seg32,1);
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
        else if(Speed_ADDMode.L1 == 4)//�ٶ���ʾ����
		{
			Display_RelSpeed.L1 = 0;
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
		else if(Speed_ADDMode.L2 == 4)//�ٶ���ʾ����
		{
			Display_RelSpeed.L2 = 0;
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
		else if(Speed_ADDMode.L3 == 4)//�ٶ���ʾ����
		{
			Display_RelSpeed.L3 = 0;
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
		else if(Speed_ADDMode.L4 == 4)//�ٶ���ʾ����
		{
			Display_RelSpeed.L4 = 0;
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
		else if(Speed_ADDMode.L5 == 4)//�ٶ���ʾ����
		{
			Display_RelSpeed.L5 = 0;
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
		else if(Speed_ADDMode.L6 == 4)//�ٶ���ʾ����
		{
			Display_RelSpeed.L6 = 0;
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
		else if(Speed_ADDMode.L7 == 4)//�ٶ���ʾ����
		{
			Display_RelSpeed.L7 = 0;
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
		else if(Speed_ADDMode.L8 == 4)//�ٶ���ʾ����
		{
			Display_RelSpeed.L8 = 0;
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
 * ����ԭ�ͣ�void ADD_Show(float dT)
 * ��    �ܣ���ʾ����ʱ��
 * ��    ��: dT:ִ������
 * ��    ����float dT
*****************************************************************
*/
void ADD_Show(float dT)
{
    static float T;
	if(Run_Status == 0)
		return;
    if(ADD_Wait_Count)//��������������־λ����һ��������״̬����������ʱ
    {
        T += dT;
        if(T >= 0.2f)//1S
        {
            ADD_Wait_Count--;//����������־λ--
            if(ADD_Wait_Count == 0)//����������־λ����0ʱ
                Temp_ADDMode = 4;//�����ȶ��¶�ģʽ
            T = 0;
        }
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Temp(void)
 * ��    �ܣ��¶���ʾ����
*****************************************************************
*/
void Deal_Temp(void)
{
    if(Run_Status == 0 || (Run_Status == 1 && Temp_State == 0))//û������û���õ������
    {
		Rel_Temp = Ture_Temp;//��ʾʵ�ʲ���¶�
		Temp_New = 0;
		Temp_Last = 0;
    }
    else
    {
        if(Temp_ADDMode == 0)//�ж����ݴ�����ʾ
        {
			if(Rel_Temp < Ctrl_Temp)//ʵ���¶ȴ��ڿ����¶�
			{	
				Temp_ADDMode = 1;//����
				Temp_New = 0;
				Temp_Last = Rel_Temp;
			}
			else
			{
				Temp_ADDMode = 2;//����
				Temp_New = 0;
				Temp_Last = Rel_Temp;
			}
		}
        else if(Temp_ADDMode == 1)//�ڼ���ģʽ��
        {
			if(Rel_Temp < Ture_Temp)
				Temp_New = Ture_Temp;//��¼��ǰ�¶�
            if(Temp_New > Temp_Last)//��ǰ�¶ȴ�����һ���¶�
                Rel_Temp = Temp_New;//��ʾ��ǰ�¶�
            else//��ǰ�¶�С�ڵ�����һ���¶�
            {
                Rel_Temp = Temp_Last;//��ʾ��һ���¶ȣ������¶�С�ڵ�ǰ�¶ȡ����������¶ȵ�����
                Temp_New = Temp_Last;//����һ���¶ȸ�ֵ����ǰ�¶�
            }
            Temp_Last = Temp_New;//����ǰ�¶ȱ���
			if(Rel_Temp >= Ctrl_Temp - 20)//������ʾֵ���ڵ����趨ֵ
            {
				ADD_Wait_Count = (-(Temp_New-Ctrl_Temp)*10);//200S�Ļ���������ʾ  
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
                Temp_ADDMode = 4;//�����ȶ�ģʽ
            }
        }
        else if(Temp_ADDMode == 3)//����
        {
            if(Rel_Temp < Ctrl_Temp)
				Rel_Temp=(Ctrl_Temp-20)+(20-(ADD_Wait_Count)*2/20);//������ʾ��ֵ
        }
		else if(Temp_ADDMode == 4)//�ȶ�ģʽ��
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
        default:
            break;
    }
	Display_WorkSpeed(Display_Speed.L1,Display_Speed.L2,
					  Display_Speed.L3,Display_Speed.L4,
					  Display_Speed.L5,Display_Speed.L6,
				      Rel_Speed.L0,Set_Speed.L0,Rel_Temp,Set_Temp,Rel_Time.L0+59,Set_Time.L0);
}
