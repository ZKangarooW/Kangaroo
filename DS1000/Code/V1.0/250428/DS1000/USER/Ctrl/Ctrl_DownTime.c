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
    if(sys.Run_Status==1)//����ϵͳ
    {
        if(Time.Rel)
        {
            T += dT;
            if(T >= 1.0f)//1S
            {			
                if(Time.Rel)
                    Time.Rel--;//����ʱ��--
                if(Time.Rel == 0)
                {
                    sys.Run_Status = 0;//�ر�ϵͳ
                    Time.Rel = Time.Set;//���ӵĻ�������ʱ���������Ḵԭ������ͱ�ɳ�������
                    Beep_Flash = 5;//��5��
                }
                T = 0;//��������
            }
        }
    }
}
