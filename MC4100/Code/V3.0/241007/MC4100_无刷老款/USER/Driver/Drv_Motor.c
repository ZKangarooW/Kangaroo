#include "Drv_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Init(void)
 * ��    �ܣ������ʼ��
*****************************************************************
*/
void Motor_Init(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//����tim1ͨ��һ
    HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ת���͵�ƽ��ת
}
