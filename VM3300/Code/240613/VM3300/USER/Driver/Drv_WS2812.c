#include "Drv_WS2812.h"

/**********结构体************/
_WS2812_RGB_ WS2812[2];
_WS2812_ WS2812_Status[2];

/**********局部变量声明******/
uint16_t WS2812_Buf1[RESET_WORD+RGB_NUM1 * 24+DUMMY_WORD]; // 存放的数组
uint16_t WS2812_Buf2[RESET_WORD+RGB_NUM2 * 24+DUMMY_WORD]; // 存放的数组

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
	
	if (WS2812_Status[1].Update)
	{
		HAL_TIM_PWM_Start_DMA(WS2812[1].Tim, WS2812[1].CHANNEL,(uint32_t *)&WS2812_Buf2[0], RESET_WORD+RGB_NUM2 * 24+DUMMY_WORD); // 开始传输字节数据
	
		WS2812_Status[1].Sending = 1; // 发送
		WS2812_Status[1].Update = 0;  // 更新完成，标志位清零
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
 * @brief 设置第几个灯的颜色
 *
 * @param num 要设置的第几个灯
 * @param r 红色的色值
 * @param g 绿色的色值
 * @param b 蓝色的色值
 */
void WS28121_SetColor(uint8_t num, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t cnt = 0;

	WS2812_Status[1].Number = num; // 灯的序号

	WS2812[1].Red_Out = WS2812[1].Red = r; // 颜色赋值
	WS2812[1].Green_Out = WS2812[1].Green = g;
	WS2812[1].Blue_Out = WS2812[1].Blue = b;

	WS2812[1].Red_Out = (WS2812[1].Red_Out + 1) / 16 * MAX_RATE * 10;		// 乘等于最大亮度值
	WS2812[1].Green_Out = (WS2812[1].Green_Out + 1) / 16 * MAX_RATE * 10; // 乘等于最大亮度值
	WS2812[1].Blue_Out = (WS2812[1].Blue_Out + 1) / 16 * MAX_RATE * 10;	// 乘等于最大亮度值

	if (WS2812_Status[1].Number == 0xFF) // 同时改变所有灯的颜色
	{
		Memaddr = 0;		  // 从头赋值
		while (cnt < RGB_NUM2) // 一个一个发
		{
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf2[Memaddr++] = ((WS2812[1].Green_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO; // 将设定值拆分放入数组中
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf2[Memaddr++] = ((WS2812[1].Red_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf2[Memaddr++] = ((WS2812[1].Blue_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
			cnt++;
		}
	}
	else if (WS2812_Status[1].Number <= RGB_NUM2) // 只改变指定序号灯的颜色，看RGB_NUM的值
	{
		Memaddr = WS2812_Status[1].Number * 24;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf2[Memaddr++] = ((WS2812[1].Green_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf2[Memaddr++] = ((WS2812[1].Red_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf2[Memaddr++] = ((WS2812[1].Blue_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
	}

	WS2812_Status[1].Update = 1; // 更新显示
}

/**
 * @brief PWM信号传输完成回调函数，该函数非常之重要
 *
 * @param htim
 */
void WS2812B_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
        {
            WS2812_Status[0].Sending = 0;							  // 发送完成，标志位清零
			HAL_TIM_PWM_Stop_DMA(WS2812[0].Tim, WS2812[0].CHANNEL);	  // 关闭DMA传输
        }
		
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
            WS2812_Status[1].Sending = 0;							  // 发送完成，标志位清零
			HAL_TIM_PWM_Stop_DMA(WS2812[1].Tim, WS2812[1].CHANNEL);	  // 关闭DMA传输
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
	WS2812[0].CHANNEL = TIM_CHANNEL_4; // 定时器通道数
	WS2812[1].Tim = &WS2812_Tim;		// 定时器选择
	WS2812[1].CHANNEL = TIM_CHANNEL_1; // 定时器通道数
    WS2812_SetColor(0xFF, 0x00, 0x00, 0x00, 1.0f);
}


/**
 * @brief WS2812显示任务
 *
 * @param dT 任务周期
 */
uint8_t New_RGB;//当前点亮的灯
uint8_t Sum_RGB = 24;//还没有点亮的灯
void WS2812_Duty(float dT)
{
    
    static uint32_t time = 0;
    static uint8_t led_check = 1;
    uint8_t step;
	int8_t Old_RGB;
    uint8_t RGB_Speed;
	uint8_t val1,val2,val3,val4;
    if (led_check) //开机灯光自检
	{
        /*****************开机灯效***************/
//        if(Sum_RGB)
//        {
//            time += 20;
//            step = (time / 20) % 25;
//            New_RGB = step;
//            if(New_RGB >= Sum_RGB)
//            {
//                WS2812_SetColor(New_RGB, 0xFF, 0xFF, 0xFF, 1.0f);
//                Sum_RGB --;
//                time = 0;
//            }
//            else
//            {
//                WS2812_SetColor(New_RGB, 0xFF, 0xFF, 0xFF, 1.0f);
//                Old_RGB = New_RGB-1;
//                if(Old_RGB<0)
//                    Old_RGB = 0;
//                WS2812_SetColor(Old_RGB, 0xFF, 0xFF, 0xFF, 0.0f);
//            }
//        }
//        else
//        {
//            WS2812_SetColor(0, 0xFF, 0xFF, 0xFF, 1.0f);
//            led_check = 0;
//            time = 0;
//        }
    /*****************开机灯效1***************/
        
        time += 20;
        step = (time / 60) % 24;
        New_RGB = 23-step;
        WS2812_SetColor(New_RGB, 0xFF, 0xFF, 0xFF, 1.0f);
        if(step >= 23)
           led_check = 0; 
    }
    else
    {
        if(sys.Run_Status ||(Infrared[0].Someone || Infrared[1].Someone))
        {
            /***************启动灯效************/
            WS2812_SetColor(0xFF, 0xFF, 0xFF, 0xFF, 0.4f);
            RGB_Speed = 100-((float)Speed.Ctrl / 3900 * 80);
            time += 20;
            step = (time / (RGB_Speed)) % 24;
            val1 = step;
            if(val1 > 23) val1 = 0;
            WS2812_SetColor(val1, 0xFF, 0xFF, 0xFF, 1.0f);
            val2 = val1+1;
            if(val2 > 23) val2 = 0;
            WS2812_SetColor(val2, 0xFF, 0xFF, 0xFF, 1.0f);	
            val3 = val2+1;
            if(val3 > 23) val3 = 0;
            WS2812_SetColor(val3, 0xFF, 0xFF, 0xFF, 1.0f);	
            val4 = val3+1;
            if(val4 > 23) val4 = 0;
            WS2812_SetColor(val4, 0xFF, 0xFF, 0xFF, 1.0f);
        }
        else
        {
            WS2812_SetColor(0xFF, 0xFF, 0xFF, 0xFF, 0.4f);
        }
    }
        
	if (!WS2812_Status[0].Sending || !WS2812_Status[1].Sending)
		WS2812_Update();
}
