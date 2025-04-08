#include "Show.h"

/**********ȫ�ֱ���**********/
float Twinkle_Time; // ��˸ʱ��

/**********�ֲ���������*******/
uint8_t Pmode_ShowFlag, Temp_ShowFlag, Speed_ShowFlag, Time_ShowFlag;                      // Pģʽ��ʱ�䡢�ٶȡ��¶���ʾ�ı�־λ��0��������1��Ϩ��
uint8_t PModeP1_ShowFlag, PModeP2_ShowFlag;                                                // P1��P2��˸
uint8_t Icn_Falg, TimeIcn_Flag, BaseIcn_Flag;                                          // �¶ȡ�ʱ�䡢����ͼ����ʾ�ı�־λ

/**
 * @brief ��˸����
 *
 * @param dT ��������
 */
void Twinkle(float dT)
{
    
}

uint8_t seg[80] = {0};

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

/**
 * @brief ��ʾ�¶�
 *
 * @param dis_set_temp �趨�¶�
 * @param dis_rel_temp ʵ���¶�
 */
void Display_IC2( _Work_Num_ work_num[])
{
    uint8_t Val;// ���ڰ�ʮ��ȡ����������

    /*******************************1�Ź�λ*******************************/
    /**********��λ1��ʵ��ת����ʾ**********/
    if (work_num[0].Speed.Display_Rel > 999) // ����999ʱ
    {
        Val = work_num[0].Speed.Display_Rel / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(2, 0x01, 0x00);bit_Cal(3, 0x01, 0x01);//��ʾ����1
        }
       else
       {
            bit_Cal(2, 0x01, 0x01);bit_Cal(3, 0x01, 0x01);//��ʾ����0
       }
    }
    else
    {
        bit_Cal(2, 0x01, 0x01);bit_Cal(3, 0x01, 0x01);//��ʾ����0
    }
    
   if (work_num[0].Speed.Display_Rel > 99) // ����99ʱ
   {
       Val = work_num[0].Speed.Display_Rel / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(4, 0x03, 0x03);bit_Cal(5, 0x07, 0x05);bit_Cal(6, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(4, 0x03, 0x00);bit_Cal(5, 0x07, 0x00);bit_Cal(6, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(4, 0x03, 0x02);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(4, 0x03, 0x00);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(4, 0x03, 0x01);bit_Cal(5, 0x07, 0x02);bit_Cal(6, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(4, 0x03, 0x01);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(4, 0x03, 0x03);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(4, 0x03, 0x00);bit_Cal(5, 0x07, 0x01);bit_Cal(6, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(4, 0x03, 0x03);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(4, 0x03, 0x01);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(4, 0x03, 0x03);bit_Cal(5, 0x07, 0x05);bit_Cal(6, 0x03, 0x03);//��ʾ������
   }

   if (work_num[0].Speed.Display_Rel > 9) // ����9ʱ
   {
       Val = work_num[0].Speed.Display_Rel / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(7, 0x03, 0x03);bit_Cal(8, 0x07, 0x05);bit_Cal(9, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(7, 0x03, 0x00);bit_Cal(8, 0x07, 0x00);bit_Cal(9, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(7, 0x03, 0x02);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(7, 0x03, 0x00);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(7, 0x03, 0x01);bit_Cal(8, 0x07, 0x02);bit_Cal(9, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(7, 0x03, 0x01);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(7, 0x03, 0x03);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(7, 0x03, 0x00);bit_Cal(8, 0x07, 0x01);bit_Cal(9, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(7, 0x03, 0x03);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(7, 0x03, 0x01);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(7, 0x03, 0x03);bit_Cal(8, 0x07, 0x05);bit_Cal(9, 0x03, 0x03);//��ʾ������
   }
    bit_Cal(10, 0x01, 0x01);//ʵ��ת�ٸ�λֻ����ʾ��

    /**********��λ1���趨ת����ʾ**********/
    if (work_num[0].Speed.Display_Set > 999) // ����999ʱ
    {
        Val = work_num[0].Speed.Display_Set / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(11, 0x01, 0x00);bit_Cal(12, 0x01, 0x01);//��ʾ����1
        }
       else
       {
            bit_Cal(11, 0x01, 0x01);bit_Cal(12, 0x01, 0x01);//��ʾ����0
       }
    }
    else
    {
        bit_Cal(11, 0x01, 0x01);bit_Cal(12, 0x01, 0x01);//��ʾ����0
    }
    
   if (work_num[0].Speed.Display_Set > 99) // ����99ʱ
   {
       Val = work_num[0].Speed.Display_Set / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(13, 0x03, 0x03);bit_Cal(14, 0x07, 0x05);bit_Cal(15, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(13, 0x03, 0x00);bit_Cal(14, 0x07, 0x00);bit_Cal(15, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(13, 0x03, 0x02);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(13, 0x03, 0x00);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(13, 0x03, 0x01);bit_Cal(14, 0x07, 0x02);bit_Cal(15, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(13, 0x03, 0x01);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(13, 0x03, 0x03);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(13, 0x03, 0x00);bit_Cal(14, 0x07, 0x01);bit_Cal(15, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(13, 0x03, 0x03);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(13, 0x03, 0x01);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(13, 0x03, 0x03);bit_Cal(14, 0x07, 0x05);bit_Cal(15, 0x03, 0x03);//��ʾ������
   }

   if (work_num[0].Speed.Display_Set > 9) // ����9ʱ
   {
       Val = work_num[0].Speed.Display_Set / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(16, 0x03, 0x03);bit_Cal(17, 0x07, 0x05);bit_Cal(18, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(16, 0x03, 0x00);bit_Cal(17, 0x07, 0x00);bit_Cal(18, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(16, 0x03, 0x02);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(16, 0x03, 0x00);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(16, 0x03, 0x01);bit_Cal(17, 0x07, 0x02);bit_Cal(18, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(16, 0x03, 0x01);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(16, 0x03, 0x03);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(16, 0x03, 0x00);bit_Cal(17, 0x07, 0x01);bit_Cal(18, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(16, 0x03, 0x03);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(16, 0x03, 0x01);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(16, 0x03, 0x03);bit_Cal(17, 0x07, 0x05);bit_Cal(18, 0x03, 0x03);//��ʾ������
   }
    bit_Cal(19, 0x01, 0x01);//ʵ��ת�ٸ�λֻ����ʾ��

    /**********��λ1��ʵ���¶���ʾ**********/
    if (work_num[0].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[0].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) / 1000 % 10;//�������0��������999���Բ�����ʾ
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = 10;//��ʾ��-��
    }
    switch (Val)
    {
        case 0:
            if (work_num[0].Temp.Display_Rel > 999)//��ʾ0
            {
                bit_Cal(0, 0x30, 0x30);bit_Cal(1, 0x1C, 0x14);bit_Cal(2, 0x0C, 0x0C);
            }
            else//����ʾ��λ
            {
                bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x00);bit_Cal(2, 0x0C, 0x00);
            }
            break;
        case 1:
            bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x00);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 2:
            bit_Cal(0, 0x30, 0x20);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x04);
            break;
        case 3:
            bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 4:
            bit_Cal(0, 0x30, 0x10);bit_Cal(1, 0x1C, 0x08);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 5:
            bit_Cal(0, 0x30, 0x10);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x08);
            break;
        case 6:
            bit_Cal(0, 0x30, 0x30);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x08);
            break;
        case 7:
            bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x04);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 8:
            bit_Cal(0, 0x30, 0x30);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 9:
            bit_Cal(0, 0x30, 0x10);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x0C);
            break;
        default:
            bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x08);bit_Cal(2, 0x0C, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[0].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[0].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = 10;//��ʾ��-��
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[0].Temp.Display_Rel > 99)//��ʾ��
            {
                bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x0A);bit_Cal(4, 0x1C, 0x1C);
            }
            else//����ʾ
            {
                bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x00);bit_Cal(4, 0x1C, 0x00);
            }
            break;
        case 1:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x00);bit_Cal(4, 0x1C, 0x0C);
            break;
        case 2:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x0E);bit_Cal(4, 0x1C, 0x14);
            break;
        case 3:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x06);bit_Cal(4, 0x1C, 0x1C);
            break;
        case 4:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x04);bit_Cal(4, 0x1C, 0x0C);
            break;
        case 5:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x06);bit_Cal(4, 0x1C, 0x18);
            break;
        case 6:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x0E);bit_Cal(4, 0x1C, 0x18);
            break;
        case 7:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x02);bit_Cal(4, 0x1C, 0x0C);
            break;
        case 8:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x0E);bit_Cal(4, 0x1C, 0x1C);
            break;
        case 9:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x06);bit_Cal(4, 0x1C, 0x1C);
            break;
        default:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x04);bit_Cal(4, 0x1C, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[0].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[0].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) / 10 % 10;
    }
    switch (Val)
    {
    case 0:
        bit_Cal(5, 0x18, 0x18);bit_Cal(6, 0x1C, 0x14);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 1:
        bit_Cal(5, 0x18, 0x00);bit_Cal(6, 0x1C, 0x00);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 2:
        bit_Cal(5, 0x18, 0x10);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x04);
        break;
    case 3:
        bit_Cal(5, 0x18, 0x00);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 4:
        bit_Cal(5, 0x18, 0x08);bit_Cal(6, 0x1C, 0x08);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 5:
        bit_Cal(5, 0x18, 0x08);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x08);
        break;
    case 6:
        bit_Cal(5, 0x18, 0x18);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x08);
        break;
    case 7:
        bit_Cal(5, 0x18, 0x00);bit_Cal(6, 0x1C, 0x04);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 8:
        bit_Cal(5, 0x18, 0x18);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 9:
        bit_Cal(5, 0x18, 0x08);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x0C);
        break;
    default:
        bit_Cal(5, 0x18, 0x00);bit_Cal(6, 0x1C, 0x08);bit_Cal(7, 0x0C, 0x00);//��ʾ��-��
        break;
    }

    if (work_num[0].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[0].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) % 10;
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(8, 0x38, 0x38);bit_Cal(9, 0x1C, 0x14);bit_Cal(10, 0x04, 0x04);
            break;
        case 1:
            bit_Cal(8, 0x38, 0x00);bit_Cal(9, 0x1C, 0x10);bit_Cal(10, 0x04, 0x04);
            break;
        case 2:
            bit_Cal(8, 0x38, 0x30);bit_Cal(9, 0x1C, 0x0C);bit_Cal(10, 0x04, 0x04);
            break;
        case 3:
            bit_Cal(8, 0x38, 0x20);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x04);
            break;
        case 4:
            bit_Cal(8, 0x38, 0x08);bit_Cal(9, 0x1C, 0x18);bit_Cal(10, 0x04, 0x04);
            break;
        case 5:
            bit_Cal(8, 0x38, 0x28);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x00);
            break;
        case 6:
            bit_Cal(8, 0x38, 0x38);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x00);
            break;
        case 7:
            bit_Cal(8, 0x38, 0x00);bit_Cal(9, 0x1C, 0x14);bit_Cal(10, 0x04, 0x04);
            break;
        case 8:
            bit_Cal(8, 0x38, 0x38);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x04);
            break;
        case 9:
            bit_Cal(8, 0x38, 0x28);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x04);
            break;
        default:
            bit_Cal(8, 0x38, 0x00);bit_Cal(9, 0x1C, 0x08);bit_Cal(10, 0x04, 0x00);//��ʾ��-��
            break;
    }

    /* 1�Ź�λʵ���¶�С���� */
    bit_Cal(7, 0x10, 0x10);

    /**********��λ1���趨�¶���ʾ**********/
    if (work_num[0].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[0].Temp.Display_Set / 1000 % 10;
    }
    else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Set) / 1000 % 10;//�������0��������999���Բ�����ʾ
    }
    else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
    {
        Val = 10;//��ʾ��-��
    }
    switch (Val)
    {
        case 0:
            if (work_num[0].Temp.Display_Set > 999)//��ʾ0
            {
                bit_Cal(10, 0x0A, 0x0A);bit_Cal(11, 0x0E, 0x0A);bit_Cal(12, 0x06, 0x06);
            }
            else//����ʾ��λ
            {
                bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x00);bit_Cal(12, 0x06, 0x00);
            }
            break;
        case 1:
            bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x00);bit_Cal(12, 0x06, 0x06);
            break;
        case 2:
            bit_Cal(10, 0x0A, 0x08);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x02);
            break;
        case 3:
            bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x06);
            break;
        case 4:
            bit_Cal(10, 0x0A, 0x02);bit_Cal(11, 0x0E, 0x04);bit_Cal(12, 0x06, 0x06);
            break;
        case 5:
            bit_Cal(10, 0x0A, 0x02);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x04);
            break;
        case 6:
            bit_Cal(10, 0x0A, 0x0A);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x04);
            break;
        case 7:
            bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x02);bit_Cal(12, 0x06, 0x06);
            break;
        case 8:
            bit_Cal(10, 0x0A, 0x0A);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x06);
            break;
        case 9:
            bit_Cal(10, 0x0A, 0x02);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x06);
            break;
        default:
            bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x04);bit_Cal(12, 0x06, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[0].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[0].Temp.Display_Set / 100 % 10;
    }
    else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
    {
        Val = 10;//��ʾ��-��
    }
    else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[0].Temp.Display_Set > 99)//��ʾ��
            {
                bit_Cal(12, 0x08, 0x08);bit_Cal(13, 0x1C, 0x14);bit_Cal(14, 0x38, 0x38);
            }
            else//����ʾ
            {
                bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x00);bit_Cal(14, 0x38, 0x00);
            }
            break;
        case 1:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x00);bit_Cal(14, 0x38, 0x30);
            break;
        case 2:
            bit_Cal(12, 0x08, 0x08);bit_Cal(13, 0x1C, 0x18);bit_Cal(14, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x18);bit_Cal(14, 0x38, 0x38);
            break;
        case 4:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x0C);bit_Cal(14, 0x38, 0x30);
            break;
        case 5:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x1C);bit_Cal(14, 0x38, 0x28);
            break;
        case 6:
            bit_Cal(12, 0x08, 0x08);bit_Cal(13, 0x1C, 0x1C);bit_Cal(14, 0x38, 0x28);
            break;
        case 7:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x00);bit_Cal(14, 0x38, 0x38);
            break;
        case 8:
            bit_Cal(12, 0x08, 0x08);bit_Cal(13, 0x1C, 0x1C);bit_Cal(14, 0x38, 0x38);
            break;
        case 9:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x1C);bit_Cal(14, 0x38, 0x38);
            break;
        default:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x08);bit_Cal(14, 0x38, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[0].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[0].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Set) / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Set) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(15, 0x1C, 0x1C);bit_Cal(16, 0x1C, 0x14);bit_Cal(17, 0x08, 0x08);
            break;
        case 1:
            bit_Cal(15, 0x1C, 0x00);bit_Cal(16, 0x1C, 0x10);bit_Cal(17, 0x08, 0x08);
            break;
        case 2:
            bit_Cal(15, 0x1C, 0x18);bit_Cal(16, 0x1C, 0x0C);bit_Cal(17, 0x08, 0x08);
            break;
        case 3:
            bit_Cal(15, 0x1C, 0x10);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x08);
            break;
        case 4:
            bit_Cal(15, 0x1C, 0x04);bit_Cal(16, 0x1C, 0x18);bit_Cal(17, 0x08, 0x08);
            break;
        case 5:
            bit_Cal(15, 0x1C, 0x14);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x00);
            break;
        case 6:
            bit_Cal(15, 0x1C, 0x1C);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x00);
            break;
        case 7:
            bit_Cal(15, 0x1C, 0x00);bit_Cal(16, 0x1C, 0x14);bit_Cal(17, 0x08, 0x08);
            break;
        case 8:
            bit_Cal(15, 0x1C, 0x1C);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x08);
            break;
        case 9:
            bit_Cal(15, 0x1C, 0x14);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x08);
            break;
        default:
            bit_Cal(15, 0x1C, 0x00);bit_Cal(16, 0x1C, 0x08);bit_Cal(17, 0x08, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[0].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[0].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Set) % 10;
    }
    else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Set) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(18, 0x3C, 0x3C);bit_Cal(19, 0x38, 0x28);
            break;
        case 1:
            bit_Cal(18, 0x3C, 0x00);bit_Cal(19, 0x38, 0x28);
            break;
        case 2:
            bit_Cal(18, 0x3C, 0x34);bit_Cal(19, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(18, 0x3C, 0x24);bit_Cal(19, 0x38, 0x38);
            break;
        case 4:
            bit_Cal(18, 0x3C, 0x08);bit_Cal(19, 0x38, 0x38);
            break;
        case 5:
            bit_Cal(18, 0x3C, 0x2C);bit_Cal(19, 0x38, 0x30);
            break;
        case 6:
            bit_Cal(18, 0x3C, 0x3C);bit_Cal(19, 0x38, 0x30);
            break;
        case 7:
            bit_Cal(18, 0x3C, 0x04);bit_Cal(19, 0x38, 0x28);
            break;
        case 8:
            bit_Cal(18, 0x3C, 0x3C);bit_Cal(19, 0x38, 0x38);
            break;
        case 9:
            bit_Cal(18, 0x3C, 0x2C);bit_Cal(19, 0x38, 0x38);
            break;
        default:
            bit_Cal(18, 0x3C, 0x00);bit_Cal(19, 0x38, 0x10);//��ʾ��-��
            break;
    }
    /* 1�Ź�λ�趨�¶�С���� */
    bit_Cal(17, 0x10, 0x10);

    /**********��λ1��ʵ��ʱ����ʾ**********/
    Val = work_num[0].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(1, 0xE0, 0x60);bit_Cal(2, 0xE0, 0xE0);
            break;
        case 1:
            bit_Cal(1, 0xE0, 0x00);bit_Cal(2, 0xE0, 0x60);
            break;
        case 2:
            bit_Cal(1, 0xE0, 0xA0);bit_Cal(2, 0xE0, 0xA0);
            break;
        default:
            bit_Cal(1, 0xE0, 0x80);bit_Cal(2, 0xE0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[0].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xD0);bit_Cal(4, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0x00);bit_Cal(4, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0x20);bit_Cal(4, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0x10);bit_Cal(4, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x60, 0x60);
            break;
        default:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0x20);bit_Cal(4, 0x60, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[0].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(5, 0xE0, 0xA0);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(5, 0xE0, 0x00);bit_Cal(6, 0xE0, 0xC0);bit_Cal(19, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(5, 0xE0, 0xC0);bit_Cal(6, 0xE0, 0x60);bit_Cal(19, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(5, 0xE0, 0x40);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(5, 0xE0, 0x60);bit_Cal(6, 0xE0, 0xC0);bit_Cal(19, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(5, 0xE0, 0x60);bit_Cal(6, 0xE0, 0xA0);bit_Cal(19, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(5, 0xE0, 0xE0);bit_Cal(6, 0xE0, 0xA0);bit_Cal(19, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(5, 0xE0, 0x00);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(5, 0xE0, 0xE0);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(5, 0xE0, 0x60);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x80);
            break;
        default:
            bit_Cal(5, 0xE0, 0x40);bit_Cal(6, 0xE0, 0x00);bit_Cal(19, 0x80, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[0].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(7, 0xE0, 0xA0);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(7, 0xE0, 0x00);bit_Cal(8, 0xC0, 0x80);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(7, 0xE0, 0xC0);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x00);bit_Cal(10, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(7, 0xE0, 0x40);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(7, 0xE0, 0x60);bit_Cal(8, 0xC0, 0x90);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(7, 0xE0, 0x60);bit_Cal(8, 0xC0, 0x40);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(7, 0xE0, 0xE0);bit_Cal(8, 0xC0, 0x40);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(7, 0xE0, 0x00);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(7, 0xE0, 0xE0);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(7, 0xE0, 0x60);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        default:
            bit_Cal(7, 0xE0, 0x40);bit_Cal(8, 0xC0, 0x00);bit_Cal(9, 0x80, 0x00);bit_Cal(10, 0x80, 0x00);//��ʾ��-��
            break;
    }
    /* 1�Ź�λʵ��ʱ��ð�� */
    bit_Cal(4, 0x80, 0x80);

    /**********��λ1���趨ʱ����ʾ**********/
    Val = work_num[0].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(9, 0x60, 0x60);bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0x50, 0x50);
            break;
        case 1:
            bit_Cal(9, 0x60, 0x00);bit_Cal(10, 0x70, 0x00);bit_Cal(11, 0x50, 0x50);
            break;
        case 2:
            bit_Cal(9, 0x60, 0x40);bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0x50, 0x10);
            break;
        default:
            bit_Cal(9, 0x60, 0x00);bit_Cal(10, 0x70, 0x20);bit_Cal(11, 0x50, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[0].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xD0);bit_Cal(13, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0x00);bit_Cal(13, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0xF0);bit_Cal(13, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0xB0);bit_Cal(13, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0x20);bit_Cal(13, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xB0);bit_Cal(13, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xF0);bit_Cal(13, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0x10);bit_Cal(13, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xF0);bit_Cal(13, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xB0);bit_Cal(13, 0x60, 0x60);
            break;
        default:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0x20);bit_Cal(13, 0x60, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[0].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(11, 0x80, 0x80);bit_Cal(14, 0xC0, 0x40);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0x00);bit_Cal(15, 0xE0, 0xC0);bit_Cal(16, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(11, 0x80, 0x80);bit_Cal(14, 0xC0, 0x80);bit_Cal(15, 0xE0, 0x60);bit_Cal(16, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0x80);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xC0);bit_Cal(16, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xA0);bit_Cal(16, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(11, 0x80, 0x80);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xA0);bit_Cal(16, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0x00);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(11, 0x80, 0x80);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x80);
            break;
        default:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0x80);bit_Cal(15, 0xE0, 0x00);bit_Cal(16, 0x80, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[0].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(16, 0x60, 0x60);bit_Cal(17, 0xE0, 0xA0);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(16, 0x60, 0x00);bit_Cal(17, 0xE0, 0x00);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(16, 0x60, 0x40);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(16, 0x60, 0x00);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(16, 0x60, 0x20);bit_Cal(17, 0xE0, 0x40);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(16, 0x60, 0x20);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(16, 0x60, 0x60);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(16, 0x60, 0x00);bit_Cal(17, 0xE0, 0x20);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(16, 0x60, 0x60);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(16, 0x60, 0x20);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(16, 0x60, 0x00);bit_Cal(17, 0xE0, 0x40);bit_Cal(18, 0xC0, 0x00);//��ʾ��-��
            break;
    }
    /* 1�Ź�λ�趨ʱ��ð�� */
    bit_Cal(13, 0x80, 0x80);
    /* 1�Ź�λ��rpm��ͼ�� */
    bit_Cal(19, 0x02, 0x02);
    
    /* 1�Ź�λ���桱ͼ�� */
    bit_Cal(19, 0x04, 0x04);

    /* 1�Ź�λ��min��ͼ�� */
    bit_Cal(19, 0x40, 0x40);

    /* 1�Ź�λ��3�Ź�λ֮����� */
    bit_Cal(0, 0x80, 0x80);

    /* 1�Ź�λת��ͼ�� */
    bit_Cal(0, 0x01, 0x01);//1�Ź�λת��ͼ��S70
    bit_Cal(1, 0x01, 0x01);//1�Ź�λת��ͼ��S71
    bit_Cal(1, 0x02, 0x02);//1�Ź�λת��ͼ��S72
    
    /* 1�Ź�λ����ͼ�� */
    bit_Cal(0, 0x02, 0x02);//1�Ź�λ����ͼ��S73
    bit_Cal(0, 0x04, 0x04);//1�Ź�λ����ͼ��S74
    bit_Cal(0, 0x08, 0x08);//1�Ź�λ�¶�̽ͷͼ��
    
    /* 1�Ź�λʱ��ͼ�� */
    bit_Cal(0, 0x40, 0x40);//1�Ź�λʱ��ͼ��

    /*******************************2�Ź�λ*******************************/
    /**********��λ2��ʵ��ת����ʾ**********/
    if (work_num[1].Speed.Display_Rel > 999) // ����999ʱ
    {
        Val = work_num[1].Speed.Display_Rel / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(22, 0x01, 0x00);bit_Cal(23, 0x01, 0x01);//��ʾ����1
        }
       else
       {
            bit_Cal(22, 0x01, 0x01);bit_Cal(23, 0x01, 0x01);//��ʾ����0
       }
    }
    else
    {
        bit_Cal(22, 0x01, 0x01);bit_Cal(23, 0x01, 0x01);//��ʾ����0
    }
    
   if (work_num[1].Speed.Display_Rel > 99) // ����99ʱ
   {
       Val = work_num[1].Speed.Display_Rel / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(24, 0x03, 0x03);bit_Cal(25, 0x07, 0x05);bit_Cal(26, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(24, 0x03, 0x00);bit_Cal(25, 0x07, 0x00);bit_Cal(26, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(24, 0x03, 0x02);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(24, 0x03, 0x00);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(24, 0x03, 0x01);bit_Cal(25, 0x07, 0x02);bit_Cal(26, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(24, 0x03, 0x01);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(24, 0x03, 0x03);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(24, 0x03, 0x00);bit_Cal(25, 0x07, 0x01);bit_Cal(26, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(24, 0x03, 0x03);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(24, 0x03, 0x01);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(24, 0x03, 0x03);bit_Cal(25, 0x07, 0x05);bit_Cal(26, 0x03, 0x03);//��ʾ������
   }

   if (work_num[1].Speed.Display_Rel > 9) // ����9ʱ
   {
       Val = work_num[1].Speed.Display_Rel / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(27, 0x03, 0x03);bit_Cal(28, 0x07, 0x05);bit_Cal(29, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(27, 0x03, 0x00);bit_Cal(28, 0x07, 0x00);bit_Cal(29, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(27, 0x03, 0x02);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(27, 0x03, 0x00);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(27, 0x03, 0x01);bit_Cal(28, 0x07, 0x02);bit_Cal(29, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(27, 0x03, 0x01);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(27, 0x03, 0x03);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(27, 0x03, 0x00);bit_Cal(28, 0x07, 0x01);bit_Cal(29, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(27, 0x03, 0x03);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(27, 0x03, 0x01);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(27, 0x03, 0x03);bit_Cal(28, 0x07, 0x05);bit_Cal(29, 0x03, 0x03);//��ʾ������
   }
    bit_Cal(30, 0x01, 0x01);//ʵ��ת�ٸ�λֻ����ʾ��

    /**********��λ2���趨ת����ʾ**********/
    if (work_num[1].Speed.Display_Set > 999) // ����999ʱ
    {
        Val = work_num[1].Speed.Display_Set / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(31, 0x01, 0x00);bit_Cal(32, 0x01, 0x01);//��ʾ����1
        }
       else
       {
            bit_Cal(31, 0x01, 0x01);bit_Cal(32, 0x01, 0x01);//��ʾ����0
       }
    }
    else
    {
        bit_Cal(31, 0x01, 0x01);bit_Cal(32, 0x01, 0x01);//��ʾ����0
    }
    
   if (work_num[1].Speed.Display_Set > 99) // ����99ʱ
   {
       Val = work_num[1].Speed.Display_Set / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(33, 0x03, 0x03);bit_Cal(34, 0x07, 0x05);bit_Cal(35, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(33, 0x03, 0x00);bit_Cal(34, 0x07, 0x00);bit_Cal(35, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(33, 0x03, 0x02);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(33, 0x03, 0x00);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(33, 0x03, 0x01);bit_Cal(34, 0x07, 0x02);bit_Cal(35, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(33, 0x03, 0x01);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(33, 0x03, 0x03);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(33, 0x03, 0x00);bit_Cal(34, 0x07, 0x01);bit_Cal(35, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(33, 0x03, 0x03);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(33, 0x03, 0x01);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(33, 0x03, 0x03);bit_Cal(34, 0x07, 0x05);bit_Cal(35, 0x03, 0x03);//��ʾ������
   }

   if (work_num[1].Speed.Display_Set > 9) // ����9ʱ
   {
       Val = work_num[1].Speed.Display_Set / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(36, 0x03, 0x03);bit_Cal(37, 0x07, 0x05);bit_Cal(38, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(36, 0x03, 0x00);bit_Cal(37, 0x07, 0x00);bit_Cal(38, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(36, 0x03, 0x02);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(36, 0x03, 0x00);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(36, 0x03, 0x01);bit_Cal(37, 0x07, 0x02);bit_Cal(38, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(36, 0x03, 0x01);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(36, 0x03, 0x03);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(36, 0x03, 0x00);bit_Cal(37, 0x07, 0x01);bit_Cal(38, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(36, 0x03, 0x03);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(36, 0x03, 0x01);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(36, 0x03, 0x03);bit_Cal(37, 0x07, 0x05);bit_Cal(38, 0x03, 0x03);//��ʾ������
   }
    bit_Cal(39, 0x01, 0x01);//ʵ��ת�ٸ�λֻ����ʾ��

    /**********��λ2��ʵ���¶���ʾ**********/
    if (work_num[1].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[1].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) / 1000 % 10;//�������0��������999���Բ�����ʾ
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = 10;//��ʾ��-��
    }
    switch (Val)
    {
        case 0:
            if (work_num[1].Temp.Display_Rel > 999)//��ʾ0
            {
                bit_Cal(20, 0x30, 0x30);bit_Cal(21, 0x1C, 0x14);bit_Cal(22, 0x0C, 0x0C);
            }
            else//����ʾ��λ
            {
                bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x00);bit_Cal(22, 0x0C, 0x00);
            }
            break;
        case 1:
            bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x00);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 2:
            bit_Cal(20, 0x30, 0x20);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x04);
            break;
        case 3:
            bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 4:
            bit_Cal(20, 0x30, 0x10);bit_Cal(21, 0x1C, 0x08);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 5:
            bit_Cal(20, 0x30, 0x10);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x08);
            break;
        case 6:
            bit_Cal(20, 0x30, 0x30);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x08);
            break;
        case 7:
            bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x04);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 8:
            bit_Cal(20, 0x30, 0x30);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 9:
            bit_Cal(20, 0x30, 0x10);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x0C);
            break;
        default:
            bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x08);bit_Cal(22, 0x0C, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[1].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[1].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = 10;//��ʾ��-��
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[1].Temp.Display_Rel > 99)//��ʾ��
            {
                bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x0A);bit_Cal(24, 0x1C, 0x1C);
            }
            else//����ʾ
            {
                bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x00);bit_Cal(24, 0x1C, 0x00);
            }
            break;
        case 1:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x00);bit_Cal(24, 0x1C, 0x0C);
            break;
        case 2:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x0E);bit_Cal(24, 0x1C, 0x14);
            break;
        case 3:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x06);bit_Cal(24, 0x1C, 0x1C);
            break;
        case 4:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x04);bit_Cal(24, 0x1C, 0x0C);
            break;
        case 5:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x06);bit_Cal(24, 0x1C, 0x18);
            break;
        case 6:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x0E);bit_Cal(24, 0x1C, 0x18);
            break;
        case 7:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x02);bit_Cal(24, 0x1C, 0x0C);
            break;
        case 8:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x0E);bit_Cal(24, 0x1C, 0x1C);
            break;
        case 9:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x06);bit_Cal(24, 0x1C, 0x1C);
            break;
        default:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x04);bit_Cal(24, 0x1C, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[1].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[1].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) / 10 % 10;
    }
    switch (Val)
    {
    case 0:
        bit_Cal(25, 0x18, 0x18);bit_Cal(26, 0x1C, 0x14);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 1:
        bit_Cal(25, 0x18, 0x00);bit_Cal(26, 0x1C, 0x00);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 2:
        bit_Cal(25, 0x18, 0x10);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x04);
        break;
    case 3:
        bit_Cal(25, 0x18, 0x00);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 4:
        bit_Cal(25, 0x18, 0x08);bit_Cal(26, 0x1C, 0x08);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 5:
        bit_Cal(25, 0x18, 0x08);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x08);
        break;
    case 6:
        bit_Cal(25, 0x18, 0x18);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x08);
        break;
    case 7:
        bit_Cal(25, 0x18, 0x00);bit_Cal(26, 0x1C, 0x04);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 8:
        bit_Cal(25, 0x18, 0x18);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 9:
        bit_Cal(25, 0x18, 0x08);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x0C);
        break;
    default:
        bit_Cal(25, 0x18, 0x00);bit_Cal(26, 0x1C, 0x08);bit_Cal(27, 0x0C, 0x00);//��ʾ��-��
        break;
    }

    if (work_num[1].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[1].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) % 10;
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(28, 0x38, 0x38);bit_Cal(29, 0x1C, 0x14);bit_Cal(30, 0x04, 0x04);
            break;
        case 1:
            bit_Cal(28, 0x38, 0x00);bit_Cal(29, 0x1C, 0x10);bit_Cal(30, 0x04, 0x04);
            break;
        case 2:
            bit_Cal(28, 0x38, 0x30);bit_Cal(29, 0x1C, 0x0C);bit_Cal(30, 0x04, 0x04);
            break;
        case 3:
            bit_Cal(28, 0x38, 0x20);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x04);
            break;
        case 4:
            bit_Cal(28, 0x38, 0x08);bit_Cal(29, 0x1C, 0x18);bit_Cal(30, 0x04, 0x04);
            break;
        case 5:
            bit_Cal(28, 0x38, 0x28);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x00);
            break;
        case 6:
            bit_Cal(28, 0x38, 0x38);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x00);
            break;
        case 7:
            bit_Cal(28, 0x38, 0x00);bit_Cal(29, 0x1C, 0x14);bit_Cal(30, 0x04, 0x04);
            break;
        case 8:
            bit_Cal(28, 0x38, 0x38);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x04);
            break;
        case 9:
            bit_Cal(28, 0x38, 0x28);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x04);
            break;
        default:
            bit_Cal(28, 0x38, 0x00);bit_Cal(29, 0x1C, 0x08);bit_Cal(30, 0x04, 0x00);//��ʾ��-��
            break;
    }

    /* 2�Ź�λʵ���¶�С���� */
    bit_Cal(27, 0x10, 0x10);

    /**********��λ2���趨�¶���ʾ**********/
    if (work_num[1].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[1].Temp.Display_Set / 1000 % 10;
    }
    else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Set) / 1000 % 10;//�������0��������999���Բ�����ʾ
    }
    else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
    {
        Val = 10;//��ʾ��-��
    }
    switch (Val)
    {
        case 0:
            if (work_num[1].Temp.Display_Set > 999)//��ʾ0
            {
                bit_Cal(30, 0x0A, 0x0A);bit_Cal(31, 0x0E, 0x0A);bit_Cal(32, 0x06, 0x06);
            }
            else//����ʾ��λ
            {
                bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x00);bit_Cal(32, 0x06, 0x00);
            }
            break;
        case 1:
            bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x00);bit_Cal(32, 0x06, 0x06);
            break;
        case 2:
            bit_Cal(30, 0x0A, 0x08);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x02);
            break;
        case 3:
            bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x06);
            break;
        case 4:
            bit_Cal(30, 0x0A, 0x02);bit_Cal(31, 0x0E, 0x04);bit_Cal(32, 0x06, 0x06);
            break;
        case 5:
            bit_Cal(30, 0x0A, 0x02);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x04);
            break;
        case 6:
            bit_Cal(30, 0x0A, 0x0A);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x04);
            break;
        case 7:
            bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x02);bit_Cal(32, 0x06, 0x06);
            break;
        case 8:
            bit_Cal(30, 0x0A, 0x0A);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x06);
            break;
        case 9:
            bit_Cal(30, 0x0A, 0x02);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x06);
            break;
        default:
            bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x04);bit_Cal(32, 0x06, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[1].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[1].Temp.Display_Set / 100 % 10;
    }
    else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
    {
        Val = 10;//��ʾ��-��
    }
    else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[1].Temp.Display_Set > 99)//��ʾ��
            {
                bit_Cal(32, 0x08, 0x08);bit_Cal(33, 0x1C, 0x14);bit_Cal(34, 0x38, 0x38);
            }
            else//����ʾ
            {
                bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x00);bit_Cal(34, 0x38, 0x00);
            }
            break;
        case 1:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x00);bit_Cal(34, 0x38, 0x30);
            break;
        case 2:
            bit_Cal(32, 0x08, 0x08);bit_Cal(33, 0x1C, 0x18);bit_Cal(34, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x18);bit_Cal(34, 0x38, 0x38);
            break;
        case 4:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x0C);bit_Cal(34, 0x38, 0x30);
            break;
        case 5:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x1C);bit_Cal(34, 0x38, 0x28);
            break;
        case 6:
            bit_Cal(32, 0x08, 0x08);bit_Cal(33, 0x1C, 0x1C);bit_Cal(34, 0x38, 0x28);
            break;
        case 7:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x00);bit_Cal(34, 0x38, 0x38);
            break;
        case 8:
            bit_Cal(32, 0x08, 0x08);bit_Cal(33, 0x1C, 0x1C);bit_Cal(34, 0x38, 0x38);
            break;
        case 9:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x1C);bit_Cal(34, 0x38, 0x38);
            break;
        default:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x08);bit_Cal(34, 0x38, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[1].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[1].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Set) / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Set) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(35, 0x1C, 0x1C);bit_Cal(36, 0x1C, 0x14);bit_Cal(37, 0x08, 0x08);
            break;
        case 1:
            bit_Cal(35, 0x1C, 0x00);bit_Cal(36, 0x1C, 0x10);bit_Cal(37, 0x08, 0x08);
            break;
        case 2:
            bit_Cal(35, 0x1C, 0x18);bit_Cal(36, 0x1C, 0x0C);bit_Cal(37, 0x08, 0x08);
            break;
        case 3:
            bit_Cal(35, 0x1C, 0x10);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x08);
            break;
        case 4:
            bit_Cal(35, 0x1C, 0x04);bit_Cal(36, 0x1C, 0x18);bit_Cal(37, 0x08, 0x08);
            break;
        case 5:
            bit_Cal(35, 0x1C, 0x14);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x00);
            break;
        case 6:
            bit_Cal(35, 0x1C, 0x1C);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x00);
            break;
        case 7:
            bit_Cal(35, 0x1C, 0x00);bit_Cal(36, 0x1C, 0x14);bit_Cal(37, 0x08, 0x08);
            break;
        case 8:
            bit_Cal(35, 0x1C, 0x1C);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x08);
            break;
        case 9:
            bit_Cal(35, 0x1C, 0x14);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x08);
            break;
        default:
            bit_Cal(35, 0x1C, 0x00);bit_Cal(36, 0x1C, 0x08);bit_Cal(37, 0x08, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[1].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[1].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Set) % 10;
    }
    else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Set) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(38, 0x3C, 0x3C);bit_Cal(39, 0x38, 0x28);
            break;
        case 1:
            bit_Cal(38, 0x3C, 0x00);bit_Cal(39, 0x38, 0x28);
            break;
        case 2:
            bit_Cal(38, 0x3C, 0x34);bit_Cal(39, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(38, 0x3C, 0x24);bit_Cal(39, 0x38, 0x38);
            break;
        case 4:
            bit_Cal(38, 0x3C, 0x08);bit_Cal(39, 0x38, 0x38);
            break;
        case 5:
            bit_Cal(38, 0x3C, 0x2C);bit_Cal(39, 0x38, 0x30);
            break;
        case 6:
            bit_Cal(38, 0x3C, 0x3C);bit_Cal(39, 0x38, 0x30);
            break;
        case 7:
            bit_Cal(38, 0x3C, 0x04);bit_Cal(39, 0x38, 0x28);
            break;
        case 8:
            bit_Cal(38, 0x3C, 0x3C);bit_Cal(39, 0x38, 0x38);
            break;
        case 9:
            bit_Cal(38, 0x3C, 0x2C);bit_Cal(39, 0x38, 0x38);
            break;
        default:
            bit_Cal(38, 0x3C, 0x00);bit_Cal(39, 0x38, 0x10);//��ʾ��-��
            break;
    }
    /* 2�Ź�λ�趨�¶�С���� */
    bit_Cal(37, 0x10, 0x10);

    /**********��λ2��ʵ��ʱ����ʾ**********/
    Val = work_num[1].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(21, 0xE0, 0x60);bit_Cal(22, 0xE0, 0xE0);
            break;
        case 1:
            bit_Cal(21, 0xE0, 0x00);bit_Cal(22, 0xE0, 0x60);
            break;
        case 2:
            bit_Cal(21, 0xE0, 0xA0);bit_Cal(22, 0xE0, 0xA0);
            break;
        default:
            bit_Cal(21, 0xE0, 0x80);bit_Cal(22, 0xE0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[1].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xD0);bit_Cal(24, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0x00);bit_Cal(24, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0xF0);bit_Cal(24, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0xB0);bit_Cal(24, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0x20);bit_Cal(24, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xB0);bit_Cal(24, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xF0);bit_Cal(24, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0x10);bit_Cal(24, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xF0);bit_Cal(24, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xB0);bit_Cal(24, 0x60, 0x60);
            break;
        default:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0x20);bit_Cal(24, 0x60, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[1].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(25, 0xE0, 0xA0);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(25, 0xE0, 0x00);bit_Cal(26, 0xE0, 0xC0);bit_Cal(39, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(25, 0xE0, 0xC0);bit_Cal(26, 0xE0, 0x60);bit_Cal(39, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(25, 0xE0, 0x40);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(25, 0xE0, 0x60);bit_Cal(26, 0xE0, 0xC0);bit_Cal(39, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(25, 0xE0, 0x60);bit_Cal(26, 0xE0, 0xA0);bit_Cal(39, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(25, 0xE0, 0xE0);bit_Cal(26, 0xE0, 0xA0);bit_Cal(39, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(25, 0xE0, 0x00);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(25, 0xE0, 0xE0);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(25, 0xE0, 0x60);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x80);
            break;
        default:
            bit_Cal(25, 0xE0, 0x40);bit_Cal(26, 0xE0, 0x00);bit_Cal(39, 0x80, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[1].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(27, 0xE0, 0xA0);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(27, 0xE0, 0x00);bit_Cal(28, 0xC0, 0x80);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(27, 0xE0, 0xC0);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x00);bit_Cal(30, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(27, 0xE0, 0x40);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(27, 0xE0, 0x60);bit_Cal(28, 0xC0, 0x90);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(27, 0xE0, 0x60);bit_Cal(28, 0xC0, 0x40);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(27, 0xE0, 0xE0);bit_Cal(28, 0xC0, 0x40);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(27, 0xE0, 0x00);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(27, 0xE0, 0xE0);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(27, 0xE0, 0x60);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        default:
            bit_Cal(27, 0xE0, 0x40);bit_Cal(28, 0xC0, 0x00);bit_Cal(29, 0x80, 0x00);bit_Cal(30, 0x80, 0x00);//��ʾ��-��
            break;
    }
    /* 2�Ź�λʵ��ʱ��ð�� */
    bit_Cal(24, 0x80, 0x80);

    /**********��λ2���趨ʱ����ʾ**********/
    Val = work_num[1].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(29, 0x60, 0x60);bit_Cal(30, 0x70, 0x50);bit_Cal(31, 0x50, 0x50);
            break;
        case 1:
            bit_Cal(29, 0x60, 0x00);bit_Cal(30, 0x70, 0x00);bit_Cal(31, 0x50, 0x50);
            break;
        case 2:
            bit_Cal(29, 0x60, 0x40);bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0x50, 0x10);
            break;
        default:
            bit_Cal(29, 0x60, 0x00);bit_Cal(30, 0x70, 0x20);bit_Cal(31, 0x50, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[1].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xD0);bit_Cal(33, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0x00);bit_Cal(33, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0xF0);bit_Cal(33, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0xB0);bit_Cal(33, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0x20);bit_Cal(33, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xB0);bit_Cal(33, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xF0);bit_Cal(33, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0x10);bit_Cal(33, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xF0);bit_Cal(33, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xB0);bit_Cal(33, 0x60, 0x60);
            break;
        default:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0x20);bit_Cal(33, 0x60, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[1].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(31, 0x80, 0x80);bit_Cal(34, 0xC0, 0x40);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0x00);bit_Cal(35, 0xE0, 0xC0);bit_Cal(36, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(31, 0x80, 0x80);bit_Cal(34, 0xC0, 0x80);bit_Cal(35, 0xE0, 0x60);bit_Cal(36, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0x80);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xC0);bit_Cal(36, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xA0);bit_Cal(36, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(31, 0x80, 0x80);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xA0);bit_Cal(36, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0x00);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(31, 0x80, 0x80);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x80);
            break;
        default:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0x80);bit_Cal(35, 0xE0, 0x00);bit_Cal(36, 0x80, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[1].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(36, 0x60, 0x60);bit_Cal(37, 0xE0, 0xA0);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(36, 0x60, 0x00);bit_Cal(37, 0xE0, 0x00);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(36, 0x60, 0x40);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(36, 0x60, 0x00);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(36, 0x60, 0x20);bit_Cal(37, 0xE0, 0x40);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(36, 0x60, 0x20);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(36, 0x60, 0x60);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(36, 0x60, 0x00);bit_Cal(37, 0xE0, 0x20);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(36, 0x60, 0x60);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(36, 0x60, 0x20);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(36, 0x60, 0x00);bit_Cal(37, 0xE0, 0x40);bit_Cal(38, 0xC0, 0x00);//��ʾ��-��
            break;
    }
    /* 2�Ź�λ�趨ʱ��ð�� */
    bit_Cal(33, 0x80, 0x80);
    /* 2�Ź�λ��rpm��ͼ�� */
    bit_Cal(39, 0x02, 0x02);
    
    /* 2�Ź�λ���桱ͼ�� */
    bit_Cal(39, 0x04, 0x04);

    /* 2�Ź�λ��min��ͼ�� */
    bit_Cal(39, 0x40, 0x40);

    /* 2�Ź�λ��3�Ź�λ֮����� */
    bit_Cal(20, 0x80, 0x80);

    /* 2�Ź�λת��ͼ�� */
    bit_Cal(20, 0x01, 0x01);//2�Ź�λת��ͼ��S70
    bit_Cal(21, 0x01, 0x01);//2�Ź�λת��ͼ��S71
    bit_Cal(21, 0x02, 0x02);//2�Ź�λת��ͼ��S72
    
    /* 2�Ź�λ����ͼ�� */
    bit_Cal(20, 0x02, 0x02);//2�Ź�λ����ͼ��S73
    bit_Cal(20, 0x04, 0x04);//2�Ź�λ����ͼ��S74
    bit_Cal(20, 0x08, 0x08);//2�Ź�λ�¶�̽ͷͼ��
    
    /* 2�Ź�λʱ��ͼ�� */
    bit_Cal(20, 0x40, 0x40);//2�Ź�λʱ��ͼ��
    
    /**********���ݷ���**********/
    for(uint8_t i=0;i<40;i++)/* 1�Ź�λ��3�Ź�λ֮����� */
    {
        Write_Addr_Dat_N(IC2, i, seg[i], 1);
    }
}

void Display_IC1(_Work_Num_ work_num[])
{
    uint8_t Val;// ���ڰ�ʮ��ȡ����������

    /*******************************3�Ź�λ*******************************/
    /**********��λ3��ʵ��ת����ʾ**********/
    if (work_num[2].Speed.Display_Rel > 999) // ����999ʱ
    {
        Val = work_num[2].Speed.Display_Rel / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(78, 0x02, 0x00);bit_Cal(77, 0x02, 0x02);//��ʾ����1
        }
       else
       {
            bit_Cal(78, 0x02, 0x02);bit_Cal(77, 0x02, 0x02);//��ʾ����0
       }
    }
    else
    {
        bit_Cal(78, 0x02, 0x02);bit_Cal(77, 0x02, 0x02);//��ʾ����0
    }
    
   if (work_num[2].Speed.Display_Rel > 99) // ����99ʱ
   {
       Val = work_num[2].Speed.Display_Rel / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x07);bit_Cal(75, 0x03, 0x02);bit_Cal(74, 0x02, 0x02);
            break;
       case 1:
            bit_Cal(77, 0x01, 0x00);bit_Cal(76, 0x07, 0x01);bit_Cal(75, 0x03, 0x00);bit_Cal(74, 0x02, 0x02);
            break;
       case 2:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x05);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x00);
            break;
       case 3:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x01);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       case 4:
            bit_Cal(77, 0x01, 0x00);bit_Cal(76, 0x07, 0x03);bit_Cal(75, 0x03, 0x01);bit_Cal(74, 0x02, 0x02);
            break;
       case 5:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x02);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       case 6:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x06);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       case 7:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x01);bit_Cal(75, 0x03, 0x00);bit_Cal(74, 0x02, 0x02);
            break;
       case 8:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x07);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       case 9:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x03);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x07);bit_Cal(75, 0x02, 0x02);bit_Cal(74, 0x02, 0x02);;//��ʾ������
   }

   if (work_num[2].Speed.Display_Rel > 9) // ����9ʱ
   {
       Val = work_num[2].Speed.Display_Rel / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x03);bit_Cal(72, 0x03, 0x02);bit_Cal(71, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(74, 0x01, 0x00);bit_Cal(73, 0x03, 0x00);bit_Cal(72, 0x03, 0x00);bit_Cal(71, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x02);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x00);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(74, 0x01, 0x00);bit_Cal(73, 0x03, 0x01);bit_Cal(72, 0x03, 0x01);bit_Cal(71, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x01);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x03);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x00);bit_Cal(72, 0x03, 0x00);bit_Cal(71, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x03);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x01);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
       bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x03);bit_Cal(72, 0x03, 0x02);bit_Cal(71, 0x03, 0x03);//��ʾ������
   }
    bit_Cal(70, 0x01, 0x01);//ʵ��ת�ٸ�λֻ����ʾ��

    /**********��λ3���趨ת����ʾ**********/
    if (work_num[2].Speed.Display_Set > 999) // ����999ʱ
    {
        Val = work_num[2].Speed.Display_Set / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(69, 0x01, 0x00);bit_Cal(68, 0x01, 0x01);//��ʾ����1
        }
       else
       {
            bit_Cal(69, 0x01, 0x01);bit_Cal(68, 0x01, 0x01);//��ʾ����0
       }
    }
    else
    {
        bit_Cal(69, 0x01, 0x01);bit_Cal(68, 0x01, 0x01);//��ʾ����0
    }
    
   if (work_num[2].Speed.Display_Set > 99) // ����99ʱ
   {
       Val = work_num[2].Speed.Display_Set / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x02);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);
            break;
       case 1:
            bit_Cal(67, 0x01, 0x00);bit_Cal(66, 0x01, 0x00);bit_Cal(65, 0x03, 0x00);bit_Cal(64, 0x03, 0x01);bit_Cal(63, 0x01, 0x01);
            break;
       case 2:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x00);bit_Cal(65, 0x03, 0x03);bit_Cal(64, 0x03, 0x02);bit_Cal(63, 0x01, 0x01);
            break;
       case 3:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x00);bit_Cal(65, 0x03, 0x01);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);
            break;
       case 4:
            bit_Cal(67, 0x01, 0x00);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x01);bit_Cal(64, 0x03, 0x01);bit_Cal(63, 0x01, 0x01);
            break;
       case 5:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x01);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x00);
            break;
       case 6:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x03);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x00);
            break;
       case 7:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x00);bit_Cal(65, 0x03, 0x00);bit_Cal(64, 0x03, 0x01);bit_Cal(63, 0x01, 0x01);
            break;
       case 8:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x03);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);
            break;
       case 9:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x01);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x02);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);//��ʾ������
   }

   if (work_num[2].Speed.Display_Set > 9) // ����9ʱ
   {
        Val = work_num[2].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
            case 0:
                bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x05);bit_Cal(61, 0x03, 0x03);
                break;
            case 1:
                bit_Cal(63, 0x06, 0x00);bit_Cal(62, 0x07, 0x04);bit_Cal(61, 0x03, 0x02);
                break;
            case 2:
                bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x02);bit_Cal(61, 0x03, 0x03);
                break;
            case 3:
                bit_Cal(63, 0x06, 0x04);bit_Cal(62, 0x07, 0x06);bit_Cal(61, 0x03, 0x03);
                break;
            case 4:
                bit_Cal(63, 0x06, 0x00);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x02);
                break;
            case 5:
                bit_Cal(63, 0x06, 0x04);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x01);
                break;
            case 6:
                bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x01);
                break;
            case 7:
                bit_Cal(63, 0x06, 0x00);bit_Cal(62, 0x07, 0x04);bit_Cal(61, 0x03, 0x03);
                break;
            case 8:
                bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x03);
                break;
            case 9:
                bit_Cal(63, 0x06, 0x04);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x03);
                break;
            default:
                break;
        }
    }
    else
    {
        bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x05);bit_Cal(61, 0x03, 0x03);//��ʾ������
    }
    bit_Cal(60, 0x02, 0x02);//ʵ��ת�ٸ�λֻ����ʾ��

    /**********��λ3��ʵ���¶���ʾ**********/
    if (work_num[2].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[2].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) / 1000 % 10;//�������0��������999���Բ�����ʾ
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = 10;//��ʾ��-��
    }
    switch (Val)
    {
        case 0:
            if (work_num[2].Temp.Display_Rel > 999)//��ʾ0
            {
                bit_Cal(78, 0x0C, 0x0C);bit_Cal(77, 0x1C, 0x14);bit_Cal(76, 0x18, 0x18);
            }
            else//����ʾ��λ
            {
                bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x00);bit_Cal(76, 0x18, 0x00);
            }
            break;
        case 1:
            bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x00);bit_Cal(76, 0x18, 0x18);
            break;
        case 2:
            bit_Cal(78, 0x0C, 0x08);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x08);
            break;
        case 3:
            bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x18);
            break;
        case 4:
            bit_Cal(78, 0x0C, 0x04);bit_Cal(77, 0x1C, 0x08);bit_Cal(76, 0x18, 0x18);
            break;
        case 5:
            bit_Cal(78, 0x0C, 0x04);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x10);
            break;
        case 6:
            bit_Cal(78, 0x0C, 0x0C);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x10);
            break;
        case 7:
            bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x04);bit_Cal(76, 0x18, 0x18);
            break;
        case 8:
            bit_Cal(78, 0x0C, 0x0C);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x18);
            break;
        case 9:
            bit_Cal(78, 0x0C, 0x04);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x18);
            break;
        default:
            bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x08);bit_Cal(76, 0x18, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[2].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[2].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = 10;//��ʾ��-��
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[2].Temp.Display_Rel > 99)//��ʾ��
            {
                bit_Cal(75, 0x3C, 0x3C);bit_Cal(74, 0x38, 0x2C);
            }
            else//����ʾ
            {
                bit_Cal(75, 0x3C, 0x00);bit_Cal(74, 0x38, 0x00);
            }
            break;
        case 1:
            bit_Cal(75, 0x3C, 0x00);bit_Cal(74, 0x38, 0x28);
            break;
        case 2:
            bit_Cal(75, 0x3C, 0x34);bit_Cal(74, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(75, 0x3C, 0x24);bit_Cal(74, 0x38, 0x3C);
            break;
        case 4:
            bit_Cal(75, 0x3C, 0x08);bit_Cal(74, 0x38, 0x3C);
            break;
        case 5:
            bit_Cal(75, 0x3C, 0x2C);bit_Cal(74, 0x38, 0x30);
            break;
        case 6:
            bit_Cal(75, 0x3C, 0x3C);bit_Cal(74, 0x38, 0x30);
            break;
        case 7:
            bit_Cal(75, 0x3C, 0x04);bit_Cal(74, 0x38, 0x28);
            break;
        case 8:
            bit_Cal(75, 0x3C, 0x3C);bit_Cal(74, 0x38, 0x3C);
            break;
        case 9:
            bit_Cal(75, 0x3C, 0x2C);bit_Cal(74, 0x38, 0x3C);
            break;
        default:
            bit_Cal(75, 0x3C, 0x00);bit_Cal(74, 0x38, 0x10);
            break;
    }

    if (work_num[2].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[2].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x14);bit_Cal(72, 0x1C, 0x1C);
            break;
        case 1:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x00);bit_Cal(72, 0x1C, 0x0C);
            break;
        case 2:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x1C);bit_Cal(72, 0x1C, 0x14);
            break;
        case 3:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x0C);bit_Cal(72, 0x1C, 0x1C);
            break;
        case 4:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x08);bit_Cal(72, 0x1C, 0x0C);
            break;
        case 5:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x0C);bit_Cal(72, 0x1C, 0x18);
            break;
        case 6:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x1C);bit_Cal(72, 0x1C, 0x18);
            break;
        case 7:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x04);bit_Cal(72, 0x1C, 0x0C);
            break;
        case 8:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x1C);bit_Cal(72, 0x1C, 0x1C);
            break;
        case 9:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x0C);bit_Cal(72, 0x1C, 0x1C);
            break;
        default:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x08);bit_Cal(72, 0x1C, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[2].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[2].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) % 10;
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(71, 0x1C, 0x1C);bit_Cal(70, 0x0E, 0x0A);bit_Cal(69, 0x02, 0x02);
            break;
        case 1:
            bit_Cal(71, 0x1C, 0x00);bit_Cal(70, 0x0E, 0x08);bit_Cal(69, 0x02, 0x02);
            break;
        case 2:
            bit_Cal(71, 0x1C, 0x18);bit_Cal(70, 0x0E, 0x06);bit_Cal(69, 0x02, 0x02);
            break;
        case 3:
            bit_Cal(71, 0x1C, 0x10);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x02);
            break;
        case 4:
            bit_Cal(71, 0x1C, 0x04);bit_Cal(70, 0x0E, 0x0C);bit_Cal(69, 0x02, 0x02);
            break;
        case 5:
            bit_Cal(71, 0x1C, 0x14);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x00);
            break;
        case 6:
            bit_Cal(71, 0x1C, 0x1C);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x00);
            break;
        case 7:
            bit_Cal(71, 0x1C, 0x00);bit_Cal(70, 0x0E, 0x0A);bit_Cal(69, 0x02, 0x02);
            break;
        case 8:
            bit_Cal(71, 0x1C, 0x1C);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x02);
            break;
        case 9:
            bit_Cal(71, 0x1C, 0x14);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x02);
            break;
        default:
            bit_Cal(71, 0x1C, 0x00);bit_Cal(70, 0x0E, 0x04);bit_Cal(69, 0x02, 0x00);//��ʾ��-��
            break;
    }

    /* 3�Ź�λʵ���¶�С���� */
    bit_Cal(72, 0x20, 0x20);

    /**********��λ3���趨�¶���ʾ**********/
    if (work_num[2].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[2].Temp.Display_Set / 1000 % 10;
    }
    else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Set) / 1000 % 10;//�������0��������999���Բ�����ʾ
    }
    else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
    {
        Val = 10;//��ʾ��-��
    }
    switch (Val)
    {
        case 0:
            if (work_num[2].Temp.Display_Set > 999)//��ʾ0
            {
                bit_Cal(69, 0x1C, 0x1C);bit_Cal(68, 0x0E, 0x0A);bit_Cal(67, 0x02, 0x02);
            }
            else//����ʾ��λ
            {
                bit_Cal(69, 0x1C, 0x00);bit_Cal(68, 0x0E, 0x00);bit_Cal(67, 0x02, 0x00);
            }
            break;
        case 1:
            bit_Cal(69, 0x1C, 0x00);bit_Cal(68, 0x0E, 0x08);bit_Cal(67, 0x02, 0x02);
            break;
        case 2:
            bit_Cal(69, 0x1C, 0x18);bit_Cal(68, 0x0E, 0x06);bit_Cal(67, 0x02, 0x02);
            break;
        case 3:
            bit_Cal(69, 0x1C, 0x10);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x02);
            break;
        case 4:
            bit_Cal(69, 0x1C, 0x04);bit_Cal(68, 0x0E, 0x0C);bit_Cal(67, 0x02, 0x02);
            break;
        case 5:
            bit_Cal(69, 0x1C, 0x14);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x00);
            break;
        case 6:
            bit_Cal(69, 0x1C, 0x1C);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x00);
            break;
        case 7:
            bit_Cal(69, 0x1C, 0x00);bit_Cal(68, 0x0E, 0x0A);bit_Cal(67, 0x02, 0x02);
            break;
        case 8:
            bit_Cal(69, 0x1C, 0x1C);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x02);
            break;
        case 9:
            bit_Cal(69, 0x1C, 0x14);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x02);
            break;
        default:
            bit_Cal(69, 0x1C, 0x00);bit_Cal(68, 0x0E, 0x04);bit_Cal(67, 0x02, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[2].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[2].Temp.Display_Set / 100 % 10;
    }
    else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
    {
        Val = 10;//��ʾ��-��
    }
    else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[2].Temp.Display_Set > 999)//��ʾ0
            {
                bit_Cal(67, 0x1C, 0x1C);bit_Cal(66, 0x0E, 0x0A);bit_Cal(65, 0x04, 0x04);
            }
            else//����ʾ��λ
            {
                bit_Cal(67, 0x1C, 0x00);bit_Cal(66, 0x0E, 0x00);bit_Cal(65, 0x04, 0x00);
            }
            break;
        case 1:
            bit_Cal(67, 0x1C, 0x00);bit_Cal(66, 0x0E, 0x08);bit_Cal(65, 0x04, 0x04);
            break;
        case 2:
            bit_Cal(67, 0x1C, 0x18);bit_Cal(66, 0x0E, 0x06);bit_Cal(65, 0x04, 0x04);
            break;
        case 3:
            bit_Cal(67, 0x1C, 0x10);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x04);
            break;
        case 4:
            bit_Cal(67, 0x1C, 0x04);bit_Cal(66, 0x0E, 0x0C);bit_Cal(65, 0x04, 0x04);
            break;
        case 5:
            bit_Cal(67, 0x1C, 0x14);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x00);
            break;
        case 6:
            bit_Cal(67, 0x1C, 0x1C);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x00);
            break;
        case 7:
            bit_Cal(67, 0x1C, 0x00);bit_Cal(66, 0x0E, 0x0A);bit_Cal(65, 0x04, 0x04);
            break;
        case 8:
            bit_Cal(67, 0x1C, 0x1C);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x04);
            break;
        case 9:
            bit_Cal(67, 0x1C, 0x14);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x04);
            break;
        default:
            bit_Cal(67, 0x1C, 0x00);bit_Cal(66, 0x0E, 0x04);bit_Cal(65, 0x04, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[2].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[2].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Set) / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Set) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(65, 0x18, 0x18);bit_Cal(64, 0x1C, 0x14);bit_Cal(63, 0x18, 0x18);
            break;
        case 1:
            bit_Cal(65, 0x18, 0x00);bit_Cal(64, 0x1C, 0x00);bit_Cal(63, 0x18, 0x18);
            break;
        case 2:
            bit_Cal(65, 0x18, 0x10);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x08);
            break;
        case 3:
            bit_Cal(65, 0x18, 0x00);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x18);
            break;
        case 4:
            bit_Cal(65, 0x18, 0x08);bit_Cal(64, 0x1C, 0x08);bit_Cal(63, 0x18, 0x18);
            break;
        case 5:
            bit_Cal(65, 0x18, 0x08);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x10);
            break;
        case 6:
            bit_Cal(65, 0x18, 0x18);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x10);
            break;
        case 7:
            bit_Cal(65, 0x18, 0x00);bit_Cal(64, 0x1C, 0x04);bit_Cal(63, 0x18, 0x18);
            break;
        case 8:
            bit_Cal(65, 0x18, 0x18);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x18);
            break;
        case 9:
            bit_Cal(65, 0x18, 0x08);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x18);
            break;
        default:
            bit_Cal(65, 0x18, 0x00);bit_Cal(64, 0x1C, 0x08);bit_Cal(63, 0x18, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[2].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[2].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Set) % 10;
    }
    else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Set) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(62, 0x38, 0x38);bit_Cal(61, 0x1C, 0x14);bit_Cal(60, 0x08, 0x08);
            break;
        case 1:
            bit_Cal(62, 0x38, 0x00);bit_Cal(61, 0x1C, 0x10);bit_Cal(60, 0x08, 0x08);
            break;
        case 2:
            bit_Cal(62, 0x38, 0x30);bit_Cal(61, 0x1C, 0x0C);bit_Cal(60, 0x08, 0x08);
            break;
        case 3:
            bit_Cal(62, 0x38, 0x20);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x08);
            break;
        case 4:
            bit_Cal(62, 0x38, 0x08);bit_Cal(61, 0x1C, 0x18);bit_Cal(60, 0x08, 0x08);
            break;
        case 5:
            bit_Cal(62, 0x38, 0x28);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x00);
            break;
        case 6:
            bit_Cal(62, 0x38, 0x38);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x00);
            break;
        case 7:
            bit_Cal(62, 0x38, 0x00);bit_Cal(61, 0x1C, 0x14);bit_Cal(60, 0x08, 0x08);
            break;
        case 8:
            bit_Cal(62, 0x38, 0x38);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x08);
            break;
        case 9:
            bit_Cal(62, 0x38, 0x28);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x08);
            break;
        default:
            bit_Cal(62, 0x38, 0x00);bit_Cal(61, 0x1C, 0x08);bit_Cal(60, 0x08, 0x00);//��ʾ��-��
            break;
    }
    /* 3�Ź�λ�趨�¶�С���� */
    bit_Cal(63, 0x20, 0x20);

     /**********��λ3��ʵ��ʱ����ʾ**********/
    Val = work_num[2].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(79, 0xC0, 0xC0);bit_Cal(78, 0xF0, 0xB0);
            break;
        case 1:
            bit_Cal(79, 0xC0, 0x00);bit_Cal(78, 0xF0, 0xA0);
            break;
        case 2:
            bit_Cal(79, 0xC0, 0x80);bit_Cal(78, 0xF0, 0x70);
            break;
        default:
            bit_Cal(79, 0xC0, 0x00);bit_Cal(78, 0xF0, 0x40);//��ʾ��-��
            break;
    }

    Val = work_num[2].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(77, 0xE0, 0xE0);bit_Cal(76, 0xE0, 0xA0);bit_Cal(75, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(77, 0xE0, 0x00);bit_Cal(76, 0xE0, 0x20);bit_Cal(75, 0x80, 0x80);
            break;
        case 2:
            bit_Cal(77, 0xE0, 0xA0);bit_Cal(76, 0xE0, 0xE0);bit_Cal(75, 0x80, 0x00);
            break;
        case 3:
            bit_Cal(77, 0xE0, 0x20);bit_Cal(76, 0xE0, 0xE0);bit_Cal(75, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(77, 0xE0, 0x40);bit_Cal(76, 0xE0, 0x60);bit_Cal(75, 0x80, 0x80);
            break;
        case 5:
            bit_Cal(77, 0xE0, 0x60);bit_Cal(76, 0xE0, 0xC0);bit_Cal(75, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(77, 0xE0, 0xE0);bit_Cal(76, 0xE0, 0xC0);bit_Cal(75, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(77, 0xE0, 0x20);bit_Cal(76, 0xE0, 0x20);bit_Cal(75, 0x80, 0x80);
            break;
        case 8:
            bit_Cal(77, 0xE0, 0xE0);bit_Cal(76, 0xE0, 0xE0);bit_Cal(75, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(77, 0xE0, 0x60);bit_Cal(76, 0xE0, 0xE0);bit_Cal(75, 0x80, 0x80);
            break;
        default:
            bit_Cal(77, 0xE0, 0x00);bit_Cal(76, 0xE0, 0x40);bit_Cal(75, 0x80, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[2].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(74, 0xC0, 0xC0);bit_Cal(73, 0xE0, 0xA0);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(74, 0xC0, 0x00);bit_Cal(73, 0xE0, 0x00);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(74, 0xC0, 0x80);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(74, 0xC0, 0x00);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(74, 0xC0, 0x40);bit_Cal(73, 0xE0, 0x40);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(74, 0xC0, 0x40);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(74, 0xC0, 0xC0);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(74, 0xC0, 0x00);bit_Cal(73, 0xE0, 0x20);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(74, 0xC0, 0xC0);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(74, 0xC0, 0x40);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(74, 0xC0, 0x00);bit_Cal(73, 0xE0, 0x40);bit_Cal(72, 0xC0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[2].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(71, 0xE0, 0xA0);bit_Cal(70, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(71, 0xE0, 0x00);bit_Cal(70, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(71, 0xE0, 0xC0);bit_Cal(70, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(71, 0xE0, 0x40);bit_Cal(70, 0xF0, 0xF0);
            break;
        case 4:
            bit_Cal(71, 0xE0, 0x60);bit_Cal(70, 0xF0, 0x60);
            break;
        case 5:
            bit_Cal(71, 0xE0, 0x60);bit_Cal(70, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(71, 0xE0, 0xE0);bit_Cal(70, 0xF0, 0xD0);
            break;
        case 7:
            bit_Cal(71, 0xE0, 0x00);bit_Cal(70, 0xF0, 0x70);
            break;
        case 8:
            bit_Cal(71, 0xE0, 0xE0);bit_Cal(70, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(71, 0xE0, 0x60);bit_Cal(70, 0xF0, 0xF0);
            break;
        default:
            bit_Cal(71, 0xE0, 0x40);bit_Cal(70, 0xF0, 0x00);//��ʾ��-��
            break;
    }
    /* 3�Ź�λʵ��ʱ��ð�� */
    bit_Cal(75, 0x40, 0x40);

    /**********��λ3���趨ʱ����ʾ**********/
    Val = work_num[2].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
         case 0:
            bit_Cal(69, 0xE0, 0xA0);bit_Cal(68, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(69, 0xE0, 0x00);bit_Cal(68, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(69, 0xE0, 0xC0);bit_Cal(68, 0xF0, 0xB0);
            break;
        default:
            bit_Cal(69, 0xE0, 0x40);bit_Cal(68, 0xF0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[2].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(67, 0xE0, 0xA0);bit_Cal(66, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(67, 0xE0, 0x00);bit_Cal(66, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(67, 0xE0, 0xC0);bit_Cal(66, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(67, 0xE0, 0x40);bit_Cal(66, 0xF0, 0xF0);
            break;
        case 4:
            bit_Cal(67, 0xE0, 0x60);bit_Cal(66, 0xF0, 0x60);
            break;
        case 5:
            bit_Cal(67, 0xE0, 0x60);bit_Cal(66, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(67, 0xE0, 0xE0);bit_Cal(66, 0xF0, 0xD0);
            break;
        case 7:
            bit_Cal(67, 0xE0, 0x00);bit_Cal(66, 0xF0, 0x70);
            break;
        case 8:
            bit_Cal(67, 0xE0, 0xE0);bit_Cal(66, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(67, 0xE0, 0x60);bit_Cal(66, 0xF0, 0xF0);
            break;
        default:
            bit_Cal(67, 0xE0, 0x40);bit_Cal(66, 0xF0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[2].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(65, 0xC0, 0xC0);bit_Cal(64, 0xE0, 0xA0);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(65, 0xC0, 0x00);bit_Cal(64, 0xE0, 0x00);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(65, 0xC0, 0x80);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(65, 0xC0, 0x00);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(65, 0xC0, 0x40);bit_Cal(64, 0xE0, 0x40);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(65, 0xC0, 0x40);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(65, 0xC0, 0xC0);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(65, 0xC0, 0x00);bit_Cal(64, 0xE0, 0x20);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(65, 0xC0, 0xC0);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(65, 0xC0, 0x40);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(65, 0xC0, 0x00);bit_Cal(64, 0xE0, 0x40);bit_Cal(63, 0xC0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[2].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(62, 0xC0, 0xC0);bit_Cal(61, 0xE0, 0xA0);bit_Cal(60, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(62, 0xC0, 0x00);bit_Cal(61, 0xE0, 0x00);bit_Cal(60, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(62, 0xC0, 0x80);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(62, 0xC0, 0x00);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(62, 0xC0, 0x40);bit_Cal(61, 0xE0, 0x40);bit_Cal(60, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(62, 0xC0, 0x40);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(62, 0xC0, 0xC0);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(62, 0xC0, 0x00);bit_Cal(61, 0xE0, 0x20);bit_Cal(60, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(62, 0xC0, 0xC0);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(62, 0xC0, 0x40);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x60);
            break;
        default:
            bit_Cal(62, 0xC0, 0x00);bit_Cal(61, 0xE0, 0x40);bit_Cal(60, 0x60, 0x00);//��ʾ��-��
            break;
    }
    /* 3�Ź�λ�趨ʱ��ð�� */
    bit_Cal(65, 0x20, 0x20);
    /* 3�Ź�λ��rpm��ͼ�� */
    bit_Cal(60, 0x04, 0x04);
    
    /* 3�Ź�λ���桱ͼ�� */
    bit_Cal(60, 0x10, 0x10);

    /* 3�Ź�λ��min��ͼ�� */
    bit_Cal(60, 0x80, 0x80);

    /* 3�Ź�λ��4�Ź�λ֮����� */
    bit_Cal(60, 0x01, 0x01);

    /* 3�Ź�λת��ͼ�� */
    bit_Cal(79, 0x01, 0x01);//3�Ź�λת��ͼ��S2
    bit_Cal(79, 0x02, 0x02);//3�Ź�λת��ͼ��S3
    bit_Cal(78, 0x01, 0x01);//3�Ź�λת��ͼ��S1
    
    /* 3�Ź�λ����ͼ�� */
    bit_Cal(79, 0x04, 0x04);//3�Ź�λ����ͼ��S4
    bit_Cal(79, 0x10, 0x10);//3�Ź�λ����ͼ��S5
    bit_Cal(79, 0x08, 0x08);//3�Ź�λ�¶�̽ͷͼ��
    
    /* 3�Ź�λʱ��ͼ�� */
    bit_Cal(79, 0x20, 0x20);//3�Ź�λʱ��ͼ��

    /*******************************4�Ź�λ*******************************/
    /**********��λ4��ʵ��ת����ʾ**********/
    if (work_num[3].Speed.Display_Rel > 999) // ����999ʱ
    {
        Val = work_num[3].Speed.Display_Rel / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(58, 0x02, 0x00);bit_Cal(57, 0x02, 0x02);//��ʾ����1
        }
       else
       {
            bit_Cal(58, 0x02, 0x02);bit_Cal(57, 0x02, 0x02);//��ʾ����0
       }
    }
    else
    {
        bit_Cal(58, 0x02, 0x02);bit_Cal(57, 0x02, 0x02);//��ʾ����0
    }
    
   if (work_num[3].Speed.Display_Rel > 99) // ����99ʱ
   {
       Val = work_num[3].Speed.Display_Rel / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x07);bit_Cal(55, 0x03, 0x02);bit_Cal(54, 0x02, 0x02);
            break;
       case 1:
            bit_Cal(57, 0x01, 0x00);bit_Cal(56, 0x07, 0x01);bit_Cal(55, 0x03, 0x00);bit_Cal(54, 0x02, 0x02);
            break;
       case 2:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x05);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x00);
            break;
       case 3:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x01);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       case 4:
            bit_Cal(57, 0x01, 0x00);bit_Cal(56, 0x07, 0x03);bit_Cal(55, 0x03, 0x01);bit_Cal(54, 0x02, 0x02);
            break;
       case 5:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x02);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       case 6:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x06);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       case 7:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x01);bit_Cal(55, 0x03, 0x00);bit_Cal(54, 0x02, 0x02);
            break;
       case 8:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x07);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       case 9:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x03);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x07);bit_Cal(55, 0x02, 0x02);bit_Cal(54, 0x02, 0x02);;//��ʾ������
   }

   if (work_num[3].Speed.Display_Rel > 9) // ����9ʱ
   {
       Val = work_num[3].Speed.Display_Rel / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x03);bit_Cal(52, 0x03, 0x02);bit_Cal(51, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(54, 0x01, 0x00);bit_Cal(53, 0x03, 0x00);bit_Cal(52, 0x03, 0x00);bit_Cal(51, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x02);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x00);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(54, 0x01, 0x00);bit_Cal(53, 0x03, 0x01);bit_Cal(52, 0x03, 0x01);bit_Cal(51, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x01);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x03);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x00);bit_Cal(52, 0x03, 0x00);bit_Cal(51, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x03);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x01);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
       bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x03);bit_Cal(52, 0x03, 0x02);bit_Cal(51, 0x03, 0x03);//��ʾ������
   }
    bit_Cal(50, 0x01, 0x01);//ʵ��ת�ٸ�λֻ����ʾ��

    /**********��λ4���趨ת����ʾ**********/
    if (work_num[3].Speed.Display_Set > 999) // ����999ʱ
    {
        Val = work_num[3].Speed.Display_Set / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(49, 0x01, 0x00);bit_Cal(48, 0x01, 0x01);//��ʾ����1
        }
       else
       {
            bit_Cal(49, 0x01, 0x01);bit_Cal(48, 0x01, 0x01);//��ʾ����0
       }
    }
    else
    {
        bit_Cal(49, 0x01, 0x01);bit_Cal(48, 0x01, 0x01);//��ʾ����0
    }
    
   if (work_num[3].Speed.Display_Set > 99) // ����99ʱ
   {
       Val = work_num[3].Speed.Display_Set / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x02);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);
            break;
       case 1:
            bit_Cal(47, 0x01, 0x00);bit_Cal(46, 0x01, 0x00);bit_Cal(45, 0x03, 0x00);bit_Cal(44, 0x03, 0x01);bit_Cal(43, 0x01, 0x01);
            break;
       case 2:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x00);bit_Cal(45, 0x03, 0x03);bit_Cal(44, 0x03, 0x02);bit_Cal(43, 0x01, 0x01);
            break;
       case 3:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x00);bit_Cal(45, 0x03, 0x01);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);
            break;
       case 4:
            bit_Cal(47, 0x01, 0x00);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x01);bit_Cal(44, 0x03, 0x01);bit_Cal(43, 0x01, 0x01);
            break;
       case 5:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x01);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x00);
            break;
       case 6:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x03);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x00);
            break;
       case 7:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x00);bit_Cal(45, 0x03, 0x00);bit_Cal(44, 0x03, 0x01);bit_Cal(43, 0x01, 0x01);
            break;
       case 8:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x03);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);
            break;
       case 9:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x01);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x02);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);//��ʾ������
   }

   if (work_num[3].Speed.Display_Set > 9) // ����9ʱ
   {
        Val = work_num[3].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
            case 0:
                bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x05);bit_Cal(41, 0x03, 0x03);
                break;
            case 1:
                bit_Cal(43, 0x06, 0x00);bit_Cal(42, 0x07, 0x04);bit_Cal(41, 0x03, 0x02);
                break;
            case 2:
                bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x02);bit_Cal(41, 0x03, 0x03);
                break;
            case 3:
                bit_Cal(43, 0x06, 0x04);bit_Cal(42, 0x07, 0x06);bit_Cal(41, 0x03, 0x03);
                break;
            case 4:
                bit_Cal(43, 0x06, 0x00);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x02);
                break;
            case 5:
                bit_Cal(43, 0x06, 0x04);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x01);
                break;
            case 6:
                bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x01);
                break;
            case 7:
                bit_Cal(43, 0x06, 0x00);bit_Cal(42, 0x07, 0x04);bit_Cal(41, 0x03, 0x03);
                break;
            case 8:
                bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x03);
                break;
            case 9:
                bit_Cal(43, 0x06, 0x04);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x03);
                break;
            default:
                break;
        }
    }
    else
    {
        bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x05);bit_Cal(41, 0x03, 0x03);//��ʾ������
    }
    bit_Cal(40, 0x02, 0x02);//ʵ��ת�ٸ�λֻ����ʾ��

    /**********��λ4��ʵ���¶���ʾ**********/
    if (work_num[3].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[3].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) / 1000 % 10;//�������0��������999���Բ�����ʾ
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = 10;//��ʾ��-��
    }
    switch (Val)
    {
        case 0:
            if (work_num[3].Temp.Display_Rel > 999)//��ʾ0
            {
                bit_Cal(58, 0x0C, 0x0C);bit_Cal(57, 0x1C, 0x14);bit_Cal(56, 0x18, 0x18);
            }
            else//����ʾ��λ
            {
                bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x00);bit_Cal(56, 0x18, 0x00);
            }
            break;
        case 1:
            bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x00);bit_Cal(56, 0x18, 0x18);
            break;
        case 2:
            bit_Cal(58, 0x0C, 0x08);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x08);
            break;
        case 3:
            bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x18);
            break;
        case 4:
            bit_Cal(58, 0x0C, 0x04);bit_Cal(57, 0x1C, 0x08);bit_Cal(56, 0x18, 0x18);
            break;
        case 5:
            bit_Cal(58, 0x0C, 0x04);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x10);
            break;
        case 6:
            bit_Cal(58, 0x0C, 0x0C);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x10);
            break;
        case 7:
            bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x04);bit_Cal(56, 0x18, 0x18);
            break;
        case 8:
            bit_Cal(58, 0x0C, 0x0C);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x18);
            break;
        case 9:
            bit_Cal(58, 0x0C, 0x04);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x18);
            break;
        default:
            bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x08);bit_Cal(56, 0x18, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[3].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[3].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = 10;//��ʾ��-��
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[3].Temp.Display_Rel > 99)//��ʾ��
            {
                bit_Cal(55, 0x3C, 0x3C);bit_Cal(54, 0x38, 0x2C);
            }
            else//����ʾ
            {
                bit_Cal(55, 0x3C, 0x00);bit_Cal(54, 0x38, 0x00);
            }
            break;
        case 1:
            bit_Cal(55, 0x3C, 0x00);bit_Cal(54, 0x38, 0x28);
            break;
        case 2:
            bit_Cal(55, 0x3C, 0x34);bit_Cal(54, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(55, 0x3C, 0x24);bit_Cal(54, 0x38, 0x3C);
            break;
        case 4:
            bit_Cal(55, 0x3C, 0x08);bit_Cal(54, 0x38, 0x3C);
            break;
        case 5:
            bit_Cal(55, 0x3C, 0x2C);bit_Cal(54, 0x38, 0x30);
            break;
        case 6:
            bit_Cal(55, 0x3C, 0x3C);bit_Cal(54, 0x38, 0x30);
            break;
        case 7:
            bit_Cal(55, 0x3C, 0x04);bit_Cal(54, 0x38, 0x28);
            break;
        case 8:
            bit_Cal(55, 0x3C, 0x3C);bit_Cal(54, 0x38, 0x3C);
            break;
        case 9:
            bit_Cal(55, 0x3C, 0x2C);bit_Cal(54, 0x38, 0x3C);
            break;
        default:
            bit_Cal(55, 0x3C, 0x00);bit_Cal(54, 0x38, 0x10);
            break;
    }

    if (work_num[3].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[3].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x14);bit_Cal(52, 0x1C, 0x1C);
            break;
        case 1:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x00);bit_Cal(52, 0x1C, 0x0C);
            break;
        case 2:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x1C);bit_Cal(52, 0x1C, 0x14);
            break;
        case 3:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x0C);bit_Cal(52, 0x1C, 0x1C);
            break;
        case 4:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x08);bit_Cal(52, 0x1C, 0x0C);
            break;
        case 5:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x0C);bit_Cal(52, 0x1C, 0x18);
            break;
        case 6:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x1C);bit_Cal(52, 0x1C, 0x18);
            break;
        case 7:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x04);bit_Cal(52, 0x1C, 0x0C);
            break;
        case 8:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x1C);bit_Cal(52, 0x1C, 0x1C);
            break;
        case 9:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x0C);bit_Cal(52, 0x1C, 0x1C);
            break;
        default:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x08);bit_Cal(52, 0x1C, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[3].Temp.Display_Rel >= 0)//���ڵ���0ʱ
    {
        Val = work_num[3].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) % 10;
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(51, 0x1C, 0x1C);bit_Cal(50, 0x0E, 0x0A);bit_Cal(49, 0x02, 0x02);
            break;
        case 1:
            bit_Cal(51, 0x1C, 0x00);bit_Cal(50, 0x0E, 0x08);bit_Cal(49, 0x02, 0x02);
            break;
        case 2:
            bit_Cal(51, 0x1C, 0x18);bit_Cal(50, 0x0E, 0x06);bit_Cal(49, 0x02, 0x02);
            break;
        case 3:
            bit_Cal(51, 0x1C, 0x10);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x02);
            break;
        case 4:
            bit_Cal(51, 0x1C, 0x04);bit_Cal(50, 0x0E, 0x0C);bit_Cal(49, 0x02, 0x02);
            break;
        case 5:
            bit_Cal(51, 0x1C, 0x14);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x00);
            break;
        case 6:
            bit_Cal(51, 0x1C, 0x1C);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x00);
            break;
        case 7:
            bit_Cal(51, 0x1C, 0x00);bit_Cal(50, 0x0E, 0x0A);bit_Cal(49, 0x02, 0x02);
            break;
        case 8:
            bit_Cal(51, 0x1C, 0x1C);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x02);
            break;
        case 9:
            bit_Cal(51, 0x1C, 0x14);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x02);
            break;
        default:
            bit_Cal(51, 0x1C, 0x00);bit_Cal(50, 0x0E, 0x04);bit_Cal(49, 0x02, 0x00);//��ʾ��-��
            break;
    }

    /* 4�Ź�λʵ���¶�С���� */
    bit_Cal(52, 0x20, 0x20);

    /**********��λ4���趨�¶���ʾ**********/
    if (work_num[3].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[3].Temp.Display_Set / 1000 % 10;
    }
    else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Set) / 1000 % 10;//�������0��������999���Բ�����ʾ
    }
    else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
    {
        Val = 10;//��ʾ��-��
    }
    switch (Val)
    {
        case 0:
            if (work_num[3].Temp.Display_Set > 999)//��ʾ0
            {
                bit_Cal(49, 0x1C, 0x1C);bit_Cal(48, 0x0E, 0x0A);bit_Cal(47, 0x02, 0x02);
            }
            else//����ʾ��λ
            {
                bit_Cal(49, 0x1C, 0x00);bit_Cal(48, 0x0E, 0x00);bit_Cal(47, 0x02, 0x00);
            }
            break;
        case 1:
            bit_Cal(49, 0x1C, 0x00);bit_Cal(48, 0x0E, 0x08);bit_Cal(47, 0x02, 0x02);
            break;
        case 2:
            bit_Cal(49, 0x1C, 0x18);bit_Cal(48, 0x0E, 0x06);bit_Cal(47, 0x02, 0x02);
            break;
        case 3:
            bit_Cal(49, 0x1C, 0x10);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x02);
            break;
        case 4:
            bit_Cal(49, 0x1C, 0x04);bit_Cal(48, 0x0E, 0x0C);bit_Cal(47, 0x02, 0x02);
            break;
        case 5:
            bit_Cal(49, 0x1C, 0x14);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x00);
            break;
        case 6:
            bit_Cal(49, 0x1C, 0x1C);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x00);
            break;
        case 7:
            bit_Cal(49, 0x1C, 0x00);bit_Cal(48, 0x0E, 0x0A);bit_Cal(47, 0x02, 0x02);
            break;
        case 8:
            bit_Cal(49, 0x1C, 0x1C);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x02);
            break;
        case 9:
            bit_Cal(49, 0x1C, 0x14);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x02);
            break;
        default:
            bit_Cal(49, 0x1C, 0x00);bit_Cal(48, 0x0E, 0x04);bit_Cal(47, 0x02, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[3].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[3].Temp.Display_Set / 100 % 10;
    }
    else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
    {
        Val = 10;//��ʾ��-��
    }
    else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[3].Temp.Display_Set > 999)//��ʾ0
            {
                bit_Cal(47, 0x1C, 0x1C);bit_Cal(46, 0x0E, 0x0A);bit_Cal(45, 0x04, 0x04);
            }
            else//����ʾ��λ
            {
                bit_Cal(47, 0x1C, 0x00);bit_Cal(46, 0x0E, 0x00);bit_Cal(45, 0x04, 0x00);
            }
            break;
        case 1:
            bit_Cal(47, 0x1C, 0x00);bit_Cal(46, 0x0E, 0x08);bit_Cal(45, 0x04, 0x04);
            break;
        case 2:
            bit_Cal(47, 0x1C, 0x18);bit_Cal(46, 0x0E, 0x06);bit_Cal(45, 0x04, 0x04);
            break;
        case 3:
            bit_Cal(47, 0x1C, 0x10);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x04);
            break;
        case 4:
            bit_Cal(47, 0x1C, 0x04);bit_Cal(46, 0x0E, 0x0C);bit_Cal(45, 0x04, 0x04);
            break;
        case 5:
            bit_Cal(47, 0x1C, 0x14);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x00);
            break;
        case 6:
            bit_Cal(47, 0x1C, 0x1C);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x00);
            break;
        case 7:
            bit_Cal(47, 0x1C, 0x00);bit_Cal(46, 0x0E, 0x0A);bit_Cal(45, 0x04, 0x04);
            break;
        case 8:
            bit_Cal(47, 0x1C, 0x1C);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x04);
            break;
        case 9:
            bit_Cal(47, 0x1C, 0x14);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x04);
            break;
        default:
            bit_Cal(47, 0x1C, 0x00);bit_Cal(46, 0x0E, 0x04);bit_Cal(45, 0x04, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[3].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[3].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Set) / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Set) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(45, 0x18, 0x18);bit_Cal(44, 0x1C, 0x14);bit_Cal(43, 0x18, 0x18);
            break;
        case 1:
            bit_Cal(45, 0x18, 0x00);bit_Cal(44, 0x1C, 0x00);bit_Cal(43, 0x18, 0x18);
            break;
        case 2:
            bit_Cal(45, 0x18, 0x10);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x08);
            break;
        case 3:
            bit_Cal(45, 0x18, 0x00);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x18);
            break;
        case 4:
            bit_Cal(45, 0x18, 0x08);bit_Cal(44, 0x1C, 0x08);bit_Cal(43, 0x18, 0x18);
            break;
        case 5:
            bit_Cal(45, 0x18, 0x08);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x10);
            break;
        case 6:
            bit_Cal(45, 0x18, 0x18);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x10);
            break;
        case 7:
            bit_Cal(45, 0x18, 0x00);bit_Cal(44, 0x1C, 0x04);bit_Cal(43, 0x18, 0x18);
            break;
        case 8:
            bit_Cal(45, 0x18, 0x18);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x18);
            break;
        case 9:
            bit_Cal(45, 0x18, 0x08);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x18);
            break;
        default:
            bit_Cal(45, 0x18, 0x00);bit_Cal(44, 0x1C, 0x08);bit_Cal(43, 0x18, 0x00);//��ʾ��-��
            break;
    }

    if (work_num[3].Temp.Display_Set >= 0)//���ڵ���0ʱ
    {
        Val = work_num[3].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Set) % 10;
    }
    else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Set) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(42, 0x38, 0x38);bit_Cal(41, 0x1C, 0x14);bit_Cal(40, 0x08, 0x08);
            break;
        case 1:
            bit_Cal(42, 0x38, 0x00);bit_Cal(41, 0x1C, 0x10);bit_Cal(40, 0x08, 0x08);
            break;
        case 2:
            bit_Cal(42, 0x38, 0x30);bit_Cal(41, 0x1C, 0x0C);bit_Cal(40, 0x08, 0x08);
            break;
        case 3:
            bit_Cal(42, 0x38, 0x20);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x08);
            break;
        case 4:
            bit_Cal(42, 0x38, 0x08);bit_Cal(41, 0x1C, 0x18);bit_Cal(40, 0x08, 0x08);
            break;
        case 5:
            bit_Cal(42, 0x38, 0x28);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x00);
            break;
        case 6:
            bit_Cal(42, 0x38, 0x38);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x00);
            break;
        case 7:
            bit_Cal(42, 0x38, 0x00);bit_Cal(41, 0x1C, 0x14);bit_Cal(40, 0x08, 0x08);
            break;
        case 8:
            bit_Cal(42, 0x38, 0x38);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x08);
            break;
        case 9:
            bit_Cal(42, 0x38, 0x28);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x08);
            break;
        default:
            bit_Cal(42, 0x38, 0x00);bit_Cal(41, 0x1C, 0x08);bit_Cal(40, 0x08, 0x00);//��ʾ��-��
            break;
    }
    /* 4�Ź�λ�趨�¶�С���� */
    bit_Cal(43, 0x20, 0x20);

     /**********��λ4��ʵ��ʱ����ʾ**********/
    Val = work_num[3].Time.Display_Rel / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(59, 0xC0, 0xC0);bit_Cal(58, 0xF0, 0xB0);
            break;
        case 1:
            bit_Cal(59, 0xC0, 0x00);bit_Cal(58, 0xF0, 0xA0);
            break;
        case 2:
            bit_Cal(59, 0xC0, 0x80);bit_Cal(58, 0xF0, 0x70);
            break;
        default:
            bit_Cal(59, 0xC0, 0x00);bit_Cal(58, 0xF0, 0x40);//��ʾ��-��
            break;
    }

    Val = work_num[3].Time.Display_Rel / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(57, 0xE0, 0xE0);bit_Cal(56, 0xE0, 0xA0);bit_Cal(55, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(57, 0xE0, 0x00);bit_Cal(56, 0xE0, 0x20);bit_Cal(55, 0x80, 0x80);
            break;
        case 2:
            bit_Cal(57, 0xE0, 0xA0);bit_Cal(56, 0xE0, 0xE0);bit_Cal(55, 0x80, 0x00);
            break;
        case 3:
            bit_Cal(57, 0xE0, 0x20);bit_Cal(56, 0xE0, 0xE0);bit_Cal(55, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(57, 0xE0, 0x40);bit_Cal(56, 0xE0, 0x60);bit_Cal(55, 0x80, 0x80);
            break;
        case 5:
            bit_Cal(57, 0xE0, 0x60);bit_Cal(56, 0xE0, 0xC0);bit_Cal(55, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(57, 0xE0, 0xE0);bit_Cal(56, 0xE0, 0xC0);bit_Cal(55, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(57, 0xE0, 0x20);bit_Cal(56, 0xE0, 0x20);bit_Cal(55, 0x80, 0x80);
            break;
        case 8:
            bit_Cal(57, 0xE0, 0xE0);bit_Cal(56, 0xE0, 0xE0);bit_Cal(55, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(57, 0xE0, 0x60);bit_Cal(56, 0xE0, 0xE0);bit_Cal(55, 0x80, 0x80);
            break;
        default:
            bit_Cal(57, 0xE0, 0x00);bit_Cal(56, 0xE0, 0x40);bit_Cal(55, 0x80, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[3].Time.Display_Rel % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(54, 0xC0, 0xC0);bit_Cal(53, 0xE0, 0xA0);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(54, 0xC0, 0x00);bit_Cal(53, 0xE0, 0x00);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(54, 0xC0, 0x80);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(54, 0xC0, 0x00);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(54, 0xC0, 0x40);bit_Cal(53, 0xE0, 0x40);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(54, 0xC0, 0x40);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(54, 0xC0, 0xC0);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(54, 0xC0, 0x00);bit_Cal(53, 0xE0, 0x20);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(54, 0xC0, 0xC0);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(54, 0xC0, 0x40);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(54, 0xC0, 0x00);bit_Cal(53, 0xE0, 0x40);bit_Cal(52, 0xC0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[3].Time.Display_Rel % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(51, 0xE0, 0xA0);bit_Cal(50, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(51, 0xE0, 0x00);bit_Cal(50, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(51, 0xE0, 0xC0);bit_Cal(50, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(51, 0xE0, 0x40);bit_Cal(50, 0xF0, 0xF0);
            break;
        case 4:
            bit_Cal(51, 0xE0, 0x60);bit_Cal(50, 0xF0, 0x60);
            break;
        case 5:
            bit_Cal(51, 0xE0, 0x60);bit_Cal(50, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(51, 0xE0, 0xE0);bit_Cal(50, 0xF0, 0xD0);
            break;
        case 7:
            bit_Cal(51, 0xE0, 0x00);bit_Cal(50, 0xF0, 0x70);
            break;
        case 8:
            bit_Cal(51, 0xE0, 0xE0);bit_Cal(50, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(51, 0xE0, 0x60);bit_Cal(50, 0xF0, 0xF0);
            break;
        default:
            bit_Cal(51, 0xE0, 0x40);bit_Cal(50, 0xF0, 0x00);//��ʾ��-��
            break;
    }
    /* 4�Ź�λʵ��ʱ��ð�� */
    bit_Cal(55, 0x40, 0x40);

    /**********��λ3���趨ʱ����ʾ**********/
    Val = work_num[3].Time.Display_Set / 3600 / 10;//����ʮλΪ��λ��Сʱ��
    switch (Val)
    {
         case 0:
            bit_Cal(49, 0xE0, 0xA0);bit_Cal(48, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(49, 0xE0, 0x00);bit_Cal(48, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(49, 0xE0, 0xC0);bit_Cal(48, 0xF0, 0xB0);
            break;
        default:
            bit_Cal(49, 0xE0, 0x40);bit_Cal(48, 0xF0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[3].Time.Display_Set / 3600 % 10;// �����λΪ��λ��Сʱ��
    switch (Val)
    {
        case 0:
            bit_Cal(47, 0xE0, 0xA0);bit_Cal(46, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(47, 0xE0, 0x00);bit_Cal(46, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(47, 0xE0, 0xC0);bit_Cal(46, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(47, 0xE0, 0x40);bit_Cal(46, 0xF0, 0xF0);
            break;
        case 4:
            bit_Cal(47, 0xE0, 0x60);bit_Cal(46, 0xF0, 0x60);
            break;
        case 5:
            bit_Cal(47, 0xE0, 0x60);bit_Cal(46, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(47, 0xE0, 0xE0);bit_Cal(46, 0xF0, 0xD0);
            break;
        case 7:
            bit_Cal(47, 0xE0, 0x00);bit_Cal(46, 0xF0, 0x70);
            break;
        case 8:
            bit_Cal(47, 0xE0, 0xE0);bit_Cal(46, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(47, 0xE0, 0x60);bit_Cal(46, 0xF0, 0xF0);
            break;
        default:
            bit_Cal(47, 0xE0, 0x40);bit_Cal(46, 0xF0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[3].Time.Display_Set % 3600 / 60 / 10; // ����ʮ��λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(45, 0xC0, 0xC0);bit_Cal(44, 0xE0, 0xA0);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(45, 0xC0, 0x00);bit_Cal(44, 0xE0, 0x00);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(45, 0xC0, 0x80);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(45, 0xC0, 0x00);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(45, 0xC0, 0x40);bit_Cal(44, 0xE0, 0x40);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(45, 0xC0, 0x40);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(45, 0xC0, 0xC0);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(45, 0xC0, 0x00);bit_Cal(44, 0xE0, 0x20);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(45, 0xC0, 0xC0);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(45, 0xC0, 0x40);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(45, 0xC0, 0x00);bit_Cal(44, 0xE0, 0x40);bit_Cal(43, 0xC0, 0x00);//��ʾ��-��
            break;
    }

    Val = work_num[3].Time.Display_Set % 3600 / 60 % 10;	// �������λΪ��λ�ķ�����
    switch (Val)
    {
        case 0:
            bit_Cal(42, 0xC0, 0xC0);bit_Cal(41, 0xE0, 0xA0);bit_Cal(40, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(42, 0xC0, 0x00);bit_Cal(41, 0xE0, 0x00);bit_Cal(40, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(42, 0xC0, 0x80);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(42, 0xC0, 0x00);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(42, 0xC0, 0x40);bit_Cal(41, 0xE0, 0x40);bit_Cal(40, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(42, 0xC0, 0x40);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(42, 0xC0, 0xC0);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(42, 0xC0, 0x00);bit_Cal(41, 0xE0, 0x20);bit_Cal(40, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(42, 0xC0, 0xC0);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(42, 0xC0, 0x40);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x60);
            break;
        default:
            bit_Cal(42, 0xC0, 0x00);bit_Cal(41, 0xE0, 0x40);bit_Cal(40, 0x60, 0x00);//��ʾ��-��
            break;
    }
    /* 4�Ź�λ�趨ʱ��ð�� */
    bit_Cal(45, 0x20, 0x20);
    /* 4�Ź�λ��rpm��ͼ�� */
    bit_Cal(40, 0x04, 0x04);
    
    /* 4�Ź�λ���桱ͼ�� */
    bit_Cal(40, 0x10, 0x10);

    /* 4�Ź�λ��min��ͼ�� */
    bit_Cal(40, 0x80, 0x80);

    /* 4�Ź�λ��4�Ź�λ֮����� */
    bit_Cal(40, 0x01, 0x01);

    /* 4�Ź�λת��ͼ�� */
    bit_Cal(59, 0x01, 0x01);//4�Ź�λת��ͼ��S2
    bit_Cal(59, 0x02, 0x02);//4�Ź�λת��ͼ��S3
    bit_Cal(58, 0x01, 0x01);//4�Ź�λת��ͼ��S1
    
    /* 4�Ź�λ����ͼ�� */
    bit_Cal(59, 0x04, 0x04);//4�Ź�λ����ͼ��S4
    bit_Cal(59, 0x10, 0x10);//4�Ź�λ����ͼ��S5
    bit_Cal(59, 0x08, 0x08);//4�Ź�λ�¶�̽ͷͼ��
    
    /* 4�Ź�λʱ��ͼ�� */
    bit_Cal(59, 0x20, 0x20);//4�Ź�λʱ��ͼ��

    /**********���ݷ���**********/
    for(uint8_t i=0;i<40;i++)
    {
        Write_Addr_Dat_N(IC1, i, seg[i+40], 1);
    }
}

/**
 * @brief ��ʾ��Ļ����
 *
 */
void Show_Display(void)
{
    
    /**********LCD��ʼ��*************/
    Lcd_Init();

    while(1)
    {
        Display_IC2(Work_Num);
        Display_IC1(Work_Num);
        vTaskDelay(10);
    }
}
