#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Cheak_TimeDown(float dT)
 * ��    �ܣ�ʱ���ʱ���
 * ��    ��: dT:ִ������
 * ��    ����float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T,T1;
    if(Time.CountDown_Start)//��������ʱ
    {
        T += dT;
        if(T >= 1)//1S
        {
			if(Time.Rel_Time)
				Time.Rel_Time--;//����ʱ��--
			else
			{
				Time.CountDown_Start= 0;//����ʱ����
				Time.Rel_Time = Time.Set_Time;
				Beep_Flash = 5;//��������5��
			}
            T = 0;//��������
        }    
    }
    else
    {
		T = 0;//��������
    }
	
	if(Time.Count_Start)//��������ʱ
    {
        T1 += dT;
        if(T1 >= 1)//1S
        {
			Time.Count_Time++;//����ʱ++
			if(Time.Count_Time >= 5999)
			{
				Time.Count_Start = 0;//�ر�����ʱ
				Time.TimeDisplay_Flag = 0;//�л�������ʱ
				Time.Count_Time = 0;//����ʱ����
				Beep_Flash = 5;//��������5��
			}
            T1 = 0;//��������
        }    
    }
    else
    {
		T1 = 0;//��������
    }
}
