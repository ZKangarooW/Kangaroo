#include "Ctrl_ControlTemp.h"

/**********结构体************/
_PID_Arg_ Temp_Arg[4];
_PID_Val_ Temp_Val[4];

/**********局部变量声明******/
uint8_t Out_Enable[4];//积分运算的开关
float adc_val[4],ctrl_val[4];
uint8_t water_type[4],step[4];//判断是油还是水0：水，1油
uint8_t Temp_type[4];//温度类型
int8_t Heat[4];//各个加热盘的pwm值

/*
*****************************************************************
 * 函数原型：void Temp_PID(void)
 * 功    能：温度控制PID系数
*****************************************************************
*/
void Temp_PID(void)
{
    for(uint8_t i = 0;i<4;i++)
    {
        Temp_Arg[i].Kp = 700*0.001f;
        Temp_Arg[i].Ki = 20*0.001f;
        Temp_Arg[i].Kd = 30;//控台面
    }
}

/*
*****************************************************************
 * 函数原型：void Motor_Out(int16_t Motor_Pwm[MOTOR_NUM])
 * 功    能：电机驱动
 * 输    入：int16_t Motor_Pwm[MOTOR_NUM]
 * 参    数：Motor_Pwm[MOTOR_NUM]各个Motor的PWM占空比值
*****************************************************************
*/
void Heat_Out(int8_t Heat_Pwm[4])
{
    HEAT0 = (uint8_t)Heat_Pwm[0];
    HEAT1 = (uint8_t)Heat_Pwm[1];
    HEAT2 = (uint8_t)Heat_Pwm[2];
    HEAT3 = (uint8_t)Heat_Pwm[3];
}

/*
*****************************************************************
 * 函数原型：static void Mesa_Ctrl(float dT, int32_t Ctrl_temp)
* 功    能：台面温度控制temp_c:控温的倍数
*****************************************************************
*/
static void Mesa_Ctrl(float dT, uint8_t i,int32_t Ctrl_temp)
{
	if(Ctrl_temp > Temp_MAX) Ctrl_temp = Temp_MAX;//最高加热Temp_MAX度
    
    ctrl_val[i] = Get_ADCVal(Ctrl_temp)*10;//查表读ADC值
    
    adc_val[i] = PT_VALUE_2_TEMP[i]*10;//实际的adc值
    
	if(Ctrl_temp > 2300 && Work_Num[i].Temp.Mesa > 2000)//如果控制温度大于230度，台面温度超过200度
		Out_Enable[i] = 1;//打开积分计算
	else if((ctrl_val - adc_val > -200 && ctrl_val - adc_val < 200))
		Out_Enable[i] = 1;//打开积分计算
	else
		Out_Enable[i] = 0;//关闭积分计算
    
	AltPID_Calculation(dT, ctrl_val[i], adc_val[i], &Temp_Arg[i], &Temp_Val[i], 100, Out_Enable[i] * 1000);
	if(Temp_Val[i].Out < 0)
		Temp_Val[i].Out = 0;
	Heat[i] =(int)Temp_Val[i].Out;
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    for(uint8_t i = 0;i<4;i++)
    {
        if(Work_Num[i].Run_Status && PT_VALUE_1_TEMP[i] >= 2200)//启动系统控制台面
        {
            if(Temp_type[i] == 1)//如果是外部探头切换过来
            {
                Work_Num[i].Temp.ADDMode = 0;
                Temp_type[i] = 0;
            }
            if(Work_Num[i].Temp.Ctrl)
            {
                Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl);
            }
            else
            {
                water_type[i] = 0;
                Heat[i] = 0;//pwm不输出
                step[i] = 0;
            }
        }
        else if(Work_Num[i].Run_Status && PT_VALUE_1_TEMP[i] < 2200)//启动系统控制水温
        {
            if(Work_Num[i].Temp.Ctrl)
            {
                if(Temp_type[i] == 0)//如果是台面探头切换过来
                {
                    Work_Num[i].Temp.ADDMode = 0;
                    Temp_type[i] = 1;
                }
                if(Work_Num[i].Temp.Ctrl < 1000)//控制温度小于100℃
                {
                    if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 150)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 3.1f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 150 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 100)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.8f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 100 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 50)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.5f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 50 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 10)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.2f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 10 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel > 0)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 1.8f);
                    }
                    else
                    {
                        Temp_Val[i].Out = 0;
                        Heat[i] = (int)Temp_Val[i].Out;
                    }
                }
                else if(Work_Num[i].Temp.Ctrl == 1000)//控制温度等于100℃
                {
                    if(!water_type[i])
                    {
                        if(step[i] == 0)
                        {
                            Mesa_Ctrl(dT, i, 3100);
                            if(Work_Num[i].Temp.Rel >= 1000)
                            {
                                step[i] = 1;
                            }
                        }
                        else if(step[i] == 1)
                        {
                            Mesa_Ctrl(dT, i, 2200);
                        }
                        if(Work_Num[i].Temp.Rel >= 1040)
                        {
                            water_type[i] = 1;//判断为油
                        }
                    }
                    else
                    {
                        if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 150)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 3.1f);
                        }
                        else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 150 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 100)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.8f);
                        }
                        else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 100 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 50)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.5f);
                        }
                        else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 50 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 10)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.2f);
                        }
                        else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 10 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel > 0)
                        {
                            Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 1.8f);
                        }
                        else
                        {
                            Temp_Val[i].Out = 0;
                            Heat[i] = (int)Temp_Val[i].Out;
                        }
                    }
                }
                else if(Work_Num[i].Temp.Ctrl > 1000)//控制温度大于100℃
                {
                    if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 150)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 3.1f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 150 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 100)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.8f);
                    }
                    if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel > 100)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.2f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 100 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel >= 50)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 2.0f);
                    }
                    else if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel < 50 && Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel > 0)
                    {
                        Mesa_Ctrl(dT, i, Work_Num[i].Temp.Ctrl * 1.8f);
                    }
                    else
                    {
                        Temp_Val[i].Out = 0;
                        Heat[i] = (int)Temp_Val[i].Out;
                    }
                }
            }
            else
            {
                water_type[i] = 0;
                Heat[i] = 0;//pwm不输出
                step[i] = 0;
            }
        }
        else
        {
            water_type[i] = 0;
            Heat[i] = 0;//pwm不输出
            step[i] = 0;
        }
    }
    Heat_Out(Heat);
}

/**
 * @brief 温度任务
 * 
 */
void Temp_Task(void *p)
{
    TickType_t xLastWakeTime;//刚开始唤醒的时间
    xLastWakeTime = xTaskGetTickCount ();
    
    Temp_PID();
    
    while(1)
    {
        Temp_Control(1.0f);
        vTaskDelayUntil(&xLastWakeTime, 1000);
    }
}

