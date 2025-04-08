#include "Ctrl_Motor.h"

/*
*****************************************************************
 * 函数原型：void Motor_Ctrl(float dT)
 * 功    能：电机控制
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
	static uint8_t Convert_Set,Ctrl_Val;//pwm的值
    if(sys.Run_Status == 1)//启动
    {
		if((HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)== 1))//盖子闭合时
		{
			if(Speed.Ctrl_Speed && ((Time.DownTime_Over == 0)||(Time.Ctrl_Time)))//速度大于0和定时器没有结束
			{
				switch(Speed.Ctrl_Speed)//分配各个速度的PWM值
				{
					case 1000: Convert_Set = 4;//1018
						break;
					case 1500: Convert_Set = 6;//1510
						break;
					case 2000: Convert_Set = 9;//2014
						break;
					case 2500: Convert_Set = 16;//2500
						break;
					case 3000: Convert_Set = 26;//3010
						break;
					case 3500: Convert_Set = 40;//3514
						break;
					case 4000: Convert_Set = 59;//3984
						break;
					case 4500: Convert_Set = 78;//4498
						break;
					case 5000: Convert_Set = 106;//5010
						break;
					case 5500: Convert_Set = 145;//5507
						break;
					case 6000: Convert_Set = 162;//6010
						break;
					case 6500: Convert_Set = 180;//6477
						break;
					case 7000: Convert_Set = 180;//6477
						break;
					default: Convert_Set=0;//停止
						break;
				}
				if(Ctrl_Val < Convert_Set)//如果控制值小于要达到的值
				{
					Ctrl_Val++;//控制值++
					if(Speed.Speed_Mode==0)//速度	
					{
						Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//计算出各个控制值下的速度
					}
					else//离心力
					{
						Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//计算出各个控制值下的速度
						Speed.Rel_Speed = 11.18*(Speed.Rel_Speed/1000)*(Speed.Rel_Speed/1000)*6;//用速度计算离心力
					}
				}
				PWM = Ctrl_Val;//PWM赋值
			}
			else
			{
				if(Ctrl_Val)
				{
					Ctrl_Val--;
					if(Speed.Speed_Mode==0)//速度	
					{
						Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//计算出各个控制值下的速度
					}
					else//离心力
					{
						Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//计算出各个控制值下的速度
						Speed.Rel_Speed = 11.18*(Speed.Rel_Speed/1000)*(Speed.Rel_Speed/1000)*6;//用速度计算离心力
					}
				}
				else//速度为零时
				{
					sys.Run_Status = 0;//关闭系统
				}
				PWM = Ctrl_Val;//PWM赋值
			}
		}
		else//盖子打开
		{
			sys.Run_Status = 0;//关闭系统
			Speed.Rel_Speed = 0;//不清零显示一直时实际转速
			Ctrl_Val = 0;//控制值清零
			PWM = Ctrl_Val;//PWM赋值
		}
    }
    else//系统关闭
    {
		if(Ctrl_Val)//控制值未清理
		{
			Ctrl_Val--;//控制值--
			if(Speed.Speed_Mode==0)//速度	
			{
				Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//计算出各个控制值下的速度
			}
			else//离心力
			{
				Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//计算出各个控制值下的速度
				Speed.Rel_Speed = 11.18*(Speed.Rel_Speed/1000)*(Speed.Rel_Speed/1000)*6;//用速度计算离心力
			}
		}
		PWM = Ctrl_Val;//PWM赋值
    }      
}
