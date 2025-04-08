#include "System_Init.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void System_Init(void)
 * ��    �ܣ�ϵͳ���ܳ�ʼ��
*****************************************************************
*/
void System_Init(void)
{
	/**********ϵͳ��ʼ����ʼ**********/
	sys.Init_ok = 0;
	
	/**********LCD��ʼ��***************/
	Lcd_Init();
	
	/**********�����ʼ��**************/
	Motor_Init();
	
	/**********��������ʼ��************/
	Encoder_Init();
	
	/**********PID��ʼ��***************/
	PID_Init();

	/**********������ʼ��**************/
	Param_Read();
	Ctrl_Speed = Speed=Set_Speed;//�ٶȳ�ʼ��
	Ctrl_Time = Time = Set_Time;//ʱ���ʼ��
	Beep_Time = 0.1;//��������0.1S  
    for(uint8_t i =0;i<=100;i++)
    {
        ADC_Val = Filter_ADC();//�˲���ȡadc�Ļ���ƽ��ֵ
        if(i == 100)//1S
        {
            NTC_Res = Get_Ntc_Temp(ADC_Val);//�����¶�
        }
        HAL_Delay(10);//û����ʱ�����������¶�
    }
	Display_SafeTemp = Safe_Rel_Temp;
	Speed_Mode = 6;//96�װ�
	
	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
