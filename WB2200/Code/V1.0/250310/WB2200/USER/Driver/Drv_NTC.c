#include "Drv_NTC.h"

/**********局部变量声明******/
uint16_t ADC_Val[AD_LEN];//adc的值 0:ad值;

/*
*****************************************************************
 * 函数原型：float Filter_ADC_EMA(void)
 * 功    能：EMA滤波
 * 输    出：滤波后的电阻值
 * 调    用：内部调用 
*****************************************************************
*/
static float Filter_ADC_EMA(void)
{   
    uint16_t ADC_value;//ADC值
    float EMA_value = 0;//EMA滤波后的值
    float R_value;//电阻值
    float V_out;//电压值
    ADC_value = ADC_Val[0];//将adc的值储存

    // 检查 ADC 值范围
    if (ADC_value <= 0 || ADC_value >= 4095) 
    {
        return EMA_value; // 返回当前 EMA 值，不更新
    }

    // 将 ADC 值转换为电压
    V_out = (ADC_value / 4095.0f) * V_IN;

    // 检查分母是否接近 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) 
    {
        return EMA_value; // 返回当前 EMA 值，不更新
    }

    // 计算 NTC 电阻值
    R_value = R_REF * ((V_IN / V_out) - 1);

    // 更新 EMA 滤波值
    EMA_value = ALPHA * R_value + ((1 - ALPHA) * EMA_value);
    
    return EMA_value;
}

/******************100K***************/
//#define A  0.0006834379508081105
//#define B  0.00021991049145573158
//#define C  9.074100194441566e-08
/** 校准 **/
#define A  -7.479824086506315e-05
#define B  0.0003174825283214902
#define C  -1.6641521707421694e-07

/*
*****************************************************************
 * 函数原型：float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
 * 功    能：Steinhart_Hart算法计算温度
 * 输    入：电阻值
 * 输    出：温度
 * 参    数：float R_NTC
 * 调    用：内部调用 
*****************************************************************
*/
static float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
{
    float temperature_K;
    float temperature_C;
    float logR = log(R_NTC);// 计算 R 的对数
    temperature_K = 1.0 / (A + B * logR + C * logR * logR * logR); // 开尔文温度
    temperature_C = temperature_K - 273.15; // 转换为摄氏度
    return temperature_C*10;
}

/*
*****************************************************************
 * 函数原型：void Read_Temp(float dT)
 * 功    能：读取温度
 * 输    入：任务周期
 * 参    数：float dT
*****************************************************************
*/
void Read_Temp(float dT)
{
    static float T;
    float Resistance1;
    T += dT;

    Resistance1 = Filter_ADC_EMA(); // 获取电阻值（已经经过EMA滤波）

    if (T >= 1.0f) // 1S
    {
        Temp.Rel = Get_Ntc_Temp_Steinhart_Hart(Resistance1); // 计算温度
        T = 0;
    }
}

/*
*****************************************************************
 * 函数原型：void Temp_Init(void)
 * 功    能：温度初始化
*****************************************************************
*/
void Temp_Init(void)
{
    float Resistance1;
    HAL_TIM_Base_Start_IT(&htim15);//开启TIM3的定时，用于刷新
	HAL_ADC_Start_DMA(&hadc,(uint32_t *)ADC_Val, AD_LEN);//用DMA获取adc值
	HAL_ADCEx_Calibration_Start(&hadc);
    for (uint8_t i = 0; i <= 100; i++)
    {
        Resistance1 = Filter_ADC_EMA(); // 获取滤波后的电阻值
        if (i == 100) // 1S
        {
            Temp.Rel = Get_Ntc_Temp_Steinhart_Hart(Resistance1); // 计算温度
        }
        HAL_Delay(10); // 延时
    }
    Temp.Display_Rel = Temp.Rel;//加了后开机不会显示0然后调成实际温度
    HAL_Delay(10); // 延时
}
