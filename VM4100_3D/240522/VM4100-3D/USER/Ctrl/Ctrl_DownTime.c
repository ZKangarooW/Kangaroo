#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Cheak_TimeDown(uint16_t dT)
 * ��    �ܣ� ʱ�䵹��ʱ���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Cheak_TimeDown(uint16_t dT)
{
    static uint16_t T;
    if(DownTime_Over ==1)//����ʱ����
    {    
        DownTime_Over = 0;//������ʱ�����ı�־λ����
        Rel_Time = Set_Time;//������ʱ�����¸�ֵ������ʱ��  
        sys.Run_Status = 0;//�ر�
    }
    if(sys.Run_Status)//����ϵͳ
    {
        T += dT;
        if(T == 1000)//1S
        {
            if(Time_State && DownTime_Over == 0 && Rel_Time)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Rel_Time)
                    Rel_Time--;//����ʱ��--
                if(Rel_Time == 0)
                {
                    DownTime_Over = 1;//time1����ʱ����
                }
            }
            T = 0;//��������
        }    
    }
    else
    {
        DownTime_Over = 0;//��ʱ���־����
    }
}
