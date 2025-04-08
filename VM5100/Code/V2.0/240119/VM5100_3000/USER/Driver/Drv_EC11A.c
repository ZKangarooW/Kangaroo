#include "Drv_EC11A.h"

/**********全局变量声明******/
uint8_t Work_Option;//选择工位号
uint8_t SetMode_Option;//选择设置模式
uint8_t EC11A_Knob1,EC11A_Knob2;//在旋动旋钮时
uint8_t Run_Status;//系统状态
uint8_t Work_All;//工位设置相同

/**********局部变量声明******/
uint8_t EC11A_Flag;//进入中断延时标志
uint8_t Key1_Press,Key2_Press;//按下按钮
uint16_t KEY1_Count,KEY2_Count;//记录KEY1,KEY2按下的时间

/*
*****************************************************************
 * 函数原型：void EC11A_FlagCheak(uint16_t dT)
 * 功    能：检测延时检测延时-2ms
 * 输    入: dT ：周期
 * 参    数：uint16_t dT
*****************************************************************
*/
void EC11A_FlagCheak(uint16_t dT)
{
    static uint16_t T;
    T += dT;//周期加加
    if(T % 4 == 0)//计时4ms
    {
        EC11A_Flag = 1;//进入中断
		T = 0;//计时清零
    }
}

/*
*****************************************************************
 * 函数原型：void Check_Knob(void)
 * 功    能：检测旋钮状态-500ms
*****************************************************************
*/
void Check_Knob(void)
{
    if(EC11A_Knob1)//旋钮被转动
	{
        EC11A_Knob1--;//1S倒计时
		if(EC11A_Knob1 == 0)//旋钮被转动
		{
			Twinkle_Time1 = 2000;//闪烁时间
		}
	}
	if(EC11A_Knob2)//旋钮被转动
	{
        EC11A_Knob2--;//1S倒计时
		if(EC11A_Knob2 == 0)//旋钮被转动
		{
			Twinkle_Time2 = 2000;//闪烁时间
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
    if(EC11A_Flag == 1)//进入中断
    {
        /***********右旋钮***********/
        if(GPIO_Pin == KEY2B_Pin)//右边旋钮触发
        {
            if((HAL_GPIO_ReadPin(KEY2A_GPIO_Port,KEY2A_Pin)==0)&&(HAL_GPIO_ReadPin(KEY2B_GPIO_Port,KEY2B_Pin)==0))//如果向左旋转
            {
                Set_Speed+=10;
				Set_Speed = (Set_Speed > 3000) ? 3000 : Set_Speed;//速度不超过3000转
            }
            else if((HAL_GPIO_ReadPin(KEY2A_GPIO_Port,KEY2A_Pin)==1)&&(HAL_GPIO_ReadPin(KEY2B_GPIO_Port,KEY2B_Pin)==0))//如果向右旋转
            {
                Set_Speed-=10;
				Set_Speed = (Set_Speed < 1500) ? 1500 : Set_Speed;//速度设置小于1500转时清零
            }
			EC11A_Knob1 = 1;
        }

        /***********左旋转**********/
		if(GPIO_Pin == KEY1B_Pin)//左边旋钮触发
		{
			if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==0)&&(HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0))//如果向左旋转
			{
				Set_Time += 60;
				Set_Time = (Set_Time > 28800) ? 28800 : Set_Time;//时间最多设定8小时
			}
			else if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==1)&&(HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0))//如果向右旋转
			{
				Set_Time -= 60;
				Set_Time = (Set_Time < 60) ? 0 : Set_Time;//时间小于1分钟不设定
			}
			Time_State  = (Set_Time < 60) ? 0 : 1;//判断是否设置了时间
			EC11A_Knob2 = 1;
		}
        EC11A_Flag = 0;//关闭中断 
    }

    /**********左边按钮中断**********/
    if(GPIO_Pin ==KEY1_Pin)
    {
        Key1_Press = 1;//按下标志被置一
    }

    /**********右边按钮中断**********/
    if(GPIO_Pin ==KEY2_Pin)
    {
        Key2_Press = 1;//按下标志被置一
    }
}

/*
*****************************************************************
 * 函数原型：void Check_KeyState(void)
 * 功    能：按键检测
*****************************************************************
*/
void Check_KeyState(void)
{
    /**********KEY1**********/
    if(Key1_Press == 1)//按钮被按下
    {
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)//如果KEY1按下
            KEY1_Count++;//按下时间++
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==1)//如果KEY1抬起
        {
            if(KEY1_Count < 200)//短按
            {
                if(sys.Run_Status == 0)
				{
					Speed_ADDMode = 0;
					sys.Run_Status = 1;
					SpeedSet_Flag = 1;
					TimeSet_Flag = 1;
					Twinkle_Time1 =0;
					EC11A_Knob1=0;
					Twinkle_Time2 =0; 
					EC11A_Knob2=0;
				}
				else
				{
					sys.Run_Status = 0;//检测电机
					Speed_ADDMode = 2;//进入减速模式下
				}
            }
            else//等于200时再清零
            {
                KEY1_Count = 0;//按钮计数清零
                Key1_Press = 0;//按钮状态为抬起
            }
			KEY1_Count = 0;//按钮计数清零
            Key1_Press = 0;//按钮状态为抬起			
        }
        if(KEY1_Count > 200 && KEY1_Count < 400)//长按
        {
            
            KEY1_Count = 400;//按钮计数等于200，这样就不会在抬起再进入单击了
        }
    }
    /**********KEY2**********/
    if(Key2_Press == 1)//按钮被按下
    {
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==0)//如果KEY2按下
            KEY2_Count++;//按下时间++
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==1)//如果KEY2抬起
        {
            if(KEY2_Count < 200)//短按
            {
				if(sys.Run_Status == 0)
				{
					Speed_ADDMode = 0;
					sys.Run_Status = 1;
					SpeedSet_Flag = 1;
					TimeSet_Flag = 1;
					Twinkle_Time1 =0;
					EC11A_Knob1=0;
					Twinkle_Time2 =0; 
					EC11A_Knob2=0;
				}
				else
				{
					sys.Run_Status = 0;//检测电机
					Speed_ADDMode = 2;//进入减速模式下
				}
				KEY2_Count = 0;//按钮计数清零
                Key2_Press = 0;//按钮状态为抬起
            }
            else//等于200时再清零
            {
                KEY2_Count = 0;//按钮计数清零
                Key2_Press = 0;//按钮状态为抬起
            }
        }
        if(KEY2_Count > 200 && KEY2_Count < 400)//长按
        {
			
			KEY2_Count = 400;//按钮计数等于200，这样就不会在抬起再进入单击了
        }
    }
}
