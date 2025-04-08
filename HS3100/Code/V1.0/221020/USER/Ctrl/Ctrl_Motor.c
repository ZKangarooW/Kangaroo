#include "Ctrl_Motor.h"

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
		if(Speed.Set_Speed > 0)
		{
			MO_ON();//�������
			PID_Speed(Speed.Ctrl_Speed,Speed.Rel_Speed,&Speed_Arg,&Speed_Val);//���PID����
			PWM = Speed_Val.Out;//pid���
		}
		else
		{
			MO_OFF();//����ر�
			Speed_Val.SumError = 0;//������ֺ�
			PWM = 0;//pwm�����
		}
    }
    else
    {
		MO_OFF();//����ر�
		Speed_Val.SumError = 0;//������ֺ�
        PWM = 0;//pwm�����
    }
}
