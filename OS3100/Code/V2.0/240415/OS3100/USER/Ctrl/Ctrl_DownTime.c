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
    if(DownTime_Over==1)//��λ����ʱ����
    {    
        DownTime_Over = 0;//������ʱ�����ı�־λ����
        Ctrl_Time = Set_Time;//������ʱ�����¸�ֵ������ʱ��  
        Beep_Flash = 5;//��������5��
		sys.Motor_Stop  = 1;
		Speed_ADDMode = 2;//�������ģʽ��
    }
    if(sys.Run_Status && sys.Motor_Stop == 0)//����ϵͳ�Ͳ���ֹͣ״̬��
    {
        T += dT;
        if(T == 1000)//1S
        {
            if(Time_State == 0 && DownTime_Over == 0 && Ctrl_Speed)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            { 
                if(Ctrl_Time)
                    Ctrl_Time--;//����ʱ��--
                else
                {
                    DownTime_Over= 1;//time1����ʱ����
                }
            }
            T = 0;//��������
        }    
    }
    else
    {
        DownTime_Over = 0;//������ʱ�����ı�־λ����
    }
}
