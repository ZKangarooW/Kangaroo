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
        if(sys.Run_Mode != 1)
        {
            T += dT;
            if(T >= 1)//1S
            {
                if(Speed.Ctrl)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
                {
                    if(Time.Rel)
                        Time.Rel--;//����ʱ��--
                    else
                    {
                        Speed.ADDMode = 2;//�������ģʽ��
                        sys.Motor_Stop = 1;//�������ģʽ
                        Beep_Flash = 3;//��������3��
                    }
                }
                T = 0;//��������
            }
        }
        else
        {
            if(Speed.ADDMode == 3)
            {
                T += dT;
                if(T >= 1)//1S
                {
                    if(Speed.Ctrl)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
                    {
                        if(Time.Rel)
                            Time.Rel--;//����ʱ��--
                        switch(sys.CGF_Step)
                        {
                            case 0:if(Time.Rel ==  720)//12����
                                    {
                                        Speed.ADDMode = 0;//���뽵�ٲ�����ʱ
                                        PMode.Option = 2;//����ڶ���
                                        Speed.Set = Param.P_Param[PMode.Option][1];//��ȡ�����еڶ��ε�ת��
                                        Speed.Ctrl = Speed.Set;//���趨�ٶȸ�ֵ�������ٶ�
                                        sys.CGF_Step = 1;//������һ��
                                    }
                                break;
                            case 1:if(Time.Rel ==  420)//7����
                                    {
                                        Speed.ADDMode = 0;//���뽵�ٲ�����ʱ
                                        PMode.Option = 3;//���������
                                        Speed.Set = Param.P_Param[PMode.Option][1];//��ȡ�����е����ε�ת��
                                        Speed.Ctrl = Speed.Set;//���趨�ٶȸ�ֵ�������ٶ�
                                        sys.CGF_Step = 2;//������һ��
                                    }
                                break;
                            case 2:if(Time.Rel ==  180)//3����
                                    {
                                        Speed.ADDMode = 0;//���뽵�ٲ�����ʱ
                                        PMode.Option = 4;//������Ķ�
                                        Speed.Set = Param.P_Param[PMode.Option][1];//��ȡ�����е��Ķε�ת��
                                        Speed.Ctrl = Speed.Set;//���趨�ٶȸ�ֵ�������ٶ�
                                        sys.CGF_Step = 3;//������һ��
                                    }
                                break;
                            case 3:if(Time.Rel == 0)//0����
                                    {
                                        Speed.ADDMode = 2;//�������ģʽ��
                                        Speed.Set = Param.P_Param[PMode.Option][1];//��ȡ�����е��Ķε�ת��
                                        Speed.Ctrl = Speed.Set;//���趨�ٶȸ�ֵ�������ٶ�
                                        sys.Motor_Stop = 1;//�������ģʽ
                                        Beep_Flash = 3;//��������3��
                                    }
                                break;
                            default:
                                break;
                        }
                    }
                    T = 0;//��������
                }
            }
        }
    }
    else
    {
		T = 0;//��������
    }
}
