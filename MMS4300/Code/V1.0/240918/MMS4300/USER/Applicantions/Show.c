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

void Display_IC1(_Work_Num_ work_num[])
{
    uint8_t Val;// ���ڰ�ʮ��ȡ����������
    
    bit_Cal(0, 0xff, 0xff);
    bit_Cal(1, 0xff, 0xff);
    /**********���ݷ���**********/
    for(uint8_t i=0;i<31;i++)
    {
        Write_Addr_Dat_N(IC1, i*2, seg[i], 1);
    }
}

void Display_IC2(_Work_Num_ work_num[])
{
    uint8_t Val;// ���ڰ�ʮ��ȡ����������
    
    /**********���ݷ���**********/
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
    Display_IC2(Work_Num);
    Display_IC1(Work_Num);
}
