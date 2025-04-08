#ifndef __DRV_HALL_H__
#define __DRV_HALL_H__

#include "include.h"

/**********宏定义************/
#define Read_HALL1 HAL_GPIO_ReadPin(HALL1_GPIO_Port, HALL1_Pin)
#define Read_HALL2 HAL_GPIO_ReadPin(HALL2_GPIO_Port, HALL2_Pin)

/**********结构体************/
/**********全局变量声明*******/
extern uint8_t HALL1, HALL2; // 霍尔1和霍尔2的值

/**********全局函数**********/
void Drv_HALL_Init(void);
void Check_HALL(float dT);
void Check_Base(float dT);

#endif
