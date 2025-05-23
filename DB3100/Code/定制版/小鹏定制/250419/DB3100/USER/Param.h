#ifndef __PARAM_H__
#define	__PARAM_H__

#include "main.h"

/**********宏定义************/
#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC6

/**********结构体************/
struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//检查是否已经初始化的开始位
	uint8_t Flash_Check_End;//检查是否已经初始化的结束位
    
    uint8_t Mode_Val;//进入的系统A或者B
    
	int P_Param[11][2];
    
};

extern struct _Save_Param_ Param;

/**********全局变量声明******/
extern uint8_t Save_Param_En;

/**********局部变量声明******/
/**********全局函数**********/
void Param_Read(void);
void Sensor_Reset(void);
void Param_Save(void);
void Param_Save_Overtime(float dT);
#endif
