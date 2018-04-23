/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Button Driver Header File                                         **/
/**                                                                   **/
/***********************************************************************/

#ifndef _BUTTON_H_
#define _BUTTON_H_

typedef unsigned char (*ButtonInFunction)(void);
typedef enum
{
    BUTTON_UP = 0,
    BUTTON_DOWN
}ButtonState;

typedef struct __Button
{
    ButtonState        state;         // State
    ButtonInFunction   inFunction;    // Function to check the button state
    unsigned char      isEnableInLow; // Is button enable in low
    unsigned long      counter;       // Counter
    unsigned long      mainDelay;     // Main delay in ns
    unsigned char      isPressed;     // Is button pressed
}Button;

void initButton(Button           * pButton,
                ButtonInFunction   inFunction,
                unsigned char      isEnableInLow,
                unsigned long      mainDelay);

unsigned char checkButton(Button *pButton);

#endif /* ifndef _BUTTON_H_ */
