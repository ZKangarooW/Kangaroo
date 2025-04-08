#include "Speed.h"

/*
*****************************************************************
 * 函数原型：void Speed_Receive(uint8_t data)
 * 功    能：速度数据接收
 * 输    入：串口1接受到的数据
 * 参    数：uint8_t data
*****************************************************************
*/
void Speed_Receive(uint8_t data)
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
                    Speed.Rel = speed*55000/32767;
				}
			}
		break;
			
		default:
			Step = Data_Cnt = 0;//清零
		break;
	}
}
