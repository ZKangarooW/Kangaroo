#include "Drv_NTC.h"

/**********局部变量**********/
const uint16_t R100K_TAB[] = //R25=100K B25=3950K -25-150
{
    170,//-10
    180,//-9
    189,//-8
    200,//-7
    210,//-6
    221,//-5
    233,//-4
    245,//-3
    258,//-2
    271,//-1
    284,//0
    298,//1
    313,//2
    328,//3
    344,//4
    361,//5
    381,//6
    404,//7
    425,//8
    448,//9
	474,//10
	492,//11
	516,//12
    548,//13
	586,//14
	611,//15
    600,//16
    632,//17
    654,//18
    682,//19
    710,//20
    734,//21
    758,//22
    794,//23
    826,//24
    858,//25
    892,//26
    928,//27
    960,//28
    994,//29
    1034,//30
    1068,//31
    1104,//32
    1140,//33
    1174,//34
    1216,//35
    1260,//36
    1294,//37
    1331,//38
    1368,//39
    1410,//40
    1442,//41
    1482,//42
    1520,//43
    1560,//44
    1603,//45
    1640,//46
    1680,//47
    1720,//48
    1760,//49
    1804,//50
    1842,//51
    1882,//52
    1920,//53
    1958,//54
    1994,//55
    2035,//56
    2072,//57
    2110,//58
    2140,//59
    2170,//60
    2206,//61
    2241,//62
    2280,//63
    2316,//64
    2351,//65
    2387,//66
    2418,//67
    2450,//68
    2487,//69
    2522,//70
    2553,//71
    2587,//72
    2617,//73
    2645,//74
    2674,//75
    2703,//76
    2732,//77
    2764,//78
    2795,//79
    2824,//80
    2853,//81
    2882,//82
    2904,//83
    2929,//84
    2959,//85
    2982,//86
    3003,//87
    3028,//88
    3048,//89
    3072,//90
    3098,//91
    3118,//92
    3138,//93
    3160,//94
    3178,//95
    3196,//96
    3216,//97
    3235,//98
    3255,//99
    3278,//100
    3308,//101
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

    /******************温度补偿*********************/
    Ture_Temp = temp;//测得温度赋值
	Rel_Temp = Ture_Temp;
    return 0;
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

/**
 * @brief 温度校准
 *
 * @param temp 测得的adc值
 * @param t1 设定的温度值
 * @param n1 在t1下测到的温度值
 * @param t2 设定的温度值
 * @param n2 在t2下测到的温度值
 */
uint16_t Temp_Calibration(uint16_t temp,uint16_t t1, uint16_t n1, uint16_t t2, uint16_t n2)
{
    float x1, y1, x2, y2, a, b, y;
    
    x1 = Get_ADCVal(t1);
    y1 = Get_ADCVal(n1);
    x2 = Get_ADCVal(t2);
    y2 = Get_ADCVal(n2);
    
    a = (y2 - y1) / (x2 - x1);
    b = y1 - a * x1;
    
    y = a * temp + b;
    
    return y;
}
uint16_t ADC_New;
/*
*****************************************************************
 * 函数原型：void Read_Temp(void)
 * 功    能：读取温度-10ms
*****************************************************************
*/
void Read_Temp(void)
{
    static uint8_t Num;
    Num++;
    ADC_Val = Filter_ADC();//滤波获取adc的滑动平均值
//    ADC_Val = Temp_Calibration(ADC_New, 570, 590, 750, 770);
//    ADC_Val = ADC_New;
    if(Num == 100)//1S
    {
        NTC_Res = Get_Ntc_Temp(ADC_Val);//计算温度
        Num = 0;
    }
}
