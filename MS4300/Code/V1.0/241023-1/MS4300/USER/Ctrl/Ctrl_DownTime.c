#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Cheak_TimeDown(float dT)
 * ��    �ܣ�ʱ�䵹��ʱ���
 * ��    �룺dT:ִ������
 * ��    ����float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T;
	if(sys.Run_Status)//����ϵͳ
    {
		if(Time.Rel > 0)
		{
			T += dT;
			if(T >= 1.0f)//1S
			{			
				if(Time.Rel)
					Time.Rel--;//����ʱ��--
				if(Time.Rel == 0)
				{
					Speed.ADDMode = 2;//���������ʾ
					sys.Motor_Stop = 1;//�������ֹͣ
					Beep_Flash = 5;//��5��
				}
				T = 0;//��������
			}
		}
    }
}
