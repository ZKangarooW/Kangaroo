#include "Show.h"

/**********ȫ�ֱ���**********/
int32_t rel_time;//ʵʱʱ��
int32_t set_time;//�趨ʱ��
uint8_t time_status;//ʱ����ʾģʽ
uint8_t Set_Mode_Enable;//P����������ģʽ 0��ģʽ���ò�����ʾ 1��ģʽ������ʾ
uint8_t run_mode_flag;//����Pʱ��ʾ
uint8_t Select_Option;//����ʱ��ǰ���õ�ѡ��
uint16_t Twinkle_Time;//��˸��ʱ��
uint16_t Twinkle_On;//��˸����ʱ
uint8_t circle_dis;//�ݶ�ģʽ����Ȧת����ʾ�������벻�����˼Ĵ����������ȣ�
uint8_t circle_dis_flag;//��Ȧ��ʼת���������벻�����˼Ĵ����������ȣ�
uint8_t mode_flag_p1;//�ݶ�ģʽ��P1����˸�������벻�����˼Ĵ����������ȣ�
uint8_t mode_flag_p2;//�ݶ�ģʽ��P1����˸�������벻�����˼Ĵ����������ȣ�
uint8_t mode_run_p1;//�ݶ�ģʽ��P1��ֵ�������벻�����˼Ĵ����������ȣ�
uint8_t mode_run_p2;//�ݶ�ģʽ��P1��ֵ�������벻�����˼Ĵ����������ȣ�
uint8_t set_mode_p;//Pģʽ���л��ݶ�ģʽ���Ǿͼ���ģʽ 1���ݶ�ģʽ 0��pģʽ�������벻�����˼Ĵ����������ȣ�
uint8_t ADD_Wait_Count;//������ʾ��������
uint8_t SetTime_State;//δ�趨ʱ����ʾ��----��

/**********�ֲ�����**********/
uint8_t FIRST_Tab[] = {0xee, 0x24, 0xba, 0xb6, 0x74, 0xd6, 0xde, 0xa4, 0xfe, 0xf6};
uint8_t LAST_Tab[] = {0x77, 0X24, 0x5d, 0x6d, 0x2e, 0x6b, 0x7b, 0x25, 0x7f, 0x6f};
uint8_t MID_Tab[] =  {0x77, 0x12, 0x5d, 0x5b, 0x3a, 0x6b, 0x6f, 0x52, 0x7f, 0x7b};
uint8_t Tab[4] = {0, 0, 0, 0};
int Dis_Rel_Temp;//��ʾʵ���¶�
int Dis_Set_Temp;//��ʾ�¶�
int Dis_Rel_Time;//ʵʱʱ��
int Dis_Set_Time;//�趨ʱ��
uint8_t temp_flag;//ѡ�������¶�ʱ��˸
uint8_t time_flag;//ѡ������ʱ��ʱ��˸
uint8_t mode_flag;//ѡ������ģʽʱ��˸
uint8_t timeicn_flag,tempicn_flag;//����ʱʱ��ͼ����¶�ͼ����˸

/*
*****************************************************************
 * ����ԭ�ͣ� void time_icn(float dT)
 * ��    �ܣ� ����ʱʱ��ͼ����˸
*****************************************************************
*/
void time_icn(float dT)
{
	static float T,T1;
	if(Run_Status == 1 && ADD_Mode == 2)
	{
		T += dT;
		if(T >= 0.5f)
		{
			timeicn_flag = ~ timeicn_flag;
			T = 0;
		}
	}
	else
	{
		timeicn_flag = 0;
		T = 0;
	}
	if(Run_Status == 1 && set_temp > Dis_Rel_Temp)
	{
		T1 += dT;
		if(T1 >= 1.0f)
		{
			tempicn_flag = ~ tempicn_flag;
			T1 = 0;
		}
	}
	else
	{
		tempicn_flag = 0;
		T1 = 0;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Circle_Go(void)
 * ��    �ܣ� ���ݶ�ģʽ-������û���õ�
*****************************************************************
*/
void Circle_Go(void)
{
//    run_mode_flag = 1;//���̶���ʾ���
//    circle_dis_flag = 1;//���ʼ��Ȧ�������벻�����˼Ĵ����������ȣ�
    if((circle_dis_flag ) && (Run_Status > 0))//���ݶȱ�־λ��һ��ϵͳ����
    {
        circle_dis -= 1;//��ʾ--
        if(circle_dis < 1)//С��1��ʾһȦ����
        circle_dis = 12;//��ͷ��
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Cheak_ShowFlag(uint16_t dT)
 * ��    �ܣ� ��˸���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Cheak_ShowFlag(uint16_t dT)
{
    if(Select_Option == 0 || Key_Status)//���û������ѡ���У��򶼵���������˸
    {
        temp_flag = 0;//����
        time_flag = 0;//����
        mode_flag = 0;//����
        return;
    }
    Twinkle_Time += dT;//��˸��ʱ
    Twinkle_On -= dT;//�޲�����˸����ʱ
    if(Select_Option == 2)//�����¶�
    {
        if(Twinkle_Time % 500 == 0)//ÿ0.5Sת��״̬
        {
            temp_flag = ~ temp_flag;
            time_flag = 0;
            mode_flag = 0;
        }
    }
    else if(Select_Option == 3)//����ʱ��
    {
        if(Twinkle_Time % 500 == 0)//ÿ0.5Sת��״̬
        {
            time_flag = ~ time_flag;
            temp_flag = 0;
            mode_flag = 0;
        }
    }
    else if(Select_Option == 1)//����ģʽ
    {
        if(Twinkle_Time % 500 == 0)//ÿ0.5Sת��״̬
        {
            temp_flag = 0;
            time_flag = 0;
            mode_flag = ~ mode_flag;
        }
    }
    else if(Select_Option == 4)//���ݶ�ģʽ����˸P1�������벻�����˼Ĵ����������ȣ�
    {
        if(Twinkle_Time % 500 == 0)//ÿ0.5Sת��״̬
        {
            mode_flag_p1 = ~mode_flag_p1;
            mode_flag_p2 = ~mode_flag_p2;
        }
    }
    else if(Select_Option == 5)//���ݶ�ģʽ����˸P2�������벻�����˼Ĵ����������ȣ�
    {
        if(Twinkle_Time % 500 == 0)//ÿ0.5Sת��״̬
        {
            mode_flag_p1 = ~mode_flag_p1;
            mode_flag_p2 = ~mode_flag_p2;
        }
    }
    if(Twinkle_Time == 10000)//��˸6�Σ�Լ10S
    {
        Twinkle_Time = 0;
    }
    if(Twinkle_On == 0)//�����˸����ʱ����
    {
        Twinkle_Time = 0;//����˸��ʱ����
        setting_Mode = 0;
        Select_Option = 0;//ѡ����˸����
		SetOK_Flag = 1;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Dis_RelTemp(int dis_rel_temp)
 * ��    �ܣ� ��ʾʵ���¶�
 * ��    ��:  dis_rel_temp��ʵ���¶�
 * ��    ���� int dis_rel_temp
*****************************************************************
*/
void Dis_RelTemp(int dis_rel_temp)
{
    if(dis_rel_temp > 999)//ǧλ
    {
        Tab[0] = LAST_Tab[dis_rel_temp / 1000];
        Tab[1] = LAST_Tab[dis_rel_temp / 100 % 10];
        Tab[2] = LAST_Tab[dis_rel_temp / 10 % 10];
        Tab[3] = LAST_Tab[dis_rel_temp % 10];
    }
    else if(dis_rel_temp > 99)//��λ
    {
        Tab[0] = 0;
        Tab[1] = LAST_Tab[dis_rel_temp / 100];
        Tab[2] = LAST_Tab[dis_rel_temp / 10 % 10];
        Tab[3] = LAST_Tab[dis_rel_temp % 10];
    }
    else if(dis_rel_temp > 9)//ʮλ
    {
        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = LAST_Tab[dis_rel_temp / 10];
        Tab[3] = LAST_Tab[dis_rel_temp % 10];
    }
    else if(dis_rel_temp > -1)//��λ
    {
        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = LAST_Tab[dis_rel_temp / 10];
        Tab[3] = LAST_Tab[dis_rel_temp % 10];
    }
    else if(dis_rel_temp > -10)//����
    {
        Tab[0] = 0;
        Tab[1] = 0x08;
        Tab[2] = LAST_Tab[0];
        Tab[3] = LAST_Tab[(-dis_rel_temp)];
    }
    else if(dis_rel_temp > -100)//��ʮλ
    {
        Tab[0] = 0;
        Tab[1] = 0x08;
        Tab[2] = LAST_Tab[(-dis_rel_temp) / 10];
        Tab[3] = LAST_Tab[(-dis_rel_temp) % 10];
    }
    else//����λ
    {
        Tab[0] = 0x08;
        Tab[1] = LAST_Tab[1];
        Tab[2] = LAST_Tab[0];
        Tab[3] = LAST_Tab[0];
    }
    
	if(Run_Status == 1)
	{
		if(set_temp > Dis_Rel_Temp)
		{
			if(tempicn_flag)//��ʼ�����¶�ʱ
				Tab[2]=Tab[2]|0x80;//����ͼ��
			else
				Tab[2]=Tab[2]|0x00;//����ʾ����ͼ��
		}
		else 
			Tab[2]=Tab[2]|0x80;//����ͼ��
	}


    Tab[3] = Tab[3] | 0x80;//ʵ���¶ȵ�С����
    Tab[0] = Tab[0] | 0x80;//�����¶ȵġ����

    if(Set_Mode_Enable)//�������벻�����˼Ĵ����������ȣ�
    {
        if((((circle_dis<10)&&(circle_dis>3))&&(circle_dis!=0))||(circle_dis==13))
        {
            Tab[1]=Tab[1]|0x80;//ģʽ��Ȧ��ʾ
        }
        else if((circle_dis==3)||(circle_dis==0))
            Tab[1]=Tab[1]&0x7f;//ģʽ��Ȧ����ʾ
        if(run_mode_flag==0)
            Tab[1]=Tab[1]|0x80;//ģʽ��Ȧ��ʾ
    }
    else
    {
        Tab[1]=Tab[1]&0x7f;//ģʽ��Ȧ����ʾ
    }
    write_addr_dat_n(0, Tab[0], 1);
    write_addr_dat_n(2, Tab[1], 1);
    write_addr_dat_n(4, Tab[2], 1);
    write_addr_dat_n(6, Tab[3], 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Dis_SetTemp(int dis_set_temp)
 * ��    �ܣ� ��ʾ�趨�¶�
 * ��    ��:  dis_set_temp���趨�¶�
 * ��    ���� int dis_set_temp
*****************************************************************
*/
void Dis_SetTemp(int dis_set_temp)
{
	if(dis_set_temp > 999)//ǧλ
    {

        Tab[0] = LAST_Tab[dis_set_temp / 1000];
        Tab[1] = LAST_Tab[dis_set_temp / 100 % 10];
        Tab[2] = LAST_Tab[dis_set_temp / 10 % 10];
        Tab[3] = LAST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > 99)//��λ
    {

        Tab[0] = 0;
        Tab[1] = LAST_Tab[dis_set_temp / 100];
        Tab[2] = LAST_Tab[dis_set_temp / 10 % 10];
        Tab[3] = LAST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > -1)//ʮλ
    {

        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = LAST_Tab[dis_set_temp / 10];
        Tab[3] = LAST_Tab[dis_set_temp % 10];
    }
    else if(dis_set_temp > -10)//��λ
    {
        Tab[0] = 0;
        Tab[1] = 0x08;
        Tab[2] = LAST_Tab[0];
        Tab[3] = LAST_Tab[(-dis_set_temp)];
    }
    else if(dis_set_temp > -100)//����
    {
        Tab[0] = 0;
        Tab[1] = 0x08;
        Tab[2] = LAST_Tab[(-dis_set_temp) / 10];
        Tab[3] = LAST_Tab[(-dis_set_temp) % 10];
    }
    else//����λ
    {
        Tab[0] = 0x08;
        Tab[1] = LAST_Tab[1];
        Tab[2] = LAST_Tab[0];
        Tab[3] = LAST_Tab[0];
    }

    Tab[2] = Tab[2] | 0x80;//�����¶ȵ�С����

    if(temp_flag)//��˸
    {
        Tab[0] = 0;
        Tab[1] = 0;
        Tab[2] = 0;
        Tab[3] = 0;
    }

    write_addr_dat_n(32, Tab[3], 1);
    write_addr_dat_n(34, Tab[2], 1);
    write_addr_dat_n(36, Tab[1], 1);
    write_addr_dat_n(38, Tab[0], 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Dis_RelTime(int dis_rel_time)
 * ��    �ܣ� ��ʾʵ��ʱ��
 * ��    ��:  dis_rel_time��ʵ��ʱ��
 * ��    ���� int dis_rel_time
*****************************************************************
*/
void Dis_RelTime(int dis_rel_time)
{
    if(time_status ==0)//������ʾ״̬��
    {
        if(dis_rel_time>59)//������60��һ��λ
        {
            Tab[0]=LAST_Tab[dis_rel_time/60/10];
            Tab[1]=LAST_Tab[dis_rel_time/60%10];
            Tab[2]=LAST_Tab[dis_rel_time%60/10];
            Tab[3]=LAST_Tab[dis_rel_time%60%10];
        }
        else
        {
            Tab[0]=LAST_Tab[0];
            Tab[1]=LAST_Tab[0];
            Tab[2]=LAST_Tab[dis_rel_time%60/10];
            Tab[3]=LAST_Tab[dis_rel_time%60%10];
        }
    }
    else//�ڷ���ʾ״̬��
    {
        Tab[0]=LAST_Tab[dis_rel_time/3600/10];
        Tab[1]=LAST_Tab[dis_rel_time/3600%10];
        Tab[2]=LAST_Tab[dis_rel_time%3600/60/10];
        Tab[3]=LAST_Tab[dis_rel_time%3600/60%10];
    }
	if(timeicn_flag == 0)
	{
		Tab[2]=Tab[2]|0x80;//ʵʱʱ��ð��
	}
	else
	{
		Tab[2]=Tab[2]|0x00;//����ʾʵʱʱ��ð��
	}
	
	if(SetTime_State)//δ�趨ʱ����ʾ��----��
    {
        Tab[3]= 0x08;
        Tab[2]= 0x08;
        Tab[1]= 0x08;
        Tab[0]= 0x08;
    }
    
//    Tab[0]=Tab[0]|0x80;//����ͼ��

    write_addr_dat_n(8,Tab[0], 1);
    write_addr_dat_n(10,Tab[1], 1);
    write_addr_dat_n(12,Tab[2], 1);
    write_addr_dat_n(14,Tab[3], 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Dis_SetTime(int dis_set_time)
 * ��    �ܣ� ��ʾ�趨ʱ��
 * ��    ��:  dis_set_time���趨ʱ��
 * ��    ���� int dis_set_time
*****************************************************************
*/
void Dis_SetTime(int dis_set_time)
{
    if(dis_set_time > 3599)//����趨ʱ�����59.59����ʱ
    {
        time_status=1;//��λ��ɷ�
    }
    else
        time_status=0;//��Ȼ������

    if(time_status ==0)//������ʾ״̬��
    {
        if(dis_set_time>59)//������60��һ��λ
        {
            Tab[0]=MID_Tab[dis_set_time/60/10];
            Tab[1]=MID_Tab[dis_set_time/60%10];
            Tab[2]=MID_Tab[dis_set_time%60/10];
            Tab[3]=MID_Tab[dis_set_time%60%10];
        }
        else
        {
            Tab[0]=MID_Tab[0];
            Tab[1]=MID_Tab[0];
            Tab[2]=MID_Tab[dis_set_time%60/10];
            Tab[3]=MID_Tab[dis_set_time%60%10];
        }
    }
    else
    {
        Tab[0]=MID_Tab[dis_set_time/3600/10];
        Tab[1]=MID_Tab[dis_set_time/3600%10];
        Tab[2]=MID_Tab[dis_set_time%3600/60/10];
        Tab[3]=MID_Tab[dis_set_time%3600/60%10];
    }
	if(timeicn_flag == 0)
	{
		Tab[1]=Tab[1]|0x80;//�趨ʱ��ð��
	}
	else
	{
		Tab[1]=Tab[1]|0x00;//����ʾ�趨ʱ��ð��
	}
    if(SetTime_State)//δ�趨ʱ����ʾ��----��
    {
        Tab[3]= 0x08;
        Tab[2]= 0x08;
        Tab[1]= 0x08;
        Tab[0]= 0x08;
    }
    
    if(time_flag)//��˸
    {
        Tab[0]=0;
        Tab[1]=0;
        Tab[2]=0;
        Tab[3]=0;
    }

   
    if(time_status)
        Tab[3]=Tab[3]|0x80;//���ӵ�λ��ʾ
    else
        Tab[2]=Tab[2]|0x80;//�뵥λ��ʾ

    write_addr_dat_n(16,Tab[3], 1);
    write_addr_dat_n(18,Tab[2], 1);
    write_addr_dat_n(20,Tab[1], 1);
    write_addr_dat_n(22,Tab[0], 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Dis_RunMode(uint8_t E,uint8_t P,uint8_t P1,uint8_t P2)
 * ��    �ܣ� ��ʾ����ģʽ
 * ��    ��:  E��Pģʽ����ʾ   P��������ݶ�ѡ�� P1���ݶ�ģʽ��P1ֵ P2���ݶ�ģʽ��P2ֵ 
 * ��    ���� uint8_t E,uint8_t P,uint8_t P1,uint8_t P2
*****************************************************************
*/
void Dis_RunMode(uint8_t E,uint8_t P,uint8_t P1,uint8_t P2)
{
    static uint8_t tab1=0;
    if(E)//����Pģʽ��ʾ
    {
        if(circle_dis)//�����׼λ����һ
        {
            switch(circle_dis)//��switch���ʵ�ֶ���תȦ
            {
                case 0:write_addr_dat_n(24,0x00, 1);
                    break;
                case 1: tab1|=0X01;tab1&=0Xbf; write_addr_dat_n(24,tab1, 1);
                    break;
                case 2: tab1|=0X02;tab1&=0X7f; write_addr_dat_n(24,tab1, 1);
                    break;
                case 3: tab1|=0X04; write_addr_dat_n(24,tab1, 1);
                    break;
                case 4: tab1|=0X08; write_addr_dat_n(24,tab1, 1);
                    break;
                case 5: tab1|=0X10; write_addr_dat_n(24,tab1, 1);
                    break;
                case 6: tab1|=0X20; write_addr_dat_n(24,tab1, 1);
                    break;
                case 7: tab1|=0X40;tab1&=0XFE; write_addr_dat_n(24,tab1, 1);
                    break;
                case 8: tab1|=0X80;tab1&=0XFC; write_addr_dat_n(24,tab1, 1);
                    break;
                case 9: tab1&=0XFB; write_addr_dat_n(24,tab1, 1);
                    break;
                case 10: tab1&=0XF7; write_addr_dat_n(24,tab1, 1);
                    break;
                case 11: tab1&=0XEF; write_addr_dat_n(24,tab1, 1);
                    break;
                case 12: tab1&=0XCF; write_addr_dat_n(24,tab1, 1);
                    break;
                case 13: tab1&=0XCF; write_addr_dat_n(24,0xff, 1);
                    break;
            }
        }

        if(run_mode_flag==0)//���벻��pģʽ��
            write_addr_dat_n(24,0xff, 1);//�����ʧ������תȦ


        //ģʽѡ��
        if(P)//�ݶ�ģʽ��
        {
            Tab[2]=MID_Tab[P1];//ģʽһ
            Tab[1]=0X08;//-
            Tab[0]=MID_Tab[P2];//ģʽ��
        }
        else//����ģʽ��
        {
            Tab[0]=MID_Tab[run_mode];//��ʾģʽ��
			Tab[1]=0X08;//-
			Tab[2]=0x7c;//��ʾ��ĸP
        }

        if(mode_flag)//��˸��ʾ
        {
            Tab[0]=0;
            Tab[1]=0;
            Tab[2]=0;
        }

        if(mode_flag_p1)//�ݶ�ģʽ��P1��˸�������벻�����˼Ĵ����������ȣ�
            Tab[2]=0;
        if(mode_flag_p2)//�ݶ�ģʽ��P2��˸�������벻�����˼Ĵ����������ȣ�
            Tab[0]=0;

        //ģʽ��Ȧ��ʾ
        if((((circle_dis<11)&&(circle_dis>4))&&(circle_dis!=0))||(circle_dis==13))
            Tab[2]=Tab[2]|0x80;//ģʽ��Ȧ��ʾ
        else if((circle_dis==4)||(circle_dis==0))
            Tab[2]=Tab[2]&0x7f;//ģʽ��Ȧ����ʾ
        if(circle_dis==0)
            Tab[2]=Tab[2]|0x80;//ģʽ��Ȧ��ʾ
        if((((circle_dis<13)&&(circle_dis>6))&&(circle_dis!=0))||(circle_dis==13))
            Tab[0]=Tab[0]|0x80;//ģʽ��Ȧ��ʾ
        else if((circle_dis==6)||(circle_dis==0))
            Tab[0]=Tab[0]&0x7f;//ģʽ��Ȧ����ʾ
        if(circle_dis==0)
            Tab[0]=Tab[0]|0x80;//ģʽ��Ȧ��ʾ
        if((((circle_dis<12)&&(circle_dis>5))&&(circle_dis!=0))||(circle_dis==13))
            Tab[1]=Tab[1]|0x80;//ģʽ��Ȧ��ʾ
        else if((circle_dis==5)||(circle_dis==0))
            Tab[1]=Tab[1]&0x7f;//ģʽ��Ȧ����ʾ
        if(circle_dis==0)
            Tab[1]=Tab[1]|0x80;//ģʽ��Ȧ��ʾ
    }
    else//����ʾ
    {
        Tab[0]=0;
        Tab[1]=0;
        Tab[2]=0;
        write_addr_dat_n(24,0x00, 1);
    }

    write_addr_dat_n(26,Tab[0], 1);
    write_addr_dat_n(28,Tab[1], 1);
    write_addr_dat_n(30,Tab[2], 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void ADD_Show(uint16_t dT)
 * ��    �ܣ� ��ʾ����ʱ��
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void ADD_Show(uint16_t dT)
{
    static uint16_t T;
    if(ADD_Wait_Count)//��������������־λ����һ��������״̬����������ʱ
    {
        T += dT;
        if(T == 1000)//1S
        {
            ADD_Wait_Count--;//����������־λ--
            if(ADD_Wait_Count == 0)//����������־λ����0ʱ
                ADD_Mode = 2;//�����ȶ��¶�ģʽ
            T = 0;
        }
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
    static int Temp_New,Temp_Last;//�����¶ȡ�֮ǰ�¶�
	if(Run_Status == 0)//û�����������
    {
		ADD_Mode = 0;
		Dis_Rel_Temp = rel_temp;      
    }
    else//�����������
    {
        if(ADD_Mode == 0)//�ж����ݴ�����ʾ
        {     
		   if(set_temp > Dis_Rel_Temp)//�趨�¶ȴ�����ʾ�¶�
		   { 
				ADD_Mode = 1;//�������ģʽ��
				Temp_New = 0;//��֮ǰ�ļ���ֵ����
				Temp_Last = 0;//��֮ǰ�ļ���ֵ����  
			}
		   else
		   {
				ADD_Mode = 4;//���뽵��ģʽ��
				Temp_New = 0;//��֮ǰ�ļ���ֵ����
				Temp_Last = rel_temp;//��֮ǰ�ļ���ֵ����  
			}
        }
        if(ADD_Mode==1)//�ڼ���ģʽ��
        {
			if(Dis_Rel_Temp >= set_temp - 20)//ʵ���¶ȴ��ڵ����趨�¶�-2��
            {
                ADD_Wait_Count = (-(Dis_Rel_Temp-set_temp)*10);//200S�Ļ���������ʾ  
				ADD_Mode = 3;
				return;
            }
            Temp_New = rel_temp;//��¼��ǰ�¶�
            if(Temp_New > Temp_Last)//��ǰ�¶ȴ�����һ���¶�
                Dis_Rel_Temp = Temp_New;//��ʾ��ǰ�¶�
            else//��ǰ�¶�С����һ���¶�
            {
                Dis_Rel_Temp = Temp_Last;//��ʾ��һ���¶ȣ������¶�С�ڵ�ǰ�¶ȡ����������¶ȵ�����
                Temp_New = Temp_Last;//����һ���¶ȸ�ֵ����ǰ�¶�
            }
            Temp_Last = Temp_New;//����ǰ�¶ȱ��� 
			
        }
        else if(ADD_Mode == 2)//�¶��ȶ�ģʽ��
        {
			Dis_Rel_Temp = set_temp;//��ʾ��ǰ��ʾ�¶�
        }   
		else if(ADD_Mode == 3)//�ȴ����º�ʼ����
        {
			if(Dis_Rel_Temp < set_temp)
				Dis_Rel_Temp=(set_temp-20)+(20-(ADD_Wait_Count)*2/20);//������ʾ��ֵ
			else if(Dis_Rel_Temp > set_temp)
				Dis_Rel_Temp=(set_temp+20)-(20-(ADD_Wait_Count)*2/20);//������ʾ��ֵ
			else
				ADD_Mode = 2;
        }  
		else if(ADD_Mode == 4)//����ģʽ��
        {
            if(Dis_Rel_Temp <= set_temp + 20)//ʵ���¶�С�ڵ����趨�¶�
            {
                ADD_Wait_Count = (-(set_temp-Dis_Rel_Temp)*10);
				ADD_Mode = 3;
				return;
            }
            Temp_New = rel_temp;//��¼��ǰ�¶�
            if(Temp_New < Temp_Last)//��ǰ�¶�С����һ���¶�
                Dis_Rel_Temp = Temp_New;//��ʾ��ǰ�¶�
            else//��ǰ�¶ȴ�����һ���¶�
            {
                Dis_Rel_Temp = Temp_Last;//��ʾ��һ���¶ȣ������¶ȴ��ڵ�ǰ�¶ȡ������½��¶ȵ�����
                Temp_New = Temp_Last;//����һ���¶ȸ�ֵ����ǰ�¶�
            }
            Temp_Last = Temp_New;//����ǰ�¶ȱ���
        }  		
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void LCD_Display(void)
 * ��    �ܣ���Ļ��ʾ
*****************************************************************
*/
void LCD_Display(void)
{
    Deal_Temp();
    
    /*********************��ʾʵ���¶�********************/
    Dis_RelTemp(Dis_Rel_Temp);

    /*********************��ʾ�趨�¶�********************/
    Dis_Set_Temp = set_temp;
    Dis_SetTemp(Dis_Set_Temp);

    /*********************��ʾʵ��ʱ��********************/
    Dis_Rel_Time = rel_time;
    Dis_RelTime(Dis_Rel_Time);

    /*********************��ʾ�趨ʱ��********************/
    Dis_Set_Time = set_time;
    Dis_SetTime(Dis_Set_Time);

    Dis_RunMode(Set_Mode_Enable,set_mode_p,mode_run_p1,mode_run_p2);//Pģʽ

}
