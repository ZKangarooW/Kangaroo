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
    if(sys.Run_Status && sys.Motor_Stop == 0)//����ϵͳ
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
                    Speed.ADDMode = 2;//���뽵����ʾ
					Speed.Cw = 0;//ת������
					sys.Motor_Stop = 1;//�����
					SpeedSet_Flag=TimeSet_Flag=1;//��������
					Speed_Twinkle_Time = Time_Twinkle_Time = 0;//�ر���˸
                    Beep_Flash = 5;//��5��
                }
                 T = 0;//��������
            }
        }
    }
}
