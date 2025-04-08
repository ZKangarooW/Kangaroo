#include "Drv_HT1623.h"

/*
*****************************************************************
 * 函数原型：static void LCD_Delay(void)
 * 功    能：LCD_us延时
 * 调    用：内部调用
*****************************************************************
*/
static void LCD_Delay(void)
{
    uint8_t a;
    for(a = 100; a > 0; a--);
}

/*
*****************************************************************
 * 函数原型：static void Write_Mode(uint8_t MODE)
 * 功    能：写入模式,数据or命令
 * 输    入: MODE ：数据or命令
 * 参    数：uint8_t MODE
 * 调    用：内部调用
*****************************************************************
*/
static void Write_Mode(uint8_t MODE)
{
    LCD_Delay();
    Clr_1625_Wr;//RW = 0;
    LCD_Delay();
    Set_1625_Dat;//DA = 1;
    Set_1625_Wr;//RW = 1;
    LCD_Delay();
    Clr_1625_Wr;//RW = 0;
    LCD_Delay();
    Clr_1625_Dat;//DA = 0;
    LCD_Delay();
    Set_1625_Wr;//RW = 1;
    LCD_Delay();
    Clr_1625_Wr;//RW = 0;
    LCD_Delay();
    if(0 == MODE)
    {
        Clr_1625_Dat;//DA = 0;
    }
    else
    {
        Set_1625_Dat;//DA = 1;
    }
    LCD_Delay();
    Set_1625_Wr;//RW = 1;
    LCD_Delay();
}

/*
*****************************************************************
 * 函数原型：static void Write_Command(uint8_t Cbyte)
 * 功    能：LCD 命令写入函数
 * 输    入: Cbyte：控制命令字
 * 参    数：uint8_t Cbyte
 * 调    用：内部调用
*****************************************************************
*/
static void Write_Command(uint8_t Cbyte)
{
    uint8_t i = 0;
    for (i = 0; i < 8; i++)
    {
        Clr_1625_Wr;
        //Delay_us(10);
        if((Cbyte >> (7 - i)) & 0x01)
        {
            Set_1625_Dat;
        }
        else
        {
            Clr_1625_Dat;
        }
        LCD_Delay();
        Set_1625_Wr;
        LCD_Delay();
    }
    Clr_1625_Wr;
    LCD_Delay();
    Clr_1625_Dat;
    Set_1625_Wr;
    LCD_Delay();
}

/*
*****************************************************************
 * 函数原型：static void Write_Address(uint8_t Abyte)
 * 功    能：LCD 地址写入函数
 * 输    入: Abyte：地址
 * 参    数：uint8_t Abyte
 * 调    用：内部调用
*****************************************************************
*/
static void Write_Address(uint8_t Abyte)
{
    uint8_t i = 0;
    Abyte = Abyte << 1;
    for(i = 0; i < 6; i++)
    {
        Clr_1625_Wr;
        if((Abyte >> (6 - i)) & 0x01)
        {
            Set_1625_Dat;
        }
        else
        {
            Clr_1625_Dat;
        }
        LCD_Delay();
        Set_1625_Wr;
        LCD_Delay();
    }
}

/*
*****************************************************************
 * 函数原型：static void Write_Data_8bit(uint8_t Dbyte)
 * 功    能：LCD 8bit数据写入函数
 * 输    入: Dbyte：数据
 * 参    数：uint8_t Dbyte
 * 调    用：内部调用
*****************************************************************
*/
static void Write_Data_8bit(uint8_t Dbyte)
{
    int i = 0;
    for(i = 0; i < 8; i++)
    {
        Clr_1625_Wr;
        if((Dbyte >> (7 - i)) & 0x01)
        {
            Set_1625_Dat;
        }
        else
        {
            Clr_1625_Dat;
        }
        LCD_Delay();
        Set_1625_Wr;
        LCD_Delay();
    }
}

/*
*****************************************************************
 * 函数原型：void Write_Data_4bit(uint8_t Dbyte)
 * 功    能：LCD 4bit数据写入函数
 * 输    入: Dbyte：数据
 * 参    数：uint8_tr Dbyte
 * 调    用：内部调用
*****************************************************************
*/
void Write_Data_4bit(uint8_t Dbyte)
{
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        Clr_1625_Wr;
        if((Dbyte >> (3 - i)) & 0x01)
        {
            Set_1625_Dat;
        }
        else
        {
            Clr_1625_Dat;
        }
        LCD_Delay();
        Set_1625_Wr;
        LCD_Delay();
    }
}

/*
*****************************************************************
 * 函数原型：void Lcd_Init(void)
 * 功    能：LCD 初始化，对lcd自身做初始化设置
*****************************************************************
*/
void Lcd_Init(void)
{
    Set_1625_Cs;
    Set_1625_Wr;
    Set_1625_Dat;
    LCD_Delay();
    Clr_1625_Cs;//CS = 0;
    LCD_Delay();
    Write_Mode(0);//命令模式
    Write_Command(0x01);//Enable System
    Write_Command(0x03);//Enable Bias
    Write_Command(0x04);//Disable Timer
    Write_Command(0x05);//Disable WDT
    Write_Command(0x08);//Tone OFF
    Write_Command(0x18);//on-chip RC震荡
    Write_Command(0x29);//1/4Duty 1/3Bias
    Write_Command(0x80);//Disable IRQ
    Write_Command(0x40);//Tone Frequency 4kHZ
    Write_Command(0xE3);//Normal Mode
    Set_1625_Cs;//CS = 1;
	
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	 __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1,60);//不输出pwm
	 
	Lcd_All();
	Temp_Init();//开机显示温度
	Lcd_Clr();
}

/*
*****************************************************************
 * 函数原型：void Lcd_Clr(void)
 * 功    能：LCD 清屏函数
*****************************************************************
*/
void Lcd_Clr(void)
{
    Write_Addr_Dat_N(0x0, 0x00, 50);
}


/*
*****************************************************************
 * 函数原型：void Lcd_All(void)
 * 功    能：LCD 全显示函数
*****************************************************************
*/
void Lcd_All(void)
{
    Write_Addr_Dat_N(0x0, 0xff, 60);
	Write_Addr_Dat_N(0, 0x0f, 1);
}

/*
*****************************************************************
 * 函数原型：void Write_Addr_Dat_N(uint8_t _addr, uint8_tr _dat, uint8_t n)
 * 功    能：屏幕显示
 * 输    入: _addr：地址  char _dat：数据 n：个数
 * 参    数：uint8_t _addr, uint8_t _dat, uint8_t n
*****************************************************************
*/
void Write_Addr_Dat_N(uint8_t _addr, uint8_t _dat, uint8_t n)
{
    uint8_t i = 0;
    Clr_1625_Cs;//CS = 0;
    LCD_Delay();
    Write_Mode(1);
    Write_Address(_addr);
    for(i = 0; i < n; i++)
    {
        Write_Data_8bit(_dat);
    }
    Set_1625_Cs;//CS = 1;
}
