#include "Drv_EC11A.h"

/**********结构体************/
_EC11A_ EC11A[2];//旋钮参数

/**
 * @brief EC11A初始化定时器
 * 
 */
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = EC1A_Pin;//EC11A旋钮中断引脚
	EC11A[0].EC11A_Pin = EC1B_Pin;//EC11A旋钮输入引脚
	EC11A[0].EC11A_GPIO = EC1B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A按键输入引脚
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A按键输入GPIO端口
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = EC2A_Pin;//EC11A旋钮中断引脚
	EC11A[1].EC11A_Pin = EC2B_Pin;//EC11A旋钮输入引脚
	EC11A[1].EC11A_GPIO = EC2B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A按键输入引脚
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A按键输入GPIO端口
}

/**
 * @brief EC11A旋钮速度计算
 * 
 * @param dT 任务周期
 */
void EC11A_Speed(float dT)
{
	static float T;
	T+=dT;
	if(T>= 1.0f)
	{
		/**********EC11A_1**********/
		EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt;//一秒检测一次。转一圈20个反馈，一分钟的速度
		EC11A[0].EC11A_Cnt = 0;//将检测到的计数清零
	
		/**********EC11A_2**********/
		EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt;//一秒检测一次。转一圈20个反馈，一分钟的速度
		EC11A[1].EC11A_Cnt = 0;//将检测到的计数清零
        T = 0;
	}
}

/**
 * @brief 检测按键按下状态
 * 
 * @param dT 任务周期
 */
void Check_Press(float dT)
{
    if(EC11A[0].EC11A_Knob>0)//旋钮0旋转
        EC11A[0].EC11A_Knob -= dT;//倒计时
	
	if(EC11A[1].EC11A_Knob>0)//旋钮1旋转
        EC11A[1].EC11A_Knob -= dT;//倒计时
}

/**
 * @brief EC11A按键扫描
 * 
 * @param dT 任务周期
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
                sys.New_Work++;
                if(sys.New_Work > 3)
                    sys.New_Work = 0;
                sys.SetMode_Option = 0;
                Twinkle_Time = 0;
                WorkLine_Flag = 0;
                WorkTwinkle_Time = 0;//工位线闪烁时间清零，为了看起来舒服
                EC11A[0].EC11A_Knob = 2.0f;//在切换时用来看起来会更明显目前在什么工位
				Beep_Time = 0.1f;
			}
			EC11A[0].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[0].LongPress = 0;//长按标志清零
			EC11A[0].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[0].Key_Cnt > 1.5 && EC11A[0].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[0].LongPress == 0)//如果没有一直一直长按着
			{
                for(uint8_t i = 0;i<4;i++)
                {
                    Work_Num[i].Speed.Set= Param.Speed[i]= Work_Num[i].Speed.Ctrl= Work_Num[sys.New_Work].Speed.Set;
                    Work_Num[i].Temp.Set = Param.Temp[i] = Work_Num[i].Temp.Ctrl = Work_Num[sys.New_Work].Temp.Set;
                    Work_Num[i].Time.Set = Param.Time[i] = Work_Num[i].Time.Ctrl = Work_Num[sys.New_Work].Time.Set;
                    Work_Num[i].Time.Rel = Work_Num[sys.New_Work].Time.Rel;
                    
                    if(Work_Num[sys.New_Work].Run_Status)
                    {
                        Work_Num[i].Run_Status = 1;
                    }
                }
                Save_Param_En = 1;//保存
				Beep_Time = 0.1f;
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
                sys.SetMode_Option ++;
                if(sys.SetMode_Option == 1 && Twinkle_Time > 0)//如果先旋转了旋钮，按下后直接跳过速度设置
                        sys.SetMode_Option = 2;
                if(sys.SetMode_Option > 3)
                    sys.SetMode_Option  = 0;
				Beep_Time = 0.1f;
                Twinkle_Time = 2.0f;
			}
			EC11A[1].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[1].LongPress = 0;//长按标志清零
			EC11A[1].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[1].LongPress == 0)//如果没有一直一直长按着
			{
                if(Work_Num[0].Run_Status != 1 && Work_Num[1].Run_Status != 1 && 
                    Work_Num[2].Run_Status != 1 && Work_Num[3].Run_Status != 1)//系统没启动的话
                {
                    for(uint8_t i = 0;i<4;i++)
                    {
                        Work_Num[i].Run_Status = 1;//启动系统
                    }
                }
                else//系统启动的话
                {
                    for(uint8_t i = 0;i<4;i++)
                    {
                        Work_Num[i].Speed.ADDMode = 2;
                        Work_Num[i].Motor_Stop = 1;//电机停止
                    }
                }
                Beep_Time = 0.1f;
                EC11A[1].LongPress = 1;//长按标志置一
            }
		}
	}
}

/*
*****************************************************************
 * 函数原型： void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option,uint8_t EC11A_Fast)
 * 功    能： 设置数值
 * 输    入:  flag ：0是加 1是减  Work_Option：工位 SetMode_Option：设置模式 EC11A_Fast 旋钮速度
 * 参    数： uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option
*****************************************************************
*/
void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option,uint8_t EC11A_Fast)
{
    if(flag == 0)//加
    {
        if(EC11A_Fast < EC11A_FastSpeed)//如果慢慢旋转
        {
            switch(SetMode_Option)//模式
            {
                case 0:
                case 1:Work_Num[Work_Option].Speed.Set += 10;
                       if(Work_Num[Work_Option].Speed.Set == 10)//从零转开始最低为100转，判断是30后
                            Work_Num[Work_Option].Speed.Set = 100;//设定转速为100开始
                       if(Work_Num[Work_Option].Speed.Set > Speed_MAX)
							Work_Num[Work_Option].Speed.Set = Speed_MAX;
                       break;
                       
                case 2:if(Work_Num[Work_Option].Temp.Set < 1000)
                            Work_Num[Work_Option].Temp.Set += 5;
                        else
                            Work_Num[Work_Option].Temp.Set += 10;
                        if(Work_Num[Work_Option].Temp.Set > Temp_MAX)
							Work_Num[Work_Option].Temp.Set = Temp_MAX;
                       break;
                
                case 3:Work_Num[Work_Option].Time.Set += 60;
                        if(Work_Num[Work_Option].Time.Set > Time_MAX)
							Work_Num[Work_Option].Time.Set = Time_MAX;
                       break;
            }
        }
        else//快速转
        {
            switch(SetMode_Option)//模式
            {
                case 0:
                case 1:Work_Num[Work_Option].Speed.Set += 30;
                       if(Work_Num[Work_Option].Speed.Set == 30)//从零转开始最低为100转，判断是30后
                            Work_Num[Work_Option].Speed.Set = 100;//设定转速为100开始
                       if(Work_Num[Work_Option].Speed.Set > Speed_MAX)
							Work_Num[Work_Option].Speed.Set = Speed_MAX;
                       break;
                       
                case 2:Work_Num[Work_Option].Temp.Set += 20;
                       if(Work_Num[Work_Option].Temp.Set > Temp_MAX)
							Work_Num[Work_Option].Temp.Set = Temp_MAX;
                       break;
                
                case 3:Work_Num[Work_Option].Time.Set += 300;
                       if(Work_Num[Work_Option].Time.Set > Time_MAX)
							Work_Num[Work_Option].Time.Set = Time_MAX;
                       break;
            }
        }
    }
    else//减
    {
        if(EC11A_Fast < EC11A_FastSpeed)//如果慢慢旋转
        {
            switch(SetMode_Option)//模式
            {
                case 0:
                case 1:Work_Num[Work_Option].Speed.Set -= 10;
                       if(Work_Num[Work_Option].Speed.Set < Speed_MIN)
							Work_Num[Work_Option].Speed.Set = 0;
                       break;
                       
                case 2:if(Work_Num[Work_Option].Temp.Set < 1000)
                                Work_Num[Work_Option].Temp.Set -= 5;
                            else
                                Work_Num[Work_Option].Temp.Set -= 10;
                        if(Work_Num[Work_Option].Temp.Set <= Temp_MIN)
							Work_Num[Work_Option].Temp.Set = Temp_MIN;
                       break;
                
                case 3:Work_Num[Work_Option].Time.Set -= 60;
                        if(Work_Num[Work_Option].Time.Set <= Time_MIN)
							Work_Num[Work_Option].Time.Set = Time_MIN;
                       break;
            }
        }
        else//快速转
        {
            switch(SetMode_Option)//模式
            {
                case 0:
                case 1:Work_Num[Work_Option].Speed.Set -= 30;
                       if(Work_Num[Work_Option].Speed.Set < Speed_MIN)
							Work_Num[Work_Option].Speed.Set = 0;
                       break;
                       
                case 2:Work_Num[Work_Option].Temp.Set -= 20;
                       if(Work_Num[Work_Option].Temp.Set <= Temp_MIN)
							Work_Num[Work_Option].Temp.Set = Temp_MIN;
                       break;
                
                case 3:Work_Num[Work_Option].Time.Set -= 300;
                       if(Work_Num[Work_Option].Time.Set <= Time_MIN)
							Work_Num[Work_Option].Time.Set = Time_MIN;
                       break;
            }
        }
    }
    Twinkle_Time = 2.0f;
}

/**
 * @brief 外部中断
 * 
 * @param GPIO_Pin 触发引脚
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A上升沿触发外部中断
	{	
		EC11A[0].EC11A_Cnt++;//旋钮计数
		EC11A[0].EC11A_Knob = 2.0f;//在旋转旋钮时
		if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//加
		{
			sys.New_Work++;
            if(sys.New_Work > 3)
                sys.New_Work = 0;
		}
		else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//减
		{
            if(sys.New_Work == 0)
                sys.New_Work = 4;
			sys.New_Work--;
		}
        WorkLine_Flag = 0xff;
        WorkTwinkle_Time = 0;
        sys.SetMode_Option = 0;
        Twinkle_Time = 0;
        Beep_Time = 0.1f;
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//在2ms内，检测到电平变化
	{ 
		EC11A[1].EC11A_Cnt++;//旋钮计数
		EC11A[1].EC11A_Knob = 1.0f;//在旋转旋钮时
		if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//加
		{
			Set_Val(0,sys.New_Work,sys.SetMode_Option,EC11A[1].EC11A_Speed);
		}
		else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//减
		{
			Set_Val(1,sys.New_Work,sys.SetMode_Option,EC11A[1].EC11A_Speed);
		}
	}
}

/**
 * @brief 旋钮任务
 * 
 */
void EC11A_Task(void *p)
{
    TickType_t xLastWakeTime;//刚开始唤醒的时间
    xLastWakeTime = xTaskGetTickCount ();

    while(1)
    {
		EC11AKey_Scan(0.01f);
		EC11A_Speed(0.01f);
		Check_Press(0.01f);
		vTaskDelayUntil(&xLastWakeTime, 10);
    }
}

