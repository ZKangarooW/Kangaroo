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
	if(Set_Time == 0)//����ʱ��Ϊ0�Ļ����������ʱ
		return;
    if(sys.Run_Status && sys.Motor_Stop == 0)//����ϵͳ
    {
        T += dT;//ʱ���dT
        if(T >= 1)//1S
        {
            if(DownTime_Over == 0 && Ctrl_Speed)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time)//���Ƽ��Ӵ���0
					Ctrl_Time--;//����ʱ��--
                else
                {
                    DownTime_Over= 1;//time1����ʱ����
					Speed_ADDMode = 4;//�������ģʽ��
					Beep_Flash = 3;//��������3��
                }
            }
            T = 0;//��������
        }    
    }
    else
    {
		T = 0;//��������
        DownTime_Over = 0;//������ʱ�����ı�־λ����
    }
}
