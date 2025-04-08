#include "Ctrl_Motor.h"

/**********ȫ�ֱ�������******/
float R;//�����ʵİ뾶

/*
*****************************************************************
 * ����ԭ�ͣ�void Xg_R(float dT)
 * ��    �ܣ��������뾶
*****************************************************************
*/
void Xg_R(float dT)
{
	switch(Speed_Mode)
	{
		case 1:R = 11;//15ml*8
				Xg_Mode = 8;
				Xg_MAX = 1900;
				Speed_MAX = 12000;
			break;
		case 2:R = 11.6;//15ml*12
				Xg_Mode = 12;
				Xg_MAX = 2000;
				Speed_MAX = 4000;
			break;
		case 3:R = 12.2;//10ml*18
				Xg_Mode = 18;
				Xg_MAX = 2100;
				Speed_MAX = 4000;
			break;	
		case 4:R = 12.1;//10ml*24
				Xg_Mode = 24;
				Xg_MAX = 2100;
				Speed_MAX = 4000;
			break;	
		case 5:R = 12;//50ml*6
				Xg_Mode = 6;
				Xg_MAX = 2100;
				Speed_MAX = 4000;
			break;	
		case 6:R = 10.2;//50ml*6
				Xg_Mode = 9;
				Xg_MAX = 600;
				Speed_MAX = 2300;
			break;	
		default:
			break;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Ctrl(float dT)
 * ��    �ܣ� �������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
	Xg_R(dT);//�������뾶
    if(sys.Run_Status == 1)//����
    {
		if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//�����1��2�պ�ʱ
		{
			if(Ctrl_Speed && ((DownTime_Over == 0)||(Ctrl_Time)) && (Safe_Temp_Flag == 0))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				if(sys.Motor_Stop)
				{
					HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
					PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
					PWM = Speed_Val.Out;//pid���
				}
				else
				{
					HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
					if(Speed_Unit)	
						PID_Speed(1000 * My_Sqrt(Ctrl_Speed/(11.18*R)),Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����������
					else
						PID_Speed(Ctrl_Speed,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����ת��
					PWM = Speed_Val.Out;//pid���
				}
			}
			else
			{
				sys.Motor_Stop = 1;//����Ѿ�ֹͣ
				if(sys.Motor_Stop)
				{
					PID_Speed(0,Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
					PWM = Speed_Val.Out;//pid���
				}
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
			}
		}
		else
		{
			sys.Run_Status = 0;//������
			SetOK_Flag = 1;//���ñ���
		}
    }
    else
    {
        PWM = 0;//pwm�����
		sys.Motor_Stop = 0;//����Ѿ�ֹͣ
		Speed_Val.SumError = 0;//��ֹ�ر��ٴ�ʱ�ٶ�һ���Ӿͳ嵽֮ǰ���ٶ�	
		HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
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
		if(Rel_Speed <= 150)
		{
			T += dT;
			if(T> 1.0f)
			{
				PWM = 0;
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
				Lock1_Status = 1;//�����1��
				Lock2_Status = 1;//�����2��
				SetOK_Flag = 1;//���ñ���
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
