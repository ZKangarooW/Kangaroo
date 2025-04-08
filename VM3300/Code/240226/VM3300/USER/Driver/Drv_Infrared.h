#ifndef __DRV_INFRARED_H__
#define __DRV_INFRARED_H__

#include "include.h"

/**********宏定义************/
#define IR1_IN HAL_GPIO_ReadPin(IR1_GPIO_Port, IR1_Pin)
#define IR2_IN HAL_GPIO_ReadPin(IR2_GPIO_Port, IR2_Pin)

#define Infrared_Send1 htim3.Instance->CCR1
#define Infrared_Send2 htim3.Instance->CCR2

/**********结构体************/
typedef struct
{
	uint8_t IRSta;//接受状态，[0:3]溢出计数器，[4]标记上升沿是否已经被捕获,[5]保留，[6]得到了一个按键的全部信息,[7]收到了引导码标志
	uint16_t Dval;//高电平计数器的值，根据此判断高低电平的时间
	uint8_t Someone;//判断是否有人在，1：有人 0：没人
	float Someone_Time;//过一段时间清零没人计数
} _Infrared_;
extern _Infrared_ Infrared[2];

/**********全局变量声明*******/
/**********全局函数**********/

void Drv_Infrared_Init(void);
void Check_Infrared(float dT);
void Infrared_TIM_Interrupt(TIM_HandleTypeDef *htim);
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif
