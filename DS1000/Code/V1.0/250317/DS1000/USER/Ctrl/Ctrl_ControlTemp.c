#include "Ctrl_ControlTemp.h"

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
		if(Temp.Ctrl == 1)//����
        {
            Heater.PWM = 30;
        }
        else
        {
            Heater.PWM = 50;
        }
	}
	else
	{
		Heater.PWM = 0;
	}
}
