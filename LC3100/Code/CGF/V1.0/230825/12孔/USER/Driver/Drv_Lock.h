#ifndef __DRV_LOCK_H__
#define	__DRV_LOCK_H__

#include "include.h"

/**********宏定义************/
#define Lock1_ON HAL_GPIO_WritePin(UC_DCT1_GPIO_Port,UC_DCT1_Pin,GPIO_PIN_SET)//Lock1打开
#define Lock1_OFF HAL_GPIO_WritePin(UC_DCT1_GPIO_Port,UC_DCT1_Pin,GPIO_PIN_RESET)//Lock1关闭
#define Lock2_ON HAL_GPIO_WritePin(UC_DCT2_GPIO_Port,UC_DCT2_Pin,GPIO_PIN_SET)//Lock1打开
#define Lock2_OFF HAL_GPIO_WritePin(UC_DCT2_GPIO_Port,UC_DCT2_Pin,GPIO_PIN_RESET)//Lock1关闭

/**********结构体************/
/**********全局变量声明******/
extern uint8_t Lock1_Status,Lock2_Status;//电磁铁的状态

/**********全局函数**********/
void Ctrl_Lock(float dT);//电磁铁控制

#endif
