#include "Drv_PT1000.h"

/**********ȫ�ֱ���**********/
float PT_VALUE_1_TEMP;//̨��̽ͷ��ֵ
float PT_VALUE_2_TEMP;//̨��̽ͷ��ֵ

/**********�ֲ�����**********/
uint16_t ADC_Val[AD_LEN];//adc��ֵ 0:̨���¶�adֵ 1���ⲿ̽ͷ  2����Ƭ���ڲ��ĵ�ѹAD���ο���1.2f��
float TL431_V;//TL431��׼2.5V��ѹ�ĵ�ѹֵ
float Vref_AD;//��Ƭ���ڲ���ѹ��ADCֵ

/*
*****************************************************************
 * ����ԭ�ͣ�int Filter_ADC(uint8_t i)
 * ��    �ܣ������˲�
 * ��    �룺ADCͨ��
 * ��    �����˲���ĵ���ֵ
 * ��    ����uint8_t i
 * ��    �ã��ڲ����� 
*****************************************************************
*/
int Filter_ADC(uint8_t i)
{
    static int ADCvalue_Buf[AD_LEN][N];//���ڴ���ɼ�����adcֵ
    static int j[AD_LEN];//���ڼ���
    
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
float Filter_ADC_EMA(float AD_in,uint8_t i)
{   
    static float EMA_value[2];//EMA�˲����ֵ����Ϊ��Ҫ���������þ�̬
    float V_out;//��ѹֵ
    float R_value;//����ֵ
    float AD_T;//����Ŵ��ĵ�ѹֵ
    uint16_t ADC_value;//ADCֵ
    
    ADC_value = AD_in;//��adc��ֵ����

    // ��� ADC ֵ��Χ
    if (ADC_value <= 0 || ADC_value > 4095) {
        return EMA_value[i]; // ���ص�ǰ EMA ֵ��������
    }

    // �� ADC ֵת��Ϊ��ѹ
    V_out = ((float)ADC_value / (float)Vref_AD) * Vref;

    // ����ĸ�Ƿ�ӽ� 0
    if (fabs(V_out) < 0.0001f || fabs(Vref - V_out) < 0.0001f) {
        return EMA_value[i]; // ���ص�ǰ EMA ֵ��������
    }

    // ���� NTC ����ֵ
    AD_T = (R_910R/(R_3K+R_910R)*TL431_V) + V_out/OP_Value;//�����ѹֵ
    R_value = (AD_T*R_3K)/(TL431_V-AD_T)*1000;//��1000����Ϊ�������ǧŷΪ��λ�ģ�Ҫת����ŷķ

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
    double T_low = -5.0;//�¶ȷ�Χ������
    double T_high = 380.0;//�¶ȷ�Χ������
    double T_mid;

    //ʹ�ö��ַ����
    while ((T_high - T_low) > 0.0001) 
    {  
        //��������
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
    float Filter_PT1;//�˲����PT1000��ADCֵ̨��
	float Filter_PT2;//�˲����PT1000��ADCֵ�ⲿ
    
	T += dT;
    
    Vref_AD = Filter_ADC(2);//��ȡ���˲���Ƭ���ڲ���ѹ��ADCֵ
    TL431_V = 2.35f;//����TL431�ĵ�ѹֵ
    
    Filter_PT1 = Filter_ADC(1);//��ȡ���˲�PT1000��ADCֵ�ⲿ
    PT_VALUE_1_TEMP = Filter_ADC_EMA(Filter_PT1,1);//������ֵ�ⲿ
    
    Filter_PT2 = Filter_ADC(0);//��ȡ���˲�PT1000��ADCֵ̨��
    PT_VALUE_2_TEMP = Filter_ADC_EMA(Filter_PT2,0);//������ֵ̨��
    
	if(T >= 1.0f)
	{    
        Temp.Outside = Wolfram_Inverse(PT_VALUE_1_TEMP);//�ⲿ�¶�
        Temp.Mesa = Wolfram_Inverse(PT_VALUE_2_TEMP);//̨���¶�
        
		if(PT_VALUE_1_TEMP < 2200)//��������ⲿ̽ͷ
            Temp.Rel = Temp.Outside;//��ʵ�¶���ʾ�ⲿ̽ͷ����¶�
		else//����û�в����ⲿ̽ͷ
			Temp.Rel = Temp.Mesa;//��ʵ�¶���ʾ̨���¶�
        
		T = 0;
	}
}
