#include "Drv_PT1000.h"

/**********ȫ�ֱ���**********/
float PT_VALUE_1_TEMP;//̨��̽ͷ��ֵ

/**********�ֲ�����**********/
uint16_t ADC_Val[AD_LEN];//adc��ֵ 0:̨���¶�adֵ

float REF_V;//2.5V
float REF_AD;//�ڲ���ad
float PT10;
float V1;
int AD1;

#define N 100//�ɼ�100��
int Filter_ADC(uint8_t i)
{
    static int ADCvalue_Buf[AD_LEN][N];//���ڴ���ɼ�����adcֵ
    static int j[AD_LEN];
    
    char count;
    long sum = 0;
    
    
    ADCvalue_Buf[i][j[i]++] =ADC_Val[i];
	
    if (j[i] == N)//�������100��ʹ��¿�ʼ
    {
        j[i] = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf[i][count];//100�����
    }
    if(ADCvalue_Buf[i][N-1] == 0)//���û�ж���100����õ�һ�ζ�������
        return ADCvalue_Buf[i][0];
    else//����100���
        return (int)(sum / N);//���ƽ��ֵ
}

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
float V_out;//��ѹֵ
float R_value;//����ֵ
float AD_T;
uint16_t ADC_value;//ADCֵ
float Filter_ADC_EMA(float AD_1)
{   
    float EMA_value;//EMA�˲����ֵ
    
    ADC_value = AD_1;//��adc��ֵ����

    // ��� ADC ֵ��Χ
    if (ADC_value <= 0 || ADC_value > 4095) {
        return EMA_value; // ���ص�ǰ EMA ֵ��������
    }

    // �� ADC ֵת��Ϊ��ѹ
    V_out = ((float)ADC_value / (float)AD1) * V_IN;

    // ����ĸ�Ƿ�ӽ� 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) {
        return EMA_value; // ���ص�ǰ EMA ֵ��������
    }

    // ���� NTC ����ֵ
    AD_T = (0.91/3.91*V1) + V_out/OP_Value;//�����ѹֵ
    R_value = (AD_T*3)/(V1-AD_T)*1000;

    // ���� EMA �˲�ֵ
    EMA_value = ALPHA * R_value + ((1 - ALPHA) * EMA_value);
    
    return EMA_value;
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
    
    AD1 = Filter_ADC(2);
    REF_V = Filter_ADC(1);
    V1 = (REF_V / 4096) * 3.3f;
    PT10 = Filter_ADC(0);
    PT_VALUE_1_TEMP = Filter_ADC_EMA(PT10);//������ֵ
	if(T >= 1.0f)
	{    
        Temp.Mesa = Wolfram_Inverse(PT_VALUE_1_TEMP);//̨���¶�
		Temp.Rel = Temp.Mesa;//��ʵ�¶���ʾ̨���¶�
		T = 0;
	}
}
