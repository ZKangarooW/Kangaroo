#include "Drv_HT1623.h"

/*
*****************************************************************
 * ����ԭ�ͣ�static void delay(uint16_t time)
 * ��    �ܣ�us��ʱ
 * ��    ��: time ��ʱ��
 * ��    ����uint16_t time
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void delay(uint16_t time)
{
    unsigned char a;
    for(a = 100; a > 0; a--);
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void write_mode(unsigned char MODE)
 * ��    �ܣ�д��ģʽ,����or����
 * ��    ��: MODE ������or����
 * ��    ����unsigned char MODE
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void write_command(unsigned char Cbyte)
 * ��    �ܣ�LCD ����д�뺯��
 * ��    ��: Cbyte������������
 * ��    ����unsigned char Cbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void write_address(unsigned char Abyte)
 * ��    �ܣ�LCD ��ַд�뺯��
 * ��    ��: Abyte����ַ
 * ��    ����unsigned char Abyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void write_data_8bit(unsigned char Dbyte)
 * ��    �ܣ�LCD 8bit����д�뺯��
 * ��    ��: Dbyte������
 * ��    ����unsigned char Dbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�void write_data_4bit(unsigned char Dbyte)
 * ��    �ܣ�LCD 4bit����д�뺯��
 * ��    ��: Dbyte������
 * ��    ����unsigned char Dbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�void Lcd_Init(void)
 * ��    �ܣ�LCD ��ʼ������lcd��������ʼ������
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
    write_mode(0);//����ģʽ
    write_command(0x01);//Enable System
    write_command(0x03);//Enable Bias
    write_command(0x04);//Disable Timer
    write_command(0x05);//Disable WDT
    write_command(0x08);//Tone OFF
    write_command(0x18);//on-chip RC��
    write_command(0x29);//1/4Duty 1/3Bias
    write_command(0x80);//Disable IRQ
    write_command(0x40);//Tone Frequency 4kHZ
    write_command(0xE3);//Normal Mode
    Set_1625_Cs;//CS = 1;
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
    Write_Addr_Dat_N(0x0, 0xff, 60);
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
