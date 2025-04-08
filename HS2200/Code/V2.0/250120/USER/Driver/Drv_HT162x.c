#include "Drv_HT162x.h"

/*
*****************************************************************
 * ����ԭ�ͣ�static void LCD_Delay(void)
 * ��    �ܣ�LCD_us��ʱ
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void LCD_Delay(void)
{
    unsigned char a;
    for(a = 100; a > 0; a--);
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Write_Mode(unsigned char MODE)
 * ��    �ܣ�д��ģʽ,����or����
 * ��    ��: MODE ������or����
 * ��    ����unsigned char MODE
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void Write_Command(unsigned char Cbyte)
 * ��    �ܣ�LCD ����д�뺯��
 * ��    ��: Cbyte������������
 * ��    ����unsigned char Cbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void Write_Address(unsigned char Abyte)
 * ��    �ܣ�LCD ��ַд�뺯��
 * ��    ��: Abyte����ַ
 * ��    ����unsigned char Abyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void Write_Data_8bit(unsigned char Dbyte)
 * ��    �ܣ�LCD 8bit����д�뺯��
 * ��    ��: Dbyte������
 * ��    ����unsigned char Dbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�void Write_Data_4bit(unsigned char Dbyte)
 * ��    �ܣ�LCD 4bit����д�뺯��
 * ��    ��: Dbyte������
 * ��    ����unsigned char Dbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�void Lcd_Init(void)
 * ��    �ܣ�LCD ��ʼ������lcd��������ʼ������
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
    Write_Mode(0);//����ģʽ
    Write_Command(0x01);//Enable System
    Write_Command(0x03);//Enable Bias
    Write_Command(0x04);//Disable Timer
    Write_Command(0x05);//Disable WDT
    Write_Command(0x08);//Tone OFF
    Write_Command(0x18);//on-chip RC��
    Write_Command(0x29);//1/4Duty 1/3Bias
    Write_Command(0x80);//Disable IRQ
    Write_Command(0x40);//Tone Frequency 4kHZ
    Write_Command(0xE3);//Normal Mode
    Set_162x_Cs;//CS = 1;
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 180);//����pwm
	 
	Lcd_All();
	HAL_Delay(1000);
	Lcd_Clr();
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Lcd_Clr(void)
 * ��    �ܣ�LCD ��������
*****************************************************************
*/
void Lcd_Clr(void)
{
    Write_Addr_Dat_N(0x0, 0x00, 60);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Lcd_All(void)
 * ��    �ܣ�LCD ȫ��ʾ����
*****************************************************************
*/
void Lcd_All(void)
{
    Write_Addr_Dat_N(0x0, 0xFF, 60);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Write_Addr_Dat_N(unsigned char _addr, unsigned char _dat, unsigned char n)
 * ��    �ܣ���Ļ��ʾ
 * ��    ��: _addr����ַ  char _dat������ n������
 * ��    ����unsigned char _addr, unsigned char _dat, unsigned char n
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
