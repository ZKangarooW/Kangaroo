#include "Ctrl_ControlTemp.h"

/**********全局变量声明******/
int Temp_Out;//温度pwm输出值
uint16_t adc_val;

/*
*****************************************************************
 * 函数原型： void PID_Init(void)
 * 功    能： pid系数初始化
*****************************************************************
*/
void PID_Init(void)
{
	Temp_Arg.Kp=10;
	Temp_Arg.Ki=0.2;
	Temp_Arg.Kd=0;
}

/*
*****************************************************************
 * 函数原型：void CoolTemp_Mode(float dT,int pwm)
 * 功    能：加热制冷切换
*****************************************************************
*/
void CoolTemp_Mode(float dT,int pwm)
{
	static float T;
	static uint8_t Mode,mode;//临时存储当前模式
	
	if(pwm >= 40)
	{
		mode = 0;//加热
	}
	else if(pwm < -50)
	{
		mode = 1;//制冷
        HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_SET);//打开风扇
	}
		
	if(Mode != mode)//如果模式变换了
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
			Mode = mode;
		}
	}
	else//没有改变模式的情况下
	{
		if(mode == 0)
		{
			COLD = 0;
			HEAT = pwm;
		}			
		else if(mode == 1)
		{
			COLD = (-pwm);
			HEAT = 0;
		}
	}
}
uint8_t Out_Enable;

/*
*****************************************************************
 * 函数原型： void Temp_Control(float dT)
 * 功    能： 温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
    if(sys.Run_Status == 1)//启动
    { 
		adc_val = Get_ADCVal(Ctrl_Temp);
		if(sys.CtrlTemp_Mode == 1)
		{
			HEAT_ICO = 1;//加热图标
		}
		else if(sys.CtrlTemp_Mode == 2)
		{
			HEAT_ICO = 2;//制冷图标
			HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_SET);//打开风扇
		}
		if((adc_val - ADC_Val > -100 && adc_val - ADC_Val < 100))
			Out_Enable = 1;
		else
			Out_Enable = 0;
		AltPID_Calculation(dT, adc_val, ADC_Val, &Temp_Arg, &Temp_Val, 100, Out_Enable * 1000);
		CoolTemp_Mode(dT,(int)Temp_Val.Out);
    }
    else 
    {
		sys.CtrlTemp_Mode = 0;
		Out_Enable = 0;
        Temp_Out = 0;//PWM输出为零
		HEAT_ICO = 0;//图标不显示
		HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_RESET);//关闭风扇
        HEAT = 0;//加热不工作
		COLD=0;
        Temp_ADDMode = 0;//显示模式为零
    }
}

