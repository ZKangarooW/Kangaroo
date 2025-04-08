#include "Drv_Touch.h"

/**********全局变量声明*******/
float Key_Status = 0;//在操作按键的时间

/**********局部变量声明*******/
float Key_Cnt1, Key_Cnt2, Key_Cnt3 = 0;//按下时间
bit Key_Flag1, Key_Flag2, Key_Flag3 = 0;//按键按下标志
bit LongPress1, LongPress2, LongPress3 = 0;//按键长按标志
float UPPress_Time, DownPress_Time = 0;      
uint32_t exKeyValueFlag = 0;//键值TK0对应0x00000001；TK1对应0x00000002；依此类推。

/**
 * @brief 触摸初始化
 *
 */
void Drv_Touch_Init(void)
{
	TouchKeyInit();//调用库函数，初始化TouchKey
}

/**
 * @brief 键值处理
 *
 * @param dT 任务周期
 */
void ChangeTouchKeyvalue(float dT)
{
    /******************************Start键******************************/
	if (exKeyValueFlag == Key1)//按下按键
	{
		if (LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	else if (Key_Flag1)//按键被按下
	{
		if (exKeyValueFlag != Key1)//抬起按键
		{
			if (Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5f)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.Run_Status)
				{
					sys.Run_Status = 0;
				}
				else
				{
					sys.Run_Status = 1;
					Speed_Val.Integral = 100;
				}
				Beep_Time = 0.1f;//蜂鸣器响0.1S
				
			}
		}
		Key_Flag1 = 0;//按键事件结束，等待下一次按下
		LongPress1 = 0;//长按标志位清零
		Key_Cnt1 = 0;//按钮计数清零
	}
	if (Key_Cnt1 > 1.5f && Key_Cnt1 < 3.0f)//按键时间大于1.5S小于3S表示长按
	{
		if (LongPress1 == 0)//如果没有一直长按着
		{
			
			LongPress1 = 1;//长按标志置一
		}
	}
	
	/******************************加键******************************/
    if(exKeyValueFlag == Key2)//按下按键
    {
        UPPress_Time += dT;//长按时间加加
        Key_Cnt2 += dT;//按下时间++
        Key_Flag2 = 1;//按键按下标志置一
    }
    if(Key_Flag2)//按键被按下
    {
        if(exKeyValueFlag != Key2)//抬起按键
        {
            if(Key_Cnt2 < 1.5f)//按键时间小于1.5S是单击
            {

//                Beep_Time = 0.1f;//蜂鸣器响0.1S
            }
            Key_Flag2 = 0;//按键事件结束，等待下一次按下
            Key_Cnt2 = 0;//按钮计数清零
        }
        else if (Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f)//按键时间大于1.9S小于2.1S表示长按
        {
			if (UPPress_Time > 5.0f)
			{
				//+10
			}
			else
			{
				//++ 
			}
            if (UPPress_Time > 5.0f)
            {
                Key_Cnt2 = 1.82f;//长按按键时间复位
            }
            else
            {
                Key_Cnt2 = 1.88f;
            }
            Key_Flag2 = 0;//按键事件结束，等待下一次按下
        }
    }
    else
    {
        UPPress_Time = 0;
        Key_Cnt2 = 0; // 按键计数清零
    }
	
	/******************************减键******************************/
    if(exKeyValueFlag == Key3)//按下按键
    {
        DownPress_Time += dT;//长按时间加加
        Key_Cnt3 += dT;//按下时间++
        Key_Flag3 = 1;//按键按下标志置一
    }
    if(Key_Flag3)//按键被按下
    {
        if(exKeyValueFlag != Key3)//抬起按键
        {
            if(Key_Cnt3 < 1.5f)//按键时间小于1.5S是单击
            {

//                Beep_Time = 0.1f;//蜂鸣器响0.1S
            }
            Key_Flag3 = 0;//按键事件结束，等待下一次按下
            Key_Cnt3 = 0;//按钮计数清零
        }
        else if (Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f)//按键时间大于1.9S小于2.1S表示长按
        {
			if (DownPress_Time > 5.0f)
			{
				//+10
			}
			else
			{
				//++ 
			}
            if (DownPress_Time > 5.0f)
            {
                Key_Cnt3 = 1.82f;//长按按键时间复位
            }
            else
            {
                Key_Cnt3 = 1.88f;
            }
            Key_Flag3 = 0;//按键事件结束，等待下一次按下
        }
    }
    else
    {
        DownPress_Time = 0;
        Key_Cnt3 = 0; // 按键计数清零
    }
}

/**
 * @brief 触摸扫描
 *
 * @param dT 任务周期
 */
void Touch_Scan(float dT)
{
	if(SOCAPI_TouchKeyStatus&0x80)//重要步骤2:  触摸键扫描一轮标志，是否调用TouchKeyScan()一定要根据此标志位置起后
	{	   																	
		SOCAPI_TouchKeyStatus &=0x7f;//重要步骤3: 清除标志位， 需要外部清除。													    
		exKeyValueFlag = TouchKeyScan();//扫描得到键值
		ChangeTouchKeyvalue(dT);//键值处理
		TouchKeyRestart();//启动下一轮转换 																 			
	}			
}

/**
 * @brief 检测按键状态
 *
 * @param dT 任务周期
 */
void Check_Press(float dT)
{
    if (Key_Status)
        Key_Status -= dT;
}

 