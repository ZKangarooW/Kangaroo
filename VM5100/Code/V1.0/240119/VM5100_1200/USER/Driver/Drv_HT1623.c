#include "Drv_HT1623.h"

/*
*****************************************************************
 * 函数原型：static void delay(uint16_t time)
 * 功    能：us延时
 * 输    入: time ：时间
 * 参    数：uint16_t time
 * 调    用：内部调用
*****************************************************************
*/
static void delay(uint16_t time)
{
    unsigned char a;
    for(a = 100; a > 0; a--);
}

/*
*****************************************************************
 * 函数原型：static void write_mode(unsigned char MODE)
 * 功    能：写入模式,数据or命令
 * 输    入: MODE ：数据or命令
 * 参    数：unsigned char MODE
 * 调    用：内部调用
*****************************************************************
*/
static void write_mode(unsigned char MODE)
{
    delay(10);
    Clr_1625_Wr;//RW = 0;
    delay(10);
    Set_1625_Dat;//DA = 1;
    Set_1625_Wr;//RW = 1;
    delay(10);
    Clr_1625_Wr;//RW = 0;
    delay(10);
    Clr_1625_Dat;
    delay(10);//DA = 0;
    Set_1625_Wr;//RW = 1;
    delay(10);
    Clr_1625_Wr;//RW = 0;
    delay(10);
    if (0 == MODE)
    {
        Clr_1625_Dat;//DA = 0;
    }
    else
    {
        Set_1625_Dat;//DA = 1;
    }
    delay(10);
    Set_1625_Wr;//RW = 1;
    delay(10);
}

/*
*****************************************************************
 * 函数原型：static void write_command(unsigned char Cbyte)
 * 功    能：LCD 命令写入函数
 * 输    入: Cbyte：控制命令字
 * 参    数：unsigned char Cbyte
 * 调    用：内部调用
*****************************************************************
*/
static void write_command(unsigned char Cbyte)
{
    unsigned char i = 0;
    for (i = 0; i < 8; i++)
    {
        Clr_1625_Wr;
        //Delay_us(10);
        if ((Cbyte >> (7 - i)) & 0x01)
        {
            Set_1625_Dat;
        }
        else
        {
            Clr_1625_Dat;
        }
        delay(10);
        Set_1625_Wr;
        delay(10);
    }
    Clr_1625_Wr;
    delay(10);
    Clr_1625_Dat;
    Set_1625_Wr;
    delay(10);
}

/*
*****************************************************************
 * 函数原型：static void write_address(unsigned char Abyte)
 * 功    能：LCD 地址写入函数
 * 输    入: Abyte：地址
 * 参    数：unsigned char Abyte
 * 调    用：内部调用
*****************************************************************
*/
static void write_address(unsigned char Abyte)
{
    unsigned char i = 0;
    Abyte = Abyte << 1;
    for (i = 0; i < 6; i++)
    {
        Clr_1625_Wr;
        if ((Abyte >> (6 - i)) & 0x01)
        {
            Set_1625_Dat;
        }
        else
        {
            Clr_1625_Dat;
        }
        delay(10);
        Set_1625_Wr;
        delay(10);
    }
}

/*
*****************************************************************
 * 函数原型：static void write_data_8bit(unsigned char Dbyte)
 * 功    能：LCD 8bit数据写入函数
 * 输    入: Dbyte：数据
 * 参    数：unsigned char Dbyte
 * 调    用：内部调用
*****************************************************************
*/
static void write_data_8bit(unsigned char Dbyte)
{
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        Clr_1625_Wr;
        if ((Dbyte >> (7 - i)) & 0x01)
        {
            Set_1625_Dat;
        }
        else
        {
            Clr_1625_Dat;
        }
        delay(10);
        Set_1625_Wr;
        delay(10);
    }
}

/*
*****************************************************************
 * 函数原型：void write_data_4bit(unsigned char Dbyte)
 * 功    能：LCD 4bit数据写入函数
 * 输    入: Dbyte：数据
 * 参    数：unsigned char Dbyte
 * 调    用：内部调用
*****************************************************************
*/
void write_data_4bit(unsigned char Dbyte)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        Clr_1625_Wr;
        if ((Dbyte >> (3 - i)) & 0x01)
        {
            Set_1625_Dat;
        }
        else
        {
            Clr_1625_Dat;
        }
        delay(10);
        Set_1625_Wr;
        delay(10);
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
    delay(500);
    Clr_1625_Cs;//CS = 0;
    delay(10);
    write_mode(0);//命令模式
    write_command(0x01);//Enable System
    write_command(0x03);//Enable Bias
    write_command(0x04);//Disable Timer
    write_command(0x05);//Disable WDT
    write_command(0x08);//Tone OFF
    write_command(0x18);//on-chip RC震荡
    write_command(0x29);//1/4Duty 1/3Bias
    write_command(0x80);//Disable IRQ
    write_command(0x40);//Tone Frequency 4kHZ
    write_command(0xE3);//Normal Mode
    Set_1625_Cs;//CS = 1;
}

/*
*****************************************************************
 * 函数原型：void Lcd_Clr(void)
 * 功    能：LCD 清屏函数
*****************************************************************
*/
void Lcd_Clr(void)
{
    Write_Addr_Dat_N(0x0, 0x00, 60);
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
}

/*
*****************************************************************
 * 函数原型：void Write_Addr_Dat_N(unsigned char _addr, unsigned char _dat, unsigned char n)
 * 功    能：屏幕显示
 * 输    入: _addr：地址  char _dat：数据 n：个数
 * 参    数：unsigned char _addr, unsigned char _dat, unsigned char n
*****************************************************************
*/
void Write_Addr_Dat_N(unsigned char _addr, unsigned char _dat, unsigned char n)
{
    unsigned char i = 0;
    Clr_1625_Cs;//CS = 0;
    delay(10);
    write_mode(1);
    write_address(_addr);
    for (i = 0; i < n; i++)
    {
        write_data_8bit(_dat);
    }
    Set_1625_Cs;//CS = 1;
}
