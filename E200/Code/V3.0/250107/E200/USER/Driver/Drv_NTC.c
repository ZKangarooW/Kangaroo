#include "Drv_NTC.h"

#define ALPHA 0.1f  // 平滑因子，调整响应速度
#define R_REF 30000.0f  // 参考电阻 5.1kΩ
#define V_IN 3.3f  // 电源电压

#define AD_LEN 2//DMA获取长度
uint16_t ADC_Val[AD_LEN];//adc的值 0:ad值; 1：
float Filter_ADC_EMA(uint8_t i)
{   
    static float EMA_value[AD_LEN];
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
#define A  -7.479824086506315e-05
#define B  0.0003174825283214902
#define C  -1.6641521707421694e-07
float Get_Ntc_Temp_Steinhart_Hart(float R_NTC)
{
    float temperature_K;
    float temperature_C1;   
    float logR = log(R_NTC); // 计算 R 的对数
    temperature_K = 1.0 / (A + B * logR + C * logR * logR * logR); // 开尔文温度
    temperature_C1 = temperature_K - 273.15; // 转换为摄氏度
    return temperature_C1*10;
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
            Heat_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[0]);//计算温度
        }
        else
        {
            Heat_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[0]);//计算温度
        }
		Cool_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[1]);//计算温度
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
void Calibration(uint16_t temp,uint16_t temp1)
{
	uint16_t Cal1,Cal2;
	
    Cal1 = 400 - temp;
    Cal2 = 600 - temp1;
    Calibration_Temp = (float)(Cal1 + Cal2)/2;
    
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
            Heat_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[0]);//计算温度
            Cool_Temp.Rel_Temp = Get_Ntc_Temp_Steinhart_Hart(resistance[1]);//计算温度
        }
        HAL_Delay(10); // 延时
    }
    Heat_Temp.Display_Temp = Heat_Temp.Rel_Temp;//加了后开机不会显示0然后调成实际温度
    Cool_Temp.Display_Temp = Cool_Temp.Rel_Temp;//加了后开机不会显示0然后调成实际温度
    HAL_Delay(10); // 延时
}
