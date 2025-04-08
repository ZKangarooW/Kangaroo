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
	
	/**********���ȳ�ʼ��**************/
	HEAT_Init();

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

//    #if (Key_Type == 0)
//    if(KEY1 == KEY_DOWN)//����MENU�����뵹��ʱģʽ�趨����
//    {
//        sys.DownTime_Mode = 1;
//    }
//    #endif

	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
