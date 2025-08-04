#include "Drv_NTC.h"

/**********局部变量**********/
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

/**********全局变量**********/
uint16_t ADC_Val;//adc的值
uint8_t NTC_Res;//温度采样返回的状态

/*
*****************************************************************
 * 函数原型： int Filter_ADC(void)
 * 功    能： 滑动平均值滤波
 * 输    出： 滤波后的值
*****************************************************************
*/
#define N 100//采集100次
int ADCvalue_Buf[N];//用于储存采集到的adc值
int i = 0;
int Filter_ADC(void)
{
    char count;
    long sum = 0;
    HAL_ADC_Start(&hadc);//开始读取adc的值
    ADCvalue_Buf[i++] = HAL_ADC_GetValue(&hadc);//将adc的值储存
    if (i == N)//加入读了100组就从新开始
    {
        i = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf[count];//100组相加
    }
    if(ADCvalue_Buf[99] == 0)//如果没有读到100组就用第一次读到的数
        return ADCvalue_Buf[0];
    else//读到100组后
        return (int)(sum / N);//输出平均值
}

/*
*****************************************************************
 * 函数原型： uint16_t Get_Ntc_Temp(uint16_t value_adc)
 * 功    能： 计算出Ntc的温度
 * 输    入:  value_adc:adc读到的值
 * 参    数： uint16_t value_adc
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

    /******************温度补偿*********************/
    Safe_Rel_Temp = temp;//测得温度赋值
    return 0;
}

/*
*****************************************************************
 * 函数原型： void Read_Temp(float dT)
 * 功    能： 读取温度-10ms
*****************************************************************
*/
void Read_Temp(float dT)
{
    static float T;
    T += dT;
    ADC_Val = Filter_ADC();//滤波获取adc的滑动平均值
    if(T >= 1)//1S
    {
        NTC_Res = Get_Ntc_Temp(ADC_Val);//计算温度
        T = 0;
    }
}
