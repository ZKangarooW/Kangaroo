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

/**
 * @brief 红外检测信号变化定时器捕获
 *
 */
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
                Infrared[0].SSI_CNT = 0; // 计数清零
                
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
                Infrared[1].SSI_CNT = 0; // 计数清零
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
    
    if(Infrared[0].Distance > 1500&&Infrared[0].Distance<3000)
    {
        Infrared[0].Someone = 1;
    }
    
    if(Infrared[0].Someone == 1)
    {
        T += dT;
        if(Infrared[0].Distance > 1500&&Infrared[0].Distance<3000)
        {
            T = 0;
        }
        if(T >= 3.0f)
        { 
            Infrared[0].Someone = 0;
            T = 0;
        }
    }
 
    if(Infrared[1].Distance > 1500&&Infrared[1].Distance<3000)
    {
        Infrared[1].Someone = 1;
    }
    
    if(Infrared[1].Someone == 1)
    {
        T1 += dT;
        if(Infrared[1].Distance > 1500&&Infrared[1].Distance<3000)
        {
            T1 = 0;
        }
        if(T1 >= 3.0f)
        { 
            Infrared[1].Someone = 0;
            T1 = 0;
        }
    }
//    if(Infrared[0].Someone==0 && Infrared[1].Someone==0)
//    {
//        Speed.ADDMode = 2;
//    }
}

/**
 * @brief 检测红外是否有接收
 *
 * @param dT 任务周期
 */
void Check_Infrared_Rec(float dT)
{
    Infrared[0].SSI_CNT += dT;// 每50ms进入
    Infrared[1].SSI_CNT += dT;// 每50ms进入
    if (Infrared[0].SSI_CNT >= 1.0) // 0.5s发现没出发输入捕获
    {
        Infrared[0].Distance = 10000;// 将红外置为10000
        Infrared[0].SSI_CNT = 0; // 计数清零
    }
    if (Infrared[1].SSI_CNT >= 1.0) // 0.5s发现没出发输入捕获
    {
        Infrared[1].Distance = 10000;// 将红外置为10000
        Infrared[1].SSI_CNT = 0; // 计数清零
    }
}
