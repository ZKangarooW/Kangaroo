#include "Ctrl_Safe_Temp.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Safe_Temp(float dT)
 * ��    �ܣ���ⰲȫ�¶�
*****************************************************************
*/
void Check_Safe_Temp(float dT)
{
	if(Safe_Rel_Temp < Safe_Set_Temp)
	{
		Safe_Temp_Flag = 0;//�����ȫ�¶ȱ���
		if(Safe_Rel_Temp+50 < Safe_Set_Temp)
		{
			Safe_Temp_Twinkleg = 0;//��ȫ�¶�ͼ�겻��˸
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
