/*
 * Timer32_HAL.c
 *
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


void startOneShotTimer0(unsigned int LoadVal)
{
    Timer32_setCount(TIMER32_0_BASE, LoadVal);
    Timer32_startTimer(TIMER32_0_BASE, true);
}

void startOneShotTimer1(unsigned int LoadVal)
{
    Timer32_setCount(TIMER32_1_BASE, LoadVal);
    Timer32_startTimer(TIMER32_1_BASE, true);
}
