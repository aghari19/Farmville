#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "graphics_HAL.h"
#include "UART_HAL.h"
#include "ButtonLED_HAL.h"
#include "Timer32_HAL.h"
#include "Farm.h"
#define LOAD_E 24000000
#define LOAD_M 16000000
#define LOAD_H 8000000
extern Graphics_Image Jon_Bunting8BPP_UNCOMP;
void initialize();
void Commands(uint8_t rChar, Graphics_Rectangle *R, Graphics_Context *g_sContext, farm_t *farm,
              eUSCI_UART_Config *uartConfig, int8_t *timeString,int8_t *MoneyString,int8_t *HealthString,int8_t *DifficultyString);
int main(void)
{
    Graphics_Context g_sContext;
    initialize();
    InitGraphics(&g_sContext);
    farm_t farm;
    Graphics_Rectangle R;
    Farm_init(&farm);
    int8_t timeString[6] = "00:00";
    int8_t MoneyString[11] = "Money:  03";
    int8_t HealthString[11] = "Health: 00";
    int8_t DifficultyString[2] = "E ";
    display(&g_sContext, timeString, MoneyString, HealthString, DifficultyString);
    Plot_init(&R, &g_sContext);
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
    uint8_t rChar;
    bool monthChange;
    bool waiting = 1;
    bool pressed = false;
    int LoadValue = LOAD_E;
    int Health;
    int plotted=0;
    while (waiting)
    {
        if(UARTHasChar(EUSCI_A0_BASE))
        {
            int8_t entered = UARTGetChar(EUSCI_A0_BASE);
            waiting = 0;
        }
    }
    display(&g_sContext, timeString, MoneyString, HealthString,
                        DifficultyString);
    while (1)
    {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
        Graphics_drawRectangle(&g_sContext, &R);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        if(timer0Expired())
        {
            startOneShotTimer0(LoadValue);
            monthChange = increaseTime(&farm);
            makeToString(farm, timeString);
            DrawTime(&g_sContext, timeString);
        }
        else if(UARTHasChar(EUSCI_A0_BASE))
        {
            rChar = UARTGetChar(EUSCI_A0_BASE);
            switch (rChar)
            {
            case 'w':
                        movePlots(&R, rChar, &g_sContext);
                        break;
            case 'a':
                        movePlots(&R, rChar, &g_sContext);
                        break;
            case 's':
                        movePlots(&R, rChar, &g_sContext);
                        break;
            case 'd':
                        movePlots(&R, rChar, &g_sContext);
                        break;
            case 'p':
                        if (isEmpty(&R, &farm) && (farm.Money>0))
                        {
                            plotted = 1;
                            plots(R,&farm,&g_sContext);
                            MoneyString[9] = farm.Money+48;
                            display(&g_sContext, timeString, MoneyString, HealthString,
                                     DifficultyString);
                            Health = (farm.Plots[0].Health+farm.Plots[1].Health+farm.Plots[2].Health+farm.Plots[3].Health+
                                    farm.Plots[4].Health+farm.Plots[5].Health)/update(&farm,false,R,&g_sContext );
                            DrawHealth(&g_sContext, HealthString, Health);
                            pressed = true;
                        }
                        break;
            case 'r':
                        if((pressed == true) | !(isEmpty(&R, &farm)))
                        {
                            changeHydration(&farm,R,rChar,&g_sContext);
                        }
                        break;
            case 't':
                        if((pressed == true) | !(isEmpty(&R, &farm)))
                        {
                            changeHealth(&farm,R,rChar,&g_sContext);
                            Health = (farm.Plots[0].Health+farm.Plots[1].Health+farm.Plots[2].Health+farm.Plots[3].Health+
                                       farm.Plots[4].Health+farm.Plots[5].Health)/update(&farm,false,R,&g_sContext );
                            DrawHealth(&g_sContext, HealthString, Health);
                        }
                        break;
            case 'h':
                        if((pressed == true) | !(isEmpty(&R, &farm)))
                        {
                            Harvest(&farm,&R,&g_sContext);
                        }
                        break;
            case 'l':
                        ChangeDifficulty(&farm, &uartConfig);
                        if(farm.Difficulty == 'M')
                        {
                            LoadValue = LOAD_M;
                            DifficultyString[0] = 'M';
                        }
                        else if (farm.Difficulty == 'H')
                        {
                            LoadValue = LOAD_H;
                            DifficultyString[0] = 'H';
                        }
                        display(&g_sContext, timeString, MoneyString, HealthString,
                                DifficultyString);
                break;
            }
        }
        if((monthChange == true))
        {
            int no_live_plots = update(&farm, monthChange ,R,&g_sContext );
            Health = (farm.Plots[0].Health+farm.Plots[1].Health+farm.Plots[2].Health+farm.Plots[3].Health+
                    farm.Plots[4].Health+farm.Plots[5].Health)/no_live_plots;
            DrawHealth(&g_sContext, HealthString, Health);
            monthChange = false;
        }
        pressed =  false;
        if((plotted == 1) && (Health == 0))
        {
            break;

        }
    }
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawImage(&g_sContext, &Jon_Bunting8BPP_UNCOMP, 0, 0);
    int8_t Over[12] = "!GAME OVER!";
    Graphics_drawString(&g_sContext, Over, -1, 25, 100, false);
}
void initialize()
{
    WDT_A_hold(WDT_A_BASE);
    InitTimer();
}
