#include "SetVal.h"

/**********全局变量声明******/
uint8_t SetOK_Flag;//检测是否波动旋钮和设置标志位

/*
*****************************************************************
 * 函数原型： void Check_Set(void)
 * 功    能： 检测设置
*****************************************************************
*/
void Check_Set(void)
{
    if(EC11A_Knob != 0)
    {
        SetOK_Flag = 1;//检测到波动旋钮，等待退出设置模式
    }
    if(SetOK_Flag == 1)
    {
        if(SetMode_Option == 0 && Twinkle_Time == 0)//在设定好后
        {     
            Set_Speeds(&Speed,&Set_Speed,&Ctrl_Speed,&Display_Speed,&Speed,&Param.Speed);//比较临时速度，不同就将设置值赋值
			
            Set_Times(&Time,&Set_Time,&Rel_Time,&Ctrl_Time,&Time,&Param.Time);//比较临时时间，不同就将设置值赋值
           
            if(Temp != Set_Temp)//比较临时温度和设定温度不一样
            {
                Ctrl_Temp = Set_Temp;//将设置温度赋值给控制温度
                Temp = Ctrl_Temp;//将设置温度赋值给临时温度
				Param.Temp = Ctrl_Temp;//将设置温度赋值给Flash
				Save_Param_En = 1;
				if(Temp_ADDMode != 0)//在温度状态下
				{
					Temp_ADDMode = 0;//重新判断
					ADD_Wait_Count = 0;	
				}
            }
            Check_Time_State(&SetTime_State,&Set_Time);//判断时间状态
			Check_Time_State(&RelTime_State,&Set_Time);//判断时间状态
			if(Set_Temp > 0)
				Temp_State = 1;
			else
				Temp_State = 0;
            SetOK_Flag = 0;
        } 
    }
}

/*
*****************************************************************
 * 函数原型： void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option)
 * 功    能： 设置数值
 * 输    入:  flag ：0是加 1是减  Work_Option：工位 SetMode_Option：设置模式
 * 参    数： uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option
*****************************************************************
*/
void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option)
{
    if(flag == 0)//加
    {
        switch(Work_Option)//工位
        {
            case 1:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L1 = Set_Speed.L1 + 10;//速度加10
                               Set_Speed.L1 = (Set_Speed.L1 < 50) ? 50 : Set_Speed.L1;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L1 = Set_Speed.L1 + 10;//速度加10
                               Set_Speed.L1 = (Set_Speed.L1 < 50) ? 50 : Set_Speed.L1;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L1 = Set_Time.L1 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L1 = Set_Time.L1 + 600;//时间加十分钟
                               }
                               break;
                   }break;
            case 2:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L2 = Set_Speed.L2 + 10;//速度加10
                                Set_Speed.L2 = (Set_Speed.L2 < 50) ? 50 : Set_Speed.L2;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L2 = Set_Speed.L2 + 10;//速度加10
                                Set_Speed.L2 = (Set_Speed.L2 < 50) ? 50 : Set_Speed.L2;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L2 = Set_Time.L2 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L2 = Set_Time.L2 + 600;//时间加十分钟
                               }
                               break;
                   }break;
            case 3:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L3 = Set_Speed.L3 + 10;//速度加10
                                Set_Speed.L3 = (Set_Speed.L3 < 50) ? 50 : Set_Speed.L3;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L3 = Set_Speed.L3 + 10;//速度加10
                                Set_Speed.L3 = (Set_Speed.L3 < 50) ? 50 : Set_Speed.L3;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L3 = Set_Time.L3 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L3 = Set_Time.L3 + 600;//时间加十分钟
                               }
                               break;
                   }break;
            case 4:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L4 = Set_Speed.L4 + 10;//速度加10
                                Set_Speed.L4 = (Set_Speed.L4 < 50) ? 50 : Set_Speed.L4;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L4 = Set_Speed.L4 + 10;//速度加10
                                Set_Speed.L4 = (Set_Speed.L4 < 50) ? 50 : Set_Speed.L4;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L4 = Set_Time.L4 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L4 = Set_Time.L4 + 600;//时间加十分钟
                               }
                               break;
                   }break;
            case 5:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L5 = Set_Speed.L5 + 10;//速度加10
                                Set_Speed.L5 = (Set_Speed.L5 < 50) ? 50 : Set_Speed.L5;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L5 = Set_Speed.L5 + 10;//速度加10
                                Set_Speed.L5 = (Set_Speed.L5 < 50) ? 50 : Set_Speed.L5;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L5 = Set_Time.L5 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L5 = Set_Time.L5 + 600;//时间加十分钟
                               }
                               break;
                   }break;
            case 6:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L6 = Set_Speed.L6 + 10;//速度加10
                                Set_Speed.L6 = (Set_Speed.L6 < 50) ? 50 : Set_Speed.L6;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L6 = Set_Speed.L6 + 10;//速度加10
                                Set_Speed.L6 = (Set_Speed.L6 < 50) ? 50 : Set_Speed.L6;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L6 = Set_Time.L6 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L6 = Set_Time.L6 + 600;//时间加十分钟
                               }

                               break;
                   }break;
            case 7:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L7 = Set_Speed.L7 + 10;//速度加10
                                Set_Speed.L7 = (Set_Speed.L7 < 50) ? 50 : Set_Speed.L7;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L7 = Set_Speed.L7 + 10;//速度加10
                                Set_Speed.L7 = (Set_Speed.L7 < 50) ? 50 : Set_Speed.L7;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃

                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L7 = Set_Time.L7 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L7 = Set_Time.L7 + 600;//时间加十分钟
                               }
                               break;
                   }break;
            case 8:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L8 = Set_Speed.L8 + 10;//速度加10
                                Set_Speed.L8 = (Set_Speed.L8 < 50) ? 50 : Set_Speed.L8;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L8 = Set_Speed.L8 + 10;//速度加10
                                Set_Speed.L8 = (Set_Speed.L8 < 50) ? 50 : Set_Speed.L8;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L8 = Set_Time.L8 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L8 = Set_Time.L8 + 600;//时间加十分钟
                               }
                               break;
                   }break;
				   
			case 9:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L9 = Set_Speed.L9 + 10;//速度加10
                                Set_Speed.L9 = (Set_Speed.L9 < 50) ? 50 : Set_Speed.L9;//小于50时从50开始加
                               break;
                        case 1:Set_Speed.L9 = Set_Speed.L9 + 10;//速度加10
                                Set_Speed.L9 = (Set_Speed.L9 < 50) ? 50 : Set_Speed.L9;//小于50时从50开始加
                               break;
                        case 2:Set_Temp = Set_Temp + 10;//温度加1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L9 = Set_Time.L9 + 60;//时间加一分钟
                               }
                               else
                               {
                                   Set_Time.L9 = Set_Time.L9 + 600;//时间加十分钟
                               }
                               break;
                   }break;
        }
    }
    if(flag == 1)
    {
        switch(Work_Option)//工位
        {
            case 1:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L1 = Set_Speed.L1 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L1 = Set_Speed.L1 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L1 = Set_Time.L1 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L1 = Set_Time.L1 - 600;//时间减十分钟
                               }
                                break;
                   }break;
            case 2:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L2 = Set_Speed.L2 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L2 = Set_Speed.L2 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L2 = Set_Time.L2 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L2 = Set_Time.L2 - 600;//时间减十分钟
                               }
                                break;
                   }break;
            case 3:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L3 = Set_Speed.L3 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L3 = Set_Speed.L3 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L3 = Set_Time.L3 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L3 = Set_Time.L3 - 600;//时间减十分钟
                               }
                                break;
                   }break;
            case 4:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L4 = Set_Speed.L4 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L4 = Set_Speed.L4 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L4 = Set_Time.L4 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L4 = Set_Time.L4 - 600;//时间减十分钟
                               }
                                break;
                   }break;
            case 5:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L5 = Set_Speed.L5 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L5 = Set_Speed.L5 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L5 = Set_Time.L5 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L5 = Set_Time.L5 - 600;//时间减十分钟
                               }
                                break;
                   }break;
            case 6:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L6 = Set_Speed.L6 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L6 = Set_Speed.L6 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L6 = Set_Time.L6 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L6 = Set_Time.L6 - 600;//时间减十分钟
                               }
                                break;
                   }break;
            case 7:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L7 = Set_Speed.L7 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L7 = Set_Speed.L7 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L7 = Set_Time.L7 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L7 = Set_Time.L7 - 600;//时间减十分钟
                               }
                                break;
                   }break;
            case 8:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L8 = Set_Speed.L8 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L8 = Set_Speed.L8 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L8 = Set_Time.L8 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L8 = Set_Time.L8 - 600;//时间减十分钟
                               }
                                break;
                   }break;		   
			case 9:switch(SetMode_Option)//模式
                   {
                        case 0:Set_Speed.L9 = Set_Speed.L9 - 10;//速度减10
                               break;
                        case 1:Set_Speed.L9 = Set_Speed.L9 - 10;//速度减10
                               break;
                        case 2:Set_Temp = Set_Temp - 10;//温度减1℃
                               break;
                        case 3:if(EC11A[1].EC11A_Speed < EC11A[1].EC11A_Fast)//如果慢慢旋转
                               {
                                   Set_Time.L9 = Set_Time.L9 - 60;//时间减一分钟
                               }
                               else
                               {
                                   Set_Time.L9 = Set_Time.L9 - 600;//时间减十分钟
                               }
                                break;
                   }break;
        }
    }
	Set_Speed.L1 = (Set_Speed.L1 > MAX_Speed) ? MAX_Speed : Set_Speed.L1;//速度不超过1500转
	Set_Speed.L1 = (Set_Speed.L1 < 50) ? 0 : Set_Speed.L1;//速度设置小于50转时清零
	Set_Time.L1 = (Set_Time.L1 > MAX_Time) ? MAX_Time : Set_Time.L1;//时间最多设定23小时59分钟
	Set_Time.L1 = (Set_Time.L1 < 60) ? 0 : Set_Time.L1;//时间小于1分钟不设定
	SetTime_State.L1  = (Set_Time.L1 < 60) ? 0 : 1;//判断是否设置了时间
	
	Set_Speed.L2 = (Set_Speed.L2 > MAX_Speed) ? MAX_Speed : Set_Speed.L2;//速度不超过1500转
	Set_Speed.L2 = (Set_Speed.L2 < 50) ? 0 : Set_Speed.L2;//速度设置小于50转时清零
	Set_Time.L2 = (Set_Time.L2 > MAX_Time) ? MAX_Time : Set_Time.L2;//时间最多设定23小时59分钟
	Set_Time.L2 = (Set_Time.L2 < 60) ? 0 : Set_Time.L2;//时间小于1分钟不设定
	SetTime_State.L2  = (Set_Time.L2 < 60) ? 0 : 1;//判断是否设置了时间
	
	Set_Speed.L3 = (Set_Speed.L3 > MAX_Speed) ? MAX_Speed : Set_Speed.L3;//速度不超过1500转
	Set_Speed.L3 = (Set_Speed.L3 < 50) ? 0 : Set_Speed.L3;//速度设置小于50转时清零
	Set_Time.L3 = (Set_Time.L3 > MAX_Time) ? MAX_Time : Set_Time.L3;//时间最多设定23小时59分钟
	Set_Time.L3 = (Set_Time.L3 < 60) ? 0 : Set_Time.L3;//时间小于1分钟不设定
	SetTime_State.L3  = (Set_Time.L3 < 60) ? 0 : 1;//判断是否设置了时间
	
	Set_Speed.L4 = (Set_Speed.L4 > MAX_Speed) ? MAX_Speed : Set_Speed.L4;//速度不超过1500转
	Set_Speed.L4 = (Set_Speed.L4 < 50) ? 0 : Set_Speed.L4;//速度设置小于50转时清零
	Set_Time.L4 = (Set_Time.L4 > MAX_Time) ? MAX_Time : Set_Time.L4;//时间最多设定23小时59分钟
	Set_Time.L4 = (Set_Time.L4 < 60) ? 0 : Set_Time.L4;//时间小于1分钟不设定
	SetTime_State.L4  = (Set_Time.L4 < 60) ? 0 : 1;//判断是否设置了时间
	
	Set_Speed.L5 = (Set_Speed.L5 > MAX_Speed) ? MAX_Speed : Set_Speed.L5;//速度不超过1500转
	Set_Speed.L5 = (Set_Speed.L5 < 50) ? 0 : Set_Speed.L5;//速度设置小于50转时清零
	Set_Time.L5 = (Set_Time.L5 > MAX_Time) ? MAX_Time : Set_Time.L5;//时间最多设定23小时59分钟
	Set_Time.L5 = (Set_Time.L5 < 60) ? 0 : Set_Time.L5;//时间小于1分钟不设定
	SetTime_State.L5  = (Set_Time.L5 < 60) ? 0 : 1;//判断是否设置了时间
	
	Set_Speed.L6 = (Set_Speed.L6 > MAX_Speed) ? MAX_Speed : Set_Speed.L6;//速度不超过1500转
	Set_Speed.L6 = (Set_Speed.L6 < 50) ? 0 : Set_Speed.L6;//速度设置小于50转时清零
	Set_Time.L6 = (Set_Time.L6 > MAX_Time) ? MAX_Time : Set_Time.L6;//时间最多设定23小时59分钟
	Set_Time.L6 = (Set_Time.L6 < 60) ? 0 : Set_Time.L6;//时间小于1分钟不设定
	SetTime_State.L6  = (Set_Time.L6 < 60) ? 0 : 1;//判断是否设置了时间
	
	Set_Speed.L7 = (Set_Speed.L7 > MAX_Speed) ? MAX_Speed : Set_Speed.L7;//速度不超过1500转
	Set_Speed.L7 = (Set_Speed.L7 < 50) ? 0 : Set_Speed.L7;//速度设置小于50转时清零
	Set_Time.L7 = (Set_Time.L7 > MAX_Time) ? MAX_Time : Set_Time.L7;//时间最多设定23小时59分钟
	Set_Time.L7 = (Set_Time.L7 < 60) ? 0 : Set_Time.L7;//时间小于1分钟不设定
	SetTime_State.L7  = (Set_Time.L7 < 60) ? 0 : 1;//判断是否设置了时间
	
	Set_Speed.L8 = (Set_Speed.L8 > MAX_Speed) ? MAX_Speed : Set_Speed.L8;//速度不超过1500转
	Set_Speed.L8 = (Set_Speed.L8 < 50) ? 0 : Set_Speed.L8;//速度设置小于50转时清零
	Set_Time.L8 = (Set_Time.L8 > MAX_Time) ? MAX_Time : Set_Time.L8;//时间最多设定23小时59分钟
	Set_Time.L8 = (Set_Time.L8 < 60) ? 0 : Set_Time.L8;//时间小于1分钟不设定
	SetTime_State.L8  = (Set_Time.L8 < 60) ? 0 : 1;//判断是否设置了时间
	
	Set_Speed.L9 = (Set_Speed.L9 > MAX_Speed) ? MAX_Speed : Set_Speed.L9;//速度不超过1500转
	Set_Speed.L9 = (Set_Speed.L9 < 50) ? 0 : Set_Speed.L9;//速度设置小于50转时清零
	Set_Time.L9 = (Set_Time.L9 > MAX_Time) ? MAX_Time : Set_Time.L9;//时间最多设定23小时59分钟
	Set_Time.L9 = (Set_Time.L9 < 60) ? 0 : Set_Time.L9;//时间小于1分钟不设定
	SetTime_State.L9  = (Set_Time.L9 < 60) ? 0 : 1;//判断是否设置了时间 
    
    Set_Temp = (Set_Temp > 1200) ? 1200 : Set_Temp;//温度不超过120℃
    Set_Temp = (Set_Temp < 10) ? 0 : Set_Temp;//温度设置小于1℃时清零
    Temp_State = (Set_Temp < 10) ? 0 : 1;//判断是否设置了温度
    
    Twinkle_Time = 2000;//闪烁显示6S  
    EC11A_Knob = 2;//检测是不是在旋动旋钮
    Work_All = 0;//退出同步模式
}

/*
*****************************************************************
 * 函数原型： void SetALL_int(int Val,_Work_Num_ *Work_Num)
 * 功    能： 将结构图中的参数赋值-int型
 * 输    入:  Val 赋予的值  Work_Num：结构体，要用&号连接
 * 参    数： int Val,_Work_Num_ *Work_Num
*****************************************************************
*/
void SetALL_int(int Val,_Work_Num_ *Work_Num)
{
    Work_Num->L1 = Val;
    Work_Num->L2 = Val;
    Work_Num->L3 = Val;
    Work_Num->L4 = Val;
    Work_Num->L5 = Val;
    Work_Num->L6 = Val;
    Work_Num->L7 = Val;
    Work_Num->L8 = Val;
	Work_Num->L9 = Val;
}

/*
*****************************************************************
 * 函数原型： void SetALL_int8(uint8_t Val,_Work_Num_Flag *Work_Num)
 * 功    能： 将结构图中的参数赋值-uint8_t型
 * 输    入:  Val 赋予的值  Work_Num：结构体，要用&号连接
 * 参    数： uint8_t Val,_Work_Num_Flag *Work_Num
*****************************************************************
*/
void SetALL_int8(uint8_t Val,_Work_Num_Flag *Work_Num)
{
    Work_Num->L1 = Val;
    Work_Num->L2 = Val;
    Work_Num->L3 = Val;
    Work_Num->L4 = Val;
    Work_Num->L5 = Val;
    Work_Num->L6 = Val;
    Work_Num->L7 = Val;
    Work_Num->L8 = Val;
	Work_Num->L9 = Val;
}

/*
*****************************************************************
 * 函数原型： void SetALL_int32(uint32_t Val,_Work_Num_long *Work_Num)
 * 功    能： 将结构图中的参数赋值-uint32_t型
 * 输    入:  Val 赋予的值  Work_Num：结构体，要用&号连接
 * 参    数： uint32_t Val,_Work_Num_long *Work_Num
*****************************************************************
*/
void SetALL_int32(uint32_t Val,_Work_Num_long *Work_Num)
{
    Work_Num->L1 = Val;
    Work_Num->L2 = Val;
    Work_Num->L3 = Val;
    Work_Num->L4 = Val;
    Work_Num->L5 = Val;
    Work_Num->L6 = Val;
    Work_Num->L7 = Val;
    Work_Num->L8 = Val;
	Work_Num->L9 = Val;
}

/*
*****************************************************************
 * 函数原型： void SetALL_TimeOver(_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num)
 * 功    能： //将两个结构体变量的参数对应赋值，用于结束时间复原
 * 输    入:  Work_Num1 结构体，要用&号连接  Work_Num：结构体，要用&号连接
 * 参    数： _Work_Num_long *Work_Num1,_Work_Num_long *Work_Num
*****************************************************************
*/
void SetALL_TimeOver(_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num)
{
    Work_Num1->L1 = Work_Num->L1;
    Work_Num1->L2 = Work_Num->L2;
    Work_Num1->L3 = Work_Num->L3;
    Work_Num1->L4 = Work_Num->L4;
    Work_Num1->L5 = Work_Num->L5;
    Work_Num1->L6 = Work_Num->L6;
    Work_Num1->L7 = Work_Num->L7;
    Work_Num1->L8 = Work_Num->L8;
	Work_Num1->L9 = Work_Num->L9;
}

/*
*****************************************************************
 * 函数原型： void SetALL_SpeedOver(_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num)
 * 功    能： 将两个结构体变量的参数对应赋值，用于结束时间速度复原
 * 输    入:  Work_Num1 结构体，要用&号连接  Work_Num：结构体，要用&号连接
 * 参    数： _Work_Num_ *Work_Num1,_Work_Num_ *Work_Num
*****************************************************************
*/
void SetALL_SpeedOver(_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num)
{
    Work_Num1->L1 = Work_Num->L1;
    Work_Num1->L2 = Work_Num->L2;
    Work_Num1->L3 = Work_Num->L3;
    Work_Num1->L4 = Work_Num->L4;
    Work_Num1->L5 = Work_Num->L5;
    Work_Num1->L6 = Work_Num->L6;
    Work_Num1->L7 = Work_Num->L7;
    Work_Num1->L8 = Work_Num->L8;
	Work_Num1->L9 = Work_Num->L9;
}
/*
*****************************************************************
 * 函数原型： void Speed_ALL(uint8_t work,_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1)
 * 功    能： 同步功能，将所有工位的速度同步
 * 输    入:  work 工位号 Work_Num 结构体，要用&号连接  Work_Num1：结构体，要用&号连接
 * 参    数： uint8_t work,_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1
*****************************************************************
*/
void Speed_ALL(uint8_t work,_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1)
{
    switch(work)
    {
        case 1: Work_Num->L1 = Work_Num1->L1;
                Work_Num->L2 = Work_Num1->L1;
                Work_Num->L3 = Work_Num1->L1;
                Work_Num->L4 = Work_Num1->L1;
                Work_Num->L5 = Work_Num1->L1;
                Work_Num->L6 = Work_Num1->L1;
                Work_Num->L7 = Work_Num1->L1;
                Work_Num->L8 = Work_Num1->L1;
				Work_Num->L9 = Work_Num1->L1;
                break;
        case 2:Work_Num->L2 = Work_Num1->L2;
                Work_Num->L1 = Work_Num1->L2;
                Work_Num->L3 = Work_Num1->L2;
                Work_Num->L4 = Work_Num1->L2;
                Work_Num->L5 = Work_Num1->L2;
                Work_Num->L6 = Work_Num1->L2;
                Work_Num->L7 = Work_Num1->L2;
                Work_Num->L8 = Work_Num1->L2;
				Work_Num->L9 = Work_Num1->L2;
                break;
        case 3:Work_Num->L3 = Work_Num1->L3;
                Work_Num->L1 = Work_Num1->L3;
                Work_Num->L2 = Work_Num1->L3;
                Work_Num->L4 = Work_Num1->L3;
                Work_Num->L5 = Work_Num1->L3;
                Work_Num->L6 = Work_Num1->L3;
                Work_Num->L7 = Work_Num1->L3;
                Work_Num->L8 = Work_Num1->L3;
				Work_Num->L9 = Work_Num1->L3;
                break;
        case 4:Work_Num->L4 = Work_Num1->L4;
                Work_Num->L1 = Work_Num1->L4;
                Work_Num->L2 = Work_Num1->L4;
                Work_Num->L3 = Work_Num1->L4;
                Work_Num->L5 = Work_Num1->L4;
                Work_Num->L6 = Work_Num1->L4;
                Work_Num->L7 = Work_Num1->L4;
                Work_Num->L8 = Work_Num1->L4;
				Work_Num->L9 = Work_Num1->L4;
                break;
        case 5:
                Work_Num->L5 = Work_Num1->L5;
                Work_Num->L1 = Work_Num1->L5;
                Work_Num->L2 = Work_Num1->L5;
                Work_Num->L3 = Work_Num1->L5;
                Work_Num->L4 = Work_Num1->L5;
                Work_Num->L6 = Work_Num1->L5;
                Work_Num->L7 = Work_Num1->L5;
                Work_Num->L8 = Work_Num1->L5;
				Work_Num->L9 = Work_Num1->L5;
                break;
        case 6:Work_Num->L6 = Work_Num1->L6;
                Work_Num->L1 = Work_Num1->L6;
                Work_Num->L2 = Work_Num1->L6;
                Work_Num->L3 = Work_Num1->L6;
                Work_Num->L4 = Work_Num1->L6;
                Work_Num->L5 = Work_Num1->L6;
                Work_Num->L7 = Work_Num1->L6;
                Work_Num->L8 = Work_Num1->L6;
				Work_Num->L9 = Work_Num1->L6;
                break;
        case 7:Work_Num->L7 = Work_Num1->L7;
                Work_Num->L1 = Work_Num1->L7;
                Work_Num->L2 = Work_Num1->L7;
                Work_Num->L3 = Work_Num1->L7;
                Work_Num->L4 = Work_Num1->L7;
                Work_Num->L5 = Work_Num1->L7;
                Work_Num->L6 = Work_Num1->L7;
                Work_Num->L8 = Work_Num1->L7;
				Work_Num->L9 = Work_Num1->L7;
                break;
        case 8:Work_Num->L8 = Work_Num1->L8;
                Work_Num->L1 = Work_Num1->L8;
                Work_Num->L2 = Work_Num1->L8;
                Work_Num->L3 = Work_Num1->L8;
                Work_Num->L4 = Work_Num1->L8;
                Work_Num->L5 = Work_Num1->L8;
                Work_Num->L6 = Work_Num1->L8;
                Work_Num->L7 = Work_Num1->L8;
				Work_Num->L9 = Work_Num1->L8;
                break;  
		case 9:Work_Num->L9 = Work_Num1->L9;
                Work_Num->L1 = Work_Num1->L9;
                Work_Num->L2 = Work_Num1->L9;
                Work_Num->L3 = Work_Num1->L9;
                Work_Num->L4 = Work_Num1->L9;
                Work_Num->L5 = Work_Num1->L9;
                Work_Num->L6 = Work_Num1->L9;
                Work_Num->L7 = Work_Num1->L9;
				Work_Num->L8 = Work_Num1->L9;
                break;  
    }
}

/*
*****************************************************************
 * 函数原型： void Time_ALL(uint8_t work,_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1)
 * 功    能： 同步功能，将所有工位的时间同步
 * 输    入:  work 工位号 Work_Num 结构体，要用&号连接  Work_Num1：结构体，要用&号连接
 * 参    数： uint8_t work,_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1
*****************************************************************
*/
void Time_ALL(uint8_t work,_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1)
{
    switch(work)
    {
        case 1: Work_Num->L1 = Work_Num1->L1;
                Work_Num->L2 = Work_Num1->L1;
                Work_Num->L3 = Work_Num1->L1;
                Work_Num->L4 = Work_Num1->L1;
                Work_Num->L5 = Work_Num1->L1;
                Work_Num->L6 = Work_Num1->L1;
                Work_Num->L7 = Work_Num1->L1;
                Work_Num->L8 = Work_Num1->L1;
				Work_Num->L9 = Work_Num1->L1;
                break;
        case 2:Work_Num->L2 = Work_Num1->L2;
                Work_Num->L1 = Work_Num1->L2;
                Work_Num->L3 = Work_Num1->L2;
                Work_Num->L4 = Work_Num1->L2;
                Work_Num->L5 = Work_Num1->L2;
                Work_Num->L6 = Work_Num1->L2;
                Work_Num->L7 = Work_Num1->L2;
                Work_Num->L8 = Work_Num1->L2;
				Work_Num->L9 = Work_Num1->L2;
                break;
        case 3:Work_Num->L3 = Work_Num1->L3;
                Work_Num->L1 = Work_Num1->L3;
                Work_Num->L2 = Work_Num1->L3;
                Work_Num->L4 = Work_Num1->L3;
                Work_Num->L5 = Work_Num1->L3;
                Work_Num->L6 = Work_Num1->L3;
                Work_Num->L7 = Work_Num1->L3;
                Work_Num->L8 = Work_Num1->L3;
				Work_Num->L9 = Work_Num1->L3;
                break;
        case 4:Work_Num->L4 = Work_Num1->L4;
                Work_Num->L1 = Work_Num1->L4;
                Work_Num->L2 = Work_Num1->L4;
                Work_Num->L3 = Work_Num1->L4;
                Work_Num->L5 = Work_Num1->L4;
                Work_Num->L6 = Work_Num1->L4;
                Work_Num->L7 = Work_Num1->L4;
                Work_Num->L8 = Work_Num1->L4;
				Work_Num->L9 = Work_Num1->L4;
                break;
        case 5:
                Work_Num->L5 = Work_Num1->L5;
                Work_Num->L1 = Work_Num1->L5;
                Work_Num->L2 = Work_Num1->L5;
                Work_Num->L3 = Work_Num1->L5;
                Work_Num->L4 = Work_Num1->L5;
                Work_Num->L6 = Work_Num1->L5;
                Work_Num->L7 = Work_Num1->L5;
                Work_Num->L8 = Work_Num1->L5;
				Work_Num->L9 = Work_Num1->L5;
                break;
        case 6:Work_Num->L6 = Work_Num1->L6;
                Work_Num->L1 = Work_Num1->L6;
                Work_Num->L2 = Work_Num1->L6;
                Work_Num->L3 = Work_Num1->L6;
                Work_Num->L4 = Work_Num1->L6;
                Work_Num->L5 = Work_Num1->L6;
                Work_Num->L7 = Work_Num1->L6;
                Work_Num->L8 = Work_Num1->L6;
				Work_Num->L9 = Work_Num1->L6;
                break;
        case 7:Work_Num->L7 = Work_Num1->L7;
                Work_Num->L1 = Work_Num1->L7;
                Work_Num->L2 = Work_Num1->L7;
                Work_Num->L3 = Work_Num1->L7;
                Work_Num->L4 = Work_Num1->L7;
                Work_Num->L5 = Work_Num1->L7;
                Work_Num->L6 = Work_Num1->L7;
                Work_Num->L8 = Work_Num1->L7;
				Work_Num->L9 = Work_Num1->L7;
                break;
        case 8:Work_Num->L8 = Work_Num1->L8;
                Work_Num->L1 = Work_Num1->L8;
                Work_Num->L2 = Work_Num1->L8;
                Work_Num->L3 = Work_Num1->L8;
                Work_Num->L4 = Work_Num1->L8;
                Work_Num->L5 = Work_Num1->L8;
                Work_Num->L6 = Work_Num1->L8;
                Work_Num->L7 = Work_Num1->L8;
				Work_Num->L9 = Work_Num1->L8;
                break;        
		case 9:Work_Num->L9 = Work_Num1->L9;
                Work_Num->L1 = Work_Num1->L9;
                Work_Num->L2 = Work_Num1->L9;
                Work_Num->L3 = Work_Num1->L9;
                Work_Num->L4 = Work_Num1->L9;
                Work_Num->L5 = Work_Num1->L9;
                Work_Num->L6 = Work_Num1->L9;
                Work_Num->L7 = Work_Num1->L9;
				Work_Num->L8 = Work_Num1->L9;
                break;    
    }
}

/*
*****************************************************************
 * 函数原型： void Flag_ALL(uint8_t work,_Work_Num_Flag *Work_Num,_Work_Num_Flag *Work_Num1)
 * 功    能： 同步功能，将所有工位的flag同步
 * 输    入:  work 工位号 Work_Num 结构体，要用&号连接  Work_Num1：结构体，要用&号连接
 * 参    数： uint8_t work,_Work_Num_Flag *Work_Num,_Work_Num_Flag *Work_Num1
*****************************************************************
*/
void Flag_ALL(uint8_t work,_Work_Num_Flag *Work_Num,_Work_Num_Flag *Work_Num1)
{
    switch(work)
    {
        case 1: Work_Num->L1 = Work_Num1->L1;
                Work_Num->L2 = Work_Num1->L1;
                Work_Num->L3 = Work_Num1->L1;
                Work_Num->L4 = Work_Num1->L1;
                Work_Num->L5 = Work_Num1->L1;
                Work_Num->L6 = Work_Num1->L1;
                Work_Num->L7 = Work_Num1->L1;
                Work_Num->L8 = Work_Num1->L1;
				Work_Num->L9 = Work_Num1->L1;
                break;
        case 2:Work_Num->L2 = Work_Num1->L2;
                Work_Num->L1 = Work_Num1->L2;
                Work_Num->L3 = Work_Num1->L2;
                Work_Num->L4 = Work_Num1->L2;
                Work_Num->L5 = Work_Num1->L2;
                Work_Num->L6 = Work_Num1->L2;
                Work_Num->L7 = Work_Num1->L2;
                Work_Num->L8 = Work_Num1->L2;
				Work_Num->L9 = Work_Num1->L2;
                break;
        case 3:Work_Num->L3 = Work_Num1->L3;
                Work_Num->L1 = Work_Num1->L3;
                Work_Num->L2 = Work_Num1->L3;
                Work_Num->L4 = Work_Num1->L3;
                Work_Num->L5 = Work_Num1->L3;
                Work_Num->L6 = Work_Num1->L3;
                Work_Num->L7 = Work_Num1->L3;
                Work_Num->L8 = Work_Num1->L3;
				Work_Num->L9 = Work_Num1->L3;
                break;
        case 4:Work_Num->L4 = Work_Num1->L4;
                Work_Num->L1 = Work_Num1->L4;
                Work_Num->L2 = Work_Num1->L4;
                Work_Num->L3 = Work_Num1->L4;
                Work_Num->L5 = Work_Num1->L4;
                Work_Num->L6 = Work_Num1->L4;
                Work_Num->L7 = Work_Num1->L4;
                Work_Num->L8 = Work_Num1->L4;
				Work_Num->L9 = Work_Num1->L4;
                break;
        case 5:
                Work_Num->L5 = Work_Num1->L5;
                Work_Num->L1 = Work_Num1->L5;
                Work_Num->L2 = Work_Num1->L5;
                Work_Num->L3 = Work_Num1->L5;
                Work_Num->L4 = Work_Num1->L5;
                Work_Num->L6 = Work_Num1->L5;
                Work_Num->L7 = Work_Num1->L5;
                Work_Num->L8 = Work_Num1->L5;
				Work_Num->L9 = Work_Num1->L5;
                break;
        case 6:Work_Num->L6 = Work_Num1->L6;
                Work_Num->L1 = Work_Num1->L6;
                Work_Num->L2 = Work_Num1->L6;
                Work_Num->L3 = Work_Num1->L6;
                Work_Num->L4 = Work_Num1->L6;
                Work_Num->L5 = Work_Num1->L6;
                Work_Num->L7 = Work_Num1->L6;
                Work_Num->L8 = Work_Num1->L6;
				Work_Num->L9 = Work_Num1->L6;
                break;
        case 7:Work_Num->L7 = Work_Num1->L7;
                Work_Num->L1 = Work_Num1->L7;
                Work_Num->L2 = Work_Num1->L7;
                Work_Num->L3 = Work_Num1->L7;
                Work_Num->L4 = Work_Num1->L7;
                Work_Num->L5 = Work_Num1->L7;
                Work_Num->L6 = Work_Num1->L7;
                Work_Num->L8 = Work_Num1->L7;
				Work_Num->L9 = Work_Num1->L7;
                break;
        case 8:Work_Num->L8 = Work_Num1->L8;
                Work_Num->L1 = Work_Num1->L8;
                Work_Num->L2 = Work_Num1->L8;
                Work_Num->L3 = Work_Num1->L8;
                Work_Num->L4 = Work_Num1->L8;
                Work_Num->L5 = Work_Num1->L8;
                Work_Num->L6 = Work_Num1->L8;
                Work_Num->L7 = Work_Num1->L8;
				Work_Num->L9 = Work_Num1->L8;
                break;      
		case 9:Work_Num->L9 = Work_Num1->L9;
                Work_Num->L1 = Work_Num1->L9;
                Work_Num->L2 = Work_Num1->L9;
                Work_Num->L3 = Work_Num1->L9;
                Work_Num->L4 = Work_Num1->L9;
                Work_Num->L5 = Work_Num1->L9;
                Work_Num->L6 = Work_Num1->L9;
                Work_Num->L7 = Work_Num1->L9;
				Work_Num->L9 = Work_Num1->L9;
				Work_Num->L8 = Work_Num1->L9;
                break;   				
    }
}

/*
*****************************************************************
 * 函数原型： void Set_Speeds(_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num2,_Work_Num_ *Work_Num3,_Work_Num_ *Work_Num4,_Work_Num_ *Work_Num5)
 * 功    能： 判断设置速度数值是否改变
 * 输    入:  Work_Num 临时存储的速度，要用&号连接  Work_Num1：设置的速度，要用&号连接 Work_Num2：要赋值的速度，要用&号连接
 * 参    数： _Work_Num_ *Work_Num,_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num2
*****************************************************************
*/
void Set_Speeds(_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num2,_Work_Num_ *Work_Num3,_Work_Num_ *Work_Num4,_Work_Num_ *Work_Num5)
{
   if(Work_Num->L1 != Work_Num1->L1)
   {
       Work_Num2->L1 = Work_Num1->L1;
	   Work_Num3->L1 = Work_Num1->L1;
	   Work_Num4->L1 = Work_Num1->L1;
	   Work_Num5->L1 = Work_Num1->L1;
	   Save_Param_En = 1;
       if(Speed_ADDMode.L1 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
            Speed_ADDMode.L1 = 0;//进入未处理，判断加速还是减速
   }
   if(Work_Num->L2 != Work_Num1->L2)
   {
		Work_Num2->L2 = Work_Num1->L2;
		Work_Num3->L2 = Work_Num1->L2;
		Work_Num4->L2 = Work_Num1->L2;
		Work_Num5->L2 = Work_Num1->L2;
		Save_Param_En = 1;
		if(Speed_ADDMode.L2 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
                Speed_ADDMode.L2 = 0;//进入未处理，判断加速还是减速  
   }
   if(Work_Num->L3 != Work_Num1->L3)
   {
        Work_Num2->L3 = Work_Num1->L3;
	    Work_Num3->L3 = Work_Num1->L3;
	    Work_Num4->L3 = Work_Num1->L3;
	    Work_Num5->L3 = Work_Num1->L3;
		Save_Param_En = 1;
        if(Speed_ADDMode.L3 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
            Speed_ADDMode.L3 = 0;//进入未处理，判断加速还是减速  
   }
   if(Work_Num->L4 != Work_Num1->L4)
   {
		Work_Num2->L4 = Work_Num1->L4; 
		Work_Num3->L4 = Work_Num1->L4; 
		Work_Num4->L4 = Work_Num1->L4; 
		Work_Num5->L4 = Work_Num1->L4; 
		Save_Param_En = 1;
       if(Speed_ADDMode.L4 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
                Speed_ADDMode.L4 = 0;//进入未处理，判断加速还是减速  
   }
   if(Work_Num->L5 != Work_Num1->L5)
   {
		Work_Num2->L5 = Work_Num1->L5;
		Work_Num3->L5 = Work_Num1->L5;
		Work_Num4->L5 = Work_Num1->L5;
		Work_Num5->L5 = Work_Num1->L5;
		Save_Param_En = 1;
       if(Speed_ADDMode.L5 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
                Speed_ADDMode.L5 = 0;//进入未处理，判断加速还是减速  
   }
   if(Work_Num->L6 != Work_Num1->L6)
   {
        Work_Num2->L6 = Work_Num1->L6;
	    Work_Num3->L6 = Work_Num1->L6;
	    Work_Num4->L6 = Work_Num1->L6;
	    Work_Num5->L6 = Work_Num1->L6;
		Save_Param_En = 1;
       if(Speed_ADDMode.L6 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
                Speed_ADDMode.L6 = 0;//进入未处理，判断加速还是减速  
   }
   if(Work_Num->L7 != Work_Num1->L7)
   {
        Work_Num2->L7 = Work_Num1->L7;
		Work_Num3->L7 = Work_Num1->L7;
		Work_Num4->L7 = Work_Num1->L7;
		Work_Num5->L7 = Work_Num1->L7;
		Save_Param_En = 1;
        if(Speed_ADDMode.L7 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
                Speed_ADDMode.L7 = 0;//进入未处理，判断加速还是减速  
   }
   if(Work_Num->L8 != Work_Num1->L8)
   {
       Work_Num2->L8 = Work_Num1->L8;
	   Work_Num3->L8 = Work_Num1->L8;
	   Work_Num4->L8 = Work_Num1->L8;
	   Work_Num5->L8 = Work_Num1->L8;
	   Save_Param_En = 1;
       if(Speed_ADDMode.L8 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
                Speed_ADDMode.L8 = 0;//进入未处理，判断加速还是减速
   }
   if(Work_Num->L9 != Work_Num1->L9)
   {
       Work_Num2->L9 = Work_Num1->L9;
	   Work_Num3->L9 = Work_Num1->L9;
	   Work_Num4->L9 = Work_Num1->L9;
	   Work_Num5->L9 = Work_Num1->L9;
	   Save_Param_En = 1;
       if(Speed_ADDMode.L9 != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
                Speed_ADDMode.L9 = 0;//进入未处理，判断加速还是减速
   }
}

/*
*****************************************************************
 * 函数原型： void Set_Times(_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num2,_Work_Num_long *Work_Num3,_Work_Num_long *Work_Num4,_Work_Num_long *Work_Num5)
 * 功    能： 判断设置时间数值是否改变
 * 输    入:  Work_Num 临时存储的时间，要用&号连接  Work_Num1：设置的时间，要用&号连接 Work_Num2：要赋值的时间，要用&号连接
 * 参    数： _Work_Num_long *Work_Num,_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num2
*****************************************************************
*/
void Set_Times(_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num2,_Work_Num_long *Work_Num3,_Work_Num_long *Work_Num4,_Work_Num_long *Work_Num5)
{
   if(Work_Num->L1 != Work_Num1->L1)
   {
       Work_Num2->L1 = Work_Num1->L1;
	   Work_Num3->L1 = Work_Num1->L1;
	   Work_Num4->L1 = Work_Num1->L1;
	   Work_Num5->L1 = Work_Num1->L1;
	   Save_Param_En = 1;
       RelTime_State.L1 = SetTime_State.L1;//同步时间状态
	   DownTime_Over.L1 = 0;
   }
   if(Work_Num->L2 != Work_Num1->L2)
   {
       Work_Num2->L2 = Work_Num1->L2;
	   Work_Num3->L2 = Work_Num1->L2;
	   Work_Num4->L2 = Work_Num1->L2;
	   Work_Num5->L2 = Work_Num1->L2;
	   Save_Param_En = 1;
       RelTime_State.L2 = SetTime_State.L2;//同步时间状态
	   DownTime_Over.L2 = 0;
   }
   if(Work_Num->L3 != Work_Num1->L3)
   {
       Work_Num2->L3 = Work_Num1->L3;
	   Work_Num3->L3 = Work_Num1->L3;
	   Work_Num4->L3 = Work_Num1->L3;
	   Work_Num5->L3 = Work_Num1->L3;
		Save_Param_En = 1;
        RelTime_State.L3 = SetTime_State.L3;//同步时间状态
	   DownTime_Over.L3 = 0;
   }
   if(Work_Num->L4 != Work_Num1->L4)
   {
       Work_Num2->L4 = Work_Num1->L4; 
	   Work_Num3->L4 = Work_Num1->L4; 
	   Work_Num4->L4 = Work_Num1->L4; 
	   Work_Num5->L4 = Work_Num1->L4;
		Save_Param_En = 1;
       RelTime_State.L4 = SetTime_State.L4;//同步时间状态
	   DownTime_Over.L4 = 0;
   }
   if(Work_Num->L5 != Work_Num1->L5)
   {
       Work_Num2->L5 = Work_Num1->L5;
	   Work_Num3->L5 = Work_Num1->L5;
	   Work_Num4->L5 = Work_Num1->L5;
	   Work_Num5->L5 = Work_Num1->L5;
		Save_Param_En = 1;
       RelTime_State.L5 = SetTime_State.L5;//同步时间状态
	   DownTime_Over.L5 = 0;
   }
   if(Work_Num->L6 != Work_Num1->L6)
   {
       Work_Num2->L6 = Work_Num1->L6;
	   Work_Num3->L6 = Work_Num1->L6;
	   Work_Num4->L6 = Work_Num1->L6;
	   Work_Num5->L6 = Work_Num1->L6;
		Save_Param_En = 1;
       RelTime_State.L6 = SetTime_State.L6;//同步时间状态
	   DownTime_Over.L6 = 0;
   }
   if(Work_Num->L7 != Work_Num1->L7)
   {
       Work_Num2->L7 = Work_Num1->L7;
	   Work_Num3->L7 = Work_Num1->L7;
	   Work_Num4->L7 = Work_Num1->L7;
	   Work_Num5->L7 = Work_Num1->L7;
		Save_Param_En = 1;
       RelTime_State.L7 = SetTime_State.L7;//同步时间状态
	   DownTime_Over.L7 = 0;
   }  
   if(Work_Num->L8 != Work_Num1->L8)
   {
       Work_Num2->L8 = Work_Num1->L8;
	   Work_Num3->L8 = Work_Num1->L8;
	   Work_Num4->L8 = Work_Num1->L8;
	   Work_Num5->L8 = Work_Num1->L8;
		Save_Param_En = 1;
       RelTime_State.L8 = SetTime_State.L8;//同步时间状态
	   DownTime_Over.L8 = 0;
   }
   if(Work_Num->L9 != Work_Num1->L9)
   {
       Work_Num2->L9 = Work_Num1->L9;
	   Work_Num3->L9 = Work_Num1->L9;
	   Work_Num4->L9 = Work_Num1->L9;
	   Work_Num5->L9 = Work_Num1->L9;
		Save_Param_En = 1;
       RelTime_State.L9 = SetTime_State.L9;//同步时间状态
	   DownTime_Over.L9 = 0;
   }
}

/*
*****************************************************************
 * 函数原型：void Check_Time_State(_Work_Num_Flag *Work_Num,_Work_Num_long *Work_Num1);
 * 功    能：判断时间状态
 * 输    入: Work_Num 实际时间状态，要用&号连接  Work_Num1：设置的时间，要用&号连接
 * 参    数：_Work_Num_Flag *Work_Num,_Work_Num_long *Work_Num1
*****************************************************************
*/
void Check_Time_State(_Work_Num_Flag *Work_Num,_Work_Num_long *Work_Num1)
{
	if(Work_Num1->L1 > 0)
		Work_Num->L1 = 1;
	else
		Work_Num->L1 = 0;
	if(Work_Num1->L2 > 0)
		Work_Num->L2 = 1;
	else
		Work_Num->L2 = 0;
	if(Work_Num1->L3 > 0)
		Work_Num->L3 = 1;
	else
		Work_Num->L3 = 0;
	if(Work_Num1->L4 > 0)
		Work_Num->L4 = 1;
	else
		Work_Num->L4 = 0;
	if(Work_Num1->L5 > 0)
		Work_Num->L5 = 1;
	else
		Work_Num->L5 = 0;
	if(Work_Num1->L6 > 0)
		Work_Num->L6 = 1;
	else
		Work_Num->L6 = 0;
	if(Work_Num1->L7 > 0)
		Work_Num->L7 = 1;
	else
		Work_Num->L7 = 0;
	if(Work_Num1->L8 > 0)
		Work_Num->L8 = 1;
	else
		Work_Num->L8 = 0;
	if(Work_Num1->L9 > 0)
		Work_Num->L9 = 1;
	else
		Work_Num->L9 = 0;
}
