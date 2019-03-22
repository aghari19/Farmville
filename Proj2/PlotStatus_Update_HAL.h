/*
 * PlotStatus_Update_HAL.h
 *
 *  Created on: Mar 22, 2019
 *      Author: abarh
 */

#ifndef PLOTSTATUS_UPDATE_HAL_H_
#define PLOTSTATUS_UPDATE_HAL_H_

/*
 * This .h files handles all the farm and plot manipulation at different levels
 */
#include "Farm.h"
#include "UART_HAL.h"

#define LOAD_E 24000000
#define LOAD_M 16000000
#define LOAD_H 8000000

/*
 * This method checks the current state of each plot when the month increases and then updates their age, health and hydration.
 */
void changeStatus(farm_t *farm,Graphics_Context *g_sContext_p );

/*
 * This method traverses through all the plots in the farm and looks at their status
 */
int checkStatus(farm_t *farm,Graphics_Context *g_sContext_p);

/*
 * This method is called when the month increases and thus decreasing the water level
 */
void changeHydration(farm_t *farm,Graphics_Rectangle R,uint8_t entered, Graphics_Context *g_sContext_p);

/*
 * This method is called when the month increases and thus decreasing the health level
 */
void changeHealth(farm_t *farm,Graphics_Rectangle R,uint8_t entered,Graphics_Context *g_sContext_p );

/*
 * This method is called when the letter 'l' is pressed and changes the baud rate of the game
 */
void ChangeDifficulty(farm_t *farm, eUSCI_UART_Config *uartConfig_p);

/*
 * This methods called the change and the check status methods
 */
int update(farm_t *farm, bool Change,Graphics_Context *g_sContext_p );

/*
 * This method resets the a dead plot when 't' is pressed.
 */
void reset(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R);



#endif /* PLOTSTATUS_UPDATE_HAL_H_ */
