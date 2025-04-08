#ifndef __DRV_INFRARED_H__
#define __DRV_INFRARED_H__

#include "include.h"

/**********宏定义************/
#define IR1_IN HAL_GPIO_ReadPin(IR1_GPIO_Port, IR1_Pin)
#define IR2_IN HAL_GPIO_ReadPin(IR2_GPIO_Port, IR2_Pin)

#define Infrared_Send1 htim3.Instance->CCR1
#define Infrared_Send2 htim3.Instance->CCR2

#define CARRIER_38KHz(N) __HAL_TIM_SET_COMPARE(&htim3, N == 1 ? TIM_CHANNEL_1 : TIM_CHANNEL_2, 52)//设置PWM占空比三分之一
#define NO_CARRIER(N)    __HAL_TIM_SET_COMPARE(&htim3, N == 1 ? TIM_CHANNEL_1 : TIM_CHANNEL_2, 0)
#define NEC_HEAD		(uint16_t)(4500) //引导码
#define NEC_ZERO 		(uint16_t)(560)  //代表0
#define NEC_ONE			(uint16_t)(1680) //代表1
#define NEC_CONTINUE 	(uint16_t)(2100) //代表连续长按
 
#define NEC_HEAD_MIN (uint16_t)(NEC_HEAD*1.0f) //4500
#define NEC_HEAD_MAX (uint16_t)(NEC_HEAD*1.4f) //6300
 
#define NEC_ZERO_MIN (uint16_t)(NEC_ZERO*0.7f)
#define NEC_ZERO_MAX (uint16_t)(NEC_ZERO*1.5f)
 
#define NEC_ONE_MIN (uint16_t)(NEC_ONE*0.7f)
#define NEC_ONE_MAX (uint16_t)(NEC_ONE*1.3f)

#define NEC_CONTINUE_MIN (uint16_t)(NEC_CONTINUE*1.0f)
#define NEC_CONTINUE_MAX (uint16_t)(NEC_CONTINUE*1.3f)

#define REMOTE_ID 0x00//红外遥控识别码(ID)

/**********结构体************/
typedef struct
{
    uint16_t Dval;//高电平计数器的值，根据此判断高低电平的时间
	uint8_t IRSta;//接受状态，[0:3]溢出计数器，[4]标记上升沿是否已经被捕获,[5]保留，[6]得到了一个按键的全部信息,[7]收到了引导码标志
    uint32_t IRRec;//红外接收到的数据
    uint32_t IRCnt;//按键按下的次数
    
	uint8_t Someone;//判断是否有人在，1：有人 0：没人
	float Someone_Time;//过一段时间清零没人计数
    uint8_t SSI_CNT;
    uint8_t SSI;//红外信号
} _Infrared_;
extern _Infrared_ Infrared[2];

/**********全局变量声明*******/
/**********全局函数**********/

void Drv_Infrared_Init(void);
void Infrared_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void NEC_Send(uint8_t val, uint8_t addr, uint8_t value, uint8_t cnt);
void Check_Infrared(float dT);
void Infrared_TIM_Interrupt(TIM_HandleTypeDef *htim);
void Infrared_SSI(float dT);

#endif
