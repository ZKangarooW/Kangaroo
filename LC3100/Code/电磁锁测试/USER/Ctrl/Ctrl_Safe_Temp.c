#include "Ctrl_Safe_Temp.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Safe_Temp(float dT)
 * ��    �ܣ���ⰲȫ�¶�
*****************************************************************
*/
void Check_Safe_Temp(float dT)
{
	if(Safe_Rel_Temp <= Safe_Set_Temp)
	{
		Safe_Temp_Flag = 0;//�����ȫ�¶ȱ���
		if(Safe_Rel_Temp+50 <= Safe_Set_Temp)
		{
			COLD_OFF;//�رշ���
			Safe_Temp_Twinkleg = 0;//��ȫ�¶�ͼ�겻��˸
		}
		else
		{
			COLD_ON;//�򿪷���
		}
		return;
	}	
	if(Safe_Rel_Temp > Safe_Set_Temp && Safe_Temp_Flag == 0)//����ʵ���¶ȴ����趨�¶�ʱ
	{
		Safe_Temp_Flag = 1;//�¶ȳ���
		Safe_Temp_Twinkleg = 1;//��ȫ�¶�ͼ����˸
		Beep_Flash = 5;//��������5��
		Speed_ADDMode = 2;//�������ģʽ��
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
		{
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
	}
	else
	{
		sys.Hardware_Damage = 0;//Ӳ�����
	}
}
