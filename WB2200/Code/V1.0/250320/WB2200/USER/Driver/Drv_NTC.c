#include "Drv_NTC.h"

/**********�ֲ���������******/
uint16_t ADC_Val[AD_LEN];//adc��ֵ 0:adֵ;

/*
*****************************************************************
 * ����ԭ�ͣ�float Filter_ADC_EMA(void)
 * ��    �ܣ�EMA�˲�
 * ��    �����˲���ĵ���ֵ
 * ��    �ã��ڲ����� 
*****************************************************************
*/
static float Filter_ADC_EMA(void)
{   
    uint16_t ADC_value;//ADCֵ
    float EMA_value = 0;//EMA�˲����ֵ
    float R_value;//����ֵ
    float V_out;//��ѹֵ
    ADC_value = ADC_Val[0];//��adc��ֵ����

    // ��� ADC ֵ��Χ
    if (ADC_value <= 0 || ADC_value >= 4095) 
    {
        return EMA_value; // ���ص�ǰ EMA ֵ��������
    }

    // �� ADC ֵת��Ϊ��ѹ
    V_out = (ADC_value / 4095.0f) * V_IN;

    // ����ĸ�Ƿ�ӽ� 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) 
    {
        return EMA_value; // ���ص�ǰ EMA ֵ��������
    }

    // ���� NTC ����ֵ
    R_value = R_REF * ((V_IN / V_out) - 1);

    // ���� EMA �˲�ֵ
    EMA_value = ALPHA * R_value + ((1 - ALPHA) * EMA_value);
    
    return EMA_value;
}

/******************100K***************/
//#define A  0.0006834379508081105
//#define B  0.00021991049145573158
//#define C  9.074100194441566e-08
/** У׼ **/
#define A  -7.479824086506315e-05
#define B  0.0003174825283214902
#define C  -1.6641521707421694e-07

/*
*****************************************************************
 * ����ԭ�ͣ�float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
 * ��    �ܣ�Steinhart_Hart�㷨�����¶�
 * ��    �룺����ֵ
 * ��    �����¶�
 * ��    ����float R_NTC
 * ��    �ã��ڲ����� 
*****************************************************************
*/
static float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
{
    float temperature_K;
    float temperature_C;
    float logR = log(R_NTC);// ���� R �Ķ���
    temperature_K = 1.0 / (A + B * logR + C * logR * logR * logR); // �������¶�
    temperature_C = temperature_K - 273.15; // ת��Ϊ���϶�
    return temperature_C*10;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Read_Temp(float dT)
 * ��    �ܣ���ȡ�¶�
 * ��    �룺��������
 * ��    ����float dT
*****************************************************************
*/
void Read_Temp(float dT)
{
    static float T;
    float Resistance1;
    T += dT;

    Resistance1 = Filter_ADC_EMA(); // ��ȡ����ֵ���Ѿ�����EMA�˲���

    if (T >= 1.0f) // 1S
    {
        Temp.Rel = Get_Ntc_Temp_Steinhart_Hart(Resistance1); // �����¶�
        T = 0;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Temp_Init(void)
 * ��    �ܣ��¶ȳ�ʼ��
*****************************************************************
*/
void Temp_Init(void)
{
    float Resistance1;
    HAL_TIM_Base_Start_IT(&htim15);//����TIM3�Ķ�ʱ������ˢ��
	HAL_ADC_Start_DMA(&hadc,(uint32_t *)ADC_Val, AD_LEN);//��DMA��ȡadcֵ
	HAL_ADCEx_Calibration_Start(&hadc);
    for (uint8_t i = 0; i <= 100; i++)
    {
        Resistance1 = Filter_ADC_EMA(); // ��ȡ�˲���ĵ���ֵ
        if (i == 100) // 1S
        {
            Temp.Rel = Get_Ntc_Temp_Steinhart_Hart(Resistance1); // �����¶�
        }
        HAL_Delay(10); // ��ʱ
    }
    Temp.Display_Rel = Temp.Rel;//���˺󿪻�������ʾ0Ȼ�����ʵ���¶�
    HAL_Delay(10); // ��ʱ
}
