#include "Drv_HT1623.h"

/*
*****************************************************************
 * ����ԭ�ͣ�static void LCD_Delay(void)
 * ��    �ܣ�LCD_us��ʱ
 * ��    �ã��ڲ�����
*****************************************************************
*/
static void LCD_Delay(void)
{
    uint8_t a;
    for(a = 100; a > 0; a--);
}

/*
*****************************************************************
 * ����ԭ�ͣ�static void Write_Mode(uint8_t MODE)
 * ��    �ܣ�д��ģʽ,����or����
 * ��    ��: MODE ������or����
 * ��    ����uint8_t MODE
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void Write_Command(uint8_t Cbyte)
 * ��    �ܣ�LCD ����д�뺯��
 * ��    ��: Cbyte������������
 * ��    ����uint8_t Cbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void Write_Address(uint8_t Abyte)
 * ��    �ܣ�LCD ��ַд�뺯��
 * ��    ��: Abyte����ַ
 * ��    ����uint8_t Abyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�static void Write_Data_8bit(uint8_t Dbyte)
 * ��    �ܣ�LCD 8bit����д�뺯��
 * ��    ��: Dbyte������
 * ��    ����uint8_t Dbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�void Write_Data_4bit(uint8_t Dbyte)
 * ��    �ܣ�LCD 4bit����д�뺯��
 * ��    ��: Dbyte������
 * ��    ����uint8_tr Dbyte
 * ��    �ã��ڲ�����
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
 * ����ԭ�ͣ�void Lcd_Init(void)
 * ��    �ܣ�LCD ��ʼ������lcd��������ʼ������
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
    Set_1625_Cs;//CS = 1;
	
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	 __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1,60);//�����pwm
	 
	Lcd_All();
	Temp_Init();//������ʾ�¶�
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
    Write_Addr_Dat_N(0x0, 0x00, 50);
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
	Write_Addr_Dat_N(0, 0x0f, 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Write_Addr_Dat_N(uint8_t _addr, uint8_tr _dat, uint8_t n)
 * ��    �ܣ���Ļ��ʾ
 * ��    ��: _addr����ַ  char _dat������ n������
 * ��    ����uint8_t _addr, uint8_t _dat, uint8_t n
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
