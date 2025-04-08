#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;
uint8_t Protect;//������

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_PID(void)
 * ��    �ܣ��¶ȿ���PIDϵ��
*****************************************************************
*/
void Temp_PID(void)
{
    Temp_Arg.Kp = 3.16907954;
    Temp_Arg.Ki = 1.32044983;
    Temp_Arg.Kd = 5.28179932;
    Temp_Arg.Kp_i = 0.1;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void setPWM(float duty_cycle)
 * ��    �ܣ����� PWM ��������Ƽ�������
*****************************************************************
*/
void setPWM(float duty_cycle)
{
    if(duty_cycle>100)
        duty_cycle = 100;
    if(duty_cycle<0)
        duty_cycle = 0;
    if(Temp.Rel >= Temp.Ctrl)
        duty_cycle = 0;
    HEAT = (int)((duty_cycle*2));
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    if(sys.Run_Status == 1)
	{
        if(Temp.Ctrl)
        {
            if(HAL_GPIO_ReadPin(FGS_GPIO_Port,FGS_Pin) == 1)
            {
                Protect = 1;//�򿪷�����
                Beep_Flash = 30;//��������30��
                sys.Run_Status = 0;
            }
            AltPID_Calculation(dT,Temp.Ctrl,Temp.Rel,&Temp_Arg,&Temp_Val,80,20);   
            setPWM(Temp_Val.Out);
        }
	}
	else
	{
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}
