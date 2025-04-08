#include "SysTick.h"

/**
 * @brief 微秒延时函数
 * 
 * @param delay 微秒
 */
void Delay_10us(uint16_t delay)
{
    uint16_t i;
    for(i = 0;i<delay;i++)
    {
        TIM1_WorkModeConfig(TIM1_WORK_MODE2,229);
        TR1 = 1; // 启动定时器0
        EA=0;//关中断(使用查询方式)
		ET1=0;//关T1中断
        while (TF1 == 0);//等待定时器0中断 
        TF1 = 0;//清除定时器0中断标志 
    }
}
