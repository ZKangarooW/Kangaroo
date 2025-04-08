#include "Drv_Lock.h"

/**********ȫ�ֱ�������******/
uint8_t Lock_Status;//�������״̬

/*
*****************************************************************
 * ����ԭ�ͣ�void Ctrl_Lock(float dT)
 * ��    �ܣ����������
*****************************************************************
*/
void Ctrl_Lock(float dT)
{
	static float T;
	if(Lock_Status == 1)
	{
		Lock_ON;//�򿪵����1
		Lock_Status = 0;
	}
	else
	{
		Lock_OFF;//�رյ����1
	}
	if((HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1))//������պ�ʱ
	{
		T = 0;
		Lid_State = 0;//�رո��ӣ���ʾͼ��
	}
	else
	{
		T += dT;
		if(T > 0.5f)
		{
			T = 0;
			Lid_State = 1;//�򿪸��ӣ���ʾͼ��
		}
	}
}
