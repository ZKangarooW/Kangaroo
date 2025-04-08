#include "Key.h"
#include "Led.h"
#include "CheckTouchKey_80F73xx.h"
#include "Buzzer.h"
#include "time.h"
#include "Temp.h"

unsigned char xdata KeyProcessFlag;	//按键处理标记位

KeyValue_t KeyValueScan;

SystemState_t State;
SystemState_t Pre_State; //煮沸前的状态

int SelfTest_Valid = 1; //是否可以进入自检状态


/*****************************************************************************
 ** \brief	 Kscan
 **
 ** \param [in]  none   
 **
 ** \return 0
 *****************************************************************************/
void Kscan(void)
{
	static unsigned long int xdata KeyOldFlag = 0;
	unsigned long int xdata KeyOnOutput = KeyFlag;
	if(KeyOnOutput)
	{
		if(KeyOnOutput != KeyOldFlag)
		{
			KeyOldFlag = KeyOnOutput;			//有检测到按键
			if(0x1 == KeyOnOutput)				//开关
			{
				KeyValueScan = On_Off;
			}
			else if(0x2 == KeyOnOutput)		//功能
			{
				KeyValueScan = Function;
			}
			else if(0x4 == KeyOnOutput)		//煮沸
			{
				KeyValueScan = Boil;
			}
			else if(0x8 == KeyOnOutput)		// +
			{
				KeyValueScan = Add;
			}
			else if(0x10 == KeyOnOutput)	// -
			{
				KeyValueScan = Sub;
			}
		}
	}
	else
	{
		KeyOldFlag = 0;
		KeyValueScan = Free;
		KeyProcessFlag = 1;		//按键弹开后，才需重新处理按键值
	}
}


/**********************************************************
函数名称： KeyProcess(void)
函数功能： 案件流程
输入参数：
输出参数：
***********************************************************/
void KeyProcess(void)
{
	static int count = 0;
	static int PowerOnCount = 0;
	int DisplayNow = 0;
	DisplayNow = GetData1();
	count++;
	
	if(PowerOnCount < 30)
	{
		PowerOnCount++; //开机计时3s，用于自检程序判断
	}
	
	if(PowerOnCount < 5 ){
		//0.5s后再进入按键检测状态
		return;
	}else if(PowerOnCount == 5)
	{ 
		//0.5s后更新显示,进入按键检测状态
		DisplayNum[0] = 11;
  	DisplayNum[1] = 11;
		DisplayNum[2] = 11;
		DisplayNum[3] = 11;
		SetSpecialData1(0);
		SetSpecialData2(0);
		SetLed(6);
	}else if(PowerOnCount == 30)
	{
		//上电3s后无法进入自检状态
		SelfTest_Valid = 0;
	}
	
	if((State == SelfTest) && (Err == 1))
	{
			//自检状态下未检测到ntc数码管显示88 88 
			SetData1(88);
			SetData2(88);
	}
	
	if(Cnt.TimeTo3s > 30) //3s闪烁后设定值有效
	{
		Num1Valid = 1; //设定值修改后需等待3s再生效
	}

	if((Cnt.TimeTo3s < 30) && (Err == 1) && (DisplayNow == 0) && (State != PowerOn) && (State != SelfTest)) //闪烁灭灯时拿下水壶需显示设定值
	{
		if(State == Temp100)
		{
			SetData1(100); //煮沸除氯显示100℃
		}
		else
		{
			SetData1(DisplayNum1); //其余功能显示原有设定值
		}
		
	}
	
	//NTC故障，按键未结束时不进行操作
	if((0 == KeyProcessFlag) || (Err == 1))   
	{
		return;
	}
	KeyProcessFlag = 0;
	
	
	switch(State)
	{
		//上电显示：-- -- led全部关闭
		case PowerOn:
		{
			DisplayNum[0] = 11;
			DisplayNum[1] = 11;
			DisplayNum[2] = 11;
			DisplayNum[3] = 11;
			SetSpecialData1(0);
			SetSpecialData2(0);
			SetLed(6);
			led1sValid = 0;
			
			DisplayNum1 = 0;
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = Temp45;
				Pre_State = Temp45;
				DisplayNum1 = 45;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
				SelfTest_Valid = 0; //开机进入其他功能时，则无法进入自检状态
			}
			
			break;
		}
		case Temp45:			//45℃状态
		{
			SetLed(0);	//第一个led灯亮

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3) //500ms至3000ms内开启闪烁
			{
				if(count> 4) // 500ms更新闪烁
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp55;
				DisplayNum1 = 55;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Pre_State = Temp45;
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				Num1Valid = 0;		//设定值闪烁3s后有效
				SubProcess();
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			
			break;
		}
		case Temp55:			//休眠状态
		{
			
			SetLed(1);	//第2个led灯亮

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp60;
				DisplayNum1 = 60;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 30;
				Pre_State = Temp55;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			
			break;
		}
    case Temp60:			//温度选择状态
		{
			SetLed(2);	//第3个led灯亮

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
				//开启加热
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp85;
				DisplayNum1 = 85;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Pre_State = Temp60;
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			break;
		}
    case Temp85:			//沸腾加热状态
		{
			SetLed(3);	//第4个led灯亮

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
				//开启加热
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp90;
				DisplayNum1 = 90;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Pre_State = Temp85;
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			break;
		}
    case Temp90: 			
		{
			SetLed(4);	//第5个led灯亮

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
				//开启加热
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp100;
				Pre_State = Temp45;
				SetData1(100);
				DisplayNum1 = 45; //煮沸显示为100℃，设定值大小未设定时为45℃,100℃烧开后跳转45℃
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Pre_State = Temp90;
				DisplayNum1 = 90;
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			break;
		}
    case Temp100:
		{
			SetLed(5);	//第6个led灯亮

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(100); //不更改之前状态的设定值，显示为100摄氏度
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(100);
				//开启加热
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp45;
				Pre_State = Temp45;
				DisplayNum1 = 45;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			break;
		}
	
		case SelfTest:
		{			
			//数码管显示12 34
			SetData1(12);
			SetData2(34);
			
			if(KeyValueScan == On_Off)
			{
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				SetData1(55);
				SetData2(55);
			}else if(KeyValueScan == Boil)
			{
				SetData1(66);
				SetData2(66);
			}else if(KeyValueScan == Add)
			{
				SetData1(77);
				SetData2(77);
			}
			break;
		}
		
	}
	
	
}

/**********************************************************
函数名称： AddProcess(void)
函数功能： 设定温度增加流程
输入参数：
输出参数：
***********************************************************/
void AddProcess(void)
{
	if(DisplayNum1 < 95)
	{
		DisplayNum1++;
	}
	Num1Valid = 0;
	Cnt.TimeTo3s = 0;
	SetData1(DisplayNum1);
}

/**********************************************************
函数名称： SubProcess(void)
函数功能： 设定温度减少流程
输入参数：
输出参数：
***********************************************************/
void SubProcess(void)
{
	if(DisplayNum1 > 37)
	{
		DisplayNum1--;
	}
	Num1Valid = 0;
	Cnt.TimeTo3s = 0;
	SetData1(DisplayNum1);
}

/**********************************************************
函数名称： LongPress(void)
函数功能： 长按更改设定温度流程
输入参数：
输出参数：
***********************************************************/
void LongPress(void)
{
	static int count = 0; //1s后更新显示数值
	static int longend_flag = 0; //长按结束标志
	
	if((Err == 0) && (State != PowerOn) && (State != SelfTest))
	{

		if(count== 5) // 500ms的时候灭一次灯
		{
			DisplayNum[0] = 12;
			DisplayNum[1] = 12;
			SetSpecialData1(1);
		}
	
		if( KeyValueScan == Add )
		{
			count++;
			if(count > 10) //1s后更新设定值
			{
				AddProcess();
				longend_flag = 1;
			}
		}else if(KeyValueScan == Sub){
			count++;
			if(count > 10 ) //1s后更新设定值
			{
				SubProcess();
				longend_flag = 1;
			}
		}else{
			count = 0;
			if(longend_flag)
			{
				longend_flag = 0;
				Num1Valid = 0;		//设定值闪烁3s后有效
				Cnt.TimeTo3s = 0;
			}
		}
	}
}

/**********************************************************
函数名称： SelfTestProcess(void)
函数功能： 自检程序
输入参数：
输出参数：
***********************************************************/
void SelfTestProcess(void)
{
	static int selftest_count = 0; //自检状态计数
	//NTC正常 上电未开机 允许进入自检状态
	if((State == PowerOn) && (SelfTest_Valid == 1))
	{
		if(KeyValueScan == Sub)
		{
			selftest_count++;
		}else
		{
			selftest_count = 0;
		}
		
		if(selftest_count > 10)
		{
			State = SelfTest;
			SelfTest_Valid = 0; //若进入自检状态则不能再次进入
			SetLed(7);	//led灯全亮
			
		}
	}
	
}