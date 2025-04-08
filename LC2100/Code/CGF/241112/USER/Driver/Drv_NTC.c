#include "Drv_NTC.h"

/**********�ֲ�����**********/
const uint16_t R100K_TAB[] = //R25=100K B25=3950K -25-150
{
387,
407,
429,
451,
474,
498,
523,
549,
575, 
603, 
631, 
660, 
691, 
722, 
754, 
787, 
820,
855, 
890, 
927, 
964, 
1002, 
1040, 
1079, 
1119, 
1160, 
1201, 
1244, 
1286, 
1329, 
1373, 
1417, 
1461, 
1506, 
1551, 
1596, 
1641, 
1686, 
1732, 
1777, 
1823, 
1868, 
1913, 
1958, 
2003, 
2048, 
2093, 
2137, 
2181, 
2225, 
2269, 
2312, 
2354, 
2396,
2438, 
2479, 
2519, 
2559, 
2598,
2636,
2674,
2711,
2748,
2784,
2819,
2853,
2887,
2920,
2952,
2984,
3014,
3044,
3074,
3102,
3130,
3157,
3184,
3209,
3235,
3259,
3283,
3306,
3329, 
3351, 
3372, 
3393, 
3413, 
3433, 
3452, 
3470, 
3488, 
3506, 
3523, 
3540, 
3556, 
3571, 
3587, 
3601, 
3616, 
3629, 
3643, 
3656, 
3668, 
3681, 
3693, 
3704, 
3715, 
3726, 
3736, 
3746, 
3756, 
3766, 
3775, 
3784, 
3793, 
3801, 
3809, 
3817,//97 
3825,//98 
3832,//99 
3839,//100 
3846,//101 
3853,//102 
3860,//103 
3866,//104
3872,//105 
3878,//106 
3884,//107 
3890,//108 
3895,//109
3901,//110 
3906,//111
3911,//112
3916,//113
3920,//114
3925,//115
3929,//116
3934,//117
3938,//118
3942,//119
3946,//120
};

/**********ȫ�ֱ���**********/
uint16_t ADC_Val;//adc��ֵ
uint8_t NTC_Res;//�¶Ȳ������ص�״̬

/*
*****************************************************************
 * ����ԭ�ͣ� int Filter_ADC(void)
 * ��    �ܣ� ����ƽ��ֵ�˲�
 * ��    ���� �˲����ֵ
*****************************************************************
*/
#define N 100//�ɼ�100��
int ADCvalue_Buf[N];//���ڴ���ɼ�����adcֵ
int i = 0;
int Filter_ADC(void)
{
    char count;
    long sum = 0;
    HAL_ADC_Start(&hadc);//��ʼ��ȡadc��ֵ
    ADCvalue_Buf[i++] = HAL_ADC_GetValue(&hadc);//��adc��ֵ����
    if (i == N)//�������100��ʹ��¿�ʼ
    {
        i = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf[count];//100�����
    }
    if(ADCvalue_Buf[99] == 0)//���û�ж���100����õ�һ�ζ�������
        return ADCvalue_Buf[0];
    else//����100���
        return (int)(sum / N);//���ƽ��ֵ
}

/*
*****************************************************************
 * ����ԭ�ͣ� uint16_t Get_Ntc_Temp(uint16_t value_adc)
 * ��    �ܣ� �����Ntc���¶�
 * ��    ��:  value_adc:adc������ֵ
 * ��    ���� uint16_t value_adc
*****************************************************************
*/
#define SHORT_CIRCUIT_THRESHOLD 15
#define OPEN_CIRCUIT_THRESHOLD 4096
uint8_t index_l, index_r ;
uint16_t Get_Ntc_Temp(uint16_t value_adc)
{
    uint8_t R100k_Tab_Size = 141;
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
        temp = (((int)index_l) - 20) * 10; //rate *10
    }
    else if(R100K_TAB[index_r] == value_adc)
    {
        temp = (((int)index_r) - 20) * 10; //rate *10
    }
    else
    {
        if(R100K_TAB[index_r] - R100K_TAB[index_l] == 0)
        {
            temp = (((int)index_l) - 20) * 10; //rate *10
        }
        else
        {
            temp = (((int)index_l) - 20) * 10 + ((value_adc - R100K_TAB[index_l] ) * 100 + 5) / 10 / (R100K_TAB[index_r] - R100K_TAB[index_l]);
        }
    }

    /******************�¶Ȳ���*********************/
    Safe_Rel_Temp = temp;//����¶ȸ�ֵ
    return 0;
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
    ADC_Val = Filter_ADC();//�˲���ȡadc�Ļ���ƽ��ֵ
    if(T >= 1)//1S
    {
        NTC_Res = Get_Ntc_Temp(ADC_Val);//�����¶�
        T = 0;
    }
}
