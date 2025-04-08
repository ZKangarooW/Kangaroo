#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Cheak_TimeDown(uint16_t dT)
 * ��    �ܣ� ʱ�䵹��ʱ���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Cheak_TimeDown(uint16_t dT)
{
    static uint16_t T;
	if(DownTime_Over==1)//����ʱ����
	{    
		DownTime_Over=0;//��ʱ���־����
		Speed_ADDMode = 2;//�������ģʽ��
		Beep_Flash = 5;//��������5��
	}
    if(sys.Run_Status && sys.Motor_Stop == 0)//����ϵͳ
    {
        T += dT;
        if(T == 1000)//1S
        {
            if(Time_State && DownTime_Over == 0 && Rel_Speed)//���ʵ��ʱ����ʾ�͵���ʱû�н����ı�־����
            {
				Ctrl_Time--;//����ʱ��--
                if(Ctrl_Time ==0)
                    DownTime_Over= 1;//time1����ʱ����
				
            }
            T = 0;//��������
        }    
    }
    else
    {
        DownTime_Over=0;//��ʱ���־����    
    }
}
