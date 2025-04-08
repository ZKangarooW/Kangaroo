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
    if(sys.Run_Status == 1 && sys.Display == 0)//����
    {
        if(Speed.Ctrl)
		{
            if(Speed.Up_Speed == 1)//����
            {
                Speed_Arg.Kp = 20 * 0.001f;
                Speed_Arg.Ki = 120 * 0.001f;
                Speed_Arg.Kd = 0 * 0.001f;
            }
            else if(Speed.Up_Speed == 2)//����
            {
                Speed_Arg.Kp = 20 * 0.001f;
                Speed_Arg.Ki = 30 * 0.001f;
                Speed_Arg.Kd = 0 * 0.001f;
            }
            else//����
            {
                Speed_Arg.Kp = 20 * 0.001f;
                Speed_Arg.Ki = 60 * 0.001f;
                Speed_Arg.Kd = 0 * 0.001f;
            }
            
            if(sys.Motor_Stop)
			{
				if(Speed_Val.Out)
					Speed_Val.Out -= 1;//����̫��*2
				if(Speed_Val.Out < 0)
					Speed_Val.Out = 0;
				PWM = Speed_Val.Out;//pid���
			}
			else
			{
				AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,400,400);//���PID����
				PWM = Speed_Val.Out;//pid���
			}
        }
		else
		{
			if(Speed_Val.Out)
				Speed_Val.Out -= 1;//����̫��*2
			if(Speed_Val.Out < 40)
				Speed_Val.Out = 0;
			PWM = Speed_Val.Out;//pid���
		}
    }
    else
    {
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm�����
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_MotorStop(float dT)
 * ��    �ܣ�������Ƿ�ֹͣ��ֹͣ�󿪸�
*****************************************************************
*/
float CW_Time;
void Check_MotorStop(float dT)
{
	static float T;
	if(sys.Motor_Stop)
	{
		if(Speed.Cw)//����ı�ת��
		{
			if(sys.Run_Status == 1)
			{
				if(Speed.Rel <= 100)
				{
					T += dT;
					CW_Time = 2.0f;
					if(T > CW_Time)
					{
						if(Speed.CwIcn) 
						{
                            HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//��ʱ��
							Speed.ADDMode = 0;
							Speed.CwIcn = 0;
						}
						else 
						{
                            HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//˳ʱ��
							Speed.ADDMode = 0;
							Speed.CwIcn = 1;
						}
						Beep_Time = 0.1f;
						sys.Motor_Stop = 0;//���ֹͣ����
						Speed.Cw = 0;//�ı�ת������
						Speed_Val.Integral = 27;//����𲽵�PWM
						T = 0;
					}
				}
			}
			else
			{
				if(Speed.CwIcn) 
				{
                    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//��ʱ��
					Speed.ADDMode = 0;
					Speed.CwIcn = 0;
				}
				else 
				{
                    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//˳ʱ��
					Speed.ADDMode = 0;
					Speed.CwIcn = 1;
				}
				sys.Motor_Stop = 0;//���ֹͣ����
				Speed.Cw = 0;//�ı�ת������
			}
		}
		else
		{
			if(Speed.Rel <= 100)
			{
				T += dT;
				if(T > 1.0f)
				{
					sys.Run_Status = 2;//�ر�
					sys.Motor_Stop = 0;//����Ѿ�ֹͣ
					SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//��������
					T = 0;
				}
			}
		}
	}
}
