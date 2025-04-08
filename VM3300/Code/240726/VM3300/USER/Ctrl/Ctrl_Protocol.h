#ifndef __CTRL_PROTOCOL_H__
#define	__CTRL_PROTOCOL_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
typedef struct
{
	uint8_t Send_Check;//校验标志位
	uint8_t Send_Flag;//发送标志位
}Data_Flag_;
extern Data_Flag_ Data_Flag;//发送标志结构体

/**********全局变量声明******/
extern uint8_t Data_To_Send[50];//发送数据缓存

/**********全局函数**********/
void Rc_SendData_Fly(uint8_t *dataToSend, uint8_t length);//遥控器发送数据到飞机
void Rc_SendData_PC(uint8_t *dataToSend, uint8_t length);//遥控器发送数据到PC
void Rc_Data_Exchange(float dT);//Data_Exchange函数处理各种数据发送请求
void Data_Receive_Anl(uint8_t *data_buf,uint8_t num);//数据接受分析

#endif
