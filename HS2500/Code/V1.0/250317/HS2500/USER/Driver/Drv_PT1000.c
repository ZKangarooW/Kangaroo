#include "Drv_PT1000.h"

#define ALPHA 0.1f  // 平滑因子，调整响应速度
#define V_IN 3.3f  // 电源电压
#define OP_Value	6.2//放大系数
#define Vref		2.494//参考电压
#define K1			0.2327367//电阻基准系数
#define AD_LEN 2//DMA获取长度
uint16_t ADC_Val[AD_LEN];//adc的值 0:台面温度ad值。 1：外部探头ad值
float EMA_value[AD_LEN];
float PT_VALUE_1_TEMP;//外部探头阻值
float PT_VALUE_2_TEMP;//台面探头阻值
float Filter_ADC_EMA(uint8_t i)
{   
    uint16_t ADC_val;
    float V_out;
    float R_NTC;
    float AD_T;
    ADC_val = ADC_Val[i];//将adc的值储存

    // 检查 ADC 值范围
    if (ADC_val <= 0 || ADC_val > 4095) {
        return EMA_value[i]; // 返回当前 EMA 值，不更新
    }

    // 将 ADC 值转换为电压
    V_out = (ADC_val / 4096.0f) * V_IN;

    // 检查分母是否接近 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) {
        return EMA_value[i]; // 返回当前 EMA 值，不更新
    }

    // 计算 NTC 电阻值
    AD_T = V_out/OP_Value/Vref+K1;//计算电压值
    R_NTC = 3000*AD_T/(1-AD_T);

    // 更新 EMA 滤波值
    EMA_value[i] = ALPHA * R_NTC + ((1 - ALPHA) * EMA_value[i]);
    
    return EMA_value[i];
}

#define R0 1000  // 参考电阻
#define A   0.003908299761668694
#define B   -5.774954439024853e-07
#define C   -6.86686242500016e-15
// Wolfram公式的逆向计算函数
double wolfram_inverse(double R_test) {
    double T_low = -5.0;  // 温度范围的下限
    double T_high = 380.0;  // 温度范围的上限
    double T_mid;

    // 使用二分法求解
    while ((T_high - T_low) > 0.0001) {  // 迭代精度
        T_mid = (T_low + T_high) / 2.0;
        double R_calculated = R0 * (1 + A * T_mid + B * T_mid * T_mid + C * T_mid * T_mid * T_mid);

        if (R_calculated > R_test) {
            T_high = T_mid;
        } else {
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
            PT_VALUE_1_TEMP = Filter_ADC_EMA(1);//计算阻值
            PT_VALUE_2_TEMP = Filter_ADC_EMA(0);//计算阻值
            Read_Temp(0.1f);
        }
    }
}

/*
*****************************************************************
 * 函数原型：float celsiusToFahrenheit(uint8_t type,int16_t celsius) 
 * 功    能：摄氏度转华氏度
*****************************************************************
*/
float celsiusToFahrenheit(uint8_t type,int16_t celsius) 
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
    PT_VALUE_1_TEMP = Filter_ADC_EMA(1)*1.003;//计算阻值
    PT_VALUE_2_TEMP = Filter_ADC_EMA(0)*1.003;//计算阻值

	if(T >= 1.0f)
	{    
        Temp.Outside = wolfram_inverse(PT_VALUE_1_TEMP);//外部温度
        Temp.Mesa = wolfram_inverse(PT_VALUE_2_TEMP);//台面温度
        if(PT_VALUE_1_TEMP < 2400)//假如插入外部探头
            Temp.Rel = Temp.Outside;//真实温度显示外部探头测的温度
		else//假如没有插入外部探头
			Temp.Rel = Temp.Mesa;//真实温度显示台面温度
		T = 0;
	}
}
