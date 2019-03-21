// Any function that calls graphic library functions should be declared here and implemented in graphics_HAL.c

// This function initializes the graphics part

#include "Farm.h"

void InitGraphics(Graphics_Context *g_sContext_p);

void Plot_init(Graphics_Rectangle *R, Graphics_Context *g_sContext_p);
void movePlots(Graphics_Rectangle *R, uint8_t rChar , Graphics_Context *g_sContext_p);

void plots(Graphics_Rectangle R, farm_t *farm, Graphics_Context *g_sContext_p);

void growing(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R );
void Ready(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R );

void display(Graphics_Context *g_sContext_p, int8_t *timeString, int8_t *MoneyString, int8_t *HealthString, int8_t *DifficultyString);

void Harvest(farm_t *farm,Graphics_Rectangle *R,Graphics_Context *g_sContext_p );

void DrawTime(Graphics_Context *g_sContext_p, int8_t *timeString);
