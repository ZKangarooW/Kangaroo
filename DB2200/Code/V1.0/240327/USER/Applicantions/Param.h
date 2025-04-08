#ifndef __PARAM_H__
#define	__PARAM_H__

#include "include.h"

/**********宏定义************/
#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xCC

/**********结构体************/
struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//检查飞控是否已经初始化的开始位
	uint8_t Flash_Check_End;//检查飞控是否已经初始化的结束位
	int P_Param[10][2];
};

extern struct _Save_Param_ Param;

/**********全局变量声明******/
extern uint8_t Save_Param_En;

/**********局部变量声明******/
/**********全局函数**********/
void Param_Read(void);
void Sensor_Reset(void);
void Param_Save(void);

#endif
