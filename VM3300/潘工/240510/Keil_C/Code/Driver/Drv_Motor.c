#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
	MO_ON;//打开电机电源
	CW;
//	PWM_IndependentModeConfig(PWM20,400);//1050电压3.2V
}
