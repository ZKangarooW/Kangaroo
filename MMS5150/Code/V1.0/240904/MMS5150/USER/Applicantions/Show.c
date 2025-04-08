#include "Show.h"

/**********ȫ�ֱ���**********/
float Twinkle_Time; // ��˸ʱ��

/**********�ֲ���������*******/
uint8_t Speed_ShowFlag, Time_ShowFlag, Sync_ShowFlag;//�ٶȡ��¶ȡ�ʱ����ʾ�ı�־λ��0��������1��Ϩ��

static void Check_Sync(float dT)
{
    static float T;
    T += dT;
    if(T >= 0.5f)
    {
        if(sys.Sync)//����ȫ������
            Sync_ShowFlag = ~Sync_ShowFlag;//ѡ�й�λ����˸
        T = 0;
    } 
}

static void Check_ShowFlag(float dT)
{
    static float T;
    
    if(sys.SetMode_Option == 0 && Twinkle_Time==0)//���û������ѡ���У��򶼵���������˸
    {
        Speed_ShowFlag = 0;//����
        Time_ShowFlag = 0;//����
        T = 0;
        return;
    }
    if(Twinkle_Time && EC11A[1].EC11A_Knob<=0)//��˸��û�в�����ťʱ
    {
        if(T == 0)
        {
            Twinkle_Time -= 0.5f;//��˸��ʱ
            if(sys.SetMode_Option == 0)//�����ٶ�
            {
                Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
                Time_ShowFlag = 0;//ʱ�䳣��
            }
            else if(sys.SetMode_Option == 1)//�����ٶ�
            {
                Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
                Time_ShowFlag = 0;//ʱ�䳣��
            }
            if(sys.SetMode_Option == 2)//����ʱ��
            {
                Speed_ShowFlag = 0;//�ٶȳ���
                Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
            }
            if(Twinkle_Time == 0)//�����˸����
            {
                sys.SetMode_Option = 0;//ģʽѡ������
            }
        }
        T += dT;
        if(T >= 0.5f)
        {
            T = 0;
        }            
    }
    else
        T = 0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Icn_Twinkle(float dT)
 * ��    �ܣ�ͼ����˸
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T[15];
    for(uint8_t i = 0;i<15;i++)
    {
        if(Work_Num[i].Run_Status)		
        {
            T[i] += dT;
            if(T[i] >= 0.5f)
            {
                if(Work_Num[i].Speed.Set)
                {
                    Work_Num[i].Speed.IconStep ++;//�ٶ�ͼ����˸;
                    if(Work_Num[i].Speed.IconStep > 3)
                        Work_Num[i].Speed.IconStep = 1;
                }
                else
                   Work_Num[i].Speed.IconStep = 0;
                
                
                if(Work_Num[i].Time.Rel)
                    Work_Num[i].Time.Icon = ~Work_Num[i].Time.Icon;//��ʱͼ����˸;
                else
                {
                    Work_Num[i].Time.Icon = 0;
                }
                T[i] = 0;
            }
		}
        else
        {
            Work_Num[i].Speed.IconStep = 0;//��ʾʱ��ͼ��
            Work_Num[i].Time.Icon = 0;//��ʾʱ��ͼ��
            T[i] = 0;
        }
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
    Check_Sync(dT);
}

uint8_t seg[46] = {0};
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

void Display(_Work_Num_ work_num[])
{
    uint8_t Val;// ���ڰ�ʮ��ȡ����������
    
    /***********��λ1**********/
    if (work_num[0].Speed.Display_Set > 999) // ����999ʱ
    {
        Val = work_num[0].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(0, 0x0C, 0x04);//��ʾ����1
        }
        else
        {
            bit_Cal(0, 0x0C, 0x0C);//��ʾ����0
        }
    }
    else
    {
         bit_Cal(0, 0x0C, 0x0C);//��ʾ����0
    }
    
    if (work_num[0].Speed.Display_Set > 99) // ����99ʱ
    {
        Val = work_num[0].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(1, 0x0F, 0x0F);bit_Cal(2, 0x07, 0x05);//��ʾ����0
            break;
        case 1:
            bit_Cal(1, 0x0F, 0x00);bit_Cal(2, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(1, 0x0F, 0x0D);bit_Cal(2, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(1, 0x0F, 0x09);bit_Cal(2, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(1, 0x0F, 0x02);bit_Cal(2, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(1, 0x0F, 0x0B);bit_Cal(2, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(1, 0x0F, 0x0F);bit_Cal(2, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(1, 0x0F, 0x01);bit_Cal(2, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(1, 0x0F, 0x0F);bit_Cal(2, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(1, 0x0F, 0x0B);bit_Cal(2, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(1, 0x0F, 0x0F);bit_Cal(2, 0x07, 0x05);//��ʾ����0
    }

    if (work_num[0].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[0].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(3, 0x0F, 0x0F);bit_Cal(4, 0x07, 0x05);//��ʾ����0
            break;
        case 1:
            bit_Cal(3, 0x0F, 0x00);bit_Cal(4, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(3, 0x0F, 0x0D);bit_Cal(4, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(3, 0x0F, 0x09);bit_Cal(4, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(3, 0x0F, 0x02);bit_Cal(4, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(3, 0x0F, 0x0B);bit_Cal(4, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(3, 0x0F, 0x0F);bit_Cal(4, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(3, 0x0F, 0x01);bit_Cal(4, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(3, 0x0F, 0x0F);bit_Cal(4, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(3, 0x0F, 0x0B);bit_Cal(4, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(3, 0x0F, 0x0F);bit_Cal(4, 0x07, 0x05);//��ʾ����0
    }

    //ʵ��ת�ٸ�λֻ����ʾ��
    bit_Cal(4, 0x08, 0x08);//��ʾ����0

    /***********��λ2**********/
    if (work_num[1].Speed.Display_Set > 999) // ����999ʱ
    {
        Val = work_num[1].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(5, 0x0C, 0x04);//��ʾ����1
        }
        else
        {
            bit_Cal(5, 0x0C, 0x0C);//��ʾ����0
        }
    }
    else
    {
         bit_Cal(5, 0x0C, 0x0C);//��ʾ����0
    }
    
    if (work_num[1].Speed.Display_Set > 99) // ����99ʱ
    {
        Val = work_num[1].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x05);//��ʾ����0
            break;
        case 1:
            bit_Cal(6, 0x0F, 0x00);bit_Cal(7, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(6, 0x0F, 0x0D);bit_Cal(7, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(6, 0x0F, 0x09);bit_Cal(7, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(6, 0x0F, 0x02);bit_Cal(7, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(6, 0x0F, 0x0B);bit_Cal(7, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(6, 0x0F, 0x01);bit_Cal(7, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(6, 0x0F, 0x0B);bit_Cal(7, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x05);//��ʾ����0
    }

    if (work_num[1].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[1].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(8, 0x0F, 0x0F);bit_Cal(9, 0x07, 0x05);//��ʾ����0
            break;
        case 1:
            bit_Cal(8, 0x0F, 0x00);bit_Cal(9, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(8, 0x0F, 0x0D);bit_Cal(9, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(8, 0x0F, 0x09);bit_Cal(9, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(8, 0x0F, 0x02);bit_Cal(9, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(8, 0x0F, 0x0B);bit_Cal(9, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(8, 0x0F, 0x0F);bit_Cal(9, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(8, 0x0F, 0x01);bit_Cal(9, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(8, 0x0F, 0x0F);bit_Cal(9, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(8, 0x0F, 0x0B);bit_Cal(9, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(8, 0x0F, 0x0F);bit_Cal(9, 0x07, 0x05);//��ʾ����0
    }
    //ʵ��ת�ٸ�λֻ����ʾ��
    bit_Cal(9, 0x08, 0x08);//��ʾ����0

    /***********��λ3**********/
    if (work_num[2].Speed.Display_Set > 999) // ����999ʱ
    {
        Val = work_num[2].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(10, 0x0C, 0x04);//��ʾ����1
        }
        else
        {
            bit_Cal(10, 0x0C, 0x0C);//��ʾ����0
        }
    }
    else
    {
         bit_Cal(10, 0x0C, 0x0C);//��ʾ����0
    }
    
    if (work_num[2].Speed.Display_Set > 99) // ����99ʱ
    {
        Val = work_num[2].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x07, 0x05);//��ʾ����0
            break;
        case 1:
            bit_Cal(11, 0x0F, 0x00);bit_Cal(12, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(11, 0x0F, 0x0D);bit_Cal(12, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(11, 0x0F, 0x09);bit_Cal(12, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(11, 0x0F, 0x02);bit_Cal(12, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(11, 0x0F, 0x0B);bit_Cal(12, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(11, 0x0F, 0x01);bit_Cal(12, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(11, 0x0F, 0x0B);bit_Cal(12, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x07, 0x05);//��ʾ����0
    }

    if (work_num[2].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[2].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x07, 0x05);//��ʾ����0
            break;
        case 1:
            bit_Cal(13, 0x0F, 0x00);bit_Cal(14, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(13, 0x0F, 0x0D);bit_Cal(14, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(13, 0x0F, 0x09);bit_Cal(14, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(13, 0x0F, 0x02);bit_Cal(14, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(13, 0x0F, 0x0B);bit_Cal(14, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(13, 0x0F, 0x01);bit_Cal(14, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(13, 0x0F, 0x0B);bit_Cal(14, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x07, 0x05);//��ʾ����0
    }
    //ʵ��ת�ٸ�λֻ����ʾ��
    bit_Cal(14, 0x08, 0x08);//��ʾ����0

    /***********��λ4**********/
    if (work_num[3].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[3].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(0, 0x30, 0x20);//��ʾ����1
        }
        else
        {
            bit_Cal(0, 0x30, 0x30);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(0, 0x30, 0x30);//��ʾ����0
    }

    if (work_num[3].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[3].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(1, 0xF0, 0xF0);bit_Cal(2, 0x70, 0x50);//��ʾ����0
            break;
        case 1:
            bit_Cal(1, 0xF0, 0x00);bit_Cal(2, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(1, 0xF0, 0xD0);bit_Cal(2, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(1, 0xF0, 0x90);bit_Cal(2, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(1, 0xF0, 0x20);bit_Cal(2, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(1, 0xF0, 0xB0);bit_Cal(2, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(1, 0xF0, 0xF0);bit_Cal(2, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(1, 0xF0, 0x10);bit_Cal(2, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(1, 0xF0, 0xF0);bit_Cal(2, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(1, 0xF0, 0xB0);bit_Cal(2, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(1, 0xF0, 0xF0);bit_Cal(2, 0x70, 0x50);//��ʾ����0
    }

    if (work_num[3].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[3].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x70, 0x50);//��ʾ����0
            break;
        case 1:
            bit_Cal(3, 0xF0, 0x00);bit_Cal(4, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(3, 0xF0, 0xD0);bit_Cal(4, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(3, 0xF0, 0x90);bit_Cal(4, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(3, 0xF0, 0x20);bit_Cal(4, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(3, 0xF0, 0x10);bit_Cal(4, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x70, 0x50);//��ʾ����0
    }

    //ʵ��ת�ٸ�λֻ����ʾ��
    bit_Cal(5, 0x40, 0x40);//��ʾ����0

    /***********��λ5**********/
    if (work_num[4].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[4].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(5, 0x30, 0x10);//��ʾ����1
        }
        else
        {
            bit_Cal(5, 0x30, 0x30);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(5, 0x30, 0x30);//��ʾ����0
    }

    if (work_num[4].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[4].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x50);//��ʾ����0
            break;
        case 1:
            bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(6, 0xF0, 0xD0);bit_Cal(7, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(6, 0xF0, 0x90);bit_Cal(7, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(6, 0xF0, 0x20);bit_Cal(7, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(6, 0xF0, 0x10);bit_Cal(7, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x50);//��ʾ����0
    }

    if (work_num[4].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[4].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x70, 0x50);//��ʾ����0
            break;
        case 1:
            bit_Cal(8, 0xF0, 0x00);bit_Cal(9, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(8, 0xF0, 0xD0);bit_Cal(9, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(8, 0xF0, 0x90);bit_Cal(9, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(8, 0xF0, 0x20);bit_Cal(9, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(8, 0xF0, 0xB0);bit_Cal(9, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(8, 0xF0, 0x10);bit_Cal(9, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(8, 0xF0, 0xB0);bit_Cal(9, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x70, 0x50);//��ʾ����0
    }

    //ʵ��ת�ٸ�λֻ����ʾ��
    bit_Cal(9, 0x80, 0x80);//��ʾ����0

    /***********��λ6**********/
    if (work_num[5].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[5].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(10, 0x30, 0x10);//��ʾ����1
        }
        else
        {
            bit_Cal(10, 0x30, 0x30);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(10, 0x30, 0x30);//��ʾ����0
    }

    if (work_num[5].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[5].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x50);//��ʾ����0
            break;
        case 1:
            bit_Cal(11, 0xF0, 0x00);bit_Cal(12, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(11, 0xF0, 0xD0);bit_Cal(12, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(11, 0xF0, 0x90);bit_Cal(12, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(11, 0xF0, 0x20);bit_Cal(12, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(11, 0xF0, 0xB0);bit_Cal(12, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(11, 0xF0, 0x10);bit_Cal(12, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(11, 0xF0, 0xB0);bit_Cal(12, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x50);//��ʾ����0
    }

    if (work_num[5].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[5].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x50);//��ʾ����0
            break;
        case 1:
            bit_Cal(13, 0xF0, 0x00);bit_Cal(14, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(13, 0xF0, 0xD0);bit_Cal(14, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(13, 0xF0, 0x90);bit_Cal(14, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(13, 0xF0, 0x20);bit_Cal(14, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(13, 0xF0, 0xB0);bit_Cal(14, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(13, 0xF0, 0x10);bit_Cal(14, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(13, 0xF0, 0xB0);bit_Cal(14, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x50);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(15, 0x40, 0x40);//��ʾ����0

    /***********��λ7**********/
    if (work_num[6].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[6].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(45, 0xC0, 0x80);//��ʾ����1
        }
        else
        {
            bit_Cal(45, 0xC0, 0xC0);//��ʾ����0
        }
    }
    else
    {
         bit_Cal(45, 0xC0, 0xC0);//��ʾ����0
    }

    if (work_num[6].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[6].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(0, 0x83, 0x81);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x01);
            break;
        case 1:
            bit_Cal(0, 0x83, 0x01);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x00);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x00);
            break;
        case 2:
            bit_Cal(0, 0x83, 0x82);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x00);
            break;
        case 3:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x00);
            break;
        case 4:
            bit_Cal(0, 0x83, 0x03);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x00);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x01);
            break;
        case 5:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x00);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x01);
            break;
        case 6:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x00);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x01);
            break;
        case 7:
            bit_Cal(0, 0x83, 0x81);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x00);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x00);
            break;
        case 8:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x01);
            break;
        case 9:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x01);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(0, 0x83, 0x81);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x01);//��ʾ����0
    }

     if (work_num[6].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[6].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x81);bit_Cal(10, 0x83, 0x83);
            break;
        case 1:
            bit_Cal(4, 0x80, 0x00);bit_Cal(5, 0x83, 0x00);bit_Cal(10, 0x83, 0x82);
            break;
        case 2:
            bit_Cal(4, 0x80, 0x00);bit_Cal(5, 0x83, 0x83);bit_Cal(10, 0x83, 0x81);
            break;
        case 3:
            bit_Cal(4, 0x80, 0x00);bit_Cal(5, 0x83, 0x82);bit_Cal(10, 0x83, 0x83);
            break;
        case 4:
           bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x02);bit_Cal(10, 0x83, 0x82);
            break;
        case 5:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x82);bit_Cal(10, 0x83, 0x03);
            break;
        case 6:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x83);bit_Cal(10, 0x83, 0x03);
            break;
        case 7:
            bit_Cal(4, 0x80, 0x00);bit_Cal(5, 0x83, 0x80);bit_Cal(10, 0x83, 0x82);
            break;
        case 8:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x83);bit_Cal(10, 0x83, 0x83);
            break;
        case 9:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x82);bit_Cal(10, 0x83, 0x83);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x81);bit_Cal(10, 0x83, 0x83);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(12, 0x80, 0x80);//��ʾ����0

    /***********��λ8**********/
    if (work_num[7].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[7].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(14, 0x80, 0x00);bit_Cal(15, 0x80, 0x80);//��ʾ����1
        }
        else
        {
            bit_Cal(14, 0x80, 0x80);bit_Cal(15, 0x80, 0x80);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(14, 0x80, 0x80);bit_Cal(15, 0x80, 0x80);//��ʾ����0
    }

    if (work_num[7].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[7].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(20, 0xF0, 0xF0);bit_Cal(21, 0x70, 0x50);//��ʾ����0
            break;
        case 1:
            bit_Cal(20, 0xF0, 0x00);bit_Cal(21, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(20, 0xF0, 0xD0);bit_Cal(21, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(20, 0xF0, 0x90);bit_Cal(21, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(20, 0xF0, 0x20);bit_Cal(21, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(20, 0xF0, 0xB0);bit_Cal(21, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(20, 0xF0, 0xF0);bit_Cal(21, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(20, 0xF0, 0x10);bit_Cal(21, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(20, 0xF0, 0xF0);bit_Cal(21, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(20, 0xF0, 0xB0);bit_Cal(21, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(20, 0xF0, 0xF0);bit_Cal(21, 0x70, 0x50);//��ʾ����0
    }

    if (work_num[7].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[7].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(22, 0xF0, 0xF0);bit_Cal(23, 0x70, 0x50);//��ʾ����0
            break;
        case 1:
            bit_Cal(22, 0xF0, 0x00);bit_Cal(23, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(22, 0xF0, 0xD0);bit_Cal(23, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(22, 0xF0, 0x90);bit_Cal(23, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(22, 0xF0, 0x20);bit_Cal(23, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(22, 0xF0, 0xB0);bit_Cal(23, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(22, 0xF0, 0xF0);bit_Cal(23, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(22, 0xF0, 0x10);bit_Cal(23, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(22, 0xF0, 0xF0);bit_Cal(23, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(22, 0xF0, 0xB0);bit_Cal(23, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(22, 0xF0, 0xF0);bit_Cal(23, 0x70, 0x50);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(23, 0x80, 0x80);//��ʾ����0

    /***********��λ9**********/
    if (work_num[8].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[8].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(24, 0x80, 0x80);bit_Cal(26, 0x80, 0x00);//��ʾ����1
        }
        else
        {
            bit_Cal(24, 0x80, 0x80);bit_Cal(26, 0x80, 0x80);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(24, 0x80, 0x80);bit_Cal(26, 0x80, 0x80);//��ʾ����0
    }

    if (work_num[8].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[8].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(22, 0x0E, 0x0C);bit_Cal(23, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(22, 0x0E, 0x06);bit_Cal(23, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x0F);//��ʾ����0
    }

    if (work_num[8].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[8].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(20, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(20, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(20, 0x0E, 0x0C);bit_Cal(21, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(20, 0x0E, 0x06);bit_Cal(21, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(20, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(20, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x0F);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(20, 0x01, 0x01);//��ʾ����0

    /***********��λ10**********/
    if (work_num[9].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[9].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(45, 0x30, 0x20);//��ʾ����1
        }
        else
        {
            bit_Cal(45, 0x30, 0x30);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(45, 0x30, 0x30);//��ʾ����0
    }

    if (work_num[9].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[9].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(43, 0xE0, 0xA0);bit_Cal(44, 0xF0, 0xF0);//��ʾ����0
            break;
        case 1:
            bit_Cal(43, 0xE0, 0xA0);bit_Cal(44, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(43, 0xE0, 0xC0);bit_Cal(44, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(43, 0xE0, 0xE0);bit_Cal(44, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(43, 0xE0, 0xE0);bit_Cal(44, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(43, 0xE0, 0x60);bit_Cal(44, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(43, 0xE0, 0x60);bit_Cal(44, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(43, 0xE0, 0xA0);bit_Cal(44, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(43, 0xE0, 0xE0);bit_Cal(44, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(43, 0xE0, 0xE0);bit_Cal(44, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(43, 0xE0, 0xA0);bit_Cal(44, 0xF0, 0xF0);//��ʾ����0
    }

    if (work_num[9].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[9].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(41, 0xE0, 0xA0);bit_Cal(42, 0xF0, 0xF0);//��ʾ����0
            break;
        case 1:
            bit_Cal(41, 0xE0, 0xA0);bit_Cal(42, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(41, 0xE0, 0xC0);bit_Cal(42, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(41, 0xE0, 0xE0);bit_Cal(42, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(41, 0xE0, 0xE0);bit_Cal(42, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(41, 0xE0, 0x60);bit_Cal(42, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(41, 0xE0, 0x60);bit_Cal(42, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(41, 0xE0, 0xA0);bit_Cal(42, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(41, 0xE0, 0xE0);bit_Cal(42, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(41, 0xE0, 0xE0);bit_Cal(42, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(41, 0xE0, 0xA0);bit_Cal(42, 0xF0, 0xF0);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(41, 0x10, 0x10);//��ʾ����0

    /***********��λ11**********/
    if (work_num[10].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[10].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(37, 0x80, 0x00);bit_Cal(39, 0x80, 0x80);//��ʾ����1
        }
        else
        {
            bit_Cal(37, 0x80, 0x80);bit_Cal(39, 0x80, 0x80);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(37, 0x80, 0x80);bit_Cal(39, 0x80, 0x80);//��ʾ����0
    }

    if (work_num[10].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[10].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0xF0);//��ʾ����0
            break;
        case 1:
            bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(39, 0x70, 0x60);bit_Cal(40, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(39, 0x70, 0x30);bit_Cal(40, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(39, 0x70, 0x30);bit_Cal(40, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0xF0);//��ʾ����0
    }

    if (work_num[10].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[10].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0xF0);//��ʾ����0
            break;
        case 1:
            bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(37, 0x70, 0x60);bit_Cal(38, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(37, 0x70, 0x30);bit_Cal(38, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(37, 0x70, 0x30);bit_Cal(38, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0xF0);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(36, 0x10, 0x10);//��ʾ����0

    /***********��λ12**********/
    if (work_num[11].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[11].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(36, 0x60, 0x40);//��ʾ����1
        }
        else
        {
            bit_Cal(36, 0x60, 0x60);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(36, 0x60, 0x60);//��ʾ����0
    }

    if (work_num[11].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[11].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(34, 0xE0, 0xA0);bit_Cal(35, 0xF0, 0xF0);//��ʾ����0
            break;
        case 1:
            bit_Cal(34, 0xE0, 0xA0);bit_Cal(35, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(34, 0xE0, 0xC0);bit_Cal(35, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(34, 0xE0, 0xE0);bit_Cal(35, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(34, 0xE0, 0xE0);bit_Cal(35, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(34, 0xE0, 0x60);bit_Cal(35, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(34, 0xE0, 0x60);bit_Cal(35, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(34, 0xE0, 0xA0);bit_Cal(35, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(34, 0xE0, 0xE0);bit_Cal(35, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(34, 0xE0, 0xE0);bit_Cal(35, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(34, 0xE0, 0xA0);bit_Cal(35, 0xF0, 0xF0);//��ʾ����0
    }

    if (work_num[11].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[11].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(32, 0xE0, 0xA0);bit_Cal(33, 0xF0, 0xF0);//��ʾ����0
            break;
        case 1:
            bit_Cal(32, 0xE0, 0xA0);bit_Cal(33, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(32, 0xE0, 0xC0);bit_Cal(33, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(32, 0xE0, 0xE0);bit_Cal(33, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(32, 0xE0, 0xE0);bit_Cal(33, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(32, 0xE0, 0x60);bit_Cal(33, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(32, 0xE0, 0x60);bit_Cal(33, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(32, 0xE0, 0xA0);bit_Cal(33, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(32, 0xE0, 0xE0);bit_Cal(33, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(32, 0xE0, 0xE0);bit_Cal(33, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(32, 0xE0, 0xA0);bit_Cal(33, 0xF0, 0xF0);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(32, 0x10, 0x10);//��ʾ����0

    /***********��λ13**********/
    if (work_num[12].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[12].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(45, 0x0C, 0x08);//��ʾ����1
        }
        else
        {
            bit_Cal(45, 0x0C, 0x0C);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(45, 0x0C, 0x0C);//��ʾ����0
    }

    if (work_num[12].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[12].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(43, 0x0E, 0x0C);bit_Cal(44, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(43, 0x0E, 0x06);bit_Cal(44, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x0F);//��ʾ����0
    }

    if (work_num[12].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[12].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(41, 0x0E, 0x0C);bit_Cal(42, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(41, 0x0E, 0x06);bit_Cal(42, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x0F);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(41, 0x01, 0x01);//��ʾ����0

    /***********��λ14**********/
    if (work_num[13].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[13].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(45, 0x03, 0x02);//��ʾ����1
        }
        else
        {
            bit_Cal(45, 0x03, 0x03);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(45, 0x03, 0x03);//��ʾ����0
    }

    if (work_num[13].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[13].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(39, 0x07, 0x05);bit_Cal(40, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(39, 0x07, 0x05);bit_Cal(40, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(39, 0x07, 0x06);bit_Cal(40, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(39, 0x07, 0x07);bit_Cal(40, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(39, 0x07, 0x07);bit_Cal(40, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(39, 0x07, 0x03);bit_Cal(40, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(39, 0x07, 0x03);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 7:
            bit_Cal(39, 0x07, 0x05);bit_Cal(40, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(39, 0x07, 0x07);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(39, 0x07, 0x07);bit_Cal(40, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(39, 0x07, 0x05);bit_Cal(40, 0x0F, 0x0F);//��ʾ����0
    }

    if (work_num[13].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[13].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(37, 0x0E, 0x0C);bit_Cal(38, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(37, 0x0E, 0x06);bit_Cal(38, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(37, 0x0E, 0x06);bit_Cal(38, 0x0F, 0x0F);
            break;
        case 7:
            bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x0F);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(36, 0x02, 0x02);//��ʾ����0

    /***********��λ15**********/
    if (work_num[14].Speed.Display_Set > 999)//����999ʱ
    {
        Val = work_num[14].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(36, 0x0C, 0x08);//��ʾ����1
        }
        else
        {
            bit_Cal(36, 0x0C, 0x0C);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(36, 0x0C, 0x0C);//��ʾ����0
    }

    if (work_num[14].Speed.Display_Set > 99)//����99ʱ
    {
        Val = work_num[14].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(34, 0x0E, 0x0A);bit_Cal(35, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(34, 0x0E, 0x0A);bit_Cal(35, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(34, 0x0E, 0x0C);bit_Cal(35, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(34, 0x0E, 0x0E);bit_Cal(35, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(34, 0x0E, 0x0E);bit_Cal(35, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(34, 0x0E, 0x06);bit_Cal(35, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(34, 0x0E, 0x06);bit_Cal(35, 0x0F, 0x0F);
            break;
        case 7:
            bit_Cal(34, 0x0E, 0x0A);bit_Cal(35, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(34, 0x0E, 0x0E);bit_Cal(35, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(34, 0x0E, 0x0E);bit_Cal(35, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(34, 0x0E, 0x0A);bit_Cal(35, 0x0F, 0x0F);//��ʾ����0
    }

    if (work_num[14].Speed.Display_Set > 9) // ����9ʱ
    {
        Val = work_num[14].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(32, 0x0E, 0x0A);bit_Cal(33, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(32, 0x0E, 0x0A);bit_Cal(33, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(32, 0x0E, 0x0C);bit_Cal(33, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(32, 0x0E, 0x0E);bit_Cal(33, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(32, 0x0E, 0x0E);bit_Cal(33, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(32, 0x0E, 0x06);bit_Cal(33, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(32, 0x0E, 0x06);bit_Cal(33, 0x0F, 0x0F);
            break;
        case 7:
            bit_Cal(32, 0x0E, 0x0A);bit_Cal(33, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(32, 0x0E, 0x0E);bit_Cal(33, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(32, 0x0E, 0x0E);bit_Cal(33, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(32, 0x0E, 0x0A);bit_Cal(33, 0x0F, 0x0F);//��ʾ����0
    }

    //ת�ٸ�λֻ����ʾ��
    bit_Cal(32, 0x01, 0x01);//��ʾ����0

    /****************************************�趨����****************************************/
    /***********ʵ��ת��**********/
    if (work_num[sys.New_Work].Speed.Display_Rel > 999)//����999ʱ
    {
        Val = work_num[sys.New_Work].Speed.Display_Rel / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(15, 0x03, 0x01);//��ʾ����1
        }
        else
        {
            bit_Cal(15, 0x03, 0x03);//��ʾ����0
        }
    }
    else
    {
        bit_Cal(15, 0x03, 0x03);//��ʾ����0
    }

    if (work_num[sys.New_Work].Speed.Display_Rel > 99)//����99ʱ
    {
        Val = work_num[sys.New_Work].Speed.Display_Rel / 100 % 10;
         switch (Val)
        {
        case 0:
            bit_Cal(16, 0x07, 0x05);bit_Cal(17, 0x0F, 0x0F);//��ʾ����0
            break;
        case 1:
            bit_Cal(16, 0x07, 0x00);bit_Cal(17, 0x0F, 0x06);
            break;
        case 2:
            bit_Cal(16, 0x07, 0x06);bit_Cal(17, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(16, 0x07, 0x02);bit_Cal(17, 0x0F, 0x0F);
            break;
        case 4:
            bit_Cal(16, 0x07, 0x03);bit_Cal(17, 0x0F, 0x06);
            break;
        case 5:
            bit_Cal(16, 0x07, 0x03);bit_Cal(17, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(16, 0x07, 0x07);bit_Cal(17, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(16, 0x07, 0x00);bit_Cal(17, 0x0F, 0x07);
            break;
        case 8:
            bit_Cal(16, 0x07, 0x07);bit_Cal(17, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(16, 0x07, 0x03);bit_Cal(17, 0x0F, 0x0F);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(16, 0x07, 0x05);bit_Cal(17, 0x0F, 0x0F);//��ʾ����0
    }

    if (work_num[sys.New_Work].Speed.Display_Rel > 9) // ����9ʱ
    {
        Val = work_num[sys.New_Work].Speed.Display_Rel / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(18, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x05);//��ʾ����0
            break;
        case 1:
            bit_Cal(18, 0x0F, 0x00);bit_Cal(19, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(18, 0x0F, 0x0D);bit_Cal(19, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(18, 0x0F, 0x09);bit_Cal(19, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(18, 0x0F, 0x02);bit_Cal(19, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(18, 0x0F, 0x0B);bit_Cal(19, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(18, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(18, 0x0F, 0x01);bit_Cal(19, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(18, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(18, 0x0F, 0x0B);bit_Cal(19, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(18, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x05);//��ʾ����0
    }
    //ʵ��ת�ٸ�λֻ����ʾ��
    bit_Cal(19, 0x08, 0x08);//��ʾ����0

    /***********�趨ת��**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0)
    {
        bit_Cal(15, 0x30, 0x00);//����ʾ
        bit_Cal(16, 0xF0, 0x00);bit_Cal(17, 0x70, 0x00);//����ʾ
        bit_Cal(18, 0xF0, 0x00);bit_Cal(19, 0x70, 0x00);//����ʾ
        bit_Cal(19, 0x80, 0x00);//����ʾ
    }
    else
    {
        if(work_num[sys.New_Work].Speed.Display_Set == 0)//��ʾ�� -- ��
        {
            bit_Cal(15, 0x30, 0x00);//����ʾ
            bit_Cal(16, 0xF0, 0x00);bit_Cal(17, 0x70, 0x20);//��ʾ��-��
            bit_Cal(18, 0xF0, 0x00);bit_Cal(19, 0x70, 0x20);//��ʾ��-��
            bit_Cal(19, 0x80, 0x00);//����ʾ
        }
        else
        {
            if (work_num[sys.New_Work].Speed.Display_Set > 999)//����999ʱ
            {
                Val = work_num[sys.New_Work].Speed.Display_Set / 1000 % 10;
                if(Val > 0)
                {
                    bit_Cal(15, 0x30, 0x10);//��ʾ����1
                }
                else
                {
                    bit_Cal(15, 0x30, 0x30);//��ʾ����0
                }
            }
            else
            {
                bit_Cal(15, 0x30, 0x30);//��ʾ����0
            }

            if (work_num[sys.New_Work].Speed.Display_Set > 99)//����99ʱ
            {
                Val = work_num[sys.New_Work].Speed.Display_Set / 100 % 10;
                switch (Val)
                {
                case 0:
                    bit_Cal(16, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x50);//��ʾ����0
                    break;
                case 1:
                    bit_Cal(16, 0xF0, 0x00);bit_Cal(17, 0x70, 0x50);
                    break;
                case 2:
                    bit_Cal(16, 0xF0, 0xD0);bit_Cal(17, 0x70, 0x30);
                    break;
                case 3:
                    bit_Cal(16, 0xF0, 0x90);bit_Cal(17, 0x70, 0x70);
                    break;
                case 4:
                    bit_Cal(16, 0xF0, 0x20);bit_Cal(17, 0x70, 0x70);
                    break;
                case 5:
                    bit_Cal(16, 0xF0, 0xB0);bit_Cal(17, 0x70, 0x60);
                    break;
                case 6:
                    bit_Cal(16, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x60);
                    break;
                case 7:
                    bit_Cal(16, 0xF0, 0x10);bit_Cal(17, 0x70, 0x50);
                    break;
                case 8:
                    bit_Cal(16, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x70);
                    break;
                case 9:
                    bit_Cal(16, 0xF0, 0xB0);bit_Cal(17, 0x70, 0x70);
                    break;
                default:
                    break;
                }
            }
            else
            {
                 bit_Cal(16, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x50);//��ʾ����0
            }

            if (work_num[sys.New_Work].Speed.Display_Set > 9) // ����9ʱ
            {
                Val = work_num[sys.New_Work].Speed.Display_Set / 10 % 10;
                switch (Val)
                {
                case 0:
                    bit_Cal(18, 0xF0, 0xF0);bit_Cal(19, 0x70, 0x50);//��ʾ����0
                    break;
                case 1:
                    bit_Cal(18, 0xF0, 0x00);bit_Cal(19, 0x70, 0x50);
                    break;
                case 2:
                    bit_Cal(18, 0xF0, 0xD0);bit_Cal(19, 0x70, 0x30);
                    break;
                case 3:
                    bit_Cal(18, 0xF0, 0x90);bit_Cal(19, 0x70, 0x70);
                    break;
                case 4:
                    bit_Cal(18, 0xF0, 0x20);bit_Cal(19, 0x70, 0x70);
                    break;
                case 5:
                    bit_Cal(18, 0xF0, 0xB0);bit_Cal(19, 0x70, 0x60);
                    break;
                case 6:
                    bit_Cal(18, 0xF0, 0xF0);bit_Cal(19, 0x70, 0x60);
                    break;
                case 7:
                    bit_Cal(18, 0xF0, 0x10);bit_Cal(19, 0x70, 0x50);
                    break;
                case 8:
                    bit_Cal(18, 0xF0, 0xF0);bit_Cal(19, 0x70, 0x70);
                    break;
                case 9:
                    bit_Cal(18, 0xF0, 0xB0);bit_Cal(19, 0x70, 0x70);
                    break;
                default:
                    break;
                }
            }
            else
            {
                 bit_Cal(18, 0xF0, 0xF0);bit_Cal(19, 0x70, 0x50);//��ʾ����0
            }

            bit_Cal(19, 0x80, 0x80);//��ʾ����0
        }
    }

    /***********ʵ��ʱ��**********/
    Val = work_num[sys.New_Work].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
    case 0:
        bit_Cal(30, 0x70, 0x50);bit_Cal(31, 0xF0, 0xF0);//��ʾ����0
        break;
    case 1:
        bit_Cal(30, 0x70, 0x50);bit_Cal(31, 0xF0, 0x00);
        break;
    case 2:
        bit_Cal(30, 0x70, 0x60);bit_Cal(31, 0xF0, 0xB0);
        break;
    case 3:
        bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0xF0, 0x90);
        break;
    case 4:
        bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0xF0, 0x40);
        break;
    case 5:
        bit_Cal(30, 0x70, 0x30);bit_Cal(31, 0xF0, 0xD0);
        break;
    case 6:
        bit_Cal(30, 0x70, 0x30);bit_Cal(31, 0xF0, 0xF0);
        break;
    case 7:
        bit_Cal(30, 0x70, 0x50);bit_Cal(31, 0xF0, 0x80);
        break;
    case 8:
        bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0xF0, 0xF0);
        break;
    case 9:
        bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0xF0, 0xD0);
        break;
    default:
        break;
    }


    Val = work_num[sys.New_Work].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
    case 0:
        bit_Cal(28, 0x70, 0x50);bit_Cal(29, 0xF0, 0xF0);//��ʾ����0
        break;
    case 1:
        bit_Cal(28, 0x70, 0x50);bit_Cal(29, 0xF0, 0x00);
        break;
    case 2:
        bit_Cal(28, 0x70, 0x60);bit_Cal(29, 0xF0, 0xB0);
        break;
    case 3:
        bit_Cal(28, 0x70, 0x70);bit_Cal(29, 0xF0, 0x90);
        break;
    case 4:
        bit_Cal(28, 0x70, 0x70);bit_Cal(29, 0xF0, 0x40);
        break;
    case 5:
        bit_Cal(28, 0x70, 0x30);bit_Cal(29, 0xF0, 0xD0);
        break;
    case 6:
        bit_Cal(28, 0x70, 0x30);bit_Cal(29, 0xF0, 0xF0);
        break;
    case 7:
        bit_Cal(28, 0x70, 0x50);bit_Cal(29, 0xF0, 0x80);
        break;
    case 8:
        bit_Cal(28, 0x70, 0x70);bit_Cal(29, 0xF0, 0xF0);
        break;
    case 9:
        bit_Cal(28, 0x70, 0x70);bit_Cal(29, 0xF0, 0xD0);
        break;
    default:
        break;
    }

    Val = work_num[sys.New_Work].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
    case 0:
        bit_Cal(26, 0x70, 0x50);bit_Cal(27, 0xF0, 0xF0);//��ʾ����0
        break;
    case 1:
        bit_Cal(26, 0x70, 0x50);bit_Cal(27, 0xF0, 0x00);
        break;
    case 2:
        bit_Cal(26, 0x70, 0x60);bit_Cal(27, 0xF0, 0xB0);
        break;
    case 3:
        bit_Cal(26, 0x70, 0x70);bit_Cal(27, 0xF0, 0x90);
        break;
    case 4:
        bit_Cal(26, 0x70, 0x70);bit_Cal(27, 0xF0, 0x40);
        break;
    case 5:
        bit_Cal(26, 0x70, 0x30);bit_Cal(27, 0xF0, 0xD0);
        break;
    case 6:
        bit_Cal(26, 0x70, 0x30);bit_Cal(27, 0xF0, 0xF0);
        break;
    case 7:
        bit_Cal(26, 0x70, 0x50);bit_Cal(27, 0xF0, 0x80);
        break;
    case 8:
        bit_Cal(26, 0x70, 0x70);bit_Cal(27, 0xF0, 0xF0);
        break;
    case 9:
        bit_Cal(26, 0x70, 0x70);bit_Cal(27, 0xF0, 0xD0);
        break;
    default:
        break;
    } 

    Val = work_num[sys.New_Work].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
     switch (Val)
    {
    case 0:
        bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0xF0);//��ʾ����0
        break;
    case 1:
        bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0x00);
        break;
    case 2:
        bit_Cal(24, 0x70, 0x60);bit_Cal(25, 0xF0, 0xB0);
        break;
    case 3:
        bit_Cal(24, 0x70, 0x70);bit_Cal(25, 0xF0, 0x90);
        break;
    case 4:
        bit_Cal(24, 0x70, 0x70);bit_Cal(25, 0xF0, 0x40);
        break;
    case 5:
        bit_Cal(24, 0x70, 0x30);bit_Cal(25, 0xF0, 0xD0);
        break;
    case 6:
        bit_Cal(24, 0x70, 0x30);bit_Cal(25, 0xF0, 0xF0);
        break;
    case 7:
        bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0x80);
        break;
    case 8:
        bit_Cal(24, 0x70, 0x70);bit_Cal(25, 0xF0, 0xF0);
        break;
    case 9:
        bit_Cal(24, 0x70, 0x70);bit_Cal(25, 0xF0, 0xD0);
        break;
    default:
        break;
    }

    /***********�趨ʱ��**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0)//����ʾ�趨ת��
    {
        bit_Cal(30, 0x07, 0x00);bit_Cal(31, 0x0F, 0x00);//����ʾ
        bit_Cal(28, 0x0E, 0x00);bit_Cal(29, 0x0F, 0x00);//����ʾ
        bit_Cal(26, 0x0E, 0x00);bit_Cal(27, 0x0F, 0x00);//����ʾ
        bit_Cal(24, 0x0E, 0x00);bit_Cal(25, 0x0F, 0x00);//����ʾ
    }
    else
    {
        if(work_num[sys.New_Work].Time.Display_Set == 0)
        {
            bit_Cal(30, 0x07, 0x02);bit_Cal(31, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(28, 0x0E, 0x04);bit_Cal(29, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(26, 0x0E, 0x04);bit_Cal(27, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(24, 0x0E, 0x04);bit_Cal(25, 0x0F, 0x00);//��ʾ��-��
        }
        else
        {
            Val = work_num[sys.New_Work].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
            switch (Val)
            {
            case 0:
                bit_Cal(30, 0x07, 0x05);bit_Cal(31, 0x0F, 0x0F);//��ʾ����0
                break;
            case 1:
                bit_Cal(30, 0x07, 0x05);bit_Cal(31, 0x0F, 0x00);
                break;
            case 2:
                bit_Cal(30, 0x07, 0x06);bit_Cal(31, 0x0F, 0x0B);
                break;
            case 3:
                bit_Cal(30, 0x07, 0x07);bit_Cal(31, 0x0F, 0x09);
                break;
            case 4:
                bit_Cal(30, 0x07, 0x07);bit_Cal(31, 0x0F, 0x04);
                break;
            case 5:
                bit_Cal(30, 0x07, 0x03);bit_Cal(31, 0x0F, 0x0D);
                break;
            case 6:
                bit_Cal(30, 0x07, 0x03);bit_Cal(31, 0x0F, 0x0F);
                break;
            case 7:
                bit_Cal(30, 0x07, 0x05);bit_Cal(31, 0x0F, 0x08);
                break;
            case 8:
                bit_Cal(30, 0x07, 0x07);bit_Cal(31, 0x0F, 0x0F);
                break;
            case 9:
                bit_Cal(30, 0x07, 0x07);bit_Cal(31, 0x0F, 0x0D);
                break;
            default:
                break;
            }


            Val = work_num[sys.New_Work].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
            switch (Val)
            {
            case 0:
                bit_Cal(28, 0x0E, 0x0A);bit_Cal(29, 0x0F, 0x0F);//��ʾ����0
                break;
            case 1:
                bit_Cal(28, 0x0E, 0x0A);bit_Cal(29, 0x0F, 0x00);
                break;
            case 2:
                bit_Cal(28, 0x0E, 0x0C);bit_Cal(29, 0x0F, 0x0B);
                break;
            case 3:
                bit_Cal(28, 0x0E, 0x0E);bit_Cal(29, 0x0F, 0x09);
                break;
            case 4:
                bit_Cal(28, 0x0E, 0x0E);bit_Cal(29, 0x0F, 0x04);
                break;
            case 5:
                bit_Cal(28, 0x0E, 0x06);bit_Cal(29, 0x0F, 0x0D);
                break;
            case 6:
                bit_Cal(28, 0x0E, 0x06);bit_Cal(29, 0x0F, 0x0F);
                break;
            case 7:
                bit_Cal(28, 0x0E, 0x0A);bit_Cal(29, 0x0F, 0x08);
                break;
            case 8:
                bit_Cal(28, 0x0E, 0x0E);bit_Cal(29, 0x0F, 0x0F);
                break;
            case 9:
                bit_Cal(28, 0x0E, 0x0E);bit_Cal(29, 0x0F, 0x0D);
                break;
            default:
                break;
            }

            Val = work_num[sys.New_Work].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
            switch (Val)
            {
            case 0:
                bit_Cal(26, 0x0E, 0x0A);bit_Cal(27, 0x0F, 0x0F);//��ʾ����0
                break;
            case 1:
                bit_Cal(26, 0x0E, 0x0A);bit_Cal(27, 0x0F, 0x00);
                break;
            case 2:
                bit_Cal(26, 0x0E, 0x0C);bit_Cal(27, 0x0F, 0x0B);
                break;
            case 3:
                bit_Cal(26, 0x0E, 0x0E);bit_Cal(27, 0x0F, 0x09);
                break;
            case 4:
                bit_Cal(26, 0x0E, 0x0E);bit_Cal(27, 0x0F, 0x04);
                break;
            case 5:
                bit_Cal(26, 0x0E, 0x06);bit_Cal(27, 0x0F, 0x0D);
                break;
            case 6:
                bit_Cal(26, 0x0E, 0x06);bit_Cal(27, 0x0F, 0x0F);
                break;
            case 7:
                bit_Cal(26, 0x0E, 0x0A);bit_Cal(27, 0x0F, 0x08);
                break;
            case 8:
                bit_Cal(26, 0x0E, 0x0E);bit_Cal(27, 0x0F, 0x0F);
                break;
            case 9:
                bit_Cal(26, 0x0E, 0x0E);bit_Cal(27, 0x0F, 0x0D);
                break;
            default:
                break;
            }

            Val = work_num[sys.New_Work].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
            switch (Val)
            {
            case 0:
                bit_Cal(24, 0x0E, 0x0A);bit_Cal(25, 0x0F, 0x0F);//��ʾ����0
                break;
            case 1:
                bit_Cal(24, 0x0E, 0x0A);bit_Cal(25, 0x0F, 0x00);
                break;
            case 2:
                bit_Cal(24, 0x0E, 0x0C);bit_Cal(25, 0x0F, 0x0B);
                break;
            case 3:
                bit_Cal(24, 0x0E, 0x0E);bit_Cal(25, 0x0F, 0x09);
                break;
            case 4:
                bit_Cal(24, 0x0E, 0x0E);bit_Cal(25, 0x0F, 0x04);
                break;
            case 5:
                bit_Cal(24, 0x0E, 0x06);bit_Cal(25, 0x0F, 0x0D);
                break;
            case 6:
                bit_Cal(24, 0x0E, 0x06);bit_Cal(25, 0x0F, 0x0F);
                break;
            case 7:
                bit_Cal(24, 0x0E, 0x0A);bit_Cal(25, 0x0F, 0x08);
                break;
            case 8:
                bit_Cal(24, 0x0E, 0x0E);bit_Cal(25, 0x0F, 0x0F);
                break;
            case 9:
                bit_Cal(24, 0x0E, 0x0E);bit_Cal(25, 0x0F, 0x0D);
                break;
            default:
                break;
            }
        }
    }

    bit_Cal(2, 0x08, 0x00);//��ʾ��λ1���»���
    bit_Cal(7, 0x08, 0x00);//��ʾ��λ2���»���
    bit_Cal(12, 0x08, 0x00);//��ʾ��λ3���»���
    bit_Cal(0, 0x40, 0x00);//��ʾ��λ4���»���
    bit_Cal(7, 0x80, 0x00);//��ʾ��λ5���»���
    bit_Cal(10, 0x40, 0x00);//��ʾ��λ6���»���
    bit_Cal(36, 0x80, 0x00);//��ʾ��λ7���»���
    bit_Cal(21, 0x80, 0x00);//��ʾ��λ8���»���
    bit_Cal(22, 0x01, 0x00);//��ʾ��λ9���»���
    bit_Cal(43, 0x10, 0x00);//��ʾ��λ10���»���
    bit_Cal(39, 0x08, 0x00);//��ʾ��λ11���»���
    bit_Cal(34, 0x10, 0x00);//��ʾ��λ12���»���
    bit_Cal(43, 0x01, 0x00);//��ʾ��λ13���»���
    bit_Cal(37, 0x01, 0x00);//��ʾ��λ14���»���
    bit_Cal(34, 0x01, 0x00);//��ʾ��λ14���»���
    
    switch(sys.New_Work)
    {
        case 0:bit_Cal(2, 0x08, 0x08);//��ʾ��λ1���»���
            break;
        case 1:bit_Cal(7, 0x08, 0x08);//��ʾ��λ2���»���
            break;
        case 2:bit_Cal(12, 0x08, 0x08);//��ʾ��λ3���»���
            break;
        case 3:bit_Cal(0, 0x40, 0x40);//��ʾ��λ4���»���
            break;
        case 4:bit_Cal(7, 0x80, 0x80);//��ʾ��λ5���»���
            break;
        case 5:bit_Cal(10, 0x40, 0x40);//��ʾ��λ6���»���
            break;
        case 6:bit_Cal(36, 0x80, 0x80);//��ʾ��λ7���»���
            break;
        case 7:bit_Cal(21, 0x80, 0x80);//��ʾ��λ8���»���
            break;
        case 8:bit_Cal(22, 0x01, 0x01);//��ʾ��λ9���»���
            break;
        case 9:bit_Cal(43, 0x10, 0x10);//��ʾ��λ10���»���
            break;
        case 10:bit_Cal(39, 0x08, 0x08);//��ʾ��λ11���»���
            break;
        case 11:bit_Cal(34, 0x10, 0x10);//��ʾ��λ12���»���
            break;
        case 12:bit_Cal(43, 0x01, 0x01);//��ʾ��λ13���»���
            break;
        case 13:bit_Cal(37, 0x01, 0x01);//��ʾ��λ14���»���
            break;
        case 14:bit_Cal(34, 0x01, 0x01);//��ʾ��λ15���»���
            break;
    }
    
    if(sys.Sync == 1)   
    {
        bit_Cal(2, 0x08, 0x08);//��ʾ��λ1���»���
        bit_Cal(7, 0x08, 0x08);//��ʾ��λ2���»���
        bit_Cal(12, 0x08, 0x08);//��ʾ��λ3���»���
        bit_Cal(0, 0x40, 0x40);//��ʾ��λ4���»���
        bit_Cal(7, 0x80, 0x80);//��ʾ��λ5���»���
        bit_Cal(10, 0x40, 0x40);//��ʾ��λ6���»���
        bit_Cal(36, 0x80, 0x80);//��ʾ��λ7���»���
        bit_Cal(21, 0x80, 0x80);//��ʾ��λ8���»���
        bit_Cal(22, 0x01, 0x01);//��ʾ��λ9���»���
        bit_Cal(43, 0x10, 0x10);//��ʾ��λ10���»���
        bit_Cal(39, 0x08, 0x08);//��ʾ��λ11���»���
        bit_Cal(34, 0x10, 0x10);//��ʾ��λ12���»���
        bit_Cal(43, 0x01, 0x01);//��ʾ��λ13���»���
        bit_Cal(37, 0x01, 0x01);//��ʾ��λ14���»���
        bit_Cal(34, 0x01, 0x01);//��ʾ��λ14���»���
        if(Sync_ShowFlag)
        {
            switch(sys.New_Work)
            {
                case 0:bit_Cal(2, 0x08, 0x00);//��ʾ��λ1���»���
                    break;
                case 1:bit_Cal(7, 0x08, 0x00);//��ʾ��λ2���»���
                    break;
                case 2:bit_Cal(12, 0x08, 0x00);//��ʾ��λ3���»���
                    break;
                case 3:bit_Cal(0, 0x40, 0x00);//��ʾ��λ4���»���
                    break;
                case 4:bit_Cal(7, 0x80, 0x00);//��ʾ��λ5���»���
                    break;
                case 5:bit_Cal(10, 0x40, 0x00);//��ʾ��λ6���»���
                    break;
                case 6:bit_Cal(36, 0x80, 0x00);//��ʾ��λ7���»���
                    break;
                case 7:bit_Cal(21, 0x80, 0x00);//��ʾ��λ8���»���
                    break;
                case 8:bit_Cal(22, 0x01, 0x00);//��ʾ��λ9���»���
                    break;
                case 9:bit_Cal(43, 0x10, 0x00);//��ʾ��λ10���»���
                    break;
                case 10:bit_Cal(39, 0x08, 0x00);//��ʾ��λ11���»���
                    break;
                case 11:bit_Cal(34, 0x10, 0x00);//��ʾ��λ12���»���
                    break;
                case 12:bit_Cal(43, 0x01, 0x00);//��ʾ��λ13���»���
                    break;
                case 13:bit_Cal(37, 0x01, 0x00);//��ʾ��λ14���»���
                    break;
                case 14:bit_Cal(34, 0x01, 0x00);//��ʾ��λ15���»���
                    break;
            }
        }
    }
    
    /* 1�Ź�λת��ͼ�� */
    if(work_num[sys.New_Work].Speed.Display_Rel)
    {
        switch(Work_Num[0].Speed.IconStep)
        {
            case 0: bit_Cal(15, 0x04, 0x04);//��λת��ͼ��S48
                    bit_Cal(15, 0x08, 0x08);//��λת��ͼ��S49
                    bit_Cal(16, 0x08, 0x08);//��λת��ͼ��S50
                break;
            case 1: bit_Cal(15, 0x04, 0x00);//��λת��ͼ��S48
                    bit_Cal(15, 0x08, 0x08);//��λת��ͼ��S49
                    bit_Cal(16, 0x08, 0x08);//��λת��ͼ��S50
                break;
            case 2: bit_Cal(15, 0x04, 0x04);//��λת��ͼ��S48
                    bit_Cal(15, 0x08, 0x00);//��λת��ͼ��S49
                    bit_Cal(16, 0x08, 0x08);//��λת��ͼ��S50
                break;
            case 3: bit_Cal(15, 0x04, 0x04);//��λת��ͼ��S48
                    bit_Cal(15, 0x08, 0x08);//��λת��ͼ��S49
                    bit_Cal(16, 0x08, 0x00);//��λת��ͼ��S50
                break;
            default:
                break;
        }
    }
    else
    {
        bit_Cal(15, 0x04, 0x04);//��λת��ͼ��S48
        bit_Cal(15, 0x08, 0x08);//��λת��ͼ��S49
        bit_Cal(16, 0x08, 0x08);//��λת��ͼ��S50
    }
    
    /**********rpmͼ��**********/
    bit_Cal(17, 0x80, 0x80);

    
    /* 1�Ź�λʱ��ͼ�� */
    if(Work_Num[sys.New_Work].Time.Icon == 0)
    {
        bit_Cal(30, 0x08, 0x08);//��λʱ��ͼ��
    }
    else
    {
        bit_Cal(30, 0x08, 0x00);//��λʱ��ͼ��
    }
    
    /**********minͼ��**********/
    bit_Cal(24, 0x01, 0x01);

    /**********�趨ʱ��ð��ͼ��**********/
    bit_Cal(28, 0x01, 0x01);

    /**********ʵ��ʱ��ð��ͼ��**********/
    bit_Cal(28, 0x80, 0x80);

    /**********���ݷ���**********/
   
    for(uint8_t i=0;i<46;i++)
    {
        Write_Addr_Dat_N(2+i, seg[i], 1);
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Speed(float dT)
 * ��    �ܣ��ٶ���ʾ����
*****************************************************************
*/
void Deal_Speed(uint8_t i)
{
    if(Work_Num[i].Run_Status)
    {
        if(Work_Num[i].Speed.Ctrl)
        {
            if(Work_Num[i].Speed.ADDMode==0)//�ڵ�������У��ٶ�δ����
            { 
                if(Work_Num[i].Speed.Ctrl >= Work_Num[i].Speed.Display_Rel)//�����ٶȴ���ʵ���ٶ�
                {
                    Work_Num[i].Speed.ADDMode = 1;//�������ģʽ��
                }
                else if(Work_Num[i].Speed.Ctrl < Work_Num[i].Speed.Display_Rel)//�����ٶ�С��ʵ���ٶ�
                {
                    Work_Num[i].Speed.ADDMode = 2;//�������ģʽ��
                }
            }
            if(Work_Num[i].Speed.ADDMode==1)//�ڽ������ģʽ��
            {
                if(Work_Num[i].Speed.Rel > Work_Num[i].Speed.Display_Rel)//��ǰ�ٶȴ�����ʾ�ٶ�
                {
                        Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Rel;//��ʾ��ǰ�ٶ�
                }
                else//��ǰ�ٶ�С����һ���ٶ�
                {
                    Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Display_Rel;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
                }  
                if(Work_Num[i].Motor_Stop == 0)
                {
                    if(Work_Num[i].Speed.Display_Rel >= Work_Num[i].Speed.Ctrl)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
                    {
                        Work_Num[i].Speed.ADDMode = 3;//�����ȶ�ģʽ
                        return;
                    }
                }
            }
            if(Work_Num[i].Speed.ADDMode == 2)//�ٶ��½�ģʽ��
            {
                if(Work_Num[i].Speed.Rel < Work_Num[i].Speed.Display_Rel)//��ǰ�ٶ�С����һ���ٶ�
                {
                        Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Rel;//��ʾ��ǰ�ٶ�
                }
                else//��ǰ�ٶȴ�����һ���ٶ�
                {
                    Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Display_Rel;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                }
                if(Work_Num[i].Motor_Stop == 0)
                {
                    if(Work_Num[i].Speed.Display_Rel <= Work_Num[i].Speed.Ctrl)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
                    {
                        Work_Num[i].Speed.ADDMode = 3;//�����ȶ�ģʽ
                        return;
                    }
                }
            }
            else if(Work_Num[i].Speed.ADDMode == 3)//�ٶ��ȶ�ģʽ��
            {
                Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Ctrl;//��ʾ�����ٶ�
            }
        }
        else
        {
            if(Work_Num[i].Speed.Rel < Work_Num[i].Speed.Display_Rel)//��ǰ�ٶ�С����һ���ٶ�
            {
                    Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Rel;//��ʾ��ǰ�ٶ�
            }
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Display_Rel;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
            }
        }
    }
    else
    {
        Work_Num[i].Speed.Display_Rel = 0;//ʵ���ٶ���ʾΪ��
        Work_Num[i].Speed.ADDMode = 0;//�����ʾ����
    }
}

/**
 * @brief ��ʾ��Ļ����
 *
 */
void Show_Display(void)
{
    for(uint8_t i = 0;i<15;i++)
    {
        Work_Num[i].Speed.Display_Set = Work_Num[i].Speed.Set;
        Deal_Speed(i);
        Work_Num[i].Time.Display_Set = Work_Num[i].Time.Set;
        Work_Num[i].Time.Display_Rel = Work_Num[i].Time.Rel + 59;
    }
    Display(Work_Num);
}
