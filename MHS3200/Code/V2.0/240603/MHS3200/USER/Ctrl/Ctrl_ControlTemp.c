#include "Ctrl_ControlTemp.h"

#if(Integration_TYPE == 0)//���ó�����������ʱ
/**********ȫ�ֱ�������******/
int HEAT_Time;//�¶�pwm���ֵ
int PWM_Out;//pid���ֵ

/*
*****************************************************************
 * ����ԭ�ͣ�void temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void temp_Control(float dT)
{ 
    if(Run_Status == 1 && Temp_State == 1)//�������������¶Ⱥ��¶ȿ���
    { 
		if(Ctrl_Temp - Ture_Temp<=10)//�����¶ȼ�ȥʵ���¶�С��5���϶�ʱ
		{
			HEAT_Time += dT;
			if(HEAT_Time < PWM_Out)
			{
				HEAT = 100;
			}
			else
			{
				HEAT = 0;
			}
		}
    }
    else
    {
        HEAT = 0;//���Ȳ�����
        Temp_ADDMode = 0;//��ʾģʽΪ��
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void PID_Cap(float dT)
 * ��    �ܣ�PID���㣬�Ǽ���ʱ��
*****************************************************************
*/
void PID_Cap(float dT)
{
	static float T;
	if(Run_Status == 1 && Temp_State == 1)//�������������¶Ⱥ��¶ȿ���
    { 
		if(Ctrl_Temp - Ture_Temp > 10)
		{
			HEAT = 100;
			PWM_Out = 0;
		}
		else if(Ctrl_Temp - Ture_Temp<=10)//�����¶ȼ�ȥʵ���¶�С��5���϶�ʱ
		{
			T += dT;
			if(T < 2.0f)
			{
				HEAT = 0;
				PWM_Out = 0;
			}
			if(T == 2.0f)
			{
				PID_Calc(Ture_Temp,Ctrl_Temp);
				PWM_Out = (int)Temp_Val.Out;//pidֵ��ֵ
				HEAT_Time = 0;
				T = 0;
			}
		}
	}
	else
	{
		Temp_Val.SumError = 0;
		PWM_Out = 0;
	}
}
#endif
