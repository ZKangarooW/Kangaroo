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
    if(sys.Run_Status && Key_Type == 0)//����ϵͳ
    {
        if(Temp.Ctrl)
        {
            if(Time.Rel > 0 && Temp.ADDMode == 3)
            {
                T += dT;
                if(T >= 1.0f)//1S
                {			
                    if(Time.Rel)
                        Time.Rel--;//����ʱ��--
                    if(Time.Rel == 0)
                    {
                        Speed.ADDMode = 1;//�������ģʽ
					    Speed.Ctrl = 0;//�������ٶ�����Ϊ0
                        Beep_Flash = 5;//��5��
                    }
                     T = 0;//��������
                }
            }
        }
        else
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
                        Speed.ADDMode = 1;//�������ģʽ
					    Speed.Ctrl = 0;//�������ٶ�����Ϊ0
                        Beep_Flash = 5;//��5��
                    }
                     T = 0;//��������
                }
            }
        }
    }
}
