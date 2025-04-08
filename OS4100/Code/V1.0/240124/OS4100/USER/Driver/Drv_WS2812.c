#include "Drv_WS2812.h"

/**********结构体************/
_WS2812_RGB_ WS2812;
_WS2812_ WS2812_Status;

/**********局部变量声明******/
uint16_t WS2812_Buf[RGB_NUM * 24 + 42]; // 存放的数组
uint16_t Memaddr = 0;					// 数组的地址值

/**
 * @brief WS2812初始化
 *
 */
void WS2812_Init(void)
{
	WS2812.Tim = &WS2812_Tim;		// 定时器选择
	WS2812.CHANNEL = TIM_CHANNEL_3; // 定时器通道数
}

/**
 * @brief 更新目前灯的状态
 *
 */
void WS2812_Update(void)
{
	if (!WS2812_Status.Update)
		return; // 在更新的时候不进入

	HAL_TIM_PWM_Start_DMA(WS2812.Tim, WS2812.CHANNEL, (uint32_t *)WS2812_Buf, Memaddr); // 开始传输字节数据

	WS2812_Status.Sending = 1; // 发送
	WS2812_Status.Update = 0;  // 更新完成，标志位清零
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

	WS2812_Status.Number = num; // 灯的序号

	WS2812.Red_Out = WS2812.Red = r; // 颜色赋值
	WS2812.Green_Out = WS2812.Green = g;
	WS2812.Blue_Out = WS2812.Blue = b;

	WS2812.Red_Out = (WS2812.Red_Out + 1) / 16 * MAX_RATE * 10;		// 乘等于最大亮度值
	WS2812.Green_Out = (WS2812.Green_Out + 1) / 16 * MAX_RATE * 10; // 乘等于最大亮度值
	WS2812.Blue_Out *= (WS2812.Blue_Out + 1) / 16 * MAX_RATE * 10;	// 乘等于最大亮度值

	if (WS2812_Status.Number == 0xFF) // 同时改变所有灯的颜色
	{
		Memaddr = 0;		  // 从头赋值
		while (cnt < RGB_NUM) // 一个一个发
		{
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf[Memaddr++] = ((WS2812.Green_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO; // 将设定值拆分放入数组中
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf[Memaddr++] = ((WS2812.Red_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
			for (uint8_t i = 0; i < 8; i++)
				WS2812_Buf[Memaddr++] = ((WS2812.Blue_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
			cnt++;
		}
	}
	else if (WS2812_Status.Number <= RGB_NUM) // 只改变指定序号灯的颜色，看RGB_NUM的值
	{
		Memaddr = WS2812_Status.Number * 24;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf[Memaddr++] = ((WS2812.Green_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf[Memaddr++] = ((WS2812.Red_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
		for (uint8_t i = 0; i < 8; i++)
			WS2812_Buf[Memaddr++] = ((WS2812.Blue_Out << i) & 0x80) ? TIMING_ONE : TIMING_ZERO;
	}

	WS2812_Status.Update = 1; // 更新显示
}

/**
 * @brief PWM信号传输完成回调函数，该函数非常之重要
 *
 * @param htim
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	WS2812_Status.Sending = 0;							  // 发送完成，标志位清零
	__HAL_TIM_SET_COMPARE(WS2812.Tim, WS2812.CHANNEL, 0); // 将占空比清零
	HAL_TIM_PWM_Stop_DMA(WS2812.Tim, WS2812.CHANNEL);	  // 关闭DMA传输
}

/**
 * @brief 按键灯光变化
 *
 * @param dT 任务周期
 */
void KEYLED_Check(float dT)
{
	if (Lock_Switch) // 按下按键
	{
		WS2812_SetColor(0x00, 0xFF, 0xFF, 0xFF);
	}
	else
	{
		WS2812_SetColor(0x00, 0x00, 0x00, 0x00);
	}

	if (Shake_Switch) // 按下按键
	{
		WS2812_SetColor(0x01, 0xFF, 0xFF, 0xFF);
	}
	else
	{
		WS2812_SetColor(0x01, 0x00, 0x00, 0x00);
	}
}

/**
 * @brief 抖动报警
 *
 * @param dT 任务周期
 */
void ShakeRGB_Check(float dT)
{
	static float T;
	static uint8_t Val;
	if (T == 0)
	{
		Val++;
		if (Val > 5)
			Val = 0;
	}
	T += dT;
	if (T >= 0.2f)
	{
		T = 0;
	}

	switch (Val)
	{
	case 0:
		WS2812_SetColor(0xFF, 0xFF, 0x00, 0x00);
		break;
	case 1:
		WS2812_SetColor(0xFF, 0x00, 0x00, 0x00);
		break;
	case 2:
		WS2812_SetColor(0xFF, 0xFF, 0x00, 0x00);
		break;
	case 3:
		WS2812_SetColor(0xFF, 0x00, 0x00, 0x00);
		break;
	default:
		WS2812_SetColor(0xFF, 0xFF, 0x00, 0x00);
		break;
	}
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

	if (Save_Param_En)
		return;

	if (led_check) // 开机灯光自检
	{
		time += 20;
		uint8_t step = (time / 500) % 4;
		if (step == 0)
//			WS2812_SetColor(0xFF, 0xFF, 0, 0);
//		else
			WS2812_SetColor(0xFF, 0xFF, 0xFF, 0xFF), led_check = 0, WS2812_Status.Mode = 1;
	}
	else
	{
		switch (WS2812_Status.Mode)
		{
		case 1:
			WS2812_SetColor(0xFF, 0xFF, 0xFF, 0xFF);
			KEYLED_Check(dT);
			WS2812_Status.Mode = 3;
			break; // 正常情况下
		case 2:
			ShakeRGB_Check(dT);
			break; // 按键变换检测
		case 3:
			
			break; // 按键变换检测
		}
	}

	if (!WS2812_Status.Sending)
		WS2812_Update();
}
