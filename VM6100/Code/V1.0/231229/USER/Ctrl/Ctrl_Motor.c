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
    Speed_Arg.Kp = 20 * 0.001f;
    Speed_Arg.Ki = 44 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Ctrl(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
int16_t Ctrl_Val;
void Motor_Ctrl(float dT)
{ 
    if(sys.Run_Status)//����
    {
        if(Speed.Ctrl)
		{
            HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
            if(sys.Motor_Stop)
			{
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
			}
			else
			{
                if(Speed.Ctrl > 2000)
                    Ctrl_Val = 2000 + ((Speed.Ctrl - 2000)/2);
                else
                    Ctrl_Val = Speed.Ctrl;
				AltPID_Calculation(dT,Ctrl_Val,Speed.Rel,&Speed_Arg,&Speed_Val,400,400);//���PID����
				PWM = Speed_Val.Out;//pid���
			}
        }
    }
    else
    {
        HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//�ߵ�ƽ��ɲ�����͵�ƽɲ��
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
void Check_MotorStop(float dT)
{
//	static float T;
	if(sys.Motor_Stop)
	{
//        if(Speed.Rel <= 300)
//        {
//            T += dT;
//            if(T > 1.0f)
//            {
                TimeSet_Flag=1;//���ñ���
                sys.Run_Status = 0;//�ر�
                sys.Motor_Stop = 0;//����Ѿ�ֹͣ
//                T = 0;
//            }
//        }
	}
}
