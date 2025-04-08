#include "Show.h"

/**********ȫ�ֱ���**********/
float Twinkle_Time; // ��˸ʱ��

/**********�ֲ���������*******/
uint8_t Speed_ShowFlag, Time_ShowFlag, Sync_ShowFlag;//�ٶȡ��¶ȡ�ʱ����ʾ�ı�־λ��0��������1��Ϩ��

/*
*****************************************************************
 * ����ԭ�ͣ�static void Icn_Twinkle(float dT)
 * ��    �ܣ�ͼ����˸
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T[4];
    for(uint8_t i = 0;i<4;i++)
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
            else if(sys.SetMode_Option == 2)//����ʱ��
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

/**
 * @brief ��˸����
 *
 * @param dT ��������
 */
void Twinkle(float dT)
{
    Icn_Twinkle(dT);
    Check_ShowFlag(dT);
}

uint8_t seg[62] = {0};
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

void Display_IC(_Work_Num_ work_num[])
{
    uint8_t Val;// ���ڰ�ʮ��ȡ����������
    
    /**********��λ4��ʵ��ת����ʾ**********/
    if (work_num[3].Speed.Display_Rel > 999) // ����999ʱ
    {
        Val = work_num[3].Speed.Display_Rel / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(14, 0x70, 0x50);bit_Cal(15, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(14, 0x70, 0x50);bit_Cal(15, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(14, 0x70, 0x60);bit_Cal(15, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(14, 0x70, 0x70);bit_Cal(15, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(14, 0x70, 0x70);bit_Cal(15, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(14, 0x70, 0x30);bit_Cal(15, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(14, 0x70, 0x30);bit_Cal(15, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(14, 0x70, 0x50);bit_Cal(15, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(14, 0x70, 0x70);bit_Cal(15, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(14, 0x70, 0x70);bit_Cal(15, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(14, 0x70, 0x50);bit_Cal(15, 0xF0, 0xF0);
    }
    
   if (work_num[3].Speed.Display_Rel > 99) // ����99ʱ
   {
       Val = work_num[3].Speed.Display_Rel / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(12, 0x70, 0x50);bit_Cal(13, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(12, 0x70, 0x50);bit_Cal(13, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(12, 0x70, 0x60);bit_Cal(13, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(12, 0x70, 0x70);bit_Cal(13, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(12, 0x70, 0x70);bit_Cal(13, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(12, 0x70, 0x30);bit_Cal(13, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(12, 0x70, 0x30);bit_Cal(13, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(12, 0x70, 0x50);bit_Cal(13, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(12, 0x70, 0x70);bit_Cal(13, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(12, 0x70, 0x70);bit_Cal(13, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(12, 0x70, 0x50);bit_Cal(13, 0xF0, 0xF0);
    }

   if (work_num[3].Speed.Display_Rel > 9) // ����9ʱ
   {
       Val = work_num[3].Speed.Display_Rel / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(10, 0x70, 0x60);bit_Cal(11, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(10, 0x70, 0x30);bit_Cal(11, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(10, 0x70, 0x30);bit_Cal(11, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0xF0, 0xF0);
    }
   
   if (work_num[3].Speed.Display_Rel>= 0) // ���ڵ���0ʱ
   {
       Val = work_num[3].Speed.Display_Rel % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(8, 0x70, 0x50);bit_Cal(9, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(8, 0x70, 0x50);bit_Cal(9, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(8, 0x70, 0x60);bit_Cal(9, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(8, 0x70, 0x70);bit_Cal(9, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(8, 0x70, 0x70);bit_Cal(9, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(8, 0x70, 0x30);bit_Cal(9, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(8, 0x70, 0x30);bit_Cal(9, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(8, 0x70, 0x50);bit_Cal(9, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(8, 0x70, 0x70);bit_Cal(9, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(8, 0x70, 0x70);bit_Cal(9, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }

    /**********��λ4���趨ת����ʾ**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 3)//����ʾ�趨ת��
    {
        bit_Cal(6, 0x70, 0x00);bit_Cal(7, 0xF0, 0x00);//��һλ����ʾ
        bit_Cal(4, 0x70, 0x00);bit_Cal(5, 0xF0, 0x00);//�ڶ�λ����ʾ
        bit_Cal(2, 0x70, 0x00);bit_Cal(3, 0xF0, 0x00);//����λ����ʾ
        bit_Cal(0, 0x70, 0x00);bit_Cal(1, 0xF0, 0x00);//����λ����ʾ
    }
    else
    {
        if(work_num[3].Speed.Display_Set == 0)//��ʾ�� -- ��
        {
            bit_Cal(6, 0x70, 0x20);bit_Cal(7, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(4, 0x70, 0x20);bit_Cal(5, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(2, 0x70, 0x20);bit_Cal(3, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(0, 0x70, 0x20);bit_Cal(1, 0xF0, 0x00);//��ʾ��-��
        }
        else
        {
            if (work_num[3].Speed.Display_Set > 999) // ����999ʱ
            {
                Val = work_num[3].Speed.Display_Set / 1000 % 10;
                switch (Val)
                {
                case 0:
                       bit_Cal(6, 0x70, 0x50);bit_Cal(7, 0xF0, 0xF0);
                    break;
                case 1:
                       bit_Cal(6, 0x70, 0x50);bit_Cal(7, 0xF0, 0x00);
                    break;
                case 2:
                       bit_Cal(6, 0x70, 0x60);bit_Cal(7, 0xF0, 0xB0);
                    break;
                case 3:
                       bit_Cal(6, 0x70, 0x70);bit_Cal(7, 0xF0, 0x90);
                    break;
                case 4:
                       bit_Cal(6, 0x70, 0x70);bit_Cal(7, 0xF0, 0x40);
                    break;
                case 5:
                       bit_Cal(6, 0x70, 0x30);bit_Cal(7, 0xF0, 0xD0);
                    break;
                case 6:
                       bit_Cal(6, 0x70, 0x30);bit_Cal(7, 0xF0, 0xF0);
                    break;
                case 7:
                       bit_Cal(6, 0x70, 0x50);bit_Cal(7, 0xF0, 0x80);
                    break;
                case 8:
                       bit_Cal(6, 0x70, 0x70);bit_Cal(7, 0xF0, 0xF0);
                    break;
                case 9:
                       bit_Cal(6, 0x70, 0x70);bit_Cal(7, 0xF0, 0xD0);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(6, 0x70, 0x50);bit_Cal(7, 0xF0, 0xF0);
            }
            
           if (work_num[3].Speed.Display_Set > 99) // ����99ʱ
           {
               Val = work_num[3].Speed.Display_Set / 100 % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(4, 0x70, 0x50);bit_Cal(5, 0xF0, 0xF0);
                    break;
                case 1:
                       bit_Cal(4, 0x70, 0x50);bit_Cal(5, 0xF0, 0x00);
                    break;
                case 2:
                       bit_Cal(4, 0x70, 0x60);bit_Cal(5, 0xF0, 0xB0);
                    break;
                case 3:
                       bit_Cal(4, 0x70, 0x70);bit_Cal(5, 0xF0, 0x90);
                    break;
                case 4:
                       bit_Cal(4, 0x70, 0x70);bit_Cal(5, 0xF0, 0x40);
                    break;
                case 5:
                       bit_Cal(4, 0x70, 0x30);bit_Cal(5, 0xF0, 0xD0);
                    break;
                case 6:
                       bit_Cal(4, 0x70, 0x30);bit_Cal(5, 0xF0, 0xF0);
                    break;
                case 7:
                       bit_Cal(4, 0x70, 0x50);bit_Cal(5, 0xF0, 0x80);
                    break;
                case 8:
                       bit_Cal(4, 0x70, 0x70);bit_Cal(5, 0xF0, 0xF0);
                    break;
                case 9:
                       bit_Cal(4, 0x70, 0x70);bit_Cal(5, 0xF0, 0xD0);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(4, 0x70, 0x50);bit_Cal(5, 0xF0, 0xF0);
            }

           if (work_num[3].Speed.Display_Set > 9) // ����9ʱ
           {
               Val = work_num[3].Speed.Display_Set / 10 % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(2, 0x70, 0x50);bit_Cal(3, 0xF0, 0xF0);
                    break;
                case 1:
                       bit_Cal(2, 0x70, 0x50);bit_Cal(3, 0xF0, 0x00);
                    break;
                case 2:
                       bit_Cal(2, 0x70, 0x60);bit_Cal(3, 0xF0, 0xB0);
                    break;
                case 3:
                       bit_Cal(2, 0x70, 0x70);bit_Cal(3, 0xF0, 0x90);
                    break;
                case 4:
                       bit_Cal(2, 0x70, 0x70);bit_Cal(3, 0xF0, 0x40);
                    break;
                case 5:
                       bit_Cal(2, 0x70, 0x30);bit_Cal(3, 0xF0, 0xD0);
                    break;
                case 6:
                       bit_Cal(2, 0x70, 0x30);bit_Cal(3, 0xF0, 0xF0);
                    break;
                case 7:
                       bit_Cal(2, 0x70, 0x50);bit_Cal(3, 0xF0, 0x80);
                    break;
                case 8:
                       bit_Cal(2, 0x70, 0x70);bit_Cal(3, 0xF0, 0xF0);
                    break;
                case 9:
                       bit_Cal(2, 0x70, 0x70);bit_Cal(3, 0xF0, 0xD0);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(2, 0x70, 0x50);bit_Cal(3, 0xF0, 0xF0);
            }
           
           if (work_num[3].Speed.Display_Set>= 0) // ���ڵ���0ʱ
           {
               Val = work_num[3].Speed.Display_Set % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(0, 0x70, 0x50);bit_Cal(1, 0xF0, 0xF0);
                    break;
                case 1:
                       bit_Cal(0, 0x70, 0x50);bit_Cal(1, 0xF0, 0x00);
                    break;
                case 2:
                       bit_Cal(0, 0x70, 0x60);bit_Cal(1, 0xF0, 0xB0);
                    break;
                case 3:
                       bit_Cal(0, 0x70, 0x70);bit_Cal(1, 0xF0, 0x90);
                    break;
                case 4:
                       bit_Cal(0, 0x70, 0x70);bit_Cal(1, 0xF0, 0x40);
                    break;
                case 5:
                       bit_Cal(0, 0x70, 0x30);bit_Cal(1, 0xF0, 0xD0);
                    break;
                case 6:
                       bit_Cal(0, 0x70, 0x30);bit_Cal(1, 0xF0, 0xF0);
                    break;
                case 7:
                       bit_Cal(0, 0x70, 0x50);bit_Cal(1, 0xF0, 0x80);
                    break;
                case 8:
                       bit_Cal(0, 0x70, 0x70);bit_Cal(1, 0xF0, 0xF0);
                    break;
                case 9:
                       bit_Cal(0, 0x70, 0x70);bit_Cal(1, 0xF0, 0xD0);
                    break;
                default:
                   break;
                }
            }
        }
    }

     /**********��λ4��ʵ��ʱ����ʾ**********/
    if(work_num[3].Time.Rel == 0)
    {
        bit_Cal(14, 0x0E, 0x04);bit_Cal(15, 0x0F, 0x00);//��ʾ��-��
        bit_Cal(12, 0x0E, 0x04);bit_Cal(13, 0x0F, 0x00);//��ʾ��-��
        bit_Cal(10, 0x0E, 0x04);bit_Cal(11, 0x0F, 0x00);//��ʾ��-��
        bit_Cal(8, 0x0E, 0x04);bit_Cal(9, 0x0F, 0x00);//��ʾ��-��
    }
    else
    {
         Val = work_num[3].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
         switch (Val)
         {
         case 0:
              bit_Cal(14, 0x0E, 0x0A);bit_Cal(15, 0x0F, 0x0F);
              break;
         case 1:
              bit_Cal(14, 0x0E, 0x0A);bit_Cal(15, 0x0F, 0x00);
              break;
         case 2:
              bit_Cal(14, 0x0E, 0x0C);bit_Cal(15, 0x0F, 0x0B);
              break;
         case 3:
              bit_Cal(14, 0x0E, 0x0E);bit_Cal(15, 0x0F, 0x09);
              break;
         case 4:
              bit_Cal(14, 0x0E, 0x0E);bit_Cal(15, 0x0F, 0x04);
              break;
         case 5:
              bit_Cal(14, 0x0E, 0x06);bit_Cal(15, 0x0F, 0x0D);
              break;
         case 6:
              bit_Cal(14, 0x0E, 0x06);bit_Cal(15, 0x0F, 0x0F);
              break;
         case 7:
              bit_Cal(14, 0x0E, 0x0A);bit_Cal(15, 0x0F, 0x08);
              break;
         case 8:
              bit_Cal(14, 0x0E, 0x0E);bit_Cal(15, 0x0F, 0x0F);
              break;
         case 9:
              bit_Cal(14, 0x0E, 0x0E);bit_Cal(15, 0x0F, 0x0D);
              break;
         default:
              break;
         }

         Val = work_num[3].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
         switch (Val)
         {
         case 0:
              bit_Cal(12, 0x0E, 0x0A);bit_Cal(13, 0x0F, 0x0F);
              break;
         case 1:
              bit_Cal(12, 0x0E, 0x0A);bit_Cal(13, 0x0F, 0x00);
              break;
         case 2:
              bit_Cal(12, 0x0E, 0x0C);bit_Cal(13, 0x0F, 0x0B);
              break;
         case 3:
              bit_Cal(12, 0x0E, 0x0E);bit_Cal(13, 0x0F, 0x09);
              break;
         case 4:
              bit_Cal(12, 0x0E, 0x0E);bit_Cal(13, 0x0F, 0x04);
              break;
         case 5:
              bit_Cal(12, 0x0E, 0x06);bit_Cal(13, 0x0F, 0x0D);
              break;
         case 6:
              bit_Cal(12, 0x0E, 0x06);bit_Cal(13, 0x0F, 0x0F);
              break;
         case 7:
              bit_Cal(12, 0x0E, 0x0A);bit_Cal(13, 0x0F, 0x08);
              break;
         case 8:
              bit_Cal(12, 0x0E, 0x0E);bit_Cal(13, 0x0F, 0x0F);
              break;
         case 9:
              bit_Cal(12, 0x0E, 0x0E);bit_Cal(13, 0x0F, 0x0D);
              break;
         default:
              break;
         }

         Val = work_num[3].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
         switch (Val)
         {
         case 0:
              bit_Cal(10, 0x0E, 0x0A);bit_Cal(11, 0x0F, 0x0F);
              break;
         case 1:
              bit_Cal(10, 0x0E, 0x0A);bit_Cal(11, 0x0F, 0x00);
              break;
         case 2:
              bit_Cal(10, 0x0E, 0x0C);bit_Cal(11, 0x0F, 0x0B);
              break;
         case 3:
              bit_Cal(10, 0x0E, 0x0E);bit_Cal(11, 0x0F, 0x09);
              break;
         case 4:
              bit_Cal(10, 0x0E, 0x0E);bit_Cal(11, 0x0F, 0x04);
              break;
         case 5:
              bit_Cal(10, 0x0E, 0x06);bit_Cal(11, 0x0F, 0x0D);
              break;
         case 6:
              bit_Cal(10, 0x0E, 0x06);bit_Cal(11, 0x0F, 0x0F);
              break;
         case 7:
              bit_Cal(10, 0x0E, 0x0A);bit_Cal(11, 0x0F, 0x08);
              break;
         case 8:
              bit_Cal(10, 0x0E, 0x0E);bit_Cal(11, 0x0F, 0x0F);
              break;
         case 9:
              bit_Cal(10, 0x0E, 0x0E);bit_Cal(11, 0x0F, 0x0D);
              break;
         default:
              break;
         }

         Val = work_num[3].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
         switch (Val)
         {
         case 0:
              bit_Cal(8, 0x0E, 0x0A);bit_Cal(9, 0x0F, 0x0F);
              break;
         case 1:
              bit_Cal(8, 0x0E, 0x0A);bit_Cal(9, 0x0F, 0x00);
              break;
         case 2:
              bit_Cal(8, 0x0E, 0x0C);bit_Cal(9, 0x0F, 0x0B);
              break;
         case 3:
              bit_Cal(8, 0x0E, 0x0E);bit_Cal(9, 0x0F, 0x09);
              break;
         case 4:
              bit_Cal(8, 0x0E, 0x0E);bit_Cal(9, 0x0F, 0x04);
              break;
         case 5:
              bit_Cal(8, 0x0E, 0x06);bit_Cal(9, 0x0F, 0x0D);
              break;
         case 6:
              bit_Cal(8, 0x0E, 0x06);bit_Cal(9, 0x0F, 0x0F);
              break;
         case 7:
              bit_Cal(8, 0x0E, 0x0A);bit_Cal(9, 0x0F, 0x08);
              break;
         case 8:
              bit_Cal(8, 0x0E, 0x0E);bit_Cal(9, 0x0F, 0x0F);
              break;
         case 9:
              bit_Cal(8, 0x0E, 0x0E);bit_Cal(9, 0x0F, 0x0D);
              break;
         default:
              break;
         }
    }

     /**********��λ4���趨ʱ����ʾ**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 3)//����ʾ�趨ת��
    {
        bit_Cal(6, 0x0E, 0x00);bit_Cal(7, 0x0F, 0x00);//��һλ����ʾ
        bit_Cal(4, 0x0E, 0x00);bit_Cal(5, 0x0F, 0x00);//�ڶ�λ����ʾ
        bit_Cal(2, 0x0E, 0x00);bit_Cal(3, 0x0F, 0x00);//����λ����ʾ
        bit_Cal(0, 0x0E, 0x00);bit_Cal(1, 0x0F, 0x00);//����λ����ʾ
    }
    else
    {
        if(work_num[3].Time.Set == 0)
        {
            bit_Cal(6, 0x0E, 0x04);bit_Cal(7, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(4, 0x0E, 0x04);bit_Cal(5, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(2, 0x0E, 0x04);bit_Cal(3, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(0, 0x0E, 0x04);bit_Cal(1, 0x0F, 0x00);//��ʾ��-��
        }
        else
        {
             Val = work_num[3].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
             switch (Val)
             {
             case 0:
                  bit_Cal(6, 0x0E, 0x0A);bit_Cal(7, 0x0F, 0x0F);
                  break;
             case 1:
                  bit_Cal(6, 0x0E, 0x0A);bit_Cal(7, 0x0F, 0x00);
                  break;
             case 2:
                  bit_Cal(6, 0x0E, 0x0C);bit_Cal(7, 0x0F, 0x0B);
                  break;
             case 3:
                  bit_Cal(6, 0x0E, 0x0E);bit_Cal(7, 0x0F, 0x09);
                  break;
             case 4:
                  bit_Cal(6, 0x0E, 0x0E);bit_Cal(7, 0x0F, 0x04);
                  break;
             case 5:
                  bit_Cal(6, 0x0E, 0x06);bit_Cal(7, 0x0F, 0x0D);
                  break;
             case 6:
                  bit_Cal(6, 0x0E, 0x06);bit_Cal(7, 0x0F, 0x0F);
                  break;
             case 7:
                  bit_Cal(6, 0x0E, 0x0A);bit_Cal(7, 0x0F, 0x08);
                  break;
             case 8:
                  bit_Cal(6, 0x0E, 0x0E);bit_Cal(7, 0x0F, 0x0F);
                  break;
             case 9:
                  bit_Cal(6, 0x0E, 0x0E);bit_Cal(7, 0x0F, 0x0D);
                  break;
             default:
                  break;
             }

             Val = work_num[3].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
             switch (Val)
             {
             case 0:
                  bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x0F, 0x0F);
                  break;
             case 1:
                  bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x0F, 0x00);
                  break;
             case 2:
                  bit_Cal(4, 0x0E, 0x0C);bit_Cal(5, 0x0F, 0x0B);
                  break;
             case 3:
                  bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x0F, 0x09);
                  break;
             case 4:
                  bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x0F, 0x04);
                  break;
             case 5:
                  bit_Cal(4, 0x0E, 0x06);bit_Cal(5, 0x0F, 0x0D);
                  break;
             case 6:
                  bit_Cal(4, 0x0E, 0x06);bit_Cal(5, 0x0F, 0x0F);
                  break;
             case 7:
                  bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x0F, 0x08);
                  break;
             case 8:
                  bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x0F, 0x0F);
                  break;
             case 9:
                  bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x0F, 0x0D);
                  break;
             default:
                  break;
             }

             Val = work_num[3].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
             switch (Val)
             {
             case 0:
                  bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x0F, 0x0F);
                  break;
             case 1:
                  bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x0F, 0x00);
                  break;
             case 2:
                  bit_Cal(2, 0x0E, 0x0C);bit_Cal(3, 0x0F, 0x0B);
                  break;
             case 3:
                  bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x0F, 0x09);
                  break;
             case 4:
                  bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x0F, 0x04);
                  break;
             case 5:
                  bit_Cal(2, 0x0E, 0x06);bit_Cal(3, 0x0F, 0x0D);
                  break;
             case 6:
                  bit_Cal(2, 0x0E, 0x06);bit_Cal(3, 0x0F, 0x0F);
                  break;
             case 7:
                  bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x0F, 0x08);
                  break;
             case 8:
                  bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x0F, 0x0F);
                  break;
             case 9:
                  bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x0F, 0x0D);
                  break;
             default:
                  break;
             }

             Val = work_num[3].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
             switch (Val)
             {
             case 0:
                  bit_Cal(0, 0x0E, 0x0A);bit_Cal(1, 0x0F, 0x0F);
                  break;
             case 1:
                  bit_Cal(0, 0x0E, 0x0A);bit_Cal(1, 0x0F, 0x00);
                  break;
             case 2:
                  bit_Cal(0, 0x0E, 0x0C);bit_Cal(1, 0x0F, 0x0B);
                  break;
             case 3:
                  bit_Cal(0, 0x0E, 0x0E);bit_Cal(1, 0x0F, 0x09);
                  break;
             case 4:
                  bit_Cal(0, 0x0E, 0x0E);bit_Cal(1, 0x0F, 0x04);
                  break;
             case 5:
                  bit_Cal(0, 0x0E, 0x06);bit_Cal(1, 0x0F, 0x0D);
                  break;
             case 6:
                  bit_Cal(0, 0x0E, 0x06);bit_Cal(1, 0x0F, 0x0F);
                  break;
             case 7:
                  bit_Cal(0, 0x0E, 0x0A);bit_Cal(1, 0x0F, 0x08);
                  break;
             case 8:
                  bit_Cal(0, 0x0E, 0x0E);bit_Cal(1, 0x0F, 0x0F);
                  break;
             case 9:
                  bit_Cal(0, 0x0E, 0x0E);bit_Cal(1, 0x0F, 0x0D);
                  break;
             default:
                  break;
             }
         }
     }

     /**********��λ3��ʵ��ת����ʾ**********/
    if (work_num[2].Speed.Display_Rel > 999) // ����999ʱ
    {
        Val = work_num[2].Speed.Display_Rel / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(22, 0x81, 0x80);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x81);
            break;
        case 1:
               bit_Cal(22, 0x81, 0x00);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x00);bit_Cal(29, 0x81, 0x00);
            break;
        case 2:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x80);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x01);
            break;
        case 3:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x00);
            break;
        case 4:
               bit_Cal(22, 0x81, 0x01);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x00);bit_Cal(29, 0x81, 0x80);
            break;
        case 5:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x01);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x80);
            break;
        case 6:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x01);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x81);
            break;
        case 7:
               bit_Cal(22, 0x81, 0x80);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x00);bit_Cal(29, 0x81, 0x00);
            break;
        case 8:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x81);
            break;
        case 9:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x80);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(22, 0x81, 0x80);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x81);
    }
    
   if (work_num[2].Speed.Display_Rel > 99) // ����99ʱ
   {
       Val = work_num[2].Speed.Display_Rel / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(28, 0x70, 0x50);bit_Cal(26, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(28, 0x70, 0x50);bit_Cal(26, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(28, 0x70, 0x60);bit_Cal(26, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(28, 0x70, 0x70);bit_Cal(26, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(28, 0x70, 0x70);bit_Cal(26, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(28, 0x70, 0x30);bit_Cal(26, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(28, 0x70, 0x30);bit_Cal(26, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(28, 0x70, 0x50);bit_Cal(26, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(28, 0x70, 0x70);bit_Cal(26, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(28, 0x70, 0x70);bit_Cal(26, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(28, 0x70, 0x50);bit_Cal(26, 0xF0, 0xF0);
    }

   if (work_num[2].Speed.Display_Rel > 9) // ����9ʱ
   {
       Val = work_num[2].Speed.Display_Rel / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0xF0);
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
    }
    else
    {
        bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0xF0);
    }
   
   if (work_num[2].Speed.Display_Rel >= 0) // ���ڵ���0ʱ
   {
       Val = work_num[2].Speed.Display_Rel % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(22, 0x70, 0x50);bit_Cal(23, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(22, 0x70, 0x50);bit_Cal(23, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(22, 0x70, 0x60);bit_Cal(23, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(22, 0x70, 0x70);bit_Cal(23, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(22, 0x70, 0x70);bit_Cal(23, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(22, 0x70, 0x30);bit_Cal(23, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(22, 0x70, 0x30);bit_Cal(23, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(22, 0x70, 0x50);bit_Cal(23, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(22, 0x70, 0x70);bit_Cal(23, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(22, 0x70, 0x70);bit_Cal(23, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }

    /**********��λ3���趨ת����ʾ**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 2)//����ʾ�趨ת��
    {
        bit_Cal(29, 0x70, 0x00);bit_Cal(21, 0xF0, 0x00);//��һλ����ʾ
        bit_Cal(19, 0x70, 0x00);bit_Cal(20, 0xF0, 0x00);//�ڶ�λ����ʾ
        bit_Cal(30, 0x70, 0x00);bit_Cal(18, 0xF0, 0x00);//����λ����ʾ
        bit_Cal(16, 0x70, 0x00);bit_Cal(17, 0xF0, 0x00);//����λ����ʾ
    }
    else
    {
        if(work_num[2].Speed.Display_Set == 0)//��ʾ�� -- ��
        {
            bit_Cal(29, 0x70, 0x20);bit_Cal(21, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(19, 0x70, 0x20);bit_Cal(20, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(30, 0x70, 0x20);bit_Cal(18, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(16, 0x70, 0x20);bit_Cal(17, 0xF0, 0x00);//��ʾ��-��
        }
        else
        {
            if (work_num[2].Speed.Display_Set > 999) // ����999ʱ
            {
                Val = work_num[2].Speed.Display_Set / 1000 % 10;
                switch (Val)
                {
                case 0:
                       bit_Cal(29, 0x70, 0x50);bit_Cal(21, 0xF0, 0xF0);
                    break;
                case 1:
                       bit_Cal(29, 0x70, 0x50);bit_Cal(21, 0xF0, 0x00);
                    break;
                case 2:
                       bit_Cal(29, 0x70, 0x60);bit_Cal(21, 0xF0, 0xB0);
                    break;
                case 3:
                       bit_Cal(29, 0x70, 0x70);bit_Cal(21, 0xF0, 0x90);
                    break;
                case 4:
                       bit_Cal(29, 0x70, 0x70);bit_Cal(21, 0xF0, 0x40);
                    break;
                case 5:
                       bit_Cal(29, 0x70, 0x30);bit_Cal(21, 0xF0, 0xD0);
                    break;
                case 6:
                       bit_Cal(29, 0x70, 0x30);bit_Cal(21, 0xF0, 0xF0);
                    break;
                case 7:
                       bit_Cal(29, 0x70, 0x50);bit_Cal(21, 0xF0, 0x80);
                    break;
                case 8:
                       bit_Cal(29, 0x70, 0x70);bit_Cal(21, 0xF0, 0xF0);
                    break;
                case 9:
                       bit_Cal(29, 0x70, 0x70);bit_Cal(21, 0xF0, 0xD0);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(29, 0x70, 0x50);bit_Cal(21, 0xF0, 0xF0);
            }
            
           if (work_num[2].Speed.Display_Set > 99) // ����99ʱ
           {
               Val = work_num[2].Speed.Display_Set / 100 % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(19, 0x70, 0x50);bit_Cal(20, 0xF0, 0xF0);
                    break;
                case 1:
                       bit_Cal(19, 0x70, 0x50);bit_Cal(20, 0xF0, 0x00);
                    break;
                case 2:
                       bit_Cal(19, 0x70, 0x60);bit_Cal(20, 0xF0, 0xB0);
                    break;
                case 3:
                       bit_Cal(19, 0x70, 0x70);bit_Cal(20, 0xF0, 0x90);
                    break;
                case 4:
                       bit_Cal(19, 0x70, 0x70);bit_Cal(20, 0xF0, 0x40);
                    break;
                case 5:
                       bit_Cal(19, 0x70, 0x30);bit_Cal(20, 0xF0, 0xD0);
                    break;
                case 6:
                       bit_Cal(19, 0x70, 0x30);bit_Cal(20, 0xF0, 0xF0);
                    break;
                case 7:
                       bit_Cal(19, 0x70, 0x50);bit_Cal(20, 0xF0, 0x80);
                    break;
                case 8:
                       bit_Cal(19, 0x70, 0x70);bit_Cal(20, 0xF0, 0xF0);
                    break;
                case 9:
                       bit_Cal(19, 0x70, 0x70);bit_Cal(20, 0xF0, 0xD0);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(19, 0x70, 0x50);bit_Cal(20, 0xF0, 0xF0);
            }

           if (work_num[2].Speed.Display_Set > 9) // ����9ʱ
           {
               Val = work_num[2].Speed.Display_Set / 10 % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(30, 0x70, 0x50);bit_Cal(18, 0xF0, 0xF0);
                    break;
                case 1:
                       bit_Cal(30, 0x70, 0x50);bit_Cal(18, 0xF0, 0x00);
                    break;
                case 2:
                       bit_Cal(30, 0x70, 0x60);bit_Cal(18, 0xF0, 0xB0);
                    break;
                case 3:
                       bit_Cal(30, 0x70, 0x70);bit_Cal(18, 0xF0, 0x90);
                    break;
                case 4:
                       bit_Cal(30, 0x70, 0x70);bit_Cal(18, 0xF0, 0x40);
                    break;
                case 5:
                       bit_Cal(30, 0x70, 0x30);bit_Cal(18, 0xF0, 0xD0);
                    break;
                case 6:
                       bit_Cal(30, 0x70, 0x30);bit_Cal(18, 0xF0, 0xF0);
                    break;
                case 7:
                       bit_Cal(30, 0x70, 0x50);bit_Cal(18, 0xF0, 0x80);
                    break;
                case 8:
                       bit_Cal(30, 0x70, 0x70);bit_Cal(18, 0xF0, 0xF0);
                    break;
                case 9:
                       bit_Cal(30, 0x70, 0x70);bit_Cal(18, 0xF0, 0xD0);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(30, 0x70, 0x50);bit_Cal(18, 0xF0, 0xF0);
            }
           
           if (work_num[2].Speed.Display_Set>= 0) // ���ڵ���0ʱ
           {
               Val = work_num[2].Speed.Display_Set % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(16, 0x70, 0x50);bit_Cal(17, 0xF0, 0xF0);
                    break;
                case 1:
                       bit_Cal(16, 0x70, 0x50);bit_Cal(17, 0xF0, 0x00);
                    break;
                case 2:
                       bit_Cal(16, 0x70, 0x60);bit_Cal(17, 0xF0, 0xB0);
                    break;
                case 3:
                       bit_Cal(16, 0x70, 0x70);bit_Cal(17, 0xF0, 0x90);
                    break;
                case 4:
                       bit_Cal(16, 0x70, 0x70);bit_Cal(17, 0xF0, 0x40);
                    break;
                case 5:
                       bit_Cal(16, 0x70, 0x30);bit_Cal(17, 0xF0, 0xD0);
                    break;
                case 6:
                       bit_Cal(16, 0x70, 0x30);bit_Cal(17, 0xF0, 0xF0);
                    break;
                case 7:
                       bit_Cal(16, 0x70, 0x50);bit_Cal(17, 0xF0, 0x80);
                    break;
                case 8:
                       bit_Cal(16, 0x70, 0x70);bit_Cal(17, 0xF0, 0xF0);
                    break;
                case 9:
                       bit_Cal(16, 0x70, 0x70);bit_Cal(17, 0xF0, 0xD0);
                    break;
                default:
                   break;
                }
            }
        }
    }

    /**********��λ3��ʵ��ʱ����ʾ**********/
    if(work_num[2].Time.Rel == 0)
    {
        bit_Cal(27, 0x7F, 0x08);//��ʾ��-��
        bit_Cal(28, 0x0E, 0x04);bit_Cal(26, 0x0F, 0x00);//��ʾ��-��
        bit_Cal(24, 0x0E, 0x04);bit_Cal(25, 0x0F, 0x00);//��ʾ��-��
        bit_Cal(22, 0x0E, 0x04);bit_Cal(23, 0x0F, 0x00);//��ʾ��-��
    }
    else
    {
         Val = work_num[2].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
         switch (Val)
         {
         case 0:
              bit_Cal(27, 0x7F, 0x77);
              break;
         case 1:
              bit_Cal(27, 0x7F, 0x12);
              break;
         case 2:
              bit_Cal(27, 0x7F, 0x5D);
              break;
         case 3:
              bit_Cal(27, 0x7F, 0x5B);
              break;
         case 4:
              bit_Cal(27, 0x7F, 0x3A);
              break;
         case 5:
              bit_Cal(27, 0x7F, 0x6B);
              break;
         case 6:
              bit_Cal(27, 0x7F, 0x6F);
              break;
         case 7:
              bit_Cal(27, 0x7F, 0x52);
              break;
         case 8:
              bit_Cal(27, 0x7F, 0x7F);
              break;
         case 9:
              bit_Cal(27, 0x7F, 0x7B);
              break;
         default:
              break;
         }

         Val = work_num[2].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
         switch (Val)
         {
         case 0:
              bit_Cal(28, 0x0E, 0x0A);bit_Cal(26, 0x0F, 0x0F);
              break;
         case 1:
              bit_Cal(28, 0x0E, 0x0A);bit_Cal(26, 0x0F, 0x00);
              break;
         case 2:
              bit_Cal(28, 0x0E, 0x0C);bit_Cal(26, 0x0F, 0x0B);
              break;
         case 3:
              bit_Cal(28, 0x0E, 0x0E);bit_Cal(26, 0x0F, 0x09);
              break;
         case 4:
              bit_Cal(28, 0x0E, 0x0E);bit_Cal(26, 0x0F, 0x04);
              break;
         case 5:
              bit_Cal(28, 0x0E, 0x06);bit_Cal(26, 0x0F, 0x0D);
              break;
         case 6:
              bit_Cal(28, 0x0E, 0x06);bit_Cal(26, 0x0F, 0x0F);
              break;
         case 7:
              bit_Cal(28, 0x0E, 0x0A);bit_Cal(26, 0x0F, 0x08);
              break;
         case 8:
              bit_Cal(28, 0x0E, 0x0E);bit_Cal(26, 0x0F, 0x0F);
              break;
         case 9:
              bit_Cal(28, 0x0E, 0x0E);bit_Cal(26, 0x0F, 0x0D);
              break;
         default:
              break;
         }

         Val = work_num[2].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
         switch (Val)
         {
         case 0:
              bit_Cal(24, 0x0E, 0x0A);bit_Cal(25, 0x0F, 0x0F);
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

         Val = work_num[2].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
         switch (Val)
         {
         case 0:
              bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x0F);
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
              bit_Cal(22, 0x0E, 0x06);bit_Cal(23, 0x0F, 0x0F);
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

     /**********��λ3���趨ʱ����ʾ**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 2)//����ʾ�趨ת��
    {
        bit_Cal(29, 0x0E, 0x00);bit_Cal(21, 0x0F, 0x00);//��һλ����ʾ
        bit_Cal(19, 0x0E, 0x00);bit_Cal(20, 0x0F, 0x00);//�ڶ�λ����ʾ
        bit_Cal(30, 0x0E, 0x00);bit_Cal(18, 0x0F, 0x00);//����λ����ʾ
        bit_Cal(16, 0x0E, 0x00);bit_Cal(17, 0x0F, 0x00);//����λ����ʾ
    }
    else
    {
        if(work_num[2].Time.Set == 0)
        {
            bit_Cal(29, 0x0E, 0x04);bit_Cal(21, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(19, 0x0E, 0x04);bit_Cal(20, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(30, 0x0E, 0x04);bit_Cal(18, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(16, 0x0E, 0x04);bit_Cal(17, 0x0F, 0x00);//��ʾ��-��
        }
        else
        {
             Val = work_num[2].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
             switch (Val)
             {
             case 0:
                  bit_Cal(29, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x0F);
                  break;
             case 1:
                  bit_Cal(29, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x00);
                  break;
             case 2:
                  bit_Cal(29, 0x0E, 0x0C);bit_Cal(21, 0x0F, 0x0B);
                  break;
             case 3:
                  bit_Cal(29, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x09);
                  break;
             case 4:
                  bit_Cal(29, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x04);
                  break;
             case 5:
                  bit_Cal(29, 0x0E, 0x06);bit_Cal(21, 0x0F, 0x0D);
                  break;
             case 6:
                  bit_Cal(29, 0x0E, 0x06);bit_Cal(21, 0x0F, 0x0F);
                  break;
             case 7:
                  bit_Cal(29, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x08);
                  break;
             case 8:
                  bit_Cal(29, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0F);
                  break;
             case 9:
                  bit_Cal(29, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0D);
                  break;
             default:
                  break;
             }

             Val = work_num[2].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
             switch (Val)
             {
             case 0:
                  bit_Cal(19, 0x0E, 0x0A);bit_Cal(20, 0x0F, 0x0F);
                  break;
             case 1:
                  bit_Cal(19, 0x0E, 0x0A);bit_Cal(20, 0x0F, 0x00);
                  break;
             case 2:
                  bit_Cal(19, 0x0E, 0x0C);bit_Cal(20, 0x0F, 0x0B);
                  break;
             case 3:
                  bit_Cal(19, 0x0E, 0x0E);bit_Cal(20, 0x0F, 0x09);
                  break;
             case 4:
                  bit_Cal(19, 0x0E, 0x0E);bit_Cal(20, 0x0F, 0x04);
                  break;
             case 5:
                  bit_Cal(19, 0x0E, 0x06);bit_Cal(20, 0x0F, 0x0D);
                  break;
             case 6:
                  bit_Cal(19, 0x0E, 0x06);bit_Cal(20, 0x0F, 0x0F);
                  break;
             case 7:
                  bit_Cal(19, 0x0E, 0x0A);bit_Cal(20, 0x0F, 0x08);
                  break;
             case 8:
                  bit_Cal(19, 0x0E, 0x0E);bit_Cal(20, 0x0F, 0x0F);
                  break;
             case 9:
                  bit_Cal(19, 0x0E, 0x0E);bit_Cal(20, 0x0F, 0x0D);
                  break;
             default:
                  break;
             }

             Val = work_num[2].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
             switch (Val)
             {
             case 0:
                  bit_Cal(30, 0x0E, 0x0A);bit_Cal(18, 0x0F, 0x0F);
                  break;
             case 1:
                  bit_Cal(30, 0x0E, 0x0A);bit_Cal(18, 0x0F, 0x00);
                  break;
             case 2:
                  bit_Cal(30, 0x0E, 0x0C);bit_Cal(18, 0x0F, 0x0B);
                  break;
             case 3:
                  bit_Cal(30, 0x0E, 0x0E);bit_Cal(18, 0x0F, 0x09);
                  break;
             case 4:
                  bit_Cal(30, 0x0E, 0x0E);bit_Cal(18, 0x0F, 0x04);
                  break;
             case 5:
                  bit_Cal(30, 0x0E, 0x06);bit_Cal(18, 0x0F, 0x0D);
                  break;
             case 6:
                  bit_Cal(30, 0x0E, 0x06);bit_Cal(18, 0x0F, 0x0F);
                  break;
             case 7:
                  bit_Cal(30, 0x0E, 0x0A);bit_Cal(18, 0x0F, 0x08);
                  break;
             case 8:
                  bit_Cal(30, 0x0E, 0x0E);bit_Cal(18, 0x0F, 0x0F);
                  break;
             case 9:
                  bit_Cal(30, 0x0E, 0x0E);bit_Cal(18, 0x0F, 0x0D);
                  break;
             default:
                  break;
             }

             Val = work_num[2].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
             switch (Val)
             {
             case 0:
                  bit_Cal(16, 0x0E, 0x0A);bit_Cal(17, 0x0F, 0x0F);
                  break;
             case 1:
                  bit_Cal(16, 0x0E, 0x0A);bit_Cal(17, 0x0F, 0x00);
                  break;
             case 2:
                  bit_Cal(16, 0x0E, 0x0C);bit_Cal(17, 0x0F, 0x0B);
                  break;
             case 3:
                  bit_Cal(16, 0x0E, 0x0E);bit_Cal(17, 0x0F, 0x09);
                  break;
             case 4:
                  bit_Cal(16, 0x0E, 0x0E);bit_Cal(17, 0x0F, 0x04);
                  break;
             case 5:
                  bit_Cal(16, 0x0E, 0x06);bit_Cal(17, 0x0F, 0x0D);
                  break;
             case 6:
                  bit_Cal(16, 0x0E, 0x06);bit_Cal(17, 0x0F, 0x0F);
                  break;
             case 7:
                  bit_Cal(16, 0x0E, 0x0A);bit_Cal(17, 0x0F, 0x08);
                  break;
             case 8:
                  bit_Cal(16, 0x0E, 0x0E);bit_Cal(17, 0x0F, 0x0F);
                  break;
             case 9:
                  bit_Cal(16, 0x0E, 0x0E);bit_Cal(17, 0x0F, 0x0D);
                  break;
             default:
                  break;
             }
         }
     }

     /**********��λ4'RPM'��ʾ**********/
     bit_Cal(0, 0x80, 0x80);

     /**********��λ4'min'��ʾ**********/
     bit_Cal(0, 0x01, 0x01);

     /**********��λ4�趨ʱ��'��'��ʾ**********/
     bit_Cal(4, 0x01, 0x01);
     
    /* 2�Ź�λ4�Ź�λ֮����� */
    if(sys.New_Work == 1 || sys.New_Work == 3)//�����ǰ��λ��2����4�Ź�λ
    {
        /**********�ұߺ����ʾ**********/
        bit_Cal(6, 0x80, 0x80);
    }
    else
    {
        bit_Cal(6, 0x80, 0x00);
    }

     /**********�м���ͼ����ʾ**********/
    if(Lock_Switch)
        bit_Cal(6, 0x01, 0x01);
    else
        bit_Cal(6, 0x01, 0x00);
     
    /* 4�Ź�λת��ͼ�� */
    switch(Work_Num[3].Speed.IconStep)
	{
		case 0: bit_Cal(10, 0x80, 0x80);
                bit_Cal(8, 0x80, 0x80);
                bit_Cal(8, 0x01, 0x01);
			break;
		case 1: bit_Cal(10, 0x80, 0x00);
                bit_Cal(8, 0x80, 0x80);
                bit_Cal(8, 0x01, 0x01);
			break;
		case 2: bit_Cal(10, 0x80, 0x80);
                bit_Cal(8, 0x80, 0x00);
                bit_Cal(8, 0x01, 0x01);
			break;
		case 3: bit_Cal(10, 0x80, 0x80);
                bit_Cal(8, 0x80, 0x80);
                bit_Cal(8, 0x01, 0x00);
			break;
		default:
			break;
	}
    /* 1�Ź�λ3�Ź�λ֮����� */
    if(sys.New_Work == 0 || sys.New_Work == 2)//�����ǰ��λ��1����3�Ź�λ
    {
        /**********��ߺ����ʾ**********/
        bit_Cal(10, 0x01, 0x01);
    }
    else
    {
        bit_Cal(10, 0x01, 0x00);
    }

    /* 3�Ź�λ4�Ź�λ֮������ */
    if(sys.New_Work == 2 || sys.New_Work == 3)//�����ǰ��λ��3����4�Ź�λ
    {
        /**********����������ʾ**********/
        bit_Cal(12, 0x80, 0x80);
    }
    else
    {
        bit_Cal(12, 0x80, 0x00);
    }

     /**********��λ4ʵ��ʱ��'��'��ʾ**********/
     bit_Cal(12, 0x01, 0x01);

    /* 4�Ź�λʱ��ͼ�� */
    if(Work_Num[3].Time.Icon == 0)
    {
        bit_Cal(14, 0x80, 0x80);
    }
    else
    {
        bit_Cal(14, 0x80, 0x00);
    }

     /**********��λ3'RPM'��ʾ**********/
     bit_Cal(16, 0x80, 0x80);

     /**********��λ3'min'��ʾ**********/
     bit_Cal(16, 0x01, 0x01); 

    /* 3�Ź�λת��ͼ�� */
    switch(Work_Num[2].Speed.IconStep)
	{
		case 0: bit_Cal(30, 0x80, 0x80);
                bit_Cal(30, 0x01, 0x01);
                bit_Cal(19, 0x80, 0x80);
			break;
		case 1: bit_Cal(30, 0x80, 0x00);
                bit_Cal(30, 0x01, 0x01);
                bit_Cal(19, 0x80, 0x80);
			break;
		case 2: bit_Cal(30, 0x80, 0x80);
                bit_Cal(30, 0x01, 0x00);
                bit_Cal(19, 0x80, 0x80);
			break;
		case 3: bit_Cal(30, 0x80, 0x80);
                bit_Cal(30, 0x01, 0x01);
                bit_Cal(19, 0x80, 0x00);
			break;
		default:
			break;
	}
   
     /**********��λ4�趨ʱ��'��'��ʾ**********/
     bit_Cal(19, 0x01, 0x01);

    /*3�Ź�λʱ��ͼ�� */
    if(Work_Num[2].Time.Icon == 0)
    {
        bit_Cal(27, 0x80, 0x80);
    }
    else
    {   
        bit_Cal(27, 0x80, 0x00);
    }

     /**********��λ3ʵ��ʱ��'��'��ʾ**********/
     bit_Cal(28, 0x01, 0x01);

     /******************** IC2 ********************/
     /**********��λ2��ʵ��ת����ʾ**********/
     if (work_num[1].Speed.Display_Rel > 999) // ����999ʱ
     {
        Val = work_num[1].Speed.Display_Rel / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(45, 0x0E, 0x0A);bit_Cal(46, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(45, 0x0E, 0x0A);bit_Cal(46, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(45, 0x0E, 0x06);bit_Cal(46, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(45, 0x0E, 0x0E);bit_Cal(46, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(45, 0x0E, 0x0E);bit_Cal(46, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(45, 0x0E, 0x0C);bit_Cal(46, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(45, 0x0E, 0x0C);bit_Cal(46, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(45, 0x0E, 0x0A);bit_Cal(46, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(45, 0x0E, 0x0E);bit_Cal(46, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(45, 0x0E, 0x0E);bit_Cal(46, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(45, 0x0E, 0x0A);bit_Cal(46, 0x0F, 0x0F);
    }
    
   if (work_num[1].Speed.Display_Rel > 99) // ����99ʱ
   {
       Val = work_num[1].Speed.Display_Rel / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(43, 0x0E, 0x06);bit_Cal(44, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(43, 0x0E, 0x0C);bit_Cal(44, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(43, 0x0E, 0x0C);bit_Cal(44, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x0F);
    }

   if (work_num[1].Speed.Display_Rel > 9) // ����9ʱ
   {
       Val = work_num[1].Speed.Display_Rel / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(41, 0x0E, 0x06);bit_Cal(42, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(41, 0x0E, 0x0C);bit_Cal(42, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(41, 0x0E, 0x0C);bit_Cal(42, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x0F);
    }
   
   if (work_num[1].Speed.Display_Rel>= 0) // ���ڵ���0ʱ
   {
       Val = work_num[1].Speed.Display_Rel % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(39, 0x0E, 0x0A);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(39, 0x0E, 0x0A);bit_Cal(40, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(39, 0x0E, 0x06);bit_Cal(40, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(39, 0x0E, 0x0E);bit_Cal(40, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(39, 0x0E, 0x0E);bit_Cal(40, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(39, 0x0E, 0x0C);bit_Cal(40, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(39, 0x0E, 0x0C);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(39, 0x0E, 0x0A);bit_Cal(40, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(39, 0x0E, 0x0E);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(39, 0x0E, 0x0E);bit_Cal(40, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    /**********��λ2���趨ת����ʾ**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 1)//����ʾ�趨ת��
    {
        bit_Cal(37, 0x0E, 0x00);bit_Cal(38, 0x0F, 0x00);//��һλ����ʾ
        bit_Cal(35, 0x0E, 0x00);bit_Cal(36, 0x0F, 0x00);//�ڶ�λ����ʾ
        bit_Cal(33, 0x0E, 0x00);bit_Cal(34, 0x0F, 0x00);//����λ����ʾ
        bit_Cal(31, 0x0E, 0x00);bit_Cal(32, 0x0F, 0x00);//����λ����ʾ
    }
    else
    {
        if(work_num[1].Speed.Display_Set == 0)//��ʾ�� -- ��
        {
            bit_Cal(37, 0x0E, 0x04);bit_Cal(38, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(35, 0x0E, 0x04);bit_Cal(36, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(33, 0x0E, 0x04);bit_Cal(34, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(31, 0x0E, 0x04);bit_Cal(32, 0x0F, 0x00);//��ʾ��-��
        }
        else
        {
             if (work_num[1].Speed.Display_Set > 999) // ����999ʱ
             {
                Val = work_num[1].Speed.Display_Set / 1000 % 10;
                switch (Val)
                {
                case 0:
                       bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x0F);
                    break;
                case 1:
                       bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x00);
                    break;
                case 2:
                       bit_Cal(37, 0x0E, 0x06);bit_Cal(38, 0x0F, 0x0D);
                    break;
                case 3:
                       bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x09);
                    break;
                case 4:
                       bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x02);
                    break;
                case 5:
                       bit_Cal(37, 0x0E, 0x0C);bit_Cal(38, 0x0F, 0x0B);
                    break;
                case 6:
                       bit_Cal(37, 0x0E, 0x0C);bit_Cal(38, 0x0F, 0x0F);
                    break;
                case 7:
                       bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x01);
                    break;
                case 8:
                       bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x0F);
                    break;
                case 9:
                       bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x0B);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x0F);
            }
            
           if (work_num[1].Speed.Display_Set > 99) // ����99ʱ
           {
               Val = work_num[1].Speed.Display_Set / 100 % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(35, 0x0E, 0x0A);bit_Cal(36, 0x0F, 0x0F);
                    break;
                case 1:
                       bit_Cal(35, 0x0E, 0x0A);bit_Cal(36, 0x0F, 0x00);
                    break;
                case 2:
                       bit_Cal(35, 0x0E, 0x06);bit_Cal(36, 0x0F, 0x0D);
                    break;
                case 3:
                       bit_Cal(35, 0x0E, 0x0E);bit_Cal(36, 0x0F, 0x09);
                    break;
                case 4:
                       bit_Cal(35, 0x0E, 0x0E);bit_Cal(36, 0x0F, 0x02);
                    break;
                case 5:
                       bit_Cal(35, 0x0E, 0x0C);bit_Cal(36, 0x0F, 0x0B);
                    break;
                case 6:
                       bit_Cal(35, 0x0E, 0x0C);bit_Cal(36, 0x0F, 0x0F);
                    break;
                case 7:
                       bit_Cal(35, 0x0E, 0x0A);bit_Cal(36, 0x0F, 0x01);
                    break;
                case 8:
                       bit_Cal(35, 0x0E, 0x0E);bit_Cal(36, 0x0F, 0x0F);
                    break;
                case 9:
                       bit_Cal(35, 0x0E, 0x0E);bit_Cal(36, 0x0F, 0x0B);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(35, 0x0E, 0x0A);bit_Cal(36, 0x0F, 0x0F);
            }

           if (work_num[1].Speed.Display_Set > 9) // ����9ʱ
           {
               Val = work_num[1].Speed.Display_Set / 10 % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(33, 0x0E, 0x0A);bit_Cal(34, 0x0F, 0x0F);
                    break;
                case 1:
                       bit_Cal(33, 0x0E, 0x0A);bit_Cal(34, 0x0F, 0x00);
                    break;
                case 2:
                       bit_Cal(33, 0x0E, 0x06);bit_Cal(34, 0x0F, 0x0D);
                    break;
                case 3:
                       bit_Cal(33, 0x0E, 0x0E);bit_Cal(34, 0x0F, 0x09);
                    break;
                case 4:
                       bit_Cal(33, 0x0E, 0x0E);bit_Cal(34, 0x0F, 0x02);
                    break;
                case 5:
                       bit_Cal(33, 0x0E, 0x0C);bit_Cal(34, 0x0F, 0x0B);
                    break;
                case 6:
                       bit_Cal(33, 0x0E, 0x0C);bit_Cal(34, 0x0F, 0x0F);
                    break;
                case 7:
                       bit_Cal(33, 0x0E, 0x0A);bit_Cal(34, 0x0F, 0x01);
                    break;
                case 8:
                       bit_Cal(33, 0x0E, 0x0E);bit_Cal(34, 0x0F, 0x0F);
                    break;
                case 9:
                       bit_Cal(33, 0x0E, 0x0E);bit_Cal(34, 0x0F, 0x0B);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(33, 0x0E, 0x0A);bit_Cal(34, 0x0F, 0x0F);
            }
           
           if (work_num[1].Speed.Display_Set>= 0) // ���ڵ���0ʱ
           {
               Val = work_num[1].Speed.Display_Set % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(31, 0x0E, 0x0A);bit_Cal(32, 0x0F, 0x0F);
                    break;
                case 1:
                       bit_Cal(31, 0x0E, 0x0A);bit_Cal(32, 0x0F, 0x00);
                    break;
                case 2:
                       bit_Cal(31, 0x0E, 0x06);bit_Cal(32, 0x0F, 0x0D);
                    break;
                case 3:
                       bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x0F, 0x09);
                    break;
                case 4:
                       bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x0F, 0x02);
                    break;
                case 5:
                       bit_Cal(31, 0x0E, 0x0C);bit_Cal(32, 0x0F, 0x0B);
                    break;
                case 6:
                       bit_Cal(31, 0x0E, 0x0C);bit_Cal(32, 0x0F, 0x0F);
                    break;
                case 7:
                       bit_Cal(31, 0x0E, 0x0A);bit_Cal(32, 0x0F, 0x01);
                    break;
                case 8:
                       bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x0F, 0x0F);
                    break;
                case 9:
                       bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x0F, 0x0B);
                    break;
                default:
                   break;
                }
             }
         }
     }

     /**********��λ2��ʵ��ʱ����ʾ**********/
    if(work_num[1].Time.Rel == 0)
    {
        bit_Cal(45, 0x70, 0x20);bit_Cal(46, 0xF0, 0x00);//��ʾ��-��
        bit_Cal(43, 0x70, 0x20);bit_Cal(44, 0xF0, 0x00);//��ʾ��-��
        bit_Cal(41, 0x70, 0x20);bit_Cal(42, 0xF0, 0x00);//��ʾ��-��
        bit_Cal(39, 0x70, 0x20);bit_Cal(40, 0xF0, 0x00);//��ʾ��-��
    }
    else
    {
         Val = work_num[1].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
         switch (Val)
         {
         case 0:
              bit_Cal(45, 0x70, 0x50);bit_Cal(46, 0xF0, 0xF0);
              break;
         case 1:
              bit_Cal(45, 0x70, 0x50);bit_Cal(46, 0xF0, 0x00);
              break;
         case 2:
              bit_Cal(45, 0x70, 0x30);bit_Cal(46, 0xF0, 0xD0);
              break;
         case 3:
              bit_Cal(45, 0x70, 0x70);bit_Cal(46, 0xF0, 0x90);
              break;
         case 4:
              bit_Cal(45, 0x70, 0x70);bit_Cal(46, 0xF0, 0x20);
              break;
         case 5:
              bit_Cal(45, 0x70, 0x60);bit_Cal(46, 0xF0, 0xB0);
              break;
         case 6:
              bit_Cal(45, 0x70, 0x60);bit_Cal(46, 0xF0, 0xF0);
              break;
         case 7:
              bit_Cal(45, 0x70, 0x50);bit_Cal(46, 0xF0, 0x10);
              break;
         case 8:
              bit_Cal(45, 0x70, 0x70);bit_Cal(46, 0xF0, 0xF0);
              break;
         case 9:
              bit_Cal(45, 0x70, 0x70);bit_Cal(46, 0xF0, 0xB0);
              break;
         default:
              break;
         }

         Val = work_num[1].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
         switch (Val)
         {
         case 0:
              bit_Cal(43, 0x70, 0x50);bit_Cal(44, 0xF0, 0xF0);
              break;
         case 1:
              bit_Cal(43, 0x70, 0x50);bit_Cal(44, 0xF0, 0x00);
              break;
         case 2:
              bit_Cal(43, 0x70, 0x30);bit_Cal(44, 0xF0, 0xD0);
              break;
         case 3:
              bit_Cal(43, 0x70, 0x70);bit_Cal(44, 0xF0, 0x90);
              break;
         case 4:
              bit_Cal(43, 0x70, 0x70);bit_Cal(44, 0xF0, 0x20);
              break;
         case 5:
              bit_Cal(43, 0x70, 0x60);bit_Cal(44, 0xF0, 0xB0);
              break;
         case 6:
              bit_Cal(43, 0x70, 0x60);bit_Cal(44, 0xF0, 0xF0);
              break;
         case 7:
              bit_Cal(43, 0x70, 0x50);bit_Cal(44, 0xF0, 0x10);
              break;
         case 8:
              bit_Cal(43, 0x70, 0x70);bit_Cal(44, 0xF0, 0xF0);
              break;
         case 9:
              bit_Cal(43, 0x70, 0x70);bit_Cal(44, 0xF0, 0xB0);
              break;
         default:
              break;
         }

         Val = work_num[1].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
         switch (Val)
         {
         case 0:
              bit_Cal(41, 0x70, 0x50);bit_Cal(42, 0xF0, 0xF0);
              break;
         case 1:
              bit_Cal(41, 0x70, 0x50);bit_Cal(42, 0xF0, 0x00);
              break;
         case 2:
              bit_Cal(41, 0x70, 0x30);bit_Cal(42, 0xF0, 0xD0);
              break;
         case 3:
              bit_Cal(41, 0x70, 0x70);bit_Cal(42, 0xF0, 0x90);
              break;
         case 4:
              bit_Cal(41, 0x70, 0x70);bit_Cal(42, 0xF0, 0x20);
              break;
         case 5:
              bit_Cal(41, 0x70, 0x60);bit_Cal(42, 0xF0, 0xB0);
              break;
         case 6:
              bit_Cal(41, 0x70, 0x60);bit_Cal(42, 0xF0, 0xF0);
              break;
         case 7:
              bit_Cal(41, 0x70, 0x50);bit_Cal(42, 0xF0, 0x10);
              break;
         case 8:
              bit_Cal(41, 0x70, 0x70);bit_Cal(42, 0xF0, 0xF0);
              break;
         case 9:
              bit_Cal(41, 0x70, 0x70);bit_Cal(42, 0xF0, 0xB0);
              break;
         default:
              break;
         }

         Val = work_num[1].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
         switch (Val)
         {
         case 0:
              bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0xF0);
              break;
         case 1:
              bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0x00);
              break;
         case 2:
              bit_Cal(39, 0x70, 0x30);bit_Cal(40, 0xF0, 0xD0);
              break;
         case 3:
              bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0x90);
              break;
         case 4:
              bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0x20);
              break;
         case 5:
              bit_Cal(39, 0x70, 0x60);bit_Cal(40, 0xF0, 0xB0);
              break;
         case 6:
              bit_Cal(39, 0x70, 0x60);bit_Cal(40, 0xF0, 0xF0);
              break;
         case 7:
              bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0x10);
              break;
         case 8:
              bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0xF0);
              break;
         case 9:
              bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0xB0);
              break;
         default:
              break;
         }
    }

     /**********��λ2���趨ʱ����ʾ**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 1)//����ʾ�趨ת��
    {
        bit_Cal(37, 0x70, 0x00);bit_Cal(38, 0xF0, 0x00);//��һλ����ʾ
        bit_Cal(35, 0x70, 0x00);bit_Cal(36, 0xF0, 0x00);//�ڶ�λ����ʾ
        bit_Cal(33, 0x70, 0x00);bit_Cal(34, 0xF0, 0x00);//����λ����ʾ
        bit_Cal(31, 0x70, 0x00);bit_Cal(32, 0xF0, 0x00);//����λ����ʾ
    }
    else
    {
        if(work_num[1].Time.Set == 0)
        {
            bit_Cal(37, 0x70, 0x20);bit_Cal(38, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(35, 0x70, 0x20);bit_Cal(36, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(33, 0x70, 0x20);bit_Cal(34, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(31, 0x70, 0x20);bit_Cal(32, 0xF0, 0x00);//��ʾ��-��
        }
        else
        {
             Val = work_num[1].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
             switch (Val)
             {
             case 0:
                  bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0xF0);
                  break;
             case 1:
                  bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0x00);
                  break;
             case 2:
                  bit_Cal(37, 0x70, 0x30);bit_Cal(38, 0xF0, 0xD0);
                  break;
             case 3:
                  bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0x90);
                  break;
             case 4:
                  bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0x20);
                  break;
             case 5:
                  bit_Cal(37, 0x70, 0x60);bit_Cal(38, 0xF0, 0xB0);
                  break;
             case 6:
                  bit_Cal(37, 0x70, 0x60);bit_Cal(38, 0xF0, 0xF0);
                  break;
             case 7:
                  bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0x10);
                  break;
             case 8:
                  bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0xF0);
                  break;
             case 9:
                  bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0xB0);
                  break;
             default:
                  break;
             }

             Val = work_num[1].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
             switch (Val)
             {
             case 0:
                  bit_Cal(35, 0x70, 0x50);bit_Cal(36, 0xF0, 0xF0);
                  break;
             case 1:
                  bit_Cal(35, 0x70, 0x50);bit_Cal(36, 0xF0, 0x00);
                  break;
             case 2:
                  bit_Cal(35, 0x70, 0x30);bit_Cal(36, 0xF0, 0xD0);
                  break;
             case 3:
                  bit_Cal(35, 0x70, 0x70);bit_Cal(36, 0xF0, 0x90);
                  break;
             case 4:
                  bit_Cal(35, 0x70, 0x70);bit_Cal(36, 0xF0, 0x20);
                  break;
             case 5:
                  bit_Cal(35, 0x70, 0x60);bit_Cal(36, 0xF0, 0xB0);
                  break;
             case 6:
                  bit_Cal(35, 0x70, 0x60);bit_Cal(36, 0xF0, 0xF0);
                  break;
             case 7:
                  bit_Cal(35, 0x70, 0x50);bit_Cal(36, 0xF0, 0x10);
                  break;
             case 8:
                  bit_Cal(35, 0x70, 0x70);bit_Cal(36, 0xF0, 0xF0);
                  break;
             case 9:
                  bit_Cal(35, 0x70, 0x70);bit_Cal(36, 0xF0, 0xB0);
                  break;
             default:
                  break;
             }

             Val = work_num[1].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
             switch (Val)
             {
             case 0:
                  bit_Cal(33, 0x70, 0x50);bit_Cal(34, 0xF0, 0xF0);
                  break;
             case 1:
                  bit_Cal(33, 0x70, 0x50);bit_Cal(34, 0xF0, 0x00);
                  break;
             case 2:
                  bit_Cal(33, 0x70, 0x30);bit_Cal(34, 0xF0, 0xD0);
                  break;
             case 3:
                  bit_Cal(33, 0x70, 0x70);bit_Cal(34, 0xF0, 0x90);
                  break;
             case 4:
                  bit_Cal(33, 0x70, 0x70);bit_Cal(34, 0xF0, 0x20);
                  break;
             case 5:
                  bit_Cal(33, 0x70, 0x60);bit_Cal(34, 0xF0, 0xB0);
                  break;
             case 6:
                  bit_Cal(33, 0x70, 0x60);bit_Cal(34, 0xF0, 0xF0);
                  break;
             case 7:
                  bit_Cal(33, 0x70, 0x50);bit_Cal(34, 0xF0, 0x10);
                  break;
             case 8:
                  bit_Cal(33, 0x70, 0x70);bit_Cal(34, 0xF0, 0xF0);
                  break;
             case 9:
                  bit_Cal(33, 0x70, 0x70);bit_Cal(34, 0xF0, 0xB0);
                  break;
             default:
                  break;
             }

             Val = work_num[1].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
             switch (Val)
             {
             case 0:
                  bit_Cal(31, 0x70, 0x50);bit_Cal(32, 0xF0, 0xF0);
                  break;
             case 1:
                  bit_Cal(31, 0x70, 0x50);bit_Cal(32, 0xF0, 0x00);
                  break;
             case 2:
                  bit_Cal(31, 0x70, 0x30);bit_Cal(32, 0xF0, 0xD0);
                  break;
             case 3:
                  bit_Cal(31, 0x70, 0x70);bit_Cal(32, 0xF0, 0x90);
                  break;
             case 4:
                  bit_Cal(31, 0x70, 0x70);bit_Cal(32, 0xF0, 0x20);
                  break;
             case 5:
                  bit_Cal(31, 0x70, 0x60);bit_Cal(32, 0xF0, 0xB0);
                  break;
             case 6:
                  bit_Cal(31, 0x70, 0x60);bit_Cal(32, 0xF0, 0xF0);
                  break;
             case 7:
                  bit_Cal(31, 0x70, 0x50);bit_Cal(32, 0xF0, 0x10);
                  break;
             case 8:
                  bit_Cal(31, 0x70, 0x70);bit_Cal(32, 0xF0, 0xF0);
                  break;
             case 9:
                  bit_Cal(31, 0x70, 0x70);bit_Cal(32, 0xF0, 0xB0);
                  break;
             default:
                  break;
            }
        }
    }

     /**********��λ1��ʵ��ת����ʾ**********/
     if (work_num[0].Speed.Display_Rel > 999) // ����999ʱ
     {
        Val = work_num[0].Speed.Display_Rel / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(61, 0x7F, 0x77);
            break;
        case 1:
               bit_Cal(61, 0x7F, 0x24);
            break;
        case 2:
               bit_Cal(61, 0x7F, 0x5D);
            break;
        case 3:
               bit_Cal(61, 0x7F, 0x6D);
            break;
        case 4:
               bit_Cal(61, 0x7F, 0x2E);
            break;
        case 5:
               bit_Cal(61, 0x7F, 0x6B);
            break;
        case 6:
               bit_Cal(61, 0x7F, 0x7B);
            break;
        case 7:
               bit_Cal(61, 0x7F, 0x25);
            break;
        case 8:
               bit_Cal(61, 0x7F, 0x7F);
            break;
        case 9:
               bit_Cal(61, 0x7F, 0x6F);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(61, 0x7F, 0x77);
    }
    
   if (work_num[0].Speed.Display_Rel > 99) // ����99ʱ
   {
       Val = work_num[0].Speed.Display_Rel / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(59, 0x0E, 0x0A);bit_Cal(60, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(59, 0x0E, 0x0A);bit_Cal(60, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(59, 0x0E, 0x06);bit_Cal(60, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(59, 0x0E, 0x0E);bit_Cal(60, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(59, 0x0E, 0x0E);bit_Cal(60, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(59, 0x0E, 0x0C);bit_Cal(60, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(59, 0x0E, 0x0C);bit_Cal(60, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(59, 0x0E, 0x0A);bit_Cal(60, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(59, 0x0E, 0x0E);bit_Cal(60, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(59, 0x0E, 0x0E);bit_Cal(60, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(59, 0x0E, 0x0A);bit_Cal(60, 0x0F, 0x0F);
    }

   if (work_num[0].Speed.Display_Rel > 9) // ����9ʱ
   {
       Val = work_num[0].Speed.Display_Rel / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(57, 0x0E, 0x0A);bit_Cal(58, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(57, 0x0E, 0x0A);bit_Cal(58, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(57, 0x0E, 0x06);bit_Cal(58, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(57, 0x0E, 0x0E);bit_Cal(58, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(57, 0x0E, 0x0E);bit_Cal(58, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(57, 0x0E, 0x0C);bit_Cal(58, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(57, 0x0E, 0x0C);bit_Cal(58, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(57, 0x0E, 0x0A);bit_Cal(58, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(57, 0x0E, 0x0E);bit_Cal(58, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(57, 0x0E, 0x0E);bit_Cal(58, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(57, 0x0E, 0x0A);bit_Cal(58, 0x0F, 0x0F);
    }
   
   if (work_num[0].Speed.Display_Rel>= 0) // ���ڵ���0ʱ
   {
       Val = work_num[0].Speed.Display_Rel % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(55, 0x0E, 0x0A);bit_Cal(56, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(55, 0x0E, 0x0A);bit_Cal(56, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(55, 0x0E, 0x06);bit_Cal(56, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(55, 0x0E, 0x0E);bit_Cal(56, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(55, 0x0E, 0x0E);bit_Cal(56, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(55, 0x0E, 0x0C);bit_Cal(56, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(55, 0x0E, 0x0C);bit_Cal(56, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(55, 0x0E, 0x0A);bit_Cal(56, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(55, 0x0E, 0x0E);bit_Cal(56, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(55, 0x0E, 0x0E);bit_Cal(56, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    /**********��λ2���趨ת����ʾ**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//����ʾ�趨ת��
    {
        bit_Cal(53, 0x0E, 0x00);bit_Cal(54, 0x0F, 0x00);//��һλ����ʾ
        bit_Cal(51, 0x0E, 0x00);bit_Cal(52, 0x0F, 0x00);//�ڶ�λ����ʾ
        bit_Cal(49, 0x0E, 0x00);bit_Cal(50, 0x0F, 0x00);//����λ����ʾ
        bit_Cal(47, 0x0E, 0x00);bit_Cal(48, 0x0F, 0x00);//����λ����ʾ
    }
    else
    {
        if(work_num[0].Speed.Display_Set == 0)//��ʾ�� -- ��
        {
            bit_Cal(53, 0x0E, 0x04);bit_Cal(54, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(51, 0x0E, 0x04);bit_Cal(52, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(49, 0x0E, 0x04);bit_Cal(50, 0x0F, 0x00);//��ʾ��-��
            bit_Cal(47, 0x0E, 0x04);bit_Cal(48, 0x0F, 0x00);//��ʾ��-��
        }
        else
        {
             if (work_num[0].Speed.Display_Set > 999) // ����999ʱ
             {
                Val = work_num[0].Speed.Display_Set / 1000 % 10;
                switch (Val)
                {
                case 0:
                       bit_Cal(53, 0x0E, 0x0A);bit_Cal(54, 0x0F, 0x0F);
                    break;
                case 1:
                       bit_Cal(53, 0x0E, 0x0A);bit_Cal(54, 0x0F, 0x00);
                    break;
                case 2:
                       bit_Cal(53, 0x0E, 0x06);bit_Cal(54, 0x0F, 0x0D);
                    break;
                case 3:
                       bit_Cal(53, 0x0E, 0x0E);bit_Cal(54, 0x0F, 0x09);
                    break;
                case 4:
                       bit_Cal(53, 0x0E, 0x0E);bit_Cal(54, 0x0F, 0x02);
                    break;
                case 5:
                       bit_Cal(53, 0x0E, 0x0C);bit_Cal(54, 0x0F, 0x0B);
                    break;
                case 6:
                       bit_Cal(53, 0x0E, 0x0C);bit_Cal(54, 0x0F, 0x0F);
                    break;
                case 7:
                       bit_Cal(53, 0x0E, 0x0A);bit_Cal(54, 0x0F, 0x01);
                    break;
                case 8:
                       bit_Cal(53, 0x0E, 0x0E);bit_Cal(54, 0x0F, 0x0F);
                    break;
                case 9:
                       bit_Cal(53, 0x0E, 0x0E);bit_Cal(54, 0x0F, 0x0B);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(53, 0x0E, 0x0A);bit_Cal(54, 0x0F, 0x0F);
            }
            
           if (work_num[0].Speed.Display_Set > 99) // ����99ʱ
           {
               Val = work_num[0].Speed.Display_Set / 100 % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(51, 0x0E, 0x0A);bit_Cal(52, 0x0F, 0x0F);
                    break;
                case 1:
                       bit_Cal(51, 0x0E, 0x0A);bit_Cal(52, 0x0F, 0x00);
                    break;
                case 2:
                       bit_Cal(51, 0x0E, 0x06);bit_Cal(52, 0x0F, 0x0D);
                    break;
                case 3:
                       bit_Cal(51, 0x0E, 0x0E);bit_Cal(52, 0x0F, 0x09);
                    break;
                case 4:
                       bit_Cal(51, 0x0E, 0x0E);bit_Cal(52, 0x0F, 0x02);
                    break;
                case 5:
                       bit_Cal(51, 0x0E, 0x0C);bit_Cal(52, 0x0F, 0x0B);
                    break;
                case 6:
                       bit_Cal(51, 0x0E, 0x0C);bit_Cal(52, 0x0F, 0x0F);
                    break;
                case 7:
                       bit_Cal(51, 0x0E, 0x0A);bit_Cal(52, 0x0F, 0x01);
                    break;
                case 8:
                       bit_Cal(51, 0x0E, 0x0E);bit_Cal(52, 0x0F, 0x0F);
                    break;
                case 9:
                       bit_Cal(51, 0x0E, 0x0E);bit_Cal(52, 0x0F, 0x0B);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(51, 0x0E, 0x0A);bit_Cal(52, 0x0F, 0x0F);
            }

           if (work_num[0].Speed.Display_Set > 9) // ����9ʱ
           {
               Val = work_num[0].Speed.Display_Set / 10 % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(49, 0x0E, 0x0A);bit_Cal(50, 0x0F, 0x0F);
                    break;
                case 1:
                       bit_Cal(49, 0x0E, 0x0A);bit_Cal(50, 0x0F, 0x00);
                    break;
                case 2:
                       bit_Cal(49, 0x0E, 0x06);bit_Cal(50, 0x0F, 0x0D);
                    break;
                case 3:
                       bit_Cal(49, 0x0E, 0x0E);bit_Cal(50, 0x0F, 0x09);
                    break;
                case 4:
                       bit_Cal(49, 0x0E, 0x0E);bit_Cal(50, 0x0F, 0x02);
                    break;
                case 5:
                       bit_Cal(49, 0x0E, 0x0C);bit_Cal(50, 0x0F, 0x0B);
                    break;
                case 6:
                       bit_Cal(49, 0x0E, 0x0C);bit_Cal(50, 0x0F, 0x0F);
                    break;
                case 7:
                       bit_Cal(49, 0x0E, 0x0A);bit_Cal(50, 0x0F, 0x01);
                    break;
                case 8:
                       bit_Cal(49, 0x0E, 0x0E);bit_Cal(50, 0x0F, 0x0F);
                    break;
                case 9:
                       bit_Cal(49, 0x0E, 0x0E);bit_Cal(50, 0x0F, 0x0B);
                    break;
                default:
                   break;
                }
            }
            else
            {
                bit_Cal(49, 0x0E, 0x0A);bit_Cal(50, 0x0F, 0x0F);
            }
           
           if (work_num[0].Speed.Display_Set>= 0) // ���ڵ���0ʱ
           {
               Val = work_num[0].Speed.Display_Set % 10;
               switch (Val)
                {
                case 0:
                       bit_Cal(47, 0x0E, 0x0A);bit_Cal(48, 0x0F, 0x0F);
                    break;
                case 1:
                       bit_Cal(47, 0x0E, 0x0A);bit_Cal(48, 0x0F, 0x00);
                    break;
                case 2:
                       bit_Cal(47, 0x0E, 0x06);bit_Cal(48, 0x0F, 0x0D);
                    break;
                case 3:
                       bit_Cal(47, 0x0E, 0x0E);bit_Cal(48, 0x0F, 0x09);
                    break;
                case 4:
                       bit_Cal(47, 0x0E, 0x0E);bit_Cal(48, 0x0F, 0x02);
                    break;
                case 5:
                       bit_Cal(47, 0x0E, 0x0C);bit_Cal(48, 0x0F, 0x0B);
                    break;
                case 6:
                       bit_Cal(47, 0x0E, 0x0C);bit_Cal(48, 0x0F, 0x0F);
                    break;
                case 7:
                       bit_Cal(47, 0x0E, 0x0A);bit_Cal(48, 0x0F, 0x01);
                    break;
                case 8:
                       bit_Cal(47, 0x0E, 0x0E);bit_Cal(48, 0x0F, 0x0F);
                    break;
                case 9:
                       bit_Cal(47, 0x0E, 0x0E);bit_Cal(48, 0x0F, 0x0B);
                    break;
                default:
                   break;
                }
             }
         }
     }

     /**********��λ2��ʵ��ʱ����ʾ**********/
    if(work_num[0].Time.Rel == 0)
    {
        bit_Cal(53, 0x81, 0x00);bit_Cal(55, 0x81, 0x01);bit_Cal(57, 0x81, 0x00);bit_Cal(59, 0x01, 0x00);//��ʾ��-��
        bit_Cal(59, 0x70, 0x20);bit_Cal(60, 0xF0, 0x00);//��ʾ��-��
        bit_Cal(57, 0x70, 0x20);bit_Cal(58, 0xF0, 0x00);//��ʾ��-��
        bit_Cal(55, 0x70, 0x20);bit_Cal(56, 0xF0, 0x00);//��ʾ��-��
    }
    else
    {
         Val = work_num[0].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
         switch (Val)
         {
         case 0:
              bit_Cal(53, 0x81, 0x81);bit_Cal(55, 0x81, 0x80);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
              break;
         case 1:
              bit_Cal(53, 0x81, 0x00);bit_Cal(55, 0x81, 0x00);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x00);
              break;
         case 2:
              bit_Cal(53, 0x81, 0x80);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x01);bit_Cal(59, 0x01, 0x01);
              break;
         case 3:
              bit_Cal(53, 0x81, 0x00);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
              break;
         case 4:
              bit_Cal(53, 0x81, 0x01);bit_Cal(55, 0x81, 0x01);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x00);
              break;
         case 5:
              bit_Cal(53, 0x81, 0x01);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x80);bit_Cal(59, 0x01, 0x01);
              break;
         case 6:
              bit_Cal(53, 0x81, 0x81);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x80);bit_Cal(59, 0x01, 0x01);
              break;
         case 7:
              bit_Cal(53, 0x81, 0x00);bit_Cal(55, 0x81, 0x00);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
              break;
         case 8:
              bit_Cal(53, 0x81, 0x81);bit_Cal(55, 0x81, 0x80);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
              break;
         case 9:
              bit_Cal(53, 0x81, 0x01);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
              break;
         default:
              break;
         }

         Val = work_num[0].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
         switch (Val)
         {
         case 0:
              bit_Cal(59, 0x70, 0x50);bit_Cal(60, 0xF0, 0xF0);
              break;
         case 1:
              bit_Cal(59, 0x70, 0x50);bit_Cal(60, 0xF0, 0x00);
              break;
         case 2:
              bit_Cal(59, 0x70, 0x30);bit_Cal(60, 0xF0, 0xD0);
              break;
         case 3:
              bit_Cal(59, 0x70, 0x70);bit_Cal(60, 0xF0, 0x90);
              break;
         case 4:
              bit_Cal(59, 0x70, 0x70);bit_Cal(60, 0xF0, 0x20);
              break;
         case 5:
              bit_Cal(59, 0x70, 0x60);bit_Cal(60, 0xF0, 0xB0);
              break;
         case 6:
              bit_Cal(59, 0x70, 0x60);bit_Cal(60, 0xF0, 0xF0);
              break;
         case 7:
              bit_Cal(59, 0x70, 0x50);bit_Cal(60, 0xF0, 0x10);
              break;
         case 8:
              bit_Cal(59, 0x70, 0x70);bit_Cal(60, 0xF0, 0xF0);
              break;
         case 9:
              bit_Cal(59, 0x70, 0x70);bit_Cal(60, 0xF0, 0xB0);
              break;
         default:
              break;
         }

         Val = work_num[0].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
         switch (Val)
         {
         case 0:
              bit_Cal(57, 0x70, 0x50);bit_Cal(58, 0xF0, 0xF0);
              break;
         case 1:
              bit_Cal(57, 0x70, 0x50);bit_Cal(58, 0xF0, 0x00);
              break;
         case 2:
              bit_Cal(57, 0x70, 0x30);bit_Cal(58, 0xF0, 0xD0);
              break;
         case 3:
              bit_Cal(57, 0x70, 0x70);bit_Cal(58, 0xF0, 0x90);
              break;
         case 4:
              bit_Cal(57, 0x70, 0x70);bit_Cal(58, 0xF0, 0x20);
              break;
         case 5:
              bit_Cal(57, 0x70, 0x60);bit_Cal(58, 0xF0, 0xB0);
              break;
         case 6:
              bit_Cal(57, 0x70, 0x60);bit_Cal(58, 0xF0, 0xF0);
              break;
         case 7:
              bit_Cal(57, 0x70, 0x50);bit_Cal(58, 0xF0, 0x10);
              break;
         case 8:
              bit_Cal(57, 0x70, 0x70);bit_Cal(58, 0xF0, 0xF0);
              break;
         case 9:
              bit_Cal(57, 0x70, 0x70);bit_Cal(58, 0xF0, 0xB0);
              break;
         default:
              break;
         }

         Val = work_num[0].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
         switch (Val)
         {
         case 0:
              bit_Cal(55, 0x70, 0x50);bit_Cal(56, 0xF0, 0xF0);
              break;
         case 1:
              bit_Cal(55, 0x70, 0x50);bit_Cal(56, 0xF0, 0x00);
              break;
         case 2:
              bit_Cal(55, 0x70, 0x30);bit_Cal(56, 0xF0, 0xD0);
              break;
         case 3:
              bit_Cal(55, 0x70, 0x70);bit_Cal(56, 0xF0, 0x90);
              break;
         case 4:
              bit_Cal(55, 0x70, 0x70);bit_Cal(56, 0xF0, 0x20);
              break;
         case 5:
              bit_Cal(55, 0x70, 0x60);bit_Cal(56, 0xF0, 0xB0);
              break;
         case 6:
              bit_Cal(55, 0x70, 0x60);bit_Cal(56, 0xF0, 0xF0);
              break;
         case 7:
              bit_Cal(55, 0x70, 0x50);bit_Cal(56, 0xF0, 0x10);
              break;
         case 8:
              bit_Cal(55, 0x70, 0x70);bit_Cal(56, 0xF0, 0xF0);
              break;
         case 9:
              bit_Cal(55, 0x70, 0x70);bit_Cal(56, 0xF0, 0xB0);
              break;
         default:
              break;
         }
    }

     /**********��λ1���趨ʱ����ʾ**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//����ʾ�趨ת��
    {
        bit_Cal(53, 0x70, 0x00);bit_Cal(54, 0xF0, 0x00);//��һλ����ʾ
        bit_Cal(51, 0x70, 0x00);bit_Cal(52, 0xF0, 0x00);//�ڶ�λ����ʾ
        bit_Cal(49, 0x70, 0x00);bit_Cal(50, 0xF0, 0x00);//����λ����ʾ
        bit_Cal(47, 0x70, 0x00);bit_Cal(48, 0xF0, 0x00);//����λ����ʾ
    }
    else
    {
        if(work_num[0].Time.Set == 0)
        {
            bit_Cal(53, 0x70, 0x20);bit_Cal(54, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(51, 0x70, 0x20);bit_Cal(52, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(49, 0x70, 0x20);bit_Cal(50, 0xF0, 0x00);//��ʾ��-��
            bit_Cal(47, 0x70, 0x20);bit_Cal(48, 0xF0, 0x00);//��ʾ��-��
        }
        else
        {
             Val = work_num[0].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
             switch (Val)
             {
             case 0:
                  bit_Cal(53, 0x70, 0x50);bit_Cal(54, 0xF0, 0xF0);
                  break;
             case 1:
                  bit_Cal(53, 0x70, 0x50);bit_Cal(54, 0xF0, 0x00);
                  break;
             case 2:
                  bit_Cal(53, 0x70, 0x30);bit_Cal(54, 0xF0, 0xD0);
                  break;
             case 3:
                  bit_Cal(53, 0x70, 0x70);bit_Cal(54, 0xF0, 0x90);
                  break;
             case 4:
                  bit_Cal(53, 0x70, 0x70);bit_Cal(54, 0xF0, 0x20);
                  break;
             case 5:
                  bit_Cal(53, 0x70, 0x60);bit_Cal(54, 0xF0, 0xB0);
                  break;
             case 6:
                  bit_Cal(53, 0x70, 0x60);bit_Cal(54, 0xF0, 0xF0);
                  break;
             case 7:
                  bit_Cal(53, 0x70, 0x50);bit_Cal(54, 0xF0, 0x10);
                  break;
             case 8:
                  bit_Cal(53, 0x70, 0x70);bit_Cal(54, 0xF0, 0xF0);
                  break;
             case 9:
                  bit_Cal(53, 0x70, 0x70);bit_Cal(54, 0xF0, 0xB0);
                  break;
             default:
                  break;
             }

             Val = work_num[0].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
             switch (Val)
             {
             case 0:
                  bit_Cal(51, 0x70, 0x50);bit_Cal(52, 0xF0, 0xF0);
                  break;
             case 1:
                  bit_Cal(51, 0x70, 0x50);bit_Cal(52, 0xF0, 0x00);
                  break;
             case 2:
                  bit_Cal(51, 0x70, 0x30);bit_Cal(52, 0xF0, 0xD0);
                  break;
             case 3:
                  bit_Cal(51, 0x70, 0x70);bit_Cal(52, 0xF0, 0x90);
                  break;
             case 4:
                  bit_Cal(51, 0x70, 0x70);bit_Cal(52, 0xF0, 0x20);
                  break;
             case 5:
                  bit_Cal(51, 0x70, 0x60);bit_Cal(52, 0xF0, 0xB0);
                  break;
             case 6:
                  bit_Cal(51, 0x70, 0x60);bit_Cal(52, 0xF0, 0xF0);
                  break;
             case 7:
                  bit_Cal(51, 0x70, 0x50);bit_Cal(52, 0xF0, 0x10);
                  break;
             case 8:
                  bit_Cal(51, 0x70, 0x70);bit_Cal(52, 0xF0, 0xF0);
                  break;
             case 9:
                  bit_Cal(51, 0x70, 0x70);bit_Cal(52, 0xF0, 0xB0);
                  break;
             default:
                  break;
             }

             Val = work_num[0].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
             switch (Val)
             {
             case 0:
                  bit_Cal(49, 0x70, 0x50);bit_Cal(50, 0xF0, 0xF0);
                  break;
             case 1:
                  bit_Cal(49, 0x70, 0x50);bit_Cal(50, 0xF0, 0x00);
                  break;
             case 2:
                  bit_Cal(49, 0x70, 0x30);bit_Cal(50, 0xF0, 0xD0);
                  break;
             case 3:
                  bit_Cal(49, 0x70, 0x70);bit_Cal(50, 0xF0, 0x90);
                  break;
             case 4:
                  bit_Cal(49, 0x70, 0x70);bit_Cal(50, 0xF0, 0x20);
                  break;
             case 5:
                  bit_Cal(49, 0x70, 0x60);bit_Cal(50, 0xF0, 0xB0);
                  break;
             case 6:
                  bit_Cal(49, 0x70, 0x60);bit_Cal(50, 0xF0, 0xF0);
                  break;
             case 7:
                  bit_Cal(49, 0x70, 0x50);bit_Cal(50, 0xF0, 0x10);
                  break;
             case 8:
                  bit_Cal(49, 0x70, 0x70);bit_Cal(50, 0xF0, 0xF0);
                  break;
             case 9:
                  bit_Cal(49, 0x70, 0x70);bit_Cal(50, 0xF0, 0xB0);
                  break;
             default:
                  break;
             }

             Val = work_num[0].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
             switch (Val)
             {
             case 0:
                  bit_Cal(47, 0x70, 0x50);bit_Cal(48, 0xF0, 0xF0);
                  break;
             case 1:
                  bit_Cal(47, 0x70, 0x50);bit_Cal(48, 0xF0, 0x00);
                  break;
             case 2:
                  bit_Cal(47, 0x70, 0x30);bit_Cal(48, 0xF0, 0xD0);
                  break;
             case 3:
                  bit_Cal(47, 0x70, 0x70);bit_Cal(48, 0xF0, 0x90);
                  break;
             case 4:
                  bit_Cal(47, 0x70, 0x70);bit_Cal(48, 0xF0, 0x20);
                  break;
             case 5:
                  bit_Cal(47, 0x70, 0x60);bit_Cal(48, 0xF0, 0xB0);
                  break;
             case 6:
                  bit_Cal(47, 0x70, 0x60);bit_Cal(48, 0xF0, 0xF0);
                  break;
             case 7:
                  bit_Cal(47, 0x70, 0x50);bit_Cal(48, 0xF0, 0x10);
                  break;
             case 8:
                  bit_Cal(47, 0x70, 0x70);bit_Cal(48, 0xF0, 0xF0);
                  break;
             case 9:
                  bit_Cal(47, 0x70, 0x70);bit_Cal(48, 0xF0, 0xB0);
                  break;
             default:
                  break;
             }
         }
     }

     /*2�Ź�λʱ��ͼ�� */
    if(Work_Num[1].Time.Icon == 0)
    {
        bit_Cal(41, 0x80, 0x80);
    }
    else
    {
        bit_Cal(41, 0x80, 0x00);
    }

    /* 2�Ź�λת��ͼ�� */
    switch(Work_Num[1].Speed.IconStep)
	{
		case 0: bit_Cal(43, 0x01, 0x01);
                 bit_Cal(45, 0x01, 0x01);
                 bit_Cal(45, 0x80, 0x80);
			break;
		case 1: bit_Cal(43, 0x01, 0x00);
                 bit_Cal(45, 0x01, 0x01);
                 bit_Cal(45, 0x80, 0x80);
			break;
		case 2: bit_Cal(43, 0x01, 0x01);
                 bit_Cal(45, 0x01, 0x01);
                 bit_Cal(45, 0x80, 0x00);
			break;
		case 3: bit_Cal(43, 0x01, 0x01);
                 bit_Cal(45, 0x01, 0x00);
                 bit_Cal(45, 0x80, 0x80);
			break;
		default:
			break;
	}

     /*1�Ź�λʱ��ͼ�� */
    if(Work_Num[0].Time.Icon == 0)
    {
        bit_Cal(51, 0x01, 0x01);
    }
    else
    {
        bit_Cal(51, 0x01, 0x00);
    }

    /* 1�Ź�λת��ͼ�� */
    switch(Work_Num[0].Speed.IconStep)
	{
		case 0: bit_Cal(49, 0x01, 0x01);
                 bit_Cal(61, 0x80, 0x80);
                 bit_Cal(49, 0x80, 0x80);
			break;
		case 1: bit_Cal(49, 0x01, 0x00);
                 bit_Cal(61, 0x80, 0x80);
                 bit_Cal(49, 0x80, 0x80);
			break;
		case 2: bit_Cal(49, 0x01, 0x01);
                 bit_Cal(61, 0x80, 0x00);
                 bit_Cal(49, 0x80, 0x80);
			break;
		case 3: bit_Cal(49, 0x01, 0x01);
                 bit_Cal(61, 0x80, 0x80);
                 bit_Cal(49, 0x80, 0x00);
			break;
		default:
			break;
	}
    
    /* 1�Ź�λ2�Ź�λ֮������ */
    if(sys.New_Work == 0 || sys.New_Work == 1)//�����ǰ��λ��1����2�Ź�λ
    {
        /**********����������ʾ**********/
        bit_Cal(41, 0x01, 0x01);
    }
    else
    {
        bit_Cal(41, 0x01, 0x00);
    }
    
     /**********��λ2'RPM'��ʾ**********/
     bit_Cal(31, 0x01, 0x01);

     /**********��λ2'min'��ʾ**********/
     bit_Cal(31, 0x80, 0x80);

     /**********��λ2�趨ʱ��'��'��ʾ**********/
     bit_Cal(35, 0x80, 0x80);
    
     /**********��λ2ʵ��ʱ��'��'��ʾ**********/
     bit_Cal(43, 0x80, 0x80);

     /**********��λ1'RPM'��ʾ**********/
     bit_Cal(47, 0x01, 0x01);

     /**********��λ1'min'��ʾ**********/
     bit_Cal(47, 0x80, 0x80);

     /**********��λ1�趨ʱ��'��'��ʾ**********/
     bit_Cal(51, 0x80, 0x80);
     
     /**********��λ1ʵ��ʱ��'��'��ʾ**********/
     bit_Cal(59, 0x80, 0x80);

     

     /**********���ݷ���**********/
     for(uint8_t i=0;i<31;i++)
     {
          Write_Addr_Dat_N(IC1, i*2, seg[i], 1);
     }
     for(uint8_t i=0;i<31;i++)
     {
          Write_Addr_Dat_N(IC2, i*2, seg[i+31], 1);
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
    for(uint8_t i = 0;i<4;i++)
    {
        Work_Num[i].Speed.Display_Set = Work_Num[i].Speed.Set;
        Deal_Speed(i);
        Work_Num[i].Time.Display_Set = Work_Num[i].Time.Set;
        Work_Num[i].Time.Display_Rel = Work_Num[i].Time.Rel;
    }
     Display_IC(Work_Num);
}
