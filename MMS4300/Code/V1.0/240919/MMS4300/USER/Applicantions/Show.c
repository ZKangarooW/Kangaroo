#include "Show.h"

/**********ȫ�ֱ���**********/
float Twinkle_Time; // ��˸ʱ��

/**********�ֲ���������*******/
uint8_t Speed_ShowFlag, Time_ShowFlag, Sync_ShowFlag;//�ٶȡ��¶ȡ�ʱ����ʾ�ı�־λ��0��������1��Ϩ��

/**
 * @brief ��˸����
 *
 * @param dT ��������
 */
void Twinkle(float dT)
{

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

     /**********��λ4��ʵ��ʱ����ʾ**********/
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

     /**********��λ4���趨ʱ����ʾ**********/
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

    /**********��λ3��ʵ��ʱ����ʾ**********/
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

     /**********��λ3���趨ʱ����ʾ**********/
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

     /**********��λ4'RPM'��ʾ**********/
     bit_Cal(0, 0x80, 0x80);

     /**********��λ4'min'��ʾ**********/
     bit_Cal(0, 0x01, 0x01);

     /**********��λ4�趨ʱ��'��'��ʾ**********/
     bit_Cal(4, 0x01, 0x01);

     /**********�ұߺ����ʾ**********/
     bit_Cal(6, 0x80, 0x80);

     /**********�м���ͼ����ʾ**********/
     bit_Cal(6, 0x01, 0x01);

     /**********��λ4ת��ͼ��S19��ʾ**********/
     bit_Cal(10, 0x80, 0x80);

     /**********��λ4ת��ͼ��S20��ʾ**********/
     bit_Cal(8, 0x80, 0x80);

     /**********��λ4ת��ͼ��S21��ʾ**********/
     bit_Cal(8, 0x01, 0x01);

     /**********��ߺ����ʾ**********/
     bit_Cal(10, 0x01, 0x01);

     /**********����������ʾ**********/
     bit_Cal(12, 0x80, 0x80);

     /**********��λ4ʵ��ʱ��'��'��ʾ**********/
     bit_Cal(12, 0x01, 0x01);

     /**********ʱ��ͼ����ʾ**********/
     bit_Cal(14, 0x80, 0x80);

     /**********��λ3'RPM'��ʾ**********/
     bit_Cal(16, 0x80, 0x80);

     /**********��λ3'min'��ʾ**********/
     bit_Cal(16, 0x01, 0x01); 

     /**********��λ3ת��ͼ��S12��ʾ**********/
     bit_Cal(19, 0x80, 0x80);

     /**********��λ3ת��ͼ��S10��ʾ**********/
     bit_Cal(30, 0x80, 0x80);

     /**********��λ3ת��ͼ��S0��ʾ**********/
     bit_Cal(30, 0x01, 0x01);

     /**********��λ4�趨ʱ��'��'��ʾ**********/
     bit_Cal(19, 0x01, 0x01);

     /**********ʱ��ͼ����ʾ**********/
     bit_Cal(27, 0x80, 0x80);

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

     /**********��λ2��ʵ��ʱ����ʾ**********/
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

     /**********��λ2���趨ʱ����ʾ**********/
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

     /**********��λ2��ʵ��ʱ����ʾ**********/
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

     /**********��λ2���趨ʱ����ʾ**********/
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

     /**********��λ2'RPM'��ʾ**********/
     bit_Cal(31, 0x01, 0x01);

     /**********��λ2'min'��ʾ**********/
     bit_Cal(31, 0x80, 0x80);

     /**********��λ2�趨ʱ��'��'��ʾ**********/
     bit_Cal(35, 0x80, 0x80);

     /**********ʱ��ͼ����ʾ**********/
     bit_Cal(41, 0x80, 0x80);

     /**********��λ2ת��ͼ��S28��ʾ**********/
     bit_Cal(43, 0x01, 0x01);

     /**********��λ2ת��ͼ��S30��ʾ**********/
     bit_Cal(45, 0x01, 0x01);

     /**********��λ2ת��ͼ��S29��ʾ**********/
     bit_Cal(45, 0x80, 0x80);

     /**********��λ2ʵ��ʱ��'��'��ʾ**********/
     bit_Cal(43, 0x80, 0x80);


     /**********��λ1'RPM'��ʾ**********/
     bit_Cal(47, 0x01, 0x01);

     /**********��λ1'min'��ʾ**********/
     bit_Cal(47, 0x80, 0x80);

     /**********��λ1�趨ʱ��'��'��ʾ**********/
     bit_Cal(51, 0x80, 0x80);

     /**********ʱ��ͼ����ʾ**********/
     bit_Cal(51, 0x01, 0x01);

     /**********��λ1ת��ͼ��S1��ʾ**********/
     bit_Cal(49, 0x01, 0x01);

     /**********��λ1ת��ͼ��S2��ʾ**********/
     bit_Cal(61, 0x80, 0x80);

     /**********��λ1ת��ͼ��3��ʾ**********/
     bit_Cal(49, 0x80, 0x80);

     /**********��λ1ʵ��ʱ��'��'��ʾ**********/
     bit_Cal(59, 0x80, 0x80);


     /**********����������ʾ**********/
     bit_Cal(41, 0x01, 0x01);

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

/**
 * @brief ��ʾ��Ļ����
 *
 */
void Show_Display(void)
{
     Work_Num[3].Speed.Display_Rel = sys.val;
     Work_Num[3].Speed.Display_Set = sys.val;
     Work_Num[3].Time.Display_Rel = sys.val1;
     Work_Num[3].Time.Display_Set = sys.val1;
     Work_Num[2].Speed.Display_Rel = sys.val;
     Work_Num[2].Speed.Display_Set = sys.val;
     Work_Num[2].Time.Display_Rel = sys.val1;
     Work_Num[2].Time.Display_Set = sys.val1;
     Work_Num[1].Speed.Display_Rel = sys.val;
     Work_Num[1].Speed.Display_Set = sys.val;
     Work_Num[1].Time.Display_Rel = sys.val1;
     Work_Num[1].Time.Display_Set = sys.val1;
      Work_Num[0].Speed.Display_Rel = sys.val;
     Work_Num[0].Speed.Display_Set = sys.val;
     Work_Num[0].Time.Display_Rel = sys.val1;
     Work_Num[0].Time.Display_Set = sys.val1;
     Display_IC(Work_Num);
}
