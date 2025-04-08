#include "Drv_EC11A.h"

/**********全局变量声明******/
uint8_t EC11A_Knob;//在旋动旋钮时

/**********局部变量声明******/
uint8_t EC11A_Flag;//进入中断延时标志
uint8_t Key1_Press;//按下按钮
uint16_t KEY1_Count;//记录KEY1按下的时间

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
	if(sys.Run_Status == 0)
	{
		if(EC11A_Knob)//旋钮被转动
			EC11A_Knob--;//1S倒计时
	}
	else
	{
		if(EC11A_Knob > 0)
		{
			EC11A_Knob--;//1S倒计时
			if(EC11A_Knob <= 0)
			{
				Ctrl_Speed = Set_Speed;
				Speed_ADDMode = 0;		
				Beep_Time = 0.1;//蜂鸣器响0.1S
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
    if(EC11A_Flag == 1)//进入中断
    {
        /***********左旋转**********/
        if(GPIO_Pin == KEY1B_Pin)//左边旋钮触发
        {
            if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==1)&&(HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0))//如果向左旋转
            {
				if(sys.Run_Status == 1 && sys.Motor_Stop == 0)
				{
					Speed = Rel_Speed/Tooth_Ratio; 
					Set_Speed -= 10;
                    if(Set_Speed <= MIN_Speed)
                        Set_Speed = MIN_Speed;
					EC11A_Knob = 2;//检测是不是在旋动旋钮
				}
                if(sys.SetMode_Option == 1)
                {
                    Set_Speed -= 10;
                    if(Set_Speed <= MIN_Speed)
                        Set_Speed = MIN_Speed;
                    Ctrl_Speed = Set_Speed;
					EC11A_Knob = 1;//检测是不是在旋动旋钮
                }
                if(sys.SetMode_Option == 2)
                {
                    Set_Time -= 60;
                    if(Set_Time <= 0)
                    {
                        Time_State = 1;//显示“----”
                        Set_Time = 0;
                    }
                    Time = Set_Time;
                    Ctrl_Time = Set_Time;
					EC11A_Knob = 1;//检测是不是在旋动旋钮
					
                }
                Twinkle_Time = 6000;//闪烁显示6S  
            }
            else if((HAL_GPIO_ReadPin(KEY1A_GPIO_Port,KEY1A_Pin)==0)&&(HAL_GPIO_ReadPin(KEY1B_GPIO_Port,KEY1B_Pin)==0))//如果向右旋转
            {
				if(sys.Run_Status == 1 && sys.Motor_Stop == 0)
				{
					Speed = Rel_Speed/Tooth_Ratio; 
					Set_Speed += 10;
                    if(Set_Speed >= MAX_Speed)
                        Set_Speed = MAX_Speed;
					EC11A_Knob = 2;//检测是不是在旋动旋钮
				}
                if(sys.SetMode_Option == 1)
                {
                    Set_Speed += 10;
                    if(Set_Speed >= MAX_Speed)
                        Set_Speed = MAX_Speed;
                    Ctrl_Speed = Set_Speed;
					EC11A_Knob = 1;//检测是不是在旋动旋钮
                }
                if(sys.SetMode_Option == 2)
                {
                    Set_Time += 60;
                    Time_State = 0;//不显示“----”
                    if(Set_Time >= 86400)
                        Set_Time = 86400;
                    Time = Set_Time;
                    Ctrl_Time = Set_Time;
					EC11A_Knob = 1;//检测是不是在旋动旋钮
					
                }
                Twinkle_Time = 6000;//闪烁显示6S  
            }
        }
        EC11A_Flag = 0;//关闭中断 
    }

    /**********左边按钮中断**********/
    if(GPIO_Pin ==KEY1_Pin)
    {
        Key1_Press = 1;//按下标志被置一
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
                    sys.SetMode_Option++;//设置模式++
                    if(sys.SetMode_Option == 3)
                    {
                        sys.SetMode_Option = 0;
                    }
                }
                else//启动下单击按键，直接停止
                {
                    sys.Motor_Stop = 1;//关闭运行
					Speed_ADDMode = 2;//进入减速模式下
                }
                Beep_Time = 0.1;//蜂鸣器响0.1S
                Twinkle_Time = 6000;//闪烁显示6S
                KEY1_Count = 0;//按钮计数清零
                Key1_Press = 0;//按钮状态为抬起
            }
            else//等于200时再清零
            {
                KEY1_Count = 0;//按钮计数清零
                Key1_Press = 0;//按钮状态为抬起
            }
        }
        if(KEY1_Count > 200 && KEY1_Count < 400)//长按
        {
            if(sys.Run_Status == 0)
            {
                sys.Run_Status = 1;
                sys.SetMode_Option = 0;
				Speed_ADDMode = 0;
				Speed_Val.SumError=0x2422;//启动电机系数
				Speed = 0;
            } 
            else
            {
                sys.Motor_Stop = 1;//检测电机
				Speed_ADDMode = 2;//进入减速模式下
            }   
            Beep_Time = 0.1;//蜂鸣器响0.1S
            KEY1_Count = 400;//按钮计数等于200，这样就不会在抬起再进入单击了
        }
    }
}
