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
        if(CGF.Mode == 0)
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
        else if(CGF.Mode == 1)
        {
            if(Speed.ADDMode == 3)
            {
                T += dT;
                if(T >= 1)//1S
                {
                    if(Param.C_Param[1][0])//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
                    {
                        if(Param.C_Param[1][0])
                            Param.C_Param[1][0]--;//����ʱ��--
                        if(Param.C_Param[1][0] ==  720)//12����
                        {
                            Speed.ADDMode = 0;//���뽵�ٲ�����ʱ
                            CGF.Option = 2;//����ڶ���
                        }
                        else if(Param.C_Param[1][0] ==  420)//7����
                        {
                            Speed.ADDMode = 0;//���뽵�ٲ�����ʱ
                            CGF.Option = 3;//���������
                        }
                        else if(Param.C_Param[1][0] ==  180)//3����
                        {
                            Speed.ADDMode = 0;//���뽵�ٲ�����ʱ
                            CGF.Option = 4;//������Ķ�
                        }
                        else if(Param.C_Param[1][0] ==  0)//0����
                        {
                            Speed.ADDMode = 2;//���뽵�ٲ�����ʱ
                            sys.Motor_Stop = 1;//�������ֹͣ
                            Beep_Flash = 3;//��������5��
                        }
                    }
                    T = 0;//��������
                }
            }
        }
        else
        {
            if(Speed.ADDMode == 3)
            {
                T += dT;
                if(T >= 1)//1S
                {
                    if(Param.C_Param[CGF.Option][0])//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
                    {
                        if(Param.C_Param[CGF.Option][0])
                            Param.C_Param[CGF.Option][0]--;//����ʱ��--
                        else 
                        {
                            Speed.ADDMode = 2;//���뽵�ٲ�����ʱ
                            sys.Motor_Stop = 1;//�������ֹͣ
                            Beep_Flash = 3;//��������5��
                        }
                    }
                    T = 0;//��������
                }
            }
        }
    }
}
