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
    Speed_Arg.Kp = 2 * 0.001f;
    Speed_Arg.Ki = 20 * 0.001f;
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
    if(sys.Run_Status == 1)//����
    {
        if(CGF.Mode == 0)
        {
            if((HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1))//������պ�ʱ
            {
                if(Speed.Ctrl)//�ٶȴ���0
                {
                    if(sys.Motor_Stop)
                    {			
                        if(Speed_Val.Out)
                            Speed_Val.Out -= (dT*4);//����̫��*2
                        if(Speed_Val.Out < 0)
                            Speed_Val.Out = 0;
                        PWM = Speed_Val.Out;//pid���
                    }
                    else
                    {	
                        if(Speed.Unit)
                            AltPID_Calculation(dT,1000 * My_Sqrt(Speed.Ctrl/(11.18*9.6)),Speed.Rel,&Speed_Arg,&Speed_Val,350,400);//���PID����������
                        else
                            AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,350,400);//���PID����ת��
                        PWM = Speed_Val.Out;//pid���
                    }
                }
            }
            else
            {
                sys.Run_Status = 0;//������
                PWM = 0;
            }
        }
        else
        {
            if((HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1))//������պ�ʱ
            {
                if(Param.C_Param[CGF.Option][1])//�ٶȴ���0
                {
                    if(sys.Motor_Stop)
                    {			
                        if(Speed_Val.Out)
                            Speed_Val.Out -= (dT*4);//����̫��*2
                        if(Speed_Val.Out < 0)
                            Speed_Val.Out = 0;
                        PWM = Speed_Val.Out;//pid���
                    }
                    else
                    {	
                        AltPID_Calculation(dT,Param.C_Param[CGF.Option][1],Speed.Rel,&Speed_Arg,&Speed_Val,350,400);//���PID����ת��
                        PWM = Speed_Val.Out;//pid���
                    }
                }
            }
            else
            {
                sys.Run_Status = 0;//������
                PWM = 0;
            }
            
        }
    }
    else
    {
        PWM = 0;//pwm�����
		Speed_Val.Integral = 0;//��ֹ�ر��ٴ�ʱ�ٶ�һ���Ӿͳ嵽֮ǰ���ٶ�	
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
		if(Speed.Rel <= 340)
		{
			T += dT;
			if(T > 2)
			{
				Lock_Status = 1;//�������
				SetOK_Flag = 1;//���ò�����һ
				sys.Run_Status = 0;//�ر�
				sys.Motor_Stop = 0;//����Ѿ�ֹͣ
                if(CGF.Mode == 1)
                {
                    CGF.Option = 1;
                    Param.C_Param[CGF.Option][0] = 840;
                }
                else if(CGF.Mode == 2)
                {
                    CGF.Option = 5;
                    Param.C_Param[CGF.Option][0] = 300;
                }
                else if(CGF.Mode == 3)
                {
                    CGF.Option = 6;
                    Param.C_Param[CGF.Option][0] = 720;
                }
                else if(CGF.Mode == 4)
                {
                    CGF.Option = 7;
                    Param.C_Param[CGF.Option][0] = 300;
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
