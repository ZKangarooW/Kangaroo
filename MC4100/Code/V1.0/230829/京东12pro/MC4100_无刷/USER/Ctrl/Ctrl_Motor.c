#include "Ctrl_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Ctrl(float dT)
 * ��    �ܣ� �������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
	static float T;
    if(sys.Run_Status == 1)//����
    {
		if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//������պ�ʱ
		{
			if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)) && (Safe_Temp_Flag == 0))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				if(sys.Motor_Stop)
				{			
					PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
					PWM = Speed_Val.Out;//pid���
					T = 0;
				}
				else
				{	
					if(Speed_Mode)	
						PID_Speed(1000 * My_Sqrt(Ctrl_Speed/(11.18*6)),Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����������
					else
						PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����ת��
					PWM = Speed_Val.Out;//pid���
					T = 0;
				}
			}
			else
			{
				sys.Motor_Stop = 1;//�����
				T = 0;
				if(sys.Motor_Stop)
				{
					PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
					PWM = Speed_Val.Out;//pid���
				}
			}
		}
		else
		{
			T += dT;
			if(T > 0.5f)
			{	
				T = 0;
				sys.Run_Status = 0;//������
			}
		}
    }
    else
    {
		T = 0;
        PWM = 0;//pwm�����
		Speed_Val.SumError = 0;//��ֹ�ر��ٴ�ʱ�ٶ�һ���Ӿͳ嵽֮ǰ���ٶ�	
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
	static float T;
	if(sys.Motor_Stop)
	{
		if(Rel_Speed <= 500)
		{
			T += dT;
			if(T>1.0f)
			{
				Lock_Status = 1;//�������
				SetOK_Flag = 1;//���ò�����һ
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
