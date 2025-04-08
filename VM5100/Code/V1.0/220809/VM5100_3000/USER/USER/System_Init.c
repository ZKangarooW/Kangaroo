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
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	
    /**********�����ʼ��**********/
    Motor_Init();
    PID_Init();
    /**********��������ʼ��**********/
    Encoder_Init();
   
    /**********��ʼ��lcd��Ļ**********/
	Lcd_Init();//��ʼ��
    LCD_Light(LCD_ON);//�򿨱���
    Lcd_All();//��ʾȫ������
    HAL_Delay(1000);//��ʱ1S
    Lcd_Clr();//����
	
    /**********ϵͳ������ʼ��**********/
	Param_Read();
	Speed = Ctrl_Speed = Set_Speed;
	Time = Ctrl_Time = Set_Time;
	Time_State  = (Set_Time < 60) ? 0 : 1;//�ж��Ƿ�������ʱ��
	Beep_Time = 0.1;
	
	/***************ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
