#include "Ctrl_DownTime.h"

/**
 * @brief ʱ�䵹��ʱ���
 *
 * @param dT ��������
 */
void Cheak_TimeDown(float dT)
{
    static float T;
    if(sys.Run_Status == 1)//����ϵͳ
    {
		if(Time.Rel > 0 && Temp.ADDMode == 4)
		{
			T += dT;
		}
        if(T >= 1.0f)//1S
        {			
            if(Time.Rel)
                Time.Rel--;//����ʱ��--
            if(Time.Rel == 0)
            {
                sys.Run_Status = 0;
                SetOK_Flag = 1;//����
                Beep_Flash = 5;//��5��
            }
            T = 0;//��������
        }
    }
}
