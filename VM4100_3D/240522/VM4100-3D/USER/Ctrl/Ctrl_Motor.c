#include "Ctrl_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Ctrl(void)
 * ��    �ܣ� �������
*****************************************************************
*/
void Motor_Ctrl(void)
{   
    if(sys.Run_Status == 1)//����
    {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//motor PWM���
        /**********Speed_L1**********/
        if(Ctrl_Speed&& (DownTime_Over == 0))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
            PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
            Motor1 = Speed_Val.Out;//pid���
        }
        else
        {
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//motor PWM���
            Rel_Speed = 0;
            Motor1 = 0;//pwm�����
        }
    }
    else
    {      
        Motor1 = 0;//pwm����� 
        Rel_Speed = 0;
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//motor PWM���
    }      
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Init(void)
 * ��    �ܣ� �����ʼ�� 
*****************************************************************
*/
void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//motor PWM���
}
