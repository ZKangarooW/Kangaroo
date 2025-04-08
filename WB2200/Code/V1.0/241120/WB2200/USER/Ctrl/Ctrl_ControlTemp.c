#include "Ctrl_ControlTemp.h"

/**********�ṹ��************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********ȫ�ֱ�������******/
uint8_t Protect;//������
uint16_t LIMIT_Val;//��������

/**********�ֲ���������******/
float CtrlTempADC_Val,RelTempADC_Val;

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_PID(void)
 * ��    �ܣ��¶ȿ���PIDϵ��
*****************************************************************
*/
void Temp_PID(void)
{
    Temp_Arg.Kp = 2;
    Temp_Arg.Ki = 5 * 0.001f;
    Temp_Arg.Kd = 100;
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
            RelTempADC_Val = ADC_Val;
			CtrlTempADC_Val = Get_ADCVal(Temp.Ctrl);
			AltPID_Calculation(dT,CtrlTempADC_Val,RelTempADC_Val,&Temp_Arg,&Temp_Val,100,LIMIT_Val);//�¶�PID����
			if(Temp_Val.Out > 1000)
				Temp_Val.Out = 1000;
			if(Temp_Val.Out <= 0)
				Temp_Val.Out = 0;
			HEAT = (int)Temp_Val.Out;
		}
	}
	else
	{
		Temp_Val.Out = 0; 
		HEAT = Temp_Val.Out;
	}
}
