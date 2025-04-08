#include "Drv_Shake.h"

/**********全局变量声明*******/
uint8_t Shake_Alarm; // 倾倒报警

/**
 * @brief 防倾倒检测
 *
 * @param dT 任务周期
 */
void Cheack_Shake(float dT)
{
//	static float T;
	
	if (!Shake_Switch)
		return;

//	if (G1 == 0)
//	{
//		T+= dT;
//		if(T >= 0.1f)
//		{
//			sys.Run_Status = 0;
//			sys.SetMode_Option = 0;
//			Speed.ADDMode = 2;
//			SetOK_Flag = 1;
//			Beep_Flash = 30;
//			Shake_Alarm = 1;
//			T = 0;
//		}
//	}
//	else
//		T = 0;
}
