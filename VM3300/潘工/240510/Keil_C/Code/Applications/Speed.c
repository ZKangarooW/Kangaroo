#include "Speed.h"

/**********局部变量声明******/
uint16_t captureValue1, captureValue2 = 0;//采样到的值
uint16_t reloadCount = 0;//溢出的次数
uint8_t g_captureState = 0x00;//捕获标志位：bit7:捕获完成bit6:捕获状态
uint32_t g_captureValue = 0;////捕获值
float frq = 0;//周期频率值
uint16_t rel = 0;

/**
 * @brief 检测速度是否停止-0.05s
 *
 * @param dT 任务周期
 */
void Check_Speed(float dT)
{
    Speed.Stop_Cnt += dT;      // 每50ms进入
    if (Speed.Stop_Cnt >= 1.0) // 0.5s发现没出发输入捕获
    {
        Speed.Rel = 0;      // 将速度清零
        Speed.Stop_Cnt = 0; // 计数清零
    }
}

/**
 * @brief 得到采样的值
 *
 * @return 采样值
 */
uint8_t GetCaptureValue(void)
{
    unsigned long int CaptureValue = 0;
    CaptureValue = ((uint16_t)RCAPXH << 8) + RCAPXL;
    return CaptureValue ;
}

/**
 * @brief 得到采样周期
 *
 * @return 采样周期
 */
uint32_t GetCaptureCycle(unsigned long int Fsys, unsigned int Value1, unsigned int Value2,unsigned int OverCount)
{
    unsigned long int value = 0;
    value = ((65536 * OverCount) + Value2 - Value1) / Fsys;
    return value;
}

/**
 * @brief 速度捕获中断函数
 *
 */
void Speed_Capture_Interrupt(void)
{
	if(TIM3_GetFlagStatus(TIM3_FLAG_TF3))
	{
		TIM3_ClearFlag(TIM3_FLAG_TF3);
		if(g_captureState & 0X40)//溢出值
		{
			reloadCount++;
		}
            
	}
	if(TIM3_GetFlagStatus(TIM3_FLAG_EXF3))
	{       
		TIM3_ClearFlag(TIM3_FLAG_EXF3);    
		if(g_captureState & 0X40)
		{
			captureValue2 = GetCaptureValue();
			g_captureValue = GetCaptureCycle(32, captureValue1, captureValue2, reloadCount);    
			frq = 1.0 / (((float)g_captureValue) / 1000000.0);
			rel = 60 * frq/5;
			Speed.Stop_Cnt = 0;
			Speed.Rel = rel;
			TLX = 0X00;
			THX = 0X00;
			g_captureState = 0X80;
			reloadCount = 0;
		}
		else
		{
			captureValue1 = GetCaptureValue();
			g_captureState = 0X40;
			reloadCount = 0;
		}
	}
}

/**
 * @brief 检测状态
 *
 */
void Check_Status(void)
{
	if(g_captureState & 0x80)
    {
            g_captureState &= (~0x80);
    }
}
