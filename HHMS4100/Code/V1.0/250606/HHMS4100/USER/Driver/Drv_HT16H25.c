#include "Drv_HT16H25.h"

/**
 * @brief 写命令
 * 
 * @param command 命令
 * @param data 数据
 */
void HT16H25_Command_Write(uint8_t command, uint8_t data)
{
    IIC_Start();
    IIC_Send_Byte(IIC_ADDR_MASTERWR); // HT16H25的IIC地址
	IIC_Wait_Ack();
    IIC_Send_Byte(command);
	IIC_Wait_Ack();
    IIC_Send_Byte(data);
	IIC_Wait_Ack();
    IIC_Stop();
}

/**
 * @brief 更新显示RAM
 * 
 * @param buff 
 */
void HT16H25_RamUpdata(uint8_t* buff)
{
	uint8_t i;
	
    IIC_Start();
    IIC_Send_Byte(IIC_ADDR_MASTERWR); // HT16H25的IIC地址
	IIC_Wait_Ack();
    IIC_Send_Byte(WriteDisRam); // Write Display RAM命令
	IIC_Wait_Ack();
    IIC_Send_Byte(0); // 起始地址
    IIC_Wait_Ack();
    for(i=0;i<LCD_Buff_Size;i++)
	{
		IIC_Send_Byte(buff[i]);//data
		IIC_Wait_Ack();
		
	}
    IIC_Stop();
}

void Write_Addr_Dat_N(uint8_t _addr, uint8_t _dat, uint8_t n)
{
    int8_t i = 0;

	IIC_Start();
    IIC_Send_Byte(IIC_ADDR_MASTERWR); // HT16H25的IIC地址
	IIC_Wait_Ack();
    IIC_Send_Byte(WriteDisRam); // Write Display RAM命令
	IIC_Wait_Ack();
	IIC_Send_Byte(_addr); // 起始地址
    IIC_Wait_Ack();
    for(i = 0; i < n; i++)
    {
        IIC_Send_Byte(_dat);
		IIC_Wait_Ack();
    }
    IIC_Stop();
}

/**
 * @brief LCD显示开关
 * 
 * @param data on:0xFF off:0x00
 */
void HT16H25_LCD_OnOFF(uint8_t data)
{
	uint8_t i;
	static uint8_t LCD_Buff[LCD_Buff_Size];
	if(data)
	{
		//data=1: LCD all on
		for(i=0;i<sizeof(LCD_Buff);i++)
		{LCD_Buff[i] = data;}
	}
	else
	{
		//data=0: LCD all off
		for(i=0;i<sizeof(LCD_Buff);i++)
		{LCD_Buff[i] = 0x00;}
	}
	HT16H25_RamUpdata(LCD_Buff);
}

/**
 * @brief HT16H25初始化
 * 
 */
void HT16H25_Init(void)
{
	HAL_GPIO_WritePin(LED_POR_GPIO_Port, LED_POR_Pin, GPIO_PIN_SET);//开启背光
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	
	IIC_Start();
	IIC_Send_Byte(IIC_ADDR_MASTERWR);//HT16H25的IIC地址
	IIC_Wait_Ack();
	IIC_Send_Byte(SoftwareReset);//power on reset
	IIC_Wait_Ack();
	IIC_Stop();
	Delay_ms(5);//delay >1ms
	
    /*****初始化序列*****/
	// 设置电荷泵输出电压为1.0V (Set charge pump output voltage to 1.0V)
	// 0xC0 = 1100 0000 (bit7-6: 11=1.0V, bit5-0: 保留位)
    HT16H25_Command_Write(ChargePump_vol, 0xc0); // 电荷泵电压设置 (Charge Pump Voltage Setting)
	
	// 启用电荷泵，倍率5x (Enable charge pump with 5x multiplier)
	// 0xC0 = 1100 0000 (bit7: 1=启用, bit6: 1=5x倍率, bit5-0: 保留位)
    HT16H25_Command_Write(ChargePump_ctrl, 0xc0); // 电荷泵控制 (Charge Pump Control)

	// 选择电荷泵作为VLCD电源 (Select charge pump as VLCD source)
	// 0x01 = 0000 0001 (bit0: 1=使用电荷泵)
	HT16H25_Command_Write(BiasCircuit, 0x01); // LCD偏置电路选择 (LCD Bias Circuit Selection)
	
	// 设置1/16占空比，1/5偏置 (Set 1/16 duty cycle, 1/5 bias)
	// 0xF4 = 1111 0100 (bit7-4: 1111=1/16 duty, bit3-0: 0100=1/5 bias)
	HT16H25_Command_Write(DriveMode, 0xF4); // LCD偏置占空比设置 (LCD Bias Duty Setting)
	
	// 选择B型驱动波形 (Select type B drive waveform)
	// 0x01 = 0000 0001 (bit0: 0=A型, 1=B型)
	HT16H25_Command_Write(DriveWaveform, 0x01); // 驱动波形设置 (Drive Waveform Setting)
	
	// 设置帧频160Hz，电荷泵频率kHz级 (Set frame rate 160Hz, charge pump in kHz range)
	// 0x0C = 0000 1100 (bit7-4: 0000=保留, bit3-0: 1100=160Hz)
	HT16H25_Command_Write(FrameFrequence, 0x0C); // 帧频率设置 (Frame Frequency Setting)
	
	// 启用振荡器并打开LCD显示 (Enable oscillator and turn on LCD)
	// 0x03 = 0000 0011 (bit1: 1=振荡器ON, bit0: 1=LCD ON)
	HT16H25_Command_Write(SystemMode, 0x03); // 系统模式设置 (System Mode Setting)
	
	HT16H25_LCD_OnOFF(0xFF);
	Delay_ms(200);
	HT16H25_LCD_OnOFF(0x00);
}
