#include "Drv_PT1000.h"

/**********全局变量**********/
float PT_VALUE_1_TEMP;//台面探头阻值

/**********局部变量**********/
uint16_t ADC_Val[AD_LEN];//adc的值 0:台面温度ad值

float REF_V;//2.5V
float REF_AD;//内部的ad
float PT10;
float V1;
int AD1;

#define N 100//采集100次
int Filter_ADC(uint8_t i)
{
    static int ADCvalue_Buf[AD_LEN][N];//用于储存采集到的adc值
    static int j[AD_LEN];
    
    char count;
    long sum = 0;
    
    
    ADCvalue_Buf[i][j[i]++] =ADC_Val[i];
	
    if (j[i] == N)//加入读了100组就从新开始
    {
        j[i] = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf[i][count];//100组相加
    }
    if(ADCvalue_Buf[i][N-1] == 0)//如果没有读到100组就用第一次读到的数
        return ADCvalue_Buf[i][0];
    else//读到100组后
        return (int)(sum / N);//输出平均值
}

/*
*****************************************************************
 * 函数原型：float Filter_ADC_EMA(uint8_t i)
 * 功    能：EMA滤波
 * 输    入：ADC通道
 * 输    出：滤波后的电阻值
 * 参    数：uint8_t i
 * 调    用：内部调用 
*****************************************************************
*/
float V_out;//电压值
float R_value;//电阻值
float AD_T;
uint16_t ADC_value;//ADC值
float Filter_ADC_EMA(float AD_1)
{   
    float EMA_value;//EMA滤波后的值
    
    ADC_value = AD_1;//将adc的值储存

    // 检查 ADC 值范围
    if (ADC_value <= 0 || ADC_value > 4095) {
        return EMA_value; // 返回当前 EMA 值，不更新
    }

    // 将 ADC 值转换为电压
    V_out = ((float)ADC_value / (float)AD1) * V_IN;

    // 检查分母是否接近 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) {
        return EMA_value; // 返回当前 EMA 值，不更新
    }

    // 计算 NTC 电阻值
    AD_T = (0.91/3.91*V1) + V_out/OP_Value;//计算电压值
    R_value = (AD_T*3)/(V1-AD_T)*1000;

    // 更新 EMA 滤波值
    EMA_value = ALPHA * R_value + ((1 - ALPHA) * EMA_value);
    
    return EMA_value;
}

/** 校准 **/
#define R0 1000  // 参考电阻
#define A   0.003908299761668694
#define B   -5.774954439024853e-07
#define C   -6.86686242500016e-15
/*
*****************************************************************
 * 函数原型：static double Wolfram_Inverse(double R_test) 
 * 功    能：Wolfram公式的逆向计算函数
 * 输    入：电阻值
 * 输    出：温度
 * 参    数：double R_test
 * 调    用：内部调用 
*****************************************************************
*/
static double Wolfram_Inverse(double R_test) 
{
    double T_low = -5.0;  // 温度范围的下限
    double T_high = 380.0;  // 温度范围的上限
    double T_mid;

    // 使用二分法求解
    while ((T_high - T_low) > 0.0001) 
    {  // 迭代精度
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
 * 函数原型：void ADCDMA_Init(void)
 * 功    能：ADC和DMA的初始化
*****************************************************************
*/
void ADCDMA_Init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc);
    HAL_TIM_Base_Start_IT(&htim15);//开启TIM15的定时，用于刷新
	HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADC_Val, AD_LEN);//用DMA获取adc值
    
    if(sys.Display == 0)
    {
        for(uint8_t i = 0; i < 200; i++)
        {
            PT_VALUE_1_TEMP = Filter_ADC_EMA(0);//计算阻值
            Read_Temp(0.1f);
        }
    }
}

/*
*****************************************************************
 * 函数原型：float CelsiusToFahrenheit(uint8_t type,int16_t celsius) 
 * 功    能：摄氏度转华氏度
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
 * 函数原型：void Read_Temp(float dT)
 * 功    能：读取温度-10ms
*****************************************************************
*/
void Read_Temp(float dT)
{
	static float T;
	
	T += dT;
    
    AD1 = Filter_ADC(2);
    REF_V = Filter_ADC(1);
    V1 = (REF_V / 4096) * 3.3f;
    PT10 = Filter_ADC(0);
    PT_VALUE_1_TEMP = Filter_ADC_EMA(PT10);//计算阻值
	if(T >= 1.0f)
	{    
        Temp.Mesa = Wolfram_Inverse(PT_VALUE_1_TEMP);//台面温度
		Temp.Rel = Temp.Mesa;//真实温度显示台面温度
		T = 0;
	}
}
