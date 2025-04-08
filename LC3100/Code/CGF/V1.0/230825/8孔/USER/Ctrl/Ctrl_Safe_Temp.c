#include "Ctrl_Safe_Temp.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Safe_Temp(float dT)
 * ��    �ܣ���ⰲȫ�¶�
*****************************************************************
*/
void Check_Safe_Temp(float dT)
{
	if(SafeTemp.Rel <= SafeTemp.Set)
	{
		SafeTemp.Flag = 0;//�����ȫ�¶ȱ���
		if(SafeTemp.Rel+50 <= SafeTemp.Set)
		{
			COLD_OFF;//�رշ���
			SafeTemp.Twinkleg = 0;//��ȫ�¶�ͼ�겻��˸
		}
		else
		{
			COLD_ON;//�򿪷���
		}
		return;
	}	
    if(sys.Run_Status && sys.Motor_Stop == 0)
    {
        if(SafeTemp.Rel > SafeTemp.Set && SafeTemp.Flag == 0)//����ʵ���¶ȴ����趨�¶�ʱ
        {
            SafeTemp.Flag = 1;//�¶ȳ���
            SafeTemp.Twinkleg = 1;//��ȫ�¶�ͼ����˸
            sys.Motor_Stop = 1;//�������ģʽ
            Beep_Flash = 5;//��������5��
            Speed.ADDMode = 2;//�������ģʽ��
        }
    }        
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Shock(float dT)
 * ��    �ܣ������
*****************************************************************
*/
void Check_Shock(float dT)
{
	static float T;
	if(HAL_GPIO_ReadPin(UC_IN3_GPIO_Port,UC_IN3_Pin)== 0)//�𶯿��طſ�
	{
		sys.Hardware_Damage = 1;//Ӳ����
        while(1)
        {
            T += dT;
            if(T <= 1)//1S
            {
                Lcd_All();
                
            }
            else if(T > 1 && T <= 2)
            {
                Lcd_Clr();
            }
            else if(T > 2)
            {
                T = 0;
            }
            PWM = 0;	
            HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
        }
	}
	else
	{
		sys.Hardware_Damage = 0;//Ӳ�����
	}
}
