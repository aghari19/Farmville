/*
 * PlotStatus_Update_HAL.c
 *
 *  Created on: Mar 21, 2019
 *      Author: abarh
 */

#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

#include "PlotStatus_Update_HAL.h"

int checkStatus(farm_t *farm,Graphics_Context *g_sContext_p)
{
    int i = 0;
    Graphics_Rectangle R;
       R.xMax = 40;
       R.xMin = 0;
       R.yMax = 60;
       R.yMin = 20;
       if(!isEmpty(&R, farm))
       {
           i++;
            if((farm->Plots[0].Age > 2) && (farm->Plots[0].Age < 9) &&
                    (farm->Plots[0].Health > 0) && (farm->Plots[0].Hydration > 3))
            {
                growing(farm,g_sContext_p, R);
            }
            if((farm->Plots[0].Age > 6) && (farm->Plots[0].Age < 9) &&
                    (farm->Plots[0].Health > 2) && (farm->Plots[0].Hydration > 2))
            {
                Ready(farm,g_sContext_p, R);
            }
            if((farm->Plots[0].Age > 9)|(farm->Plots[0].Health == 0)|(farm->Plots[0].Hydration == 0))
            {
                Dead(farm,g_sContext_p, R);
            }
       }
       R.xMax = 80;
       R.yMax = 60;
       if(!isEmpty(&R, farm))
       {
           i++;
           if((farm->Plots[1].Age > 2) && (farm->Plots[1].Age < 9) &&
                   (farm->Plots[1].Health > 0) && (farm->Plots[1].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
           if((farm->Plots[1].Age > 6) && (farm->Plots[1].Age < 9) &&
                   (farm->Plots[1].Health > 2) && (farm->Plots[1].Hydration > 2))
           {
               Ready(farm,g_sContext_p, R);
           }
           if((farm->Plots[1].Age > 9)|(farm->Plots[1].Health == 0)|(farm->Plots[1].Hydration == 0))
           {
               Dead(farm,g_sContext_p, R);
           }
       }
       R.xMax = 120;
       R.yMax = 60;
       if(!isEmpty(&R, farm))
       {
           i++;
           if((farm->Plots[2].Age > 2) && (farm->Plots[2].Age < 9) &&
                   (farm->Plots[2].Health > 0) && (farm->Plots[2].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
           if((farm->Plots[2].Age > 6) && (farm->Plots[2].Age < 9) &&
                   (farm->Plots[2].Health > 2) && (farm->Plots[2].Hydration > 2))
           {
               Ready(farm,g_sContext_p, R);
           }
           if((farm->Plots[2].Age > 9)|(farm->Plots[2].Health == 0)|(farm->Plots[2].Hydration == 0))
           {
               Dead(farm,g_sContext_p, R);
           }
       }
       R.xMax = 40;
       R.yMax = 100;
       if(!isEmpty(&R, farm))
       {
           i++;
           if((farm->Plots[3].Age > 2) && (farm->Plots[3].Age < 9) &&
                   (farm->Plots[3].Health > 0) && (farm->Plots[3].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
           if((farm->Plots[3].Age > 6) && (farm->Plots[3].Age < 9) &&
                   (farm->Plots[3].Health > 2) && (farm->Plots[3].Hydration > 2))
           {
               Ready(farm,g_sContext_p, R);
           }
           if((farm->Plots[3].Age > 9)|(farm->Plots[3].Health == 0)|(farm->Plots[3].Hydration == 0))
           {
               Dead(farm,g_sContext_p, R);
           }
       }
       R.xMax = 80;
       R.yMax = 100;
       if(!isEmpty(&R, farm))
       {
           i++;
           if((farm->Plots[4].Age > 2) && (farm->Plots[4].Age < 9) &&
                   (farm->Plots[4].Health > 0) && (farm->Plots[4].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
           if((farm->Plots[4].Age > 6) && (farm->Plots[4].Age < 9) &&
                   (farm->Plots[4].Health > 2) && (farm->Plots[4].Hydration > 2))
           {
               Ready(farm,g_sContext_p, R);
           }
           if((farm->Plots[4].Age > 9)|(farm->Plots[4].Health == 0)|(farm->Plots[4].Hydration == 0))
           {
               Dead(farm,g_sContext_p, R);
           }
       }
       R.xMax = 120;
       R.yMax = 100;
       if(!isEmpty(&R, farm))
       {
           i++;
           if((farm->Plots[5].Age > 2) && (farm->Plots[5].Age < 9) &&
                   (farm->Plots[5].Health > 0) && (farm->Plots[5].Hydration > 3))
           {
               growing(farm,g_sContext_p, R);
           }
           if((farm->Plots[5].Age > 6) && (farm->Plots[5].Age < 9) &&
                   (farm->Plots[5].Health > 2) && (farm->Plots[5].Hydration > 2))
           {
               Ready(farm,g_sContext_p, R);
           }
           if((farm->Plots[5].Age > 9)|(farm->Plots[5].Health == 0)|(farm->Plots[5].Hydration == 0))
           {
               Dead(farm,g_sContext_p, R);
           }
       }
       return i;
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
        if(farm->Plots[1].Hydration != 0)
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
        if(farm->Plots[2].Hydration != 0)
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
        Graphics_drawString(g_sContext_p,Age , -1,109, 45, true);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    }
    R.xMax = 40;
    R.yMax = 100;
    if(!isEmpty(&R, farm))
    {
        if(farm->Plots[3].Health != 0)
            farm->Plots[3].Health--;
        if(farm->Plots[3].Hydration != 0)
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
        if(farm->Plots[4].Hydration != 0)
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
        if(farm->Plots[5].Hydration != 0)
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
        Graphics_drawString(g_sContext_p,Age , -1,109, 85, true);
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


void ChangeDifficulty(farm_t *farm, eUSCI_UART_Config *uartConfig_p)
{
    if(farm->Difficulty == 'E')
    {
        farm->Difficulty = 'M';
        UARTSetBaud(EUSCI_A0_BASE, uartConfig_p, baud19200);
    }
    else if(farm->Difficulty == 'M')
    {
        farm->Difficulty = 'H';
        UARTSetBaud(EUSCI_A0_BASE, uartConfig_p, baud57600);
    }
}

int update(farm_t *farm, bool Change, Graphics_Rectangle R,Graphics_Context *g_sContext_p )
{
    if(Change == true)
    {
        changeStatus(farm,g_sContext_p);
    }
    return checkStatus(farm,g_sContext_p);
}






