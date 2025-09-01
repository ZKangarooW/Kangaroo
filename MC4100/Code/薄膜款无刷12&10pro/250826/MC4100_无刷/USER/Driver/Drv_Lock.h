#ifndef __DRV_LOCK_H__
#define	__DRV_LOCK_H__

#include "include.h"

/**********宏定义************/
#define Lock_ON HAL_GPIO_WritePin(UC_DCT_GPIO_Port,UC_DCT_Pin,GPIO_PIN_SET)//Lock1打开
#define Lock_OFF HAL_GPIO_WritePin(UC_DCT_GPIO_Port,UC_DCT_Pin,GPIO_PIN_RESET)//Lock1关闭

/**********结构体************/
/**********全局变量声明******/
extern uint8_t Lock_Status;//电磁铁的状态

/**********局部变量声明******/
/**********全局函数**********/
void Ctrl_Lock(float dT);//电磁铁控制

#endif
