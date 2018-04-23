/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Display Driver Source File                                        **/
/**                                                                   **/
/***********************************************************************/

#include "display.h"
#include "defines.h"

#define  UPDATE_NSEG    1*1000*1000

static void sendInfoToDisplay(DisplayManager * pDisplayManager,
                              unsigned long value,
                              unsigned char updateAllDisplays);

void initDisplayManager(DisplayManager   * pDisplayManager,
                        unsigned long      value,
                        unsigned char      numberOfDisplays,
                        DisplayOutFunction outFunction,
                        unsigned long      mainDelay)
{
    if (pDisplayManager != NULL)
    {
        pDisplayManager->value = value;
        pDisplayManager->numberOfDisplays = numberOfDisplays;
        pDisplayManager->outFunction = outFunction;
        pDisplayManager->mainDelay = mainDelay;

        pDisplayManager->counter = (unsigned long)(UPDATE_NSEG / mainDelay);
        sendInfoToDisplay(pDisplayManager, value, 1);
    }
}

static void sendInfoToDisplay(DisplayManager * pDisplayManager,
                              unsigned long value,
                              unsigned char updateAllDisplays)
{
    unsigned long currentValue = pDisplayManager->value;
    unsigned long resCurValue = 0;
    unsigned long newValue = value;
    unsigned long resValue = 0;
    unsigned char display = 1;

    if (updateAllDisplays)
    {
        while (display <= pDisplayManager->numberOfDisplays)
        {
            resValue  = newValue % 10;
            newValue -= resValue;
            newValue /= 10;

            pDisplayManager->outFunction(resValue, display);
            display++;
        }
    }
    else
    {
        while (display <= pDisplayManager->numberOfDisplays)
        {
            resValue  = newValue % 10;
            newValue -= resValue;
            newValue /= 10;

            resCurValue   = currentValue % 10;
            currentValue -= resCurValue;
            currentValue /= 10;

            if (resValue != resCurValue)
            {
                pDisplayManager->outFunction(resValue, display); 
            }

            display++;
        }
    }
}

void updateDisplay(DisplayManager * pDisplayManager, unsigned long value)
{
    if (pDisplayManager != NULL)
    {
        //wait 1ms
        if (pDisplayManager->counter == 0) 
        {
            //if value changed
            if (pDisplayManager->value != value)
            {
                sendInfoToDisplay(pDisplayManager, value, 0);
            }

            pDisplayManager->counter = (unsigned long)(UPDATE_NSEG / pDisplayManager->mainDelay); 
        }
        else
        {
            pDisplayManager->counter--;
        }
    }
}


