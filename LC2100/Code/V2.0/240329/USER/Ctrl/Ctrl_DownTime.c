#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Cheak_TimeDown(float dT)
 * ��    �ܣ�ʱ�䵹��ʱ���
 * ��    �룺dT��ִ������
 * ��    ����float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T;
    if(sys.Run_Status)//����ϵͳ
    {
        if(Time.Ctrl)
        {
            T += dT;
            if(T >= 1)//1S
            {
                if(Time.Ctrl)
                    Time.Ctrl--;//����ʱ��--
                if(Time.Ctrl == 0)
                {
                    Speed.ADDMode = 2;//�������ģʽ��
                    sys.Motor_Stop = 1;//�������ֹͣ
                    Beep_Flash = 5;//��������5��
                }
                T = 0;//��������
            } 
        }            
    }
}
