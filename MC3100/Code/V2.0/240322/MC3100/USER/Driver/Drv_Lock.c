#include "Drv_Lock.h"

/**********ȫ�ֱ�������******/
uint8_t Lock_Status;//���ӵ�״̬

/*
*****************************************************************
 * ����ԭ�ͣ�void Ctrl_Lock(float dT)
 * ��    �ܣ��ؿ��Ǽ��
*****************************************************************
*/
void Ctrl_Lock(float dT)
{
	if((HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)== 1))//���ӱպ�ʱ
	{
		Lock_Status = 0;//�رո��ӣ���ʾͼ��
	}
	else
	{
		Lock_Status = 1;//�򿪸��ӣ���ʾͼ��
	}
}
