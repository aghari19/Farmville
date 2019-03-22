/*
 * PlotStatus_Update_HAL.h
 *
 *  Created on: Mar 21, 2019
 *      Author: abarh
 */

#ifndef PLOTSTATUS_UPDATE_HAL_H_
#define PLOTSTATUS_UPDATE_HAL_H_

#include "Farm.h"
#include "UART_HAL.h"

#define LOAD_E 24000000
#define LOAD_M 16000000
#define LOAD_H 8000000

void changeStatus(farm_t *farm,Graphics_Context *g_sContext_p );

int checkStatus(farm_t *farm,Graphics_Context *g_sContext_p);

void changeHydration(farm_t *farm,Graphics_Rectangle R,uint8_t entered, Graphics_Context *g_sContext_p);

void changeHealth(farm_t *farm,Graphics_Rectangle R,uint8_t entered,Graphics_Context *g_sContext_p );

void ChangeDifficulty(farm_t *farm, eUSCI_UART_Config *uartConfig_p);

int update(farm_t *farm, bool Change,Graphics_Context *g_sContext_p );

void reset(farm_t *farm,Graphics_Context *g_sContext_p,Graphics_Rectangle R);

#endif /* PLOTSTATUS_UPDATE_HAL_H_ */
