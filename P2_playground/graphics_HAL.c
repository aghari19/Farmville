#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

#include "Farm.h"
#include "graphics_HAL.h"

// This function is not used in upper level functions, so it does not need to be declared in the graphics_HAL.h
void InitFonts()
{
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
}

void InitGraphics(Graphics_Context *g_sContext_p)
{

    Graphics_initContext(g_sContext_p,
                         &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(g_sContext_p, &g_sFontCmtt12);

    InitFonts();

    Graphics_clearDisplay(g_sContext_p);
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
        Graphics_drawString(g_sContext_p, Age, -1, 109, 45, true);

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
        Graphics_drawString(g_sContext_p, Age, -1, 109, 85, true);

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);


    }
}

bool isEmptyDead(Graphics_Rectangle *R, farm_t *farm)
{
    if((R->xMax == 40) && (R->yMax == 60))
        {
            if((farm->Plots[0].Health == 0) && (farm->Plots[0].Age != 0))
                return true;
            else
                return false;
        }
        else if((R->xMax == 80) && (R->yMax == 60))
        {
            if((farm->Plots[1].Health == 0) && (farm->Plots[1].Age != 0))
                return true;
            else
                return false;
        }
        else if((R->xMax == 120) && (R->yMax == 60))
        {
            if((farm->Plots[2].Health == 0) && (farm->Plots[2].Age != 0))
                return true;
            else
                return false;

        }
        else if ((R->xMax == 40) && (R->yMax == 100))
        {
            if((farm->Plots[3].Health == 0) && (farm->Plots[3].Age != 0))
                return true;
            else
                return false;

        }
        else if ((R->xMax == 80) && (R->yMax == 100))
        {
            if((farm->Plots[4].Health == 0)&& (farm->Plots[4].Age != 0))
                return true;
            else
                return false;
        }
        else if ((R->xMax == 120) && (R->yMax == 100))
        {
            if((farm->Plots[5].Age == 0) && (farm->Plots[5].Health == 0)&& (farm->Plots[5].Age != 0))
                return true;
            else
                return false;
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

void Ready(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R )
{
    if ((R.xMax == 40) && (R.yMax == 60))
    {
        Graphics_fillCircle(g_sContext_p, 10, 30, 2);
        Graphics_drawLineV(g_sContext_p, 8, 26, 34);
        Graphics_drawLineV(g_sContext_p, 12, 26, 34);

        Graphics_fillCircle(g_sContext_p, 20, 30, 2);
        Graphics_drawLineV(g_sContext_p, 18, 26, 34);
        Graphics_drawLineV(g_sContext_p, 22, 26, 34);

        Graphics_fillCircle(g_sContext_p, 30, 30, 2);
        Graphics_drawLineV(g_sContext_p, 28, 26, 34);
        Graphics_drawLineV(g_sContext_p, 32, 26, 34);

        Graphics_fillCircle(g_sContext_p, 10, 40, 2);
        Graphics_drawLineV(g_sContext_p, 8, 36, 44);
        Graphics_drawLineV(g_sContext_p, 12, 36, 44);

        Graphics_fillCircle(g_sContext_p, 20, 40, 2);
        Graphics_drawLineV(g_sContext_p, 18, 36, 44);
        Graphics_drawLineV(g_sContext_p, 22, 36, 44);

        Graphics_fillCircle(g_sContext_p, 30, 40, 2);
        Graphics_drawLineV(g_sContext_p, 28, 36, 44);
        Graphics_drawLineV(g_sContext_p, 32, 36, 44);

    }
    else if ((R.xMax == 80) && (R.yMax == 60))
    {
        Graphics_fillCircle(g_sContext_p, 50, 30, 2);
        Graphics_drawLineV(g_sContext_p, 48, 26, 34);
        Graphics_drawLineV(g_sContext_p, 52, 26, 34);

        Graphics_fillCircle(g_sContext_p, 60, 30, 2);
        Graphics_drawLineV(g_sContext_p, 58, 26, 34);
        Graphics_drawLineV(g_sContext_p, 62, 26, 34);

        Graphics_fillCircle(g_sContext_p, 70, 30, 2);
        Graphics_drawLineV(g_sContext_p, 68, 26, 34);
        Graphics_drawLineV(g_sContext_p, 72, 26, 34);

        Graphics_fillCircle(g_sContext_p, 50, 40, 2);
        Graphics_drawLineV(g_sContext_p, 48, 36, 44);
        Graphics_drawLineV(g_sContext_p, 52, 36, 44);

        Graphics_fillCircle(g_sContext_p, 60, 40, 2);
        Graphics_drawLineV(g_sContext_p, 58, 36, 44);
        Graphics_drawLineV(g_sContext_p, 62, 36, 44);

        Graphics_fillCircle(g_sContext_p, 70, 40, 2);
        Graphics_drawLineV(g_sContext_p, 68, 36, 44);
        Graphics_drawLineV(g_sContext_p, 72, 36, 44);

    }
    else if ((R.xMax == 120) && (R.yMax == 60))
    {
        Graphics_fillCircle(g_sContext_p, 90, 30, 2);
        Graphics_drawLineV(g_sContext_p, 88, 26, 34);
        Graphics_drawLineV(g_sContext_p, 92, 26, 34);

        Graphics_fillCircle(g_sContext_p, 100, 30, 2);
        Graphics_drawLineV(g_sContext_p, 98, 26, 34);
        Graphics_drawLineV(g_sContext_p, 102, 26, 34);

        Graphics_fillCircle(g_sContext_p, 110, 30, 2);
        Graphics_drawLineV(g_sContext_p, 108, 26, 34);
        Graphics_drawLineV(g_sContext_p, 112, 26, 34);

        Graphics_fillCircle(g_sContext_p, 90, 40, 2);
        Graphics_drawLineV(g_sContext_p, 88, 36, 44);
        Graphics_drawLineV(g_sContext_p, 92, 36, 44);

        Graphics_fillCircle(g_sContext_p, 100, 40, 2);
        Graphics_drawLineV(g_sContext_p, 98, 36, 44);
        Graphics_drawLineV(g_sContext_p, 102, 36, 44);

        Graphics_fillCircle(g_sContext_p, 110, 40, 2);
        Graphics_drawLineV(g_sContext_p, 108, 36, 44);
        Graphics_drawLineV(g_sContext_p, 112, 36, 44);


    }
    else if ((R.xMax == 40) && (R.yMax == 100))
    {
        Graphics_fillCircle(g_sContext_p, 10, 70, 2);
        Graphics_drawLineV(g_sContext_p, 8, 66, 74);
        Graphics_drawLineV(g_sContext_p, 12, 66, 74);

        Graphics_fillCircle(g_sContext_p, 20, 70, 2);
        Graphics_drawLineV(g_sContext_p, 18, 66, 74);
        Graphics_drawLineV(g_sContext_p, 22, 66, 74);

        Graphics_fillCircle(g_sContext_p, 30, 70, 2);
        Graphics_drawLineV(g_sContext_p, 28, 66, 74);
        Graphics_drawLineV(g_sContext_p, 32, 66, 74);

        Graphics_fillCircle(g_sContext_p, 10, 80, 2);
        Graphics_drawLineV(g_sContext_p, 8, 76, 84);
        Graphics_drawLineV(g_sContext_p, 12, 76, 84);

        Graphics_fillCircle(g_sContext_p, 20, 80, 2);
        Graphics_drawLineV(g_sContext_p, 18, 76, 84);
        Graphics_drawLineV(g_sContext_p, 22, 76, 84);

        Graphics_fillCircle(g_sContext_p, 30, 80, 2);
        Graphics_drawLineV(g_sContext_p, 28, 76, 84);
        Graphics_drawLineV(g_sContext_p, 32, 76, 84);

    }
    else if ((R.xMax == 80) && (R.yMax == 100))
    {
        Graphics_fillCircle(g_sContext_p, 50, 70, 2);
        Graphics_drawLineV(g_sContext_p, 48, 66, 74);
        Graphics_drawLineV(g_sContext_p, 52, 66, 74);

        Graphics_fillCircle(g_sContext_p, 60, 70, 2);
        Graphics_drawLineV(g_sContext_p, 58, 66, 74);
        Graphics_drawLineV(g_sContext_p, 62, 66, 74);

        Graphics_fillCircle(g_sContext_p, 70, 70, 2);
        Graphics_drawLineV(g_sContext_p, 68, 66, 74);
        Graphics_drawLineV(g_sContext_p, 72, 66, 74);

        Graphics_fillCircle(g_sContext_p, 50, 80, 2);
        Graphics_drawLineV(g_sContext_p, 48, 76, 84);
        Graphics_drawLineV(g_sContext_p, 52, 76, 84);

        Graphics_fillCircle(g_sContext_p, 60, 80, 2);
        Graphics_drawLineV(g_sContext_p, 58, 76, 84);
        Graphics_drawLineV(g_sContext_p, 62, 76, 84);

        Graphics_fillCircle(g_sContext_p, 70, 80, 2);
        Graphics_drawLineV(g_sContext_p, 68, 76, 84);
        Graphics_drawLineV(g_sContext_p, 72, 76, 84);

    }
    else if ((R.xMax == 120) && (R.yMax == 100))
    {
        Graphics_fillCircle(g_sContext_p, 90, 70, 2);
        Graphics_drawLineV(g_sContext_p, 88, 66, 74);
        Graphics_drawLineV(g_sContext_p, 92, 66, 74);

        Graphics_fillCircle(g_sContext_p, 100, 70, 2);
        Graphics_drawLineV(g_sContext_p, 98, 66, 74);
        Graphics_drawLineV(g_sContext_p, 102, 66, 74);

        Graphics_fillCircle(g_sContext_p, 110, 70, 2);
        Graphics_drawLineV(g_sContext_p, 108, 66, 74);
        Graphics_drawLineV(g_sContext_p, 112, 66, 74);

        Graphics_fillCircle(g_sContext_p, 90, 80, 2);
        Graphics_drawLineV(g_sContext_p, 88, 76, 84);
        Graphics_drawLineV(g_sContext_p, 92, 76, 84);

        Graphics_fillCircle(g_sContext_p, 100, 80, 2);
        Graphics_drawLineV(g_sContext_p, 98, 76, 84);
        Graphics_drawLineV(g_sContext_p, 102, 76, 84);

        Graphics_fillCircle(g_sContext_p, 110, 80, 2);
        Graphics_drawLineV(g_sContext_p, 108, 76, 84);
        Graphics_drawLineV(g_sContext_p, 112, 76, 84);

    }
}
void Dead(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R )
{
    if ((R.xMax == 40) && (R.yMax == 60)) //The first Plot in the array it is the second plot
    {
        Graphics_Rectangle Rec;
        Rec.xMin = 1;
        Rec.xMax = 39;
        Rec.yMin = 21;
        Rec.yMax = 59;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext_p,&Rec);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineV(g_sContext_p, 10, 26, 34);
        Graphics_drawLineV(g_sContext_p, 20, 26, 34);
        Graphics_drawLineV(g_sContext_p, 30, 26, 34);
        Graphics_drawLineV(g_sContext_p, 10, 36, 44);
        Graphics_drawLineV(g_sContext_p, 20, 36, 44);
        Graphics_drawLineV(g_sContext_p, 30, 36, 44);
        //farm->Plots[0].Age = 0;
        farm->Plots[0].Health = 0;
        //farm->Plots[0].Hydration = 0;

    }
    else if ((R.xMax == 80) && (R.yMax == 60))
    {
        Graphics_Rectangle Rec;
        Rec.xMin = 41;
        Rec.xMax = 79;
        Rec.yMin = 21;
        Rec.yMax = 59;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext_p,&Rec);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineV(g_sContext_p, 50, 26, 34);
        Graphics_drawLineV(g_sContext_p, 60, 26, 34);
        Graphics_drawLineV(g_sContext_p, 70, 26, 34);
        Graphics_drawLineV(g_sContext_p, 50, 36, 44);
        Graphics_drawLineV(g_sContext_p, 60, 36, 44);
        Graphics_drawLineV(g_sContext_p, 70, 36, 44);
        //farm->Plots[1].Age = 0;
        farm->Plots[1].Health = 0;
        //farm->Plots[1].Hydration = 0;
    }
    else if ((R.xMax == 120) && (R.yMax == 60))
    {
        Graphics_Rectangle Rec;
        Rec.xMin = 81;
        Rec.xMax = 119;
        Rec.yMin = 21;
        Rec.yMax = 59;

        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext_p,&Rec);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineV(g_sContext_p, 90, 26, 34);
        Graphics_drawLineV(g_sContext_p, 100, 26, 34);
        Graphics_drawLineV(g_sContext_p, 110, 26, 34);
        Graphics_drawLineV(g_sContext_p, 90, 36, 44);
        Graphics_drawLineV(g_sContext_p, 100, 36, 44);
        Graphics_drawLineV(g_sContext_p, 110, 36, 44);
        //farm->Plots[2].Age = 0;
        farm->Plots[2].Health = 0;
        //farm->Plots[2].Hydration = 0;
    }
    else if ((R.xMax == 40) && (R.yMax == 100))
    {
        Graphics_Rectangle Rec;
        Rec.xMin = 1;
        Rec.xMax = 39;
        Rec.yMin = 61;
        Rec.yMax = 99;
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext_p,&Rec);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineV(g_sContext_p, 10, 66, 74);
        Graphics_drawLineV(g_sContext_p, 20, 66, 74);
        Graphics_drawLineV(g_sContext_p, 30, 66, 74);
        Graphics_drawLineV(g_sContext_p, 10, 76, 84);
        Graphics_drawLineV(g_sContext_p, 20, 76, 84);
        Graphics_drawLineV(g_sContext_p, 30, 76, 84);
        //farm->Plots[3].Age = 0;
        farm->Plots[3].Health = 0;
        //farm->Plots[3].Hydration = 0;
    }
    else if ((R.xMax == 80) && (R.yMax == 100))
    {
        Graphics_Rectangle Rec;
        Rec.xMin = 41;
        Rec.xMax = 79;
        Rec.yMin = 61;
        Rec.yMax = 99;
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext_p,&Rec);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineV(g_sContext_p, 50, 66, 74);
        Graphics_drawLineV(g_sContext_p, 60, 66, 74);
        Graphics_drawLineV(g_sContext_p, 70, 66, 74);
        Graphics_drawLineV(g_sContext_p, 50, 76, 84);
        Graphics_drawLineV(g_sContext_p, 60, 76, 84);
        Graphics_drawLineV(g_sContext_p, 70, 76, 84);
        //farm->Plots[4].Age = 0;
        farm->Plots[4].Health = 0;
        //farm->Plots[4].Hydration = 0;
    }
    else if ((R.xMax == 120) && (R.yMax == 100))
    {
        Graphics_Rectangle Rec;
        Rec.xMin = 81;
        Rec.xMax = 119;
        Rec.yMin = 61;
        Rec.yMax = 99;
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
        Graphics_fillRectangle(g_sContext_p,&Rec);
        Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
        Graphics_drawLineV(g_sContext_p, 90, 66, 74);
        Graphics_drawLineV(g_sContext_p, 100, 66, 74);
        Graphics_drawLineV(g_sContext_p, 110, 66, 74);
        Graphics_drawLineV(g_sContext_p, 90, 76, 84);
        Graphics_drawLineV(g_sContext_p, 100, 76, 84);
        Graphics_drawLineV(g_sContext_p, 110, 76, 84);
        //farm->Plots[5].Age = 0;
        farm->Plots[5].Health = 0;
        //farm->Plots[5].Hydration = 0;
    }
}

void growing(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R )
{
    if ((R.xMax == 40) && (R.yMax == 60)) //The first Plot in the array it is the second plot
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
        Graphics_drawLineV(g_sContext_p, 110, 36, 44);

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

void Harvest(farm_t *farm,Graphics_Rectangle *R,Graphics_Context *g_sContext_p )
{
    if((R->xMax == 40) && (R->yMax == 60))
    {
        if((farm->Plots[0].Age > 6) && (farm->Plots[0].Age < 9) &&
                           (farm->Plots[0].Health > 2) && (farm->Plots[0].Hydration > 2))
        {
            farm->Plots[0].Age = 0;
            farm->Plots[0].Health = 0;
            farm->Plots[0].Hydration = 0;

            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(g_sContext_p,R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
            farm->Money = farm->Money + 2;

            int8_t Money[3];
            Money[0] = ((farm->Money/10)%10) + 48;
            Money[1] = (farm->Money%10) + 48;

            Graphics_drawString(g_sContext_p, Money, -1, 70, 105, true);
        }
    }
    else if((R->xMax == 80) && (R->yMax == 60))
    {
        if ((farm->Plots[1].Age > 6) && (farm->Plots[1].Age < 9)
                && (farm->Plots[1].Health > 2)
                && (farm->Plots[1].Hydration > 2))
        {
            farm->Plots[1].Age = 0;
            farm->Plots[1].Health = 0;
            farm->Plots[1].Hydration = 0;

            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
            farm->Money = farm->Money + 2;

            int8_t Money[3];
            Money[0] = ((farm->Money / 10) % 10) + 48;
            Money[1] = (farm->Money % 10) + 48;

            Graphics_drawString(g_sContext_p, Money, -1, 70, 105, true);
        }
    }
    else if((R->xMax == 120) && (R->yMax == 60))
    {
        if ((farm->Plots[2].Age > 6) && (farm->Plots[2].Age < 9)
                && (farm->Plots[2].Health > 2)
                && (farm->Plots[2].Hydration > 2))
        {
            farm->Plots[2].Age = 0;
            farm->Plots[2].Health = 0;
            farm->Plots[2].Hydration = 0;

            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
            farm->Money = farm->Money + 2;

            int8_t Money[3];
            Money[0] = ((farm->Money / 10) % 10) + 48;
            Money[1] = (farm->Money % 10) + 48;

            Graphics_drawString(g_sContext_p, Money, -1, 70, 105, true);
        }
    }
    else if((R->xMax == 40) && (R->yMax == 100))
    {
        if ((farm->Plots[3].Age > 6) && (farm->Plots[3].Age < 9)
                && (farm->Plots[3].Health > 2)
                && (farm->Plots[3].Hydration > 2))
        {
            farm->Plots[3].Age = 0;
            farm->Plots[3].Health = 0;
            farm->Plots[3].Hydration = 0;

            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
            farm->Money = farm->Money + 2;

            int8_t Money[3];
            Money[0] = ((farm->Money / 10) % 10) + 48;
            Money[1] = (farm->Money % 10) + 48;

            Graphics_drawString(g_sContext_p, Money, -1, 70, 105, true);
        }
    }
    else if((R->xMax == 80) && (R->yMax == 100))
    {
        if ((farm->Plots[4].Age > 6) && (farm->Plots[4].Age < 9)
                && (farm->Plots[4].Health > 2)
                && (farm->Plots[4].Hydration > 2))
        {
            farm->Plots[4].Age = 0;
            farm->Plots[4].Health = 0;
            farm->Plots[4].Hydration = 0;

            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
            farm->Money = farm->Money + 2;

            int8_t Money[3];
            Money[0] = ((farm->Money / 10) % 10) + 48;
            Money[1] = (farm->Money % 10) + 48;

            Graphics_drawString(g_sContext_p, Money, -1, 70, 105, true);
        }
    }
    else if((R->xMax == 120) && (R->yMax == 100))
    {
        if ((farm->Plots[5].Age > 6) && (farm->Plots[5].Age < 9)
                && (farm->Plots[5].Health > 2)
                && (farm->Plots[5].Hydration > 2))
        {
            farm->Plots[5].Age = 0;
            farm->Plots[5].Health = 0;
            farm->Plots[5].Hydration = 0;

            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
            Graphics_fillRectangle(g_sContext_p, R);
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
            farm->Money = farm->Money + 2;

            int8_t Money[3];
            Money[0] = ((farm->Money / 10) % 10) + 48;
            Money[1] = (farm->Money % 10) + 48;

            Graphics_drawString(g_sContext_p, Money, -1, 70, 105, true);
        }
    }

}

void DrawTime(Graphics_Context *g_sContext_p, int8_t *timeString)
{
    Graphics_drawString(g_sContext_p, timeString, -1, 10, 5, true);
}

void DrawHealth(Graphics_Context *g_sContext_p, int8_t *HealthString, int Health)
{
    //HealthString[8] = "0";
    HealthString[8] = ((Health / 10) % 10) + 48;
    HealthString[9] = (Health % 10) + 48;

    Graphics_drawString(g_sContext_p, HealthString, -1, 10, 115, true);

}
