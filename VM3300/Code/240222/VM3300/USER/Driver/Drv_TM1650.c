#include "Drv_TM1650.h"

void TM1650_delay_us(unsigned short j)
{
  Delay_us(j);
}


void TM1650_Start(void)
{
	SDA_OUT();     
	TM1650_SDA_H;	  	  
	TM1650_SCL_H;
	TM1650_delay_us(4);
 	TM1650_SDA_L;
	TM1650_delay_us(4);
	TM1650_SCL_L;
}


void TM1650_Stop(void)
{
	SDA_OUT();
	TM1650_SCL_L;
	TM1650_SDA_L;
 	TM1650_delay_us(4);
	TM1650_SCL_H; 
	TM1650_delay_us(4);
	TM1650_SDA_H;
					   	
}


unsigned char  TM1650_Wait_Ack(void)
{
	unsigned char  ucErrTime=0;
	SDA_IN();       
	TM1650_SDA_H;TM1650_delay_us(1);	   
	TM1650_SCL_H;TM1650_delay_us(1);	 
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

void TM1650_Ack(void)
{
	TM1650_SCL_L;
	SDA_OUT();
	TM1650_SDA_L;
	TM1650_delay_us(4);
	TM1650_SCL_H;
	TM1650_delay_us(4);
	TM1650_SCL_L;
}
	    
void TM1650_NAck(void)
{
	TM1650_SCL_L;
	SDA_OUT();
	TM1650_SDA_H;
	TM1650_delay_us(4);
	TM1650_SCL_H;
	TM1650_delay_us(4);
	TM1650_SCL_L;
}					 				     
		



void TM1650_Send_Byte(unsigned char  oneByte)
{                        
    unsigned char  t;   
    SDA_OUT(); 	    
    TM1650_SCL_L;
    for(t=0;t<8;t++)
    {              
        if((oneByte&0x80)==0x80)   TM1650_SDA_H;
					else	                   TM1650_SDA_L;
        oneByte<<=1; 	  
		TM1650_delay_us(4);   
		TM1650_SCL_H;
		TM1650_delay_us(4); 
		TM1650_SCL_L;	
		TM1650_delay_us(4);
    }	 
}


unsigned char  TM1650_Read_Byte(void)
{
	unsigned char i,rekey=0;
	SDA_IN();
	for(i=0;i<8;i++ )
	{
		TM1650_SCL_L; 
		TM1650_delay_us(4);
		TM1650_SCL_H;
		rekey<<=1;
		if(TM1650_SDA_RD()) rekey++;   
		TM1650_delay_us(4); 
	}			

	
	return rekey;
}





void TM1650_SendCommand(unsigned char add,unsigned char dat)
{	
  TM1650_Start();
	TM1650_Send_Byte(add);
	TM1650_Wait_Ack();
	TM1650_Send_Byte(dat);
	TM1650_Wait_Ack();
	TM1650_Stop(); 
}

static uint8_t s_7number[10] = {0xF5,0x84,0xB3,0x97,0xC6,0x57,0x77,0x85,0xF7,0xD7};
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
  TM1650_Start();
	TM1650_Send_Byte(indexAddr);
	TM1650_Wait_Ack();
	TM1650_Send_Byte(numValue);
	TM1650_Wait_Ack();
	TM1650_Stop(); 
        
}

void TM1650_SetDisplay(uint8_t brightness)//
{
	TM1650_SendCommand(0x48,brightness*16 + 1*4 + 1);
}

void DisplayNumber_4BitDig(uint16_t Num)
{	uint16_t Numb;
	Numb = Num+10000;
	TM1650_SendDigData(3,Numb/1000%10);
	TM1650_SendDigData(2,Num/100%10);	
	TM1650_SendDigData(1,Num/10%10);
	TM1650_SendDigData(4,Num%10);
	
}

void TM1650_Init(void)
{
	TM1650_SCL_H;
	TM1650_SDA_H;
	TM1650_SetDisplay(brighting_2);
	DisplayNumber_4BitDig(1234);
}

