#include "TimeDown.h"

/**********ȫ�ֱ���**********/
uint8_t time_disable;//�رռ�ʱ
uint8_t time_Last;//һֱ��ʱ

/*
*****************************************************************
 * ����ԭ�ͣ� void Sys_Init(void)
 * ��    �ܣ� ʱ�䵹��ʱ���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Cheak_TimeDown(uint16_t dT)
{
    static uint16_t T;
    if(ADD_Mode != 2)//ϵͳ�����Ϳ�ʼ����ʱ
        return;  
    if(T == 1000)//1S
    {
        if(time_disable==0)
            return;
        if(rel_time)//ʵ��ʱ�����0
        {
            rel_time--;//ÿһ���һ
        }
        else//����ʱ����
        {
            time_disable = 0;//�رյ���ʱ��־λ
            Beep_Flash = 5;
        }    
    } 
    else if(T > 1000)//����1S��
    {
        T = dT;//��Ϊ�Ѿ��Ա�++��
    }    
    T += dT;//������100ms
}
