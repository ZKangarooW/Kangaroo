#include "Drv_EC11A.h"

/**********结构体************/
_EC11A_ EC11A[2];//旋钮参数

/*
*****************************************************************
 * 函数原型：void EC11A_Init(void)
 * 功    能：EC11A初始化定时器
*****************************************************************
*/
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = EC1A_Pin;//EC11A旋钮中断引脚
	EC11A[0].EC11A_Pin = EC1B_Pin;//EC11A旋钮输入引脚
	EC11A[0].EC11A_GPIO = EC1B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A按键输入引脚
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A按键输入GPIO端口
	
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//判断旋转速度阈值
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = EC2A_Pin;//EC11A旋钮中断引脚
	EC11A[1].EC11A_Pin = EC2B_Pin;//EC11A旋钮输入引脚
	EC11A[1].EC11A_GPIO = EC2B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A按键输入引脚
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A按键输入GPIO端口
	
	EC11A[1].EC11A_Fast = EC11A_FastSpeed;//判断旋转速度阈值
}

/*
*****************************************************************
 * 函数原型：void EC11A_Speed(float dT)
 * 功    能：EC11A旋钮速度计算
*****************************************************************
*/
void EC11A_Speed(float dT)
{
	/**********EC11A_1**********/
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//一秒检测一次。转一圈20个反馈，一分钟的速度
	EC11A[0].EC11A_Cnt = 0;//将检测到的计数清零
	
	/**********EC11A_2**********/
	EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt*60/20;//一秒检测一次。转一圈20个反馈，一分钟的速度
	EC11A[1].EC11A_Cnt = 0;//将检测到的计数清零
}

/*
*****************************************************************
 * 函数原型：void Check_Press(float dT)
 * 功    能：检测按键按下状态-500ms
*****************************************************************
*/
void Check_Press(float dT)
{
    if(EC11A[0].EC11A_Knob)//旋钮0旋转
        EC11A[0].EC11A_Knob -= dT;//倒计时
	
	if(EC11A[1].EC11A_Knob)//旋钮1旋转
        EC11A[1].EC11A_Knob -= dT;//倒计时
}

/*
*****************************************************************
 * 函数原型：void EC11AKey_Scan(float dT)
 * 功    能：EC11A按键扫描
*****************************************************************
*/
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********/
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)//按下按键
	{
		if(EC11A[0].LongPress == 0)//没有长按过
		{
			EC11A[0].Key_Cnt += dT;//按下时间++
			EC11A[0].Key_Flag = 1;//按键按下标志置一
		}
	}
	if(EC11A[0].Key_Flag == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_UP)//抬起按键
		{   
			if(EC11A[0].Key_Cnt > 0.1 && EC11A[0].Key_Cnt < 1.5)//小于1.5S是单击
			{
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			EC11A[0].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[0].LongPress = 0;//长按标志清零
			EC11A[0].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[0].Key_Cnt > 1.5 && EC11A[0].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[0].LongPress == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//“滴滴”两下用于误触
				EC11A[0].LongPress = 1;//长按标志置一
			}
		}
	}
	
	/**********EC11A_2**********/
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//按下按键
	{
		if(EC11A[1].LongPress == 0)//没有长按过
		{
			EC11A[1].Key_Cnt += dT;//按下时间++
			EC11A[1].Key_Flag = 1;//按键按下标志置一
		}
	}
	if(EC11A[1].Key_Flag == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_UP)//抬起按键
		{   
			if(EC11A[1].Key_Cnt > 0.1 && EC11A[1].Key_Cnt < 1.5)//小于1.5S是单击
			{
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			EC11A[1].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[1].LongPress = 0;//长按标志清零
			EC11A[1].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[1].LongPress == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//“滴滴”两下用于误触
				EC11A[1].LongPress = 1;//长按标志置一
			}
		}
	}
}

/*
*****************************************************************
 * 函数原型：void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * 功    能：外部中断
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A上升沿触发外部中断
	{
        if(GPIO_Pin == EC11A[0].EXTI_Pin)//在2ms内，检测到电平变化
        { 
            EC11A[0].EC11A_Cnt++;//旋钮计数
            EC11A[0].EC11A_Knob = 2.0f;//在旋转旋钮时
            if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//加
            {
                Speed.Set += 50;
            }
            else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//减
            {
                Speed.Set -= 50;
                if(Speed.Set<0)
                    Speed.Set = 0;
            }
        }
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//A上升沿触发外部中断
	{
        if(GPIO_Pin == EC11A[1].EXTI_Pin)//在2ms内，检测到电平变化
        { 
            EC11A[1].EC11A_Cnt++;//旋钮计数
            EC11A[1].EC11A_Knob = 2;//在旋转旋钮时
            if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//加
            {
                Temp.Set += 50;
            }
            else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//减
            {
                Temp.Set -= 50;
                if(Temp.Set<0)
                    Temp.Set = 0;
            }
        }
    }
}
