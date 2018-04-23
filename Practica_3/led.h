/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Led Driver Header File                                            **/
/**                                                                   **/
/***********************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _LED_H_
#define _LED_H_

typedef void (*LedOutFunction)(unsigned char turnOn);

typedef struct __Led
{
    unsigned char      turnOn;         // is turn on the led
    LedOutFunction     outFunction;    // Function to turn on/off the led
    unsigned long      delay;          // Delay in ms (0 means forever)
    unsigned long      counter;        // Counter
    unsigned long      mainDelay;      // Main delay in ns
}Led;

void initLed(Led              * pLed,
             LedOutFunction     outFunction,
             unsigned long      delay,
             unsigned long      mainDelay);

void turnOnOffLed(Led  * pLed, unsigned char turnOn);

void turnOnOffLedAuto(Led  * pLed);

#endif /* ifndef _LED_H_ */

#ifdef __cplusplus
}
#endif
