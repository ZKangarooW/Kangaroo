#include "Drv_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Init(void)
 * ��    �ܣ������ʼ��
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//����tim3ͨ����
	HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
    HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ת���͵�ƽ��ת
}
