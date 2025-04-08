#ifndef __DRV_REMOTE_H__
#define __DRV_REMOTE_H__

#include "include.h"

/**********宏定义************/
//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0    		 
#define IR_IN HAL_GPIO_ReadPin(IR2_GPIO_Port, IR2_Pin)
extern uint8_t Remote_Flag;
/**********结构体************/
/**********全局变量声明*******/
/**********全局函数**********/
uint8_t Remote_Scan(void);
void Drv_Remote_Init(void);
void Remote_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void Check_Remote(float dT);
#endif
