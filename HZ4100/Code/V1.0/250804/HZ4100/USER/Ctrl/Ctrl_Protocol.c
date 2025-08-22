#include "Ctrl_Protocol.h"

/**********结构体************/
uint8_t Receive_ok;
/**********全局变量声明******/
uint8_t app_CalcCRC8(uint8_t *ptr, uint8_t len) {
    static uint8_t crc;
    static uint8_t i;
    crc = 0;
    while (len--) {
        crc ^= *ptr++;
        for (i = 0; i < 8; i++) {
            if (crc & 0x01)
                crc = (crc >> 1) ^ 0x8C;
            else
                crc >>= 1;
    }
  }
  return crc;
}

/*
*****************************************************************
 * 函数原型：void Speed_Receive(uint8_t data)
 * 功    能：速度数据接收
 * 输    入：串口1接受到的数据
 * 参    数：uint8_t data
*****************************************************************
*/
void Data_Receive(uint8_t data)
{
    static uint8_t RxBuffer[9];
    static uint8_t Data_Cnt = 0;
	static uint8_t Step = 0;
	
    uint8_t crc1 = 0;
    uint16_t speed;
    
	switch(Step)
	{
		case 0:
			if(data==0xA5)//包头
			{
				Step=1;
				RxBuffer[Data_Cnt++]=data;
			}else Step = Data_Cnt = 0;
		break;
			
		case 1:
			RxBuffer[Data_Cnt++]=data;
		
			if(Data_Cnt==9)
			{
                crc1 = app_CalcCRC8(RxBuffer, Data_Cnt-1);
                Step = Data_Cnt = 0;
				if(crc1 == RxBuffer[8])
				{
                    speed = (uint16_t)(RxBuffer[5]<<8)|RxBuffer[4];//测量距离
                    Speed.uart_Rel = speed*55000/32767;
                    Temp.Rel = RxBuffer[6]*10;
                    Receive_ok = 1;
                    
				}
			}
		break;
			
		default:
			Step = Data_Cnt = 0;//清零
		break;
	}
}
