#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Tab[] = {0x77,0x24,0x5D,0x6D,0x2E,0x6B,0x7B,0x25,0x7F,0x6F};//0·9
uint8_t Tab1[] = {0x77,0x12,0x5D,0x5B,0x3A,0x6B,0x6f,0x52,0x7F,0x7B};//0·9
uint8_t Temp_ShowFlag,Speed_ShowFlag,Time_ShowFlag;//温度、速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag,SpeedIcn_ShowFlag;//加热图标闪烁和时间图标闪烁和速度图标闪烁

/*
*****************************************************************
 * 函数原型：static void Icn_Twinkle(float dT)
 * 功    能：图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status)		
	{
		T += dT;
		if(T >= 0.5f)
		{
			if(Speed.Set)
			{
				SpeedIcn_ShowFlag ++;//速度图标闪烁;
				if(SpeedIcn_ShowFlag > 3)
					SpeedIcn_ShowFlag = 1;
			}
            else
            {
                SpeedIcn_ShowFlag = 0;
            }
			if(Temp.Set)
				TempIcn_ShowFlag = ~TempIcn_ShowFlag;//温度图标闪烁;
            else
                TempIcn_ShowFlag = 0;
			if(Time.Rel && (!Temp.Ctrl || TempIcn_ShowFlag != TimeIcn_ShowFlag) && (Temp.Set == 0 || Temp.ADDMode == 3))
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//时间图标闪烁;
            else
            {
                TimeIcn_ShowFlag = 0;
            }
			T = 0;
		}
	}
	else
	{
		SpeedIcn_ShowFlag = 0;//不显示速度图标
		TempIcn_ShowFlag = 0;//不显示温度图标
		TimeIcn_ShowFlag = 0;//不显示时间图标
	}
}

/*
*****************************************************************
 * 函数原型：static void Check_ShowFlag(float dT)
 * 功    能：闪烁检测
 * 输    入: dT:执行周期
 * 参    数：float dT
 * 调    用：内部调用
*****************************************************************
*/
static void Check_ShowFlag(float dT)
{
	static float T;
    if(sys.SetMode_Option == 0)//如果没在设置选项中，则都点亮，不闪烁
    {
        Speed_ShowFlag = 0;//常亮
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        Twinkle_Time = 0;//闪烁计时清零
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作按键时
    {
		T += dT;
		if(T >= 0.5f)
		{
			Twinkle_Time -= 0.5;//闪烁计时
			if(sys.SetMode_Option == 1)//设置温度
			{
				Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
				Speed_ShowFlag = 0;//速度常亮
				Time_ShowFlag = 0;//时间常亮
			}
			else if(sys.SetMode_Option == 2)//设置速度
			{ 
				Temp_ShowFlag = 0;//温度常亮
				Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
				Time_ShowFlag = 0;//时间常亮
			}
			else if(sys.SetMode_Option == 3)//设置时间
			{
				Temp_ShowFlag = 0;//温度常亮
				Speed_ShowFlag = 0;//速度常亮
				Time_ShowFlag = ~Time_ShowFlag;//时间闪烁		
			}
			if(Twinkle_Time == 0)//如果闪烁结束
			{
				sys.SetMode_Option = 0;//模式选择清零
			} 
			T = 0;			
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//常亮
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
		T = 0;
	}
}

/*
*****************************************************************
 * 函数原型：void Twinkle(float dT)
 * 功    能：闪烁函数
*****************************************************************
*/
void Twinkle(float dT)
{
	Check_ShowFlag(dT);//闪烁检测
	Icn_Twinkle(dT);//图标闪烁
}

/*
*****************************************************************
 * 函数原型：void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
 * 功    能：显示温度
 * 输    入: dis_set_temp 设定温度  dis_rel_temp 实际温度
 * 参    数：int16_t dis_set_temp,int16_t dis_rel_temp
*****************************************************************
*/
void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********设定温度计算**********/
	if(Temp_ShowFlag == 0)
	{
		if(dis_set_temp > 0)
		{
			if(dis_set_temp > 999)//大于999时
			{
				Val=dis_set_temp/1000;//取出千位
				seg1 = Tab1[Val];
			}
			else
			{
				Val = 0x00;//不显示
			}
			if(dis_set_temp > 99)//大于99时
			{
				Val=dis_set_temp/100;//取出百位
				if(dis_set_temp > 999)//大于999时
					Val=Val%10;//取出百位
				seg2 = Tab1[Val];
			}
			else
			{
				seg2 = 0x00;//不显示
			}
			if(dis_set_temp > 9)//大于9时
			{
				Val=dis_set_temp/10;//取出十位
				if(dis_set_temp > 99)//大于99时
					Val=Val%10;//取出十位
				seg3 = Tab1[Val];
			}
			else
			{
				seg3 = Tab1[0];//不显示0
			}
			Val=dis_set_temp%10;//取出个位
			seg4 = Tab1[Val];
			seg3 &= 0x7F;seg3 |= 0x80;//设定温度的小数点
		}
		else
		{
			seg1 = 0x08;//显示"-"
			seg2 = 0x08;//显示"-"
			seg3 = 0x08;//显示"-"
			seg4 = 0x08;//显示"-"
			seg3 &= 0x7F;seg3 |= 0x00;//不显示设定温度的小数点
		}
	}
	else
	{
		seg1 = 0x00;//不显示设定温度
		seg2 = 0x00;//不显示设定温度
		seg3 = 0x00;//不显示设定温度
		seg4 = 0x00;//不显示设定温度
		seg3 &= 0x7F;seg3 |= 0x00;//不显示设定温度的小数点
	}
	
	/***********实际温度计算**********/
	if(dis_rel_temp > 999)//大于999时
	{
		Val=dis_rel_temp/1000;//取出千位
		seg5 = Tab[Val];
	}
	else
	{
		seg5 = 0x00;//不显示
	}
	if(dis_rel_temp > 99)//大于99时
	{
		Val=dis_rel_temp/100;//取出百位
		if(dis_rel_temp > 999)//大于999时
			Val=Val%10;//取出百位
		seg6 = Tab[Val];
	}
	else
	{
		seg6 = 0x00;//不显示
	}
	if(dis_rel_temp > 9)//大于9时
	{
		Val=dis_rel_temp/10;//取出十位
		if(dis_rel_temp > 99)//大于99时
			Val=Val%10;//取出十位
		seg7 = Tab[Val];
	}
	else
	{
		seg7 = Tab[0];//不显示0
	}
	Val=dis_rel_temp%10;//取出个位
	seg8 = Tab[Val];
	
	/*************温度小数点的图标*******/
	seg7 &= 0x7F;seg7 |= 0x80;//实际温度的小数点
	
	/****************℃******************/
	seg4 &= 0x7F;seg4 |= 0x80;//℃

	/*************加热图标***************/
//	if(sys.Run_Status && Temp.Ctrl_Temp)
	if(TempIcn_ShowFlag == 0)
	{
		seg6 &= 0x7F;seg6 |= 0x80;//加热图标底部
		seg8 &= 0x7F;seg8 |= 0x80;//加热图标上半部分
	}
	else
	{
		seg6 &= 0x7F;seg6 |= 0x00;//不显示加热图标底部
		seg8 &= 0x7F;seg8 |= 0x00;//不显示加热图标上半部分
	}
	
	/*************发送数据***************/	
	Write_Addr_Dat_N(38, seg1,1);
	Write_Addr_Dat_N(36, seg2,1);
	Write_Addr_Dat_N(34, seg3,1);
	Write_Addr_Dat_N(32, seg4,1);
	Write_Addr_Dat_N(0, seg5,1);
	Write_Addr_Dat_N(2, seg6,1);
	Write_Addr_Dat_N(4, seg7,1);
	Write_Addr_Dat_N(6, seg8,1);
}

/*
*****************************************************************
 * 函数原型：void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
 * 功    能：显示转速
 * 输    入: dis_set_speed 设定转速  dis_rel_speed 实际转速
 * 参    数：int16_t dis_set_speed,int16_t dis_rel_speed
*****************************************************************
*/
void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint16_t Val;//用于百十个取出来的数字
	if(Speed_ShowFlag == 0)
	{
        if(dis_set_speed > 0)
		{
            /***********设定转速计算**********/
            if(dis_set_speed > 999)//大于999时
            {
                Val=dis_set_speed/1000;//取出千位
                seg1 = Tab1[Val];
            }
            else
            {
                seg1 = 0x00;//显示0
            }
            if(dis_set_speed > 99)//大于99时
            {
                Val=dis_set_speed/100;//取出百位
                if(dis_set_speed > 999)//大于999时
                    Val=Val%10;//取出百位
                seg2 = Tab1[Val];
            }
            else
            {
                seg2 = 0x00;//显示0
            }
            if(dis_set_speed > 9)//大于9时
            {
                Val=dis_set_speed/10;//取出十位
                if(dis_set_speed > 99)//大于99时
                    Val=Val%10;//取出十位
                seg3 = Tab1[Val];
            }
            else
            {
                seg3 = 0x00;//显示0
            }
            Val=dis_set_speed%10;//取出个位
            seg4 = Tab1[Val];
        }
        else
        {
            seg1 = 0x08;//显示"-"
			seg2 = 0x08;//显示"-"
			seg3 = 0x08;//显示"-"
			seg4 = 0x08;//显示"-"
        }
	}
	else
	{
		seg1 = 0x00;//不显示设定速度
		seg2 = 0x00;//不显示设定速度
		seg3 = 0x00;//不显示设定速度
		seg4 = 0x00;//不显示设定速度
	}
	
	/***********实际转速计算**********/
	if(dis_rel_speed > 999)//大于999时
	{
		Val=dis_rel_speed/1000;//取出千位
		seg5 = Tab[Val];
	}
	else
	{
		seg5 = 0x00;//显示0
	}
	if(dis_rel_speed > 99)//大于99时
	{
		Val=dis_rel_speed/100;//取出百位
		if(dis_rel_speed > 999)//大于999时
			Val=Val%10;//取出百位
		seg6 = Tab[Val];
	}
	else
	{
		seg6 = 0x00;//显示0
	}
	if(dis_rel_speed > 9)//大于9时
	{
		Val=dis_rel_speed/10;//取出十位
		if(dis_rel_speed > 99)//大于99时
			Val=Val%10;//取出十位
		seg7 = Tab[Val];
	}
	else
	{
		seg7 = 0x00;//显示0
	}
	Val=dis_rel_speed%10;//取出个位
	seg8 = Tab[Val];


	/***************rpm******************/
	seg4 &= 0x7F;seg4 |= 0x80;//rpm
	
	/*************转速图标***************/
	switch(SpeedIcn_ShowFlag)
	{
		case 0: seg5 &= 0x7F;seg5 |= 0x80;//转速S6
				seg6 &= 0x7F;seg6 |= 0x80;//转速S5
				seg7 &= 0x7F;seg7 |= 0x80;//转速S7
			break;
		case 1: seg5 &= 0x7F;seg5 |= 0x80;//转速S6
				seg6 &= 0x7F;seg6 |= 0x80;//转速S5
				seg7 &= 0x7F;seg7 |= 0x00;//转速S7
			break;
		case 2: seg5 &= 0x7F;seg5 |= 0x80;//转速S6
				seg6 &= 0x7F;seg6 |= 0x00;//转速S5
				seg7 &= 0x7F;seg7 |= 0x80;//转速S7
			break;
		case 3: seg5 &= 0x7F;seg5 |= 0x00;//转速S6
				seg6 &= 0x7F;seg6 |= 0x80;//转速S5
				seg7 &= 0x7F;seg7 |= 0x80;//转速S7
			break;
		default:
			break;
	}
	
	/*************发送数据***************/	
	Write_Addr_Dat_N(22, seg1,1);
	Write_Addr_Dat_N(20, seg2,1);
	Write_Addr_Dat_N(18, seg3,1);
	Write_Addr_Dat_N(16, seg4,1);
	Write_Addr_Dat_N(8, seg5,1);
	Write_Addr_Dat_N(10, seg6,1);
	Write_Addr_Dat_N(12, seg7,1);
	Write_Addr_Dat_N(14, seg8,1);
}

/*
*****************************************************************
 * 函数原型：void Display_Time(int32_t dis_time)
 * 功    能：显示时间
 * 输    入: dis_time 时间
 * 参    数：int32_t dis_time
*****************************************************************
*/
void Display_Time(int32_t dis_time)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint8_t SH,H,SM,M;//时间的单位取值
	
	if(Time.Set || sys.SetMode_Option == 3)//设定时间大于0，在设定时间和闪烁下
	{
		if(!Time_ShowFlag)
        {
			if(Time.Set)//假如设定时间大于0
			{
				/**************时间计算*************/
				SH=dis_time/3600/10;//计算十位单位的小时数
				H=dis_time/3600%10;//计算个位单位的小时数
				SM=dis_time%3600/60/10;//计算十分位单位的分钟数
				M=dis_time%3600/60%10;//计算个分位单位的分钟数
				seg1 = Tab1[SH];
				seg2 = Tab1[H];
				seg3 = Tab1[SM];
				seg4 = Tab1[M];
			}
			else
			{
				seg1 = 0x08;//显示"-"
				seg2 = 0x08;//显示"-"
				seg3 = 0x08;//显示"-"
				seg4 = 0x08;//显示"-"
			}
		}
		else//设定时间等于0
		{
			seg1 = 0x00;//不显示时间
			seg2 = 0x00;//不显示时间
			seg3 = 0x00;//不显示时间
			seg4 = 0x00;//不显示时间
		}
	}
	else//设定时间等于0
	{
		seg1 = 0x00;//不显示时间
		seg2 = 0x00;//不显示时间
		seg3 = 0x00;//不显示时间
		seg4 = 0x00;//不显示时间
	}

	if(Time.Set > 0 || sys.SetMode_Option == 3)
	{
		/************时间冒号图标************/
		seg2 &= 0x7F;seg2 |= 0x80;//时间冒号
		
		/*************时间单位图标***********/
		seg4 &= 0x7F;seg4 |= 0x80;//min
		
		/*************时间图标***************/	
		if(TimeIcn_ShowFlag == 0)
		{
			seg1 &= 0x7F;seg1 |= 0x80;//时间图标
		}
		else
		{
			seg1 &= 0x7F;seg1 |= 0x00;//不显示时间图标
		}
	}
	else
	{
		seg2 &= 0x7F;seg2 |= 0x00;//不显示时间冒号
		seg4 &= 0x7F;seg4 |= 0x00;//不显示min
		seg1 &= 0x7F;seg1 |= 0x00;//不显示显示时间图标
	}

	/*************外部探头的图标*********/
	if(PT_VALUE_1_TEMP < 2200)//假如插入外部探头
	{
		seg3 &= 0x7F;seg3 |= 0x80;//外部探头的图标
	}
	else
	{
		seg3 &= 0x7F;seg3 |= 0x00;//不显示外部探头的图标
	}
	
	/*************发送数据***************/	
	Write_Addr_Dat_N(30, seg1,1);
	Write_Addr_Dat_N(28, seg2,1);
	Write_Addr_Dat_N(26, seg3,1);
	Write_Addr_Dat_N(24, seg4,1);
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(float dT)
 * 功    能：速度显示处理
*****************************************************************
*/
void Deal_Speed(float dT)
{
	if(sys.Run_Status)
	{
        if(Speed.ADDMode==0)//在电机控制中，速度未处理
		{ 
			if(Speed.Ctrl >= Speed.Display_Rel)//控制速度大于实际速度
            {
                Speed.ADDMode = 1;//进入加速模式下
            }
            else if(Speed.Ctrl < Speed.Display_Rel)//控制速度小于实际速度
            {
                Speed.ADDMode = 2;//进入减速模式下
            }
		}
		if(Speed.ADDMode==1)//在进入加速模式下
		{
			Speed.New = Speed.Rel;//记录当前速度
            if(Speed.New > Speed.Display_Rel)//当前速度大于显示速度
			{
				if(Speed.Display_Rel < Speed.New)
					Speed.Display_Rel+=1;//显示当前速度
			}
            else//当前速度小于上一次速度
            {
                Speed.Display_Rel = Speed.Display_Rel;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
            }  
            if(Speed.Display_Rel >= Speed.Ctrl)//实际速度大于等于控制速度
            {
                Speed.ADDMode = 3;//进入稳定模式
                return;
            }
		}
		if(Speed.ADDMode==2)//在进入减速模式下
		{ 
			Speed.New = Speed.Rel;//记录当前速度
            
            if(Speed.New < Speed.Display_Rel)//当前速度小于上一次速度
			{
				if(Speed.Display_Rel > Speed.New)
					Speed.Display_Rel -=1;//显示当前速度
			}
            else//当前速度大于上一次速度
            {
                Speed.Display_Rel = Speed.Display_Rel;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
            }
            
            if(sys.Motor_Stop == 0)
			{
                if(Speed.Display_Rel <= Speed.Ctrl)//当前的速度大于等于控制速度
                {
                    Speed.ADDMode = 3;//进入稳定模式
                    return;
                }
            }
		}
		else if(Speed.ADDMode == 3)//速度稳定模式下
		{
			Speed.Display_Rel = Speed.Ctrl;//显示控制速度
		}
	}
	else
	{
        Speed.Display_Rel = 0;
		Speed.New =0;//现在的速度清零
		Speed.Last = 0;//之前的速度清零
		Speed.ADDMode = 0;//清除显示处理
	}
}

/*
*****************************************************************
 * 函数原型：void Deal_Temp(float dT)
 * 功    能：温度显示处理
*****************************************************************
*/

void Deal_Temp(float dT)
{
    static float T;
	uint8_t val;
	if(sys.Run_Status && Temp.Ctrl)
	{
		if(PT_VALUE_1_TEMP < 2200)//假如插入外部探头
			val = 40;
		else//假如没有插入外部探头
		{
			if(Temp.Ctrl < 2800)
				val = 100;
			else
				val = 140;
		}
		if(ABS(Temp.Ctrl - Temp.Rel) < val)
		{
			if(Temp.ADDMode==0)//判断模式
			{ 
				if(Temp.Ctrl > Temp.Rel)
				{
					Temp.ADDMode = 1;//进入升温模式
                    Temp_Arg.Kd = 30; 
					Temp.Last = Temp.Rel;
				}
				else if(Temp.Ctrl < Temp.Rel)
				{
					Temp.ADDMode = 2;//进入降温模式
                    Temp_Arg.Kd = 0; 
					Temp.Last = Temp.Rel;//记录当前温度
				}
				else
				{
					Temp.ADDMode = 3;//进入稳定模式
					Temp_Arg.Kd = 10;//pid参数调整
				}
			}
            
			else if(Temp.ADDMode==1)//在进入升温模式下
			{ 
				Temp.New = Temp.Rel;//记录当前温度
				if(Temp.New > Temp.Last)//当前温度大于上一次温度
					Temp.Display_Rel = Temp.New;//显示当前温度
				else//当前温度小于上一次温度
				{
                    if(Temp.Ctrl == 1000)
                    {
                        if(Temp.Display_Rel == Temp.Last)
                        {
                            T += dT;
                            if(T > 10)
                            {
                                Temp.Display_Rel += 1;
                                Temp.Last = Temp.Display_Rel;
                                T = 0;
                            }
                        }
                        else
                        {
                            T = 0;
                        }
                    }
					Temp.Display_Rel = Temp.Last;//显示上一次温度，不让温度小于当前温度。呈现攀升速度的现象
					Temp.New = Temp.Last;//将上一次温度赋值给当前温度
				}
                Temp.Last = Temp.New;//将当前温度保存                
				if(Temp.Display_Rel >= Temp.Ctrl)//当前的温度大于等于控制温度
				{
					Temp.ADDMode = 3;//进入稳定模式
                    Temp_Val.Integral = 0;//温度控制积分清零
                    Temp_Arg.Kd = 10;//pid参数调整
				}
			}
            
			else if(Temp.ADDMode==2)//在进入降温模式下
			{ 
				Temp.New = Temp.Rel;//记录当前温度
				if(Temp.New < Temp.Last)//当前温度小于上一次温度
					Temp.Display_Rel = Temp.New;//显示当前温度
				else//当前温度大于上一次温度
				{
					Temp.Display_Rel = Temp.Last;//显示上一次温度，不让温度小于当前温度。呈现攀升速度的现象
					Temp.New = Temp.Last;//将上一次温度赋值给当前温度
				}
				Temp.Last = Temp.New;//将当前温度保存
				if(Temp.Display_Rel <= Temp.Ctrl)//当前的温度小于等于控制温度
				{
					Temp.ADDMode = 3;//进入稳定模式
                    Temp_Val.Integral = 0;//温度控制积分清零
                    Temp_Arg.Kd = 10;//pid参数调整
				}
			}
            
			else if(Temp.ADDMode == 3)//温度稳定模式下
			{
				Temp.Display_Rel = Temp.Ctrl;//显示控制温度
			}
            
		}
		else
		{
			Temp.ADDMode = 0;//进入稳定模式 
			Temp.Display_Rel = Temp.Rel;//显示实际温度
		}
	}
	else
	{
		Temp.Display_Rel = Temp.Rel;//显示实际温度
		Temp.New =0;//现在的速度清零
		Temp.Last = 0;//之前的速度清零
		Temp.ADDMode = 0;//清除显示处理
        T = 0;
	}
}

/*
*****************************************************************
 * 函数原型： void Show_Display(void)
 * 功    能： 显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{
	Temp.Display_Set = Temp.Set;//显示设定温度

	Speed.Display_Set = Speed.Set;//显示设定转速
	
	if(sys.Run_Status)
    {
        if(sys.SetMode_Option == 3)
            Time.Display = Time.Set;//显示设定时间  
        else
            Time.Display = Time.Rel + 59;//显示控制时间
    }
	else			
		Time.Display = Time.Set;//显示设定时间  
        
	Display_Temp(Temp.Display_Set,Temp.Display_Rel);//显示温度
	Display_Speed(Speed.Display_Set,Speed.Display_Rel);//显示转速
	Display_Time(Time.Display);//显示时间
}
