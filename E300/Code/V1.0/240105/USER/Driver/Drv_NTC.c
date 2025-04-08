#include "Drv_NTC.h"

/**********局部变量**********/
const uint16_t R100K_TAB[] = //R25=100K B25=3950K -25-150
{
    160,//-10
	170,//-9
    180,//-8
    189,//-7
    200,//-6
    210,//-5
    221,//-4
    233,//-3
    245,//-2
    258,//-1
    271,//0
    284,//1
    298,//2
    313,//3
    328,//4
    344,//5
    361,//6
    372,//7
    396,//8
    416,//9
    440,//10
	462,//11
	482,//12
	508,//13
    528,//14
	558,//15
	576,//16
    600,//17
    632,//18
    654,//19
    682,//20
    710,//21
    734,//22
    758,//23
    794,//24
    826,//25
    860,//26
    892,//27
    917,//28
    950,//29
    982,//30
    1014,//31
    1044,//32
    1075,//33
    1107,//34
    1146,//35
    1182,//36
    1220,//37
    1260,//38
    1294,//39
    1331,//40
    1372,//41
    1405,//42
    1454,//43
    1497,//44
    1556,//45
    1598,//46
    1632,//47
    1672,//48
    1720,//49
    1760,//50
    1804,//51
    1842,//52
    1882,//53
    1920,//54
    1958,//55
    2010,//56
    2079,//57
    2122,//58
    2158,//59
    2193,//60
    2233,//61
    2272,//62
    2316,//63
    2347,//64
    2380,//65
    2412,//66
    2446,//67
    2475,//68
    2506,//69
    2539,//70
    2574,//71
    2608,//72
    2638,//73
    2664,//74
    2698,//75
    2726,//76
    2760,//77
    2784,//78
    2812,//79
    2842,//80
    2870,//81
    2900,//82
    2924,//83
    2952,//84
    2976,//85
    2996,//86
    3022,//87
    3042,//88
    3064,//89
    3092,//90
    3112,//91
    3132,//92
    3154,//93
    3176,//94
    3196,//95
    3214,//96
    3234,//97
    3250,//98
    3269,//99
    3292,//100
    3338,//101
    3354,//102
    3374,//103
    3384,//104
    3392,//105
    3409,//106
    3426,//107
    3442,//108
    3458,//109
    3473,//110
    3489,//111
    3503,//112
    3518,//113
    3532,//114
    3545,//115
    3559,//116
    3572,//117
    3585,//118
    3597,//119
    3609,//120
    3621,//121
    3632,//122
    3643,//123
    3654,//124
    3665,//125
    3675,//126
    3685,//127
    3695,//128
    3705,//129
    3714,//130
};

/**********全局变量声明******/
uint16_t ADC_Val;//adc的值

/*
*****************************************************************
 * 函数原型：int Filter_ADC(void)
 * 功    能：滑动平均值滤波
 * 输    出：滤波后的值
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
    if(ADCvalue_Buf[N-1] == 0)//如果没有读到100组就用第一次读到的数
        return ADCvalue_Buf[0];
    else//读到100组后
        return (int)(sum / N);//输出平均值
}

/*
*****************************************************************
 * 函数原型：uint16_t Get_Ntc_Temp(uint16_t value_adc)
 * 功    能：计算出Ntc的温度
 * 输    入: value_adc:adc读到的值
 * 参    数：uint16_t value_adc
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
        temp = (((int)index_l) - 10) * 10; //rate *10
    }
    else if(R100K_TAB[index_r] == value_adc)
    {
        temp = (((int)index_r) - 10) * 10; //rate *10
    }
    else
    {
        if(R100K_TAB[index_r] - R100K_TAB[index_l] == 0)
        {
            temp = (((int)index_l) - 10) * 10; //rate *10
        }
        else
        {
            temp = (((int)index_l) - 10) * 10 + ((value_adc - R100K_TAB[index_l] ) * 100 + 5) / 10 / (R100K_TAB[index_r] - R100K_TAB[index_l]);
        }
    }

    return temp;
}

/*
*****************************************************************
 * 函数原型：uint16_t Get_ADCVal(int16_t temp)
 * 功    能：计算当前温度的adc值
 * 输    入：temp：当前温度
 * 输    出：ADC值
 * 参    数：uint16_t temp
*****************************************************************
*/
uint16_t Get_ADCVal(int16_t temp)
{
	int16_t adc,adc1;
	float val2;
	int16_t val3,val1;
	
	val3 = (temp/10)+10;
	val2 = (float)(temp%10)/10;
	
	val1 = ((temp+10)/10)+10;
	
	adc = R100K_TAB[val3];
	adc1 = R100K_TAB[val1];
	return adc+((adc1-adc)*val2);
}

/*
*****************************************************************
 * 函数原型：void Read_Temp(float dT)
 * 功    能：读取温度-10ms
*****************************************************************
*/
void Read_Temp(float dT)
{
    static float T;
    T += dT;
    
    ADC_Val = Filter_ADC();//滤波获取adc的滑动平均值
    
    if(T >= 1.0f)//1S
    {
        Temp.Rel = Get_Ntc_Temp(ADC_Val);//计算温度
        T = 0;
    }
}


/* 
*****************************************************************
 * 函数原型：void Temp_Init(void)
 * 功    能：开机显示温度
*****************************************************************
*/
void Temp_Init(void)
{
    for(uint8_t i =0;i<=100;i++)
    {
        ADC_Val = Filter_ADC();
        if(i == 100)//1S
        {
            Temp.Rel = Get_Ntc_Temp(ADC_Val);//计算温度
            Temp.Display_Rel = Temp.Rel;//用来显示
        }
        HAL_Delay(10);//没有延时开机读不出温度
    }
}
