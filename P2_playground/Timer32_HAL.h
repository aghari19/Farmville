/*
 * Timer32_HAL.h
 *
 */

#ifndef TIMER32_HAL_H_
#define TIMER32_HAL_H_

#include "Farm.h"

/*
 * This method starts the timer with different load values depending on the difficulty level
 */
void startOneShotTimer0(unsigned int LoadVal);
void startOneShotTimer1(unsigned int LoadVal);

//This method initializes the timer
void InitTimer();

//This method returns the timer has expired or not
bool timer0Expired();

//This method taken in a number in this case time and converts it into a string
void makeToString(farm_t farm, int8_t *string);

//This method increses the timers once the timer starts at very time the loop is encountered
bool increaseTime(farm_t *farm);

#endif /* TIMER32_HAL_H_ */
