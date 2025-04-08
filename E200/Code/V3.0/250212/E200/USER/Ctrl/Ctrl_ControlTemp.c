#include "Ctrl_ControlTemp.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Iint(void)
 * ��    �ܣ��¶ȳ�ʼ��
*****************************************************************
*/
void Temp_Iint(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//����tim1ͨ��2��PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//����tim3ͨ��2��PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//����tim3ͨ��2��PWM
}

/**********�ṹ��************/
_PID_Val_ HeatTemp_Val;//pid���ݽṹ
_PID_Arg_ HeatTemp_Arg;//pid����ϵ��
_PID_Val_ CoolTemp_Val;//pid���ݽṹ
_PID_Arg_ CoolTemp_Arg;//pid����ϵ��

/*
*****************************************************************
 * ����ԭ�ͣ� void PID_Init(void)
 * ��    �ܣ� pidϵ����ʼ��
*****************************************************************
*/
void PID_Init(void)
{
	HeatTemp_Arg.Kp=3.75;
	HeatTemp_Arg.Ki=0.0798;
	HeatTemp_Arg.Kd=0;
	HeatTemp_Arg.Kp_i = 0.3;
    
	CoolTemp_Arg.Kp=3.15;
	CoolTemp_Arg.Ki=0.0116;
	CoolTemp_Arg.Kd=0;
    CoolTemp_Arg.Kp_i = 0.3;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void CoolTemp_Mode(float dT,int pwm)
 * ��    �ܣ����������л�
*****************************************************************
*/uint8_t Mode,mode;//��ʱ�洢��ǰģʽ
void CoolTemp_Mode(float dT,float Ctrl_temp,float pwm)
{
	static float T;
	static float T1;
	
	if(pwm >= 10 && (Ctrl_temp > Cool_Temp.Rel_Temp))
	{
		mode = 0;//����
	}
	else if(pwm < -10 && (Ctrl_temp < Cool_Temp.Rel_Temp))
	{
		mode = 1;//����
	}
		
	if(Mode != mode)//���ģʽ�任��
	{
		T += dT;//��ʼ��ʱ
		if(T <= 1.0f)//һ��û�Ѽ��Ⱥ����䶼���Ͳ�����
		{
			COLD = 0;
			HEAT = 0;
		}
		else//һ��󽫸ĵ�ģʽ��ֵ
		{
			T = 0;
			Mode = mode;
		}
	}
	else//û�иı�ģʽ�������
	{
        if(Mode == 1)//����
        {
            if(pwm < -60)
            {
                T1 +=dT;
                if(T1 > 10.0)
                {
                    T1 = 0;
                    WIND_ON;
                }
            }
            else if(pwm > 10)
            {
                T1 +=dT;
                if(T1 > 10.0)
                {
                    T1 = 0;
                    WIND_OFF;
                }
            }
            else
            {
                T1 = 0;
            }
                
            if(Ctrl_temp < Cool_Temp.Rel_Temp && pwm <0)
            {
                HEAT = 0;
                COLD = (int)(ABS(pwm*10));
            }
            else
            {
                HEAT = 0;
                COLD = 0;
            }
        }
        else
        {
            if(pwm > 50)
                WIND_OFF;
            if(Ctrl_temp > Cool_Temp.Rel_Temp&& pwm >0)
            {
                HEAT = (int)(pwm*10);
                COLD = 0;
            }
            else
            {
                HEAT = 0;
                COLD = 0;
            } 
        }
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void setPWM(float duty_cycle)
 * ��    �ܣ����� PWM ��������Ƽ�������
*****************************************************************
*/
void setPWM(float Ctrl_Temp,float duty_cycle)
{
    if(duty_cycle>100)
        duty_cycle = 100;
    if(duty_cycle<0)
        duty_cycle = 0;
    if(Heat_Temp.Rel_Temp >= Ctrl_Temp)
        duty_cycle = 0;
    UC_HEAT = (int)(duty_cycle*10);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
        AltPID_Calculation(dT,Heat_Temp.Ctrl_Temp,Heat_Temp.Rel_Temp,&HeatTemp_Arg,&HeatTemp_Val,80,20);   
        setPWM(Heat_Temp.Ctrl_Temp, HeatTemp_Val.Out);
	}
	else
	{
		setPWM(Heat_Temp.Ctrl_Temp,0);
	}
}

void Cool_Temp_Control(float dT)
{ 
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
        AltPID_Calculation(dT,Cool_Temp.Ctrl_Temp,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
        CoolTemp_Mode(dT,Cool_Temp.Ctrl_Temp,CoolTemp_Val.Out);
	}
    else if(sys.Calibration == 1)
	{
		WIND_OFF;//�رշ���
		if(sys.Calibration_Step == 0)
		{
            AltPID_Calculation(dT,260,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
            CoolTemp_Mode(dT,260,CoolTemp_Val.Out);
		}
		else
		{
            AltPID_Calculation(dT,400,Cool_Temp.Rel_Temp,&CoolTemp_Arg,&CoolTemp_Val,80,20);   
            CoolTemp_Mode(dT,400,CoolTemp_Val.Out);
		}
	}
	else
	{
		WIND_OFF;//�رշ���
        CoolTemp_Mode(dT,0,0);
	}
}
