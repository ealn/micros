/*
 * button.c
 *
 *  Created on: 01/05/2018
 *      Author: jpaco
 */


#include "button.h"
#include "CustomIOWrapper.h"

static uint8_t buttonStatus[2];
static uint8_t buttonPressedFilter[2];

uint8_t BTN_readButton(uint8_t btn)
{
    return buttonStatus[btn];
}

void BTN_RunSM()
{
    // Buttons are active low
    if(READ_BUTTON(BTN_BUTTON1) == 0)
    {
        if(buttonPressedFilter[BUTTON1] >= BUTTON_PRESSED_FILTER_CYCLES)
            buttonStatus[BUTTON1] = 1;
        else
            buttonPressedFilter[BUTTON1]++;
    }
    else
    {
        buttonStatus[BUTTON1] = 0;
        buttonPressedFilter[BUTTON1] = 0;
    }
    if(READ_BUTTON(BTN_BUTTON2) == 0)
    {
        if(buttonPressedFilter[BUTTON2] >= BUTTON_PRESSED_FILTER_CYCLES)
            buttonStatus[BUTTON2] = 1;
        else
            buttonPressedFilter[BUTTON2]++;
    }
    else
    {
        buttonStatus[BUTTON2] = 0;
        buttonPressedFilter[BUTTON2] = 0;
    }
}
