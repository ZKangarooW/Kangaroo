#include "Ctrl_Motor.h"

/**********�ṹ��************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val;

/**
 * @brief �������PIDϵ��
 *
 */
void Motor_PID(void)
{
    Speed_Arg.Kp = 4 * 0.001f;
    Speed_Arg.Ki = 60 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/**
 * @brief �������
 *
 * @param dT ��������
 */
void Motor_Ctrl(float dT)
{
    if (sys.Run_Status == 1) // ����
    {
        if (Speed.Ctrl) // �ٶȴ���0�Ͷ�ʱ��û�н���
        {
            if(sys.Motor_Stop)//��ֹͣ����ģʽ��
			{			
				if (Speed_Val.Out)
                    Speed_Val.Out -= 1;
                if (Speed_Val.Out < 0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out; // PWM���
			}
			else
			{	
                AltPID_Calculation(dT, Speed.Ctrl, Speed.Rel, &Speed_Arg, &Speed_Val, 150, 999); // ���PID����
                if (Speed_Val.Out < 0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out; // PID���
			}
        }
        else
        {
            sys.Motor_Stop = 1;//�����
			if(sys.Motor_Stop)//��ֹͣ����ģʽ��
			{
                if (Speed_Val.Out)
                    Speed_Val.Out -= 1;
                if (Speed_Val.Out < 0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out; // PWM���
            }
        }
    }
    else
    {
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out; // PWM���
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
	if(sys.Motor_Stop)//��ֹͣ����ģʽ��
	{
		if(Speed.Rel < 180)
		{
			T += dT;//ʱ���dT
			if(T>1.0f)//�ٶ�Ϊ��ʱ�����1Sʱ
			{
				SetOK_Flag = 1;//���ò�����һ
				sys.Run_Status = 0;//�ر�
				sys.Motor_Stop = 0;//����Ѿ�ֹͣ
				T = 0;//ʱ������
			}
		}
	}
	else
	{
		T = 0;//ʱ������
	}
}
