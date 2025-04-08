#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/*
*****************************************************************
 * ����ԭ�ͣ�static void Set_Heating_Power(float pwm)
 * ��    �ܣ����ü����̹���
 * ��    ��: ���ȵ�pwm���� 
 * ��    ����float control_signal
*****************************************************************
*/
static void Set_Heating_Power(float pwm)
{
    // ����PID������Ƽ����̹���
    int power = (int)pwm;  // �������ź�תΪ���ʣ���Χ0-255��
    if(Temp.Rel>Temp.Mesa)
    {
        HEAT = 0;
        HEAT_OFF;
    }
    else if (power < 0)
    {
        power = 0;  // ���ƹ���Ϊ0
        HEAT = power;//����С��300��PWM����
        HEAT_OFF;
    }
    else if (power < 100)
    {
        HEAT = power;//����С��300��PWM����
        HEAT_OFF;
    }
    
    else//������ʴ���300���Ҳ�С��0���ü̵�������
    {
        power = 0;//���ƹ���Ϊ0
        HEAT = power;//����С��300��PWM����
        HEAT_ON;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_PID(void)
 * ��    �ܣ��¶ȿ���PIDϵ��
*****************************************************************
*/
void Temp_PID(void)
{
	Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 8*0.001f;//18
	Temp_Arg.Kd = 90*0.001f;;//��̨��
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * ��    �ܣ�̨���¶ȿ���
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    AltPID_Calculation(dT, Ctrl_temp, Temp.Mesa, &Temp_Arg, &Temp_Val, 100, 300);
    Set_Heating_Power(Temp_Val.Out);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    if(sys.Run_Status)//����ϵͳ����̨��
	{
        if(Temp.Ctrl)
        {
            Mesa_Ctrl(dT, Temp.Ctrl);
        }
        else
        {
            HEAT = 0;//pwm�����
            HEAT_OFF;
        }
	}
    else
	{
		HEAT = 0;//pwm�����
        HEAT_OFF;
	}
}
