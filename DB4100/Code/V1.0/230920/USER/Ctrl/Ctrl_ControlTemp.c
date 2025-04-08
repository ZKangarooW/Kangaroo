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
	if(sys.Run_Status == 1)//����ϵͳ
	{
		CtrlTempADC_Val = Get_ADCVal(Temp.Ctrl);
		RelTempADC_Val = ADC_Val;
		AltPID_Calculation(dT, CtrlTempADC_Val, RelTempADC_Val, &Temp_Arg, &Temp_Val, 400, 400);
		if(Temp_Val.Out < 0) Temp_Val.Out = 0;
		HEAT = (int)Temp_Val.Out;
    }
	else
	{
        Temp_Val.Out = 0;
		HEAT = 0;//pwm�����
	}
}
