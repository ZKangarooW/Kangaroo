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
    if(sys.Run_Status == 1 && Temp.ADDMode == 4)//����ϵͳ
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
                    sys.Run_Status = 2;//ϵͳ�ر�
					SetOK_Flag = 1;//�ٶ����ã�ʱ������
					Temp.Last_Mode = Temp.ADDMode;//��¼�ر�ʱ����ʾģʽ
					Temp.ADD_Wait_Count = 0;//���������ʱ��
                    Temp.ADDMode = 0;//������ʾģʽ����
					Beep_Flash = 5;//��5��
                }
				T = 0;//��������
            }
        }
    }
}
