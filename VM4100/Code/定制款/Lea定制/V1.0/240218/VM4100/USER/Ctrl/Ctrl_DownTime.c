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
	if(Set_Time == 0)//����ʱ��Ϊ0�Ļ����������ʱ
		return;
    if(sys.Run_Status)//����ϵͳ
    {
        T += dT;//ʱ���dT
        if(T >= 1)//1S
        {
            if(DownTime_Over == 0 && Ctrl_Speed && sys.Motor_Stop == 0)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
                if(Ctrl_Time)//���Ƽ��Ӵ���0
				{	
					if(Time_State == 0)//ʱ����ʾ
						Ctrl_Time--;//����ʱ��--
				}
                else
                {
					if(sys.Run_Step < 1)
					{
						sys.Run_Step ++;
						Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];
						Set_Time = Param.Time[Speed_Mode][sys.Run_Step];
						Ctrl_Time = Set_Time;//���趨ʱ�丳ֵ������ʱ��
						Ctrl_Speed = Set_Speed;//���趨�ٶȸ�ֵ�������ٶ�
						if(Speed_ADDMode != 0)//���繤λֻ�������������������ٶȵ�����²�����0������δ����ģʽ��
							Speed_ADDMode = 0;//����δ�����жϼ��ٻ��Ǽ��� 
						Beep_Flash = 1;//��������1��
					}
					else
					{
						sys.Run_Step = 0;
						Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];
						Set_Time = Param.Speed[Speed_Mode][sys.Run_Step];
						DownTime_Over= 1;//time1����ʱ����
						Speed_ADDMode = 4;//�������ģʽ��
						Beep_Flash = 3;//��������3��
					}
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
