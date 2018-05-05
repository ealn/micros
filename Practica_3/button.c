/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autores: Efrain Adrian Luna Nevarez                               **/
/**          Jose Francisco Velazquez Aguirre                         **/
/** Fecha: 18/03/2018                                                 **/
/** Button Driver Source File                                         **/
/**                                                                   **/
/***********************************************************************/

#include "button.h"
#include "defines.h"

#define  REBOUND_EFECT_NSEG      100*1000   //100ms = 100 000 microseg

void initButton(Button           * pButton,
                ButtonInFunction   inFunction,
                unsigned char      isEnableInLow,
                unsigned long      mainDelay)
{
    if (pButton != NULL)
    {
        pButton->state = BUTTON_UP;
        pButton->inFunction = inFunction;
        pButton->isEnableInLow = isEnableInLow;
        pButton->mainDelay = mainDelay;
        pButton->isPressed = 0;

        pButton->counter = (unsigned long)(REBOUND_EFECT_NSEG / pButton->mainDelay);
    }
}

static unsigned char valueChanged(Button *pButton)
{
    unsigned char ret = 0;
    unsigned char newValue = 0;
    ButtonState   newState = BUTTON_UP;

    if (pButton != NULL)
    {
        newValue = pButton->inFunction(); 

        if (pButton->isEnableInLow)
        {
            if (newValue == 0)
            {
                newState = BUTTON_DOWN;
            }
        }
        else
        {
            if (newValue == 1)
            {
                newState = BUTTON_DOWN;
            }
        }
        
        if (newState != pButton->state)
        {
            ret = 1;
        }
    }

    return ret;
}

unsigned char checkButton(Button *pButton)
{
    unsigned char ret = 0;

    if (pButton != NULL)
    {
        //check if the button was pressed
        if (!pButton->isPressed)
        {
            if (valueChanged(pButton))
            {
                pButton->state = BUTTON_DOWN;
                pButton->isPressed = 1;
            }
        }
        else
        {
            //wait 100ms
            if (pButton->counter == 0) 
            {
                if (valueChanged(pButton))
                {
                    //one click completed
                    pButton->state = BUTTON_UP;
                    pButton->isPressed = 0;
                    ret = 1;
                }

                pButton->counter = (unsigned long)(REBOUND_EFECT_NSEG / pButton->mainDelay); 
            }
            else
            {
                pButton->counter--;
            }
        }
    }

    return ret; 
}


