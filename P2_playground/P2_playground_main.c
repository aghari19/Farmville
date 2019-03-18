#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>


#include "graphics_HAL.h"
#include "UART_HAL.h"
#include "Farm.h"
// include all other .h files

void initialize();
void InitTimer();
void startTimer0();

void makeToString(farm_t farm, int8_t *string);
void increaseTime(farm_t farm);

void display(Graphics_Context *g_sContext_p, int8_t *timeString, int8_t *MoneyString, int8_t *HealthString, int8_t *DifficultyString);


int main(void)
{
    Graphics_Context g_sContext;

    initialize();
    InitGraphics(&g_sContext);

    farm_t farm;
    Farm_init(&farm);


    int8_t timeString[6] = "00:00";
    int8_t MoneyString[11] = "Money:  00";
    int8_t HealthString[11] = "Health: 00";
    int8_t DifficultyString[2] = "E";

    display(&g_sContext, timeString, MoneyString, HealthString, DifficultyString);

    eUSCI_UART_Config uartConfig =
       {
            EUSCI_A_UART_CLOCKSOURCE_SMCLK,               // SMCLK Clock Source = 48MHz
            312,                                           // UCBR   = 19
            8,                                            // UCBRF  = 8
            0x00,                                         // UCBRS  = 0xAA
            EUSCI_A_UART_NO_PARITY,                       // No Parity
            EUSCI_A_UART_LSB_FIRST,                       // LSB First
            EUSCI_A_UART_ONE_STOP_BIT,                    // One stop bit
            EUSCI_A_UART_MODE,                            // UART mode
            EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // Oversampling
       };


    InitUART(EUSCI_A0_BASE, &uartConfig, GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3);

    uint8_t rChar, tChar;
    int i=0;

    while (1)
    {
        if (UARTHasChar(EUSCI_A0_BASE))
        {
            rChar = UARTGetChar(EUSCI_A0_BASE);
            i++;
    }

}

void display(Graphics_Context *g_sContext_p, int8_t *timeString,
             int8_t *MoneyString, int8_t *HealthString, int8_t *DifficultyString)
{
    Graphics_Rectangle R;

        R.xMin = 0;
        R.xMax = 127;
        R.yMin = 20;
        R.yMax = 100;

    Graphics_drawRectangle(g_sContext_p, &R);
    Graphics_drawLineV(g_sContext_p, 40, 20, 100);
    Graphics_drawLineV(g_sContext_p, 82, 20, 100);
    Graphics_drawLineH(g_sContext_p, 0, 127, 60);
    Graphics_drawString(g_sContext_p, timeString, -1, 10, 5, true);
    Graphics_drawString(g_sContext_p, DifficultyString, -1, 110, 5, true);
    Graphics_drawString(g_sContext_p, MoneyString, -1, 10, 105, true);
    Graphics_drawString(g_sContext_p, HealthString, -1, 10, 115, true);
}


void makeToString(farm_t farm, int8_t *string)
{
    string[4] = (farm.DaysPassed % 10) + 48;
    string[3] = ((farm.DaysPassed / 10) % 10) + 48;
    string[1] = (farm.MonthsPassed % 10) + 48;
    string[0] = ((farm.MonthsPassed / 10) % 10) + 48;
}

void increaseTime(farm_t farm)
{
    if(farm.Difficulty == 'E')
    {
        farm.DaysPassed = farm.DaysPassed+ 1;
        if(farm.DaysPassed == 15)
        {
            farm.DaysPassed = 0;
            farm.MonthsPassed =farm.MonthsPassed + 1;
        }
    }
    else if(farm.Difficulty == 'M')
    {

    }
    else if(farm.Difficulty == 'H')
    {

    }
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

void startTimer0()
{
    Timer32_setCount(TIMER32_0_BASE, TENTH_SEC_COUNT);
    Timer32_startTimer(TIMER32_0_BASE, true);
}


void initialize()
{
    // stop the watchdog timer
    WDT_A_hold(WDT_A_BASE);

    InitTimer();

    // call your intialization functions
}


