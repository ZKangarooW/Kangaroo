#include "Drv_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Init(void)
 * ��    �ܣ������ʼ���𲽵�ѹ25
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//ʹ�ܵ��
	HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//˳ʱ��
	Speed.CwIcn = 1;//˳ʱ��ͼ��
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//����tim1ͨ��һ
}
