#include "System_Init.h"
//#define COLD htim3.Instance->CCR1//����ģ��PWM
//#define HEAT htim3.Instance->CCR2//����ģ��PWM
/*
*****************************************************************
 * ����ԭ�ͣ� void System_Init(void)
 * ��    �ܣ� ϵͳ���ܳ�ʼ��
*****************************************************************
*/
void System_Init(void)
{	
	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 0;
	
	/**********LCD��ʼ��***************/
	Lcd_Init();
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//����tim3ͨ��2��pwm
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//����tim3ͨ��2��pwm
	
	/**********������������************/
	Beep_Time = 0.1;

	HAL_GPIO_WritePin(WIND_GPIO_Port,WIND_Pin,GPIO_PIN_RESET);//�򿪷�����
//	COLD = 0;
//	HEAT = 0;
	
	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
