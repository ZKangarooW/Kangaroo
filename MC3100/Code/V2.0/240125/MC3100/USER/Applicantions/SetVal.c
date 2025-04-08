#include "SetVal.h"

/**********全局变量声明******/
uint8_t SetOK_Flag;//检测是否按下按键
uint16_t Rcf_Speed[13] = {1000,1500,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000};

/*
*****************************************************************
 * 函数原型：void Check_Set(float dT)
 * 功    能：检测设置
*****************************************************************
*/
void Check_Set(float dT)
{
    if(Key_Status != 0)//按下加减按键
    {
        SetOK_Flag = 1;//检测到波动旋钮，等待退出设置模式
    }
    if(SetOK_Flag == 1)//检测到按下加减按键后
    {
        if(sys.SetMode_Option == 0)//在设定好后
        {    
			if(Speed.Speed_Mode==0)//速度	
			{
				if(Speed.Ctrl_Speed != Speed.Set_Speed)//判断控制速度和设定速度是不是不一样
				{
					Speed.Ctrl_Speed = Speed.Set_Speed;//把设定速度赋值给控制速度
					Param.Speed = Speed.Set_Speed;//转速
				}
			}	
			else//离心力
			{
				Speed.Ctrl_Speed = Rcf_Speed[Speed.Speed_Rcf];//将离心力对应的转速转换
				Param.Speed_Rcf = Speed.Speed_Rcf;//将离心力的选项保存
			}				
			if(Time.Ctrl_Time != Time.Set_Time)//实际时间不等于设定时间
			{
				Time.Ctrl_Time = Time.Set_Time;//把设定时间赋值给控制时间
				Param.Time = Time.Set_Time;//时间
			}  
            SetOK_Flag = 0;//表示已经设置好了，将设置标志位清零
			Save_Param_En = 1;//保存
        } 
    }
}
