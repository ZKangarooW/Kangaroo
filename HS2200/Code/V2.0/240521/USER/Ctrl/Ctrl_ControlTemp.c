#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********局部变量声明******/
uint8_t Out_Enable;//积分运算的开关
float adc_val,ctrl_val;
uint8_t water_type,step;//判断是油还是水0：水，1油
uint8_t Temp_type;//温度类型

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
	Temp_Arg.Kp = 700*0.001f;
	Temp_Arg.Ki = 20*0.001f;
	Temp_Arg.Kd = 30;//控台面
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
	if(Ctrl_temp > Temp_MAX) Ctrl_temp = Temp_MAX;//最高加热Temp_MAX度
	adc_val = Get_ADCVal(Ctrl_temp)*10;//查表读ADC值
	ctrl_val = PT_VALUE_2_TEMP*10;//实际的adc值
	if(Ctrl_temp > 2300 && Temp.Mesa > 2000)//如果控制温度大于230度，台面温度超过200度
		Out_Enable = 1;//打开积分计算
	else if((adc_val - ctrl_val > -200 && adc_val - ctrl_val < 200))
		Out_Enable = 1;//打开积分计算
	else
		Out_Enable = 0;//关闭积分计算
	AltPID_Calculation(dT, adc_val, ctrl_val, &Temp_Arg, &Temp_Val, 100, Out_Enable * 1000);
	if(Temp_Val.Out < 0)
		Temp_Val.Out = 0;
	HEAT =(int)Temp_Val.Out;
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if(sys.Run_Status && PT_VALUE_1_TEMP >= 2200)//启动系统控制台面
	{
		if(Temp_type == 1)//如果是外部探头切换过来
		{
			Temp.ADDMode = 0;
			Temp_type = 0;
		}
		if(Temp.Ctrl)
		{
			Mesa_Ctrl(dT, Temp.Ctrl);
		}
		else
		{
			water_type = 0;
			HEAT = 0;//pwm不输出
			step = 0;
		}
	}
	else if(sys.Run_Status && PT_VALUE_1_TEMP < 2200)//启动系统控制水温
	{
		if(Temp.Ctrl)
		{	
			if(Temp_type == 0)//如果是台面探头切换过来
			{
				Temp.ADDMode = 0;
				Temp_type = 1;
			}
			if(Temp.Ctrl < 1000)//控制温度小于100℃
			{
                if(Temp.Ctrl - Temp.Rel >= 150)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 3.1f);
				}
				else if(Temp.Ctrl - Temp.Rel < 150 && Temp.Ctrl - Temp.Rel >= 100)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.8f);
				}
				else if(Temp.Ctrl - Temp.Rel < 100 && Temp.Ctrl - Temp.Rel >= 50)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.5f);
				}
				else if(Temp.Ctrl - Temp.Rel < 50 && Temp.Ctrl - Temp.Rel >= 10)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.2f);
				}
				else if(Temp.Ctrl - Temp.Rel < 10 && Temp.Ctrl - Temp.Rel > 0)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 1.8f);
				}
				else
				{
					Temp_Val.Out = 0;
					HEAT = (int)Temp_Val.Out;
				}
			}
			else if(Temp.Ctrl == 1000)//控制温度等于100℃
			{
				if(!water_type)
				{
					if(step == 0)
					{
						Mesa_Ctrl(dT, 3100);
						if(Temp.Rel >= 1000)
						{
							step = 1;
						}
					}
					else if(step == 1)
					{
						Mesa_Ctrl(dT, 2200);
					}
					if(Temp.Rel >= 1040)
					{
						water_type = 1;//判断为油
					}
				}
				else
				{
					if(Temp.Ctrl - Temp.Rel >= 150)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 3.1f);
                    }
                    else if(Temp.Ctrl - Temp.Rel < 150 && Temp.Ctrl - Temp.Rel >= 100)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 2.8f);
                    }
                    else if(Temp.Ctrl - Temp.Rel < 100 && Temp.Ctrl - Temp.Rel >= 50)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 2.5f);
                    }
                    else if(Temp.Ctrl - Temp.Rel < 50 && Temp.Ctrl - Temp.Rel >= 10)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 2.2f);
                    }
                    else if(Temp.Ctrl - Temp.Rel < 10 && Temp.Ctrl - Temp.Rel > 0)
                    {
                        Mesa_Ctrl(dT, Temp.Ctrl * 1.8f);
                    }
					else
					{
						Temp_Val.Out = 0;
						HEAT = (int)Temp_Val.Out;
					}
				}
			}
			else if(Temp.Ctrl > 1000)//控制温度大于100℃
			{
				if(Temp.Ctrl - Temp.Rel >= 150)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 3.1f);
				}
				else if(Temp.Ctrl - Temp.Rel < 150 && Temp.Ctrl - Temp.Rel >= 100)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.8f);
				}
				else if(Temp.Ctrl - Temp.Rel < 100 && Temp.Ctrl - Temp.Rel >= 50)
                {
					Mesa_Ctrl(dT, Temp.Ctrl * 2.2f);
				}
				else if(Temp.Ctrl - Temp.Rel < 100 && Temp.Ctrl - Temp.Rel >= 50)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 2.0f);
				}
				else if(Temp.Ctrl - Temp.Rel < 50 && Temp.Ctrl - Temp.Rel > 0)
				{
					Mesa_Ctrl(dT, Temp.Ctrl * 1.8f);
				}
				else
				{
					Temp_Val.Out = 0;
					HEAT =(int)Temp_Val.Out;
				}
			}
		}
		else
		{
			water_type = 0;
			HEAT = 0;//pwm不输出
			step = 0;
		}
	}
	else
	{
		water_type = 0;
		HEAT = 0;//pwm不输出
		step = 0;
	}
}
