#ifndef __CTRL_PROTOCOL_H__
#define	__CTRL_PROTOCOL_H__

#include "include.h"

/**********宏定义************/
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

/**********结构体************/
typedef struct
{
	uint8_t Send_Data;//发送数据
}_Data_Flag_;
extern _Data_Flag_ Data_Flag;//发送标志结构体

/**********全局变量声明******/
extern uint8_t Data_To_Send[10];//发送数据缓存

/**********全局函数**********/
void Data_Exchange(float dT);
uint8_t app_CalcCRC8(uint8_t *ptr, uint8_t len);

#endif
