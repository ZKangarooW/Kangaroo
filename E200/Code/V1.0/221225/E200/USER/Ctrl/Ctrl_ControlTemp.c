#include "Ctrl_ControlTemp.h"

/**********全局变量声明******/
int Temp_Out,UC_Temp_Out;//加热制冷的pwm和但加热的pwm
int8_t val;

/*
*****************************************************************
 * 函数原型：void Temp_Iint(void)
 * 功    能：温度初始化
*****************************************************************
*/
void Temp_Iint(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);//开启tim1通道2的PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道2的PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道2的PWM
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
	
	if(pwm >= 0)
	{
		if(pwm > 120)
			WIND_OFF;
		mode = 0;//加热
	}
	else if(pwm < 0)
	{
		if(pwm < -600)
			WIND_ON;
		mode = 1;//制冷
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
			val = 1;
			HEAT = pwm;
		}			
		else if(mode == 1)
		{
			val = -1;
			if(Cool_Temp.Ctrl_Temp <= 220)
				COLD = (-pwm)+450;
			else if(Cool_Temp.Ctrl_Temp <= 240)
				COLD = (-pwm)+400;
			else if(Cool_Temp.Ctrl_Temp <= 250)
				COLD = (-pwm)+365;
			else if(Cool_Temp.Ctrl_Temp <= 280)
				COLD = (-pwm)+300;
			else if(Cool_Temp.Ctrl_Temp <= 300)
				COLD = (-pwm)+200;
			else if(Cool_Temp.Ctrl_Temp <= 310)
				COLD = (-pwm)+180;
			else if(Cool_Temp.Ctrl_Temp <= 320)
				COLD = (-pwm)+170;
			else if(Cool_Temp.Ctrl_Temp <= 330)
				COLD = (-pwm)+160;
			else
				COLD = (-pwm)+20;
		}
	}
}

/*
*****************************************************************
 * 函数原型：void Temp_Control(float dT)
 * 功    能：温度加热控制
*****************************************************************
*/
void Temp_Control(float dT)
{ 
	if((sys.SetMode_Option == 0 || sys.SetMode_Option == 3) && sys.Calibration == 0)
	{
		PID_Temp(Get_ADCVal(Heat_Temp.Ctrl_Temp)/Calibration_Temp,ADC_Val1,&HeatTemp_Arg,&HeatTemp_Val);//PID计算
		UC_Temp_Out = (int)HeatTemp_Val.Out;//PID值赋值
		PID_Temp(Get_ADCVal(Cool_Temp.Ctrl_Temp)*Calibration_Temp,ADC_Val2,&CoolTemp_Arg,&CoolTemp_Val);//PID计算
		Temp_Out = (int)CoolTemp_Val.Out;//PID值赋值
	}
	else if(sys.Calibration == 1)
	{
		WIND_OFF;//关闭风扇
		Temp_Out = 0;
		if(sys.Calibration_Step == 0)
		{
			PID_Temp(Get_ADCVal(400),ADC_Val1,&HeatTemp_Arg,&HeatTemp_Val);//PID计算
			UC_Temp_Out = (int)HeatTemp_Val.Out;//PID值赋值
		}
		else
		{
			PID_Temp(Get_ADCVal(600),ADC_Val1,&HeatTemp_Arg,&HeatTemp_Val);//PID计算
			UC_Temp_Out = (int)HeatTemp_Val.Out;//PID值赋值
		}
	}
	else
	{
		WIND_OFF;//关闭风扇
		UC_Temp_Out = 0;
		Temp_Out = 0;
	}
	
	CoolTemp_Mode(dT, Temp_Out);
	if(UC_Temp_Out < 0)
		UC_Temp_Out = 0;
	UC_HEAT = UC_Temp_Out;
}
