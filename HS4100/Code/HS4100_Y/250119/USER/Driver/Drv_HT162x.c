#include "Drv_HT162x.h"

/*
*****************************************************************
 * 函数原型：static void LCD_Delay(void)
 * 功    能：LCD_us延时
 * 调    用：内部调用
*****************************************************************
*/
static void LCD_Delay(void)
{
    unsigned char a;
    for(a = 100; a > 0; a--);
}

/*
*****************************************************************
 * 函数原型：static void Write_Mode(unsigned char MODE)
 * 功    能：写入模式,数据or命令
 * 输    入: MODE ：数据or命令
 * 参    数：unsigned char MODE
 * 调    用：内部调用
*****************************************************************
*/
static void Write_Mode(unsigned char MODE)
{
    LCD_Delay();
    Clr_162x_Wr;//RW = 0;
    LCD_Delay();
    Set_162x_Dat;//DA = 1;
    Set_162x_Wr;//RW = 1;
    LCD_Delay();
    Clr_162x_Wr;//RW = 0;
    LCD_Delay();
    Clr_162x_Dat;//DA = 0;
    LCD_Delay();
    Set_162x_Wr;//RW = 1;
    LCD_Delay();
    Clr_162x_Wr;//RW = 0;
    LCD_Delay();
    if (0 == MODE)
    {
        Clr_162x_Dat;//DA = 0;
    }
    else
    {
        Set_162x_Dat;//DA = 1;
    }
    LCD_Delay();
    Set_162x_Wr;//RW = 1;
    LCD_Delay();
}

/*
*****************************************************************
 * 函数原型：static void Write_Command(unsigned char Cbyte)
 * 功    能：LCD 命令写入函数
 * 输    入: Cbyte：控制命令字
 * 参    数：unsigned char Cbyte
 * 调    用：内部调用
*****************************************************************
*/
static void Write_Command(unsigned char Cbyte)
{
    unsigned char i = 0;
    for (i = 0; i < 8; i++)
    {
        Clr_162x_Wr;
        if ((Cbyte >> (7 - i)) & 0x01)
        {
            Set_162x_Dat;
        }
        else
        {
            Clr_162x_Dat;
        }
        LCD_Delay();
        Set_162x_Wr;
        LCD_Delay();
    }
    Clr_162x_Wr;
    LCD_Delay();
    Clr_162x_Dat;
    Set_162x_Wr;
    LCD_Delay();
}

/*
*****************************************************************
 * 函数原型：static void Write_Address(unsigned char Abyte)
 * 功    能：LCD 地址写入函数
 * 输    入: Abyte：地址
 * 参    数：unsigned char Abyte
 * 调    用：内部调用
*****************************************************************
*/
static void Write_Address(unsigned char Abyte)
{
    unsigned char i = 0;
    Abyte = Abyte << 1;
    for (i = 0; i < 6; i++)
    {
        Clr_162x_Wr;
        if ((Abyte >> (6 - i)) & 0x01)
        {
            Set_162x_Dat;
        }
        else
        {
            Clr_162x_Dat;
        }
        LCD_Delay();
        Set_162x_Wr;
        LCD_Delay();
    }
}

/*
*****************************************************************
 * 函数原型：static void Write_Data_8bit(unsigned char Dbyte)
 * 功    能：LCD 8bit数据写入函数
 * 输    入: Dbyte：数据
 * 参    数：unsigned char Dbyte
 * 调    用：内部调用
*****************************************************************
*/
static void Write_Data_8bit(unsigned char Dbyte)
{
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        Clr_162x_Wr;
        if ((Dbyte >> (7 - i)) & 0x01)
        {
            Set_162x_Dat;
        }
        else
        {
            Clr_162x_Dat;
        }
        LCD_Delay();
        Set_162x_Wr;
        LCD_Delay();
    }
}

/*
*****************************************************************
 * 函数原型：void Write_Data_4bit(unsigned char Dbyte)
 * 功    能：LCD 4bit数据写入函数
 * 输    入: Dbyte：数据
 * 参    数：unsigned char Dbyte
 * 调    用：内部调用
*****************************************************************
*/
void Write_Data_4bit(unsigned char Dbyte)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        Clr_162x_Wr;
        if ((Dbyte >> (3 - i)) & 0x01)
        {
            Set_162x_Dat;
        }
        else
        {
            Clr_162x_Dat;
        }
        LCD_Delay();
        Set_162x_Wr;
        LCD_Delay();
    }
}

/*
*****************************************************************
 * 函数原型：void Lcd_Init(void)
 * 功    能：LCD 初始化，对lcd自身做初始化设置
https://wenku.baidu.com/view/2859970bdd88d0d232d46a57.html?fr=aladdin664466&ind=1&aigcsid=63568&qtype=0&lcid=1&queryKey=ht1622&verifyType=&_wkts_=1750222967808&bdQuery=HT1622&needWelcomeRecommand=1&unResetStore=1&ILK=17502231-0465-0213-0221-982780297686
*****************************************************************
*/
void Lcd_Init(void)
{
    Set_162x_Cs;
    Set_162x_Wr;
    Set_162x_Dat;
    LCD_Delay();
    Clr_162x_Cs;//CS = 0;
    LCD_Delay();
    Write_Mode(0);//命令模式
    Write_Command(0x01);//打开系统振荡器
    Write_Command(0x03);//打开液晶显示屏 关闭0x02
    Write_Command(0x04);//禁止时基输出  使能0x06
    Write_Command(0x05);//禁止WDT超时输出 使能0x07
    Write_Command(0x08);//关闭音频输出
    Write_Command(0x18);//系统时钟源，片上RC震荡 0x1C外部时钟源
    Write_Command(0x80);//禁止IRQ输出，使能IRQ输出
    Write_Command(0x40);//音频输出频率4kHZ，0x60 2KHZ
	Write_Command(0xA6);//时基时钟输出64HZ 0xA0：1HZ；0xA1：2HZ；0xA2：4HZ
//										   0xA3：8HZ；0xA4：16HZ；0xA5：32HZ；0xA7：128Hz
    Write_Command(0xE3);//正常模式
    Set_162x_Cs;//CS = 1;
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1);//背光pwm
	 
	Lcd_All();
	HAL_Delay(1000);
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
    Write_Addr_Dat_N(0x0, 0xFF, 60);
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
    Clr_162x_Cs;//CS = 0;
    LCD_Delay();
    Write_Mode(1);
    Write_Address(_addr);
    for (i = 0; i < n; i++)
    {
        Write_Data_8bit(_dat);
    }
    Set_162x_Cs;//CS = 1;
}
