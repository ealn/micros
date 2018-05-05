/*
 * CustomIOFunctions.h
 *
 *  Created on: 28/04/2018
 *      Author: jpaco
 */

#ifndef CUSTOMIOWRAPPER_H_
#define CUSTOMIOWRAPPER_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

// Dummy definitions for easy coding in C files, support for macro-expansion is below
#define LCD_PIN_E
#define LCD_PIN_RS
#define LCD_PIN_DATA4
#define LCD_PIN_DATA5
#define LCD_PIN_DATA6
#define LCD_PIN_DATA7
#define LED_SYSTEMLED
#define BTN_BUTTON1
#define BTN_BUTTON2

// Pin definitions
#define LCD_PIN_E_PORT          GPIO_PORTB_BASE
#define LCD_PIN_E_PIN           GPIO_PIN_0
#define LCD_PIN_RS_PORT         GPIO_PORTB_BASE
#define LCD_PIN_RS_PIN         GPIO_PIN_1
#define LCD_PIN_DATA4_PORT      GPIO_PORTE_BASE
#define LCD_PIN_DATA4_PIN       GPIO_PIN_4
#define LCD_PIN_DATA5_PORT      GPIO_PORTE_BASE
#define LCD_PIN_DATA5_PIN       GPIO_PIN_5
#define LCD_PIN_DATA6_PORT      GPIO_PORTB_BASE
#define LCD_PIN_DATA6_PIN       GPIO_PIN_4
#define LCD_PIN_DATA7_PORT      GPIO_PORTA_BASE
#define LCD_PIN_DATA7_PIN       GPIO_PIN_5
#define LED_SYSTEMLED_PORT      GPIO_PORTF_BASE
#define LED_SYSTEMLED_PIN       GPIO_PIN_3
#define BTN_BUTTON1_PORT        GPIO_PORTF_BASE
#define BTN_BUTTON1_PIN         GPIO_PIN_0
#define BTN_BUTTON2_PORT        GPIO_PORTF_BASE
#define BTN_BUTTON2_PIN         GPIO_PIN_4

// Function wrappers
#define PIN_AS_OUTPUT(x)        GPIOPinTypeGPIOOutput(x##_PORT,x##_PIN)
#define PIN_AS_INPUT(x)         GPIOPinTypeGPIOInput(x##_PORT,x##_PIN);GPIOPadConfigSet(x##_PORT, x##_PIN,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU)
#define OUTPUT_HIGH(x)          GPIOPinWrite(x##_PORT,x##_PIN,x##_PIN)
#define OUTPUT_LOW(x)           GPIOPinWrite(x##_PORT,x##_PIN,0)
#define READ_BUTTON(x)          GPIOPinRead(x##_PORT,x##_PIN)




#endif /* CUSTOMIOWRAPPER_H_ */
