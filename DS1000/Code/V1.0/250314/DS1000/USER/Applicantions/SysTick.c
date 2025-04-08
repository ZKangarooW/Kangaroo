#include "SysTick.h"

#define CPU_FREQUENCY_MHZ	48//ʱ����Ƶ

/**
 * @brief forѭ��ʵ�ֺ������ʱ����
 * 
 * @param delay ����
 */
void Delay_ms(uint32_t delay)
{
    uint32_t Delay = delay * (CPU_FREQUENCY_MHZ*1000) / 9;
    do
    {
        _nop_();
    } while (Delay--);
}
