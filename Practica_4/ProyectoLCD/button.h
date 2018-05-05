/*
 * button.h
 *
 *  Created on: 01/05/2018
 *      Author: jpaco
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>

#define BUTTON1 0
#define BUTTON2 1
#define BUTTON_PRESSED_FILTER_CYCLES 5

//////////////////////////////////////////////
// Interface functions
//////////////////////////////////////////////
uint8_t BTN_readButton(uint8_t btn);
void BTN_RunSM();

//////////////////////////////////////////////
// Internal functions
//////////////////////////////////////////////



#endif /* BUTTON_H_ */
