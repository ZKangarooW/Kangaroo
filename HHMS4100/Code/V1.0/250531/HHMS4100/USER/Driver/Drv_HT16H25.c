#include "Drv_HT16H25.h"

uint8_t LCD_Buff[LCD_Buff_Size];
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t d);
uint8_t IIC_Wait_Ack(void);
uint8_t  IIC_Read_Byte(void);
void IIC_Ack(uint8_t ack);
// 写命令
void HT16H25_Command_Write(uint8_t command, uint8_t data) {
    IIC_Start();
    IIC_Send_Byte(IIC_ADDR_MASTERWR);
	IIC_Wait_Ack();
    IIC_Send_Byte(command);
	IIC_Wait_Ack();
    IIC_Send_Byte(data);
	IIC_Wait_Ack();
    IIC_Stop();
}

// 更新显示RAM
void HT16H25_RamUpdata(uint8_t* buff) {
	uint8_t i;
	
    IIC_Start();
    IIC_Send_Byte(IIC_ADDR_MASTERWR);
	IIC_Wait_Ack();
    IIC_Send_Byte(WriteDisRam); // Write Display RAM命令
	IIC_Wait_Ack();
    IIC_Send_Byte(0); // 起始地址
    IIC_Wait_Ack();
    for(i=0;i<LCD_Buff_Size;i++)
	{
		IIC_Send_Byte(buff[i]);		//data
		IIC_Wait_Ack();
		
	}
    IIC_Stop();
}

void HT16H25_LCD_OnOFF(uint8_t data)
{
	uint8_t i;
	
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
		{LCD_Buff[i] = 0;}
	}
}

// 初始化
void HT16H25_Init(void) {
	HAL_GPIO_WritePin(LED_POR_GPIO_Port, LED_POR_Pin, GPIO_PIN_SET);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	IIC_Start();
	IIC_Send_Byte(IIC_ADDR_MASTERWR);
	IIC_Wait_Ack();
	IIC_Send_Byte(SoftwareReset);
	IIC_Wait_Ack();
	IIC_Stop();
	Delay_ms(5);
	
    // 初始化序列
    HT16H25_Command_Write(ChargePump_vol, 0xc0); // 软件复位
    HT16H25_Command_Write(ChargePump_ctrl, 0xc0); // 软件复位
	HT16H25_Command_Write(BiasCircuit, 0x01); // 软件复位
	HT16H25_Command_Write(DriveMode, 0xF4); // 软件复位
	HT16H25_Command_Write(DriveWaveform, 0x01); // 软件复位
	HT16H25_Command_Write(FrameFrequence, 0x0C); // 软件复位
	HT16H25_Command_Write(SystemMode, 0x03); // 软件复位
	
	
	HT16H25_LCD_OnOFF(0xFF);
	HT16H25_RamUpdata(LCD_Buff);
	for(uint8_t i = 30;i < 50;i ++){
			LCD_Buff[i] = 0xff; 
		}
		// LCD_Buff[byte_n] = byte_d;					
		HT16H25_RamUpdata(LCD_Buff);
}
