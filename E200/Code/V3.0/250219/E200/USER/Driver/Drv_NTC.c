#include "Drv_NTC.h"

#define ALPHA 0.1f  // 平滑因子，调整响应速度
#define R_REF 30000.0f  // 参考电阻 5.1kΩ
#define V_IN 3.3f  // 电源电压

#define AD_LEN 2//DMA获取长度
uint16_t ADC_Val[AD_LEN];//adc的值 0:ad值; 1：
float EMA_value[AD_LEN];
float Filter_ADC_EMA(uint8_t i)
{   
    uint16_t ADC_val;
    float V_out;
    float R_NTC;
    ADC_val = ADC_Val[i];//将adc的值储存

    // 检查 ADC 值范围
    if (ADC_val <= 0 || ADC_val >= 4095) {
        
        return EMA_value[i]; // 返回当前 EMA 值，不更新
    }

    // 将 ADC 值转换为电压
    V_out = (ADC_val / 4095.0f) * V_IN;

    // 检查分母是否接近 0
    if (fabs(V_out) < 0.0001f || fabs(V_IN - V_out) < 0.0001f) {
        return EMA_value[i]; // 返回当前 EMA 值，不更新
    }

    // 计算 NTC 电阻值
    R_NTC = R_REF * ((V_IN / V_out) - 1);

    // 更新 EMA 滤波值
    EMA_value[i] = ALPHA * R_NTC + ((1 - ALPHA) * EMA_value[i]);
    
    return EMA_value[i];
}

/******************100K***************/
//#define A  0.0006834379508081105
//#define B  0.00021991049145573158
//#define C  9.074100194441566e-08
/** 校准 **/
#define A   0.0007591600777748435
#define B  0.0002076905133879821
#define C   1.1750230209075526e-07
float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
{
    float temperature_K;
    float temperature_C1;   
    float logR = log(R_NTC); // 计算 R 的对数
    temperature_K = 1.0 / (A + B * logR + C * logR * logR * logR); // 开尔文温度
    temperature_C1 = temperature_K - 273.15; // 转换为摄氏度
    return temperature_C1*10;
}

// 从温度(℃)计算NTC电阻值(Ω)
float Calculate_NTC_Resistance(float temperature_C) {
    float T = temperature_C + 273.15f; // 转换为开尔文温度
    float x = (A - 1.0f/T) / C;       // 中间变量
    float y = sqrt(pow(B/(3.0f*C), 3) + pow(x/2.0f, 2));
    float lnR = cbrt(y - x/2.0f) - cbrt(y + x/2.0f);
    float R = exp(lnR);
    
    return R;
}

float resistance[AD_LEN];
void Read_Temp(float dT)
{
    static float T;
    T += dT;

    resistance[0] = Filter_ADC_EMA(0); // 获取电阻值（已经经过EMA滤波）
    resistance[1] = Filter_ADC_EMA(1); // 获取电阻值（已经经过EMA滤波）
    
    if (T >= 1.0f) // 1S
    {
        if(sys.Calibration)
		{
            Cool_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[1]);//计算温度
        }
        else
        {
            Cool_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[1])*Calibration_Temp;//计算温度
        }
		Heat_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[0])*Calibration_Temp;//计算温度
        T = 0;
    }
}

/*
*****************************************************************
 * 函数原型：void Calibration(uint16_t temp,uint16_t temp1)
 * 功    能：温度校准计算
 * 输    入：temp：40的温度，temp1：60的温度
 * 参    数：uint16_t temp,uint16_t temp1
*****************************************************************
*/
float Calibration_Temp;
float calibration_factor[AD_LEN] = {1.0f, 1.0f}; // 校准系数数组
float Cal1,Cal2;
float Cal3,Cal4;
float Cal5,Cal6;
void Calibration(uint16_t temp,uint16_t temp1)
{
	Cal5 = (float)temp/10;
	Cal6 = (float)temp1/10;
	
    Cal1 = Calculate_NTC_Resistance(Cal5);
    Cal2 = Calculate_NTC_Resistance(Cal6);
	
	Cal3 = Calculate_NTC_Resistance(26.0f);
    Cal4 = Calculate_NTC_Resistance(40.0f);
	
	// 计算校准系数
    calibration_factor[0] = Cal3 / Cal1;
    calibration_factor[1] = Cal4 / Cal2;
	
    Calibration_Temp = (calibration_factor[0] + calibration_factor[1]) / 2.0f;
	
	Param.Calibration_Temp = Calibration_Temp;//温度校准系数
	Save_Param_En = 1;//保存
}

void ADCDMA_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim3);//开启TIM3的定时，用于刷新
	HAL_ADC_Start_DMA(&hadc,(uint32_t *)ADC_Val, AD_LEN);//用DMA获取adc值
	HAL_ADCEx_Calibration_Start(&hadc);
    for (uint8_t i = 0; i <= 100; i++)
    {
        resistance[0] = Filter_ADC_EMA(0); // 获取电阻值（已经经过EMA滤波）
        resistance[1] = Filter_ADC_EMA(1); // 获取电阻值（已经经过EMA滤波）
        if (i == 100) // 1S
        {
            Heat_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[0])*Calibration_Temp;//计算温度
            Cool_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[1])*Calibration_Temp;//计算温度
        }
        HAL_Delay(10); // 延时
    }
    Heat_Temp.Display_Temp = Heat_Temp.Rel_Temp;//加了后开机不会显示0然后调成实际温度
    Cool_Temp.Display_Temp = Cool_Temp.Rel_Temp;//加了后开机不会显示0然后调成实际温度
    HAL_Delay(10); // 延时
}
