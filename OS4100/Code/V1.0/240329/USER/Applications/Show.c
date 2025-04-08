#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间

/**********局部变量声明*******/
uint8_t Temp_ShowFlag, Speed_ShowFlag, Time_ShowFlag; // 时间、速度、温度显示的标志位，0：常亮，1：熄灭
uint8_t Shake_Step;

/**
 * @brief 闪烁检测
 *
 * @param dT 任务周期
 */
static void Check_ShowFlag(float dT)
{
	static float T;
	if (!sys.SetMode_Option) // 如果没有在设置选项中，则都点亮，不闪烁
	{
		Temp_ShowFlag = 0;	// 常亮
		Speed_ShowFlag = 0; // 常亮
		Time_ShowFlag = 0;	// 常亮
		Twinkle_Time = 0;	// 闪烁计时清零
		return;
	}
	if (Twinkle_Time && !EC11A[0].EC11A_Knob) // 闪烁和没有操作按键时
	{
		SetOK_Flag = 1; // 检测到设置，等待退出设置模式
		if (T == 0)
		{
			if (Twinkle_Time == 0)
			{
				sys.SetMode_Option = 0; // 模式选择清零
				Temp_ShowFlag = 0;		// 常亮
				Speed_ShowFlag = 0;		// 常亮
				Time_ShowFlag = 0;		// 常亮
			}
			if (sys.SetMode_Option == 1)
			{
				Temp_ShowFlag = 0;				  // 常亮
				Speed_ShowFlag = ~Speed_ShowFlag; // 速度闪烁
				Time_ShowFlag = 0;				  // 常亮
			}
			else if (sys.SetMode_Option == 2)
			{
				Temp.Safe_Mode = 1;				// 点亮"SAFE"图标
				Temp_ShowFlag = ~Temp_ShowFlag; // 温度闪烁
				Speed_ShowFlag = 0;				// 常亮
				Time_ShowFlag = 0;				// 常亮
			}
			else if (sys.SetMode_Option == 3)
			{
				Temp_ShowFlag = 0;				// 常亮
				Speed_ShowFlag = 0;				// 常亮
				Time_ShowFlag = ~Time_ShowFlag; // 时间闪烁
			}
		}
		T += dT;
		if (T >= 0.5f)
		{
			Twinkle_Time -= 0.5f;
			if (Twinkle_Time <= 0)
			{
				sys.SetMode_Option = 0;
			}
			T = 0;
		}
	}
	else
	{
		Temp_ShowFlag = 0;	// 常亮
		Speed_ShowFlag = 0; // 常亮
		Time_ShowFlag = 0;	// 常亮
		T = 0;
	}
}

/**
 * @brief 闪烁检测
 *
 * @param dT 任务周期
 */
static void Check_ShakeCartoon(float dT)
{
	static float T;
	if (Shake_Alarm) // 启动，并且在设定了转速的情况下
	{
		if (T == 0)
		{
			Shake_Step++;
			if (Shake_Step > 6)
				Shake_Step = 1;
		}
		T += dT;
		if (T >= 0.2f)
		{
			T = 0;
		}
	}
	else
	{
		Shake_Step = 0;
		T = 0;
	}
}

/**
 * @brief 转速图标转动任务
 *
 * @param dT 任务周期
 */
void SpeedIcn_Duty(float dT)
{
	static float T;
	if ((sys.Run_Status == 1) && Speed.Ctrl) // 启动，并且在设定了转速的情况下
	{
		if (T == 0)
		{
			Speed.IcnStep++;
			if (Speed.IcnStep > 3)
				Speed.IcnStep = 1;
		}
		T += dT;
		if (T >= 0.5f)
		{
			T = 0;
		}
	}
	else
	{
		Speed.IcnStep = 0;
		T = 0;
	}
}

/**
 * @brief 图标闪烁
 *
 * @param dT 任务周期
 */
static void Icn_Twinkle(float dT)
{
	static float T;

	if (sys.Run_Status == 1)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Time.Icn = ~Time.Icn;
			T = 0;
		}
	}
	else
	{
		Time.Icn = 0;
	}
}

/**
 * @brief 安全温度图标闪烁检测
 *
 * @param dT 任务周期
 */
static void Check_Safe_Mode(float dT)
{
	static float T;
	if (Temp.Icn)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Temp.Safe_Mode = ~Temp.Safe_Mode; // 安全温度图标闪烁
			T = 0;
		}
	}
	else
	{
		if (sys.SetMode_Option == 2)
			Temp.Safe_Mode = 1;
		else
			Temp.Safe_Mode = 0;
	}
}

/**
 * @brief 闪烁函数
 *
 * @param dT 任务周期
 */
void Twinkle(float dT)
{
	Check_Safe_Mode(dT);
	Check_ShowFlag(dT);
	Check_ShakeCartoon(dT);
	SpeedIcn_Duty(dT);
	Icn_Twinkle(dT);
}

/**
 * @brief 显示屏幕函数
 *
 * @param dis_rel_speed 实际转速
 * @param dis_set_speed 设定转速
 * @param dis_N 显示扭力
 * @param dis_temp 显示温度
 * @param dis_time 显示时间
 */
void Display_Show(uint16_t dis_rel_speed, uint16_t dis_set_speed, uint16_t dis_N, int16_t dis_temp, uint32_t dis_time)
{
	uint8_t seg[22] = {0};

	uint8_t Val;		  // 用于百十个取出来的数字
	uint8_t SH, H, SM, M; // 时间的单位取值
	if (!Shake_Alarm)
	{
		/**********dis_rel_speed**********/
		if (dis_rel_speed > 999) // 大于999时
		{
			Val = dis_rel_speed / 1000 % 10;
			switch (Val)
			{
			case 0:
				seg[0] &= 0xF8;
				seg[0] |= 0x07;
				seg[1] &= 0xF8;
				seg[1] |= 0x05;
				seg[2] &= 0xFE;
				seg[2] |= 0x01; // 数字0
				break;
			case 1:
				seg[0] &= 0xF8;
				seg[0] |= 0x00;
				seg[1] &= 0xF8;
				seg[1] |= 0x04;
				seg[2] &= 0xFE;
				seg[2] |= 0x01; // 数字1
				break;
			case 2:
				seg[0] &= 0xF8;
				seg[0] |= 0x06;
				seg[1] &= 0xF8;
				seg[1] |= 0x03;
				seg[2] &= 0xFE;
				seg[2] |= 0x01; // 数字2
				break;
			case 3:
				seg[0] &= 0xF8;
				seg[0] |= 0x04;
				seg[1] &= 0xF8;
				seg[1] |= 0x07;
				seg[2] &= 0xFE;
				seg[2] |= 0x01; // 数字3
				break;
			case 4:
				seg[0] &= 0xF8;
				seg[0] |= 0x01;
				seg[1] &= 0xF8;
				seg[1] |= 0x06;
				seg[2] &= 0xFE;
				seg[2] |= 0x01; // 数字4
				break;
			case 5:
				seg[0] &= 0xF8;
				seg[0] |= 0x05;
				seg[1] &= 0xF8;
				seg[1] |= 0x07;
				seg[2] &= 0xFE;
				seg[2] |= 0x00; // 数字5
				break;
			case 6:
				seg[0] &= 0xF8;
				seg[0] |= 0x07;
				seg[1] &= 0xF8;
				seg[1] |= 0x07;
				seg[2] &= 0xFE;
				seg[2] |= 0x00; // 数字6
				break;
			case 7:
				seg[0] &= 0xF8;
				seg[0] |= 0x00;
				seg[1] &= 0xF8;
				seg[1] |= 0x05;
				seg[2] &= 0xFE;
				seg[2] |= 0x01; // 数字7
				break;
			case 8:
				seg[0] &= 0xF8;
				seg[0] |= 0x07;
				seg[1] &= 0xF8;
				seg[1] |= 0x07;
				seg[2] &= 0xFE;
				seg[2] |= 0x01; // 数字8
				break;
			case 9:
				seg[0] &= 0xF8;
				seg[0] |= 0x05;
				seg[1] &= 0xF8;
				seg[1] |= 0x07;
				seg[2] &= 0xFE;
				seg[2] |= 0x01; // 数字9
				break;
			default:
				break;
			}
		}
		else
		{
			seg[0] &= 0xF8;
			seg[0] |= 0x00;
			seg[1] &= 0xF8;
			seg[1] |= 0x00;
			seg[2] &= 0xFE;
			seg[2] |= 0x00; // 数字0或者可以不显示
		}
		if (dis_rel_speed > 99) // 大于99时
		{
			Val = dis_rel_speed / 100 % 10;
			switch (Val)
			{
			case 0:
				seg[2] &= 0xF9;
				seg[2] |= 0x06;
				seg[3] &= 0xF8;
				seg[3] |= 0x05;
				seg[4] &= 0xFC;
				seg[4] |= 0x03; // 数字0
				break;
			case 1:
				seg[2] &= 0xF9;
				seg[2] |= 0x00;
				seg[3] &= 0xF8;
				seg[3] |= 0x00;
				seg[4] &= 0xFC;
				seg[4] |= 0x03; // 数字1
				break;
			case 2:
				seg[2] &= 0xF9;
				seg[2] |= 0x04;
				seg[3] &= 0xF8;
				seg[3] |= 0x07;
				seg[4] &= 0xFC;
				seg[4] |= 0x01; // 数字2
				break;
			case 3:
				seg[2] &= 0xF9;
				seg[2] |= 0x00;
				seg[3] &= 0xF8;
				seg[3] |= 0x07;
				seg[4] &= 0xFC;
				seg[4] |= 0x03; // 数字3
				break;
			case 4:
				seg[2] &= 0xF9;
				seg[2] |= 0x02;
				seg[3] &= 0xF8;
				seg[3] |= 0x02;
				seg[4] &= 0xFC;
				seg[4] |= 0x03; // 数字4
				break;
			case 5:
				seg[2] &= 0xF9;
				seg[2] |= 0x02;
				seg[3] &= 0xF8;
				seg[3] |= 0x07;
				seg[4] &= 0xFC;
				seg[4] |= 0x02; // 数字5
				break;
			case 6:
				seg[2] &= 0xF9;
				seg[2] |= 0x06;
				seg[3] &= 0xF8;
				seg[3] |= 0x07;
				seg[4] &= 0xFC;
				seg[4] |= 0x02; // 数字6
				break;
			case 7:
				seg[2] &= 0xF9;
				seg[2] |= 0x00;
				seg[3] &= 0xF8;
				seg[3] |= 0x01;
				seg[4] &= 0xFC;
				seg[4] |= 0x03; // 数字7
				break;
			case 8:
				seg[2] &= 0xF9;
				seg[2] |= 0x06;
				seg[3] &= 0xF8;
				seg[3] |= 0x07;
				seg[4] &= 0xFC;
				seg[4] |= 0x03; // 数字8
				break;
			case 9:
				seg[2] &= 0xF9;
				seg[2] |= 0x02;
				seg[3] &= 0xF8;
				seg[3] |= 0x07;
				seg[4] &= 0xFC;
				seg[4] |= 0x03; // 数字9
				break;
			default:
				break;
			}
		}
		else
		{
			seg[2] &= 0xF9;
			seg[2] |= 0x00;
			seg[3] &= 0xF8;
			seg[3] |= 0x00;
			seg[4] &= 0xFC;
			seg[4] |= 0x00; // 数字0或者可以不显示
		}

		if (dis_rel_speed > 9) // 大于9时
		{
			Val = dis_rel_speed / 10 % 10;
			switch (Val)
			{
			case 0:
				seg[4] &= 0xFB;
				seg[4] |= 0x04;
				seg[5] &= 0xF8;
				seg[5] |= 0x05;
				seg[6] &= 0xF8;
				seg[6] |= 0x07; // 数字0
				break;
			case 1:
				seg[4] &= 0xFB;
				seg[4] |= 0x00;
				seg[5] &= 0xF8;
				seg[5] |= 0x00;
				seg[6] &= 0xF8;
				seg[6] |= 0x06; // 数字1
				break;
			case 2:
				seg[4] &= 0xFB;
				seg[4] |= 0x04;
				seg[5] &= 0xF8;
				seg[5] |= 0x06;
				seg[6] &= 0xF8;
				seg[6] |= 0x03; // 数字2
				break;
			case 3:
				seg[4] &= 0xFB;
				seg[4] |= 0x00;
				seg[5] &= 0xF8;
				seg[5] |= 0x06;
				seg[6] &= 0xF8;
				seg[6] |= 0x07; // 数字3
				break;
			case 4:
				seg[4] &= 0xFB;
				seg[4] |= 0x00;
				seg[5] &= 0xF8;
				seg[5] |= 0x03;
				seg[6] &= 0xF8;
				seg[6] |= 0x06; // 数字4
				break;
			case 5:
				seg[4] &= 0xFB;
				seg[4] |= 0x00;
				seg[5] &= 0xF8;
				seg[5] |= 0x07;
				seg[6] &= 0xF8;
				seg[6] |= 0x05; // 数字5
				break;
			case 6:
				seg[4] &= 0xFB;
				seg[4] |= 0x04;
				seg[5] &= 0xF8;
				seg[5] |= 0x07;
				seg[6] &= 0xF8;
				seg[6] |= 0x05; // 数字6
				break;
			case 7:
				seg[4] &= 0xFB;
				seg[4] |= 0x00;
				seg[5] &= 0xF8;
				seg[5] |= 0x00;
				seg[6] &= 0xF8;
				seg[6] |= 0x07; // 数字7
				break;
			case 8:
				seg[4] &= 0xFB;
				seg[4] |= 0x04;
				seg[5] &= 0xF8;
				seg[5] |= 0x07;
				seg[6] &= 0xF8;
				seg[6] |= 0x07; // 数字8
				break;
			case 9:
				seg[4] &= 0xFB;
				seg[4] |= 0x00;
				seg[5] &= 0xF8;
				seg[5] |= 0x07;
				seg[6] &= 0xF8;
				seg[6] |= 0x07; // 数字9
				break;
			default:
				break;
			}
		}
		else
		{
			seg[4] &= 0xFB;
			seg[4] |= 0x00;
			seg[5] &= 0xF8;
			seg[5] |= 0x00;
			seg[6] &= 0xF8;
			seg[6] |= 0x00; // 数字0或者可以不显示
		}

		if (dis_rel_speed > 0) // 大于等于0时
		{
			Val = dis_rel_speed % 10;
			switch (Val)
			{
			case 0:
				seg[7] &= 0xF8;
				seg[7] |= 0x07;
				seg[8] &= 0xF8;
				seg[8] |= 0x05;
				seg[9] &= 0xFE;
				seg[9] |= 0x01; // 数字0
				break;
			case 1:
				seg[7] &= 0xF8;
				seg[7] |= 0x00;
				seg[8] &= 0xF8;
				seg[8] |= 0x04;
				seg[9] &= 0xFE;
				seg[9] |= 0x01; // 数字1
				break;
			case 2:
				seg[7] &= 0xF8;
				seg[7] |= 0x06;
				seg[8] &= 0xF8;
				seg[8] |= 0x03;
				seg[9] &= 0xFE;
				seg[9] |= 0x01; // 数字2
				break;
			case 3:
				seg[7] &= 0xF8;
				seg[7] |= 0x04;
				seg[8] &= 0xF8;
				seg[8] |= 0x07;
				seg[9] &= 0xFE;
				seg[9] |= 0x01; // 数字3
				break;
			case 4:
				seg[7] &= 0xF8;
				seg[7] |= 0x01;
				seg[8] &= 0xF8;
				seg[8] |= 0x06;
				seg[9] &= 0xFE;
				seg[9] |= 0x01; // 数字4
				break;
			case 5:
				seg[7] &= 0xF8;
				seg[7] |= 0x05;
				seg[8] &= 0xF8;
				seg[8] |= 0x07;
				seg[9] &= 0xFE;
				seg[9] |= 0x00; // 数字5
				break;
			case 6:
				seg[7] &= 0xF8;
				seg[7] |= 0x07;
				seg[8] &= 0xF8;
				seg[8] |= 0x07;
				seg[9] &= 0xFE;
				seg[9] |= 0x00; // 数字6
				break;
			case 7:
				seg[7] &= 0xF8;
				seg[7] |= 0x00;
				seg[8] &= 0xF8;
				seg[8] |= 0x05;
				seg[9] &= 0xFE;
				seg[9] |= 0x01; // 数字7
				break;
			case 8:
				seg[7] &= 0xF8;
				seg[7] |= 0x07;
				seg[8] &= 0xF8;
				seg[8] |= 0x07;
				seg[9] &= 0xFE;
				seg[9] |= 0x01; // 数字8
				break;
			case 9:
				seg[7] &= 0xF8;
				seg[7] |= 0x05;
				seg[8] &= 0xF8;
				seg[8] |= 0x07;
				seg[9] &= 0xFE;
				seg[9] |= 0x01; // 数字9
				break;
			default:
				break;
			}
		}
		else
		{
			seg[7] &= 0xF8;
			seg[7] |= 0x07;
			seg[8] &= 0xF8;
			seg[8] |= 0x05;
			seg[9] &= 0xFE;
			seg[9] |= 0x01; // 数字0或者可以不显示
		}

		/**********dis_set_speed**********/
		if (!Speed_ShowFlag)
		{
			if (dis_set_speed > 999) // 大于999时
			{
				Val = dis_set_speed / 1000 % 10;
				switch (Val)
				{
				case 0:
					seg[0] &= 0xC7;
					seg[0] |= 0x38;
					seg[1] &= 0xC7;
					seg[1] |= 0x28;
					seg[2] &= 0xF7;
					seg[2] |= 0x08; // 数字0
					break;
				case 1:
					seg[0] &= 0xC7;
					seg[0] |= 0x00;
					seg[1] &= 0xC7;
					seg[1] |= 0x20;
					seg[2] &= 0xF7;
					seg[2] |= 0x08; // 数字1
					break;
				case 2:
					seg[0] &= 0xC7;
					seg[0] |= 0x30;
					seg[1] &= 0xC7;
					seg[1] |= 0x18;
					seg[2] &= 0xF7;
					seg[2] |= 0x08; // 数字2
					break;
				case 3:
					seg[0] &= 0xC7;
					seg[0] |= 0x20;
					seg[1] &= 0xC7;
					seg[1] |= 0x38;
					seg[2] &= 0xF7;
					seg[2] |= 0x08; // 数字3
					break;
				case 4:
					seg[0] &= 0xC7;
					seg[0] |= 0x08;
					seg[1] &= 0xC7;
					seg[1] |= 0x30;
					seg[2] &= 0xF7;
					seg[2] |= 0x08; // 数字4
					break;
				case 5:
					seg[0] &= 0xC7;
					seg[0] |= 0x28;
					seg[1] &= 0xC7;
					seg[1] |= 0x38;
					seg[2] &= 0xF7;
					seg[2] |= 0x00; // 数字5
					break;
				case 6:
					seg[0] &= 0xC7;
					seg[0] |= 0x38;
					seg[1] &= 0xC7;
					seg[1] |= 0x38;
					seg[2] &= 0xF7;
					seg[2] |= 0x00; // 数字6
					break;
				case 7:
					seg[0] &= 0xC7;
					seg[0] |= 0x00;
					seg[1] &= 0xC7;
					seg[1] |= 0x28;
					seg[2] &= 0xF7;
					seg[2] |= 0x08; // 数字7
					break;
				case 8:
					seg[0] &= 0xC7;
					seg[0] |= 0x38;
					seg[1] &= 0xC7;
					seg[1] |= 0x38;
					seg[2] &= 0xF7;
					seg[2] |= 0x08; // 数字8
					break;
				case 9:
					seg[0] &= 0xC7;
					seg[0] |= 0x28;
					seg[1] &= 0xC7;
					seg[1] |= 0x38;
					seg[2] &= 0xF7;
					seg[2] |= 0x08; // 数字9
					break;
				default:
					break;
				}
			}
			else
			{
				seg[0] &= 0xC7;
				seg[0] |= 0x00;
				seg[1] &= 0xC7;
				seg[1] |= 0x00;
				seg[2] &= 0xF7;
				seg[2] |= 0x00; // 数字0或者可以不显示
			}

			if (dis_set_speed > 99) // 大于99时
			{
				Val = dis_set_speed / 100 % 10;
				switch (Val)
				{
				case 0:
					seg[2] &= 0xCF;
					seg[2] |= 0x30;
					seg[3] &= 0xC7;
					seg[3] |= 0x28;
					seg[4] &= 0xE7;
					seg[4] |= 0x18; // 数字0
					break;
				case 1:
					seg[2] &= 0xCF;
					seg[2] |= 0x00;
					seg[3] &= 0xC7;
					seg[3] |= 0x00;
					seg[4] &= 0xE7;
					seg[4] |= 0x18; // 数字1
					break;
				case 2:
					seg[2] &= 0xCF;
					seg[2] |= 0x20;
					seg[3] &= 0xC7;
					seg[3] |= 0x38;
					seg[4] &= 0xE7;
					seg[4] |= 0x08; // 数字2
					break;
				case 3:
					seg[2] &= 0xCF;
					seg[2] |= 0x00;
					seg[3] &= 0xC7;
					seg[3] |= 0x38;
					seg[4] &= 0xE7;
					seg[4] |= 0x18; // 数字3
					break;
				case 4:
					seg[2] &= 0xCF;
					seg[2] |= 0x10;
					seg[3] &= 0xC7;
					seg[3] |= 0x10;
					seg[4] &= 0xE7;
					seg[4] |= 0x18; // 数字4
					break;
				case 5:
					seg[2] &= 0xCF;
					seg[2] |= 0x10;
					seg[3] &= 0xC7;
					seg[3] |= 0x38;
					seg[4] &= 0xE7;
					seg[4] |= 0x10; // 数字5
					break;
				case 6:
					seg[2] &= 0xCF;
					seg[2] |= 0x30;
					seg[3] &= 0xC7;
					seg[3] |= 0x38;
					seg[4] &= 0xE7;
					seg[4] |= 0x10; // 数字6
					break;
				case 7:
					seg[2] &= 0xCF;
					seg[2] |= 0x00;
					seg[3] &= 0xC7;
					seg[3] |= 0x08;
					seg[4] &= 0xE7;
					seg[4] |= 0x18; // 数字7
					break;
				case 8:
					seg[2] &= 0xCF;
					seg[2] |= 0x30;
					seg[3] &= 0xC7;
					seg[3] |= 0x38;
					seg[4] &= 0xE7;
					seg[4] |= 0x18; // 数字8
					break;
				case 9:
					seg[2] &= 0xCF;
					seg[2] |= 0x10;
					seg[3] &= 0xC7;
					seg[3] |= 0x38;
					seg[4] &= 0xE7;
					seg[4] |= 0x18; // 数字9
					break;
				default:
					break;
				}
			}
			else
			{
				seg[2] &= 0xCF;
				seg[2] |= 0x00;
				seg[3] &= 0xC7;
				seg[3] |= 0x00;
				seg[4] &= 0xE7;
				seg[4] |= 0x00; // 数字0或者可以不显示
			}

			if (dis_set_speed > 9) // 大于9时
			{
				Val = dis_set_speed / 10 % 10;
				switch (Val)
				{
				case 0:
					seg[4] &= 0xDF;
					seg[4] |= 0x20;
					seg[5] &= 0xC7;
					seg[5] |= 0x28;
					seg[6] &= 0xC7;
					seg[6] |= 0x38; // 数字0
					break;
				case 1:
					seg[4] &= 0xDF;
					seg[4] |= 0x00;
					seg[5] &= 0xC7;
					seg[5] |= 0x00;
					seg[6] &= 0xC7;
					seg[6] |= 0x30; // 数字1
					break;
				case 2:
					seg[4] &= 0xDF;
					seg[4] |= 0x20;
					seg[5] &= 0xC7;
					seg[5] |= 0x30;
					seg[6] &= 0xC7;
					seg[6] |= 0x18; // 数字2
					break;
				case 3:
					seg[4] &= 0xDF;
					seg[4] |= 0x00;
					seg[5] &= 0xC7;
					seg[5] |= 0x30;
					seg[6] &= 0xC7;
					seg[6] |= 0x38; // 数字3
					break;
				case 4:
					seg[4] &= 0xDF;
					seg[4] |= 0x00;
					seg[5] &= 0xC7;
					seg[5] |= 0x18;
					seg[6] &= 0xC7;
					seg[6] |= 0x30; // 数字4
					break;
				case 5:
					seg[4] &= 0xDF;
					seg[4] |= 0x00;
					seg[5] &= 0xC7;
					seg[5] |= 0x38;
					seg[6] &= 0xC7;
					seg[6] |= 0x28; // 数字5
					break;
				case 6:
					seg[4] &= 0xDF;
					seg[4] |= 0x20;
					seg[5] &= 0xC7;
					seg[5] |= 0x38;
					seg[6] &= 0xC7;
					seg[6] |= 0x28; // 数字6
					break;
				case 7:
					seg[4] &= 0xDF;
					seg[4] |= 0x00;
					seg[5] &= 0xC7;
					seg[5] |= 0x00;
					seg[6] &= 0xC7;
					seg[6] |= 0x38; // 数字7
					break;
				case 8:
					seg[4] &= 0xDF;
					seg[4] |= 0x20;
					seg[5] &= 0xC7;
					seg[5] |= 0x38;
					seg[6] &= 0xC7;
					seg[6] |= 0x38; // 数字8
					break;
				case 9:
					seg[4] &= 0xDF;
					seg[4] |= 0x00;
					seg[5] &= 0xC7;
					seg[5] |= 0x38;
					seg[6] &= 0xC7;
					seg[6] |= 0x38; // 数字9
					break;
				default:
					break;
				}
			}
			else
			{
				seg[4] &= 0xDF;
				seg[4] |= 0x00;
				seg[5] &= 0xC7;
				seg[5] |= 0x00;
				seg[6] &= 0xC7;
				seg[6] |= 0x00; // 数字0或者可以不显示
			}

			if (dis_set_speed > 0) // 大于等于0时
			{
				Val = dis_set_speed % 10;
				switch (Val)
				{
				case 0:
					seg[7] &= 0xC7;
					seg[7] |= 0x38;
					seg[8] &= 0xC7;
					seg[8] |= 0x28;
					seg[9] &= 0xF7;
					seg[9] |= 0x08; // 数字0
					break;
				case 1:
					seg[7] &= 0xC7;
					seg[7] |= 0x00;
					seg[8] &= 0xC7;
					seg[8] |= 0x20;
					seg[9] &= 0xF7;
					seg[9] |= 0x08; // 数字1
					break;
				case 2:
					seg[7] &= 0xC7;
					seg[7] |= 0x30;
					seg[8] &= 0xC7;
					seg[8] |= 0x18;
					seg[9] &= 0xF7;
					seg[9] |= 0x08; // 数字2
					break;
				case 3:
					seg[7] &= 0xC7;
					seg[7] |= 0x20;
					seg[8] &= 0xC7;
					seg[8] |= 0x38;
					seg[9] &= 0xF7;
					seg[9] |= 0x08; // 数字3
					break;
				case 4:
					seg[7] &= 0xC7;
					seg[7] |= 0x08;
					seg[8] &= 0xC7;
					seg[8] |= 0x30;
					seg[9] &= 0xF7;
					seg[9] |= 0x08; // 数字4
					break;
				case 5:
					seg[7] &= 0xC7;
					seg[7] |= 0x28;
					seg[8] &= 0xC7;
					seg[8] |= 0x38;
					seg[9] &= 0xF7;
					seg[9] |= 0x00; // 数字5
					break;
				case 6:
					seg[7] &= 0xC7;
					seg[7] |= 0x38;
					seg[8] &= 0xC7;
					seg[8] |= 0x38;
					seg[9] &= 0xF7;
					seg[9] |= 0x00; // 数字6
					break;
				case 7:
					seg[7] &= 0xC7;
					seg[7] |= 0x00;
					seg[8] &= 0xC7;
					seg[8] |= 0x28;
					seg[9] &= 0xF7;
					seg[9] |= 0x08; // 数字7
					break;
				case 8:
					seg[7] &= 0xC7;
					seg[7] |= 0x38;
					seg[8] &= 0xC7;
					seg[8] |= 0x38;
					seg[9] &= 0xF7;
					seg[9] |= 0x08; // 数字8
					break;
				case 9:
					seg[7] &= 0xC7;
					seg[7] |= 0x28;
					seg[8] &= 0xC7;
					seg[8] |= 0x38;
					seg[9] &= 0xF7;
					seg[9] |= 0x08; // 数字9
					break;
				default:
					break;
				}
			}
			else
			{
				seg[7] &= 0xC7;
				seg[7] |= 0x38;
				seg[8] &= 0xC7;
				seg[8] |= 0x28;
				seg[9] &= 0xF7;
				seg[9] |= 0x08; // 数字0或者可以不显示
			}
		}
		else
		{
			seg[0] &= 0xC7;
			seg[0] |= 0x00;
			seg[1] &= 0xC7;
			seg[1] |= 0x00;
			seg[2] &= 0xF7;
			seg[2] |= 0x00; // 不显示
			seg[2] &= 0xCF;
			seg[2] |= 0x00;
			seg[3] &= 0xC7;
			seg[3] |= 0x00;
			seg[4] &= 0xE7;
			seg[4] |= 0x00; // 不显示
			seg[4] &= 0xDF;
			seg[4] |= 0x00;
			seg[5] &= 0xC7;
			seg[5] |= 0x00;
			seg[6] &= 0xC7;
			seg[6] |= 0x00; // 不显示
			seg[7] &= 0xC7;
			seg[7] |= 0x00;
			seg[8] &= 0xC7;
			seg[8] |= 0x00;
			seg[9] &= 0xF7;
			seg[9] |= 0x00; // 不显示
		}

		/**********dis_N**********/
		if (dis_N > 999) // 大于999时
		{
			Val = dis_N / 1000 % 10;
			switch (Val)
			{
			case 0:
				seg[1] &= 0x3F;
				seg[1] |= 0xC0;
				seg[2] &= 0xBF;
				seg[2] |= 0x40;
				seg[19] &= 0x3F;
				seg[19] |= 0xC0;
				seg[20] &= 0x3F;
				seg[20] |= 0x40; // 数字0
				break;
			case 1:
				seg[1] &= 0x3F;
				seg[1] |= 0x00;
				seg[2] &= 0xBF;
				seg[2] |= 0x40;
				seg[19] &= 0x3F;
				seg[19] |= 0x80;
				seg[20] &= 0x3F;
				seg[20] |= 0x00; // 数字1
				break;
			case 2:
				seg[1] &= 0x3F;
				seg[1] |= 0x40;
				seg[2] &= 0xBF;
				seg[2] |= 0x40;
				seg[19] &= 0x3F;
				seg[19] |= 0x40;
				seg[20] &= 0x3F;
				seg[20] |= 0xC0; // 数字2
				break;
			case 3:
				seg[1] &= 0x3F;
				seg[1] |= 0x40;
				seg[2] &= 0xBF;
				seg[2] |= 0x40;
				seg[19] &= 0x3F;
				seg[19] |= 0xC0;
				seg[20] &= 0x3F;
				seg[20] |= 0x80; // 数字3
				break;
			case 4:
				seg[1] &= 0x3F;
				seg[1] |= 0x80;
				seg[2] &= 0xBF;
				seg[2] |= 0x40;
				seg[19] &= 0x3F;
				seg[19] |= 0x80;
				seg[20] &= 0x3F;
				seg[20] |= 0x80; // 数字4
				break;
			case 5:
				seg[1] &= 0x3F;
				seg[1] |= 0xC0;
				seg[2] &= 0xBF;
				seg[2] |= 0x00;
				seg[19] &= 0x3F;
				seg[19] |= 0xC0;
				seg[20] &= 0x3F;
				seg[20] |= 0x80; // 数字5
				break;
			case 6:
				seg[1] &= 0x3F;
				seg[1] |= 0xC0;
				seg[2] &= 0xBF;
				seg[2] |= 0x00;
				seg[19] &= 0x3F;
				seg[19] |= 0xC0;
				seg[20] &= 0x3F;
				seg[20] |= 0xC0; // 数字6
				break;
			case 7:
				seg[1] &= 0x3F;
				seg[1] |= 0x40;
				seg[2] &= 0xBF;
				seg[2] |= 0x40;
				seg[19] &= 0x3F;
				seg[19] |= 0x80;
				seg[20] &= 0x3F;
				seg[20] |= 0x00; // 数字7
				break;
			case 8:
				seg[1] &= 0x3F;
				seg[1] |= 0xC0;
				seg[2] &= 0xBF;
				seg[2] |= 0x40;
				seg[19] &= 0x3F;
				seg[19] |= 0xC0;
				seg[20] &= 0x3F;
				seg[20] |= 0xC0; // 数字8
				break;
			case 9:
				seg[1] &= 0x3F;
				seg[1] |= 0xC0;
				seg[2] &= 0xBF;
				seg[2] |= 0x40;
				seg[19] &= 0x3F;
				seg[19] |= 0xC0;
				seg[20] &= 0x3F;
				seg[20] |= 0x80; // 数字9
				break;
			default:
				break;
			}
		}
		else
		{
			seg[1] &= 0x3F;
			seg[1] |= 0x00;
			seg[2] &= 0xBF;
			seg[2] |= 0x00;
			seg[19] &= 0x3F;
			seg[19] |= 0x00;
			seg[20] &= 0x3F;
			seg[20] |= 0x00; // 数字0
		}

		if (dis_N > 99) // 大于99时
		{
			Val = dis_N / 100 % 10;
			switch (Val)
			{
			case 0:
				seg[3] &= 0x3F;
				seg[3] |= 0xC0;
				seg[4] &= 0xBF;
				seg[4] |= 0x40;
				seg[17] &= 0x3F;
				seg[17] |= 0xC0;
				seg[18] &= 0x3F;
				seg[18] |= 0x40; // 数字0
				break;
			case 1:
				seg[3] &= 0x3F;
				seg[3] |= 0x00;
				seg[4] &= 0xBF;
				seg[4] |= 0x40;
				seg[17] &= 0x3F;
				seg[17] |= 0x80;
				seg[18] &= 0x3F;
				seg[18] |= 0x00; // 数字1
				break;
			case 2:
				seg[3] &= 0x3F;
				seg[3] |= 0x40;
				seg[4] &= 0xBF;
				seg[4] |= 0x40;
				seg[17] &= 0x3F;
				seg[17] |= 0x40;
				seg[18] &= 0x3F;
				seg[18] |= 0xC0; // 数字2
				break;
			case 3:
				seg[3] &= 0x3F;
				seg[3] |= 0x40;
				seg[4] &= 0xBF;
				seg[4] |= 0x40;
				seg[17] &= 0x3F;
				seg[17] |= 0xC0;
				seg[18] &= 0x3F;
				seg[18] |= 0x80; // 数字3
				break;
			case 4:
				seg[3] &= 0x3F;
				seg[3] |= 0x80;
				seg[4] &= 0xBF;
				seg[4] |= 0x40;
				seg[17] &= 0x3F;
				seg[17] |= 0x80;
				seg[18] &= 0x3F;
				seg[18] |= 0x80; // 数字4
				break;
			case 5:
				seg[3] &= 0x3F;
				seg[3] |= 0xC0;
				seg[4] &= 0xBF;
				seg[4] |= 0x00;
				seg[17] &= 0x3F;
				seg[17] |= 0xC0;
				seg[18] &= 0x3F;
				seg[18] |= 0x80; // 数字5
				break;
			case 6:
				seg[3] &= 0x3F;
				seg[3] |= 0xC0;
				seg[4] &= 0xBF;
				seg[4] |= 0x00;
				seg[17] &= 0x3F;
				seg[17] |= 0xC0;
				seg[18] &= 0x3F;
				seg[18] |= 0xC0; // 数字6
				break;
			case 7:
				seg[3] &= 0x3F;
				seg[3] |= 0x40;
				seg[4] &= 0xBF;
				seg[4] |= 0x40;
				seg[17] &= 0x3F;
				seg[17] |= 0x80;
				seg[18] &= 0x3F;
				seg[18] |= 0x00; // 数字7
				break;
			case 8:
				seg[3] &= 0x3F;
				seg[3] |= 0xC0;
				seg[4] &= 0xBF;
				seg[4] |= 0x40;
				seg[17] &= 0x3F;
				seg[17] |= 0xC0;
				seg[18] &= 0x3F;
				seg[18] |= 0xC0; // 数字8
				break;
			case 9:
				seg[3] &= 0x3F;
				seg[3] |= 0xC0;
				seg[4] &= 0xBF;
				seg[4] |= 0x40;
				seg[17] &= 0x3F;
				seg[17] |= 0xC0;
				seg[18] &= 0x3F;
				seg[18] |= 0x80; // 数字9
				break;
			default:
				break;
			}
		}
		else
		{
			seg[3] &= 0x3F;
			seg[3] |= 0x00;
			seg[4] &= 0xBF;
			seg[4] |= 0x00;
			seg[17] &= 0x3F;
			seg[17] |= 0x00;
			seg[18] &= 0x3F;
			seg[18] |= 0x00; // 数字0
		}

		if (dis_N > 9) // 大于9时
		{
			Val = dis_N / 10 % 10;
			switch (Val)
			{
			case 0:
				seg[5] &= 0x3F;
				seg[5] |= 0xC0;
				seg[6] &= 0xBF;
				seg[6] |= 0x40;
				seg[15] &= 0x3F;
				seg[15] |= 0xC0;
				seg[16] &= 0x3F;
				seg[16] |= 0x40; // 数字0
				break;
			case 1:
				seg[5] &= 0x3F;
				seg[5] |= 0x00;
				seg[6] &= 0xBF;
				seg[6] |= 0x40;
				seg[15] &= 0x3F;
				seg[15] |= 0x80;
				seg[16] &= 0x3F;
				seg[16] |= 0x00; // 数字1
				break;
			case 2:
				seg[5] &= 0x3F;
				seg[5] |= 0x40;
				seg[6] &= 0xBF;
				seg[6] |= 0x40;
				seg[15] &= 0x3F;
				seg[15] |= 0x40;
				seg[16] &= 0x3F;
				seg[16] |= 0xC0; // 数字2
				break;
			case 3:
				seg[5] &= 0x3F;
				seg[5] |= 0x40;
				seg[6] &= 0xBF;
				seg[6] |= 0x40;
				seg[15] &= 0x3F;
				seg[15] |= 0xC0;
				seg[16] &= 0x3F;
				seg[16] |= 0x80; // 数字3
				break;
			case 4:
				seg[5] &= 0x3F;
				seg[5] |= 0x80;
				seg[6] &= 0xBF;
				seg[6] |= 0x40;
				seg[15] &= 0x3F;
				seg[15] |= 0x80;
				seg[16] &= 0x3F;
				seg[16] |= 0x80; // 数字4
				break;
			case 5:
				seg[5] &= 0x3F;
				seg[5] |= 0xC0;
				seg[6] &= 0xBF;
				seg[6] |= 0x00;
				seg[15] &= 0x3F;
				seg[15] |= 0xC0;
				seg[16] &= 0x3F;
				seg[16] |= 0x80; // 数字5
				break;
			case 6:
				seg[5] &= 0x3F;
				seg[5] |= 0xC0;
				seg[6] &= 0xBF;
				seg[6] |= 0x00;
				seg[15] &= 0x3F;
				seg[15] |= 0xC0;
				seg[16] &= 0x3F;
				seg[16] |= 0xC0; // 数字6
				break;
			case 7:
				seg[5] &= 0x3F;
				seg[5] |= 0x40;
				seg[6] &= 0xBF;
				seg[6] |= 0x40;
				seg[15] &= 0x3F;
				seg[15] |= 0x80;
				seg[16] &= 0x3F;
				seg[16] |= 0x00; // 数字7
				break;
			case 8:
				seg[5] &= 0x3F;
				seg[5] |= 0xC0;
				seg[6] &= 0xBF;
				seg[6] |= 0x40;
				seg[15] &= 0x3F;
				seg[15] |= 0xC0;
				seg[16] &= 0x3F;
				seg[16] |= 0xC0; // 数字8
				break;
			case 9:
				seg[5] &= 0x3F;
				seg[5] |= 0xC0;
				seg[6] &= 0xBF;
				seg[6] |= 0x40;
				seg[15] &= 0x3F;
				seg[15] |= 0xC0;
				seg[16] &= 0x3F;
				seg[16] |= 0x80; // 数字9
				break;
			default:
				break;
			}
		}
		else
		{
			seg[5] &= 0x3F;
			seg[5] |= 0xC0;
			seg[6] &= 0xBF;
			seg[6] |= 0x40;
			seg[15] &= 0x3F;
			seg[15] |= 0xC0;
			seg[16] &= 0x3F;
			seg[16] |= 0x40; // 数字0
		}

		if (dis_N > 0) // 大于等于0时
		{
			Val = dis_N % 10;
			switch (Val)
			{
			case 0:
				seg[7] &= 0x3F;
				seg[7] |= 0xC0;
				seg[8] &= 0xBF;
				seg[8] |= 0x40;
				seg[12] &= 0x3F;
				seg[12] |= 0xC0;
				seg[13] &= 0x3F;
				seg[13] |= 0x40; // 数字0
				break;
			case 1:
				seg[7] &= 0x3F;
				seg[7] |= 0x00;
				seg[8] &= 0xBF;
				seg[8] |= 0x40;
				seg[12] &= 0x3F;
				seg[12] |= 0x80;
				seg[13] &= 0x3F;
				seg[13] |= 0x00; // 数字1
				break;
			case 2:
				seg[7] &= 0x3F;
				seg[7] |= 0x40;
				seg[8] &= 0xBF;
				seg[8] |= 0x40;
				seg[12] &= 0x3F;
				seg[12] |= 0x40;
				seg[13] &= 0x3F;
				seg[13] |= 0xC0; // 数字2
				break;
			case 3:
				seg[7] &= 0x3F;
				seg[7] |= 0x40;
				seg[8] &= 0xBF;
				seg[8] |= 0x40;
				seg[12] &= 0x3F;
				seg[12] |= 0xC0;
				seg[13] &= 0x3F;
				seg[13] |= 0x80; // 数字3
				break;
			case 4:
				seg[7] &= 0x3F;
				seg[7] |= 0x80;
				seg[8] &= 0xBF;
				seg[8] |= 0x40;
				seg[12] &= 0x3F;
				seg[12] |= 0x80;
				seg[13] &= 0x3F;
				seg[13] |= 0x80; // 数字4
				break;
			case 5:
				seg[7] &= 0x3F;
				seg[7] |= 0xC0;
				seg[8] &= 0xBF;
				seg[8] |= 0x00;
				seg[12] &= 0x3F;
				seg[12] |= 0xC0;
				seg[13] &= 0x3F;
				seg[13] |= 0x80; // 数字5
				break;
			case 6:
				seg[7] &= 0x3F;
				seg[7] |= 0xC0;
				seg[8] &= 0xBF;
				seg[8] |= 0x00;
				seg[12] &= 0x3F;
				seg[12] |= 0xC0;
				seg[13] &= 0x3F;
				seg[13] |= 0xC0; // 数字6
				break;
			case 7:
				seg[7] &= 0x3F;
				seg[7] |= 0x40;
				seg[8] &= 0xBF;
				seg[8] |= 0x40;
				seg[12] &= 0x3F;
				seg[12] |= 0x80;
				seg[13] &= 0x3F;
				seg[13] |= 0x00; // 数字7
				break;
			case 8:
				seg[7] &= 0x3F;
				seg[7] |= 0xC0;
				seg[8] &= 0xBF;
				seg[8] |= 0x40;
				seg[12] &= 0x3F;
				seg[12] |= 0xC0;
				seg[13] &= 0x3F;
				seg[13] |= 0xC0; // 数字8
				break;
			case 9:
				seg[7] &= 0x3F;
				seg[7] |= 0xC0;
				seg[8] &= 0xBF;
				seg[8] |= 0x40;
				seg[12] &= 0x3F;
				seg[12] |= 0xC0;
				seg[13] &= 0x3F;
				seg[13] |= 0x80; // 数字9
				break;
			default:
				break;
			}
		}
		else
		{
			seg[7] &= 0x3F;
			seg[7] |= 0xC0;
			seg[8] &= 0xBF;
			seg[8] |= 0x40;
			seg[12] &= 0x3F;
			seg[12] |= 0xC0;
			seg[13] &= 0x3F;
			seg[13] |= 0x40; // 数字0
		}

		/**********dis_temp**********/
		if (PT_VALUE_1_TEMP < 2000)
		{
			if (!Temp_ShowFlag)
			{
				if (dis_temp >= 0) // 大于等于0时
				{
					Val = dis_temp / 1000 % 10;
					switch (Val)
					{
					case 0:
						if (dis_temp > 999)
						{
							seg[19] &= 0xC7;
							seg[19] |= 0x38;
							seg[20] &= 0xC7;
							seg[20] |= 0x28;
							seg[21] &= 0xF7;
							seg[21] |= 0x08; // 数字0
						}
						else
						{
							seg[19] &= 0xC7;
							seg[19] |= 0x00;
							seg[20] &= 0xC7;
							seg[20] |= 0x00;
							seg[21] &= 0xF7;
							seg[21] |= 0x00; // 不显示
						}
						break;
					case 1:
						seg[19] &= 0xC7;
						seg[19] |= 0x18;
						seg[20] &= 0xC7;
						seg[20] |= 0x00;
						seg[21] &= 0xF7;
						seg[21] |= 0x00; // 数字1
						break;
					case 2:
						seg[19] &= 0xC7;
						seg[19] |= 0x30;
						seg[20] &= 0xC7;
						seg[20] |= 0x18;
						seg[21] &= 0xF7;
						seg[21] |= 0x08; // 数字2
						break;
					case 3:
						seg[19] &= 0xC7;
						seg[19] |= 0x38;
						seg[20] &= 0xC7;
						seg[20] |= 0x18;
						seg[21] &= 0xF7;
						seg[21] |= 0x00; // 数字3
						break;
					case 4:
						seg[19] &= 0xC7;
						seg[19] |= 0x18;
						seg[20] &= 0xC7;
						seg[20] |= 0x30;
						seg[21] &= 0xF7;
						seg[21] |= 0x00; // 数字4
						break;
					case 5:
						seg[19] &= 0xC7;
						seg[19] |= 0x28;
						seg[20] &= 0xC7;
						seg[20] |= 0x38;
						seg[21] &= 0xF7;
						seg[21] |= 0x00; // 数字5
						break;
					case 6:
						seg[19] &= 0xC7;
						seg[19] |= 0x28;
						seg[20] &= 0xC7;
						seg[20] |= 0x38;
						seg[21] &= 0xF7;
						seg[21] |= 0x08; // 数字6
						break;
					case 7:
						seg[19] &= 0xC7;
						seg[19] |= 0x38;
						seg[20] &= 0xC7;
						seg[20] |= 0x00;
						seg[21] &= 0xF7;
						seg[21] |= 0x00; // 数字7
						break;
					case 8:
						seg[19] &= 0xC7;
						seg[19] |= 0x38;
						seg[20] &= 0xC7;
						seg[20] |= 0x38;
						seg[21] &= 0xF7;
						seg[21] |= 0x08; // 数字8
						break;
					case 9:
						seg[19] &= 0xC7;
						seg[19] |= 0x38;
						seg[20] &= 0xC7;
						seg[20] |= 0x38;
						seg[21] &= 0xF7;
						seg[21] |= 0x00; // 数字9
						break;
					default:
						seg[19] &= 0xC7;
						seg[19] |= 0x00;
						seg[20] &= 0xC7;
						seg[20] |= 0x00;
						seg[21] &= 0xF7;
						seg[21] |= 0x00; // 不显示
						break;
					}

					Val = dis_temp / 100 % 10;
					switch (Val)
					{
					case 0:
						if (dis_temp > 99)
						{
							seg[16] &= 0xDF;
							seg[16] |= 0x20;
							seg[17] &= 0xC7;
							seg[17] |= 0x28;
							seg[18] &= 0xC7;
							seg[18] |= 0x38; // 数字0
						}
						else
						{
							seg[16] &= 0xDF;
							seg[16] |= 0x00;
							seg[17] &= 0xC7;
							seg[17] |= 0x00;
							seg[18] &= 0xC7;
							seg[18] |= 0x00; // 不显示
						}
						break;
					case 1:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x08;
						seg[18] &= 0xC7;
						seg[18] |= 0x00; // 数字1
						break;
					case 2:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x30;
						seg[18] &= 0xC7;
						seg[18] |= 0x18; // 数字2
						break;
					case 3:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x08; // 数字3
						break;
					case 4:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x18;
						seg[18] &= 0xC7;
						seg[18] |= 0x20; // 数字4
						break;
					case 5:
						seg[16] &= 0xDF;
						seg[16] |= 0x00;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x28; // 数字5
						break;
					case 6:
						seg[16] &= 0xDF;
						seg[16] |= 0x00;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x38; // 数字6
						break;
					case 7:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x28;
						seg[18] &= 0xC7;
						seg[18] |= 0x00; // 数字7
						break;
					case 8:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x38; // 数字8
						break;
					case 9:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x28; // 数字9
						break;
					default:
						break;
					}
					Val = dis_temp / 10 % 10;
					switch (Val)
					{
					case 0:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x28;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字0
						break;
					case 1:
						seg[14] &= 0x9F;
						seg[14] |= 0x20;
						seg[15] &= 0xC7;
						seg[15] |= 0x08;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字1
						break;
					case 2:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x10;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字2
						break;
					case 3:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x18;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字3
						break;
					case 4:
						seg[14] &= 0x9F;
						seg[14] |= 0x20;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字4
						break;
					case 5:
						seg[14] &= 0x9F;
						seg[14] |= 0x40;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字5
						break;
					case 6:
						seg[14] &= 0x9F;
						seg[14] |= 0x40;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字6
						break;
					case 7:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x08;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字7
						break;
					case 8:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字8
						break;
					case 9:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字9
						break;
					default:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x28;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字0
						break;
					}
					Val = dis_temp % 10;
					switch (Val)
					{
					case 0:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x28;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字0
						break;
					case 1:
						seg[12] &= 0xC7;
						seg[12] |= 0x18;
						seg[13] &= 0xC7;
						seg[13] |= 0x00;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字1
						break;
					case 2:
						seg[12] &= 0xC7;
						seg[12] |= 0x30;
						seg[13] &= 0xC7;
						seg[13] |= 0x18;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字2
						break;
					case 3:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x18;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字3
						break;
					case 4:
						seg[12] &= 0xC7;
						seg[12] |= 0x18;
						seg[13] &= 0xC7;
						seg[13] |= 0x30;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字4
						break;
					case 5:
						seg[12] &= 0xC7;
						seg[12] |= 0x28;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字5
						break;
					case 6:
						seg[12] &= 0xC7;
						seg[12] |= 0x28;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字6
						break;
					case 7:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x00;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字7
						break;
					case 8:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字8
						break;
					case 9:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字9
						break;
					default:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x28;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字0
						break;
					}
				}
				else if (dis_temp < 0 && dis_temp > -100)
				{
					seg[19] &= 0xC7;
					seg[19] |= 0x00;
					seg[20] &= 0xC7;
					seg[20] |= 0x00;
					seg[21] &= 0xF7;
					seg[21] |= 0x00;
					seg[16] &= 0xDF;
					seg[16] |= 0x00;
					seg[17] &= 0xC7;
					seg[17] |= 0x10;
					seg[18] &= 0xC7;
					seg[18] |= 0x00;
					Val = ABS(dis_temp) / 10 % 10;
					switch (Val)
					{
					case 0:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x28;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字0
						break;
					case 1:
						seg[14] &= 0x9F;
						seg[14] |= 0x20;
						seg[15] &= 0xC7;
						seg[15] |= 0x08;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字1
						break;
					case 2:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x10;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字2
						break;
					case 3:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x18;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字3
						break;
					case 4:
						seg[14] &= 0x9F;
						seg[14] |= 0x20;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字4
						break;
					case 5:
						seg[14] &= 0x9F;
						seg[14] |= 0x40;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字5
						break;
					case 6:
						seg[14] &= 0x9F;
						seg[14] |= 0x40;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字6
						break;
					case 7:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x08;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字7
						break;
					case 8:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字8
						break;
					case 9:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字9
						break;
					default:
						break;
					}
					Val = ABS(dis_temp) % 10;
					switch (Val)
					{
					case 0:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x28;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字0
						break;
					case 1:
						seg[12] &= 0xC7;
						seg[12] |= 0x18;
						seg[13] &= 0xC7;
						seg[13] |= 0x00;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字1
						break;
					case 2:
						seg[12] &= 0xC7;
						seg[12] |= 0x30;
						seg[13] &= 0xC7;
						seg[13] |= 0x18;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字2
						break;
					case 3:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x18;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字3
						break;
					case 4:
						seg[12] &= 0xC7;
						seg[12] |= 0x18;
						seg[13] &= 0xC7;
						seg[13] |= 0x30;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字4
						break;
					case 5:
						seg[12] &= 0xC7;
						seg[12] |= 0x28;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字5
						break;
					case 6:
						seg[12] &= 0xC7;
						seg[12] |= 0x28;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字6
						break;
					case 7:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x00;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字7
						break;
					case 8:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字8
						break;
					case 9:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字9
						break;
					default:
						break;
					}
				}
				else if (dis_temp <= -100 && dis_temp > -1000)
				{
					seg[19] &= 0xC7;
					seg[19] |= 0x00;
					seg[20] &= 0xC7;
					seg[20] |= 0x10;
					seg[21] &= 0xF7;
					seg[21] |= 0x00;
					Val = ABS(dis_temp) / 100 % 10;
					switch (Val)
					{
					case 0:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x28;
						seg[18] &= 0xC7;
						seg[18] |= 0x38; // 数字0
						break;
					case 1:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x08;
						seg[18] &= 0xC7;
						seg[18] |= 0x00; // 数字1
						break;
					case 2:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x30;
						seg[18] &= 0xC7;
						seg[18] |= 0x18; // 数字2
						break;
					case 3:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x08; // 数字3
						break;
					case 4:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x18;
						seg[18] &= 0xC7;
						seg[18] |= 0x20; // 数字4
						break;
					case 5:
						seg[16] &= 0xDF;
						seg[16] |= 0x00;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x28; // 数字5
						break;
					case 6:
						seg[16] &= 0xDF;
						seg[16] |= 0x00;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x38; // 数字6
						break;
					case 7:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x28;
						seg[18] &= 0xC7;
						seg[18] |= 0x00; // 数字7
						break;
					case 8:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x38; // 数字8
						break;
					case 9:
						seg[16] &= 0xDF;
						seg[16] |= 0x20;
						seg[17] &= 0xC7;
						seg[17] |= 0x38;
						seg[18] &= 0xC7;
						seg[18] |= 0x28; // 数字9
						break;
					default:
						seg[16] &= 0xDF;
						seg[16] |= 0x00;
						seg[17] &= 0xC7;
						seg[17] |= 0x00;
						seg[18] &= 0xC7;
						seg[18] |= 0x00; // 不显示
						break;
					}
					Val = ABS(dis_temp) / 10 % 10;
					switch (Val)
					{
					case 0:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x28;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字0
						break;
					case 1:
						seg[14] &= 0x9F;
						seg[14] |= 0x20;
						seg[15] &= 0xC7;
						seg[15] |= 0x08;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字1
						break;
					case 2:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x10;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字2
						break;
					case 3:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x18;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字3
						break;
					case 4:
						seg[14] &= 0x9F;
						seg[14] |= 0x20;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字4
						break;
					case 5:
						seg[14] &= 0x9F;
						seg[14] |= 0x40;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字5
						break;
					case 6:
						seg[14] &= 0x9F;
						seg[14] |= 0x40;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字6
						break;
					case 7:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x08;
						seg[16] &= 0xE7;
						seg[16] |= 0x00; // 数字7
						break;
					case 8:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x18; // 数字8
						break;
					case 9:
						seg[14] &= 0x9F;
						seg[14] |= 0x60;
						seg[15] &= 0xC7;
						seg[15] |= 0x38;
						seg[16] &= 0xE7;
						seg[16] |= 0x08; // 数字9
						break;
					default:
						break;
					}
					Val = ABS(dis_temp) % 10;
					switch (Val)
					{
					case 0:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x28;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字0
						break;
					case 1:
						seg[12] &= 0xC7;
						seg[12] |= 0x18;
						seg[13] &= 0xC7;
						seg[13] |= 0x00;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字1
						break;
					case 2:
						seg[12] &= 0xC7;
						seg[12] |= 0x30;
						seg[13] &= 0xC7;
						seg[13] |= 0x18;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字2
						break;
					case 3:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x18;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字3
						break;
					case 4:
						seg[12] &= 0xC7;
						seg[12] |= 0x18;
						seg[13] &= 0xC7;
						seg[13] |= 0x30;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字4
						break;
					case 5:
						seg[12] &= 0xC7;
						seg[12] |= 0x28;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字5
						break;
					case 6:
						seg[12] &= 0xC7;
						seg[12] |= 0x28;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字6
						break;
					case 7:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x00;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字7
						break;
					case 8:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x10; // 数字8
						break;
					case 9:
						seg[12] &= 0xC7;
						seg[12] |= 0x38;
						seg[13] &= 0xC7;
						seg[13] |= 0x38;
						seg[14] &= 0xEF;
						seg[14] |= 0x00; // 数字9
						break;
					default:
						break;
					}
				}
			}
			else
			{
				seg[19] &= 0xC7;
				seg[19] |= 0x00;
				seg[20] &= 0xC7;
				seg[20] |= 0x00;
				seg[21] &= 0xF7;
				seg[21] |= 0x00; // 不显示
				seg[16] &= 0xDF;
				seg[16] |= 0x00;
				seg[17] &= 0xC7;
				seg[17] |= 0x00;
				seg[18] &= 0xC7;
				seg[18] |= 0x00; // 不显示
				seg[14] &= 0x9F;
				seg[14] |= 0x00;
				seg[15] &= 0xC7;
				seg[15] |= 0x00;
				seg[16] &= 0xE7;
				seg[16] |= 0x00; // 不显示
				seg[12] &= 0xC7;
				seg[12] |= 0x00;
				seg[13] &= 0xC7;
				seg[13] |= 0x00;
				seg[14] &= 0xEF;
				seg[14] |= 0x00; // 不显示
			}
		}
		else
		{
			seg[19] &= 0xC7;
			seg[19] |= 0x00;
			seg[20] &= 0xC7;
			seg[20] |= 0x10;
			seg[21] &= 0xF7;
			seg[21] |= 0x00; // "-"

			seg[16] &= 0xDF;
			seg[16] |= 0x00;
			seg[17] &= 0xC7;
			seg[17] |= 0x10;
			seg[18] &= 0xC7;
			seg[18] |= 0x00; // "-"

			seg[14] &= 0x9F;
			seg[14] |= 0x00;
			seg[15] &= 0xC7;
			seg[15] |= 0x10;
			seg[16] &= 0xE7;
			seg[16] |= 0x00; // "-"

			seg[12] &= 0xC7;
			seg[12] |= 0x00;
			seg[13] &= 0xC7;
			seg[13] |= 0x10;
			seg[14] &= 0xEF;
			seg[14] |= 0x00; // "-"
		}
		/**********dis_time**********/
		if (!Time_ShowFlag)
		{
			if (Time.Set) // 假如设定时间大于0
			{
				/**********时间计算**********/
				if (Time.Set < 3600)
				{
					SH = dis_time % 3600 / 60 / 10; // 计算十位为单位的分钟数
					H = dis_time % 3600 / 60 % 10;	// 计算个位为单位的分钟数
					SM = dis_time % 60 / 10;		// 计算十分位为单位的秒钟数
					M = dis_time % 60 % 10;			// 计算十分位为单位的秒钟数
				}
				else
				{
					SH = dis_time / 3600 / 10;		// 计算十位为单位的小时数
					H = dis_time / 3600 % 10;		// 计算个位为单位的小时数
					SM = dis_time % 3600 / 60 / 10; // 计算十分位为单位的分钟数
					M = dis_time % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
				}
				/**********时间冒号图标**********/
				seg[16] &= 0xFD;
				seg[16] |= 0x02; // 时间冒号图标COL
				switch (SH)
				{
				case 0:
					seg[19] &= 0xF8;
					seg[19] |= 0x07;
					seg[20] &= 0xF8;
					seg[20] |= 0x05;
					seg[21] &= 0xFE;
					seg[21] |= 0x01; // 数字0
					break;
				case 1:
					seg[19] &= 0xF8;
					seg[19] |= 0x03;
					seg[20] &= 0xF8;
					seg[20] |= 0x00;
					seg[21] &= 0xFE;
					seg[21] |= 0x00; // 数字1
					break;
				case 2:
					seg[19] &= 0xF8;
					seg[19] |= 0x06;
					seg[20] &= 0xF8;
					seg[20] |= 0x03;
					seg[21] &= 0xFE;
					seg[21] |= 0x01; // 数字2
					break;
				case 3:
					seg[19] &= 0xF8;
					seg[19] |= 0x07;
					seg[20] &= 0xF8;
					seg[20] |= 0x03;
					seg[21] &= 0xFE;
					seg[21] |= 0x00; // 数字3
					break;
				case 4:
					seg[19] &= 0xF8;
					seg[19] |= 0x03;
					seg[20] &= 0xF8;
					seg[20] |= 0x06;
					seg[21] &= 0xFE;
					seg[21] |= 0x00; // 数字4
					break;
				case 5:
					seg[19] &= 0xF8;
					seg[19] |= 0x05;
					seg[20] &= 0xF8;
					seg[20] |= 0x07;
					seg[21] &= 0xFE;
					seg[21] |= 0x00; // 数字5
					break;
				case 6:
					seg[19] &= 0xF8;
					seg[19] |= 0x05;
					seg[20] &= 0xF8;
					seg[20] |= 0x07;
					seg[21] &= 0xFE;
					seg[21] |= 0x01; // 数字6
					break;
				case 7:
					seg[19] &= 0xF8;
					seg[19] |= 0x07;
					seg[20] &= 0xF8;
					seg[20] |= 0x00;
					seg[21] &= 0xFE;
					seg[21] |= 0x00; // 数字7
					break;
				case 8:
					seg[19] &= 0xF8;
					seg[19] |= 0x07;
					seg[20] &= 0xF8;
					seg[20] |= 0x07;
					seg[21] &= 0xFE;
					seg[21] |= 0x01; // 数字8
					break;
				case 9:
					seg[19] &= 0xF8;
					seg[19] |= 0x07;
					seg[20] &= 0xF8;
					seg[20] |= 0x07;
					seg[21] &= 0xFE;
					seg[21] |= 0x00; // 数字9
					break;
				default:
					break;
				}
				switch (H)
				{
				case 0:
					seg[16] &= 0xFB;
					seg[16] |= 0x04;
					seg[17] &= 0xF8;
					seg[17] |= 0x05;
					seg[18] &= 0xF8;
					seg[18] |= 0x07; // 数字0
					break;
				case 1:
					seg[16] &= 0xFB;
					seg[16] |= 0x04;
					seg[17] &= 0xF8;
					seg[17] |= 0x01;
					seg[18] &= 0xF8;
					seg[18] |= 0x00; // 数字1
					break;
				case 2:
					seg[16] &= 0xFB;
					seg[16] |= 0x04;
					seg[17] &= 0xF8;
					seg[17] |= 0x06;
					seg[18] &= 0xF8;
					seg[18] |= 0x03; // 数字2
					break;
				case 3:
					seg[16] &= 0xFB;
					seg[16] |= 0x04;
					seg[17] &= 0xF8;
					seg[17] |= 0x07;
					seg[18] &= 0xF8;
					seg[18] |= 0x01; // 数字3
					break;
				case 4:
					seg[16] &= 0xFB;
					seg[16] |= 0x04;
					seg[17] &= 0xF8;
					seg[17] |= 0x03;
					seg[18] &= 0xF8;
					seg[18] |= 0x04; // 数字4
					break;
				case 5:
					seg[16] &= 0xFB;
					seg[16] |= 0x00;
					seg[17] &= 0xF8;
					seg[17] |= 0x07;
					seg[18] &= 0xF8;
					seg[18] |= 0x05; // 数字5
					break;
				case 6:
					seg[16] &= 0xFB;
					seg[16] |= 0x00;
					seg[17] &= 0xF8;
					seg[17] |= 0x07;
					seg[18] &= 0xF8;
					seg[18] |= 0x07; // 数字6
					break;
				case 7:
					seg[16] &= 0xFB;
					seg[16] |= 0x04;
					seg[17] &= 0xF8;
					seg[17] |= 0x05;
					seg[18] &= 0xF8;
					seg[18] |= 0x00; // 数字7
					break;
				case 8:
					seg[16] &= 0xFB;
					seg[16] |= 0x04;
					seg[17] &= 0xF8;
					seg[17] |= 0x07;
					seg[18] &= 0xF8;
					seg[18] |= 0x07; // 数字8
					break;
				case 9:
					seg[16] &= 0xFB;
					seg[16] |= 0x04;
					seg[17] &= 0xF8;
					seg[17] |= 0x07;
					seg[18] &= 0xF8;
					seg[18] |= 0x05; // 数字9
					break;
				default:
					break;
				}

				switch (SM)
				{
				case 0:
					seg[14] &= 0xF8;
					seg[14] |= 0x07;
					seg[15] &= 0xF8;
					seg[15] |= 0x05;
					seg[16] &= 0xFE;
					seg[16] |= 0x01; // 数字0
					break;
				case 1:
					seg[14] &= 0xF8;
					seg[14] |= 0x03;
					seg[15] &= 0xF8;
					seg[15] |= 0x00;
					seg[16] &= 0xFE;
					seg[16] |= 0x00; // 数字1
					break;
				case 2:
					seg[14] &= 0xF8;
					seg[14] |= 0x06;
					seg[15] &= 0xF8;
					seg[15] |= 0x03;
					seg[16] &= 0xFE;
					seg[16] |= 0x01; // 数字2
					break;
				case 3:
					seg[14] &= 0xF8;
					seg[14] |= 0x07;
					seg[15] &= 0xF8;
					seg[15] |= 0x03;
					seg[16] &= 0xFE;
					seg[16] |= 0x00; // 数字3
					break;
				case 4:
					seg[14] &= 0xF8;
					seg[14] |= 0x03;
					seg[15] &= 0xF8;
					seg[15] |= 0x06;
					seg[16] &= 0xFE;
					seg[16] |= 0x00; // 数字4
					break;
				case 5:
					seg[14] &= 0xF8;
					seg[14] |= 0x05;
					seg[15] &= 0xF8;
					seg[15] |= 0x07;
					seg[16] &= 0xFE;
					seg[16] |= 0x00; // 数字5
					break;
				case 6:
					seg[14] &= 0xF8;
					seg[14] |= 0x05;
					seg[15] &= 0xF8;
					seg[15] |= 0x07;
					seg[16] &= 0xFE;
					seg[16] |= 0x01; // 数字6
					break;
				case 7:
					seg[14] &= 0xF8;
					seg[14] |= 0x07;
					seg[15] &= 0xF8;
					seg[15] |= 0x00;
					seg[16] &= 0xFE;
					seg[16] |= 0x00; // 数字7
					break;
				case 8:
					seg[14] &= 0xF8;
					seg[14] |= 0x07;
					seg[15] &= 0xF8;
					seg[15] |= 0x07;
					seg[16] &= 0xFE;
					seg[16] |= 0x01; // 数字8
					break;
				case 9:
					seg[14] &= 0xF8;
					seg[14] |= 0x07;
					seg[15] &= 0xF8;
					seg[15] |= 0x07;
					seg[16] &= 0xFE;
					seg[16] |= 0x00; // 数字9
					break;
				default:
					break;
				}

				switch (M)
				{
				case 0:
					seg[11] &= 0xFB;
					seg[11] |= 0x04;
					seg[12] &= 0xF8;
					seg[12] |= 0x05;
					seg[13] &= 0xF8;
					seg[13] |= 0x07; // 数字0
					break;
				case 1:
					seg[11] &= 0xFB;
					seg[11] |= 0x04;
					seg[12] &= 0xF8;
					seg[12] |= 0x01;
					seg[13] &= 0xF8;
					seg[13] |= 0x00; // 数字1
					break;
				case 2:
					seg[11] &= 0xFB;
					seg[11] |= 0x04;
					seg[12] &= 0xF8;
					seg[12] |= 0x06;
					seg[13] &= 0xF8;
					seg[13] |= 0x03; // 数字2
					break;
				case 3:
					seg[11] &= 0xFB;
					seg[11] |= 0x04;
					seg[12] &= 0xF8;
					seg[12] |= 0x07;
					seg[13] &= 0xF8;
					seg[13] |= 0x01; // 数字3
					break;
				case 4:
					seg[11] &= 0xFB;
					seg[11] |= 0x04;
					seg[12] &= 0xF8;
					seg[12] |= 0x03;
					seg[13] &= 0xF8;
					seg[13] |= 0x04; // 数字4
					break;
				case 5:
					seg[11] &= 0xFB;
					seg[11] |= 0x00;
					seg[12] &= 0xF8;
					seg[12] |= 0x07;
					seg[13] &= 0xF8;
					seg[13] |= 0x05; // 数字5
					break;
				case 6:
					seg[11] &= 0xFB;
					seg[11] |= 0x00;
					seg[12] &= 0xF8;
					seg[12] |= 0x07;
					seg[13] &= 0xF8;
					seg[13] |= 0x07; // 数字6
					break;
				case 7:
					seg[11] &= 0xFB;
					seg[11] |= 0x04;
					seg[12] &= 0xF8;
					seg[12] |= 0x05;
					seg[13] &= 0xF8;
					seg[13] |= 0x00; // 数字7
					break;
				case 8:
					seg[11] &= 0xFB;
					seg[11] |= 0x04;
					seg[12] &= 0xF8;
					seg[12] |= 0x07;
					seg[13] &= 0xF8;
					seg[13] |= 0x07; // 数字8
					break;
				case 9:
					seg[11] &= 0xFB;
					seg[11] |= 0x04;
					seg[12] &= 0xF8;
					seg[12] |= 0x07;
					seg[13] &= 0xF8;
					seg[13] |= 0x05; // 数字9
					break;
				default:
					break;
				}
			}
			else
			{
				seg[19] &= 0xF8;
				seg[19] |= 0x00;
				seg[20] &= 0xF8;
				seg[20] |= 0x02;
				seg[21] &= 0xFE;
				seg[21] |= 0x00; // 显示‘-’
				seg[16] &= 0xFB;
				seg[16] |= 0x00;
				seg[17] &= 0xF8;
				seg[17] |= 0x02;
				seg[18] &= 0xF8;
				seg[18] |= 0x00; // 显示‘-’
				seg[14] &= 0xF8;
				seg[14] |= 0x00;
				seg[15] &= 0xF8;
				seg[15] |= 0x02;
				seg[16] &= 0xFE;
				seg[16] |= 0x00; // 显示‘-’
				seg[11] &= 0xFB;
				seg[11] |= 0x00;
				seg[12] &= 0xF8;
				seg[12] |= 0x02;
				seg[13] &= 0xF8;
				seg[13] |= 0x00; // 显示‘-’
				/**********时间冒号图标**********/
				seg[16] &= 0xFD;
				seg[16] |= 0x00; // 时间冒号图标COL
			}
		}
		else
		{
			seg[19] &= 0xF8;
			seg[19] |= 0x00;
			seg[20] &= 0xF8;
			seg[20] |= 0x00;
			seg[21] &= 0xFE;
			seg[21] |= 0x00; // 不显示
			seg[16] &= 0xFB;
			seg[16] |= 0x00;
			seg[17] &= 0xF8;
			seg[17] |= 0x00;
			seg[18] &= 0xF8;
			seg[18] |= 0x00; // 不显示
			seg[14] &= 0xF8;
			seg[14] |= 0x00;
			seg[15] &= 0xF8;
			seg[15] |= 0x00;
			seg[16] &= 0xFE;
			seg[16] |= 0x00; // 不显示
			seg[11] &= 0xFB;
			seg[11] |= 0x00;
			seg[12] &= 0xF8;
			seg[12] |= 0x00;
			seg[13] &= 0xF8;
			seg[13] |= 0x00; // 不显示
		}

		/**********抖动图标**********/
		if (Shake_Switch == 0)
		{
			seg[9] &= 0xFB;
			seg[9] |= 0x00; // 抖动图标S4
			seg[9] &= 0xFD;
			seg[9] |= 0x00; // 抖动图标S1
			seg[10] &= 0xFE;
			seg[10] |= 0x00; // 抖动图标S2
			seg[0] &= 0xBF;
			seg[0] |= 0x00; // 抖动图标S5
			seg[10] &= 0xFD;
			seg[10] |= 0x00; // 抖动图标S3
		}
		else
		{
			seg[9] &= 0xFB;
			seg[9] |= 0x04; // 抖动图标S4
			seg[9] &= 0xFD;
			seg[9] |= 0x02; // 抖动图标S1
			seg[10] &= 0xFE;
			seg[10] |= 0x01; // 抖动图标S2
			seg[0] &= 0xBF;
			seg[0] |= 0x40; // 抖动图标S5
			seg[10] &= 0xFD;
			seg[10] |= 0x02; // 抖动图标S3
		}

		/**********rpm**********/
		seg[9] &= 0xEF;
		seg[9] |= 0x10; // 设定转速单位rpm
		seg[9] &= 0xDF;
		seg[9] |= 0x20; // 实际转速单位rpm

		/**********转速图标**********/
		switch (Speed.IcnStep)
		{
		case 0:
			seg[0] &= 0x7F;
			seg[0] |= 0x80; // 转速图标S6
			seg[21] &= 0xBF;
			seg[21] |= 0x40; // 转速图标S7
			seg[21] &= 0x7F;
			seg[21] |= 0x80; // 转速图标S8
			break;

		case 1:
			seg[0] &= 0x7F;
			seg[0] |= 0x00; // 转速图标S6
			seg[21] &= 0xBF;
			seg[21] |= 0x40; // 转速图标S7
			seg[21] &= 0x7F;
			seg[21] |= 0x80; // 转速图标S8
			break;

		case 2:
			seg[0] &= 0x7F;
			seg[0] |= 0x80; // 转速图标S6
			seg[21] &= 0xBF;
			seg[21] |= 0x00; // 转速图标S7
			seg[21] &= 0x7F;
			seg[21] |= 0x80; // 转速图标S8
			break;

		case 3:
			seg[0] &= 0x7F;
			seg[0] |= 0x80; // 转速图标S6
			seg[21] &= 0xBF;
			seg[21] |= 0x40; // 转速图标S7
			seg[21] &= 0x7F;
			seg[21] |= 0x00; // 转速图标S8
			break;
		default:
			break;
		}

		/**********扭力图标**********/
		seg[21] &= 0xDF;
		seg[21] |= 0x20; // 扭力图标S9

		/**********扭力小数点图标**********/
		seg[14] &= 0x7F;
		seg[14] |= 0x80; // 扭力小数点图标DOT1

		/**********扭力单位图标**********/
		seg[11] &= 0xEF;
		seg[11] |= 0x10; // 扭力单位图标S15

		/**********安全温度图标**********/
		if (Temp.Safe_Mode)
		{
			seg[21] &= 0xEF;
			seg[21] |= 0x10; // 安全温度图标S10
		}
		else
		{
			seg[21] &= 0xEF;
			seg[21] |= 0x00; // 不显示安全温度图标S10
		}

		/**********安全温度小数点图标**********/
		if (PT_VALUE_1_TEMP < 2000)
		{
			seg[14] &= 0xF7;
			seg[14] |= 0x08; // 安全温度小数点图标DOT2
		}
		else
		{
			seg[14] &= 0xF7;
			seg[14] |= 0x00; // 安全温度小数点图标DOT2
		}

		/*********安全温度单位图标**********/
		if (PT_VALUE_1_TEMP < 2000)
		{
			seg[11] &= 0xF7;
			seg[11] |= 0x08; // 安全温度单位图标S16
		}
		else
		{
			seg[11] &= 0xF7;
			seg[11] |= 0x00; // 安全温度单位图标S16
		}
		/**********锁定图标**********/
		if (Lock_Switch)
		{
			seg[21] &= 0xFB;
			seg[21] |= 0x04; // 锁定图标S11
		}
		else
		{
			seg[21] &= 0xFB;
			seg[21] |= 0x00; // 不显示锁定图标S11
		}

		/**********时间图标**********/
		if (Time.Icn)
		{
			seg[21] &= 0xFD;
			seg[21] |= 0x00; // 时间图标S12
		}
		else
		{
			seg[21] &= 0xFD;
			seg[21] |= 0x02; // 时间图标S12
		}

		/*********时间单位图标**********/
		if (Time.Set < 3600)
		{
			seg[11] &= 0xFD;
			seg[11] |= 0x02; // 时间单位图标sec
			seg[11] &= 0xFE;
			seg[11] |= 0x00; // 时间单位图标min
		}
		else
		{
			seg[11] &= 0xFD;
			seg[11] |= 0x00; // 时间单位图标sec
			seg[11] &= 0xFE;
			seg[11] |= 0x01; // 时间单位图标min
		}
	}
	else
	{
		for (uint8_t i = 0; i < 22; i++)
		{
			seg[i] = 0x00;
		}
		if (Shake_Step == 2 || Shake_Step == 4 || Shake_Switch == 0)
		{
			seg[9] &= 0xFB;
			seg[9] |= 0x00; // 抖动图标S4
			seg[9] &= 0xFD;
			seg[9] |= 0x00; // 抖动图标S1
			seg[10] &= 0xFE;
			seg[10] |= 0x00; // 抖动图标S2
			seg[0] &= 0xBF;
			seg[0] |= 0x00; // 抖动图标S5
			seg[10] &= 0xFD;
			seg[10] |= 0x00; // 抖动图标S3
		}
		else
		{
			seg[9] &= 0xFB;
			seg[9] |= 0x04; // 抖动图标S4
			seg[9] &= 0xFD;
			seg[9] |= 0x02; // 抖动图标S1
			seg[10] &= 0xFE;
			seg[10] |= 0x01; // 抖动图标S2
			seg[0] &= 0xBF;
			seg[0] |= 0x40; // 抖动图标S5
			seg[10] &= 0xFD;
			seg[10] |= 0x02; // 抖动图标S3
		}
	}
	/**********发送数据**********/
	for (uint8_t i = 0; i < 22; i++)
	{
		Write_Addr_Dat_N(i * 2, seg[i], 1);
	}
}

/**
 * @brief 速度显示处理
 *
 * @param dT 任务周期
 */
void Deal_Speed(float dT)
{
	if (sys.Run_Status == 1)
	{
		if (Speed.ADDMode == 0) // 在电机控制中，速度未处理
		{
			if (Speed.Ctrl >= Speed.Display_Rel) // 控制速度大于实际速度
			{
				Speed.ADDMode = 1; // 进入加速模式下
			}
			else if (Speed.Ctrl < Speed.Display_Rel) // 控制速度小于实际速度
			{
				Speed.ADDMode = 2; // 进入减速模式下
			}
		}
		if (Speed.ADDMode == 1) // 在进入加速模式下
		{
			if (Speed.Rel > Speed.Display_Rel) // 当前速度大于显示速度
			{
				if (Speed.Display_Rel < Speed.Rel)
					Speed.Display_Rel += 1; // 显示当前速度
			}
			else // 当前速度小于上一次速度
			{
				Speed.Display_Rel = Speed.Display_Rel; // 显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
			}
			if (Speed.Display_Rel >= Speed.Ctrl) // 实际速度大于等于控制速度
			{
				Speed.ADDMode = 3; // 进入稳定模式
				return;
			}
		}
		if (Speed.ADDMode == 2) // 速度下降模式下
		{
			if (Speed.Rel < Speed.Display_Rel) // 当前速度小于上一次速度
			{
				if (Speed.Display_Rel > Speed.Rel)
					Speed.Display_Rel -= 1; // 显示当前速度
			}
			else // 当前速度大于上一次速度
			{
				Speed.Display_Rel = Speed.Display_Rel; // 显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
			}

			if (Speed.Display_Rel <= Speed.Ctrl) // 实际速度小于等于控制速度
			{
				Speed.ADDMode = 3; // 进入稳定模式
				return;
			}
		}
		else if (Speed.ADDMode == 3) // 速度稳定模式下
		{
			Speed.Display_Rel = Speed.Ctrl; // 显示控制速度
		}
	}
	else
	{
		if (Speed.Display_Rel && Speed.Display_Rel > Speed.Rel)
			Speed.Display_Rel -= 1; // 显示当前速度
	}
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(void)
{
	Speed.Display_Set = Speed.Set;

	if (sys.SetMode_Option == 2)
	{
		Temp.Display = Temp.Set;
	}
	else
	{
		Temp.Display = Temp.Rel;
	}

	if (sys.Run_Status)
	{
		Time.Display = Time.Rel;
	}
	else
	{
		Time.Display = Time.Set;
	}
	Speed.Display_N = Speed.N_Val;

	Display_Show(Speed.Display_Rel, Speed.Display_Set, Speed.Display_N, Temp.Display, Time.Display);
}
