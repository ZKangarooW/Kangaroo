#include "Drv_NTC.h"

/**********局部变量**********/
const uint16_t R100K_TAB[] = //R25=100K B25=3950K -25-150
{
    221,//-10
    233,//-9
    245,//-8
    258,//-7
    271,//-6
    284,//-5
    298,//-4
    313,//-3
    328,//-2
    344,//-1
    361,//0
    372,//1
    396,//2
    416,//3
    440,//4
	462,//5
	482,//6
	508,//7
    528,//8
	563,//9
	600,//10
    616,//11
    634,//12
    649,//13
    668,//14
    684,//15
    708,//16
    730,//17
    746,//18
    768,//19
    788,//20
    798,//21
    830,//22 
    854,//23
    882,//24
    892,//25
    928,//26
    941,//27
    967,//28
    994,//29
    1014,//30
    1034,//31
    1068,//32  
    1104,//33
    1140,//34
    1174,//35
    1199,//36
    1226,//37
    1260,//38
    1294,//39
    1331,//40
    1368,//41
    1410,//42****
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
    2150,//59
    2190,//60
    2222,//61
    2260,//62
    2300,//63
    2332,//64
    2370,//65
    2404,//66
    2432,//67
    2468,//68
    2506,//69
    2539,//70
    2574,//71
    2612,//72
    2642,//73
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
    3724,//130
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
