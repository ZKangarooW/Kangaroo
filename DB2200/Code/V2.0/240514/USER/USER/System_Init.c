#include "System_Init.h"

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
    
    /**********LCD��ʼ��**********/  
	Lcd_Init();
	Lcd_All();
	HAL_Delay(1000);
	Lcd_Clr();
	
    /**********PID��ʼ��**********/     
    PID_Init();
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//����tim3ͨ��2��pwm
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//����tim3ͨ��2��pwm

	Param_Read();
    /**********��ֵ��ʼ��**********/  
	HAL_ADC_Start(&hadc);//��ʼ��ȡadc��ֵ
    HAL_Delay(10);//û����ʱ�����������¶�
    NTC_Res = Get_Ntc_Temp(HAL_ADC_GetValue(&hadc));//��adc��ֵ����
	Rel_Temp = Ture_Temp;
	Display_RelTemp = Rel_Temp;
	
	Beep_Time = 0.1;//��������0.1S
	
	Display_Circle = 13;//�ݶ�ģʽ����Ȧת����ʾ
	
	/***************ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
