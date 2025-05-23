#include "Drv_LedDisplay.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间
uint8_t IconRun_Time;//跑圈时间

/**********局部变量声明******/
uint8_t DIG,UC,UC10;//DIG,UC的数据
uint8_t SPEED_Tab[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};//显示0-9
uint8_t Icon_Run[] = {0xB4, 0xD8, 0x6C};//圆圈跑起来
uint8_t t;//显示时间
uint8_t Speed_ShowFlag = 0;//速度闪烁
uint8_t Time_ShowFlag = 0;//时间闪烁
uint8_t TimeIcon_ShowFalg = 0;//时间冒号闪烁
uint8_t Icon_ShowFlag = 0;//运行闪烁

/*
*****************************************************************
 * 函数原型： void Check_ShowFlag(float dT)
 * 功    能： 闪烁检测
 * 输    入:  dT:执行周期
 * 参    数： float dT
*****************************************************************
*/
void Check_ShowFlag(float dT)
{
    static float T,T1;
    if(sys.Run_Status)//运行时
    {
        if (T1 == 0)
        {
            TimeIcon_ShowFalg = ~TimeIcon_ShowFalg;
            Icon_ShowFlag = ~Icon_ShowFlag;
        }
        T1 += dT;
        if (T1 >= 0.5f)
        {
            T1 = 0;
        }
    }
    if(!sys.SetMode_Option)//如果没在设置选项中，则都点亮，不闪烁
    {
        Speed_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        Twinkle_Time = 0;//闪烁计时清零
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作旋钮时
    {
        if (T == 0)
        {
            if(sys.SetMode_Option == 1)//设置速度
            {
                Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
                Time_ShowFlag = 0;//时间常亮
            }
            else if(sys.SetMode_Option == 2)//设置温度
            {
                Speed_ShowFlag = 0;//速度常亮
                Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
            }  
        }
        T += dT;
        if (T >= 0.5f)
        {
            Twinkle_Time -= 0.5f;
            if(Twinkle_Time <= 0)//如果闪烁结束
                sys.SetMode_Option = 0;//模式选择清零   
            T = 0;    
        }            
    }
}

/*
*****************************************************************
 * 函数原型： void UCdata_Display(uint8_t uc)
 * 功    能： UC数据判断控制引脚 
*****************************************************************
*/
void UCdata_Display(uint8_t uc)
{
	 for(uint8_t i=0; i<7; i++)
    {
        if((uc<<i) & 0x80)
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(UC_A_GPIO_Port, UC_A_Pin, GPIO_PIN_SET);break;
                case 1: HAL_GPIO_WritePin(UC_B_GPIO_Port, UC_B_Pin, GPIO_PIN_SET);break;
                case 2: HAL_GPIO_WritePin(UC_C_GPIO_Port, UC_C_Pin, GPIO_PIN_SET);break;
                case 3: HAL_GPIO_WritePin(UC_D_GPIO_Port, UC_D_Pin, GPIO_PIN_SET);break;
                case 4: HAL_GPIO_WritePin(UC_E_GPIO_Port, UC_E_Pin, GPIO_PIN_SET);break;
                case 5: HAL_GPIO_WritePin(UC_F_GPIO_Port, UC_F_Pin, GPIO_PIN_SET);break;
                case 6: HAL_GPIO_WritePin(UC_G_GPIO_Port, UC_G_Pin, GPIO_PIN_SET);break;
            }      
        }
        else
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(UC_A_GPIO_Port, UC_A_Pin, GPIO_PIN_RESET);break;
                case 1: HAL_GPIO_WritePin(UC_B_GPIO_Port, UC_B_Pin, GPIO_PIN_RESET);break;
                case 2: HAL_GPIO_WritePin(UC_C_GPIO_Port, UC_C_Pin, GPIO_PIN_RESET);break;
                case 3: HAL_GPIO_WritePin(UC_D_GPIO_Port, UC_D_Pin, GPIO_PIN_RESET);break;
                case 4: HAL_GPIO_WritePin(UC_E_GPIO_Port, UC_E_Pin, GPIO_PIN_RESET);break;
                case 5: HAL_GPIO_WritePin(UC_F_GPIO_Port, UC_F_Pin, GPIO_PIN_RESET);break;
                case 6: HAL_GPIO_WritePin(UC_G_GPIO_Port, UC_G_Pin, GPIO_PIN_RESET);break;
            }
        }
    } 
}

/*
*****************************************************************
 * 函数原型： DIGdata_Display(uint8_t DIG)
 * 功    能： DIG数据判断控制引脚 
*****************************************************************
*/
void DIGdata_Display(uint8_t DIG)
{
	 for(uint8_t i=0; i<8; i++)
    {
        if((DIG<<i) & 0x80)
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_RESET);break;
                case 1: HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_RESET);break;
                case 2: HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_RESET);break;
                case 3: HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_RESET);break;
                case 4: HAL_GPIO_WritePin(DIG5_GPIO_Port, DIG5_Pin, GPIO_PIN_RESET);break;
                case 5: HAL_GPIO_WritePin(DIG6_GPIO_Port, DIG6_Pin, GPIO_PIN_RESET);break;
                case 6: HAL_GPIO_WritePin(DIG7_GPIO_Port, DIG7_Pin, GPIO_PIN_RESET);break;
                case 7: HAL_GPIO_WritePin(DIG8_GPIO_Port, DIG8_Pin, GPIO_PIN_RESET);break;
            }      
        }
        else
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_SET);break;
                case 1: HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_SET);break;
                case 2: HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_SET);break;
                case 3: HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_SET);break;
                case 4: HAL_GPIO_WritePin(DIG5_GPIO_Port, DIG5_Pin, GPIO_PIN_SET);break;
                case 5: HAL_GPIO_WritePin(DIG6_GPIO_Port, DIG6_Pin, GPIO_PIN_SET);break;
                case 6: HAL_GPIO_WritePin(DIG7_GPIO_Port, DIG7_Pin, GPIO_PIN_SET);break;
                case 7: HAL_GPIO_WritePin(DIG8_GPIO_Port, DIG8_Pin, GPIO_PIN_SET);break;
            }
        }
    } 
}

/*
*****************************************************************
 * 函数原型： void DIGdata_Set(void)
 * 功    能： 1-8DIG引脚全部拉高
*****************************************************************
*/
void DIGdata_Set(void)
{
    HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG5_GPIO_Port, DIG5_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG6_GPIO_Port, DIG6_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG7_GPIO_Port, DIG7_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG8_GPIO_Port, DIG8_Pin, GPIO_PIN_SET);
}

/*
*****************************************************************
 * 函数原型： void Display_SpeedShow(uint16_t speed)
 * 功    能： 显示速度
 * 输    入:  speed：要显示的速度
 * 参    数： uint16_t speed
*****************************************************************
*/
void Display_SpeedShow(uint16_t speed)
{
    uint8_t Val;//用于百十个取出来的数字
    if(t == 1)
    {
        /***********L1千位***********/
        if(speed > 999)//大于999时
        {	
			Val=speed/1000;//取出千位的数字			
            switch(Val)
            {
                case 0:UC = SPEED_Tab[0];//数字0
                    break;
                case 1:UC = SPEED_Tab[1];//数字1
                    break;
                case 2:UC = SPEED_Tab[2];//数字2
                    break;
                case 3:UC = SPEED_Tab[3];//数字3
                    break;	
                case 4:UC = SPEED_Tab[4];//数字4
                    break;	
                case 5:UC = SPEED_Tab[5];//数字5
                    break;
                case 6:UC = SPEED_Tab[6];//数字6
                    break;	
                case 7:UC = SPEED_Tab[7];//数字7
                    break;	
                case 8:UC = SPEED_Tab[8];//数字8
                    break;	
                case 9:UC = SPEED_Tab[9];//数字9
                    break;
                default:
                    break;
            }	
            UCdata_Display(UC);
            if(Speed_ShowFlag >= 1 && Key_Status == 0)//闪烁速度
                DIGdata_Display(0x00);          
            else
                DIGdata_Display(0x80);
        }
        else//小于999时
        {
            DIGdata_Display(0x00);
        }  
    }
    else if(t == 2)
    {
        /***********L1百位***********/
        if(speed > 99)//大于99时
        {
            Val=speed/100;//取出百位的数字
            if(speed > 999)//加入大于999时
                Val=Val%10;//取出百位的数字
            switch(Val)
            {
                case 0:UC = SPEED_Tab[0];//数字0
                    break;
                case 1:UC = SPEED_Tab[1];//数字1
                    break;
                case 2:UC = SPEED_Tab[2];//数字2
                    break;
                case 3:UC = SPEED_Tab[3];//数字3
                    break;	
                case 4:UC = SPEED_Tab[4];//数字4
                    break;	
                case 5:UC = SPEED_Tab[5];//数字5
                    break;
                case 6:UC = SPEED_Tab[6];//数字6
                    break;	
                case 7:UC = SPEED_Tab[7];//数字7
                    break;	
                case 8:UC = SPEED_Tab[8];//数字8
                    break;	
                case 9:UC = SPEED_Tab[9];//数字9
                    break;
                default:
                    break;
            }	
            UCdata_Display(UC); 
            if(Speed_ShowFlag >= 1 && Key_Status == 0)
                DIGdata_Display(0x00);          
            else
                DIGdata_Display(0x40);
        }
        else
        {
            DIGdata_Display(0x00);//不显示
        }
        
    }
    else if(t == 3)
    {
        /***********L1十位***********/
        if(speed > 9)//大于9时
        {
            Val=speed/10;//取出十位的数字
            if(speed > 99)//大于99时
                Val=Val%10;//取出十位的数字
            switch(Val)
            {
                case 0:UC = SPEED_Tab[0];//数字0
                    break;
                case 1:UC = SPEED_Tab[1];//数字1
                    break;
                case 2:UC = SPEED_Tab[2];//数字2
                    break;
                case 3:UC = SPEED_Tab[3];//数字3
                    break;	
                case 4:UC = SPEED_Tab[4];//数字4
                    break;	
                case 5:UC = SPEED_Tab[5];//数字5
                    break;
                case 6:UC = SPEED_Tab[6];//数字6
                    break;	
                case 7:UC = SPEED_Tab[7];//数字7
                    break;	
                case 8:UC = SPEED_Tab[8];//数字8
                    break;	
                case 9:UC = SPEED_Tab[9];//数字9
                    break;
                default:
                    break;
            }
            UCdata_Display(UC);  
            if(Speed_ShowFlag >= 1 && Key_Status == 0)
                DIGdata_Display(0x00);          
            else
                DIGdata_Display(0x20);         
        }
        else
        {
            DIGdata_Display(0x00);//不显示
        }
    }
    else if(t == 4)
    {
        /***********L1个位***********/
        UC = SPEED_Tab[0];//数字0
        UCdata_Display(UC);
        if(Speed_ShowFlag >= 1 && Key_Status == 0)
            DIGdata_Display(0x00);          
        else
            DIGdata_Display(0x10);
    }
}

/*
*****************************************************************
 * 函数原型： void Display_TimeShow(int32_t time)
 * 功    能： 显示时间
 * 输    入:  time：要显示的时间
 * 参    数： int32_t time
*****************************************************************
*/
void Display_TimeShow(int32_t time)
{
    uint8_t SH,H,SM,M;//用于百十个取出来的数字
    SH=time/3600/10;//计算十位单位的小时数
    H=time/3600%10;//计算个位单位的小时数
    SM=time%3600/60/10;//计算十分位单位的分钟数
    M=time%3600/60%10;//计算个分位单位的分钟数
    if(t == 5)
    {
        /***********L1千位***********/
        switch(SH)
        {
            case 0:UC = SPEED_Tab[0];//数字0
                break;
            case 1:UC = SPEED_Tab[1];//数字1
                break;
            case 2:UC = SPEED_Tab[2];//数字2
                break;
            case 3:UC = SPEED_Tab[3];//数字3
                break;	
            case 4:UC = SPEED_Tab[4];//数字4
                break;	
            case 5:UC = SPEED_Tab[5];//数字5
                break;
            case 6:UC = SPEED_Tab[6];//数字6
                break;	
            case 7:UC = SPEED_Tab[7];//数字7
                break;	
            case 8:UC = SPEED_Tab[8];//数字8
                break;	
            case 9:UC = SPEED_Tab[9];//数字9
                break;
            default:
                break;
        }
        if(Time.Set <= 0)
            UCdata_Display(0x02);
        else            
            UCdata_Display(UC); 
        if(Time_ShowFlag >= 1 && Key_Status == 0)//时间闪烁
            DIGdata_Display(0x00);          
        else        
            DIGdata_Display(0x08);
    }
    else if(t == 6)
    {
        /***********L1百位***********/
        switch(H)
        {
            case 0:UC = SPEED_Tab[0];//数字0
                break;
            case 1:UC = SPEED_Tab[1];//数字1
                break;
            case 2:UC = SPEED_Tab[2];//数字2
                break;
            case 3:UC = SPEED_Tab[3];//数字3
                break;	
            case 4:UC = SPEED_Tab[4];//数字4
                break;	
            case 5:UC = SPEED_Tab[5];//数字5
                break;
            case 6:UC = SPEED_Tab[6];//数字6
                break;	
            case 7:UC = SPEED_Tab[7];//数字7
                break;	
            case 8:UC = SPEED_Tab[8];//数字8
                break;	
            case 9:UC = SPEED_Tab[9];//数字9
                break;
            default:
                break;
        }	
        if(Time.Set <= 0)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC);  
        if(Time_ShowFlag >= 1 && Key_Status == 0)
            DIGdata_Display(0x00);          
        else
            DIGdata_Display(0x04);
    }
    else if(t == 7)
    {
        /***********L1十位***********/
        switch(SM)
        {
            case 0:UC = SPEED_Tab[0];//数字0
                break;
            case 1:UC = SPEED_Tab[1];//数字1
                break;
            case 2:UC = SPEED_Tab[2];//数字2
                break;
            case 3:UC = SPEED_Tab[3];//数字3
                break;	
            case 4:UC = SPEED_Tab[4];//数字4
                break;	
            case 5:UC = SPEED_Tab[5];//数字5
                break;
            case 6:UC = SPEED_Tab[6];//数字6
                break;	
            case 7:UC = SPEED_Tab[7];//数字7
                break;	
            case 8:UC = SPEED_Tab[8];//数字8
                break;	
            case 9:UC = SPEED_Tab[9];//数字9
                break;
            default:
                break;
        }	
        if(Time.Set <= 0)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC); 
        if(Time_ShowFlag >= 1 && Key_Status == 0)
            DIGdata_Display(0x00);          
        else        
            DIGdata_Display(0x02);
    }
    else if(t == 8)
    {
        /***********L1个位***********/
        switch(M)
        {
            case 0:UC = SPEED_Tab[0];//数字0
                break;
            case 1:UC = SPEED_Tab[1];//数字1
                break;
            case 2:UC = SPEED_Tab[2];//数字2
                break;
            case 3:UC = SPEED_Tab[3];//数字3
                break;	
            case 4:UC = SPEED_Tab[4];//数字4
                break;	
            case 5:UC = SPEED_Tab[5];//数字5
                break;
            case 6:UC = SPEED_Tab[6];//数字6
                break;	
            case 7:UC = SPEED_Tab[7];//数字7
                break;	
            case 8:UC = SPEED_Tab[8];//数字8
                break;	
            case 9:UC = SPEED_Tab[9];//数字9
                break;
            default:
                break;
        }	
        if(Time.Set <= 0)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC);  
        if(Time_ShowFlag >= 1 && Key_Status == 0)
            DIGdata_Display(0x00);          
        else
            DIGdata_Display(0x01);    
    }
}

/*
*****************************************************************
 * 函数原型： void Display_Icon(void)
 * 功    能： 显示图标
*****************************************************************
*/
void Display_Icon(void)
{
    if(t == 9)
    {
        UC = 0x18;//时间冒号图标        
        UCdata_Display(UC);  
        DIGdata_Set();
        if(TimeIcon_ShowFalg >= 1 && sys.Run_Status == 1 && Time.Set <= 0)//闪烁
        {
            DIG9_OFF;
        }
        else
        {
            DIG9_ON;
        }
        DIG10_OFF;
    }
    else if(t == 10)
    {
        static uint8_t cnt;
        IconRun_Time++;
        if(IconRun_Time >= 10)//200ms跑圈
        {
            cnt ++;
            if(cnt == 4)
                cnt = 1;
            switch(cnt)
            {
                case 1:UC10 = Icon_Run[0];break;
                case 2:UC10 = Icon_Run[1];break;
                case 3:UC10 = Icon_Run[2];break;
            } 
            IconRun_Time = 0;
        }
        if(sys.Run_Status == 0)
            UC10 = 0xFC; 
        UC = UC10;   
        UCdata_Display(UC);  
        DIGdata_Set();
        DIG9_OFF;
        DIG10_ON;
    }
    if(t == 11)//刷新
    {
        DIGdata_Set();
        DIG9_OFF;
        DIG10_OFF;
        t = 0;
    }
}

/*
*****************************************************************
 * 函数原型： void Deal_Speed(void)
 * 功    能： 速度显示处理
*****************************************************************
*/
uint16_t Rel_Val;
void Deal_Speed(void)
{
    Rel_Val = Speed.Rel;
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//启动的情况下
    {
        if(Speed.ADDMode == 0)//在电机控制中，速度未处理
        {
            if(Speed.Ctrl > Rel_Val)//控制速度大于实际速度
            {
                Speed.New =0;//现在的速度清零
                Speed.Last = 0;//之前的速度清零
                Speed.ADDMode = 1;//进入加速模式下
            }
            else if(Speed.Ctrl <= Rel_Val)//控制速度小于显示速度
            {
                Speed.New=0;//现在的速度清零
                Speed.Last = Rel_Val;//之前的速度等于当前显示速度
                Speed.ADDMode = 2;//进入减速模式下
            }
        }
        if(Speed.ADDMode==1)//在进入加速模式下
        { 
			if(Rel_Val >= Speed.Ctrl)//实际速度大于等于控制速度
			{
				Speed.ADDMode = 3;//进入稳定模式
				return;
			}
			Speed.New = Rel_Val;//记录当前速度
			if(Speed.New > Speed.Last)//当前速度大于上一次速度
				Speed.Display = Speed.New;//显示当前速度
			else//当前速度小于上一次速度
			{
				Speed.Display = Speed.Last;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
				Speed.New = Speed.Last;//将上一次速度赋值给当前速度
			}
			Speed.Last = Speed.New;//将当前速度保存 				
        }
        else if(Speed.ADDMode == 2)//速度下降模式下
        {
			if(Rel_Val <= Speed.Ctrl)//实际速度小于等于控制速度
			{
				Speed.ADDMode = 3;//稳定模式
				return;
			}
			Speed.New = Rel_Val;//记录当前速度
			if(Speed.New < Speed.Last)//当前速度小于上一次速度
				Speed.Display = Speed.New;//显示当前速度
			else//当前速度大于上一次速度
			{
				Speed.Display = Speed.Last;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
				Speed.New = Speed.Last;//将上一次速度赋值给当前速度
			}
			Speed.Last = Speed.New;//将当前速度保存
        }
        else if(Speed.ADDMode == 3)//速度稳定模式下
        {
            Speed.Display = Speed.Ctrl;//显示控制速度
        }
		else if(Speed.ADDMode == 4)//速度下降停止模式下
        {
            Speed.New = Rel_Val;//记录当前速度
            if(Speed.New < Speed.Last)//当前速度小于上一次速度
                Speed.Display = Speed.New;//显示当前速度
            else//当前速度大于上一次速度
            {
                Speed.Display = Speed.Last;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed.New = Speed.Last;//将上一次速度赋值给当前速度
            }
            Speed.Last = Speed.New;//将当前速度保存
        }
    }
}


/*
*****************************************************************
 * 函数原型： void Display_Show(float dT)
 * 功    能： 显示屏幕
*****************************************************************
*/
void Display_Show(float dT)
{
	t++;
	if(sys.Run_Status == 0)
	{
		Speed.Display = Speed.Set;
		Time.Display = Time.Set;
	}
	else
	{
		if(sys.SetMode_Option == 1)//在设置速度模式下
        {
            Speed.Display = Speed.Set;//显示设定速度
            Time.Display = Time.Rel+59;//显示实际时间
        }
        else if(sys.SetMode_Option == 2)//在设置时间模式下
        {
            Deal_Speed();//速度显示处理
            Time.Display = Time.Set;//显示设定时间 
        }            
        else//在不设置模式下
        {
            Deal_Speed();//速度显示处理 
            Time.Display = Time.Rel+59;//显示实际时间
        }
	}
	Display_SpeedShow(Speed.Display);
	Display_TimeShow(Time.Display);
	Display_Icon();
}
