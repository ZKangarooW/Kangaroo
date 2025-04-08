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
    if(EC11A[1].EC11A_Knob > 0)
    {
        SetOK_Flag = 1;//检测到波动旋钮，等待退出设置模式
    }
    if(SetOK_Flag == 1)
    {
        if(sys.SetMode_Option == 0 && Twinkle_Time == 0)//在设定好后
        {     
            
            SetOK_Flag = 0;
        } 
    }
}

