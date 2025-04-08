#include "Show.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��

/**********�ֲ���������******/
uint8_t Temp_ShowFlag,Time_ShowFlag;//�¶ȡ�ʱ����ʾ�ı�־λ 0:���� 1��Ϩ��
uint8_t Run_TempDisplay;//�����¶���ʾ
uint8_t Protect_ShowFlag;//������ͼ��
uint8_t cnt=0;
uint8_t seg[16] = {0};

/**
 * @brief ��˸���
 *
 * @param dT ��������
 */
static void Check_ShowFlag(float dT)
{
    static float T;
    if(Twinkle_Time)
    {
        if (!sys.SetMode_Option) // ���û��������ѡ���У��򶼵���������˸
        {
            Temp_ShowFlag = 0;    // ����
            Time_ShowFlag = 0;    // ����
            Twinkle_Time = 0;     // ��˸��ʱ����
            return;
        }
        if (Twinkle_Time && !Key_Status) // ��˸��û�в�������ʱ
        {
            if (T == 0)
            {
                if (Twinkle_Time == 0)
                {
                    sys.SetMode_Option = 0; // ģʽѡ������
                    Temp_ShowFlag = 0;      // ����
                    Time_ShowFlag = 0;      // ����
                }
                else if (sys.SetMode_Option == 1)
                {
                    Temp_ShowFlag = ~Temp_ShowFlag; // �¶���˸
                    Time_ShowFlag = 0;              // ����
                }
                else if (sys.SetMode_Option == 2)
                {
                    Temp_ShowFlag = 0;              // ����
                    Time_ShowFlag = ~Time_ShowFlag; // ʱ����˸
                }
            }
            T += dT;
            if (T >= 0.5f)
            {
                Twinkle_Time -= 0.5f;
                if (Twinkle_Time <= 0)
                {
                    sys.SetMode_Option = 0;
                }
                T = 0;
            }
        }
        else
        {
            Temp_ShowFlag = 0;// ����
            Time_ShowFlag = 0;// ����
            T = 0;
        }
    }
}

/**
 * @brief ͼ����˸
 *
 * @param dT ��������
 */
void Icn_Twinkle(float dT)
{
    static float T;
    if (sys.Run_Status == 1) // �������������趨��ת�ٵ������
    {
        if (T == 0)
        {
            if(Temp.Ctrl > Temp_MIN)
                Temp.Icn = ~Temp.Icn;
            if(Time.Ctrl > Time_MIN)
                Time.Icn = ~Time.Icn;
        }
        T += dT;
        if (T >= 0.5f)
        {
            T = 0;
        }
    }
    else
    {
        Temp.Icn = 0;
        Time.Icn = 0;
        T = 0;
    }
}

/**
 * @brief �¶���ʾ
 *
 * @param dT ��������
 */
void TempDisplay(float dT)
{
    static float T;
    if ((sys.Run_Status == 1) && (Twinkle_Time == 0) && (Temp.ADDMode != 4))// �������������趨��ת�ٵ������
    {
        if (T == 0)
        {
            switch(Run_TempDisplay)
            {
                case 0:
                    Temp_ShowFlag = 1;
                    break;
                case 1:
                    Temp_ShowFlag = 0;
                    break;
                case 2:
                    Temp_ShowFlag = 1;
                    break;
                case 3:
                    Temp_ShowFlag = 0;
                    break;
                case 4:
                    Temp_ShowFlag = 1;
                    break;
                default:
                    Temp_ShowFlag = 0;
                    break;
            }
            Run_TempDisplay ++;
            if(Run_TempDisplay > 60)
                Run_TempDisplay = 0;
        }
        T += dT;
        if (T >= 0.5f)
        {
            T = 0;
        }
    }
    else
    {
        Run_TempDisplay = 0;
        T = 0;
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

/**
 * @brief ��˸����
 *
 * @param dT ��������
 */
void Twinkle(float dT)
{
    Check_ShowFlag(dT);
    Icn_Twinkle(dT);
    TempDisplay(dT);
    Protect_Twinkle(dT);//��������˸
}

/**
 * @brief λ������
 *
 * @param *bit �����λ��
 * @param num ����ڵ���
 * @param num1 ����ڵ���
 */
void bit_Cal(uint8_t bit,uint8_t num,uint8_t num1)
{
    seg[bit] &= (0xFF-num);seg[bit] |= num1;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Display_Screen(int16_t dis_temp,int32_t dis_time)
 * ��    �ܣ���ʾ��Ļ����
 * ��    ��: dis_temp����ʾ�¶ȣ�dis_time����ʾʱ��
 * ��    ����int16_t dis_temp,int32_t dis_time
*****************************************************************
*/
void Display_Screen(int16_t dis_temp,int32_t dis_time)
{   
    uint16_t Val;//���ڰ�ʮ��ȡ����������
    uint8_t SH,H,SM,M;//ʱ��ĵ�λȡֵ
    seg[cnt] = 0x00;
    if (!Temp_ShowFlag)
    {
        if(Temp.Set <= Temp_MIN)
        {
            Val = 11;//��ʾ��-��
        }
        else if(dis_temp > 999)//����999ʱ
        {
            Val=dis_temp/1000;//ȡ��ǧλ
            if(dis_temp > 9999)//����9999ʱ
                Val=Val%10;//ȡ��ǧλ
        }
        else if (dis_temp > -100) // ����-100ʱ
        {
            Val = 10;//����ʾ
        }
        else if (dis_temp > -1000) // ����-1000ʱ
        {
            Val = 11;//��ʾ��-��
        }
        switch(Val)
        {
            case 0:bit_Cal(0,0x01,0x01);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x00);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//����0
                break;
            case 1:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x00);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x00);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x00);
                    bit_Cal(7,0x01,0x00);//����1
                break;
            case 2:bit_Cal(0,0x01,0x01);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x00);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x00);
                    bit_Cal(7,0x01,0x01);//����2
                break;
            case 3:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x00);
                    bit_Cal(7,0x01,0x01);//����3
                break;	
            case 4:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x00);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x00);//����4
                break;	
            case 5:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x00);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//����5
                break;	
            case 6:bit_Cal(0,0x01,0x01);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x00);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//����6
                break;	
            case 7:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x00);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x00);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x00);
                    bit_Cal(7,0x01,0x01);//����7
                break;	
            case 8:bit_Cal(0,0x01,0x01);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//����8
                break;	
            case 9:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//����9
                break;
            case 10:  
                bit_Cal(0,0x01,0x00);
                bit_Cal(1,0x01,0x00);
                bit_Cal(3,0x01,0x00);
                bit_Cal(4,0x01,0x00);
                bit_Cal(5,0x01,0x00);
                bit_Cal(6,0x01,0x00);
                bit_Cal(7,0x01,0x00);//����ʾ
                break;
            case 11:  
                bit_Cal(0,0x01,0x00);
                bit_Cal(1,0x01,0x00);
                bit_Cal(3,0x01,0x00);
                bit_Cal(4,0x01,0x01);
                bit_Cal(5,0x01,0x00);
                bit_Cal(6,0x01,0x00);
                bit_Cal(7,0x01,0x00);//��ʾ��-��
                break;
            default:
                break;
        }			
        
        if(Temp.Set <= Temp_MIN)
        {
            Val = 11;//��ʾ��-��
        }
        else if(dis_temp > 99)//����99ʱ
        {
            Val=dis_temp/ 100 % 10;//ȡ����λ
        }
        else if (dis_temp >= 0) // ���ڵ���0ʱ
        {
            Val = 10;//����ʾ
        }
        else if (dis_temp > -100) // ����-100ʱ
        {
            Val = 11;//��ʾ��-��
        }
        else if (dis_temp > -1000) // ����-1000ʱ
        {
            Val=ABS(dis_temp)/ 100 % 10;//ȡ����λ
        }
        switch(Val)
        {
            case 0:bit_Cal(0,0x02,0x02);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x00);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//����0
                break;
            case 1:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x00);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x00);//����1
                break;
            case 2:bit_Cal(0,0x02,0x02);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x00);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x02);//����2
                break;
            case 3:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x02);//����3
                break;	
            case 4:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x00);//����4
                break;	
            case 5:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x00);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//����5
                break;	
            case 6:bit_Cal(0,0x02,0x02);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x00);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//����6
                break;	
            case 7:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x00);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x02);//����7
                break;	
            case 8:bit_Cal(0,0x02,0x02);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//����8
                break;	
            case 9:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//����9
                break;
                
            case 10:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x00);
                    bit_Cal(4,0x02,0x00);
                    bit_Cal(5,0x02,0x00);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x00);//����ʾ
                   break; 
            case 11:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x00);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x00);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x00);//��ʾ��-��
                   break; 
            default:
                break;
        }


        Val=ABS(dis_temp) / 10 % 10;//ȡ��ʮλ
        if(Temp.Set <= Temp_MIN)
        {
            Val = 11;//��ʾ��-��
        }
        switch(Val)
        {
            case 0:bit_Cal(0,0x04,0x04);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x00);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//����0
                break;
            case 1:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x00);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x00);//����1
                break;
            case 2:bit_Cal(0,0x04,0x04);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x00);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x04);//����2
                break;
            case 3:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x04);//����3
                break;	
            case 4:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x00);//����4
                break;	
            case 5:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x00);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//����5
                break;	
            case 6:bit_Cal(0,0x04,0x04);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x00);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//����6
                break;	
            case 7:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x00);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x04);//����7
                break;	
            case 8:bit_Cal(0,0x04,0x04);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//����8
                break;	
            case 9:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//����9
                break;
            case 10:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x00);
                    bit_Cal(4,0x04,0x00);
                    bit_Cal(5,0x04,0x00);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x00);//����ʾ
                   break; 
            case 11:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x00);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x00);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x00);//��ʾ��-��
                   break; 
            default:
                break;
        }			
        
        /***********dis_speed��λ***********/
        Val=ABS(dis_temp) % 10;//ȡ����λ
        if(Temp.Set <= Temp_MIN)
        {
            Val = 11;//��ʾ��-��
        }
        switch(Val)
        {
            case 0:bit_Cal(0,0x08,0x08);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x00);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//����0
                break;
            case 1:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x00);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x00);//����1
                break;
            case 2:bit_Cal(0,0x08,0x08);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x00);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x08);//����2
                break;
            case 3:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x08);//����3
                break;	
            case 4:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x00);//����4
                break;	
            case 5:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x00);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//����5
                break;	
            case 6:bit_Cal(0,0x08,0x08);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x00);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//����6
                break;	
            case 7:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x00);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x08);//����7
                break;	
            case 8:bit_Cal(0,0x08,0x08);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//����8
                break;	
            case 9:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//����9
                break;
            case 10:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x00);
                    bit_Cal(4,0x08,0x00);
                    bit_Cal(5,0x08,0x00);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x00);//����ʾ
                break;
            case 11:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x00);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x00);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x00);//��ʾ��-��
                break;
            default:
                break;
        }	
    }
    else
    {
        bit_Cal(0,0x0f,0x00);
        bit_Cal(1,0x0f,0x00);
        bit_Cal(3,0x0f,0x00);
        bit_Cal(4,0x0f,0x00);
        bit_Cal(5,0x0f,0x00);
        bit_Cal(6,0x0f,0x00);
        bit_Cal(7,0x0f,0x00);//4λ����ʾ
    }
    
    if(Temp.Icn == 0)
    {
        if(Temp.Set <= Temp_MIN)
        {
            bit_Cal(2,0x04,0x00);//����ʾ
        }
        else
        {
            bit_Cal(2,0x04,0x04);//�¶�С����
        }
    }
    else
    {
       bit_Cal(2,0x04,0x00);//����ʾ 
    }
    
    SH=dis_time/3600/10;//����ʮλ��λ��Сʱ��
    H=dis_time/3600%10;//�����λ��λ��Сʱ��
    SM=dis_time%3600/60/10;//����ʮ��λ��λ�ķ�����
    M=dis_time%3600/60%10;//�������λ��λ�ķ�����
    if(Time.Set <= 0)
    {
        SH = 10;
        H = 10;
        SM = 10;
        M = 10;
    }
    if (!Time_ShowFlag)
    {
        switch(SH)
        {
            case 0:bit_Cal(8,0x10,0x10);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x00);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//����0
                break;
            case 1:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x00);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x00);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x00);//����1
                break;
            case 2:bit_Cal(8,0x10,0x10);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x00);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x10);//����2
                break;
            case 3:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x10);//����3
                break;	
            case 4:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x00);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x00);//����4
                break;	
            case 5:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x00);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//����5
                break;	
            case 6:bit_Cal(8,0x10,0x10);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x00);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//����6
                break;	
            case 7:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x00);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x00);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x10);//����7
                break;	
            case 8:bit_Cal(8,0x10,0x10);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//����8
                break;	
            case 9:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//����9
                break;
            case 10:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x00);
                    bit_Cal(11,0x10,0x00);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x00);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x00);//��ʾ��-��
                break;
            default:
                break;
        }			

        switch(H)
        {
            case 0:bit_Cal(8,0x20,0x20);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x00);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//����0
                break;
            case 1:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x00);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x00);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x00);//����1
                break;
            case 2:bit_Cal(8,0x20,0x20);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x00);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x20);//����2
                break;
            case 3:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x20);//����3
                break;	
            case 4:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x00);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x00);//����4
                break;	
            case 5:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x00);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//����5
                break;	
            case 6:bit_Cal(8,0x20,0x20);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x00);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//����6
                break;	
            case 7:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x00);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x00);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x20);//����7
                break;	
            case 8:bit_Cal(8,0x20,0x20);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//����8
                break;	
            case 9:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//����9
                break;
            case 10:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x00);
                    bit_Cal(11,0x20,0x00);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x00);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x00);//��ʾ��-��
                break;
            default:
                break;
        }			
    
        switch(SM)
        {
            case 0:bit_Cal(8,0x40,0x40);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x00);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//����0
                break;
            case 1:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x00);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x00);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x00);//����1
                break;
            case 2:bit_Cal(8,0x40,0x40);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x00);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x40);//����2
                break;
            case 3:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x40);//����3
                break;	
            case 4:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x00);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x00);//����4
                break;	
            case 5:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x00);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//����5
                break;	
            case 6:bit_Cal(8,0x40,0x40);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x00);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//����6
                break;	
            case 7:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x00);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x00);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x40);//����7
                break;	
            case 8:bit_Cal(8,0x40,0x40);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//����8
                break;	
            case 9:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//����9
                break;
            case 10:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x00);
                    bit_Cal(11,0x40,0x00);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x00);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x00);//��ʾ��-��
                break;
            default:
                break;
        }			
        switch(M)
        {
            case 0:bit_Cal(8,0x80,0x80);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x00);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//����0
                break;
            case 1:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x00);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x00);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x00);//����1
                break;
            case 2:bit_Cal(8,0x80,0x80);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x00);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x80);//����2
                break;
            case 3:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x80);//����3
                break;	
            case 4:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x00);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x00);//����4
                break;	
            case 5:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x00);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//����5
                break;	
            case 6:bit_Cal(8,0x80,0x80);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x00);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//����6
                break;	
            case 7:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x00);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x00);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x80);//����7
                break;	
            case 8:bit_Cal(8,0x80,0x80);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//����8
                break;	
            case 9:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//����9
                break;
            case 10:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x00);
                    bit_Cal(11,0x80,0x00);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x00);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x00);//��ʾ��-��
                break;
            default:
                break;
        }
    }
    else
    {
        bit_Cal(8,0xf0,0x00);
        bit_Cal(9,0xf0,0x00);
        bit_Cal(11,0xf0,0x00);
        bit_Cal(12,0xf0,0x00);
        bit_Cal(13,0xf0,0x00);
        bit_Cal(14,0xf0,0x00);
        bit_Cal(15,0xf0,0x00);//����ʾ
    }
    
     if((sys.DownTime_Type == 0 &&Temp.ADDMode == 4)||(sys.DownTime_Type == 1))
     {
        if(Time.Icn == 0)
        {
            if(Time.Set <= Time_MIN)
            {
                bit_Cal(10,0x20,0x00);//����ʾ
            }
            else
            {
                bit_Cal(10,0x20,0x20);//ʱ��ð��
            }
        }
        else
        {
            bit_Cal(10,0x20,0x00);//����ʾ
        }
    }
     else
     {
         if(Time.Set <= Time_MIN)
            {
                bit_Cal(10,0x20,0x00);//����ʾ
            }
            else
            {
                bit_Cal(10,0x20,0x20);//ʱ��ð��
            }
     }
     
    if(Protect)
    {
        if(Protect_ShowFlag)
        {
            memset(seg, 0xFF, sizeof(seg));//�������   
        }
        else
        {
            memset(seg, 0, sizeof(seg));//�������   
        }
    }
    
	TM1640_Write_DATA(cnt, seg[cnt]);
	cnt ++;
	if(cnt >= 16)
		cnt= 0;
}

void DownTime_Display(void)
{
    seg[cnt] = 0x00;
    if(sys.DownTime_Type == C1)
    {
        bit_Cal(0,0x0C,0x04);
        bit_Cal(1,0x0C,0x04);
        bit_Cal(3,0x0C,0x08);
        bit_Cal(4,0x0C,0x00);
        bit_Cal(5,0x0C,0x08);
        bit_Cal(6,0x0C,0x04);
        bit_Cal(7,0x0C,0x04);//����C1
    }
    else
    {
        bit_Cal(0,0x0C,0x0C);
        bit_Cal(1,0x0C,0x0C);
        bit_Cal(3,0x0C,0x00);
        bit_Cal(4,0x0C,0x08);
        bit_Cal(5,0x0C,0x08);
        bit_Cal(6,0x0C,0x04);
        bit_Cal(7,0x0C,0x0C);//����C2
    }
    
    /*************��������***************/	
	TM1640_Write_DATA(cnt, seg[cnt]);
	cnt ++;
	if(cnt >= 16)
		cnt= 0;
}

/**
 * @brief �¶���ʾ����
 *
 * @param dT ��������
 */
void Deal_Temp(float dT)
{
    static float T;
    if (sys.Run_Status == 0)
    {
        Temp.ADDMode = 0;
        Temp.Display_Rel = Temp.Rel;
    }
    else if (sys.Run_Status == 1)
    {
        if (Temp.ADDMode == 0)
        {
            if (Temp.Ctrl > Temp.Display_Rel)
            {
                Temp.ADDMode = 1; // �������ģʽ
            }
            else
            {
                Temp.ADDMode = 2; // ��������ģʽ
            }
        }
        else if (Temp.ADDMode == 1)
        {
            if (Temp.Rel > Temp.Display_Rel && Temp.Display_Rel <= Temp.Ctrl)
            {
                Temp.Display_Rel++;
                T = 0;
            }
            if (Temp.Display_Rel >= Temp.Ctrl - 20)
            {
                Temp.ADDMode = 3;
                return;
            }
        }
        else if (Temp.ADDMode == 2)
        {
            if (Temp.Rel < Temp.Display_Rel && Temp.Display_Rel >= Temp.Ctrl)
            {
                Temp.Display_Rel--;
                T = 0;
            }
            if (Temp.Display_Rel <= Temp.Ctrl + 20)
            {
                Temp.ADDMode = 3;
                return;
            }
        }
        else if (Temp.ADDMode == 3)
        {
            T += dT;
            if (Temp.Display_Rel < Temp.Ctrl)
            {
                if (T >= 2.0f)
                {
                    Temp.Display_Rel += 1;
                    T = 0;
                }
            }
            else if (Temp.Display_Rel > Temp.Ctrl)
            {
                if (T >= 2.0f)
                {
                    Temp.Display_Rel -= 1;
                    T = 0;
                }
            }
            else
            {
                Temp.ADDMode = 4;
                Temp_ShowFlag = 0;//������˸ʱ�����������ںڵ���ʱ��
                T = 0;
            }
        }
        else if (Temp.ADDMode == 4)
        {
            Temp.Display_Rel = Temp.Ctrl;
        }
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
    if(sys.Run_Status)
    {
        if(Twinkle_Time == 0)
        {
            if(Temp.ADDMode == 4)
            {
                Temp.Display = Temp.Display_Rel;
            }
            else
            {
                if(Run_TempDisplay > 4)
                    Temp.Display = Temp.Display_Rel;
                else
                    Temp.Display = Temp.Ctrl;
            }
        }
        else
        {
            Temp.Display = Temp.Set;
            Time.Display = Time.Set;
        }
        Time.Display = Time.Rel+59;
    }
    else
    {
        if(Twinkle_Time == 0)
        {
            Temp.Display = Temp.Display_Rel;
            Time.Display = Time.Set;
        }
        else
        {
            Temp.Display = Temp.Set;
            Time.Display = Time.Set;
        }
    }
    if(sys.DownTime_Mode)
    {
        DownTime_Display();
    }
    else
    {
        Display_Screen(Temp.Display,Time.Display);
    }
}
