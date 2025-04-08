#include "Beep.h"

/**********ȫ�ֱ���**********/
float Beep_Time;//���������ʱ��
float Beep_Flash;//��������Ĵ���

/*
*****************************************************************
 * ����ԭ�ͣ� void Buzzer_Status(float dT)
 * ��    �ܣ� ��������״̬���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Buzzer_Status(float dT)
{
    static float BT;
    if(Beep_Time <= 0 && Beep_Flash <= 0)//��������ʱ��С�ڵ���0ʱ
    {
        Beep_OFF;//�رշ�����
        return;
    }
    if(Beep_Time)
    {
        Beep_ON;//�򿪷�����
        Beep_Time -= dT;//���������ʱ��--
    }
    if(Beep_Flash)
    {
		BT =  BT + dT;//����++
		if(BT < 0.2)//���С��0.2sʱ
		{
			Beep_ON;//��������
		}
		else if(BT >= 0.2 && BT < 0.3)//��0.2��0.3s֮��ʱ
		{
			Beep_OFF;//�رշ�����
		}
		else if(BT >= 0.3)//���ڵ���0.3sʱ
		{
			Beep_Flash--;//����--
			BT = 0;//��������
		}
    }
}
