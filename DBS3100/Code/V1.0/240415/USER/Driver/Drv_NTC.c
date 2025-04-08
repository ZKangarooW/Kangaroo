#include "Drv_NTC.h"

/**********全局变量**********/
#define AD_LEN 2          // DMA获取长度
uint16_t ADC_Val[AD_LEN]; // adc的值 0:内部探头。 1：热盖的探头
uint16_t ADC_Val1, ADC_Val2;
#define N 50         // 采集N次
int ADCvalue_Buf[N]; // 用于储存采集到的adc值
int i = 0;
int ADCvalue_Buf1[N]; // 用于储存采集到的adc值
int j = 0;

/**
 * @brief 滑动平均值滤波
 *
 * @return int 滤波后的值
 */
int Filter_ADC(void)
{
    uint8_t count;
    long sum = 0;

    ADCvalue_Buf[i++] = ADC_Val[0]; // 将adc的值储存

    if (i == N) // 加入读了N组就从新开始
    {
        i = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf[count]; // N组相加
    }
    if (ADCvalue_Buf[N - 1] == 0) // 如果没有读到100组就用第一次读到的数
        return ADCvalue_Buf[0];
    else                       // 读到N组后
        return (int)(sum / N); // 输出平均值
}

/**
 * @brief 滑动平均值滤波
 *
 * @return int 滤波后的值
 */
int Filter_ADC1(void)
{
    uint8_t count;
    long sum = 0;

    ADCvalue_Buf1[j++] = ADC_Val[1]; // 将adc的值储存

    if (j == N) // 加入读了N组就从新开始
    {
        j = 0;
    }
    for (count = 0; count < N; count++)
    {
        sum += ADCvalue_Buf1[count]; // N组相加
    }
    if (ADCvalue_Buf1[N - 1] == 0) // 如果没有读到100组就用第一次读到的数
        return ADCvalue_Buf1[0];
    else                       // 读到N组后
        return (int)(sum / N); // 输出平均值
}

/**
 * @brief ADC和DMA的初始化
 *
 */
void ADCDMA_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim15);                        // 开启TIM3的定时，用于刷新
    HAL_ADC_Start_DMA(&hadc, (uint32_t *)ADC_Val, AD_LEN); // 用DMA获取adc值
    HAL_ADCEx_Calibration_Start(&hadc);
}

float BX = 3950.0f;//即查询规格书找到的材料参数B
float T25 = (273.15+25.0);//T25=250.0+273.15//如果是25就只能算出整数，250的个位是小数
float R25 = 100.0f;//25摄氏度下对应的NTC电阻值为100千欧，注意此处单位为千欧，因此传入的Rntc单位也要一致为千欧
float N1,N2,N3,N4;
float Get_Temperature(float Rntc)
{
    N1 = (log(Rntc/R25))/BX;
//    N1 = (log(Rntc)-log(R25))/BX;
	N2 = 1/T25 + N1;
	N3 = 1/N2;
	N4 = (N3-273.15);
	return N4;//计算出的实际温度
}


// 根据已知温度点和对应的传感器输出值，计算当前温度对应的传感器输出值
float calibrate(float temperature) {
    
    float x1, y1, x2, y2, a, b, y;
    
    x1 = 30;
    y1 = 32.4;
    
    x2 = 70;
    y2 = 77.2;
    a = (y2 - y1) / (x2 - x1);
    b = y1 - a * x1;
    
    y = a * temperature + b;
    
    return y;
}


/**
 * @brief 读取温度
 *
 * @param dT 任务周期
 */
float Vr,adz;
float ad_Temp;
void Read_Temp(float dT)
{
    static float T;
    T += dT;
    ADC_Val1 = Filter_ADC(); //滤波获取adc的滑动平均值
    ADC_Val2 = Filter_ADC1();//滤波获取adc的滑动平均值

    Vr = 3.3f/((3.3*ADC_Val1/4095)/100)-100;
    ad_Temp = Get_Temperature(Vr) * 10;
    Temp.Rel =  calibrate(ad_Temp) -10;
    
//    adz = Get_Vr(Temp.Rel/10);
    
//    if (T >= 0.2f) // 1S
//    {
//        
//        T = 0;
//    }
}
