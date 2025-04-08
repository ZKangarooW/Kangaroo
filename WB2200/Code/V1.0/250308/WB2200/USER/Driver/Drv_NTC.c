#include "Drv_NTC.h"

#define ALPHA 0.1f  // 平滑因子，调整响应速度
#define R_REF 100000.0f  // 参考电阻 5.1kΩ
#define V_IN 3.3f  // 电源电压

#define AD_LEN 1//DMA获取长度
uint16_t ADC_Val2[AD_LEN];//adc的值 0:ad值;
float EMA_value = 0;
uint16_t ADC_val1;
float V_out;
float R_NTC;
float Te = 0;
float Filter_ADC_EMA(void)
{   
    ADC_val1 = ADC_Val2[0];//将adc的值储存

    // 检查 ADC 值范围
    if (ADC_val1 <= 0 || ADC_val1 >= 4095) {
        return EMA_value; // 返回当前 EMA 值，不更新
    }

    // 将 ADC 值转换为电压
    V_out = (ADC_val1 / 4095.0f) * V_IN;

    // 检查分母是否接近 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) {
        return EMA_value; // 返回当前 EMA 值，不更新
    }

    // 计算 NTC 电阻值
    R_NTC = R_REF * ((V_IN / V_out) - 1);

    // 更新 EMA 滤波值
    EMA_value = ALPHA * R_NTC + ((1 - ALPHA) * EMA_value);
    
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

float temperature_K;
float temperature_C1;   
float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
{
    float logR = log(R_NTC); // 计算 R 的对数
    temperature_K = 1.0 / (A + B * logR + C * logR * logR * logR); // 开尔文温度
    temperature_C1 = temperature_K - 273.15 + Te; // 转换为摄氏度
    return temperature_C1*10;
}

float resistance1;
void Read_Temp(float dT)
{
    static float T;
    T += dT;

    resistance1 = Filter_ADC_EMA(); // 获取电阻值（已经经过EMA滤波）

    if (T >= 1.0f) // 1S
    {
        Temp.Rel = Get_Ntc_Temp_Steinhart_Hart(resistance1); // 计算温度
        T = 0;
    }
}

void Temp_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim15);//开启TIM3的定时，用于刷新
	HAL_ADC_Start_DMA(&hadc,(uint32_t *)ADC_Val2, AD_LEN);//用DMA获取adc值
	HAL_ADCEx_Calibration_Start(&hadc);
    for (uint8_t i = 0; i <= 100; i++)
    {
        resistance1 = Filter_ADC_EMA(); // 获取滤波后的电阻值
        if (i == 100) // 1S
        {
            Temp.Rel = Get_Ntc_Temp_Steinhart_Hart(resistance1); // 计算温度
        }
        HAL_Delay(10); // 延时
    }
    Temp.Display_Rel = Temp.Rel;//加了后开机不会显示0然后调成实际温度
    HAL_Delay(10); // 延时
}
