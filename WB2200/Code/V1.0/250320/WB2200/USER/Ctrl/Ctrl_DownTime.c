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
        if(sys.DownTime_Type == 0 && Temp.ADDMode != 4)//C1
        {
            return;
        }
		if(Time.Rel > 0)
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
//                SetOK_Flag = 1;//������Ϊ��ȥ�����жϲ����иı䡣�����Լ�����
                Time.Rel = Time.Set;
                Temp_ShowFlag = 0;//�����Ҫ����һ�Σ���Ȼ������˸
                Beep_Flash = 5;//��5��
            }
            T = 0;//��������
        }
    }
}
