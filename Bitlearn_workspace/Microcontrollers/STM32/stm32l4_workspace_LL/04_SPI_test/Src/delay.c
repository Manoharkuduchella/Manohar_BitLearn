#include "delay.h"

void delay_us(uint32_t us)
{
    while (us--)
    {
        for (volatile uint32_t i = 0; i < 4; i++)
        {
            __asm volatile ("nop");
        }
    }
}

void delay_ms(uint32_t ms)
{
    while (ms--)
    {
        delay_us(1000);
    }
}
