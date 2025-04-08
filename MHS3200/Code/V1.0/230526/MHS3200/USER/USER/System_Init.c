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
    
    /**********����Դ���ȿ���**********/  
    #if(Integration_TYPE <= 1)//���ó�����������ʱ
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    #elif(Integration_TYPE == 2)//���óɾ���ʱ
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    #endif
    
    /**********����ģ��pem����**********/
    #if(Temp_TYPE == 1)//���óɼ��ȿ�
        #if(Integration_TYPE <= 1)//���ó�����������ʱ
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
        #elif(Integration_TYPE == 2)//���óɾ���ʱ
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
        #endif
    #endif
    
    /**********�����ʼ��**********/
    Motor_Init();
    
    /**********��������ʼ��**********/
    Encoder_Init();
    
    /**********EC11A��ʼ����ʱ��*******/
	EC11A_Init();
    
    /**********��ʼ��lcd��Ļ**********/
	Lcd_Init();//��ʼ��
    LCD_Light(LCD_ON);//�򿨱��� 
    Lcd_All();//��ʾȫ������
    HAL_Delay(1000);//��ʱ1S
	Lcd_Clr();//����

    /**********ϵͳ������ʼ��**********/
    Work_Option = 1;//��λ��1
	Param_Read();//��ȡ����
    SetOK_Flag = 1;
    PID_Init();//pidϵ����ʼ��
    Beep_Time = 0.1;//��������0.1S

	/***************ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
