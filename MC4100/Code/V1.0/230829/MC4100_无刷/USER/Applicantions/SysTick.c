#include "SysTick.h"

/*
*****************************************************************
 * 函数原型：void Delay_us(__IO uint32_t delay)
 * 功    能：微妙延时函数
*****************************************************************
*/
#define CPU_FREQUENCY_MHZ	72//STM32时钟主频
void Delay_us(__IO uint32_t delay)
{
    int last,curr,val;
    int temp;
    while(delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}
