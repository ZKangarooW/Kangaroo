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
		if(Temp.Ctrl == 0)//����
        {
            Heater.PWM = 25;
        }
        else
        {
            Heater.PWM = 60;
        }
	}
	else
	{
		Heater.PWM = 0;
	}
}
