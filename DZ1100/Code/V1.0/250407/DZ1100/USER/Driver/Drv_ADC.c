#include "Drv_ADC.h"

/**********局部变量**********/
uint16_t ADC_Val[AD_LEN];//ADC的值
uint16_t F_ADC;//滤波后的ADC值
float ADC_V;//ADC得到的电压
float Power_V;//电池电压
//float ADC_ASD[4];

/*
*****************************************************************
 * 函数原型：void Drv_ADC_Init(void)
 * 功    能：ADC驱动初始化
*****************************************************************
*/
void Drv_ADC_Init(void)
{
    //设置ADC的运行模式
	ADC_ConfigRunMode(ADC_CLK_DIV_128, ADC_RESULT_LEFT);	//设置ADC时钟为系统时钟的128分频，ADC结果为左对齐，如有对ADC时钟有操作请参考"中微8051芯片ADC模块应用笔记"
	
	//设置ADC转换通道
	ADC_EnableChannel(ADC_CH_16);	
	GPIO_SET_MUX_MODE(P20CFG, GPIO_P20_MUX_AN16);	
	
	//设置ADC LDO
	ADC_EnableLDO();
	ADC_ConfigADCVref(ADC_VREF_3V);		//ADC_VREF_1P2V, ADC_VREF_2V, ADC_VREF_2P4V, ADC_VREF_3V	
	
	//设置ADC中断
	ADC_EnableInt();
	IRQ_SET_PRIORITY(IRQ_ADC,IRQ_PRIORITY_HIGH);	
	IRQ_ALL_ENABLE();
}

/*
*****************************************************************
 * 函数原型：int Filter_ADC(uint8_t i)
 * 功    能：滑动滤波
 * 输    入：ADC通道
 * 输    出：滤波后的电阻值
 * 参    数：uint8_t i
 * 调    用：内部调用 
*****************************************************************
*/
int Filter_ADC(uint8_t i)
{
    static int ADCvalue_Buf[AD_LEN][N];//用于储存采集到的adc值
    static int j[AD_LEN];//用于计数
    
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
 * 函数原型：void Get_ADC_Value(float dT)
 * 功    能：获取ADC的值
*****************************************************************
*/
void Get_ADC_Value(float dT)
{
    /*温度采样*/	
	ADC_Start();
	ADC_GO();
	while(ADC_IS_BUSY);
	ADC_Val[0] =  ADC_GetADCResult();   
	ADC_Stop();	
    
    F_ADC = Filter_ADC(0);
    ADC_V = (float)(F_ADC)/4096*V_IN;
    Power_V = ADC_V/0.3333f;//这里1和3都是M欧姆。因为单位相同
//    ADC_ASD[0] = ADC_Val[0];
//    ADC_ASD[1] = F_ADC;
//    ADC_ASD[2] = ADC_V;
//    ADC_ASD[3] = Power_V;
}

/*
*****************************************************************
 * 函数原型：void Check_Power(float dT)
 * 功    能：检测电池点亮并报警
*****************************************************************
*/
void Check_Power(float dT)
{
    if(sys.Run_Status)
    {
        if(Power_V < 6.8f)
        {
            LED1_ON;
        }
        else
        {
            LED1_OFF;
        }
    }
    else
    {
        if(Power_V < 7.0f)
        {
            LED1_ON;
        }
        else
        {
            LED1_OFF;
        }
    }
}
