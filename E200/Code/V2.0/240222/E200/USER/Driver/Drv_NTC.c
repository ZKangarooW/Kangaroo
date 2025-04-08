#include "Drv_NTC.h"

/**********�ֲ�����**********/
const uint16_t R100K_TAB[] = //R25=100K B25=3950K -25-150
{
	122,//-18
	129,//-17
	137,//-16
	145,//-15
	153,//-14
	161,//-13
	170,//-12
	180,//-11
	189,//-10
	200,//-9
	210,//-8
	221,//-7
	233,//-6
	245,//-5
	258,//-4
	271,//-3
	284,//-2
	298,//-1
	313,//0
	328,//1
	344,//2
	361,//3
	378,//4
	395,//5
	413,//6
	432,//7
	452,//8
	472,//9
	493,//10
	514,//11
	536,//12
	559,//13
	582,//14
	606,//15
	631,//16
	656,//17
	682,//18
	709,//19
	740,//20
	768,//21
	799,//22
	824,//23
	854,//24
	890,//25
	926,//26
	953,//27
	989,//28
	1014,//29
	1044,//30
	1077,//31
	1112,//32
	1147,//33
	1182,//34
	1218,//35
	1254,//36
	1290,//37
	1331,//38
	1366,//39
	1410,//40
	1440,//41
	1478,//42
	1516,//43
	1554,//44
	1593,//45
	1632,//46
	1670,//47
	1709,//48
	1748,//49
	1787,//50
	1826,//51
	1865,//52
	1904,//53
	1943,//54
	1981,//55
	2012,//56
	2058,//57
	2096,//58
	2134,//59
	2160,//60
	2209,//61
	2246,//62
	2282,//63
	2319,//64
	2355,//65
	2390,//66
	2426,//67
	2460,//68
	2495,//69
	2529,//70
	2562,//71
	2595,//72
	2628,//73
	2660,//74
	2692,//75
	2723,//76
	2754,//77
	2784,//78
	2813,//79
	2843,//80
	2871,//81
	2899,//82
	2927,//83
	2954,//84
	2981,//85
	3007,//86
	3032,//87
	3057,//88
	3082,//89
	3106,//90
	3129,//91
	3152,//92
	3175,//93
	3197,//94
	3218,//95
	3240,//96
	3260,//97
	3280,//98
	3300,//99
	3319,//100
	3338,//101
	3356,//102
	3374,//103
	3392,//104         
    3409,//105
    3426,//106
    3442,//107
    3458,//108
    3473,//109
    3489,//110
    3503,//111
    3518,//112
    3532,//113
    3545,//114
    3559,//115
    3572,//116
    3585,//117
    3597,//118
    3609,//119
    3621,//120
    3632,//121
    3643,//122
    3654,//123
    3665,//124
    3675,//125
    3685,//126
    3695,//127
    3705,//128
    3714,//129
};

/**********ȫ�ֱ���**********/
#define AD_LEN 2//DMA��ȡ����
uint16_t ADC_Val[AD_LEN];//adc��ֵ 0:�¶�adֵ�� 1��adֵ;
uint16_t ADC_Val1,ADC_Val2;
float  Calibration_Temp;
	
/*
*****************************************************************
 * ����ԭ�ͣ�int Filter_ADC(void)
 * ��    �ܣ�����ƽ��ֵ�˲�
 * ��    �����˲����ֵ
*****************************************************************
*/
#define N 50//�ɼ�100��
int ADCvalue_Buf[N];//���ڴ���ɼ�����adcֵ
int i = 0;
int Filter_ADC(void)
{
    char count;
    long sum = 0;
    
    ADCvalue_Buf[i++] = ADC_Val[0];//��adc��ֵ����
	
    if (i == N)//�������100��ʹ��¿�ʼ
    {
        i = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf[count];//100�����
    }
    if(ADCvalue_Buf[N-1] == 0)//���û�ж���100����õ�һ�ζ�������
        return ADCvalue_Buf[0];
    else//����100���
        return (int)(sum / N);//���ƽ��ֵ
}

/*
*****************************************************************
 * ����ԭ�ͣ�int Filter_ADC1(void)
 * ��    �ܣ�����ƽ��ֵ�˲�
 * ��    �����˲����ֵ
*****************************************************************
*/
int ADCvalue_Buf1[N];//���ڴ���ɼ�����adcֵ
int j = 0;
int Filter_ADC1(void)
{
    char count;
    long sum = 0;
    
    ADCvalue_Buf1[j++] = ADC_Val[1];//��adc��ֵ����
	
    if (j == N)//�������100��ʹ��¿�ʼ
    {
        j = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf1[count];//100�����
    }
    if(ADCvalue_Buf1[N-1] == 0)//���û�ж���100����õ�һ�ζ�������
        return ADCvalue_Buf1[0];
    else//����100���
        return (int)(sum / N);//���ƽ��ֵ
}

/*
*****************************************************************
 * ����ԭ�ͣ�uint16_t Get_Ntc_Temp(uint16_t value_adc)
 * ��    �ܣ������Ntc���¶�
 * ��    ��: value_adc:adc������ֵ
 * ��    ����uint16_t value_adc
*****************************************************************
*/
#define SHORT_CIRCUIT_THRESHOLD 15
#define OPEN_CIRCUIT_THRESHOLD 4096
uint8_t index_l, index_r ;
uint16_t Get_Ntc_Temp(uint16_t value_adc)
{
    uint8_t R100k_Tab_Size = 148;
    int temp = 0;
    if(value_adc <= SHORT_CIRCUIT_THRESHOLD)
    {
        return 1;
    }
    else if(value_adc >= OPEN_CIRCUIT_THRESHOLD)
    {
        return 2;
    }
    else if(value_adc < R100K_TAB[0])
    {
        return 3;
    }

    else if(value_adc > R100K_TAB[R100k_Tab_Size - 1])
    {
        return 4;
    }

    index_l = 0;
    index_r = R100k_Tab_Size - 1;
    for(; index_r - index_l > 1;)
    {
        if((value_adc <= R100K_TAB[index_r]) && (value_adc > R100K_TAB[(index_l + index_r) % 2 == 0 ? (index_l + index_r) / 2 : (index_l + index_r) / 2 ]))
        {
            index_l = (index_l + index_r) % 2 == 0 ? (index_l + index_r) / 2 : (index_l + index_r) / 2 ;
        }
        else
        {
            index_r = (index_l + index_r) / 2;
        }
    }
    if(R100K_TAB[index_l] == value_adc)
    {
        temp = (((int)index_l) - 18) * 10; //rate *10
    }
    else if(R100K_TAB[index_r] == value_adc)
    {
        temp = (((int)index_r) - 18) * 10; //rate *10
    }
    else
    {
        if(R100K_TAB[index_r] - R100K_TAB[index_l] == 0)
        {
            temp = (((int)index_l) - 18) * 10; //rate *10
        }
        else
        {
            temp = (((int)index_l) - 18) * 10 + ((value_adc - R100K_TAB[index_l] ) * 100 + 5) / 10 / (R100K_TAB[index_r] - R100K_TAB[index_l]);
        }
    }

    /******************�¶Ȳ���*********************/
    return temp;
}

/*
*****************************************************************
 * ����ԭ�ͣ�uint16_t Get_ADCVal(uint16_t temp)
 * ��    �ܣ����㵱ǰ�¶ȵ�adcֵ
 * ��    �룺temp����ǰ�¶�
 * ��    ����ADCֵ
 * ��    ����uint16_t temp
*****************************************************************
*/
uint16_t Get_ADCVal(uint16_t temp)
{
	uint16_t adc,adc1;
	float val2;
	uint16_t val3,val1;
	
	val3 = (temp/10)+18;
	val2 = (float)(temp%10)/10;
	
	val1 = ((temp+10)/10)+18;
	
	adc = R100K_TAB[val3];
	adc1 = R100K_TAB[val1];
	return adc+((adc1-adc)*val2)+((adc1-adc)*0.1)-1;
}


/*
*****************************************************************
 * ����ԭ�ͣ�void Calibration(uint16_t temp,uint16_t temp1)
 * ��    �ܣ��¶�У׼����
 * ��    �룺temp��40���¶ȣ�temp1��60���¶�
 * ��    ����uint16_t temp,uint16_t temp1
*****************************************************************
*/
void Calibration(uint16_t temp,uint16_t temp1)
{
	float Cal1,Cal2;
	uint16_t ADCv1,ADCv2;
	
	ADCv1 = Get_ADCVal(temp);
	Cal1 = 1402/(float)ADCv1;
	ADCv2 = Get_ADCVal(temp1);
	Cal2 = 2171/ADCv2;
	Calibration_Temp = (float)(Cal1 + Cal2)/2;
	Param.Calibration_Temp = Calibration_Temp;//�¶�У׼ϵ��
	Save_Param_En = 1;//����
}

/*
*****************************************************************
 * ����ԭ�ͣ�void ADCDMA_Init(void)
 * ��    �ܣ�ADC��DMA�ĳ�ʼ��
*****************************************************************
*/
void ADCDMA_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);//����TIM3�Ķ�ʱ������ˢ��
	HAL_ADC_Start_DMA(&hadc,(uint32_t *)ADC_Val, AD_LEN);//��DMA��ȡadcֵ
	HAL_ADCEx_Calibration_Start(&hadc);
	for(uint8_t i=0;i<10;i++)
	{
		Heat_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val[0]*Calibration_Temp);//�����¶�
		Cool_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val[1]/Calibration_Temp);//�����¶�
		HAL_Delay(10);
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Read_Temp(float dT)
 * ��    �ܣ� ��ȡ�¶�-10ms
*****************************************************************
*/
void Read_Temp(float dT)
{
    static float T;
    T += dT;
	ADC_Val1 = Filter_ADC();//�˲���ȡadc�Ļ���ƽ��ֵ
	ADC_Val2 = Filter_ADC1();
    if(T >= 2.0f)//1S
    {
		if(sys.Calibration)
		{
			Heat_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val1);//�����¶�
		}
		else
		{
			Heat_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val1*Calibration_Temp);//�����¶�
		}
		Cool_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val2/Calibration_Temp);//�����¶�
		T = 0;
    }
}
