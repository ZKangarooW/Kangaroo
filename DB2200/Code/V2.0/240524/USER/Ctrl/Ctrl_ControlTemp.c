#include "Ctrl_ControlTemp.h"

/**********ȫ�ֱ�������******/
int Temp_Out;//�¶�pwm���ֵ
uint16_t adc_val;

/*
*****************************************************************
 * ����ԭ�ͣ� void PID_Init(void)
 * ��    �ܣ� pidϵ����ʼ��
*****************************************************************
*/
void PID_Init(void)
{
	Temp_Arg.Kp=10;
	Temp_Arg.Ki=0.2;
	Temp_Arg.Kd=0;
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
	
	if(pwm >= 40)
	{
		mode = 0;//����
	}
	else if(pwm < -50)
	{
		mode = 1;//����
        HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_SET);//�򿪷���
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
			COLD = 0;
			HEAT = pwm;
		}			
		else if(mode == 1)
		{
			COLD = (-pwm);
			HEAT = 0;
		}
	}
}
uint8_t Out_Enable;

/*
*****************************************************************
 * ����ԭ�ͣ� void Temp_Control(float dT)
 * ��    �ܣ� �¶ȼ��ȿ���
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    if(sys.Run_Status == 1)//����
    { 
		adc_val = Get_ADCVal(Ctrl_Temp);
		if(sys.CtrlTemp_Mode == 1)
		{
			HEAT_ICO = 1;//����ͼ��
		}
		else if(sys.CtrlTemp_Mode == 2)
		{
			HEAT_ICO = 2;//����ͼ��
			HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_SET);//�򿪷���
		}
		if((adc_val - ADC_Val > -100 && adc_val - ADC_Val < 100))
			Out_Enable = 1;
		else
			Out_Enable = 0;
		AltPID_Calculation(dT, adc_val, ADC_Val, &Temp_Arg, &Temp_Val, 100, Out_Enable * 1000);
		CoolTemp_Mode(dT,(int)Temp_Val.Out);
    }
    else 
    {
		sys.CtrlTemp_Mode = 0;
		Out_Enable = 0;
        Temp_Out = 0;//PWM���Ϊ��
		HEAT_ICO = 0;//ͼ�겻��ʾ
		HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_RESET);//�رշ���
        HEAT = 0;//���Ȳ�����
		COLD=0;
        Temp_ADDMode = 0;//��ʾģʽΪ��
    }
}

