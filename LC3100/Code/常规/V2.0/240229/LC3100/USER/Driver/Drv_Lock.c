#include "Drv_Lock.h"

/**********ȫ�ֱ�������******/
uint8_t Lock1_Status,Lock2_Status;//�������״̬

/*
*****************************************************************
 * ����ԭ�ͣ�void Ctrl_Lock(float dT)
 * ��    �ܣ����������
*****************************************************************
*/
void Ctrl_Lock(float dT)
{
	if(Lock1_Status == 1)
	{
		Lock1_ON;//�򿪵����1
		Lock1_Status = 0;
	}
	else
	{
		Lock1_OFF;//�رյ����1
	}
	if(Lock2_Status == 1)
	{
		Lock2_ON;//�򿪵����2
		Lock2_Status = 0;
	}
	else
	{
		Lock2_OFF;//�رյ����2
	}
	if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//�����1�͵����2���պ�ʱ
	{
		Lid_State = 0;//�رո��ӣ���ʾͼ��
	}
	else
	{
		Lid_State = 1;//�򿪸��ӣ���ʾͼ��
	}
	
}
