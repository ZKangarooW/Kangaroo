#include "SysTick.h"

/**
 * @brief ΢����ʱ����
 * 
 * @param delay ΢��
 */
void Delay_10us(uint16_t delay)
{
    uint16_t i;
    for(i = 0;i<delay;i++)
    {
        TIM1_WorkModeConfig(TIM1_WORK_MODE2,229);
        TR1 = 1; // ������ʱ��0
        EA=0;//���ж�(ʹ�ò�ѯ��ʽ)
		ET1=0;//��T1�ж�
        while (TF1 == 0);//�ȴ���ʱ��0�ж� 
        TF1 = 0;//�����ʱ��0�жϱ�־ 
    }
}
