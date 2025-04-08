#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * 函数原型：void Cheak_TimeDown(uint16_t dT)
 * 功    能：时间倒计时检测
 * 输    入: dT:执行周期
 * 参    数：uint16_t dT
*****************************************************************
*/
void Cheak_TimeDown(uint16_t dT)
{
    static uint16_t T;
	if(sys.Run_Status == 1)
	{
		if(DownTime_Over ==1)//倒计时结束
		{   	
			if(PMode_Status == 2)
			{
				PMode_Option++;
				if(PMode_Option <= PMode_P2)
				{
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
					Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
					sys.DownTime_Status = 0;//关闭
					DownTime_Over = 0;
					sys.SetMode_Option = 0;
					sys.SetP_Mode_Option = 0;
					Temp_ADDMode= 0;
					SetOK_Flag = 1;
					CtrlMode = 1;
				}
				else
				{
					PMode_Option = PMode_P1;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
					Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
					SetOK_Flag = 1;	
					PMode_Mode = 1;//梯度模式
					sys.CtrlTemp_Mode = 0;
					sys.Run_Status = 0;
					Beep_Flash = 5;
				}
			}
			else
			{		
				Ctrl_Time = Time;				
				sys.DownTime_Status = 0;//关闭
				sys.Run_Status = 0;//关闭
				Beep_Flash = 5;
			}
		}
		if(sys.DownTime_Status)//启动倒计时
		{
			T += dT;
			if(T == 1000)//1S
			{
				if(Time_State == 0 && DownTime_Over == 0 && Ctrl_Time)//如果实际时间显示和倒计时没有结束的标志还在
				{
					if(Ctrl_Time)
						Ctrl_Time--;//控制时间--
					if(Ctrl_Time == 0)
					{
						DownTime_Over = 1;//time1倒计时结束
					}
				}
				T = 0;//周期清零
			}    
		}
	}
	else
	{
		DownTime_Over = 0;//将时间标志清零
		sys.DownTime_Status = 0;//关闭
	}
}
