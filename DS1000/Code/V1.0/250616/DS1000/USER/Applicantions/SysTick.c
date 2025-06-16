#include "SysTick.h"

#define CPU_FREQUENCY_MHZ	48//时钟主频

/**
 * @brief for循环实现毫秒的延时函数
 * 
 * @param delay 毫秒
 */
void Delay_ms(uint32_t delay)
{
    uint32_t Delay = delay * (CPU_FREQUENCY_MHZ*1000) / 9;
    do
    {
        _nop_();
    } while (Delay--);
}
