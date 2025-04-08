#include "Ctrl_DownTime.h"

/**
 * @brief ʱ�䵹��ʱ���
 *
 * @param dT ��������
 */
void Cheak_TimeDown(float dT)
{
    static float T;

    if (sys.Run_Status == 1) // ����ϵͳ
    {
        if (Time.Rel > 0)
        {
            T += dT;
        }
        if (T >= 1.0f) // 1S
        {
            if (Time.Rel)
                Time.Rel--; // ����ʱ��--

            if (Time.Rel == 0)
            {
                sys.Run_Status = 0;//�ر�����
                Speed.ADDMode = 2;//�������ģʽ��
                Twinkle_Time = 0;
                Key_Status = 0;
                Beep_Flash = 5;
                SetOK_Flag = 1;
                T = 0; // ��������
            }
            T = 0;
        }
    }
}
