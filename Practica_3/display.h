/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Display Driver Header File                                        **/
/**                                                                   **/
/***********************************************************************/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

typedef void (*DisplayOutFunction)(unsigned char value, unsigned char displayNumber);

typedef struct __DisplayManager
{
    unsigned long      value;
    unsigned char      numberOfDisplays;
    DisplayOutFunction outFunction;
    unsigned long      counter;       // Counter
    unsigned long      mainDelay;     // Main delay in ns
}DisplayManager;

void initDisplayManager(DisplayManager   * pDisplayManager,
                        unsigned long      value,
                        unsigned char      numberOfDisplays,
                        DisplayOutFunction outFunction,
                        unsigned long      mainDelay);

void updateDisplay(DisplayManager * pDisplayManager, unsigned long value);

#endif /* ifndef _DISPLAY_H_ */
