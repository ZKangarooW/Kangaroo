#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Cheak_TimeDown(float dT)
 * ��    �ܣ�ʱ�䵹��ʱ���
 * ��    ��: dT:ִ������
 * ��    ����float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T;
    if(sys.Run_Status)//����ϵͳ
    {
        T += dT;//ʱ���dT
        if(T >= 1)//1S
        {
            if(Time.DownTime_Over == 0 && Speed.Ctrl_Speed)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Time.Ctrl_Time)//���Ƽ��Ӵ���0
				{	
					Time.Ctrl_Time--;//����ʱ��--
				}
                else
                {
                    Time.DownTime_Over= 1;//time1����ʱ����
					sys.Run_Status = 0;//�ر�ϵͳ
					Beep_Flash = 3;//��������3��
                }
            }
            T = 0;//��������
        }    
    }
    else
    {
		T = 0;//��������
        Time.DownTime_Over = 0;//������ʱ�����ı�־λ����
    }
}
