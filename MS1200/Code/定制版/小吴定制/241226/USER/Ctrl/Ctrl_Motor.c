#include "Ctrl_Motor.h"

/**********�ṹ��************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val;

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_PID(void)
 * ��    �ܣ��������PIDϵ��
*****************************************************************
*/
void Motor_PID(void)
{
    Speed_Arg.Kp = 40 * 0.001f;
    Speed_Arg.Ki = 60 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Ctrl(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{
    if(sys.Run_Status)//����
    {
		if(!sys.Motor_Stop)
		{
			HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//���ɲ����
			/**********Speed_L1**********/
			AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,200,200);//���PID����
			if(Speed_Val.Out<0)
				Speed_Val.Out = 0;
			PWM = Speed_Val.Out;//pid���
		}
		else
		{
			if(Speed_Val.Out)
				Speed_Val.Out -= 1;
			PWM = Speed_Val.Out;//pwm�����
		}
    }
    else
    { 
		HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_RESET);//���ɲ����
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm�����
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
	static float T,T1;
	if(sys.Motor_Stop)
	{
		if(Speed.Rel <= 800)//��һ������
		{
			T1 += dT;
			if(T1 > 30.0f)
			{
				sys.Run_Status = 0;//�ر�
				sys.Motor_Stop = 0;//����Ѿ�ֹͣ
				T1 = 0;
			}
		}
		else
		{
			T = 0;
			T1 = 0;
		}
		
		if(Speed.Rel <= 220)//������
		{
			T += dT;
			if(T > 1.0f)
			{
				sys.Run_Status = 0;//�ر�
				sys.Motor_Stop = 0;//����Ѿ�ֹͣ
				T = 0;
			}
		}
		else
		{
			T = 0;
			T1 = 0;
		}
	}
	else
	{
		T = 0;
		T1 = 0;
	}
}
