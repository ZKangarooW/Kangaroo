#include "Drv_Infrared.h"

/**********结构体************/
_Infrared_ Infrared[2];

/**
 * @brief 红外驱动初始化
 *
 */
void Drv_Infrared_Init(void)
{
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道一 PA6左手边
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道二 PA7右手边
	
    
    HAL_TIM_Base_Start_IT(&htim15);
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);//开启tim15通道1的捕获（中断方式）PA2右手边
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_2);//开启tim15通道2的捕获（中断方式）PA3左手边
    HAL_TIM_Base_Start_IT(&htim1);//开启溢出中断
    Infrared[0].Distance = 10000;// 将红外置为10000
    Infrared[1].Distance = 10000;// 将红外置为10000
}

/**
 * @brief 定时器更新（溢出）中断回调函数
 *
 */
void Infrared_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM15)
    {
        Infrared[0].Cnt++;
        Infrared[1].Cnt++;
    }
}

///*
//*****************************************************************
// * 函数原型：int Filter_ADC(void)
// * 功    能：滑动平均值滤波
// * 输    出：滤波后的值
//*****************************************************************
//*/
//#define I 10//采集10次
//int InfraredValue_Buf[2][I];//用于储存采集到的Speed值
//int j[2];//计数值
//int Filter_Infrared(uint8_t new_work,uint16_t infrared)
//{
//    char count;
//    long sum = 0;

//    InfraredValue_Buf[new_work][j[new_work]++] = infrared;
//	
//    if(j[new_work] == I)//假如读了100组就从新开始
//    {
//        j[new_work] = 0;
//    }
//    for(count = 0; count < I; count++)
//    {
//        sum += InfraredValue_Buf[new_work][count];//100组相加
//    }
////    if(InfraredValue_Buf[new_work][I-1] == 0)//如果没有读到100组就用第一次读到的数
//        return InfraredValue_Buf[new_work][I-1];
////    else//读到100组后
////        return (int)(sum / I);//输出平均值
//}

/**
 * @brief 红外检测信号变化定时器捕获
 *
 */
uint16_t Infrared_F[2];
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM15)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
            if(Infrared[0].Edge == 0)//如果捕获到上升沿
            {
                Infrared[0].t1 = HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_1);
                
                //设置为下降沿捕获
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);
                
                Infrared[0].Cnt = 0;//计数器清零
                
                Infrared[0].Edge = 1;//采集下降沿
            }
            else if(Infrared[0].Edge == 1)
            {
                Infrared[0].t2 = HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_1);
                
                Infrared[0].t2 += Infrared[0].Cnt * 65535;
                
                Infrared[0].T = Infrared[0].t2 - Infrared[0].t1;
                
                //设置为上升沿沿捕获
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);
                
                Infrared[0].Distance = Infrared[0].T * 0.000001 * 300000; 
                
                if(Infrared[0].Distance>10000)
                {
                    Infrared[0].Distance = 10000;
                }
                
                Infrared[0].SSI_CNT ++; // 计数清零
                
                Infrared[0].Edge = 0;//采集上升沿
            }	 		     	    
		}
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
            if(Infrared[1].Edge == 0)//如果捕获到上升沿
            {
                Infrared[1].t1 = HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_2);
                
                //设置为下降沿捕获
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_INPUTCHANNELPOLARITY_FALLING);
                
                Infrared[1].Cnt = 0;//计数器清零
                
                Infrared[1].Edge = 1;//采集下降沿
            }
            else if(Infrared[1].Edge == 1)
            {
                Infrared[1].t2 = HAL_TIM_ReadCapturedValue(&htim15,TIM_CHANNEL_2);
                
                Infrared[1].t2 += Infrared[1].Cnt * 65535;
                
                Infrared[1].T = Infrared[1].t2 - Infrared[1].t1;
                
                //设置为上升沿沿捕获
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15,TIM_CHANNEL_2,TIM_INPUTCHANNELPOLARITY_RISING);
                
                Infrared[1].Distance = Infrared[1].T * 0.000001 * 300000; 
                
                if(Infrared[1].Distance>10000)
                {
                    Infrared[1].Distance = 10000;
                }
                
                Infrared[1].SSI_CNT ++; // 计数清零
                Infrared[1].Edge = 0;//采集上升沿
            }  	    
		}
	}
}

/**
 * @brief 结束码(自己加的)
 * 
 * @param val 0：通道二 1:通道一
 */
static void NEC_Send_Tail(uint8_t val)
{
	CARRIER_38KHz(val);
	Delay_us(200);
	NO_CARRIER(val);
	Delay_us(3000);//2.5<3ms<3.3ms
 
}

/**
 * @brief 后发送16位地址码（18ms36ms）、8位数据码（9ms18ms）以及8为数据反码
 * 
 * @param val 0：通道二 1:通道一
 * @param addr 发送的地址
 * @param value 数据
 * @param cnt 次数 
 */
void NEC_Send(uint8_t val)
{
	NEC_Send_Tail(val);//发送重复码 
}

/**
 * @brief 检测红外
 * 
 * @param dT 任务周期
 */
void Check_Infrared(float dT)
{
    static float T;
    static float T1;
    if(sys.Run_Status)
        return;
    if(Infrared[0].Someone==0)
    {
        if(Infrared[0].SSI>6)
        {
            T += dT;
            if(T >= 0.2f)
            {
                Infrared[0].Someone = 1;
                if(Infrared[1].Someone == 0)
                    Beep_Time = 0.1f;
                T=0;
            }
        }
        else 
        {
            T = 0;
        }
    }
    else
    {
        T += dT;
        if(Infrared[0].SSI>6)
        {
            T = 0;
        }
        if(T >= 3.0f)
        { 
            Infrared[0].Someone = 0;
            if(Infrared[1].Someone == 0)
                Beep_Flash = 2;
            T = 0;
        }
    }
 
    if(Infrared[1].Someone==0)
    {
        if(Infrared[1].SSI>6)
        {
            T1 += dT;
            if(T1 >= 0.2f)
            {
                Infrared[1].Someone = 1;
                if(Infrared[0].Someone == 0)
                    Beep_Time = 0.1f;
                T1=0;
            }
        }
        else 
        {
            T1 = 0;
        }
    }
    else
    {
        T1 += dT;
        if(Infrared[1].SSI>6)
        {
            T1 = 0;
        }
        if(T1 >= 3.0f)
        { 
            Infrared[1].Someone = 0;
            if(Infrared[0].Someone == 0)
                Beep_Flash = 2;
            T1 = 0;
        }
    }
}

/**
 * @brief 检测红外是否有接收
 *
 * @param dT 任务周期
 */
void Check_Infrared_Rec(float dT)
{
    static float T,T1;
    
    T += dT;
    T1 += dT;
   
    if (T >= 0.2) // 0.5s发现没出发输入捕获
    {
        Infrared[0].SSI = Infrared[0].SSI_CNT;
        Infrared[0].SSI_CNT = 0; // 计数清零
    }
    if (T1 >= 0.2) // 0.5s发现没出发输入捕获
    {
        Infrared[1].SSI = Infrared[1].SSI_CNT;
        Infrared[1].SSI_CNT = 0; // 计数清零
    }
}
