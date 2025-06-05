#include "Torque.h"

#define Num 100			 // 采集100次
uint16_t value_Buf[Num]; // 用于储存采集到的adc值
uint8_t j = 0;
/**
 * @brief 滑动平均值滤波
 *
 * @return int 滤波后的值
 */
int Filter_TorqueADC(void)
{
	uint8_t count;
	long sum = 0;

	value_Buf[j++] = ADC_Val[1];

	if (j == Num) // 加入读了100组就从新开始
	{
		j = 0;
	}
	for (count = 0; count < Num; count++)
	{
		sum += value_Buf[count]; // 100组相加
	}
	if (value_Buf[Num - 1] == 0) // 如果没有读到100组就用第一次读到的数
		return value_Buf[0];
	else						 // 读到100组后
		return (int)(sum / Num); // 输出平均值
}

float Torque_Val_Avg;
float Motor_V = 0;
float Motor_I = 0;
float Motor_P = 0;

/**
 * @brief 扭矩计算
 * 1、算出采集到的电压
 * 2、算出电流 I = V /21/0.05
 * 3、算出功率 P = 24*I*1000；（KW）
 * 4、算出扭矩 N = （P（KW） / Speed(rpm/min) * 减速比 * 9550 ）*1000（包含N.m->N.cm是1：100  还有的10是用于显示） / 减速比
 * @param dK
 */
void Torque_Calculation(float dT)
{
	static float T;
	if(sys.Run_Status == 1)
	{
		T += dT;
		Torque_Val_Avg = Filter_TorqueADC();

		if (T >= 1.0f)
		{
			//		Motor_P = 3.3f/4096*Torque_Val_Avg /21 /0.05f *24.0f/1000;
			Motor_V = 3.3f / 4096 * Torque_Val_Avg;
			Motor_I = Motor_V / 21 / 0.05f;
			Motor_P = 24.0f * Motor_I / 1000;
			Speed.N_Val = (Motor_P / Speed.Rel * Tooth_Ratio * 9550) * 1000 / Tooth_Ratio; // 1000是1N.M = 100N.cm  10是用于显示。 减速电机扭矩计算按减速比来算
			if (Speed.N_Val <= 0)
				Speed.N_Val = 0;
			T = 0;
		}
	}
	else
	{
		Torque_Val_Avg = 0;
		Motor_V = 0;
		Motor_I = 0;
		Motor_P = 0;
		Speed.N_Val = 0;
		T = 0;
	}
}
