#include "Show.h"

/**********ȫ�ֱ�������******/
float Speed_Twinkle_Time,Time_Twinkle_Time;//�ٶ���˸ʱ���ʱ����˸ʱ��

/**********�ֲ���������******/
uint8_t Speed_ShowFlag,Time_ShowFlag;//�ٶȡ�ʱ����ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t cnt;

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
	static float Speed_T,Time_T;
	if(Speed_Twinkle_Time && !EC11A[0].EC11A_Knob)//�ٶ���˸��û�в�������ʱ
    {
		Speed_T += dT;
		if(Speed_T >= 0.5f)
		{
			Speed_Twinkle_Time -= 0.5;//��˸��ʱ
			Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
			if(Speed_Twinkle_Time == 0)//�����˸����
			{
				SpeedSet_Flag = 1;//�����ٶ��趨
				Beep_Time = 0.1;//��������0.1S
			} 
			Speed_T = 0;		
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//����
		Speed_T = 0;
	}
	
	if(Time_Twinkle_Time && !EC11A[1].EC11A_Knob)//ʱ����˸��û�в�������ʱ
    {
		Time_T += dT;
		if(Time_T >= 0.5f)
		{
			Time_Twinkle_Time -= 0.5;//��˸��ʱ
			Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
			if(Time_Twinkle_Time == 0)//�����˸����
			{
				TimeSet_Flag = 1;//����ʱ���趨
				Beep_Time = 0.1;//��������0.1S
			} 
			Time_T = 0;			
		}			
    }
	else
	{
		Time_ShowFlag = 0;//����
		Time_T = 0;
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
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Screen(int16_t dis_set_speed,int16_t dis_rel_speed,int32_t dis_set_time,int32_t dis_rel_time)
 * ��    �ܣ���ʾ��Ļ����
 * ��    ��: dis_set_speed���趨ת�٣�dis_rel_speed��ʵ��ת�٣�dis_set_time���趨ʱ�䣬dis_rel_time��ʵ��ʱ��
 * ��    ����int16_t dis_set_speed,int16_t dis_rel_speed,int32_t dis_set_time,int32_t dis_rel_time
*****************************************************************
*/
void Display_Screen(int16_t dis_set_speed,int16_t dis_rel_speed,int32_t dis_set_time,int32_t dis_rel_time)
{
	uint8_t seg[16] = {0};
//	uint8_t seg0,seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9,seg10,seg11,seg12,seg13,seg14,seg15;
//	seg0=0;seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;seg10=0;seg11=0;seg12=0;seg13=0;seg14=0;;seg15=0;
	uint16_t Val;//���ڰ�ʮ��ȡ����������
	uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
    
    /***********dis_set_speedǧλ***********/
    if(!Speed_ShowFlag)//��˸��ʾ
    {
        if(dis_set_speed > 999)//����999ʱ
        {
            Val=dis_set_speed/1000;//ȡ��ǧλ
            if(dis_set_speed > 9999)//����9999ʱ
                Val=Val%10;//ȡ��ǧλ
            switch(Val)
            {
                case 0:seg[0]&=0xFE;seg[1]&=0xFE;seg[3]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[0]|=0x01;seg[1]|=0x01;seg[3]|=0x01;seg[5]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//����0
                    break;
                case 1:seg[3]&=0xFE;seg[5]&=0xFE;
                        seg[3]|=0x01;seg[5]|=0x01;//����1
                    break;
                case 2:seg[0]&=0xFE;seg[1]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[7]&=0xFE;
                        seg[0]|=0x01;seg[1]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[7]|=0x01;//����2
                    break;
                case 3:seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[7]&=0xFE;
                        seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[7]|=0x01;//����3
                    break;	
                case 4:seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;
                        seg[3]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[6]|=0x01;//����4
                    break;	
                case 5:seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//����5
                    break;	
                case 6:seg[0]&=0xFE;seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[0]|=0x01;seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//����6
                    break;	
                case 7:seg[3]&=0xFE;seg[5]&=0xFE;seg[7]&=0xFE;
                        seg[3]|=0x01;seg[5]|=0x01;seg[7]|=0x01;//����7
                    break;	
                case 8:seg[0]&=0xFE;seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[0]|=0x01;seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//����8
                    break;	
                case 9:seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//����9
                    break;
                default:
                    break;
            }			
        }
        else
        {
            seg[0]&=0xFE;seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
            seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//����ʾ
        }

        /***********dis_set_speed��λ***********/
        if(dis_set_speed > 99)//����99ʱ
        {
            Val=dis_set_speed/100;//ȡ����λ
            if(dis_set_speed > 999)//����999ʱ
                Val=Val%10;//ȡ����λ
            switch(Val)
            {
                case 0:seg[0]&=0xFD;seg[1]&=0xFD;seg[3]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[0]|=0x02;seg[1]|=0x02;seg[3]|=0x02;seg[5]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//����0
                    break;
                case 1:seg[3]&=0xFD;seg[5]&=0xFD;
                        seg[3]|=0x02;seg[5]|=0x02;//����1
                    break;
                case 2:seg[0]&=0xFD;seg[1]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[7]&=0xFD;
                        seg[0]|=0x02;seg[1]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[7]|=0x02;//����2
                    break;
                case 3:seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[7]&=0xFD;
                        seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[7]|=0x02;//����3
                    break;	
                case 4:seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;
                        seg[3]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[6]|=0x02;//����4
                    break;	
                case 5:seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//����5
                    break;	
                case 6:seg[0]&=0xFD;seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[0]|=0x02;seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//����6
                    break;	
                case 7:seg[3]&=0xFD;seg[5]&=0xFD;seg[7]&=0xFD;
                        seg[3]|=0x02;seg[5]|=0x02;seg[7]|=0x02;//����7
                    break;	
                case 8:seg[0]&=0xFD;seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[0]|=0x02;seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//����8
                    break;	
                case 9:seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//����9
                    break;
                default:
                    break;
            }			
        }
        else
        {
            seg[0]&=0xFD;seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
            seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//����ʾ
        }
        
        /***********dis_set_speedʮλ***********/
        if(dis_set_speed > 9)//����9ʱ
        {
            Val=dis_set_speed/10;//ȡ��ʮλ
            if(dis_set_speed > 99)//����99ʱ
                Val=Val%10;//ȡ��ʮλ
            switch(Val)
            {
                case 0:seg[0]&=0xFB;seg[1]&=0xFB;seg[3]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[0]|=0x04;seg[1]|=0x04;seg[3]|=0x04;seg[5]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//����0
                    break;
                case 1:seg[3]&=0xFB;seg[5]&=0xFB;
                        seg[3]|=0x04;seg[5]|=0x04;//����1
                    break;
                case 2:seg[0]&=0xFB;seg[1]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[7]&=0xFB;
                        seg[0]|=0x04;seg[1]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[7]|=0x04;//����2
                    break;
                case 3:seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[7]&=0xFB;
                        seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[7]|=0x04;//����3
                    break;	
                case 4:seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;
                        seg[3]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[6]|=0x04;//����4
                    break;	
                case 5:seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//����5
                    break;	
                case 6:seg[0]&=0xFB;seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[0]|=0x04;seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//����6
                    break;	
                case 7:seg[3]&=0xFB;seg[5]&=0xFB;seg[7]&=0xFB;
                        seg[3]|=0x04;seg[5]|=0x04;seg[7]|=0x04;//����7
                    break;	
                case 8:seg[0]&=0xFB;seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[0]|=0x04;seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//����8
                    break;	
                case 9:seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//����9
                    break;
                default:
                    break;
            }			
        }
        else
        {
            seg[0]&=0xFB;seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
            seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//����ʾ
        }
        
        /***********dis_set_speed��λ***********/
        Val=dis_set_speed%10;//ȡ����λ
        switch(Val)
        {
            case 0:seg[0]&=0xF7;seg[1]&=0xF7;seg[3]&=0xF7;seg[5]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[0]|=0x08;seg[1]|=0x08;seg[3]|=0x08;seg[5]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//����0
                break;
            case 1:seg[3]&=0xF7;seg[5]&=0xF7;
                    seg[3]|=0x08;seg[5]|=0x08;//����1
                break;
            case 2:seg[0]&=0xF7;seg[1]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[7]&=0xF7;
                    seg[0]|=0x08;seg[1]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[7]|=0x08;//����2
                break;
            case 3:seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[7]&=0xF7;
                    seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[7]|=0x08;//����3
                break;	
            case 4:seg[3]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[6]&=0xF7;
                    seg[3]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[6]|=0x08;//����4
                break;	
            case 5:seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//����5
                break;	
            case 6:seg[0]&=0xF7;seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[0]|=0x08;seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//����6
                break;	
            case 7:seg[3]&=0xF7;seg[5]&=0xF7;seg[7]&=0xF7;
                    seg[3]|=0x08;seg[5]|=0x08;seg[7]|=0x08;//����7
                break;	
            case 8:seg[0]&=0xF7;seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[0]|=0x08;seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//����8
                break;	
            case 9:seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//����9
                break;
            default:
                break;
        }	
    }
    else
    {		
        seg[0]&=0xF0;seg[1]&=0xF0;seg[3]&=0xF0;seg[4]&=0xF0;seg[5]&=0xF0;seg[6]&=0xF0;seg[7]&=0xF0;
        seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//����ʾ
    }
    
    /***********dis_rel_speedǧλ***********/
    if(dis_rel_speed > 999)//����999ʱ
    {
        Val=dis_rel_speed/1000;//ȡ��ǧλ
        if(dis_rel_speed > 9999)//����9999ʱ
            Val=Val%10;//ȡ��ǧλ
        switch(Val)
        {
            case 0:seg[0]&=0xEF;seg[1]&=0xEF;seg[3]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[0]|=0x10;seg[1]|=0x10;seg[3]|=0x10;seg[5]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//����0
                break;
            case 1:seg[3]&=0xEF;seg[5]&=0xEF;
                    seg[3]|=0x10;seg[5]|=0x10;//����1
                break;
            case 2:seg[0]&=0xEF;seg[1]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[7]&=0xEF;
                    seg[0]|=0x10;seg[1]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[7]|=0x10;//����2
                break;
            case 3:seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[7]&=0xEF;
                    seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[7]|=0x10;//����3
                break;	
            case 4:seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;
                    seg[3]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[6]|=0x10;//����4
                break;	
            case 5:seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//����5
                break;	
            case 6:seg[0]&=0xEF;seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[0]|=0x10;seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//����6
                break;	
            case 7:seg[3]&=0xEF;seg[5]&=0xEF;seg[7]&=0xEF;
                    seg[3]|=0x10;seg[5]|=0x10;seg[7]|=0x10;//����7
                break;	
            case 8:seg[0]&=0xEF;seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[0]|=0x10;seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//����8
                break;	
            case 9:seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//����9
                break;
            default:
                break;
        }			
    }
    else
    {
        seg[0]&=0xEF;seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
        seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//����ʾ
    }

    /***********dis_rel_speed��λ***********/
    if(dis_rel_speed > 99)//����99ʱ
    {
        Val=dis_rel_speed/100;//ȡ����λ
        if(dis_rel_speed > 999)//����999ʱ
            Val=Val%10;//ȡ����λ
        switch(Val)
        {
            case 0:seg[0]&=0xDF;seg[1]&=0xDF;seg[3]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[0]|=0x20;seg[1]|=0x20;seg[3]|=0x20;seg[5]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//����0
                break;
            case 1:seg[3]&=0xDF;seg[5]&=0xDF;
                    seg[3]|=0x20;seg[5]|=0x20;//����1
                break;
            case 2:seg[0]&=0xDF;seg[1]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[7]&=0xDF;
                    seg[0]|=0x20;seg[1]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[7]|=0x20;//����2
                break;
            case 3:seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[7]&=0xDF;
                    seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[7]|=0x20;//����3
                break;	
            case 4:seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;
                    seg[3]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[6]|=0x20;//����4
                break;	
            case 5:seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//����5
                break;	
            case 6:seg[0]&=0xDF;seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[0]|=0x20;seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//����6
                break;	
            case 7:seg[3]&=0xDF;seg[5]&=0xDF;seg[7]&=0xDF;
                    seg[3]|=0x20;seg[5]|=0x20;seg[7]|=0x20;//����7
                break;	
            case 8:seg[0]&=0xDF;seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[0]|=0x20;seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//����8
                break;	
            case 9:seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//����9
                break;
            default:
                break;
        }			
    }
    else
    {
        seg[0]&=0xDF;seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
        seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//����ʾ
    }
    /***********dis_rel_speedʮλ***********/
    if(dis_rel_speed > 9)//����9ʱ
    {
        Val=dis_rel_speed/10;//ȡ��ʮλ
        if(dis_rel_speed > 99)//����99ʱ
            Val=Val%10;//ȡ��ʮλ
        switch(Val)
        {
            case 0:seg[0]&=0xBF;seg[1]&=0xBF;seg[3]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[0]|=0x40;seg[1]|=0x40;seg[3]|=0x40;seg[5]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//����0
                break;
            case 1:seg[3]&=0xBF;seg[5]&=0xBF;
                    seg[3]|=0x40;seg[5]|=0x40;//����1
                break;
            case 2:seg[0]&=0xBF;seg[1]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[7]&=0xBF;
                    seg[0]|=0x40;seg[1]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[7]|=0x40;//����2
                break;
            case 3:seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[7]&=0xBF;
                    seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[7]|=0x40;//����3
                break;	
            case 4:seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;
                    seg[3]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[6]|=0x40;//����4
                break;	
            case 5:seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//����5
                break;	
            case 6:seg[0]&=0xBF;seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[0]|=0x40;seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//����6
                break;	
            case 7:seg[3]&=0xBF;seg[5]&=0xBF;seg[7]&=0xBF;
                    seg[3]|=0x40;seg[5]|=0x40;seg[7]|=0x40;//����7
                break;	
            case 8:seg[0]&=0xBF;seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[0]|=0x40;seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//����8
                break;	
            case 9:seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//����9
                break;
            default:
                break;
        }			
    }
    else
    {
        seg[0]&=0xBF;seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
        seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//����ʾ
    }
    /***********dis_rel_speed��λ***********/
    Val=dis_rel_speed%10;//ȡ����λ
    switch(Val)
    {
        case 0:seg[0]&=0x7F;seg[1]&=0x7F;seg[3]&=0x7F;seg[5]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[0]|=0x80;seg[1]|=0x80;seg[3]|=0x80;seg[5]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//����0
            break;
        case 1:seg[3]&=0x7F;seg[5]&=0x7F;
                seg[3]|=0x80;seg[5]|=0x80;//����1
            break;
        case 2:seg[0]&=0x7F;seg[1]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[7]&=0x7F;
                seg[0]|=0x80;seg[1]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[7]|=0x80;//����2
            break;
        case 3:seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[7]&=0x7F;
                seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[7]|=0x80;//����3
            break;	
        case 4:seg[3]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[6]&=0x7F;
                seg[3]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[6]|=0x80;//����4
            break;	
        case 5:seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//����5
            break;	
        case 6:seg[0]&=0x7F;seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[0]|=0x80;seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//����6
            break;	
        case 7:seg[3]&=0x7F;seg[5]&=0x7F;seg[7]&=0x7F;
                seg[3]|=0x80;seg[5]|=0x80;seg[7]|=0x80;//����7
            break;	
        case 8:seg[0]&=0x7F;seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[0]|=0x80;seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//����8
            break;	
        case 9:seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//����9
            break;
        default:
            break;
    }	
    
    if(!Time_ShowFlag)//�趨ʱ����˸
    {
        if(dis_set_time)//�趨ʱ�����0
        {
            /***********dis_set_time**********/
            SH=dis_set_time/3600/10;//����ʮλ��λ��Сʱ��
            H=dis_set_time/3600%10;//�����λ��λ��Сʱ��
            SM=dis_set_time%3600/60/10;//����ʮ��λ��λ�ķ�����
            M=dis_set_time%3600/60%10;//�������λ��λ�ķ�����
            
            switch(SH)
            {
                case 0:seg[8]&=0xFE;seg[9]&=0xFE;seg[11]&=0xFE;seg[13]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[8]|=0x01;seg[9]|=0x01;seg[11]|=0x01;seg[13]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//����0
                    break;
                case 1:seg[11]&=0xFE;seg[13]&=0xFE;
                        seg[11]|=0x01;seg[13]|=0x01;//����1
                    break;
                case 2:seg[8]&=0xFE;seg[9]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[15]&=0xFE;
                        seg[8]|=0x01;seg[9]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[15]|=0x01;//����2
                    break;
                case 3:seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[15]&=0xFE;
                        seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[15]|=0x01;//����3
                    break;	
                case 4:seg[11]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[14]&=0xFE;
                        seg[11]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[14]|=0x01;//����4
                    break;	
                case 5:seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//����5
                    break;	
                case 6:seg[8]&=0xFE;seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[8]|=0x01;seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//����6
                    break;	
                case 7:seg[11]&=0xFE;seg[13]&=0xFE;seg[15]&=0xFE;
                        seg[11]|=0x01;seg[13]|=0x01;seg[15]|=0x01;//����7
                    break;	
                case 8:seg[8]&=0xFE;seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[8]|=0x01;seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//����8
                    break;	
                case 9:seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//����9
                    break;
                default:
                    break;
            }		
            switch(H)
            {
                case 0:seg[8]&=0xFD;seg[9]&=0xFD;seg[11]&=0xFD;seg[13]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[8]|=0x02;seg[9]|=0x02;seg[11]|=0x02;seg[13]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//����0
                    break;
                case 1:seg[11]&=0xFD;seg[13]&=0xFD;
                        seg[11]|=0x02;seg[13]|=0x02;//����1
                    break;
                case 2:seg[8]&=0xFD;seg[9]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[15]&=0xFD;
                        seg[8]|=0x02;seg[9]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[15]|=0x02;//����2
                    break;
                case 3:seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[15]&=0xFD;
                        seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[15]|=0x02;//����3
                    break;	
                case 4:seg[11]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[14]&=0xFD;
                        seg[11]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[14]|=0x02;//����4
                    break;	
                case 5:seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//����5
                    break;	
                case 6:seg[8]&=0xFD;seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[8]|=0x02;seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//����6
                    break;	
                case 7:seg[11]&=0xFD;seg[13]&=0xFD;seg[15]&=0xFD;
                        seg[11]|=0x02;seg[13]|=0x02;seg[15]|=0x02;//����7
                    break;	
                case 8:seg[8]&=0xFD;seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[8]|=0x02;seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//����8
                    break;	
                case 9:seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//����9
                    break;
                default:
                    break;
            }		
            switch(SM)
            {
                case 0:seg[8]&=0xFB;seg[9]&=0xFB;seg[11]&=0xFB;seg[13]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[8]|=0x04;seg[9]|=0x04;seg[11]|=0x04;seg[13]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//����0
                    break;
                case 1:seg[11]&=0xFB;seg[13]&=0xFB;
                        seg[11]|=0x04;seg[13]|=0x04;//����1
                    break;
                case 2:seg[8]&=0xFB;seg[9]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[15]&=0xFB;
                        seg[8]|=0x04;seg[9]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[15]|=0x04;//����2
                    break;
                case 3:seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[15]&=0xFB;
                        seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[15]|=0x04;//����3
                    break;	
                case 4:seg[11]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[14]&=0xFB;
                        seg[11]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[14]|=0x04;//����4
                    break;	
                case 5:seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//����5
                    break;	
                case 6:seg[8]&=0xFB;seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[8]|=0x04;seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//����6
                    break;	
                case 7:seg[11]&=0xFB;seg[13]&=0xFB;seg[15]&=0xFB;
                        seg[11]|=0x04;seg[13]|=0x04;seg[15]|=0x04;//����7
                    break;	
                case 8:seg[8]&=0xFB;seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[8]|=0x04;seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//����8
                    break;	
                case 9:seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//����9
                    break;
                default:
                    break;
            }		
            switch(M)
            {
                case 0:seg[8]&=0xF7;seg[9]&=0xF7;seg[11]&=0xF7;seg[13]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[8]|=0x08;seg[9]|=0x08;seg[11]|=0x08;seg[13]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//����0
                    break;
                case 1:seg[11]&=0xF7;seg[13]&=0xF7;
                        seg[11]|=0x08;seg[13]|=0x08;//����1
                    break;
                case 2:seg[8]&=0xF7;seg[9]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[15]&=0xF7;
                        seg[8]|=0x08;seg[9]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[15]|=0x08;//����2
                    break;
                case 3:seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[15]&=0xF7;
                        seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[15]|=0x08;//����3
                    break;	
                case 4:seg[11]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[14]&=0xF7;
                        seg[11]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[14]|=0x08;//����4
                    break;	
                case 5:seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//����5
                    break;	
                case 6:seg[8]&=0xF7;seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[8]|=0x08;seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//����6
                    break;	
                case 7:seg[11]&=0xF7;seg[13]&=0xF7;seg[15]&=0xF7;
                        seg[11]|=0x08;seg[13]|=0x08;seg[15]|=0x08;//����7
                    break;	
                case 8:seg[8]&=0xF7;seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[8]|=0x08;seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//����8
                    break;	
                case 9:seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//����9
                    break;
                default:
                    break;
            }
        }
        else
        {
            seg[8]&=0xF0;seg[9]&=0xF0;seg[11]&=0xF0;seg[12]&=0xF0;seg[13]&=0xF0;seg[14]&=0xF0;seg[15]&=0xF0;
            seg[8]|=0x00;seg[9]|=0x00;seg[11]|=0x00;seg[12]|=0x0F;seg[13]|=0x00;seg[14]|=0x00;seg[15]|=0x00;//��ʾ��-- --��
        }
    }
    else
    {
        seg[8]&=0xF0;seg[9]&=0xF0;seg[11]&=0xF0;seg[12]&=0xF0;seg[13]&=0xF0;seg[14]&=0xF0;seg[15]&=0xF0;
        seg[8]|=0x00;seg[9]|=0x00;seg[11]|=0x00;seg[12]|=0x00;seg[13]|=0x00;seg[14]|=0x00;seg[15]|=0x00;
    }
	
    /***********dis_rel_time**********/
    if(Time.Rel || dis_set_time)//��ʾʱ���ʾΪ0
	{
        SH=dis_rel_time/3600/10;//����ʮλ��λ��Сʱ��
        H=dis_rel_time/3600%10;//�����λ��λ��Сʱ��
        SM=dis_rel_time%3600/60/10;//����ʮ��λ��λ�ķ�����
        M=dis_rel_time%3600/60%10;//�������λ��λ�ķ�����
        
        switch(SH)
        {
            case 0:seg[8]&=0xEF;seg[9]&=0xEF;seg[11]&=0xEF;seg[13]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[8]|=0x10;seg[9]|=0x10;seg[11]|=0x10;seg[13]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//����0
                break;
            case 1:seg[11]&=0xEF;seg[13]&=0xEF;
                    seg[11]|=0x10;seg[13]|=0x10;//����1
                break;
            case 2:seg[8]&=0xEF;seg[9]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[15]&=0xEF;
                    seg[8]|=0x10;seg[9]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[15]|=0x10;//����2
                break;
            case 3:seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[15]&=0xEF;
                    seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[15]|=0x10;//����3
                break;	
            case 4:seg[11]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[14]&=0xEF;
                    seg[11]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[14]|=0x10;//����4
                break;	
            case 5:seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//����5
                break;	
            case 6:seg[8]&=0xEF;seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[8]|=0x10;seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//����6
                break;	
            case 7:seg[11]&=0xEF;seg[13]&=0xEF;seg[15]&=0xEF;
                    seg[11]|=0x10;seg[13]|=0x10;seg[15]|=0x10;//����7
                break;	
            case 8:seg[8]&=0xEF;seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[8]|=0x10;seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//����8
                break;	
            case 9:seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//����9
                break;
            default:
                break;
        }		
        switch(H)
        {
            case 0:seg[8]&=0xDF;seg[9]&=0xDF;seg[11]&=0xDF;seg[13]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[8]|=0x20;seg[9]|=0x20;seg[11]|=0x20;seg[13]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//����0
                break;
            case 1:seg[11]&=0xDF;seg[13]&=0xDF;
                    seg[11]|=0x20;seg[13]|=0x20;//����1
                break;
            case 2:seg[8]&=0xDF;seg[9]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[15]&=0xDF;
                    seg[8]|=0x20;seg[9]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[15]|=0x20;//����2
                break;
            case 3:seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[15]&=0xDF;
                    seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[15]|=0x20;//����3
                break;	
            case 4:seg[11]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[14]&=0xDF;
                    seg[11]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[14]|=0x20;//����4
                break;	
            case 5:seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//����5
                break;	
            case 6:seg[8]&=0xDF;seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[8]|=0x20;seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//����6
                break;	
            case 7:seg[11]&=0xDF;seg[13]&=0xDF;seg[15]&=0xDF;
                    seg[11]|=0x20;seg[13]|=0x20;seg[15]|=0x20;//����7
                break;	
            case 8:seg[8]&=0xDF;seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[8]|=0x20;seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//����8
                break;	
            case 9:seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//����9
                break;
            default:
                break;
        }		
        switch(SM)
        {
            case 0:seg[8]&=0xBF;seg[9]&=0xBF;seg[11]&=0xBF;seg[13]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[8]|=0x40;seg[9]|=0x40;seg[11]|=0x40;seg[13]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//����0
                break;
            case 1:seg[11]&=0xBF;seg[13]&=0xBF;
                    seg[11]|=0x40;seg[13]|=0x40;//����1
                break;
            case 2:seg[8]&=0xBF;seg[9]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[15]&=0xBF;
                    seg[8]|=0x40;seg[9]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[15]|=0x40;//����2
                break;
            case 3:seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[15]&=0xBF;
                    seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[15]|=0x40;//����3
                break;	
            case 4:seg[11]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[14]&=0xBF;
                    seg[11]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[14]|=0x40;//����4
                break;	
            case 5:seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//����5
                break;	
            case 6:seg[8]&=0xBF;seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[8]|=0x40;seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//����6
                break;	
            case 7:seg[11]&=0xBF;seg[13]&=0xBF;seg[15]&=0xBF;
                    seg[11]|=0x40;seg[13]|=0x40;seg[15]|=0x40;//����7
                break;	
            case 8:seg[8]&=0xBF;seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[8]|=0x40;seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//����8
                break;	
            case 9:seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//����9
                break;
            default:
                break;
        }		
        switch(M)
        {
            case 0:seg[8]&=0x7F;seg[9]&=0x7F;seg[11]&=0x7F;seg[13]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[8]|=0x80;seg[9]|=0x80;seg[11]|=0x80;seg[13]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//����0
                break;
            case 1:seg[11]&=0x7F;seg[13]&=0x7F;
                    seg[11]|=0x80;seg[13]|=0x80;//����1
                break;
            case 2:seg[8]&=0x7F;seg[9]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[15]&=0x7F;
                    seg[8]|=0x80;seg[9]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[15]|=0x80;//����2
                break;
            case 3:seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[15]&=0x7F;
                    seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[15]|=0x80;//����3
                break;	
            case 4:seg[11]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[14]&=0x7F;
                    seg[11]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[14]|=0x80;//����4
                break;	
            case 5:seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//����5
                break;	
            case 6:seg[8]&=0x7F;seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[8]|=0x80;seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//����6
                break;	
            case 7:seg[11]&=0x7F;seg[13]&=0x7F;seg[15]&=0x7F;
                    seg[11]|=0x80;seg[13]|=0x80;seg[15]|=0x80;//����7
                break;	
            case 8:seg[8]&=0x7F;seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[8]|=0x80;seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//����8
                break;	
            case 9:seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//����9
                break;
            default:
                break;
        }	
    }
    else
    {
        seg[8]&=0x0F;seg[9]&=0x0F;seg[11]&=0x0F;seg[12]&=0x0F;seg[13]&=0x0F;seg[14]&=0x0F;seg[15]&=0x0F;
        seg[8]|=0x00;seg[9]|=0x00;seg[11]|=0x00;seg[12]|=0xF0;seg[13]|=0x00;seg[14]|=0x00;seg[15]|=0x00;//��ʾ��-- --��
    }    
    
    /**********�趨ʱ��ð��**********/
    seg[10]&=0xDF;seg[10]|=0x20;
    /**********ʵ��ʱ��ð��**********/
    seg[10]&=0xFD;seg[10]|=0x02;
    
	
	
	TM1640_Write_DATA(cnt, seg[cnt]);
	cnt ++;
	if(cnt >= 16)
		cnt= 0;
//	TM1640_Write_DATA(1, seg[1]);
//	TM1640_Write_DATA(2, seg[2]);
//	TM1640_Write_DATA(3, seg[3]);
//	TM1640_Write_DATA(4, seg[4]);
//	TM1640_Write_DATA(5, seg[5]);
//	TM1640_Write_DATA(6, seg[6]);
//	TM1640_Write_DATA(7, seg[7]);
//	TM1640_Write_DATA(8, seg[8]);
//	TM1640_Write_DATA(9, seg[9]);
//    TM1640_Write_DATA(10, seg[10]);
//	TM1640_Write_DATA(11, seg[11]);
//	TM1640_Write_DATA(12, seg[12]);
//	TM1640_Write_DATA(13, seg[13]);
//	TM1640_Write_DATA(14, seg[14]);
//    TM1640_Write_DATA(15, seg[15]);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Speed(float dT)
 * ��    �ܣ��ٶ���ʾ����
*****************************************************************
*/
int16_t Speed_CalVal;//�������ٶ�
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
			Speed_Arg.Kp = 20 * 0.001f;
			Speed_Arg.Ki = 44 * 0.001f;
		}
		if(Speed.ADDMode==1)//�ڽ������ģʽ��
		{
			Speed_Arg.Kp = 20 * 0.001f;
			Speed_Arg.Ki = 44 * 0.001f;
            if(Speed.Rel > 2000)
                Speed_CalVal = 2000 + ((Speed.Rel - 2000) * 2);
            else
                Speed_CalVal = Speed.Rel;
			Speed.New = Speed_CalVal;//��¼��ǰ�ٶ�
            
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
            if(Speed.Rel > 2000)
                Speed_CalVal = 2000 + ((Speed.Rel - 2000) * 2);
            else
                Speed_CalVal = Speed.Rel;
            Speed.New = Speed_CalVal;//��¼��ǰ�ٶ�
            
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
			Speed_Arg.Kp = 5 * 0.001f;
			Speed_Arg.Ki = 10 * 0.001f;
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
    Display_Screen(Speed.Display_Set,Speed.Display_Rel,Time.Display_Set,Time.Display_Rel);
}
