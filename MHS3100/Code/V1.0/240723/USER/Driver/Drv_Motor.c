#include "Drv_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Init(void)
 * ��    �ܣ������ʼ���𲽵�ѹ25
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_RESET);//��ʹ�ܵ��
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//����tim1ͨ��һ
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//����tim1ͨ����
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);//����tim1ͨ����
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);//����tim1ͨ����
}
