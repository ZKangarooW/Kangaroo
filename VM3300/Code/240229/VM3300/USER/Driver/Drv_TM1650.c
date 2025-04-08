#include "Drv_TM1650.h"

/**********�ֲ���������******/
static uint8_t s_7number[10] = {0xF5,0x84,0xB3,0x97,0xC6,0x57,0x77,0x85,0xF7,0xD7};

/**
 * @brief TM1650��ʼ����
 *
 */
void TM1650_Start(void)
{
	SDA_OUT();     
	TM1650_SDA_H;	  	  
	TM1650_SCL_H;
	Delay_us(4);
 	TM1650_SDA_L;
	Delay_us(4);
	TM1650_SCL_L;
	Delay_us(4);
}

/**
 * @brief TM1650ֹͣ����
 *
 */
void TM1650_Stop(void)
{
	SDA_OUT();
	TM1650_SDA_L;
	TM1650_SCL_H;
 	Delay_us(4);
	TM1650_SDA_H;
}

/**
 * @brief TM1650�ȴ���Ӧ
 *
 */
uint8_t TM1650_Wait_Ack(void)
{
	uint8_t ucErrTime=0;    
	TM1650_SDA_H;
	Delay_us(4);
	SDA_IN();	   
	TM1650_SCL_H;
	Delay_us(4);	 
	while(TM1650_SDA_RD())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			TM1650_Stop();
			return 1;
		}
	}
	TM1650_SCL_L;	   
	return 0;  
} 

/**
 * @brief TM1650Ack�ź�
 *
 */
void TM1650_Ack(void)
{
	TM1650_SCL_L;
	SDA_OUT();
	TM1650_SDA_L;
	Delay_us(4);
	TM1650_SCL_H;
	Delay_us(4);
	TM1650_SCL_L;
}

/**
 * @brief TM1650NAck�ź�
 *
 */	    
void TM1650_NAck(void)
{
	TM1650_SCL_L;
	SDA_OUT();
	TM1650_SDA_H;
	Delay_us(4);
	TM1650_SCL_H;
	Delay_us(4);
	TM1650_SCL_L;
}					 				     

/**
 * @brief TM1650����һ���ֽ�����
 *
 * @param oneByte �ֽ�ֵ
 */
void TM1650_Send_Byte(uint8_t oneByte)
{                        
    uint8_t t;   
    SDA_OUT(); 	    
    TM1650_SCL_L;
	TM1650_SDA_L;
    for(t=0;t<8;t++)
    {     
		TM1650_SCL_L;	
		Delay_us(2);		
        if((oneByte&0x80)==0x80)   
		{
			TM1650_SDA_H;
			Delay_us(4);
		}
		else	
		{
			TM1650_SDA_L;
			Delay_us(4);
		}
        oneByte<<=1; 	  
		Delay_us(4);   
		TM1650_SCL_H;
		Delay_us(4); 
		TM1650_SCL_L;	
		Delay_us(4);
    }
	TM1650_SCL_L;
    TM1650_SDA_L;
}

/**
 * @brief TM1650��һ���ֽ�����
 *
 */
uint8_t TM1650_Read_Byte(void)
{
	uint8_t i,rekey=0;
	SDA_IN();
	for(i=0;i<8;i++ )
	{
		TM1650_SCL_L; 
		Delay_us(4);
		TM1650_SCL_H;
		rekey<<=1;
		if(TM1650_SDA_RD()) rekey++;   
		Delay_us(4); 
	}			
	return rekey;
}

/**
 * @brief TM1650��������
 *
 * @param add ��ַ
 * @param dat �ֽ�ֵ
 */
void TM1650_SendCommand(uint8_t add,uint8_t dat)
{	
	TM1650_Start();
	TM1650_Send_Byte(add);
	TM1650_Wait_Ack();
	TM1650_Send_Byte(dat);
	TM1650_Wait_Ack();
	TM1650_Stop(); 
}

/**
 * @brief TM1650��ʾ����
 *
 * @param index Ҫ���õĵڼ��������
 * @param num ���õ���ֵ
 */
void TM1650_SendDigData(uint16_t index,uint16_t num)
{	
	uint8_t indexAddr =  0;
	uint8_t numValue  =  0;
	switch(index)
	{
		case 1:indexAddr = 0x68;break;
		case 2:indexAddr = 0x6A;break;
		case 3:indexAddr = 0x6C;break;
		case 4:indexAddr = 0x6E;break;
		default:break;
	}	
	numValue = s_7number[num];
//	numValue = num;
	TM1650_Start();
	TM1650_Send_Byte(indexAddr);
	TM1650_Wait_Ack();
	TM1650_Send_Byte(numValue);
	TM1650_Wait_Ack();
	TM1650_Stop(); 
}

/**
 * @brief TM1650��ʾ����
 *
 * @param brightness ����1��8�궨��
 */
void TM1650_SetDisplay(uint8_t brightness)
{
	TM1650_SendCommand(0x48,brightness*16 + 1*4 + 1);
}

/**
 * @brief TM1650��ʾλ��ֵ����
 *
 * @param Num ��ֵ
 */
void DisplayNumber_4BitDig(uint16_t Num)
{	uint16_t Numb;
	Numb = Num+10000;
	
//	TM1650_SendDigData(3,0x01);
	TM1650_SendDigData(3,Numb/1000%10);
	TM1650_SendDigData(2,Num/100%10);	
	TM1650_SendDigData(1,Num/10%10);
	TM1650_SendDigData(4,Num%10);
}

/**
 * @brief TM1650������ʼ��
 *
 */
void DrvTM1650_Init(void)
{
	TM1650_SCL_H;
	TM1650_SDA_H;
	HAL_Delay(20);//���20ms��ʱ���ӿ�����������
	TM1650_SetDisplay(brighting_1);
}

