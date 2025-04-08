#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Tab[] = {0xFA,0x0A,0xD6,0x9E,0x2E,0xBC,0xFC,0x1A,0xFE,0xBE};//0·9
uint8_t Temp_ShowFlag,Time_ShowFlag,Pmode_Flag;//温度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag;//加热图标闪烁和时间图标闪烁

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
	if(sys.Run_Status == 1)		
	{
		T += dT;
		if(T >= 0.5f)
		{
            if(Temp.Set)
				TempIcn_ShowFlag = ~TempIcn_ShowFlag;//温度图标闪烁;
			if(Time.Rel)
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//开盖图标闪烁;
			T = 0;
		}
	}
	else
	{
        TempIcn_ShowFlag = 0;//不显示温度图标
		TimeIcn_ShowFlag = 0;//显示时间图标
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
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        Pmode_Flag = 0;//常亮
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
				Time_ShowFlag = 0;//时间常亮
                Pmode_Flag = 0;//常亮
			}
			else if(sys.SetMode_Option == 2)//设置时间
			{
				Temp_ShowFlag = 0;//温度常亮
				Time_ShowFlag = ~Time_ShowFlag;//时间闪烁	
                Pmode_Flag = 0;//常亮                
			}
            else if(sys.SetMode_Option == 3)//设置PMode
			{
				Temp_ShowFlag = 0;//温度常亮
				Time_ShowFlag = 0;//时间闪烁
                Pmode_Flag = ~Pmode_Flag;//常亮                
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
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        Pmode_Flag = 0;//常亮
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
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;
	uint8_t Temp_QU,Temp_BU,Temp_SU,Temp_GU;//实际温度的计算位数取值
	uint8_t Temp_QD,Temp_BD,Temp_SD,Temp_GD;//设定温度的计算位数取值
	uint16_t Val;//用于百十个取出来的数字
	
	/***********设定温度计算**********/
	if(Temp_ShowFlag == 0)
	{
		if(dis_set_temp > 999)//大于999时
		{
			Val=dis_set_temp/1000;//取出千位
			Temp_QD = Tab[Val];
		}
		else
		{
			Temp_QD = 0x00;//不显示
		}
		if(dis_set_temp > 99)//大于99时
		{
			Val=dis_set_temp/100;//取出百位
			if(dis_set_temp > 999)//大于999时
				Val=Val%10;//取出百位
			Temp_BD = Tab[Val];
		}
		else
		{
			Temp_BD = 0x00;//不显示
		}
		if(dis_set_temp > 9)//大于9时
		{
			Val=dis_set_temp/10;//取出十位
			if(dis_set_temp > 99)//大于99时
				Val=Val%10;//取出十位
			Temp_SD = Tab[Val];
		}
		else
		{
			Temp_SD = Tab[0];//不显示0
		}
		Val=dis_set_temp%10;//取出个位
		Temp_GD = Tab[Val];
		seg6 &= 0x7F;seg6 |= 0x80;//设定温度的小数点
	}
	else
	{
		Temp_QD = 0x00;//不显示设定温度
		Temp_BD = 0x00;//不显示设定温度
		Temp_SD = 0x00;//不显示设定温度
		Temp_GD = 0x00;//不显示设定温度
		seg6 &= 0x7F;seg6 |= 0x00;//不显示设定温度的小数点
	}
	
	/***********实际温度计算**********/
	if(dis_rel_temp > 999)//大于999时
	{
		Val=dis_rel_temp/1000;//取出千位
		Temp_QU = Tab[Val];
	}
	else
	{
		Temp_QU = 0x00;//不显示
	}
	if(dis_rel_temp > 99)//大于99时
	{
		Val=dis_rel_temp/100;//取出百位
		if(dis_rel_temp > 999)//大于999时
			Val=Val%10;//取出百位
		Temp_BU = Tab[Val];
	}
	else
	{
		Temp_BU = 0x00;//不显示
	}
	if(dis_rel_temp > 9)//大于9时
	{
		Val=dis_rel_temp/10;//取出十位
		if(dis_rel_temp > 99)//大于99时
			Val=Val%10;//取出十位
		Temp_SU = Tab[Val];
	}
	else
	{
		Temp_SU = Tab[0];//不显示0
	}
	Val=dis_rel_temp%10;//取出个位
	Temp_GU = Tab[Val];
	
	/*************温度小数点的图标*******/
	seg6 &= 0xFE;seg6 |= 0x01;//实际温度的小数点
	
	/****************℃******************/
	seg8 &= 0x7F;seg8 |= 0x80;//℃
	
    /*************加热图标显示***********/ 
    if(sys.Run_Status == 1 && TempIcn_ShowFlag == 0)
    {
        seg9 &= 0xFB;seg9 |= 0x04;
    }
    else
    {
        seg9 &= 0xFB;seg9 |= 0x00;
    }
	
	/*************数据拆分***************/	
	seg1 &= 0xF0;seg1 |= Temp_QU>>4;
	seg2 &= 0xF1;seg2 |= Temp_QU & 0x0E;
	seg1 &= 0x0F;seg1 |= Temp_QD & 0xF0;
	seg2 &= 0x8F;seg2 |= (Temp_QD & 0x0F) << 3;

	seg3 &= 0xF0;seg3 |= Temp_BU>>4;
	seg4 &= 0xF1;seg4 |= Temp_BU & 0x0E;
	seg3 &= 0x0F;seg3 |= Temp_BD & 0xF0;
	seg4 &= 0x8F;seg4 |= (Temp_BD & 0x0F) << 3;
	
	seg5 &= 0xF0;seg5 |= Temp_SU>>4;
	seg6 &= 0xF1;seg6 |= Temp_SU & 0x0E;
	seg5 &= 0x0F;seg5 |= Temp_SD & 0xF0;
	seg6 &= 0x8F;seg6 |= (Temp_SD & 0x0F) << 3;
	
	seg7 &= 0xF0;seg7 |= Temp_GU>>4;
	seg8 &= 0xF1;seg8 |= Temp_GU & 0x0E;
	seg7 &= 0x0F;seg7 |= Temp_GD & 0xF0;
	seg8 &= 0x8F;seg8 |= (Temp_GD & 0x0F) << 3;

	/*************发送数据***************/	
	Write_Addr_Dat_N(0, seg1,1);//SEG27
	Write_Addr_Dat_N(2, seg2,1);//SEG26
	Write_Addr_Dat_N(4, seg3,1);//SEG25
	Write_Addr_Dat_N(6, seg4,1);//SEG24
	Write_Addr_Dat_N(8, seg5,1);//SEG23
	Write_Addr_Dat_N(10, seg6,1);//SEG22
	Write_Addr_Dat_N(12, seg7,1);//SEG21
	Write_Addr_Dat_N(14, seg8,1);//SEG20
    Write_Addr_Dat_N(16, seg9,1);//SEG19
}

/*
*****************************************************************
 * 函数原型：void Display_Time(int32_t dis_set_time,int32_t dis_rel_time)
 * 功    能：显示时间
 * 输    入: dis_set_time 设定转速  dis_rel_time 实际转速
 * 参    数：int32_t dis_set_time,int32_t dis_rel_time
*****************************************************************
*/
void Display_Time(int32_t dis_set_time,int32_t dis_rel_time)
{
	uint8_t seg10,seg11,seg12,seg13,seg14,seg15,seg16,seg17,seg18,seg19;
	seg10=0;seg11=0;seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;seg18=0;seg19=0;
	uint8_t Time_QU,Time_BU,Time_SU,Time_GU;//实际时间的计算位数取值
	uint8_t Time_QD,Time_BD,Time_SD,Time_GD;//设定时间的计算位数取值
    uint8_t SH,H,SM,M;//时间的单位取值
    
    /***********设定时间计算**********/
	if(Time_ShowFlag == 0)
	{
        if(dis_set_time)
        {
            if(Time.Set < 3600)
            {
                SH=dis_set_time%3600/60/10;//计算十位单位的分钟数
                H=dis_set_time%3600/60%10;//计算个位单位的分钟数
                SM=dis_set_time%60/10;//计算十分位单位的秒钟数
                M=dis_set_time%60%10;//计算十分位单位的秒钟数
            }
            else
            {
                SH=dis_set_time/3600/10;//计算十位单位的小时数
                H=dis_set_time/3600%10;//计算个位单位的小时数
                SM=dis_set_time%3600/60/10;//计算十分位单位的分钟数
                M=dis_set_time%3600/60%10;//计算个分位单位的分钟数
            }
            Time_QD = Tab[SH];
            Time_BD = Tab[H];
            Time_SD = Tab[SM];
            Time_GD = Tab[M];
        }
        else
        {
            Time_QD = 0x04;
            Time_BD = 0x04;
            Time_SD = 0x04;
            Time_GD = 0x04;
        }
	}
	else
	{
		Time_QD = 0x00;//不显示设定速度
		Time_BD = 0x00;//不显示设定速度
		Time_SD = 0x00;//不显示设定速度
		Time_GD = 0x00;//不显示设定速度
	}
	
	/***********实际时间计算**********/
    if(dis_rel_time)
    {
        if(Time.Set < 3600)
        {
            SH=dis_rel_time%3600/60/10;//计算十位单位的分钟数
            H=dis_rel_time%3600/60%10;//计算个位单位的分钟数
            SM=dis_rel_time%60/10;//计算十分位单位的秒钟数
            M=dis_rel_time%60%10;//计算十分位单位的秒钟数
        }
        else
        {
            SH=dis_rel_time/3600/10;//计算十位单位的小时数
            H=dis_rel_time/3600%10;//计算个位单位的小时数
            SM=dis_rel_time%3600/60/10;//计算十分位单位的分钟数
            M=dis_rel_time%3600/60%10;//计算个分位单位的分钟数
        }
        Time_QU = Tab[SH];
        Time_BU = Tab[H];
        Time_SU = Tab[SM];
        Time_GU = Tab[M];
    }
    else
    {
        Time_QU = 0x04;
        Time_BU = 0x04;
        Time_SU = 0x04;
        Time_GU = 0x04;
    }
  
	/***************rpm******************/
//	seg15 &= 0x7F;seg15 |= 0x80;//rpm
    if(Time.Set < 3600)
    {
        seg17 &= 0xFE;seg17 |= 0x01;//sec
    }
    else
    {
        seg17 &= 0x7F;seg17 |= 0x80;//min
    }

    /***************时间冒号显示**************/
    seg13 &= 0x7F;seg13 |= 0x80;//底下的时间冒号
    seg13 &= 0xFE;seg13 |= 0x01;//上面的时间冒号
    
    /***************时间图标显示**************/
    if(TimeIcn_ShowFlag == 0)
    {
        seg10 &= 0xF8;seg10 |= 0x07;
        seg11 &= 0xFD;seg11 |= 0x02;
    }
    else
    {
        seg10 &= 0xF8;seg10 |= 0x00;
        seg11 &= 0xFD;seg11 |= 0x00;
    }
    
	/*************数据拆分***************/
	seg19 &= 0xF0;seg19 |= Time_QU>>4;
	seg18 &= 0xF1;seg18 |= Time_QU & 0x0E;
	seg19 &= 0x0F;seg19 |= Time_QD & 0xF0;
	seg18 &= 0x8F;seg18 |= (Time_QD & 0x0F) << 3;

	seg12 &= 0xF0;seg12 |= Time_BU>>4;
	seg13 &= 0xF1;seg13 |= Time_BU & 0x0E;
	seg12 &= 0x0F;seg12 |= Time_BD & 0xF0;
	seg13 &= 0x8F;seg13 |= (Time_BD & 0x0F) << 3;
	
	seg14 &= 0xF0;seg14 |= Time_SU>>4;
	seg15 &= 0xF1;seg15 |= Time_SU & 0x0E;
	seg14 &= 0x0F;seg14 |= Time_SD & 0xF0;
	seg15 &= 0x8F;seg15 |= (Time_SD & 0x0F) << 3;
	
	seg16 &= 0xF0;seg16 |= Time_GU>>4;
	seg17 &= 0xF1;seg17 |= Time_GU & 0x0E;
	seg16 &= 0x0F;seg16 |= Time_GD & 0xF0;
	seg17 &= 0x8F;seg17 |= (Time_GD & 0x0F) << 3;	
	
	/*************发送数据***************/	
    Write_Addr_Dat_N(18, seg10,1);//SEG18
	Write_Addr_Dat_N(20, seg11,1);//SEG17
	Write_Addr_Dat_N(22, seg12,1);//SEG16
	Write_Addr_Dat_N(24, seg13,1);//SEG15
	Write_Addr_Dat_N(26, seg14,1);//SEG14
	Write_Addr_Dat_N(28, seg15,1);//SEG13
	Write_Addr_Dat_N(30, seg16,1);//SEG12
	Write_Addr_Dat_N(32, seg17,1);//SEG11
	Write_Addr_Dat_N(34, seg18,1);//SEG10
	Write_Addr_Dat_N(36, seg19,1);//SEG9	
}

/*
*****************************************************************
 * 函数原型：void Display_Pmode(uint8_t dis_option)
 * 功    能：显示P模式
 * 输    入: dis_option：当前的记忆模式
 * 参    数：uint8_t dis_option
*****************************************************************
*/
void Display_Pmode(uint8_t dis_option)
{
	uint8_t seg20,seg21,seg22,seg23,seg24,seg25,seg26,seg27;
	seg20=0;seg21=0;seg22=0;seg23=0;seg24=0;seg25=0;seg26=0;seg27=0;
	uint8_t Val;//计算位数取值
    
    if(PMode.Show_Circle)
    {
        
        /**********P模式外框**********/
        seg20 &= 0x87;seg20 |= 0x78;
        seg21 &= 0x7F;seg21 |= 0x80;
        seg23 &= 0x7F;seg23 |= 0x80;
        seg24 &= 0xF7;seg24 |= 0x08;
        seg25 &= 0x7F;seg25 |= 0x80;
        seg27 &= 0x0F;seg27 |= 0xF0;
        
        if(Pmode_Flag == 0)
        {
            seg23 &= 0xDF;seg23 |= 0x20;//"-"
            
            seg25 &= 0xCF;seg25 |= 0x30;//"P"
            seg26 &= 0x8F;seg26 |= 0x70;
            
            Val = Tab[dis_option];
            seg22 &= 0x0F;seg22 |= Val & 0xF0;
            seg21 &= 0x8F;seg21 |= (Val & 0x0F) << 3;
        }
        else
        {
            seg23 &= 0xDF;seg23 |= 0x00;//"-"
            
            seg25 &= 0xCF;seg25 |= 0x00;//"P"
            seg26 &= 0x8F;seg26 |= 0x00;
            
            Val = Tab[dis_option];
            seg22 &= 0x0F;seg22 |= Val & 0x00;
            seg21 &= 0x8F;seg21 |= (Val & 0x00) << 3;
        }
    }
    else
    {
        /**********P模式外框**********/
        seg20 &= 0x87;seg20 |= 0x00;
        seg21 &= 0x7F;seg21 |= 0x00;
        seg23 &= 0x7F;seg23 |= 0x00;
        seg24 &= 0xF7;seg24 |= 0x00;
        seg25 &= 0x7F;seg25 |= 0x00;
        seg27 &= 0x0F;seg27 |= 0x00;
        
        
        seg23 &= 0xDF;seg23 |= 0x00;//"-"
        
        seg25 &= 0xCF;seg25 |= 0x00;//"P"
        seg26 &= 0x8F;seg26 |= 0x00;
        
        Val = 0x00;
        seg22 &= 0x0F;seg22 |= Val & 0xF0;
        seg21 &= 0x8F;seg21 |= (Val & 0x0F) << 3;
    }
	/*************发送数据***************/	
    Write_Addr_Dat_N(38, seg20,1);//SEG20
	Write_Addr_Dat_N(40, seg21,1);//SEG21
	Write_Addr_Dat_N(42, seg22,1);//SEG22
	Write_Addr_Dat_N(44, seg23,1);//SEG23
	Write_Addr_Dat_N(46, seg24,1);//SEG24
	Write_Addr_Dat_N(48, seg25,1);//SEG25
	Write_Addr_Dat_N(50, seg26,1);//SEG26
	Write_Addr_Dat_N(52, seg27,1);//SEG27	
}

/*
*****************************************************************
 * 函数原型：void ADD_Show(float dT)
 * 功    能：显示上升时间
 * 输    入：dT:执行周期
 * 参    数：float dT
*****************************************************************
*/
void ADD_Show(float dT)
{
    static float T;
    if(Temp.ADD_Wait_Count)//加入慢速上升标志位大于一并且升温状态在慢速上升时
    {
        T += dT;
        if(T >= 1.0f)//1S
        {
            Temp.ADD_Wait_Count--;//慢速上声标志位--
            if(Temp.ADD_Wait_Count == 0)//慢速上升标志位等于0时
                Temp.ADDMode = 3;//进入稳定温度模式
            T = 0;
        }
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
	
    if(sys.Run_Status == 0)//没启动的情况下
    {
		Temp.ADDMode = 0;
		Temp.Display_Rel = Temp.Rel;
    }
    else if(sys.Run_Status == 1)//启动的情况下
    {
        if(Temp.ADDMode == 0)//判断数据处理显示
        {     
		   if(Temp.Ctrl > Temp.Display_Rel)//设定温度大于显示温度
		   { 
				Temp.ADDMode = 1;//进入加热模式下
				Temp.New = 0;//将之前的记入值清零
			}
		   else
		   {
				Temp.ADDMode = 2;//进入降温模式下
				Temp.New = 0;//将之前的记入值清零 
			}
        }
        if(Temp.ADDMode == 1)//在加热模式下
        {
            if(Temp.Rel > Temp.Display_Rel && Temp.Display_Rel <= Temp.Ctrl)
			{
                Temp.Display_Rel ++;
				T = 0;
			}
			if(Temp.Display_Rel >= Temp.Set - 20)//实际温度大于等于设定温度-2℃
            {
                Temp.ADD_Wait_Count = ((Temp.Set-Temp.Display_Rel)*10);//200S的缓慢升温显示  
				Temp.ADDMode = 3;
				return;
            }
        }
		else if(Temp.ADDMode == 2)//降温模式下
        {
            if(Temp.Rel < Temp.Display_Rel && Temp.Display_Rel >= Temp.Ctrl)//当前温度小于上一次温度
			{
                Temp.Display_Rel--;//显示当前温度
				T = 0;
			}
			if(Temp.Display_Rel <= Temp.Set + 20)//实际温度小于等于设定温度-2℃
            {
                Temp.ADD_Wait_Count = (-(Temp.Set-Temp.Display_Rel)*10);//200S的缓慢升温显示 
				Temp_Val.Integral = 0;//积分清零
				Temp.ADDMode = 3;
				return;
            }
        }  	
		else if(Temp.ADDMode == 3)//等待降温后开始升温
        {
			if(Temp.Display_Rel < Temp.Set)
				Temp.Display_Rel=(Temp.Set-20)+(20-(Temp.ADD_Wait_Count)*2/20);//缓慢显示数值
			else if(Temp.Display_Rel > Temp.Set)
				Temp.Display_Rel=(Temp.Set+20)-(20-(Temp.ADD_Wait_Count)*2/20);//缓慢显示数值
			else
				Temp.ADDMode = 4;
        }  
        else if(Temp.ADDMode == 4)//温度稳定模式下
        {
			Temp.Display_Rel = Temp.Ctrl;//显示当前显示温度
        }   	
    }
	else if(sys.Run_Status == 2)//关闭的情况下
	{
		if(Temp.Display_Rel < Temp.Rel)
		{
			T += dT;
			if(T >= 10.0f)
			{
				Temp.Display_Rel -= 1;
				if(Temp.Display_Rel< 370)
					sys.Run_Status = 0;
				T = 0;
			}
		}
		else
		{
			T = 0;
			sys.Run_Status = 0;
		}
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

    Time.Display_Rel = Time.Rel;//显示控制时间		
    Time.Display_Set = Time.Set;//显示设定时间  
    
    Display_Pmode(PMode.Option);
    
	if(Temp.Display_Rel >= 1000)
		Temp.Display_Rel = 1000;
	
	Display_Temp(Temp.Display_Set,Temp.Display_Rel);//显示温度
    Display_Time(Time.Display_Set,Time.Display_Rel);//显示时间
}
