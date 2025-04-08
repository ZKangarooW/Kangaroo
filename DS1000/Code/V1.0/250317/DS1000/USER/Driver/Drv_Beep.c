#include "Drv_Beep.h"

/**********ȫ�ֱ���**********/
float Beep_Time;//���������ʱ��
float Beep_Flash;//��������Ĵ���

/*
*****************************************************************
 * ����ԭ�ͣ� void Drv_BUZZER_Init(void)
 * ��    �ܣ� ������������ʼ��
*****************************************************************
*/
void Drv_BUZZER_Init(void)
{
	/*
	(1)���÷�����ʱ��
	*/
	BUZ_ConfigBuzzer(BUZ_CKS_32,188);			//Fsys=48Mhz��Fbuz = Fsys/(2*16*150) =4khz
	/*
	(2)���÷��������IO
	*/	
	GPIO_SET_MUX_MODE(P06CFG,GPIO_P06_MUX_BUZZ);
		
	/*
	(3)�رշ�����ʱ��
	*/	
	BUZ_EnableBuzzer();	
}

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
        else if(BT >= 0.3)//���ڵ���0.2sʱ
        {
            Beep_Flash--;//����--
            BT = 0;//��������
        }
    }
}
