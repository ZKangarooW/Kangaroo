#include "Drv_NTC.h"

#define ALPHA 0.05f  // ƽ�����ӣ�������Ӧ�ٶ�
#define R_REF 10000.0f  // �ο����� 5.1k��
#define V_IN 3.3f  // ��Դ��ѹ

#define AD_LEN 1//DMA��ȡ����
uint16_t ADC_Val2[AD_LEN];//adc��ֵ 0:adֵ;
float EMA_value = 0;
uint16_t ADC_val1;
float V_out;
float R_NTC;
float Te = 0.0f;
float Filter_ADC_EMA(void)
{   
    ADC_val1 = ADC_Val2[0];//��adc��ֵ����

    // ��� ADC ֵ��Χ
    if (ADC_val1 <= 0 || ADC_val1 >= 4095) {
        
        return EMA_value; // ���ص�ǰ EMA ֵ��������
    }

    // �� ADC ֵת��Ϊ��ѹ
    V_out = (ADC_val1 / 4095.0f) * V_IN;

    // ����ĸ�Ƿ�ӽ� 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) {
        return EMA_value; // ���ص�ǰ EMA ֵ��������
    }

    // ���� NTC ����ֵ
    R_NTC = R_REF * ((V_IN / V_out) - 1);

    // ���� EMA �˲�ֵ
    EMA_value = ALPHA * R_NTC + ((1 - ALPHA) * EMA_value);
    
    return EMA_value;
}
/******************10K***************/
//#define A 0.0011480191821922857
//#define B 0.0002309316762082348
//#define C 1.009730930918305e-07

#define A 0.0006865629623061078
#define B 0.0002170264653468129
#define C 8.064505232781423e-08
/******************100K***************/
//#define A  0.0006834379508081105
//#define B  0.00021991049145573158
//#define C  9.074100194441566e-08


float temperature_K;
float temperature_C1;   

float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
{
    float logR = log(R_NTC); // ���� R �Ķ���
    temperature_K = 1.0 / (A + B * logR + C * logR * logR * logR); // �������¶�
    temperature_C1 = temperature_K - 273.15 + Te; // ת��Ϊ���϶�
    return temperature_C1*10;
}

float resistance1;
void Read_Temp(float dT)
{
    static float T;
    T += dT;

    resistance1 = Filter_ADC_EMA()*0.9442857142857143; // ��ȡ����ֵ���Ѿ�����EMA�˲���

    if (T >= 1.0f) // 1S
    {
        Temp.Rel = Get_Ntc_Temp_Steinhart_Hart(resistance1); // �����¶�
        T = 0;
    }
}

void Temp_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim15);//����TIM3�Ķ�ʱ������ˢ��
	HAL_ADC_Start_DMA(&hadc,(uint32_t *)ADC_Val2, AD_LEN);//��DMA��ȡadcֵ
	HAL_ADCEx_Calibration_Start(&hadc);
    for (uint8_t i = 0; i <= 100; i++)
    {
        resistance1 = Filter_ADC_EMA(); // ��ȡ�˲���ĵ���ֵ
        if (i == 100) // 1S
        {
            Temp.Rel = Get_Ntc_Temp_Steinhart_Hart(resistance1); // �����¶�
        }
        HAL_Delay(10); // ��ʱ
    }
    HAL_Delay(10); // ��ʱ
}
