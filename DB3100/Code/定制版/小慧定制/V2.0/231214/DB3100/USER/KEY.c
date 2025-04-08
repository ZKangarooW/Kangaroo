#include "KEY.h"

/**********全局变量**********/
uint16_t run_mode = 0;//运行模式
uint8_t Key_Status;//在操作按键时
/**********局部变量**********/
uint16_t cur=300;//连续按加快加减速度
uint16_t Scan_Status=0;//快速加减标志
uint8_t KEY1_Pin_ON=0;//长按标志
uint8_t Key_Flag;//按键按下标志
uint8_t LongPress;//按键长按标志
float Key_Cnt;//按下时间

/*
*****************************************************************
 * 函数原型： static uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 * 功    能： 按键扫描
 * 输    入:  *GPIOx：gipo管脚 GPIO_Pin：引脚
 * 输    出： KEY_ON/KEY_OFF
 * 参    数： GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin
 * 调    用： 内部调用
*****************************************************************
*/
static uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if(HAL_GPIO_ReadPin (GPIOx, GPIO_Pin) == 1 )//按键按下
    {
        uint32_t cur_time = HAL_GetTick();//相当于延时8ms
        static uint32_t start_time = 0;
        if(cur_time - start_time < cur)
            return KEY_OFF;
        if(HAL_GPIO_ReadPin (GPIOx, GPIO_Pin) == 1)
        {
            Scan_Status++;
            if(Scan_Status > 3)//一直按着的时间
                cur = 2;
            start_time = cur_time;
            return KEY_ON;
        }
    }
    else//松开按键后
    {
        if((HAL_GPIO_ReadPin (GPIOB, KEY2_Pin) == 0) && (HAL_GPIO_ReadPin (GPIOB, KEY3_Pin) == 0 ) && (HAL_GPIO_ReadPin (GPIOB, KEY1_Pin) == 0 ) )
        {
            if(HAL_GPIO_ReadPin (GPIOB, KEY5_Pin) == 0)
            {
                KEY1_Pin_ON = 0;//长按计数
            }
            Scan_Status = 0;
            cur = 300;
            return KEY_OFF;
        }
    }
    return KEY_OFF;
}

/*
*****************************************************************
 * 函数原型： void Key_Handle(float dT)
 * 功    能： 按键功能
*****************************************************************
*/
void Key_Handle(float dT)
{
///******************************减***************************************/
//    if((Key_Scan(GPIOB,KEY3_Pin) == KEY_ON))//减
//    {
//        if(Run_Status > 0) //运行中不能设置
//            return;
//        if(Select_Option == 2)//在设置温度选项
//        {
//            set_temp--;//温度--；
//            if(set_temp < 0)//如果设定温度小于0时（单加热只能自动降温）
//            {
//                set_temp = 0;//将设定温度保持在0
//            }
//        }
//        if(Select_Option == 3)//在设置时间选项
//        {
//            if(time_status == 0)//在秒单位模式下
//            {
//                if(set_time)
//                    set_time -= 5;//时间减5s
//                if(set_time < 5)//小于5s的设定值时
//                {
//					set_time = 0;
//                    time_Last = 1;//跳出倒计时
//                    SetTime_State = 1;//设定时间显示“----”
//                }  				
//            }
//            else//在分为单位的模式下
//                set_time -= 60;//时间减1分钟
//        }
//        if(Select_Option == 1)//在设置模式选项
//        {
//            run_mode--;//P记忆位置--
//            if(run_mode < 1)//小于1时返回到第九个位置
//            {
//                run_mode = 1;
//            }
//			Flash_Read((uint8_t *)(&Param),sizeof(Param));
//			set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
//			set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
//			if(set_time > 0 )
//			{
//				SetTime_State = 0;//设定时间退出显示“----”
//				time_Last = 0;
//			}
//			else
//			{
//				SetTime_State = 1;//设定时间显示“----”
//				time_Last = 1;
//			}
//			SetOK_Flag = 1;
//        }
//        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
//        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
//    }
// 
///******************************加***************************************/    
//    if((Key_Scan(GPIOB,KEY2_Pin) == KEY_ON))//加
//    {
//        if(Run_Status > 0) //运行中不能设置
//            return;
//        if(Select_Option == 2)//在设置温度选项
//        {
//            set_temp++;//温度++；
//            if(set_temp > 1000)//最高设定温度在100℃
//                set_temp = 1000;
//        }
//        if(Select_Option == 3)//在设置时间选项
//        {
//            if(time_status == 0)//在秒单位模式下
//            {
//                set_time += 5;//时间加5s
//                time_Last = 0;//加入倒计时
//                SetTime_State = 0;//设定时间退出显示“----”
//            }
//            else//在分单位模式下
//                set_time += 60;//时间加60s
//            if(set_time > 86399)//最高可定时23.59小时
//                set_time = 86399;
//        }
//        if(Select_Option == 1)//在设置模式选项
//        {
//            run_mode++;//P记忆位置++
//            if(run_mode > 9)//大于9时返回到第一个位置
//            {
//                run_mode = 9;
//            }
//			Flash_Read((uint8_t *)(&Param),sizeof(Param));
//			set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
//			set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
//			if(set_time > 0 )
//			{
//				SetTime_State = 0;//设定时间退出显示“----”
//				time_Last = 0;
//			}
//			else
//			{
//				SetTime_State = 1;//设定时间显示“----”
//				time_Last = 1;
//			}
//			SetOK_Flag = 1;
//        }
//        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
//        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
//    }
//    
///*****************************菜单键*************************************/ 
//    if((Key_Scan(GPIOB,KEY1_Pin) == KEY_ON))//菜单键
//    {    
//        if(Run_Status > 0) //运行中不能设置
//            return;
//        Select_Option++;//设置选项切换
//		if(Set_Mode_Enable == 0)
//		{
//			if(Select_Option == 1)//不进入p模式按一下直接进入温度设定
//			{
//				Select_Option = 2;
//			}
//			if(Select_Option > 3)//在温度和时间来换选择
//			{
//				Select_Option = 0;//不进行设置    			
//			}
//		}
//		else
//		{
//			if(Select_Option > 3)//在温度和时间和P模式来换选择
//			{
//				Select_Option = 0;//不进行设置    	
//			}
//		}
//        Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
//        Beep_Time = 0.1;//蜂鸣器响0.1S
//    }
//      
///*******************************P键*************************************/  
//if(HAL_GPIO_ReadPin(GPIOB,KEY5_Pin )== 1)//P键
//    {
//        if(Run_Status > 0) //运行中不能设置
//            return; 
//		if(LongPress == 0)//没有长按过
//		{
//			Key_Cnt += dT;//按下时间++
//			Key_Flag = 1;//按键按下标志置一
//		}
//	}
//	if(Key_Flag == 1)//按键被按下
//	{
//        if(HAL_GPIO_ReadPin(GPIOB,KEY5_Pin )== 0)//P键
//        {
//			if(Key_Cnt < 1.5)//小于1.5S是单击
//			{
//				if(Set_Mode_Enable == 0)
//				{
//					Set_Mode_Enable = 1;//显示p模式的框
//					Select_Option = 1;//进入设定p的位置
//					run_mode = 1;
//					Flash_Read((uint8_t *)(&Param),sizeof(Param));
//					set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
//					set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
//					if(set_time > 0 )
//					{
//						SetTime_State = 0;//设定时间退出显示“----”
//						time_Last = 0;
//					}
//					else
//					{
//						SetTime_State = 1;//设定时间显示“----”
//						time_Last = 1;
//					}
//					SetOK_Flag = 1;	
//					Twinkle_On = 6000;//闪烁倒计时，如果停止按键设置，6S后停止闪烁
//					Beep_Time = 0.1;//蜂鸣器响0.1S
//				}
//				else
//				{
//					Set_Mode_Enable = 0;//不显示P模式
//					run_mode_flag = 0;//不显示P模式框
//					set_time=1200;//退出P模式设置设定时间为20min
//					rel_time=1200;//退出P模式设置实际时间为20min
//					set_temp=370;//退出P模式设置设定温度37℃
//					Select_Option = 0;//不闪烁设置
//					run_mode = 0;
//					Flash_Read((uint8_t *)(&Param),sizeof(Param));
//					set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
//					set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
//					SetOK_Flag = 1;
//					Beep_Time = 0.1;//蜂鸣器响0.1S
//				}
//			}
//			Key_Flag = 0;//按键事件结束，等待下一次按下
//			LongPress = 0;//长按标志清零
//			Key_Cnt = 0;//按钮计数清零
//		}
//		if(Key_Cnt > 1.5 && Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
//		{
//			if(LongPress == 0)//如果没有一直一直长按着
//			{
//				LongPress = 1;//长按标志置一
//			}
//		}
//	}	

    
/******************************开始/停止********************************/       
    if((Key_Scan(GPIOB,KEY4_Pin) == KEY_ON))//开始/停止
    {
        if(Run_Status == 0)//系统没启动
        {
            Select_Option = 0;//设定选项清零
            Run_Status = 1; //系统启动         
            time_disable = 0;//关闭倒计时
            ADD_Mode = 0;//加热状态清零
			Run_Val = 0;
			SetOK_Flag = 1;	
        }
        else
        {
            Run_Status = 0;//关闭系统
            time_disable = 0;//关闭倒计时
			Run_Val = 0;
            ADD_Mode = 0;//加热状态清零
			set_time=Param.P_Param[0][1];//开机设置设定时间为20min
			set_temp=Param.P_Param[0][0];//开机设置设定温度37℃
			SetOK_Flag = 1;
        }
        Beep_Time = 0.1;//蜂鸣器响0.1S
    }
}

/*
*****************************************************************
 * 函数原型：void Check_Key(void)
 * 功    能：检测按键状态-1s
*****************************************************************
*/
void Check_Key(void)
{
    if(Key_Status)
        Key_Status--;
}
