#include "Drv_PT1000.h"

/**********ȫ�ֱ���**********/
float PT_VALUE_1_TEMP;//�ⲿ̽ͷ��ֵ
float PT_VALUE_2_TEMP;//̨��̽ͷ��ֵ

/**********�ֲ�����**********/
uint16_t ADC_Val[AD_LEN];//adc��ֵ 0:̨���¶�adֵ�� 1���ⲿ̽ͷadֵ

/*
*****************************************************************
 * ����ԭ�ͣ�float Filter_ADC_EMA(uint8_t i)
 * ��    �ܣ�EMA�˲�
 * ��    �룺ADCͨ��
 * ��    �����˲���ĵ���ֵ
 * ��    ����uint8_t i
 * ��    �ã��ڲ����� 
*****************************************************************
*/
float Filter_ADC_EMA(uint8_t i)
{   
    static float EMA_value[AD_LEN] = {0};//EMA˲ֵ(静态变量自动初始化为0)
    uint16_t ADC_value;//ADCֵ
    float V_out;//��ѹֵ
    float R_value;//����ֵ
    float AD_T;
    ADC_value = ADC_Val[i];//��adc��ֵ����

    // ��� ADC ֵ��Χ
    if (ADC_value <= 0 || ADC_value > 4095) {
        return EMA_value[i]; // ���ص�ǰ EMA ֵ��������
    }

    // �� ADC ֵת��Ϊ��ѹ
    V_out = (ADC_value / 4096.0f) * V_IN;

    // ����ĸ�Ƿ�ӽ� 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) {
        return EMA_value[i]; // ���ص�ǰ EMA ֵ��������
    }

    // ���� NTC ����ֵ
    AD_T = V_out/OP_Value/Vref+K1;//�����ѹֵ
    R_value = 3000*AD_T/(1-AD_T);

    // ���� EMA �˲�ֵ
    EMA_value[i] = ALPHA * R_value + ((1 - ALPHA) * EMA_value[i]);
    
    return EMA_value[i];
}

/** У׼ **/
#define R0 1000  // �ο�����
#define A   0.003908299761668694
#define B   -5.774954439024853e-07
#define C   -6.86686242500016e-15
/*
*****************************************************************
 * ����ԭ�ͣ�static double Wolfram_Inverse(double R_test) 
 * ��    �ܣ�Wolfram��ʽ��������㺯��
 * ��    �룺����ֵ
 * ��    �����¶�
 * ��    ����double R_test
 * ��    �ã��ڲ����� 
*****************************************************************
*/
static double Wolfram_Inverse(double R_test) 
{
    double T_low = -5.0;  // �¶ȷ�Χ������
    double T_high = 380.0;  // �¶ȷ�Χ������
    double T_mid;

    // ʹ�ö��ַ����
    while ((T_high - T_low) > 0.0001) 
    {  // ��������
        T_mid = (T_low + T_high) / 2.0;
        double R_calculated = R0 * (1 + A * T_mid + B * T_mid * T_mid + C * T_mid * T_mid * T_mid);

        if (R_calculated > R_test) 
        {
            T_high = T_mid;
        } 
        else 
        {
            T_low = T_mid;
        }
    }

    return (T_low + T_high)*10 / 2.0;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void ADCDMA_Init(void)
 * ��    �ܣ�ADC��DMA�ĳ�ʼ��
*****************************************************************
*/
void ADCDMA_Init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc);
    HAL_TIM_Base_Start_IT(&htim15);//����TIM15�Ķ�ʱ������ˢ��
	HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADC_Val, AD_LEN);//��DMA��ȡadcֵ
    if(sys.Display == 0)
    {
        for(uint8_t i = 0; i < 200; i++)
        {
            PT_VALUE_1_TEMP = Filter_ADC_EMA(0);//������ֵ
            PT_VALUE_2_TEMP = Filter_ADC_EMA(1);//������ֵ
            Read_Temp(0.1f);
        }
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�float CelsiusToFahrenheit(uint8_t type,int16_t celsius) 
 * ��    �ܣ����϶�ת���϶�
*****************************************************************
*/
float CelsiusToFahrenheit(uint8_t type,int16_t celsius) 
{
    if(type)
        return ((float)celsius * 90 / 50) + 320;
    else
        return celsius;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Read_Temp(float dT)
 * ��    �ܣ���ȡ�¶�-10ms
*****************************************************************
*/
void Read_Temp(float dT)
{
	static float T;
	
	T += dT;
    PT_VALUE_1_TEMP = Filter_ADC_EMA(0)*1.003;//������ֵ
    PT_VALUE_2_TEMP = Filter_ADC_EMA(1)*1.003;//������ֵ

    
	if(T >= 1.0f)
	{    
        Temp.Outside = Wolfram_Inverse(PT_VALUE_1_TEMP);//�ⲿ�¶�
        Temp.Mesa = Wolfram_Inverse(PT_VALUE_2_TEMP);//̨���¶�
        
        if(PT_VALUE_1_TEMP < 2400)//��������ⲿ̽ͷ
            Temp.Rel = Temp.Outside;//��ʵ�¶���ʾ�ⲿ̽ͷ����¶�
		else//����û�в����ⲿ̽ͷ
			Temp.Rel = Temp.Mesa;//��ʵ�¶���ʾ̨���¶�
		T = 0;
	}
}
