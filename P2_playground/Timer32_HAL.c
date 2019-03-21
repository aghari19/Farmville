/*
 * Timer32_HAL.c
 *
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Farm.h"

#define LOAD_E 24000000
#define LOAD_M 16000000
#define LOAD_H 8000000

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

void InitTimer()
{

    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_0_BASE, 1);
    Timer32_startTimer(TIMER32_0_BASE, true);

    Timer32_initModule(TIMER32_1_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_startTimer(TIMER32_1_BASE, true);
    Timer32_setCount(TIMER32_1_BASE, 1);
}

bool timer0Expired()
{
    return (Timer32_getValue(TIMER32_0_BASE) == 0);
}

void makeToString(farm_t farm, int8_t *string)
{
    string[4] = (farm.DaysPassed % 10) + 48;
    string[3] = ((farm.DaysPassed / 10) % 10) + 48;
    string[1] = (farm.MonthsPassed % 10) + 48;
    string[0] = ((farm.MonthsPassed / 10) % 10) + 48;
}

bool increaseTime(farm_t *farm)
{
    farm->DaysPassed = farm->DaysPassed + 1;
    if (farm->DaysPassed == 30)
    {
        farm->DaysPassed = 0;
        farm->MonthsPassed = farm->MonthsPassed + 1;
        return true;
    }
    return false;
}

