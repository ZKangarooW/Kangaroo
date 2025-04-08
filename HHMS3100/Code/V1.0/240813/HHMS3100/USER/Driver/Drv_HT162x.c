#include "Drv_HT162x.h"

/**
 * @brief д��ģʽ������or����
 *
 * @param x ��ĻоƬѡ�ͣ�0���°벿�֣�1���ϰ벿��
 * @param MODE ����or����
 */
static void Write_Mode(uint8_t x,uint8_t MODE)
{
    Delay_us(4);
    Clr_162x_Wr(x);//RW = 0;
    Delay_us(4);
    Set_162x_Dat(x);//DA = 1;
    Set_162x_Wr(x);//RW = 1;
    Delay_us(4);
    Clr_162x_Wr(x);//RW = 0;
    Delay_us(4);
    Clr_162x_Dat(x);//DA = 0;
    Delay_us(4);
    Set_162x_Wr(x);//RW = 1;
    Delay_us(4);
    Clr_162x_Wr(x);//RW = 0;
    Delay_us(4);
    if(0 == MODE)
    {
        Clr_162x_Dat(x);//DA = 0;
    }
    else
    {
        Set_162x_Dat(x);//DA = 1;
    }
    Delay_us(4);
    Set_162x_Wr(x);//RW = 1;
    Delay_us(4);
}

/**
 * @brief LCD����д�뺯��
 *
 * @param x ��ĻоƬѡ�ͣ�0���°벿�֣�1���ϰ벿��
 * @param Cbyte ����������
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
        Delay_us(4);
        Set_162x_Wr(x);
        Delay_us(4);
    }
    Clr_162x_Wr(x);
    Delay_us(4);
    Clr_162x_Dat(x);
    Set_162x_Wr(x);
    Delay_us(4);
}

/**
 * @brief LCD��ַд�뺯��
 *
 * @param x ��ĻоƬѡ�ͣ�0���°벿�֣�1���ϰ벿��
 * @param Abyte ��ַ
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
        Delay_us(4);
        Set_162x_Wr(x);
        Delay_us(4);
    }
}

/**
 * @brief ����д�뺯��
 *
 * @param x ��ĻоƬѡ�ͣ�0���°벿�֣�1���ϰ벿��
 * @param Dbyte д�������
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
        Delay_us(4);
        Set_162x_Wr(x);
        Delay_us(4);
    }
}

/**
 * @brief ����д�뺯��
 *
 * @param x ��ĻоƬѡ�ͣ�0���°벿�֣�1���ϰ벿��
 * @param Dbyte д�������
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
        Delay_us(4);
        Set_162x_Wr(x);
        Delay_us(4);
    }
}

/**
 * @brief LCD��ʼ��
 *
 */
void Lcd_Init(void)
{
    HAL_GPIO_WritePin(LED_POR_GPIO_Port, LED_POR_Pin, GPIO_PIN_SET);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    
    Set_162x_Cs(IC2);
    Set_162x_Wr(IC2);
    Set_162x_Dat(IC2);
    Delay_us(4);
    Clr_162x_Cs(IC2);//CS = 0;
    Delay_us(4);
    Write_Mode(IC2,0);//����ģʽ
    Write_Command(IC2,0x01);//Enable System
    Write_Command(IC2,0x03);//Enable Bias
    Write_Command(IC2,0x04);//Disable Timer
    Write_Command(IC2,0x05);//Disable WDT
    Write_Command(IC2,0x08);//Tone OFF
    Write_Command(IC2,0x18);//on-chip RC��
    Write_Command(IC2,0x29);//1/4Duty 1/3Bias
    Write_Command(IC2,0x80);//Disable IRQ
    Write_Command(IC2,0x40);//Tone Frequency 4kHZ
    Write_Command(IC2,0xE3);//Normal Mode
    Set_162x_Cs(IC2);//CS = 1;
	
    Set_162x_Cs(IC1);
    Set_162x_Wr(IC1);
    Set_162x_Dat(IC1);
    Delay_us(4);
    Clr_162x_Cs(IC1);//CS = 0;
    Delay_us(4);
    Write_Mode(IC1,0);//����ģʽ
    Write_Command(IC1,0x01);//Enable System
    Write_Command(IC1,0x03);//Enable Bias
    Write_Command(IC1,0x04);//Disable Timer
    Write_Command(IC1,0x05);//Disable WDT
    Write_Command(IC1,0x08);//Tone OFF
    Write_Command(IC1,0x18);//on-chip RC��
    Write_Command(IC1,0x29);//1/4Duty 1/3Bias
    Write_Command(IC1,0x80);//Disable IRQ
    Write_Command(IC1,0x40);//Tone Frequency 4kHZ
    Write_Command(IC1,0xE3);//Normal Mode
    Set_162x_Cs(IC1);//CS = 1;
    
    Lcd_All(IC2);//��ʾȫ������
    Lcd_All(IC1);//��ʾȫ������
    Delay_ms(500);
	Lcd_Clr(IC2);//����
    Lcd_Clr(IC1);//����
}

/**
 * @brief LCD��������
 *
 * @param x ��ĻоƬѡ�ͣ�0���°벿�֣�1���ϰ벿��
 */
void Lcd_Clr(uint8_t x)
{
    Write_Addr_Dat_N(x, 0x0, 0x00, 60);
}

/**
 * @brief LCDȫ�Ժ���
 *
 * @param x ��ĻоƬѡ�ͣ�0���°벿�֣�1���ϰ벿��
 */
void Lcd_All(uint8_t x)
{
    Write_Addr_Dat_N(x, 0x0, 0xFF, 60);
}

/**
 * @brief ��Ļ��ʾ
 *
 * @param x ��ĻоƬѡ�ͣ�0���°벿�֣�1���ϰ벿��
 * @param _addr ��ֵַ
 * @param _dat ����
 * @param n ���ݵĸ���
 */
void Write_Addr_Dat_N(uint8_t x, uint8_t _addr, uint8_t _dat, uint8_t n)
{
    int8_t i = 0;
    Clr_162x_Cs(x);//CS = 0;
    Delay_us(4);
    Write_Mode(x,1);
    Write_Address(x,_addr);
    for(i = 0; i < n; i++)
    {
        Write_Data_8bit(x,_dat);
    }
    Set_162x_Cs(x);//CS = 1;
}
