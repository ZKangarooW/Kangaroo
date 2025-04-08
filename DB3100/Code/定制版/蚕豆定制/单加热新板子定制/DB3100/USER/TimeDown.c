#include "TimeDown.h"

/**********全局变量**********/
uint8_t time_disable;//关闭计时
uint8_t time_Last;//一直计时

/*
*****************************************************************
 * 函数原型： void Sys_Init(void)
 * 功    能： 时间倒计时检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Cheak_TimeDown(uint16_t dT)
{
    static uint16_t T;
    if(ADD_Mode != 2)//系统启动和开始倒计时
        return;  
    if(T == 1000)//1S
    {
        if(time_disable==0)
            return;
        if(rel_time)//实际时间大于0
        {
            rel_time--;//每一秒减一
        }
        else//倒计时结束
        {
            time_disable = 0;//关闭倒计时标志位
            Beep_Flash = 5;
        }    
    } 
    else if(T > 1000)//大于1S后
    {
        T = dT;//因为已经对比++；
    }    
    T += dT;//周期是100ms
}
