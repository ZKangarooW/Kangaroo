#ifndef __DRV_INFRARED_H__
#define __DRV_INFRARED_H__

#include "include.h"

/**********宏定义************/

#define CARRIER_38KHz() PWM_IndependentModeConfig(PWM06,280);//设置PWM占空比.初始化周期27us。
#define NO_CARRIER()	PWM_IndependentModeConfig(PWM06,0);//1050电压3.2V

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
void Check_Infrared(float dT);
void Infrared_TIM_Interrupt(void);
void NEC_Send(uint8_t addr, uint8_t value, uint8_t cnt);

#endif
