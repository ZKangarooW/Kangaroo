#include "Ctrl_ControlTemp.h"

/**********�ֲ���������******/
uint8_t Out_Enable;//��������Ŀ���
float adc_val,ctrl_val;
uint8_t water_type,step;//�ж����ͻ���ˮ0��ˮ��1��
uint8_t Temp_type;//�¶�����

/*
*****************************************************************
 * ����ԭ�ͣ�static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * ��    �ܣ�̨���¶ȿ���
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
	if(Ctrl_temp > 2800) Ctrl_temp = 2800;//��߼���280��
	adc_val = Get_ADCVal(Ctrl_temp)*10;//����ADCֵ
	ctrl_val = PT_VALUE_2_TEMP*10;//ʵ�ʵ�adcֵ
	if(Ctrl_temp > 2300 && Temp.Mesa_Temp > 2000)//��������¶ȴ���230�ȣ�̨���¶ȳ���200��
		Out_Enable = 1;//�򿪻��ּ���
	else if((adc_val - ctrl_val > -200 && adc_val - ctrl_val < 200))
		Out_Enable = 1;//�򿪻��ּ���
	else
		Out_Enable = 0;//�رջ��ּ���
	AltPID_Calculation(dT, adc_val, ctrl_val, &Temp_Arg, &Temp_Val, 100, Out_Enable * 1000);
	HEAT_ON();//����ģ�鿪��
	if(Temp_Val.Out < 0)
		Temp_Val.Out = 0;
	HEAT =(int)Temp_Val.Out;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Control(float dT)
 * ��    �ܣ��¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if(sys.Run_Status && PT_VALUE_1_TEMP >= 2000)//����ϵͳ����̨��
	{
		if(Temp_type == 1)//������ⲿ̽ͷ�л�����
		{
			Temp.Temp_ADDMode = 0;
			Temp_type = 0;
		}
		if(Temp.Ctrl_Temp)
		{
			Mesa_Ctrl(dT, Temp.Ctrl_Temp);
		}
		else
		{
			water_type = 0;
			HEAT_OFF();//����ģ��ر�
			HEAT = 0;//pwm�����
			step = 0;
		}
	}
	else if(sys.Run_Status && PT_VALUE_1_TEMP < 2000)//����ϵͳ����ˮ��
	{
		if(Temp.Ctrl_Temp)
		{	
			if(Temp_type == 0)//�����̨��̽ͷ�л�����
			{
				Temp.Temp_ADDMode = 0;
				Temp_type = 1;
			}
			if(Temp.Ctrl_Temp < 1000)//�����¶�С��100��
			{
				if(Temp.Ctrl_Temp - Temp.Rel_Temp > 100)
				{
					Mesa_Ctrl(dT, Temp.Ctrl_Temp*2.8f);
				}
				else if(Temp.Ctrl_Temp - Temp.Rel_Temp < 100 && Temp.Ctrl_Temp - Temp.Rel_Temp >= 50)
				{
					Mesa_Ctrl(dT, Temp.Ctrl_Temp*2.5f);
				}
				else if(Temp.Ctrl_Temp - Temp.Rel_Temp < 50 && Temp.Ctrl_Temp - Temp.Rel_Temp >= 10)
				{
					Mesa_Ctrl(dT, Temp.Ctrl_Temp*2.2f);
				}
				else if(Temp.Ctrl_Temp - Temp.Rel_Temp < 10 && Temp.Ctrl_Temp - Temp.Rel_Temp > 0)
				{
					Mesa_Ctrl(dT, Temp.Ctrl_Temp*2.1f);
				}
				else
				{
					Temp_Val.Out = 0;
					HEAT =(int)Temp_Val.Out;
				}
			}
			else if(Temp.Ctrl_Temp == 1000)//�����¶ȵ���100��
			{
				if(!water_type)
				{
					if(step == 0)
					{
						Mesa_Ctrl(dT, 2800);
						if(Temp.Rel_Temp >= 1000)
						{
							step = 1;
						}
					}
					else if(step == 1)
					{
						Mesa_Ctrl(dT, 2200);
					}
					if(Temp.Rel_Temp >= 1040)
					{
						water_type = 1;//�ж�Ϊ��
					}
				}
				else
				{
					if(Temp.Ctrl_Temp - Temp.Rel_Temp > 100)
					{
						Mesa_Ctrl(dT, Temp.Ctrl_Temp*2.8f);
					}
					else if(Temp.Ctrl_Temp - Temp.Rel_Temp < 100 && Temp.Ctrl_Temp - Temp.Rel_Temp >= 50)
					{
						Mesa_Ctrl(dT, Temp.Ctrl_Temp*2.5f);
					}
					else if(Temp.Ctrl_Temp - Temp.Rel_Temp < 50 && Temp.Ctrl_Temp - Temp.Rel_Temp >= 10)
					{
						Mesa_Ctrl(dT, Temp.Ctrl_Temp*2.2f);
					}
					else if(Temp.Ctrl_Temp - Temp.Rel_Temp < 10 && Temp.Ctrl_Temp - Temp.Rel_Temp > 0)
					{
						Mesa_Ctrl(dT, Temp.Ctrl_Temp*2.1f);
					}
					else
					{
						Temp_Val.Out = 0;
						HEAT =(int)Temp_Val.Out;
					}
				}
			}
			else if(Temp.Ctrl_Temp > 1000)//�����¶ȴ���100��
			{
				if(Temp.Ctrl_Temp - Temp.Rel_Temp > 100)
				{
					Mesa_Ctrl(dT, Temp.Ctrl_Temp * 2.2f);
				}
				else if(Temp.Ctrl_Temp - Temp.Rel_Temp < 100 && Temp.Ctrl_Temp - Temp.Rel_Temp >= 50)
				{
					Mesa_Ctrl(dT, Temp.Ctrl_Temp * 2.0f);
				}
				else if(Temp.Ctrl_Temp - Temp.Rel_Temp < 50 && Temp.Ctrl_Temp - Temp.Rel_Temp > 0)
				{
					Mesa_Ctrl(dT, Temp.Ctrl_Temp * 1.8f);
				}
				else
				{
					Temp_Val.Out = 0;
					HEAT =(int)Temp_Val.Out;
				}
			}
		}
		else
		{
			water_type = 0;
			HEAT_OFF();//����ģ��ر�
			HEAT = 0;//pwm�����
			step = 0;
		}
	}
	else
	{
		water_type = 0;
		HEAT_OFF();//����ģ��ر�
		HEAT = 0;//pwm�����
		step = 0;
	}
}
