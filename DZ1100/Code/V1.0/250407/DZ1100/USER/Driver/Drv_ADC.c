#include "Drv_ADC.h"

/**********�ֲ�����**********/
uint16_t ADC_Val[AD_LEN];//ADC��ֵ
uint16_t F_ADC;//�˲����ADCֵ
float ADC_V;//ADC�õ��ĵ�ѹ
float Power_V;//��ص�ѹ
//float ADC_ASD[4];

/*
*****************************************************************
 * ����ԭ�ͣ�void Drv_ADC_Init(void)
 * ��    �ܣ�ADC������ʼ��
*****************************************************************
*/
void Drv_ADC_Init(void)
{
    //����ADC������ģʽ
	ADC_ConfigRunMode(ADC_CLK_DIV_128, ADC_RESULT_LEFT);	//����ADCʱ��Ϊϵͳʱ�ӵ�128��Ƶ��ADC���Ϊ����룬���ж�ADCʱ���в�����ο�"��΢8051оƬADCģ��Ӧ�ñʼ�"
	
	//����ADCת��ͨ��
	ADC_EnableChannel(ADC_CH_16);	
	GPIO_SET_MUX_MODE(P20CFG, GPIO_P20_MUX_AN16);	
	
	//����ADC LDO
	ADC_EnableLDO();
	ADC_ConfigADCVref(ADC_VREF_3V);		//ADC_VREF_1P2V, ADC_VREF_2V, ADC_VREF_2P4V, ADC_VREF_3V	
	
	//����ADC�ж�
	ADC_EnableInt();
	IRQ_SET_PRIORITY(IRQ_ADC,IRQ_PRIORITY_HIGH);	
	IRQ_ALL_ENABLE();
}

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
 * ����ԭ�ͣ�void Get_ADC_Value(float dT)
 * ��    �ܣ���ȡADC��ֵ
*****************************************************************
*/
void Get_ADC_Value(float dT)
{
    /*�¶Ȳ���*/	
	ADC_Start();
	ADC_GO();
	while(ADC_IS_BUSY);
	ADC_Val[0] =  ADC_GetADCResult();   
	ADC_Stop();	
    
    F_ADC = Filter_ADC(0);
    ADC_V = (float)(F_ADC)/4096*V_IN;
    Power_V = ADC_V/0.3333f;//����1��3����Mŷķ����Ϊ��λ��ͬ
//    ADC_ASD[0] = ADC_Val[0];
//    ADC_ASD[1] = F_ADC;
//    ADC_ASD[2] = ADC_V;
//    ADC_ASD[3] = Power_V;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Power(float dT)
 * ��    �ܣ�����ص���������
*****************************************************************
*/
void Check_Power(float dT)
{
    if(sys.Run_Status)
    {
        if(Power_V < 6.8f)
        {
            LED1_ON;
        }
        else
        {
            LED1_OFF;
        }
    }
    else
    {
        if(Power_V < 7.0f)
        {
            LED1_ON;
        }
        else
        {
            LED1_OFF;
        }
    }
}
