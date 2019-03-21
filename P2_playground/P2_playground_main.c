#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>


#include "graphics_HAL.h"
#include "UART_HAL.h"
#include "Farm.h"
#include "ButtonLED_HAL.h"
#include "Timer32_HAL.h"

// include all other .h files

#define LOAD_E 24000000
#define LOAD_M 16000000
#define LOAD_H 8000000


void initialize();
void InitTimer();
bool timer0Expired();
void startTimerE();
void startTimerM();
void startTimerH();

void makeToString(farm_t farm, int8_t *string);
bool increaseTime(farm_t *farm);

void ChangeDifficulty(farm_t *farm, eUSCI_UART_Config *uartConfig_p);

void display(Graphics_Context *g_sContext_p, int8_t *timeString, int8_t *MoneyString, int8_t *HealthString, int8_t *DifficultyString);
void movePlots(Graphics_Rectangle *R, uint8_t rChar , Graphics_Context *g_sContext_p);
void Plot_init(Graphics_Rectangle *R, Graphics_Context *g_sContext_p);

void plots(Graphics_Rectangle R, farm_t *farm, Graphics_Context *g_sContext_p);
bool isEmpty(Graphics_Rectangle *R, farm_t *farm);

void Commands(uint8_t rChar, Graphics_Rectangle *R, Graphics_Context *g_sContext, farm_t *farm,
              eUSCI_UART_Config *uartConfig, int8_t *timeString,int8_t *MoneyString,int8_t *HealthString,int8_t *DifficultyString);

void Draw_PlotStatus(Graphics_Rectangle *R, farm_t *farm, Graphics_Context *g_sContext_p);

void changeHydration(farm_t *farm,Graphics_Rectangle R,uint8_t entered, Graphics_Context *g_sContext_p);
void changeHealth(farm_t *farm,Graphics_Rectangle R,uint8_t entered,Graphics_Context *g_sContext_p );
void changeStatus(farm_t *farm,Graphics_Context *g_sContext_p );

void checkStatus(farm_t *farm,Graphics_Context *g_sContext_p);
void growing(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R );

void update(farm_t *farm, bool Change, Graphics_Rectangle R,Graphics_Context *g_sContext_p );


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

    while (waiting)
    {
        if(UARTHasChar(EUSCI_A0_BASE))
        {
            waiting = 0;
        }
    }

    while (1)
    {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
        Graphics_drawRectangle(&g_sContext, &R);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        if(timer0Expired())
        {
            startOneShotTimer0(LOAD_E);
            monthChange = increaseTime(&farm);
            makeToString(farm, timeString);
            display(&g_sContext, timeString, MoneyString, HealthString,
                    DifficultyString);
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
                            plots(R,&farm,&g_sContext);
                            MoneyString[9] = farm.Money+48;
                            display(&g_sContext, timeString, MoneyString, HealthString,
                                     DifficultyString);
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
                        }
                        break;
            case 'l':
                        ChangeDifficulty(&farm, &uartConfig);
                        if(farm.Difficulty == 'M')
                        {
                            DifficultyString[0] = 'M';
                        }
                        else if (farm.Difficulty == 'H')
                        {
                            DifficultyString[0] = 'H';
                        }
                        display(&g_sContext, timeString, MoneyString, HealthString,
                                DifficultyString);
                break;
            }
            //Commands(rChar, &R, &g_sContext, &farm, &uartConfig,
                     //timeString, MoneyString, HealthString, DifficultyString);
        }
        if((monthChange == true))
        {
            update(&farm, monthChange ,R,&g_sContext );

            monthChange = false;
        }
        pressed =  false;
    }
}

void update(farm_t *farm, bool Change, Graphics_Rectangle R,Graphics_Context *g_sContext_p )
{
    if(Change == true)
    {
        changeStatus(farm,g_sContext_p);
    }
    checkStatus(farm,g_sContext_p);
}

void growing(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R )
{
    if((R.xMax == 40) && (R.yMax == 60))//The first Plot in the array it is the second plot
        {
            Graphics_fillCircle(g_sContext_p, 10, 30, 2);
            Graphics_drawLineV(g_sContext_p, 10, 26, 34);

            Graphics_fillCircle(g_sContext_p, 20, 30, 2);
            Graphics_drawLineV(g_sContext_p, 20, 26, 34);

            Graphics_fillCircle(g_sContext_p, 30, 30, 2);
            Graphics_drawLineV(g_sContext_p, 30, 26, 34);

            Graphics_fillCircle(g_sContext_p, 10, 40, 2);
            Graphics_drawLineV(g_sContext_p, 10, 36, 44);

            Graphics_fillCircle(g_sContext_p, 20, 40, 2);
            Graphics_drawLineV(g_sContext_p, 20, 36, 44);

            Graphics_fillCircle(g_sContext_p, 30, 40, 2);
            Graphics_drawLineV(g_sContext_p, 30, 36, 44);

        }
        else if ((R.xMax == 80) && (R.yMax == 60))
        {
            turnOn_LaunchpadLED2_green();

            Graphics_fillCircle(g_sContext_p, 50, 30, 2);
            Graphics_drawLineV(g_sContext_p, 50, 26, 34);

            Graphics_fillCircle(g_sContext_p, 60, 30, 2);
            Graphics_drawLineV(g_sContext_p, 60, 26, 34);

            Graphics_fillCircle(g_sContext_p, 70, 30, 2);
            Graphics_drawLineV(g_sContext_p, 70, 26, 34);

            Graphics_fillCircle(g_sContext_p, 50, 40, 2);
            Graphics_drawLineV(g_sContext_p, 50, 36, 44);

            Graphics_fillCircle(g_sContext_p, 60, 40, 2);
            Graphics_drawLineV(g_sContext_p, 60, 36, 44);

            Graphics_fillCircle(g_sContext_p, 70, 40, 2);
            Graphics_drawLineV(g_sContext_p, 70, 36, 44);

        }
        else if ((R.xMax == 120) && (R.yMax == 60))
        {
            Graphics_fillCircle(g_sContext_p, 90, 30, 2);
            Graphics_drawLineV(g_sContext_p, 90, 26, 34);


            Graphics_fillCircle(g_sContext_p, 100, 30, 2);
            Graphics_drawLineV(g_sContext_p, 100, 26, 34);


            Graphics_fillCircle(g_sContext_p, 110, 30, 2);
            Graphics_drawLineV(g_sContext_p, 110, 26, 34);


            Graphics_fillCircle(g_sContext_p, 90, 40, 2);
            Graphics_drawLineV(g_sContext_p, 90, 36, 44);


            Graphics_fillCircle(g_sContext_p, 100, 40, 2);
            Graphics_drawLineV(g_sContext_p, 100, 36, 44);


            Graphics_fillCircle(g_sContext_p, 110, 40, 2);
            Graphics_drawLineV(g_sContext_p, 70, 36, 44);


        }
        else if ((R.xMax == 40) && (R.yMax == 100))
        {
            Graphics_fillCircle(g_sContext_p, 10, 70, 2);
            Graphics_drawLineV(g_sContext_p, 10, 66, 74);

            Graphics_fillCircle(g_sContext_p, 20, 70, 2);
            Graphics_drawLineV(g_sContext_p, 20, 66, 74);

            Graphics_fillCircle(g_sContext_p, 30, 70, 2);
            Graphics_drawLineV(g_sContext_p, 30, 66, 74);

            Graphics_fillCircle(g_sContext_p, 10, 80, 2);
            Graphics_drawLineV(g_sContext_p, 10, 76, 84);

            Graphics_fillCircle(g_sContext_p, 20, 80, 2);
            Graphics_drawLineV(g_sContext_p, 20, 76, 84);

            Graphics_fillCircle(g_sContext_p, 30, 80, 2);
            Graphics_drawLineV(g_sContext_p, 30, 76, 84);


        }
        else if ((R.xMax == 80) && (R.yMax == 100))
        {
            Graphics_fillCircle(g_sContext_p, 50, 70, 2);
            Graphics_drawLineV(g_sContext_p, 50, 66, 74);

            Graphics_fillCircle(g_sContext_p, 60, 70, 2);
            Graphics_drawLineV(g_sContext_p, 60, 66, 74);

            Graphics_fillCircle(g_sContext_p, 70, 70, 2);
            Graphics_drawLineV(g_sContext_p, 70, 66, 74);

            Graphics_fillCircle(g_sContext_p, 50, 80, 2);
            Graphics_drawLineV(g_sContext_p, 50, 76, 84);

            Graphics_fillCircle(g_sContext_p, 60, 80, 2);
            Graphics_drawLineV(g_sContext_p, 60, 76, 84);

            Graphics_fillCircle(g_sContext_p, 70, 80, 2);
            Graphics_drawLineV(g_sContext_p, 70, 76, 84);

        }
        else if ((R.xMax == 120) && (R.yMax == 100))
        {
            Graphics_fillCircle(g_sContext_p, 90, 70, 2);
            Graphics_drawLineV(g_sContext_p, 90, 66, 74);

            Graphics_fillCircle(g_sContext_p, 100, 70, 2);
            Graphics_drawLineV(g_sContext_p, 100, 66, 74);

            Graphics_fillCircle(g_sContext_p, 110, 70, 2);
            Graphics_drawLineV(g_sContext_p, 110, 66, 74);

            Graphics_fillCircle(g_sContext_p, 90, 80, 2);
            Graphics_drawLineV(g_sContext_p, 90, 76, 84);

            Graphics_fillCircle(g_sContext_p, 100, 80, 2);
            Graphics_drawLineV(g_sContext_p, 100, 76, 84);

            Graphics_fillCircle(g_sContext_p, 110, 80, 2);
            Graphics_drawLineV(g_sContext_p, 110, 76, 84);

        }
}
void checkStatus(farm_t *farm,Graphics_Context *g_sContext_p)
{
    Graphics_Rectangle R;
       R.xMax = 40;
       R.xMin = 0;
       R.yMax = 60;
       R.yMin = 20;
       if(!isEmpty(&R, farm))
       {
            if((farm->Plots[0].Age > 2) && (farm->Plots[0].Age < 9) &&
                    (farm->Plots[0].Health > 0) && (farm->Plots[0].Hydration > 3))
            {
                turnOn_BoosterpackLED_green();
                growing(farm,g_sContext_p, R);
            }
       }
       R.xMax = 80;
       R.yMax = 60;
       if(!isEmpty(&R, farm))
       {
           if((farm->Plots[1].Age > 2) && (farm->Plots[1].Age < 9) &&
                   (farm->Plots[1].Health > 0) && (farm->Plots[1].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
       }
       R.xMax = 120;
       R.yMax = 60;
       if(!isEmpty(&R, farm))
       {
           if((farm->Plots[2].Age > 2) && (farm->Plots[2].Age < 9) &&
                   (farm->Plots[2].Health > 0) && (farm->Plots[2].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
       }
       R.xMax = 40;
       R.yMax = 100;
       if(!isEmpty(&R, farm))
       {
           if((farm->Plots[3].Age > 2) && (farm->Plots[3].Age < 9) &&
                   (farm->Plots[3].Health > 0) && (farm->Plots[3].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
       }
       R.xMax = 80;
       R.yMax = 100;
       if(!isEmpty(&R, farm))
       {
           if((farm->Plots[4].Age > 2) && (farm->Plots[4].Age < 9) &&
                   (farm->Plots[4].Health > 0) && (farm->Plots[4].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
       }
       R.xMax = 120;
       R.yMax = 100;
       if(!isEmpty(&R, farm))
       {
           if((farm->Plots[5].Age > 2) && (farm->Plots[5].Age < 9) &&
                   (farm->Plots[5].Health > 0) && (farm->Plots[5].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
       }
}

void changeStatus(farm_t *farm,Graphics_Context *g_sContext_p )
{
    Graphics_Rectangle R;
    R.xMax = 40;
    R.xMin = 0;
    R.yMax = 60;
    R.yMin = 20;
    if(!isEmpty(&R, farm))
    {
        if(farm->Plots[0].Health != 0)
            farm->Plots[0].Health--;
        if(farm->Plots[0].Hydration != 0)
            farm->Plots[0].Hydration--;
        if(farm->Plots[0].Age != 9)
            farm->Plots[0].Age++;

        int8_t Health[2];
        Health[0] = farm->Plots[0].Health + 48;
        Health[1] = '\0';

        int8_t hydration[1];
        hydration[0] = farm->Plots[0].Hydration + 48;

        int8_t Age[1];
        Age[0] = farm->Plots[0].Age + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,2, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,16, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p,Age , -1,30, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    R.xMax = 80;
    R.yMax = 60;
    if(!isEmpty(&R, farm))
    {
        if(farm->Plots[1].Health != 0)
            farm->Plots[1].Health--;
        if(farm->Plots[1].Hydration != 1)
            farm->Plots[1].Hydration--;
        if(farm->Plots[1].Age != 9)
            farm->Plots[1].Age++;

        int8_t Health[2];
        Health[0] = farm->Plots[1].Health + 48;
        Health[1] = '\0';


        int8_t hydration[1];
        hydration[0] = farm->Plots[1].Hydration + 48;

        int8_t Age[1];
        Age[0] = farm->Plots[1].Age + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,41, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,55, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p,Age , -1,70, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    R.xMax = 120;
    R.yMax = 60;
    if(!isEmpty(&R, farm))
    {
        if(farm->Plots[2].Health != 0)
            farm->Plots[2].Health--;
        if(farm->Plots[2].Hydration != 1)
            farm->Plots[2].Hydration--;
        if(farm->Plots[2].Age != 9)
            farm->Plots[2].Age++;

        int8_t Health[2];
        Health[0] = farm->Plots[2].Health + 48;
        Health[1] = '\0';


        int8_t hydration[1];
        hydration[0] = farm->Plots[2].Hydration + 48;

        int8_t Age[1];
        Age[0] = farm->Plots[2].Age + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,81, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,95, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p,Age , -1,105, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    R.xMax = 40;
    R.yMax = 100;
    if(!isEmpty(&R, farm))
    {
        if(farm->Plots[3].Health != 0)
            farm->Plots[3].Health--;
        if(farm->Plots[3].Hydration != 1)
            farm->Plots[3].Hydration--;
        if(farm->Plots[3].Age != 9)
            farm->Plots[3].Age++;

        int8_t Health[2];
        Health[0] = farm->Plots[3].Health + 48;
        Health[1] = '\0';


        int8_t hydration[1];
        hydration[0] = farm->Plots[3].Hydration + 48;

        int8_t Age[1];
        Age[0] = farm->Plots[3].Age + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,2, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,16, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p,Age , -1,30, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    R.xMax = 80;
    R.yMax = 100;
    if(!isEmpty(&R, farm))
    {
        if(farm->Plots[4].Health != 0)
            farm->Plots[4].Health--;
        if(farm->Plots[4].Hydration != 1)
            farm->Plots[4].Hydration--;
        if(farm->Plots[4].Age != 9)
            farm->Plots[4].Age++;

        int8_t Health[2];
        Health[0] = farm->Plots[4].Health + 48;
        Health[1] = '\0';


        int8_t hydration[1];
        hydration[0] = farm->Plots[4].Hydration + 48;

        int8_t Age[1];
        Age[0] = farm->Plots[4].Age + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,41, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,55, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p,Age , -1,70, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    R.xMax = 120;
    R.yMax = 100;
    if(!isEmpty(&R, farm))
    {
        if(farm->Plots[5].Health != 0)
            farm->Plots[5].Health--;
        if(farm->Plots[5].Hydration != 1)
            farm->Plots[5].Hydration--;
        if(farm->Plots[5].Age != 9)
            farm->Plots[5].Age++;

        int8_t Health[2];
        Health[0] = farm->Plots[5].Health + 48;
        Health[1] = '\0';


        int8_t hydration[1];
        hydration[0] = farm->Plots[5].Hydration + 48;

        int8_t Age[1];
        Age[0] = farm->Plots[5].Age + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,81, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,95, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p,Age , -1,105, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

    }
}
void changeHealth(farm_t *farm,Graphics_Rectangle R,uint8_t entered,Graphics_Context *g_sContext_p )
{
    if((R.xMax == 40) && (R.yMax == 60))
    {
        if(entered == 't')
        {
            if(farm->Plots[0].Health != 5)
                farm->Plots[0].Health++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[0].Health != 0)
                farm->Plots[0].Health--;
        }

        int8_t Health[1];
        Health[0] = farm->Plots[0].Health + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,2, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 80) && (R.yMax == 60))
    {
        if(entered == 't')
        {
            if(farm->Plots[1].Health != 5)
                farm->Plots[1].Health++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[1].Health != 0)
                farm->Plots[1].Health--;
        }

        int8_t Health[1];
        Health[0] = farm->Plots[1].Health + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,41, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 120) && (R.yMax == 60))
    {
        if(entered == 't')
        {
            if(farm->Plots[2].Health != 5)
                farm->Plots[2].Health++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[2].Health != 0)
                farm->Plots[2].Health--;
        }

        int8_t Health[1];
        Health[0] = farm->Plots[2].Health + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,81, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 40) && (R.yMax == 100))
    {
        if(entered == 't')
        {
            if(farm->Plots[3].Health != 5)
                farm->Plots[3].Health++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[3].Health != 0)
                farm->Plots[3].Health--;
        }

        int8_t Health[1];
        Health[0] = farm->Plots[3].Health + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,2, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 80) && (R.yMax == 100))
    {
        if(entered == 't')
        {
            if(farm->Plots[4].Health != 5)
                farm->Plots[4].Health++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[4].Health != 0)
                farm->Plots[4].Health--;
        }

        int8_t Health[1];
        Health[0] = farm->Plots[4].Health + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,41, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 120) && (R.yMax == 100))
    {
        if(entered == 't')
        {
            if(farm->Plots[5].Health != 5)
                farm->Plots[5].Health++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[5].Health != 0)
                farm->Plots[5].Health--;
        }

        int8_t Health[1];
        Health[0] = farm->Plots[5].Health + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p,Health , -1,81, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
}

void changeHydration(farm_t *farm,Graphics_Rectangle R,uint8_t entered,Graphics_Context *g_sContext_p )
{
    if((R.xMax == 40) && (R.yMax == 60))
    {
        if(entered == 'r')
        {
            if(farm->Plots[0].Hydration != 5)
                farm->Plots[0].Hydration++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[0].Hydration != 0)
                farm->Plots[0].Hydration--;
        }

        int8_t hydration[1];
        hydration[0] = farm->Plots[0].Hydration + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,16, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 80) && (R.yMax == 60))
    {
        if(entered == 'r')
        {
            if(farm->Plots[1].Hydration != 5)
                farm->Plots[1].Hydration++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[1].Hydration != 0)
                farm->Plots[1].Hydration--;
        }

        int8_t hydration[1];
        hydration[0] = farm->Plots[1].Hydration + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,55, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 120) && (R.yMax == 60))
    {
        if(entered == 'r')
        {
            if(farm->Plots[2].Hydration != 5)
                farm->Plots[2].Hydration++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[2].Hydration != 0)
                farm->Plots[2].Hydration--;
        }

        int8_t hydration[1];
        hydration[0] = farm->Plots[2].Hydration + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,95, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 40) && (R.yMax == 100))
    {
        if(entered == 'r')
        {
            if(farm->Plots[3].Hydration != 5)
                farm->Plots[3].Hydration++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[3].Hydration != 0)
                farm->Plots[3].Hydration--;
        }

        int8_t hydration[1];
        hydration[0] = farm->Plots[3].Hydration + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,16, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 80) && (R.yMax == 100))
    {
        if(entered == 'r')
        {
            if(farm->Plots[4].Hydration != 5)
                farm->Plots[4].Hydration++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[4].Hydration != 0)
                farm->Plots[4].Hydration--;
        }

        int8_t hydration[1];
        hydration[0] = farm->Plots[4].Hydration + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,55, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    else if((R.xMax == 120) && (R.yMax == 100))
    {
        if(entered == 'r')
        {
            if(farm->Plots[5].Hydration != 5)
                farm->Plots[5].Hydration++;
        }
        else if(entered == 'm')
        {
            if(farm->Plots[5].Hydration != 0)
                farm->Plots[5].Hydration--;
        }

        int8_t hydration[1];
        hydration[0] = farm->Plots[5].Hydration + 48;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p,hydration , -1,95, 85, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
}

bool isEmpty(Graphics_Rectangle *R, farm_t *farm )
{
    if((R->xMax == 40) && (R->yMax == 60))
    {
        if((farm->Plots[0].Age == 0) && (farm->Plots[0].Health == 0))
            return true;
        else
            return false;
    }
    else if((R->xMax == 80) && (R->yMax == 60))
    {
        if((farm->Plots[1].Age == 0) && (farm->Plots[1].Health == 0))
            return true;
        else
            return false;
    }
    else if((R->xMax == 120) && (R->yMax == 60))
    {
        if((farm->Plots[2].Age == 0) && (farm->Plots[2].Health == 0))
            return true;
        else
            return false;

    }
    else if ((R->xMax == 40) && (R->yMax == 100))
    {
        if((farm->Plots[3].Age == 0) && (farm->Plots[3].Health == 0))
            return true;
        else
            return false;

    }
    else if ((R->xMax == 80) && (R->yMax == 100))
    {
        if((farm->Plots[4].Age == 0) && (farm->Plots[4].Health == 0))
            return true;
        else
            return false;
    }
    else if ((R->xMax == 120) && (R->yMax == 100))
    {
        if((farm->Plots[5].Age == 0) && (farm->Plots[5].Health == 0))
            return true;
        else
            return false;
    }
}

void plots(Graphics_Rectangle R,farm_t *farm ,Graphics_Context *g_sContext_p)
{
    int8_t Age[1];
    int8_t Health[1];
    int8_t Hydration[1];

    farm->Money--;
    if((R.xMax == 40) && (R.yMax == 60))//The first Plot in the array it is the second plot
    {
        farm->Plots[0].Health = 3;
        farm->Plots[0].Hydration = 2;
        farm->Plots[0].Age = 0;

        Health[0] = farm->Plots[0].Health + 48;
        Hydration[0] = farm->Plots[0].Hydration + 48;
        Age[0] = farm->Plots[0].Age + 48;


        Graphics_fillCircle(g_sContext_p, 10, 30, 1);
        Graphics_fillCircle(g_sContext_p, 20, 30, 1);
        Graphics_fillCircle(g_sContext_p, 30, 30, 1);
        Graphics_fillCircle(g_sContext_p, 10, 40, 1);
        Graphics_fillCircle(g_sContext_p, 20, 40, 1);
        Graphics_fillCircle(g_sContext_p, 30, 40, 1);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p, Health, -1, 2, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p, Hydration, -1, 16, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p, Age, -1, 30, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

    }
    else if ((R.xMax == 80) && (R.yMax == 60))
    {
        farm->Plots[1].Age = 0;
        farm->Plots[1].Health = 3;
        farm->Plots[1].Hydration = 2;

        Age[0] = farm->Plots[1].Age + 48;
        Health[0] = farm->Plots[1].Health + 48;
        Hydration[0] = farm->Plots[1].Hydration + 48;

        Graphics_fillCircle(g_sContext_p, 50, 30, 1);
        Graphics_fillCircle(g_sContext_p, 60, 30, 1);
        Graphics_fillCircle(g_sContext_p, 70, 30, 1);
        Graphics_fillCircle(g_sContext_p, 50, 40, 1);
        Graphics_fillCircle(g_sContext_p, 60, 40, 1);
        Graphics_fillCircle(g_sContext_p, 70, 40, 1);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p, Health, -1, 41, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p, Hydration, -1, 55, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p, Age, -1, 70, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

    }
    else if ((R.xMax == 120) && (R.yMax == 60))
    {
        farm->Plots[2].Age = 0;
        farm->Plots[2].Health = 3;
        farm->Plots[2].Hydration = 2;

        Age[0] = farm->Plots[2].Age + 48;
        Health[0] = farm->Plots[2].Health + 48;
        Hydration[0] = farm->Plots[2].Hydration + 48;

        Graphics_fillCircle(g_sContext_p, 90, 30, 1);
        Graphics_fillCircle(g_sContext_p, 100, 30, 1);
        Graphics_fillCircle(g_sContext_p, 110, 30, 1);
        Graphics_fillCircle(g_sContext_p, 90, 40, 1);
        Graphics_fillCircle(g_sContext_p, 100, 40, 1);
        Graphics_fillCircle(g_sContext_p, 110, 40, 1);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p, Health, -1, 81, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p, Hydration, -1, 95, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p, Age, -1, 105, 45, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);


    }
    else if ((R.xMax == 40) && (R.yMax == 100))
    {
        farm->Plots[3].Age = 0;
        farm->Plots[3].Health = 3;
        farm->Plots[3].Hydration = 2;

        Age[0] = farm->Plots[3].Age + 48;
        Health[0] = farm->Plots[3].Health + 48;
        Hydration[0] = farm->Plots[3].Hydration + 48;

        Graphics_fillCircle(g_sContext_p, 10, 70, 1);
        Graphics_fillCircle(g_sContext_p, 20, 70, 1);
        Graphics_fillCircle(g_sContext_p, 30, 70, 1);
        Graphics_fillCircle(g_sContext_p, 10, 80, 1);
        Graphics_fillCircle(g_sContext_p, 20, 80, 1);
        Graphics_fillCircle(g_sContext_p, 30, 80, 1);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p, Health, -1, 2, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p, Hydration, -1, 16, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p, Age, -1, 30, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

    }
    else if ((R.xMax == 80) && (R.yMax == 100))
    {
        farm->Plots[4].Age = 0;
        farm->Plots[4].Health = 3;
        farm->Plots[4].Hydration = 2;

        Age[0] = farm->Plots[4].Age + 48;
        Health[0] = farm->Plots[4].Health + 48;
        Hydration[0] = farm->Plots[4].Hydration + 48;


        Graphics_fillCircle(g_sContext_p, 50, 70, 1);
        Graphics_fillCircle(g_sContext_p, 60, 70, 1);
        Graphics_fillCircle(g_sContext_p, 70, 70, 1);
        Graphics_fillCircle(g_sContext_p, 50, 80, 1);
        Graphics_fillCircle(g_sContext_p, 60, 80, 1);
        Graphics_fillCircle(g_sContext_p, 70, 80, 1);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p, Health, -1, 41, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p, Hydration, -1, 55, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p, Age, -1, 70, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);


    }
    else if ((R.xMax == 120) && (R.yMax == 100))
    {
        farm->Plots[5].Age = 0;
        farm->Plots[5].Health = 3;
        farm->Plots[5].Hydration = 2;

        Age[0] = farm->Plots[5].Age + 48;
        Health[0] = farm->Plots[5].Health + 48;
        Hydration[0] = farm->Plots[5].Hydration + 48;


        Graphics_fillCircle(g_sContext_p, 90, 70, 1);
        Graphics_fillCircle(g_sContext_p, 100, 70, 1);
        Graphics_fillCircle(g_sContext_p, 110, 70, 1);
        Graphics_fillCircle(g_sContext_p, 90, 80, 1);
        Graphics_fillCircle(g_sContext_p, 100, 80, 1);
        Graphics_fillCircle(g_sContext_p, 110, 80, 1);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
        Graphics_drawString(g_sContext_p, Health, -1, 81, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLUE);
        Graphics_drawString(g_sContext_p, Hydration, -1, 95, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_YELLOW);
        Graphics_drawString(g_sContext_p, Age, -1, 105, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);


    }
}
void movePlots(Graphics_Rectangle *R, uint8_t rChar, Graphics_Context *g_sContext_p)
{
    if(rChar == 'd')
    {
        if(R->xMax+40 <= 120)
        {
            Graphics_drawRectangle(g_sContext_p, R);
            R->xMin = R->xMin + 40;
            R->xMax = R->xMax + 40;
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
            Graphics_drawRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        }
    }
    else if(rChar == 's')
    {
        if(R->yMax+40 <= 100)
        {
            Graphics_drawRectangle(g_sContext_p, R);
            R->yMin = R->yMin + 40;
            R->yMax = R->yMax + 40;
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
            Graphics_drawRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        }
    }
    else if(rChar == 'a')
    {
        if(R->xMin-40 >= 0)
        {
            Graphics_drawRectangle(g_sContext_p, R);
            R->xMin = R->xMin - 40;
            R->xMax = R->xMax - 40;
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
            Graphics_drawRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        }
    }
    else if(rChar == 'w')
    {
        if(R->yMin-40 >= 0)
        {
            Graphics_drawRectangle(g_sContext_p, R);
            R->yMin = R->yMin - 40;
            R->yMax = R->yMax - 40;
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
            Graphics_drawRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        }
    }
}

void Plot_init(Graphics_Rectangle *R, Graphics_Context *g_sContext_p)
{
    R->xMin = 0;
    R->xMax = 40;
    R->yMin = 20;
    R->yMax = 60;
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_GREEN);
    Graphics_drawRectangle(g_sContext_p, R);
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);

}

void ChangeDifficulty(farm_t *farm, eUSCI_UART_Config *uartConfig_p)
{
    if(farm->Difficulty == 'E')
    {
        farm->Difficulty = 'M';
        //UARTSetBaud(EUSCI_A0_BASE, uartConfig_p,baud19200);
    }
    else if(farm->Difficulty == 'M')
    {
        farm->Difficulty = 'H';
    }
}

void display(Graphics_Context *g_sContext_p, int8_t *timeString,
             int8_t *MoneyString, int8_t *HealthString, int8_t *DifficultyString)
{
    Graphics_Rectangle R;

        R.xMin = 0;
        R.xMax = 120;
        R.yMin = 20;
        R.yMax = 100;

    Graphics_drawRectangle(g_sContext_p, &R);
    Graphics_drawLineV(g_sContext_p, 40, 20, 100);
    Graphics_drawLineV(g_sContext_p, 80, 20, 100);
    Graphics_drawLineH(g_sContext_p, 0, 120, 60);
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


void InitTimer()
{

    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_setCount(TIMER32_0_BASE, 1);
    Timer32_startTimer(TIMER32_0_BASE, true);

    Timer32_initModule(TIMER32_1_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);
    Timer32_startTimer(TIMER32_1_BASE, true);
    Timer32_setCount(TIMER32_1_BASE, 1);
}

void startTimerE()
{
    Timer32_setCount(TIMER32_0_BASE, LOAD_E);
    Timer32_startTimer(TIMER32_0_BASE, true);
}

void startTimerM()
{
    Timer32_setCount(TIMER32_0_BASE, LOAD_M);
    Timer32_startTimer(TIMER32_0_BASE, true);
}

void startTimerH()
{
    Timer32_setCount(TIMER32_0_BASE, LOAD_H);
    Timer32_startTimer(TIMER32_0_BASE, true);
}

bool timer0Expired()
{
    return (Timer32_getValue(TIMER32_0_BASE) == 0);
}

void initialize()
{
    // stop the watchdog timer
    WDT_A_hold(WDT_A_BASE);

    initialize_LaunchpadLED2_red();
    initialize_LaunchpadLED2_green();
    initialize_LaunchpadLED2_blue();
    initialize_BoosterpackLED_red();
    initialize_BoosterpackLED_green();
    initialize_BoosterpackLED_blue();

    turnOff_LaunchpadLED2_red();
    turnOff_LaunchpadLED2_green();
    turnOff_LaunchpadLED2_blue();
    turnOff_BoosterpackLED_red();
    turnOff_BoosterpackLED_green();
    turnOff_BoosterpackLED_blue();

    InitTimer();

    // call your intialization functions
}

/*void Commands(uint8_t rChar, Graphics_Rectangle *R, Graphics_Context *g_sContext, farm_t *farm,
              eUSCI_UART_Config *uartConfig, int8_t *timeString,int8_t *MoneyString,int8_t *HealthString,int8_t *DifficultyString)
{
    rChar = UARTGetChar(EUSCI_A0_BASE);
    switch(rChar)
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
                    if(isEmpty(&R, &farm))
                    {
                        plots(&R, &farm, &g_sContext);
                    }
                    break;
        case 'r':
                    break;
        case 'l':
                    ChangeDifficulty(&farm, &uartConfig);
                    display(&g_sContext, timeString, MoneyString, HealthString, DifficultyString);
                    break;
    }
}*/


