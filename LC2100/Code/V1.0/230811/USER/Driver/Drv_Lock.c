#include "Drv_Lock.h"

/**********ȫ�ֱ�������******/
uint8_t Lock_Status;//�������״̬
uint8_t Lid_State;//��ʾͼ��

/*
*****************************************************************
 * ����ԭ�ͣ�void Ctrl_Lock(float dT)
 * ��    �ܣ����������
*****************************************************************
*/
void Ctrl_Lock(float dT)
{
	if(Lock_Status == 1)
	{
		Lock_ON;//�򿪵����1
		Lock_Status = 0;
	}
	else
	{
		Lock_OFF;//�رյ����1
	}
	if((HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1))//������պ�ʱ
	{
		Lid_State = 0;//�رո��ӣ���ʾͼ��
	}
	else
	{
		Lid_State = 1;//�򿪸��ӣ���ʾͼ��
	}
}
