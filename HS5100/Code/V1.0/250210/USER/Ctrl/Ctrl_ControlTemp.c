#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;

/**********局部变量声明******/
uint8_t Out_Enable;//积分运算的开关
float adc_val,ctrl_val;
uint8_t water_type,step;//判断是油还是水0：水，1油
uint8_t Temp_type;//温度类型
int Heat;//加热盘的pwm值

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
	Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 8*0.001f;//18
	Temp_Arg.Kd = 90*0.001f;;//控台面
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
 * 功    能：台面温度控制
*****************************************************************
*/
static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
{
    static float T;
    static float T1;
    
    if(Ctrl_temp > Temp.Safe_Temp - 500) Ctrl_temp = Temp.Safe_Temp - 500;//最高加热Temp_MAX度
    if ((Ctrl_temp > 1000)&&(Temp.Rel < Ctrl_temp - 150))//达到目标温度-0.5℃前全速加热
    {
        Heat = 399;
    }
    else if ((Ctrl_temp <= 1000)&&Temp.Rel < Ctrl_temp - 100)//达到目标温度-0.5℃前全速加热
    {
        T += dT;
        if(T <3.0f)
            Heat = 399;
        else if(T >= 3.0f && T < 5.0f)
            Heat = 0;
        else
             T = 0;
    }
    else if ((Ctrl_temp > 1000)&&Temp.Rel < Ctrl_temp)//达到目标温度-0.5℃前全速加热
    {
        Heat = 399;
    }
    else if (Temp.Rel >= Ctrl_temp + 10) //超出设置值1℃时全关
    {
        Heat = 0;
    }
    else    //PID控制
    {   //设定加热周期为1000ms，1000分之PID_Para.pid_result毫秒开加热器
        ctrl_val = Get_ADCVal(Ctrl_temp);//查表读ADC值
        
        adc_val = PT_VALUE_2_TEMP;//实际的adc值
        
        if(Ctrl_temp > 2300 && Temp.Mesa > 2000)//如果控制温度大于230度，台面温度超过200度
            Out_Enable = 1;//打开积分计算
        else if((ctrl_val - adc_val > -200 && ctrl_val - adc_val < 200))
            Out_Enable = 1;//打开积分计算
        else
            Out_Enable = 0;//关闭积分计算
        
        if(Temp.Up_Speed == 1)//快速
        {
            Temp_Arg.Kp = 1000*0.001f;
            Temp_Arg.Ki = 12*0.001f;//18
            Temp_Arg.Kd = 0 * 0.001f;
        }
        else if(Speed.Up_Speed == 2)//慢速
        {
            Temp_Arg.Kp = 200*0.001f;
            Temp_Arg.Ki = 3*0.001f;//18
            Temp_Arg.Kd = 0 * 0.001f;
        }
        else//正常
        {
            Temp_Arg.Kp = 500*0.001f;
            Temp_Arg.Ki = 6*0.001f;//18
            Temp_Arg.Kd = 0 * 0.001f;
        }
            
        AltPID_Calculation(dT, ctrl_val, adc_val, &Temp_Arg, &Temp_Val, 100, Out_Enable * 100);
        if(Temp_Val.Out < 0)
            Temp_Val.Out = 0;
        if(Temp_Val.Out > 100)
            Temp_Val.Out = 100;
        
        T1 += dT;
        if (T1 <= (float)(Temp_Val.Out/10))
        {
            Heat =300;
        }
        else
        {
            Heat =0;
        }
        if(T1 > 10.0f)
            T1 = 0;
    }
    if(Temp.Rel<=Temp.Ctrl)
        HEAT = Heat;
    else
        HEAT = 0;
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
				if(Temp.Ctrl - Temp.Rel > 100)
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
