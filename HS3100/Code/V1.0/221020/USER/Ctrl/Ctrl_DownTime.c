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
		if(Time.Ctrl_Time > 0 && Speed.Speed_ADDMode != 1)
		{
			T += dT;
			if(T >= 1.0f)//1S
			{			
				if(Time.Ctrl_Time)
					Time.Ctrl_Time--;//����ʱ��--
				if(Time.Ctrl_Time == 0)
				{
					Speed.Speed_ADDMode = 1;//�������ģʽ
					Speed.Ctrl_Speed = 0;//�������ٶ�����Ϊ0
					Beep_Flash = 5;//��5��
				}
				T = 0;//��������
			}    
		}
    }
}
