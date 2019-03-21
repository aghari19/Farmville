/*
 * Timer32_HAL.h
 *
 */

#ifndef TIMER32_HAL_H_
#define TIMER32_HAL_H_

#include "Farm.h"


void startOneShotTimer0(unsigned int LoadVal);
void startOneShotTimer1(unsigned int LoadVal);

void InitTimer();
bool timer0Expired();

void makeToString(farm_t farm, int8_t *string);
bool increaseTime(farm_t *farm);

// add more functions


#endif /* TIMER32_HAL_H_ */
