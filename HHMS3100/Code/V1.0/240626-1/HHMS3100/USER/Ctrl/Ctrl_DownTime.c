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
    static float T[4];
    if(sys.Run_Status)//����ϵͳ
    {
        for(uint8_t i = 0;i<4;i++)
        {
            if(Work_Num[i].Temp.Ctrl)
            {
                if(Work_Num[i].Time.Rel > 0 && Work_Num[i].Temp.ADDMode == 3)
                {
                    T[i] += dT;
                    if(T[i] >= 1.0f)//1S
                    {			
                        if(Work_Num[i].Time.Rel)
                            Work_Num[i].Time.Rel--;//����ʱ��--
                        if(Work_Num[i].Time.Rel == 0)
                        {
//                            Work_Num[i].Speed.ADDMode = 2;//�������ģʽ
//                            sys.Motor_Stop = 1;//���ֹͣ
//                            Beep_Flash = 5;//��5��
                        }
                        T[i] = 0;//��������
                    }
                }
            }
            else
            {
                if(Work_Num[i].Time.Rel > 0)
                {
                    T[i] += dT;
                    if(T[i] >= 1.0f)//1S
                    {			
                        if(Work_Num[i].Time.Rel)
                            Work_Num[i].Time.Rel--;//����ʱ��--
                        if(Work_Num[i].Time.Rel == 0)
                        {
//                            Speed.ADDMode = 2;//�������ģʽ
//                            sys.Motor_Stop = 1;//���ֹͣ
//                            Beep_Flash = 5;//��5��
                        }
                        T[i] = 0;//��������
                    }
                }
            }
        }
    }
}
