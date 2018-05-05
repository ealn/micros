/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autores: Efrain Adrian Luna Nevarez                               **/
/**          Jose Francisco Velazquez Aguirre                         **/
/** Fecha: 18/03/2018                                                 **/
/** Led Driver Source File                                            **/
/**                                                                   **/
/***********************************************************************/

#include "led.h"
#include "defines.h"

#define FACTOR_TO_MICROSEG      1000

void initLed(Led              * pLed,
             LedOutFunction     outFunction,
             unsigned char      isEnableInLow,
             unsigned long      delay,
             unsigned long      mainDelay)
{
    if (pLed != NULL)
    {
        pLed->turnOn = 0;
        pLed->outFunction = outFunction;
        pLed->isEnableInLow = isEnableInLow;
        pLed->delay = delay;
        pLed->mainDelay = mainDelay;

        pLed->counter = pLed->delay * FACTOR_TO_MICROSEG / pLed->mainDelay;
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

        if (pLed->isEnableInLow)
        {
            pLed->outFunction(!pLed->turnOn); 
        }
        else
        {
            pLed->outFunction(pLed->turnOn);
        }
    }
}

void turnOnOffLedAuto(Led  * pLed)
{
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

            if (pLed->isEnableInLow)
            {
                pLed->outFunction(!pLed->turnOn); 
            }
            else
            {
                pLed->outFunction(pLed->turnOn);
            }

            pLed->counter = pLed->delay * FACTOR_TO_MICROSEG / pLed->mainDelay;
        }
        else
        {
            pLed->counter--;
        }
    }
}

