#include "System_Init.h"

/**
 * @brief ϵͳ���ܳ�ʼ��
 * 
 */
void System_Init(void)
{
	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 0;
    
    if(HAL_GPIO_ReadPin(Key_POR_GPIO_Port,Key_POR_Pin) == KEY_DOWN)//���°���
	{	
		sys.Display = 1;
	}
    else
    {
        sys.Display = 0;
    }
    
	/**********������ʼ��**************/
	Param_Read();
	
	/**********LCD��ʼ��***************/
	Lcd_Init();
	
	/**********��������ʼ��************/
	Encoder_Init();
	
	/**********�����ʼ��**************/
	Motor_Init();
	
	/**********���ȳ�ʼ��**************/
	HEAT_Init();
    
	/**********���PIDϵ��*************/
	Motor_PID();
    
	/**********�¶�PIDϵ��*************/
	Temp_PID();
	
	/**********EC11A��ʼ����ʱ��*******/
	EC11A_Init();
	
	/**********ADC&DMA��ʼ��***********/  
	ADCDMA_Init();
	
	/**********��������0.1S************/  
    if(sys.Display == 0)
    {
        Beep_Time = 0.1;
    }
	
	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
