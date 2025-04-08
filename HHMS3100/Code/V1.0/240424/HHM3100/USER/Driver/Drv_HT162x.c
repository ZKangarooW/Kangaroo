#include "Drv_HT162x.h"

/**
 * @brief LCD_us延时
 *
 */
static void LCD_Delay(void)
{
    uint8_t a;
    for (a = 100; a > 0; a--);
}

/**
 * @brief 写入模式，数据or命令
 *
 * @param x 屏幕芯片选型，0是下半部分，1是上半部分
 * @param MODE 数据or命令
 */
static void Write_Mode(uint8_t x,uint8_t MODE)
{
    LCD_Delay();
    Clr_162x_Wr(x);//RW = 0;
    LCD_Delay();
    Set_162x_Dat(x);//DA = 1;
    Set_162x_Wr(x);//RW = 1;
    LCD_Delay();
    Clr_162x_Wr(x);//RW = 0;
    LCD_Delay();
    Clr_162x_Dat(x);//DA = 0;
    LCD_Delay();
    Set_162x_Wr(x);//RW = 1;
    LCD_Delay();
    Clr_162x_Wr(x);//RW = 0;
    LCD_Delay();
    if(0 == MODE)
    {
        Clr_162x_Dat(x);//DA = 0;
    }
    else
    {
        Set_162x_Dat(x);//DA = 1;
    }
    LCD_Delay();
    Set_162x_Wr(x);//RW = 1;
    LCD_Delay();
}

/**
 * @brief LCD命令写入函数
 *
 * @param x 屏幕芯片选型，0是下半部分，1是上半部分
 * @param Cbyte 控制命令字
 */
static void Write_Command(uint8_t x, uint8_t Cbyte)
{
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        Clr_162x_Wr(x);
        if((Cbyte >> (7 - i)) & 0x01)
        {
            Set_162x_Dat(x);
        }
        else
        {
            Clr_162x_Dat(x);
        }
        LCD_Delay();
        Set_162x_Wr(x);
        LCD_Delay();
    }
    Clr_162x_Wr(x);
    LCD_Delay();
    Clr_162x_Dat(x);
    Set_162x_Wr(x);
    LCD_Delay();
}

/**
 * @brief LCD地址写入函数
 *
 * @param x 屏幕芯片选型，0是下半部分，1是上半部分
 * @param Abyte 地址
 */
static void Write_Address(uint8_t x, uint8_t Abyte)
{
    uint8_t i = 0;
    Abyte = Abyte << 1;
    for (i = 0; i < 7; i++)
    {
        Clr_162x_Wr(x);
        if((Abyte >> (6 - i)) & 0x01)
        {
            Set_162x_Dat(x);
        }
        else
        {
            Clr_162x_Dat(x);
        }
        LCD_Delay();
        Set_162x_Wr(x);
        LCD_Delay();
    }
}

/**
 * @brief 数据写入函数
 *
 * @param x 屏幕芯片选型，0是下半部分，1是上半部分
 * @param Dbyte 写入的数据
 */
static void Write_Data_8bit(uint8_t x, uint8_t Dbyte)
{
    int i = 0;
    for(i = 0; i < 8; i++)
    {
        Clr_162x_Wr(x);
        if((Dbyte >> (7 - i)) & 0x01)
        {
            Set_162x_Dat(x);
        }
        else
        {
            Clr_162x_Dat(x);
        }
        LCD_Delay();
        Set_162x_Wr(x);
        LCD_Delay();
    }
}

/**
 * @brief 数据写入函数
 *
 * @param x 屏幕芯片选型，0是下半部分，1是上半部分
 * @param Dbyte 写入的数据
 */
void Write_Data_4bit(uint8_t x, uint8_t Dbyte)
{
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        Clr_162x_Wr(x);
        if((Dbyte >> (3 - i)) & 0x01)
        {
            Set_162x_Dat(x);
        }
        else
        {
            Clr_162x_Dat(x);
        }
        LCD_Delay();
        Set_162x_Wr(x);
        LCD_Delay();
    }
}

/**
 * @brief LCD初始化
 *
 */
void Lcd_Init(void)
{
    Set_162x_Cs(0);
    Set_162x_Wr(0);
    Set_162x_Dat(0);
    LCD_Delay();
    Clr_162x_Cs(0);//CS = 0;
    LCD_Delay();
    Write_Mode(0,0);//命令模式
    Write_Command(0,0x01);//Enable System
    Write_Command(0,0x03);//Enable Bias
    Write_Command(0,0x04);//Disable Timer
    Write_Command(0,0x05);//Disable WDT
    Write_Command(0,0x08);//Tone OFF
    Write_Command(0,0x18);//on-chip RC震荡
    Write_Command(0,0x29);//1/4Duty 1/3Bias
    Write_Command(0,0x80);//Disable IRQ
    Write_Command(0,0x40);//Tone Frequency 4kHZ
    Write_Command(0,0xE3);//Normal Mode
    Set_162x_Cs(0);//CS = 1;
	
    Set_162x_Cs(1);
    Set_162x_Wr(1);
    Set_162x_Dat(1);
    LCD_Delay();
    Clr_162x_Cs(1);//CS = 0;
    LCD_Delay();
    Write_Mode(1,0);//命令模式
    Write_Command(1,0x01);//Enable System
    Write_Command(1,0x03);//Enable Bias
    Write_Command(1,0x04);//Disable Timer
    Write_Command(1,0x05);//Disable WDT
    Write_Command(1,0x08);//Tone OFF
    Write_Command(1,0x18);//on-chip RC震荡
    Write_Command(1,0x29);//1/4Duty 1/3Bias
    Write_Command(1,0x80);//Disable IRQ
    Write_Command(1,0x40);//Tone Frequency 4kHZ
    Write_Command(1,0xE3);//Normal Mode
    Set_162x_Cs(1);//CS = 1;
    
    Lcd_All(0);//显示全部内容
    Lcd_All(1);//显示全部内容
//    HAL_Delay(1000);//延时1S
//	Lcd_Clr(0);//清屏
//    Lcd_Clr(1);//清屏
}

/**
 * @brief LCD清屏函数
 *
 * @param x 屏幕芯片选型，0是下半部分，1是上半部分
 */
void Lcd_Clr(uint8_t x)
{
    Write_Addr_Dat_N(x, 0x0, 0x00, 60);
}

/**
 * @brief LCD全显函数
 *
 * @param x 屏幕芯片选型，0是下半部分，1是上半部分
 */
void Lcd_All(uint8_t x)
{
    Write_Addr_Dat_N(x, 0x0, 0xFF, 60);
}

/**
 * @brief 屏幕显示
 *
 * @param x 屏幕芯片选型，0是下半部分，1是上半部分
 * @param _addr 地址值
 * @param _dat 数据
 * @param n 数据的个数
 */
void Write_Addr_Dat_N(uint8_t x, uint8_t _addr, uint8_t _dat, uint8_t n)
{
    int8_t i = 0;
    Clr_162x_Cs(x);//CS = 0;
    LCD_Delay();
    Write_Mode(x,1);
    Write_Address(x,_addr);
    for(i = 0; i < n; i++)
    {
        Write_Data_8bit(x,_dat);
    }
    Set_162x_Cs(x);//CS = 1;
}
