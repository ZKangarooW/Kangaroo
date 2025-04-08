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
    /**********�����1**********/
	if(Lock1_Status == 1)//��������1��ǰ�ǹر�״̬
	{
		Lock1_ON;//�򿪵����1
		Lock1_Status = 0;//��״̬����Ϊ0�����ⳤ��һֱ��
	}
	else
	{
		Lock1_OFF;//�رյ����1
	}
    
    /**********�����2**********/
	if(Lock2_Status == 1)//��������2��ǰ�ǹر�״̬
	{
		Lock2_ON;//�򿪵����2
		Lock2_Status = 0;//��״̬����Ϊ0�����ⳤ��һֱ��
	}
	else
	{
		Lock2_OFF;//�رյ����2
	}
    
    /**********����״̬��ʾ**********/
	if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin) == 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin) == 1))//�����1�͵����2���պ�ʱ
	{
		sys.Lid_State = 0;//�رո��ӣ���ʾͼ��
	}
	else
	{
		sys.Lid_State = 1;//�򿪸��ӣ���ʾͼ��
	}
}
