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
		if(Temp.ADDMode == 3 && Time.Rel > 0 && sys.Time_Status)
		{
			T += dT;
			if(T >= 1.0f)//1S
			{			
				if(Time.Rel)
					Time.Rel--;//����ʱ��--
				if(Time.Rel == 0)
				{
					sys.Time_Status = 0;
					Beep_Flash = 60;//��5��
				}
				 T = 0;//��������
			}
		}
    }
}
