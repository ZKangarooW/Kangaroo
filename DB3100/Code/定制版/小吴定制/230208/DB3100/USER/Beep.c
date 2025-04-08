#include "Beep.h"

/**********全局变量**********/
float Beep_Time;//蜂鸣器响的时间

/*
*****************************************************************
 * 函数原型： void Buzzer_Status(float dT)
 * 功    能： 蜂鸣器的状态检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Buzzer_Status(float dT)
{
    if(Beep_Time <= 0)
    { 
        Beep_OFF; 
        return;
    } 
    Beep_ON;
    Beep_Time -= dT;
}
