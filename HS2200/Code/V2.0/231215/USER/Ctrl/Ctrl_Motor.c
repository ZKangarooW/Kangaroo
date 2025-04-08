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
        /**********Speed_L1**********/
        if(Speed.Ctrl)//�ٶȴ���0�Ͷ�ʱ��û�н���
        {
			AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,350,400);//���PID����
            if(Speed_Val.Out<0)
                Speed_Val.Out = 0;
			PWM = Speed_Val.Out;//pid���
        }
        else
        {
			if(Speed_Val.Out)
				Speed_Val.Out -= 1;
			if(Speed_Val.Out<0)
				Speed_Val.Out = 0;
			PWM = Speed_Val.Out;//pwm�����
        }
    }
    else
    { 
        if(Speed_Val.Out)
		    Speed_Val.Out -= 1;
        if(Speed_Val.Out<0)
            Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm�����
    }
}
