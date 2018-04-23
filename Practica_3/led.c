/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Led Driver Source File                                            **/
/**                                                                   **/
/***********************************************************************/

#include "led.h"
#include "defines.h"

#define FACTOR_TO_NS      1000*1000

void initLed(Led              * pLed,
             LedOutFunction     outFunction,
             unsigned long      delay,
             unsigned long      mainDelay)
{
    unsigned long ms = 0;

    if (pLed != NULL)
    {
        pLed->turnOn = 0;
        pLed->outFunction = outFunction;
        pLed->delay = delay;
        pLed->mainDelay = mainDelay;

        ms = (unsigned long)(FACTOR_TO_NS / pLed->mainDelay);
        pLed->counter = pLed->delay * ms;
    }
}

void turnOnOffLed(Led  * pLed, unsigned char turnOn)
{
    if (pLed != NULL)
    {
        if (!turnOn)
        {
            pLed->turnOn = 0;
        }
        else
        {
            pLed->turnOn = 1;
        }

        pLed->outFunction(pLed->turnOn);
    }
}

void turnOnOffLedAuto(Led  * pLed)
{
    unsigned long ms = 0;

    if (pLed != NULL)
    {
        //wait
        if (pLed->counter == 0) 
        {
            //toogle led
            if (pLed->turnOn)
            {
                pLed->turnOn = 0;
            }
            else
            {
                pLed->turnOn = 1;
            }

            pLed->outFunction(pLed->turnOn);

            ms = (unsigned long)(FACTOR_TO_NS / pLed->mainDelay);
            pLed->counter = pLed->delay * ms;
        }
        else
        {
            pLed->counter--;
        }
    }
}

