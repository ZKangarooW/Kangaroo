#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Cheak_TimeDown(float dT)
 * ��    �ܣ� ʱ�䵹��ʱ���
 * ��    ��:  dT:ִ������
 * ��    ���� float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T;
    if(sys.Run_Status && sys.Motor_Stop == 0)//����ϵͳ
    {
        T += dT;
        if(T >= 1)//1S
        {
            if(Ctrl_Time)
                Ctrl_Time--;//����ʱ��--
            else
            {
                sys.Motor_Stop = 1;//�����
                Speed_ADDMode = 2;//�������ģʽ��
                Beep_Flash = 3;//��������3��
            }
            T = 0;
        }    
    }
    else
    {
		T = 0;//��������
        DownTime_Over = 0;//������ʱ�����ı�־λ����
    }
}
