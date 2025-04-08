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
    Speed_Arg.Kp = 16 * 0.001f;
    Speed_Arg.Ki = 24 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Motor_Ctrl(float dT)
 * ��    �ܣ� �������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
    if(sys.Run_Status == 1)//����
    {
		if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//�����1��2�պ�ʱ
		{
			if(Speed.Ctrl)//�ٶȴ���0
			{
				if(sys.Motor_Stop)
				{
					HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
					if(Speed_Val.Out)
                        Speed_Val.Out -= (dT*10);//����̫��*2
                    if(Speed_Val.Out < 0)
                        Speed_Val.Out = 0;
                    PWM = Speed_Val.Out;//pid���
				}
				else
				{
					HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
					if(Speed.Unit)	
						AltPID_Calculation(dT,1000 * My_Sqrt(Speed.Ctrl/(11.18*Mode_R)),Speed.Rel,&Speed_Arg,&Speed_Val,400,400);//���PID����������
					else
						AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,400,400);//���PID����
					PWM = Speed_Val.Out;//pid���
				}
			}
		}
		else
		{
			sys.Run_Status = 0;//������
            HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
			SetOK_Flag = 1;//���ñ���
		}
    }
    else
    {
        PWM = 0;//pwm�����
		sys.Motor_Stop = 0;//����Ѿ�ֹͣ
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
		if(Speed.Rel <= 150)
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
                if(sys.Run_Mode == 1)//��CGFģʽ��
                {
                    PMode.Option = 1;//�������Ϊ1
                    sys.CGF_Step = 0;//����Ϊ0
                    Speed.Set = Param.P_Param[PMode.Option][1];//��ȡ�����е��Ķε�ת��
                    Speed.Ctrl = Speed.Set;//���趨�ٶȸ�ֵ�������ٶ�
                }
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
