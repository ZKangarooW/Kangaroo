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
			if(sys.Motor_Stop)
			{
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
				if(Speed_Val.Out > 400) 
					Speed_Val.Out = 400;
				if(Speed_Val.Out)
					Speed_Val.Out--;
				PWM = Speed_Val.Out;//pid���
			}
			else
			{
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
				PID_Speed(Ctrl_Speed*Tooth_Ratio,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
				PWM = Speed_Val.Out;//pid���
			}
		}
		else
		{
			sys.Motor_Stop = 1;//����Ѿ�ֹͣ
			HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
			if(Speed_Val.Out > 400) 
					Speed_Val.Out = 400;
			if(Speed_Val.Out)
					Speed_Val.Out--;
			PWM = Speed_Val.Out;//pid���
		}
    }
    else
    {
        HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
        PWM = 0;//pwm�����
		sys.Motor_Stop = 0;//����Ѿ�ֹͣ
		Speed_Val.SumError = 0;//��ֹ�ر��ٴ�ʱ�ٶ�һ���Ӿͳ嵽֮ǰ���ٶ�
    }      
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_MotorStop(float dT)
 * ��    �ܣ�������Ƿ�ֹͣ
*****************************************************************
*/
void Check_MotorStop(float dT)
{
	static float T;
	if(sys.Motor_Stop)
	{
		if(Rel_Speed == 0)
		{
			T += dT;
			if(T > 1.0f)
			{
				PWM = 0;
				sys.Run_Status = 0;//�ر�
				sys.Motor_Stop = 0;//����Ѿ�ֹͣ
				T = 0;
			}
		}
		else
		{
			T = 0;
		}
	}
	else
	{
		T = 0;
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
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//����tim3ͨ��һ
	HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
    HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ת���͵�ƽ��ת
}
