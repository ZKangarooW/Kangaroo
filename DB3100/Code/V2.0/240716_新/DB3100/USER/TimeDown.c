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
        if(time_Last == 1)
            return;
        if(rel_time)//ʵ��ʱ�����0
        {
            rel_time--;//ÿһ���һ
        }
        else//����ʱ����
        {
            Run_Status = 0;//ϵͳ�ر�
            time_disable = 1;//�رյ���ʱ��־λ
            ADD_Mode = 0;//����ģʽ��0
			Flash_Read((uint8_t *)(&Param),sizeof(Param));
			set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
			set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
            Beep_Flash = 5;
			SetOK_Flag = 1;
        }    
    } 
    else if(T > 1000)//����1S��
    {
        T = dT;//��Ϊ�Ѿ��Ա�++��
    }    
    T += dT;//������100ms
}
