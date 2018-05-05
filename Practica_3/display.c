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

#define  REFRESH_MICROSEG        2 * 1000          // each 2 miliseconds refresh the display
#define  UPDATE_VALUE_MICROSEG   1 * 1000 * 1000   //each second update the display

static void sendInfoToDisplay(DisplayManager * pDisplayManager);

void initDisplayManager(DisplayManager   * pDisplayManager,
                        unsigned long      value,
                        unsigned char      numberOfDisplays,
                        unsigned char      isEnableInLow,
                        DisplayOutFunction outFunction,
                        unsigned long      mainDelay)
{
    if (pDisplayManager != NULL)
    {
        pDisplayManager->value = value;
        pDisplayManager->numberOfDisplays = numberOfDisplays;
        pDisplayManager->isEnableInLow = isEnableInLow;
        pDisplayManager->outFunction = outFunction;
        pDisplayManager->mainDelay = mainDelay;

        pDisplayManager->refreshCounter = (unsigned long)(REFRESH_MICROSEG / mainDelay);
        pDisplayManager->updateCounter = (unsigned long)(UPDATE_VALUE_MICROSEG / mainDelay);
    }
}

static unsigned char convertValueTo7Seg(DisplayManager * pDisplayManager, unsigned char value)
{
    unsigned char seg = 0;

    // convert to 7 seg
    //   - g f e d c b a
    //0b 0 0 0 0 1 1 0 1

    switch (value)
    {
        case 0:
            seg = 0b00111111;
            break; 
        case 1:
            seg = 0b00000110;
            break; 
        case 2:
            seg = 0b01011011;
            break; 
        case 3:
            seg = 0b01001111;
            break; 
        case 4:
            seg = 0b01100110;
            break;
        case 5:
            seg = 0b01101101;
            break;
        case 6:
            seg = 0b01111101;
            break;
        case 7:
            seg = 0b00000111;
            break;
        case 8:
            seg = 0b01111111;
            break;
        case 9:
            seg = 0b01101111;
            break;
    }

    if (pDisplayManager->isEnableInLow)
    {
        seg = ~seg;
    }

    return seg;
}

static void sendInfoToDisplay(DisplayManager * pDisplayManager)
{
    unsigned long value = pDisplayManager->value;
    unsigned long res = 0;
    unsigned char display = 1;
    unsigned char seg7 = 0;

    while (display <= pDisplayManager->numberOfDisplays)
    {
        res    = value % 10;
        value -= res;
        value /= 10;

        seg7 = convertValueTo7Seg(pDisplayManager, (unsigned char)res);

        pDisplayManager->outFunction(seg7, display);
        display++;
    }
}

unsigned char updateDisplay(DisplayManager * pDisplayManager, unsigned long value)
{
    unsigned char ret = 0;

    if (pDisplayManager != NULL)
    {
        //wait 1 seg
        if (pDisplayManager->updateCounter == 0) 
        {
            pDisplayManager->value = value;
            pDisplayManager->updateCounter = (unsigned long)(UPDATE_VALUE_MICROSEG / pDisplayManager->mainDelay);
            ret = 1;
        }
        else
        {
            pDisplayManager->updateCounter--;
        }
    }

    return ret;
}

unsigned char refreshDisplay(DisplayManager * pDisplayManager)
{
    unsigned char ret = 0;

    if (pDisplayManager != NULL)
    {
        //wait 2 miliseconds
        if (pDisplayManager->refreshCounter == 0) 
        {
            sendInfoToDisplay(pDisplayManager);
            pDisplayManager->refreshCounter = (unsigned long)(REFRESH_MICROSEG / pDisplayManager->mainDelay);
            ret = 1;
        }
        else
        {
            pDisplayManager->refreshCounter--;
        }
    }

    return ret;
}
