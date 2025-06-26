#include "Ctrl_ControlTemp.h"

/**********全局变量声明******/
uint8_t Temp_Control;//温度控制开关
uint8_t Add_Ctrl;//温度补偿值
int Temp_Out;//温度pwm输出值

/*
*****************************************************************
 * 函数原型： void temp_Control(void)
 * 功    能： 温度加热控制
*****************************************************************
*/
void temp_Control(void)
{ 
    if(Run_Status == 1 && Temp_Control == 1 && Temp_State == 1)//启动和设置了温度和温度控制
    { 
        if(Temp >= 460 && Temp < 760)
            Add_Ctrl = 90;
        else if(Temp >= 760 && Temp < 960)
            Add_Ctrl = 140;
        else if(Temp >= 960 && Temp < 1090)
            Add_Ctrl = 160;
        else if(Temp >= 1090 && Temp <= 1200)
            Add_Ctrl = 220;
        PID_Calc(Ture_Temp,Ctrl_Temp+Add_Ctrl);//pid计算
        if(Temp_Val.Out>5 && Temp_Val.Out<18)//当最后加热功率在3到12范围内时
        {
           Temp_Val.Out = 15;//保存最小功率
        }
        Temp_Out = (int)Temp_Val.Out;//pid值赋值
        if(Temp_Out >= 1000) 	Temp_Out = 1000;//pid输出限幅
        else if(Temp_Out <=0)	Temp_Out = 0; 
        HEAT = Temp_Out;//控制加热模块
    }
    else
    {
        Temp_Out = 0;//PWM输出为零
        HEAT = 0;//加热不工作
        Temp_ADDMode = 0;//显示模式为零
    }
}
