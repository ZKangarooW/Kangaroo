#include "SetVal.h"

/**********全局变量声明******/
uint8_t SetOK_Flag;//检测是否波动旋钮和设置标志位

/*
*****************************************************************
 * 函数原型： void Check_Set(float dT)
 * 功    能： 检测设置 
*****************************************************************
*/
void Check_Set(float dT)
{
    if(EC11A[1].EC11A_Knob > 0)
    {
        SetOK_Flag = 1;//检测到波动旋钮，等待退出设置模式
    }
    if(SetOK_Flag == 1 && Twinkle_Time <= 0)
    {
        if(sys.SetMode_Option == 0 && Twinkle_Time == 0)//在设定好后
        {     
            for(uint8_t i = 0;i<4;i++)
            {
                if(Work_Num[i].Speed.Set != Work_Num[i].Speed.Ctrl)
                {
                    Work_Num[i].Speed.Ctrl = Work_Num[i].Speed.Set;
                    Param.Speed[i] = Work_Num[i].Speed.Set;
                    if(Work_Num[i].Speed.ADDMode != 0)
                        Work_Num[i].Speed.ADDMode = 0;
                }
                if(Work_Num[i].Temp.Set != Work_Num[i].Temp.Ctrl)
                {
                    Work_Num[i].Temp.Ctrl = Work_Num[i].Temp.Set;
                    Param.Temp[i] = Work_Num[i].Temp.Set;
                    if(Work_Num[i].Speed.ADDMode != 0)
                        Work_Num[i].Speed.ADDMode = 0;
                }
                if(Work_Num[i].Time.Set != Work_Num[i].Time.Ctrl)
                {
                    Work_Num[i].Time.Ctrl = Work_Num[i].Time.Set;
                    Work_Num[i].Time.Rel = Work_Num[i].Time.Set;
                    Param.Time[i] = Work_Num[i].Time.Set;
                }
            }
            Save_Param_En = 1;//保存
            SetOK_Flag = 0;
        } 
    }
}

/**
 * @brief 设定任务
 * 
 */
void Setting_Task(void *p)
{ 
    while(1)
    {
        Check_Set(0.1f);
        Param_Save_Overtime(0.1f);
        vTaskDelay(100);
    }
}
