#include "Drv_HEAT.h"

/**
 * @brief 初始化加热制冷
 *
 */
void HEAT_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}


/**
 * @brief 控温模式任务
 * 
 * @param dT 任务周期
 * @param pwm 功率
 */
uint8_t Mode; // 储存上一次的模式
void HEAT_Duty(float dT, int16_t pwm)
{
	static float T;

	if(pwm >= 0)
	{
		Temp.Mode = 0;//加热
	}
	else if(pwm < 0)
	{
		Temp.Mode = 1;//制冷
	}
		
	if(Mode != Temp.Mode)//如果模式变换了
	{
		T += dT;//开始计时
		if(T <= 1.0f)//一秒没把加热和制冷都拉低不工作
		{
			COLD = 0;
			HEAT = 0;
		}
		else//一秒后将改的模式赋值
		{
			T = 0;
			Mode = Temp.Mode;
		}
	}
	else//没有改变模式的情况下
	{
		if(Temp.Mode == 0)
		{
			COLD = 0;
			HEAT = pwm;
		}			
		else if(Temp.Mode == 1)
		{
			COLD = (-pwm);
			HEAT = 0;
		}
	}
}
