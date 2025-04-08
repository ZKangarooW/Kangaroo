#include "System_Init.h"

/**
 * @brief ϵͳ���ܳ�ʼ��
 * 
 */
void System_Init(void)
{
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);//�ر�LED
    HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);//�ر�LED
    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);//�ر�LED
    HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);//�ر�LED
    HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_SET);//�ر�LED
    HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_SET);//�ر�LED
	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 0;
    
	/**********������ʼ��**************/
	Param_Read();
	
	/**********LCD��ʼ��***************/
	Lcd_Init();
	
//	/**********��������ʼ��************/
//	Encoder_Init();
//	
//	/**********�����ʼ��**************/
//	Motor_Init();
//	
//	/**********���ȳ�ʼ��**************/
//	HEAT_Init();
//    
//	/**********���PIDϵ��*************/
//	Motor_PID();
//    
//	/**********�¶�PIDϵ��*************/
//	Temp_PID();
//	
//	/**********EC11A��ʼ����ʱ��*******/
//	EC11A_Init();
//	
//	/**********ADC&DMA��ʼ��***********/  
//	ADCDMA_Init();
	
	/**********��������0.1S************/  
    Beep_Time = 0.1;
    
	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
