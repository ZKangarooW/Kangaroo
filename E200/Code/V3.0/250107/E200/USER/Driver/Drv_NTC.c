#include "Drv_NTC.h"

#define ALPHA 0.1f  // ƽ�����ӣ�������Ӧ�ٶ�
#define R_REF 30000.0f  // �ο����� 5.1k��
#define V_IN 3.3f  // ��Դ��ѹ

#define AD_LEN 2//DMA��ȡ����
uint16_t ADC_Val[AD_LEN];//adc��ֵ 0:adֵ; 1��
float Filter_ADC_EMA(uint8_t i)
{   
    static float EMA_value[AD_LEN];
    uint16_t ADC_val;
    float V_out;
    float R_NTC;
    ADC_val = ADC_Val[i];//��adc��ֵ����

    // ��� ADC ֵ��Χ
    if (ADC_val <= 0 || ADC_val >= 4095) {
        
        return EMA_value[i]; // ���ص�ǰ EMA ֵ��������
    }

    // �� ADC ֵת��Ϊ��ѹ
    V_out = (ADC_val / 4095.0f) * V_IN;

    // ����ĸ�Ƿ�ӽ� 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) {
        return EMA_value[i]; // ���ص�ǰ EMA ֵ��������
    }

    // ���� NTC ����ֵ
    R_NTC = R_REF * ((V_IN / V_out) - 1);

    // ���� EMA �˲�ֵ
    EMA_value[i] = ALPHA * R_NTC + ((1 - ALPHA) * EMA_value[i]);
    
    return EMA_value[i];
}

/******************100K***************/
//#define A  0.0006834379508081105
//#define B  0.00021991049145573158
//#define C  9.074100194441566e-08
/** У׼ **/
#define A  -7.479824086506315e-05
#define B  0.0003174825283214902
#define C  -1.6641521707421694e-07
float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
{
    float temperature_K;
    float temperature_C1;   
    float logR = log(R_NTC); // ���� R �Ķ���
    temperature_K = 1.0 / (A + B * logR + C * logR * logR * logR); // �������¶�
    temperature_C1 = temperature_K - 273.15; // ת��Ϊ���϶�
    return temperature_C1*10;
}

float resistance[AD_LEN];
void Read_Temp(float dT)
{
    static float T;
    T += dT;

    resistance[0] = Filter_ADC_EMA(0); // ��ȡ����ֵ���Ѿ�����EMA�˲���
    resistance[1] = Filter_ADC_EMA(1); // ��ȡ����ֵ���Ѿ�����EMA�˲���
    
    if (T >= 1.0f) // 1S
    {
        if(sys.Calibration)
		{
            Heat_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[0]);//�����¶�
        }
        else
        {
            Heat_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[0]);//�����¶�
        }
		Cool_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[1]);//�����¶�
        T = 0;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Calibration(uint16_t temp,uint16_t temp1)
 * ��    �ܣ��¶�У׼����
 * ��    �룺temp��40���¶ȣ�temp1��60���¶�
 * ��    ����uint16_t temp,uint16_t temp1
*****************************************************************
*/
float Calibration_Temp;
void Calibration(uint16_t temp,uint16_t temp1)
{
	uint16_t Cal1,Cal2;
	
    Cal1 = 400 - temp;
    Cal2 = 600 - temp1;
    Calibration_Temp = (float)(Cal1 + Cal2)/2;
    
	Param.Calibration_Temp = Calibration_Temp;//�¶�У׼ϵ��
	Save_Param_En = 1;//����
}

void ADCDMA_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);//����TIM3�Ķ�ʱ������ˢ��
	HAL_ADC_Start_DMA(&hadc,(uint32_t *)ADC_Val, AD_LEN);//��DMA��ȡadcֵ
	HAL_ADCEx_Calibration_Start(&hadc);
    for (uint8_t i = 0; i <= 100; i++)
    {
        resistance[0] = Filter_ADC_EMA(0); // ��ȡ����ֵ���Ѿ�����EMA�˲���
        resistance[1] = Filter_ADC_EMA(1); // ��ȡ����ֵ���Ѿ�����EMA�˲���
        if (i == 100) // 1S
        {
            Heat_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[0]);//�����¶�
            Cool_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[1]);//�����¶�
        }
        HAL_Delay(10); // ��ʱ
    }
    Heat_Temp.Display_Temp = Heat_Temp.Rel_Temp;//���˺󿪻�������ʾ0Ȼ�����ʵ���¶�
    Cool_Temp.Display_Temp = Cool_Temp.Rel_Temp;//���˺󿪻�������ʾ0Ȼ�����ʵ���¶�
    HAL_Delay(10); // ��ʱ
}
