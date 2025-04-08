#include "Drv_WS2812.h"

/**********结构体************/
_WS2812_RGB_ WS2812[2];
_WS2812_ WS2812_Status[2];

/**********局部变量声明******/
uint16_t WS2812_Buf1[RESET_WORD+RGB_NUM1 * 24+DUMMY_WORD]; // 存放的数组
uint16_t WS2812_Buf2[RESET_WORD+RGB_NUM2 * 24+DUMMY_WORD]; // 存放的数组

uint16_t Memaddr = 0;					// 数组的地址值

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
}

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
void WS2812_SetColor(uint8_t num, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t cnt = 0;

	WS2812_Status[0].Number = num; // 灯的序号

	WS2812[0].Red_Out = WS2812[0].Red = r; // 颜色赋值
	WS2812[0].Green_Out = WS2812[0].Green = g;
	WS2812[0].Blue_Out = WS2812[0].Blue = b;

	WS2812[0].Red_Out = (WS2812[0].Red_Out + 1) / 16 * MAX_RATE * 10;		// 乘等于最大亮度值
	WS2812[0].Green_Out = (WS2812[0].Green_Out + 1) / 16 * MAX_RATE * 10; // 乘等于最大亮度值
	WS2812[0].Blue_Out = (WS2812[0].Blue_Out + 1) / 16 * MAX_RATE * 10;	// 乘等于最大亮度值

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
/*
*****************************************************************
 * 函数原型：static void WS2812_Breath(float dT, uint8_t num, uint8_t f, uint8_t r, uint8_t g, uint8_t b)
 * 功    能：呼吸灯
 * 输    入：num：第几个RGB灯，f：是否点亮，r、g、b：表示颜色的值
 * 参    数：float dT, uint8_t num, uint8_t f, uint8_t r, uint8_t g, uint8_t b
 * 调    用：内部调用
*****************************************************************
*/
static void WS2812_Breath(float dT, uint8_t num, uint8_t r, uint8_t g, uint8_t b)
{
    static float T;
    float Run_Time;

    T += dT;
    if(T >= (float)(BREATH_TIME / 1000)) T = 0;
    Run_Time = (T * 1000) / BREATH_TIME * 6.28f;
    Run_Time = (cosf(Run_Time) + 1) * 0.5;

	WS2812_SetColor(num, r * Run_Time,g * Run_Time,b * Run_Time);
}

/*
*****************************************************************
 * 函数原型：static void WS2812_Colorful(float dT, uint8_t num, uint8_t f)
 * 功    能：七彩变幻
 * 输    入：num：第几个RGB灯，f：是否点亮
 * 参    数：float dT, uint8_t num, uint8_t f
 * 调    用：内部调用
*****************************************************************
*/
static void WS2812_Colorful(float dT, uint8_t num)
{
    static float T;
    float Run_Time;
	uint8_t Red,Green,Blue;
    T += dT;
    if(T >= (float)(COLORFUL_TIME / 1000)) T = 0;
    Run_Time = (T * 1000) / COLORFUL_TIME * 6.28f;
	
	Red = ((cosf(Run_Time - 1.04f) + 1) * 0.5f) * 0xFF;
	Green = ((cosf(Run_Time + 0.00f) + 1) * 0.5f) * 0xFF;
	Blue = ((cosf(Run_Time + 1.04f) + 1) * 0.5f) * 0xFF;
	
	WS2812_SetColor(num, Red,Green,Blue);
        
}

/**
 * @brief WS2812显示任务
 *
 * @param dT 任务周期
 */
void WS2812_Duty(float dT)
{
	static uint16_t time = 0;
	static uint8_t led_check = 1;
	static uint32_t time1 = 0;
//	if (Save_Param_En)
//		return;
	uint8_t val1,val2,val3,val4,val5,val6,val7,val8,val9,val10;
	if (led_check) //开机灯光自检
	{
		time += 20;
		uint8_t step = (time / 500) % 4;
		if (step == 0)
			WS2812_SetColor(0xFF, 0xFF, 0, 0);
		else if (step == 1)
			WS2812_SetColor(0xFF, 0, 0xFF, 0);
		else
			WS2812_SetColor(0xFF, 0, 0, 0), led_check = 0, WS2812_Status[0].Mode = 1;
	}
	else
	{
		switch (WS2812_Status[0].Mode)
		{
		case 1:
//			time1 += 20;
//			uint8_t step1 = (time1 / 25) % 12;
//			WS2812_Colorful(dT,step1);
//			WS2812_Colorful(dT,24-step1);

//			time1 += 20;
//			uint8_t step1 = (time1 / 25) % 24;
//			WS2812_Colorful(dT,step1);
			
		
//			time1 += 20;
//			uint8_t step1 = (time1 / 25) % (RGB_NUM1/2);
//			if(time1 > 25*(RGB_NUM1/2))
//				time1 = 0;
//			WS2812_Colorful(dT,step1);
//			WS2812_Colorful(dT,12+step1);
		
		WS2812_SetColor(0xFF, 0, 0, 0);
		/**************************************/
//			if (sys.Run_Status == 1 || Speed.Rel > 100)
//			{
//				WS2812_SetColor(0xFF, 0, 0, 0);
//				time1 += 20;
//				uint8_t step1 = (time1 / 20) % 24;
//				val1 = step1;
//				if(val1 > 23) val1 = 0;
//				WS2812_SetColor(val1, 0xFF, 0xFF, 0xFF);
//				val2 = val1+1;
//				if(val2 > 23) val2 = 0;
//				WS2812_SetColor(val2, 0xFF, 0xFF, 0xFF);
//				val3 = val2+1;
//				if(val3 > 23) val3 = 0;
//				WS2812_SetColor(val3, 0xFF, 0xFF, 0xFF);
//				val4 = val3 + 1;
//				if(val4 > 23) val4 = 0;
//				WS2812_SetColor(val4, 0xFF, 0xFF, 0xFF);
//				val5 = val4 + 1;
//				if(val5 > 23) val5 = 0;
//				WS2812_SetColor(val5, 0xFF, 0xFF, 0xFF);
//				val6 = val5 + 1;
//				if(val6 > 23) val6 = 0;
//				WS2812_SetColor(val6, 0xFF, 0xFF, 0xFF);
//				
//				val7 = val6 + 1;
//				if(val7 > 23) val7 = 0;
//				WS2812_SetColor(val7, 0xFF, 0xFF, 0xFF);
//				val8= val7 + 1;
//				if(val8 > 23) val8 = 0;
//				WS2812_SetColor(val8, 0xFF, 0xFF, 0xFF);
//				val9 = val8 + 1;
//				if(val9 > 23) val9 = 0;
//				WS2812_SetColor(val9, 0xFF, 0xFF, 0xFF);
//				val10= val9 + 1;
//				if(val10 > 23) val10 = 0;
//				WS2812_SetColor(val10, 0xFF, 0xFF, 0xFF);
//				
//				
//				if(step1 > 23)
//					time1 = 0;
//			}
//			else
//			{
//				WS2812_SetColor(0xFF, 0xFF, 0xFF, 0xFF);
//				time1 = 0;
//			}



//			time1 += 20;
//			uint8_t step1 = (time1 / 50) % ((RGB_NUM1/2)-1);
//			if(time1 > 50*((RGB_NUM1/2)-1))
//				time1 = 0;
//			WS2812_SetColor(step1, 0, 0, 0);
//			WS2812_SetColor(step1+1, 0, 0, 0);
//			WS2812_SetColor(24-step1, 0, 0, 0);
//			WS2812_SetColor(24-(step1 + 1), 0, 0, 0);
//			WS2812_SetColor(0, 0, 0, 0);
//			WS2812_SetColor(1, 0, 0, 0);
//			WS2812_SetColor(23-0, 0, 0, 0);
//			WS2812_SetColor(23-1, 0, 0, 0);
			break; // 正常情况下
		case 2:
			break; // 按键变换检测
		case 3:
			break; // 按键变换检测
		}
	}

//	WS28121_SetColor(1, 0xFF, 0xFF, 0xFF);
//	WS28121_SetColor(2, 0xFF, 0xFF, 0xFF);
//	WS28121_SetColor(3, 0xFF, 0xFF, 0xFF);
	WS28121_SetColor(1, 0, 0, 0);
	WS28121_SetColor(2, 0, 0, 0);
	WS28121_SetColor(3, 0, 0, 0);
	
	if (!WS2812_Status[0].Sending || !WS2812_Status[1].Sending)
		WS2812_Update();
}
