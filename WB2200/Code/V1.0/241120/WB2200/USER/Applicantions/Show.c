#include "Show.h"

/**********ȫ�ֱ�������******/
float Speed_Twinkle_Time,Time_Twinkle_Time;//�ٶ���˸ʱ���ʱ����˸ʱ��

/**********�ֲ���������******/
uint8_t Speed_ShowFlag,Time_ShowFlag;//�ٶȡ�ʱ����ʾ�ı�־λ 0:���� 1��Ϩ��

uint8_t cnt=0;
uint8_t seg[16] = {0};

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
    
    if(dis_temp > 999)//����999ʱ
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
    
    if(dis_temp > 99)//����99ʱ
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
    
        bit_Cal(2,0x04,0x04);//�¶�С����
        SH=dis_time/3600/10;//����ʮλ��λ��Сʱ��
        H=dis_time/3600%10;//�����λ��λ��Сʱ��
        SM=dis_time%3600/60/10;//����ʮ��λ��λ�ķ�����
        M=dis_time%3600/60%10;//�������λ��λ�ķ�����
    
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
            default:
                break;
        }
	TM1640_Write_DATA(cnt, seg[cnt]);
	cnt ++;
	if(cnt >= 16)
		cnt= 0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Show_Display(void)
 * ��    �ܣ���ʾ��Ļ����
*****************************************************************
*/
void Show_Display(void)
{	
    Display_Screen(-158,3590);
}
