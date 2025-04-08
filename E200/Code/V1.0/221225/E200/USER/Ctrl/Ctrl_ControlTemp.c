#include "Ctrl_ControlTemp.h"

/**********ȫ�ֱ�������******/
int Temp_Out,UC_Temp_Out;//���������pwm�͵����ȵ�pwm
int8_t val;

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

/*
*****************************************************************
 * ����ԭ�ͣ�void CoolTemp_Mode(float dT,int pwm)
 * ��    �ܣ����������л�
*****************************************************************
*/
void CoolTemp_Mode(float dT,int pwm)
{
	static float T;
	static uint8_t Mode,mode;//��ʱ�洢��ǰģʽ
	
	if(pwm >= 0)
	{
		if(pwm > 120)
			WIND_OFF;
		mode = 0;//����
	}
	else if(pwm < 0)
	{
		if(pwm < -600)
			WIND_ON;
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
		if(mode == 0)
		{
			val = 1;
			HEAT = pwm;
		}			
		else if(mode == 1)
		{
			val = -1;
			if(Cool_Temp.Ctrl_Temp <= 220)
				COLD = (-pwm)+450;
			else if(Cool_Temp.Ctrl_Temp <= 240)
				COLD = (-pwm)+400;
			else if(Cool_Temp.Ctrl_Temp <= 250)
				COLD = (-pwm)+365;
			else if(Cool_Temp.Ctrl_Temp <= 280)
				COLD = (-pwm)+300;
			else if(Cool_Temp.Ctrl_Temp <= 300)
				COLD = (-pwm)+200;
			else if(Cool_Temp.Ctrl_Temp <= 310)
				COLD = (-pwm)+180;
			else if(Cool_Temp.Ctrl_Temp <= 320)
				COLD = (-pwm)+170;
			else if(Cool_Temp.Ctrl_Temp <= 330)
				COLD = (-pwm)+160;
			else
				COLD = (-pwm)+20;
		}
	}
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
		PID_Temp(Get_ADCVal(Heat_Temp.Ctrl_Temp)/Calibration_Temp,ADC_Val1,&HeatTemp_Arg,&HeatTemp_Val);//PID����
		UC_Temp_Out = (int)HeatTemp_Val.Out;//PIDֵ��ֵ
		PID_Temp(Get_ADCVal(Cool_Temp.Ctrl_Temp)*Calibration_Temp,ADC_Val2,&CoolTemp_Arg,&CoolTemp_Val);//PID����
		Temp_Out = (int)CoolTemp_Val.Out;//PIDֵ��ֵ
	}
	else if(sys.Calibration == 1)
	{
		WIND_OFF;//�رշ���
		Temp_Out = 0;
		if(sys.Calibration_Step == 0)
		{
			PID_Temp(Get_ADCVal(400),ADC_Val1,&HeatTemp_Arg,&HeatTemp_Val);//PID����
			UC_Temp_Out = (int)HeatTemp_Val.Out;//PIDֵ��ֵ
		}
		else
		{
			PID_Temp(Get_ADCVal(600),ADC_Val1,&HeatTemp_Arg,&HeatTemp_Val);//PID����
			UC_Temp_Out = (int)HeatTemp_Val.Out;//PIDֵ��ֵ
		}
	}
	else
	{
		WIND_OFF;//�رշ���
		UC_Temp_Out = 0;
		Temp_Out = 0;
	}
	
	CoolTemp_Mode(dT, Temp_Out);
	if(UC_Temp_Out < 0)
		UC_Temp_Out = 0;
	UC_HEAT = UC_Temp_Out;
}
