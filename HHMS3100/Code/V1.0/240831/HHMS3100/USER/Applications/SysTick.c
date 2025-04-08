#include "SysTick.h"

#define CPU_FREQUENCY_MHZ	72//STM32ʱ����Ƶ
/**
 * @brief ΢����ʱ����
 * 
 * @param delay ΢��
 */
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

/**
 * @brief forѭ��ʵ�ֺ������ʱ����
 * 
 * @param delay ����
 */
void Delay_ms(uint32_t delay)
{
    uint32_t Delay = delay * 72000 / 9;
    do
    {
        __NOP();
    } while (Delay--);
}
