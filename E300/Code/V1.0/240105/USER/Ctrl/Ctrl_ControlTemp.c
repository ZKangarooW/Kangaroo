#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********�ֲ���������******/
float CtrlTempADC_Val,RelTempADC_Val;//�����¶Ⱥ�ʵ���¶ȵ�ADCֵ

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_PID(void)
 * ��    �ܣ��¶ȿ���PIDϵ��
*****************************************************************
*/
void Temp_PID(void)
{
	Temp_Arg.Kp = 120;
	Temp_Arg.Ki = 50*0.001f;
	Temp_Arg.Kd = 20000*0.001f;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if(sys.Run_Status)//����ϵͳ
	{
		CtrlTempADC_Val = Get_ADCVal(Temp.Ctrl);
		RelTempADC_Val = ADC_Val;
		AltPID_Calculation(dT, CtrlTempADC_Val, RelTempADC_Val, &Temp_Arg, &Temp_Val, 100, 1000);
		if(Temp_Val.Out < 0) Temp_Val.Out = 0;
		HEAT =(int)Temp_Val.Out;
    }
	else
	{
        Temp_Val.Out = 0;
		HEAT = 0;//pwm�����
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Temp_Time(float dT)
 * ��    �ܣ���̨�����ȵ�ʱ��
*****************************************************************
*/
void Check_Temp_Time(float dT)
{
    static float T;
    if(sys.Run_Status && Temp.Ctrl)
    {
        T += dT;
        if(T > 28800.0f)//8Сʱ
        {
            sys.Run_Status = 0;//ϵͳ�ر�
            sys.Time_Status = 0;//����ʱ�ر�
            SpeedSet_Flag = TimeSet_Flag = 1;//�ٶ����ã�ʱ������
            Temp_Twinkle_Time = Time_Twinkle_Time =0;//��˸ʱ������
            EC11A[0].EC11A_Knob = EC11A[1].EC11A_Knob = 0;//��ťʱ������
            Beep_Time = 5.0f;//��������0.1S
            Temp.ADDMode = 0;//������ʾģʽ����
            T = 0;
        }
    }
    else
    {
        T = 0;
    }
}
