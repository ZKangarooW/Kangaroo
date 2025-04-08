#include "Drv_WS2812.h"

/**********结构体************/
_WS2812_RGB_ WS2812[1];
_WS2812_ WS2812_Status[1];

/**********局部变量声明******/
uint16_t WS2812_Buf1[RESET_WORD+RGB_NUM1 * 24+DUMMY_WORD]; // 存放的数组
uint16_t Memaddr = 0;					// 数组的地址值

/**
 * @brief 更新目前灯的状态
 *
 */
void WS2812_Update(void)
{
	if (WS2812_Status[0].Update)
	{
		HAL_TIM_PWM_Start_DMA(WS2812[0].Tim, WS2812[0].CHANNEL,(uint32_t *)&WS2812_Buf1[0], RESET_WORD+RGB_NUM1 * 24+DUMMY_WORD); // 开始传输字节数据
	
		WS2812_Status[0].Sending = 1; // 发送
		WS2812_Status[0].Update = 0;  // 更新完成，标志位清零
	}
}

/**
 * @brief 设置第几个灯的颜色
 *
 * @param num 要设置的第几个灯
 * @param r 红色的色值
 * @param g 绿色的色值
 * @param b 蓝色的色值
 */
void WS2812_SetColor(uint8_t num, uint8_t r, uint8_t g, uint8_t b,float light)
{
	uint8_t cnt = 0;

	WS2812_Status[0].Number = num; // 灯的序号

	WS2812[0].Red_Out = WS2812[0].Red = r; // 颜色赋值
	WS2812[0].Green_Out = WS2812[0].Green = g;
	WS2812[0].Blue_Out = WS2812[0].Blue = b;

	WS2812[0].Red_Out = (WS2812[0].Red_Out + 1) / 16 * light * 10;		// 乘等于最大亮度值
	WS2812[0].Green_Out = (WS2812[0].Green_Out + 1) / 16 * light * 10; // 乘等于最大亮度值
	WS2812[0].Blue_Out = (WS2812[0].Blue_Out + 1) / 16 * light * 10;	// 乘等于最大亮度值

	if (WS2812_Status[0].Number == 0xFF) // 同时改变所有灯的颜色
	{
		Memaddr = 0;		  // 从头赋值
		while (cnt < RGB_NUM1) // 一个一个发
		{
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf1[Memaddr++] = ((WS2812[0].Green_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO; // 将设定值拆分放入数组中
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf1[Memaddr++] = ((WS2812[0].Red_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf1[Memaddr++] = ((WS2812[0].Blue_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
			cnt++;
		}
	}
	else if (WS2812_Status[0].Number <= RGB_NUM1) // 只改变指定序号灯的颜色，看RGB_NUM的值
	{
		Memaddr = WS2812_Status[0].Number * 24;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf1[Memaddr++] = ((WS2812[0].Green_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf1[Memaddr++] = ((WS2812[0].Red_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf1[Memaddr++] = ((WS2812[0].Blue_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
	}

	WS2812_Status[0].Update = 1; // 更新显示
}

/**
 * @brief PWM信号传输完成回调函数，该函数非常之重要
 *
 * @param htim
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
        {
            WS2812_Status[0].Sending = 0;							  // 发送完成，标志位清零
//			HAL_TIM_PWM_Stop_DMA(WS2812[0].Tim, WS2812[0].CHANNEL);	  // 关闭DMA传输
        }
    }
	
}

/**
 * @brief WS2812初始化
 *
 */
void WS2812_Init(void)
{
	WS2812[0].Tim = &WS2812_Tim;		// 定时器选择
	WS2812[0].CHANNEL = TIM_CHANNEL_2; // 定时器通道数
    HAL_TIMEx_PWMN_Start(WS2812[0].Tim, WS2812[0].CHANNEL); // 开启tim5通道四 26值起来
    WS2812_SetColor(0xFF, 0x00, 0x00, 0x00, 1.0f);
}


/**
 * @brief WS2812显示任务
 *
 * @param dT 任务周期
 */
void WS2812_Duty(float dT)
{
//    if(Work_Num[0].Run_Status != 1 && Work_Num[1].Run_Status != 1 
//       && Work_Num[2].Run_Status != 1 && Work_Num[3].Run_Status != 1
//        )//系统没启动的话
//    {
//            WS2812_SetColor(0x0C, 0x00, 0x00, 0x00, 0);
//    }
//    else
//    {
//        WS2812_SetColor(0x0C, 0xFF, 0xFF, 0xFF, 1.0f);//Start
//    }
//    
//    if (Lock_Switch)
//    {
//        WS2812_SetColor(0x0D, 0xFF, 0xFF, 0xFF, 1.0f);//锁定按键
//    }
//    else
//    {
//        WS2812_SetColor(0x0D, 0x00, 0x00, 0x00, 1.0f);//锁定按键
//    }
//    
//    if(sys.Sync)
//    {
//        WS2812_SetColor(0x0E, 0xFF, 0xFF, 0xFF, 1.0f);//Sync
//    }
//    else
//    {
//        WS2812_SetColor(0x0E, 0x00, 0x00, 0x00, 1.0f);//Sync
//    }
//    
	if (!WS2812_Status[0].Sending)
		WS2812_Update();
}
