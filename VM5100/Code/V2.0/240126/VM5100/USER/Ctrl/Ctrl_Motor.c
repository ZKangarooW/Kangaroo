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
        /**********Speed_L1**********/
        if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)))//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
			if(Param.type==0)
			{
				PID_Speed(Ctrl_Speed+500,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
			}
			else if(Param.type == 1)
			{
				PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
			}
			PWM = Speed_Val.Out;//pid���
        }
        else
        {
			SpeedSet_Flag = TimeSet_Flag = 1;//���ñ���
			sys.Run_Status = 0;//�ر�
			PWM = 0;//pid���
        }
    }
    else
    { 
		Speed_Val.SumError = 0;
		Speed_Val.Out = 0;
        PWM = 0;//pwm�����
    }      
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_MotorStop(float dT)
 * ��    �ܣ�������Ƿ�ֹͣ��ֹͣ�󿪸�
*****************************************************************
*/
void Check_MotorStop(float dT)
{
//	static float T;
//	if(sys.Motor_Stop)
//	{
//		if(Rel_Speed == 0)
//		{
//			T += dT;
//			if(T > 1.0f)
//			{
//				PWM = 0;
//				SpeedSet_Flag = TimeSet_Flag = 1;//���ñ���
//				sys.Run_Status = 0;//�ر�
//				sys.Motor_Stop = 0;//����Ѿ�ֹͣ
//				T = 0;
//			}
//		}
//	}
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Init(void)
 * ��    �ܣ� �����ʼ�� 
*****************************************************************
*/
void Motor_Init(void)
{
    HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//ʹ�ܵ��
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//motor PWM���
}
