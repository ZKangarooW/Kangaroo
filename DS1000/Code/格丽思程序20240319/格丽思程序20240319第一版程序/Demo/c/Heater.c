
#include "Heater.h"
#include "Gpio.h"
#include "Key.h"
#include "Temp.h"
#include "led.h"
#include "Buzzer.h"

#include <CMS\FY80F49x.H>
Heater_t Heater;


void Heater_Config(void)
{
	
//		/*可控硅加热*/
//		GPIO_SET_MUX_MODE(P15CFG, GPIO_MUX_GPIO);
		GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_5);
//		P15 = 0;
	
		/*过零检测*/
		GPIO_SET_MUX_MODE(P20CFG, GPIO_MUX_GPIO);
		GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_0);
}


void CtrlHeater_SCR(void)
{
	signed int Delta;
	int display1 = 0;	//当前显示设定温度
	display1 = GetData1();
	
	if(1 == Heater.UseSCR)
	{
	
		Delta = display1 - DisplayNum2; //设定温度减去当前温度 

		Heater.SCRCnt =(Heater.SCRCnt < U8_MAX)?Heater.SCRCnt+1:0;	
		Heater.SCRFullTimeSet = 100;
		if(Heater.SCRCnt == Heater.SCRFullTimeSet)
		{
			Heater.SCRCnt = 0;
			
			if(Delta > 5)
			{
				Heater.SCROnTimeSet = 100;
			}
			else if(Delta >= 0)
			{
				Heater.SCROnTimeSet = 70;
			}
			else
			{
				Heater.SCROnTimeSet = 0;
			}
		}
		
	#
		if(Heater.SCRCnt < Heater.SCROnTimeSet)
		{
			Heater.SCROn = 1;
		}
		else
		{
			Heater.SCROn = 0;
		}
	}else{
		if(State == SelfTest) 
		{
			//自检状态则开启可控硅畅开
			Heater.SCROn = 1;
		}else
		{
			//不加热则关闭加热管脚
			Heater.SCROn = 0;
		}
	}
	
	/*SCR动作*/
	if(1 == Heater.SCROn)
	{
			Heater_SCR_IO = On ;
	}
}


/*************************************************************************************************
函数名称：CtrlHeater()
函数功能：控制加热是否开启
输入参数
输出参数
**************************************************************************************************/
void CtrlHeater(void)
{
	static int equState = 0;
	static unsigned int count = 0; //最大值65535
	static int s15 = 0;			//沸水时长
	int display2 = 0; //当前显示温度
	int display1 = 0;	//当前显示设定温度
	//NTC故障、初始上电状态下不进行加热,自检状态下不进行温度检测的加热开关控制
	if((Err == 1) || (State == PowerOn) || (State == SelfTest) )
	{
		Heater.UseSCR = 0;
		return;
	}
	
	display1 = GetData1();
	if((DisplayNum2 < display1) && (Num1Valid == 1))//如果现在温度小于设定温度，且设定值有效，则进行加热
	{
		if(DisplayNum2 <= (DisplayNum1-3)) //实际温度与设定值温度相差3度时，下次温度达到设定值后再响蜂鸣器
  	{
			equState = 0; //温度相等状态，温度相差3摄氏度以上时进行蜂鸣器提示
			count = 0; //煮沸除氯时拿起水壶降温相差3℃以上，煮沸除氯重新计时
		}
		
		if((equState == 1) && (display1 == 100))
		{
			count++; //若进入除氯状态，计数累加
			if(count > 15000) //该程序1ms进一次 15s
			{
				s15++;
				count = 0;
			}
		}
		
		Heater.UseSCR = 1;
	}else{	//否则不加热
		display2 = GetData2();
		if((equState == 0 ) && (DisplayNum2 == display1))
		{
			if( display2 == display1 )
			{
				if((State != Temp100) && (Num1Valid == 1))
				{
					BeepSet(200, 2);
				}
				
				equState = 1; //达到设定温度后，在设定温度不变时不进行蜂鸣器提示
			}
		}
		
		if((State == Temp100) && (display2 == display1) && (Num1Valid == 1)) //若为沸水状态，应持续1分钟后再关闭加热
		{
			count++;
			if(count > 15000) //该程序1ms进一次 15s
			{
				s15++;
				count = 0;
			}
			
			if(s15 < 5 ) //15s*5 = 1min15s
			{
				Heater.UseSCR = 1; 
				return;
			}
			BeepSet(80, 1);
			State = Pre_State;

			SetData1(DisplayNum1);
			equState = 0;	//状态变更时应将温度相等状态至零
			s15 = 0;
		}
		
		Heater.UseSCR = 0;
	}
	
	
	
	
}
