#include "Drv_NTC.h"

/**********局部变量**********/
const uint16_t R100K_TAB[] = //R25=100K B25=3950K -25-150
{
//    160,//-10
//	170,//-12
    180,//-10
    189,//-9
    200,//-8
    210,//-7
    221,//-6
    233,//-5
    245,//-4
    258,//-3
    271,//-2
    284,//-1
    298,//0
    313,//1
    328,//2
    344,//3
    361,//4
    372,//5
    396,//6
    416,//7
    440,//8
	462,//9
	482,//10
	508,//11
    528,//12
	558,//13
	576,//14
    600,//15
    632,//16
    654,//17
    682,//18
    710,//19
    734,//20
    758,//21
    794,//22
    826,//23
    860,//24
    892,//25
    917,//26
    950,//27
    982,//28
    1014,//29
    1044,//30
    1075,//31
    1107,//32
    1146,//33
    1182,//34
    1260,//35
    1294,//36
    1324,//37
    1372,//38
	1393,//39
    1415,//40
    1465,//41
    1497,//42
    1556,//43
    1598,//44
    1621,//45
    1652,//46
    1720,//47
	1740,//48
    1760,//49
    1804,//50
    1842,//51
    1882,//52
    1920,//53
    1958,//54
    1994,//55
    2045,//56
	2083,//57
    2122,//58
    2142,//59
    2193,//60
    2245,//61
    2290,//62
    2330,//63
    2359,//64
    2400,//65
    2418,//66
    2460,//67
    2502,//68
    2539,//69
    2553,//70
    2580,//71
    2614,//72
    2648,//73
    2681,//74
    2710,//75
    2736,//76
    2765,//77
    2788,//78
    2812,//79
    2845,//80
    2870,//81
    2894,//82
    2934,//83
    2963,//84
    2989,//85
    3022,//86
    3042,//87
    3064,//88
    3092,//89
    3112,//90
    3132,//91
    3154,//92
    3176,//93
    3192,//94
	3202,//95
    3222,//96 
    3240,//97
    3269,//97
    3292,//98
	3315,//99
    3338,//100
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

/**********全局变量**********/
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
