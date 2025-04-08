#include "Drv_NTC.h"

/**********局部变量**********/
const uint16_t R100K_TAB[] = //R25=100K B25=3950K -25-150
{
	122,//-17
	129,//-16
	137,//-15
	145,//-14
	153,//-13
	161,//-12
	170,//-11
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
	378,//5
	395,//6
	413,//7
	432,//8
	452,//9
	472,//10
	493,//11
	514,//12
	536,//13
	559,//14
	582,//15
	606,//16
	631,//17
	656,//18
	682,//19
	709,//20
	736,//21
	764,//22
	793,//23
	822,//24
	852,//25
	882,//26
	914,//27
	945,//28
	977,//29
	1010,//30
	1044,//31
	1077,//32
	1112,//33
	1147,//34
	1182,//35
	1218,//36
	1254,//37
	1290,//38
	1327,//39
	1364,//40
	1402,//41
	1440,//42
	1478,//43
	1516,//44
	1554,//45
	1593,//46
	1632,//47
	1670,//48
	1709,//49
	1748,//50
	1787,//51
	1826,//52
	1865,//53
	1904,//54
	1943,//55
	1981,//56
	2020,//57
	2058,//58
	2096,//59
	2134,//60
	2171,//61
	2209,//62
	2246,
	2282,
	2319,
	2355,
	2390,
	2426,
	2460,
	2495,
	2529,
	2562,
	2595,
	2628,
	2660,
	2692,
	2723,
	2754,
	2784,
	2813,
	2843,
	2871,
	2899,
	2927,
	2954,
	2981,
	3007,
	3032,
	3057,
	3082,
	3106,
	3129,
	3152,
	3175,
	3197,
	3218,
	3240,
	3260,
	3280,
	3300,
	3319,//109
	3338,//108
	3356,//107
	3374,//106
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
#define AD_LEN 2//DMA获取长度
uint16_t ADC_Val[AD_LEN];//adc的值 0:温度ad值。 1：ad值;
uint16_t ADC_Val1,ADC_Val2;
float  Calibration_Temp;
	
/*
*****************************************************************
 * 函数原型：int Filter_ADC(void)
 * 功    能：滑动平均值滤波
 * 输    出：滤波后的值
*****************************************************************
*/
#define N 50//采集100次
int ADCvalue_Buf[N];//用于储存采集到的adc值
int i = 0;
int Filter_ADC(void)
{
    char count;
    long sum = 0;
    
    ADCvalue_Buf[i++] = ADC_Val[0];//将adc的值储存
	
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
 * 函数原型：int Filter_ADC1(void)
 * 功    能：滑动平均值滤波
 * 输    出：滤波后的值
*****************************************************************
*/
int ADCvalue_Buf1[N];//用于储存采集到的adc值
int j = 0;
int Filter_ADC1(void)
{
    char count;
    long sum = 0;
    
    ADCvalue_Buf1[j++] = ADC_Val[1];//将adc的值储存
	
    if (j == N)//加入读了100组就从新开始
    {
        j = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf1[count];//100组相加
    }
    if(ADCvalue_Buf1[N-1] == 0)//如果没有读到100组就用第一次读到的数
        return ADCvalue_Buf1[0];
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
        temp = (((int)index_l) - 17) * 10; //rate *10
    }
    else if(R100K_TAB[index_r] == value_adc)
    {
        temp = (((int)index_r) - 17) * 10; //rate *10
    }
    else
    {
        if(R100K_TAB[index_r] - R100K_TAB[index_l] == 0)
        {
            temp = (((int)index_l) - 17) * 10; //rate *10
        }
        else
        {
            temp = (((int)index_l) - 17) * 10 + ((value_adc - R100K_TAB[index_l] ) * 100 + 5) / 10 / (R100K_TAB[index_r] - R100K_TAB[index_l]);
        }
    }

    /******************温度补偿*********************/
    return temp;
}

/*
*****************************************************************
 * 函数原型：uint16_t Get_ADCVal(uint16_t temp)
 * 功    能：计算当前温度的adc值
 * 输    入：temp：当前温度
 * 输    出：ADC值
 * 参    数：uint16_t temp
*****************************************************************
*/
uint16_t Get_ADCVal(uint16_t temp)
{
	uint16_t adc,adc1;
	float val2;
	uint16_t val3,val1;
	
	val3 = (temp/10)+17;
	val2 = (float)(temp%10)/10;
	
	val1 = ((temp+10)/10)+17;
	
	adc = R100K_TAB[val3];
	adc1 = R100K_TAB[val1];
	return adc+((adc1-adc)*val2)+((adc1-adc)*0.1)-1;
}


/*
*****************************************************************
 * 函数原型：void Calibration(uint16_t temp,uint16_t temp1)
 * 功    能：温度校准计算
 * 输    入：temp：40的温度，temp1：60的温度
 * 参    数：uint16_t temp,uint16_t temp1
*****************************************************************
*/
void Calibration(uint16_t temp,uint16_t temp1)
{
	float Cal1,Cal2;
	uint16_t ADCv1,ADCv2;
	
	ADCv1 = Get_ADCVal(temp);
	Cal1 = 1364/(float)ADCv1;
	ADCv2 = Get_ADCVal(temp1);
	Cal2 = 2134/ADCv2;
	Calibration_Temp = (float)(Cal1 + Cal2)/2;
	Param.Calibration_Temp = Calibration_Temp;//温度校准系数
	Save_Param_En = 1;//保存
	
}

/*
*****************************************************************
 * 函数原型：void ADCDMA_Init(void)
 * 功    能：ADC和DMA的初始化
*****************************************************************
*/
void ADCDMA_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);//开启TIM3的定时，用于刷新
	HAL_ADC_Start_DMA(&hadc,(uint32_t *)ADC_Val, AD_LEN);//用DMA获取adc值
	HAL_ADCEx_Calibration_Start(&hadc);
	for(uint8_t i=0;i<10;i++)
	{
		Heat_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val[0]*Calibration_Temp);//计算温度
		Cool_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val[1]/Calibration_Temp);//计算温度
		HAL_Delay(10);
	}
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
	ADC_Val1 = Filter_ADC();//滤波获取adc的滑动平均值
	ADC_Val2 = Filter_ADC1();
    if(T >= 2.0f)//1S
    {
		if(sys.Calibration)
		{
			Heat_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val1);//计算温度
		}
		else
		{
			Heat_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val1*Calibration_Temp);//计算温度
		}
		Cool_Temp.Rel_Temp = Get_Ntc_Temp(ADC_Val2/Calibration_Temp);//计算温度
		T = 0;
		
    }
}
