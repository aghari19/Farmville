// Any function that calls graphic library functions should be declared here and implemented in graphics_HAL.c

// This function initializes the graphics part

#include "Farm.h"

//This method initializes the graphics
void InitGraphics(Graphics_Context *g_sContext_p);

//This method draws the initial games screen with the plots, time, Difficulty level, money and health.
void Plot_init(Graphics_Rectangle *R, Graphics_Context *g_sContext_p);

/*   This method is called when the characters a,s,d,w are
 *   encountered. It moves from the current position if possible and highlights it in green
*/
void movePlots(Graphics_Rectangle *R, uint8_t rChar , Graphics_Context *g_sContext_p);

/*
 * This method is called when the character 'p' is encounter. It plots a circles as seeds on the selected plot and display the age,
 * health and hydration of the plot.
 */
void plots(Graphics_Rectangle R, farm_t *farm, Graphics_Context *g_sContext_p);
/*
 * This method is called when the plot moves from seeding to growing and prints a symbol that signifies the plant is growing along
 * with updating the age, health and hydration
 */
void growing(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R );

/*
 * This method is called when the plot moves from growing to ready i.e., can be harvested. It does the updation of the same members
 * growing() and plots()
 */
void Ready(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R );

/*
 * This Method is called when the plant has not be harvest and it moves to being a dead plant and updates health = 0;
 */
void Dead(farm_t *farm,Graphics_Context *g_sContext_p, Graphics_Rectangle R );

/*
 * This method displays the whole farm status
 */
void display(Graphics_Context *g_sContext_p, int8_t *timeString, int8_t *MoneyString, int8_t *HealthString, int8_t *DifficultyString);

/*
 * This method is called when 'h' is encountered and the plant is harvested, the money increases and the plot clears.
 */
void Harvest(farm_t *farm,Graphics_Rectangle *R,Graphics_Context *g_sContext_p );

/*
 * This method is called every time the timer changes which varies with the baudrate the farm is running at.
 */
void DrawTime(Graphics_Context *g_sContext_p, int8_t *timeString);

/*
 * This method is called when the health of the farm changes and the method draws the new health
 */
void DrawHealth(Graphics_Context *g_sContext_p, int8_t *HealthString, int Health);

/*
 * This method checks if the position on player is at is Empty or not.
 */
bool isEmpty(Graphics_Rectangle R, farm_t *farm);

/*
 * This method checks if the position the player is at is dead with crops or not.
 */
bool isEmptyDead(Graphics_Rectangle R, farm_t *farm);

/*
 * This method displays the game over screen
 */
void drawGameOver(Graphics_Context *g_sContext_p,Graphics_Image *Image );
