#include "Drv_WS2812.h"

/**********结构体************/
_WS2812_RGB_ WS2812 = {0,0,0,0,0,0,0};
_WS2812_ WS2812_Status = {0,0,0};

/**********局部变量声明******/
uint8_t WS2812_Buf[RGB_NUM * 24] = {0};//存放的数组
uint16_t Memaddr = 0;//数组的地址值

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
	uint8_t i = 0;
	WS2812_Status.Number = num;//灯的序号

	WS2812.Red_Out = WS2812.Red = r;//颜色赋值
	WS2812.Green_Out = WS2812.Green = g;
	WS2812.Blue_Out = WS2812.Blue = b;

	if (WS2812_Status.Number == 0xFF)//同时改变所有灯的颜色
	{
		Memaddr = 0;// 从头赋值
		while (cnt < RGB_NUM) // 一个一个发
		{
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X80;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X40;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X20;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0x10;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X08;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X04;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X02;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X01;//将设定值拆分放入数组中
			
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X80;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X40;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X20;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0x10;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X08;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X04;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X02;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X01;//将设定值拆分放入数组中
			
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X80;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X40;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X20;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0x10;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X08;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X04;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X02;//将设定值拆分放入数组中
			WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X01;//将设定值拆分放入数组中
			cnt++;
		}
	}
	else if (WS2812_Status.Number <= RGB_NUM)//只改变指定序号灯的颜色，看RGB_NUM的值
	{
		Memaddr = WS2812_Status.Number * 24;
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X80;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X40;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X20;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0x10;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X08;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X04;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X02;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Green_Out&0X01;//将设定值拆分放入数组中
		
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X80;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X40;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X20;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0x10;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X08;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X04;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X02;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Red_Out&0X01;//将设定值拆分放入数组中
		
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X80;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X40;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X20;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0x10;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X08;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X04;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X02;//将设定值拆分放入数组中
		WS2812_Buf[Memaddr++] = WS2812.Blue_Out&0X01;//将设定值拆分放入数组中
	}
	WS2812_Status.Update = 1;//更新显示
}

/**
 * @brief 发送数据控制引脚电平变换
 *
 * @param data_bit 发送1数据还是0数据
 */
void WS2812_Bit(bit data_bit)
{
	if(data_bit)
	{
		WS2812B_H;
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
		WS2812B_L;	
	}
	else
	{
		WS2812B_H;
		_nop_();_nop_();_nop_();
		WS2812B_L;	
	}
}

/**
 * @brief 大于50us的低电平清除帧
 *
 */
void WS2812_Reset(void)
{
	u16 i;
	WS2812B_L;
	for(i=0;i<90;i++){
		_nop_();_nop_();
	}
}

/**
 * @brief 发送灯的数据
 *
 * @param pData 数据数组
 *
 * @param Length 数组长度
 */
void WS2812_SendBuf(const uint8_t *pData,uint16_t Length)
{
	uint16_t i;
	
	for(i = 0;i<Length;i++)//循环发送
	{
		WS2812_Bit(pData[i]);
	}
	
	WS2812_Reset();//等待50us
}

/**
 * @brief 更新目前灯的状态
 *
 */
void WS2812_Update(void)
{
	if (WS2812_Status.Update)
	{
		WS2812_SendBuf(&WS2812_Buf,RGB_NUM * 24);//开始传输字节数据
		WS2812_Status.Update = 0;//更新完成，标志位清零
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
	static uint32_t time1 = 0;
	uint8_t step;
	uint8_t step1;
	uint8_t val1,val2;
	if (led_check) //开机灯光自检
	{
		time += 20;
		step = (time / 500) % 3;
		if (step == 0)
			WS2812_SetColor(0xFF, 0xFF, 0, 0);
		else if (step == 1)
			WS2812_SetColor(0xFF, 0, 0xFF, 0);
		else
			WS2812_SetColor(0xFF, 0, 0, 0xFF), led_check = 0, WS2812_Status.Mode = 1;
	}
	else
	{
		switch (WS2812_Status.Mode)
		{
			case 1:
				WS2812_SetColor(0xFF, 0x30, 0x30, 0x30);
				time1 += 20;
				step1 = (time1 / 100) % 24+3;
				val1 = step1;
				if(val1 > 26) val1 = 3;
				WS2812_SetColor(val1, 0xFF, 0xFF, 0xFF);
				val2 = val1+1;
				if(val2 > 26) val2 = 3;
				WS2812_SetColor(val2, 0xFF, 0xFF, 0xFF);	
			break;
		}
	}
}
