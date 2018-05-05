/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autores: Efrain Adrian Luna Nevarez                               **/
/**          Jose Francisco Velazquez Aguirre                         **/
/** Fecha: 18/03/2018                                                 **/
/** Display Driver Header File                                        **/
/**                                                                   **/
/***********************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

typedef void (*DisplayOutFunction)(unsigned char value, unsigned char displayNumber);

typedef struct __DisplayManager
{
    unsigned long      value;            // Display value
    unsigned char      numberOfDisplays; // Number of displays
    unsigned char      isEnableInLow;    // True if the display is anode commun
    DisplayOutFunction outFunction;      // output function
    unsigned long      refreshCounter;   // Refresh counter
    unsigned long      updateCounter;    // Update counter
    unsigned long      mainDelay;        // Main delay in microseg
}DisplayManager;

void initDisplayManager(DisplayManager   * pDisplayManager,
                        unsigned long      value,
                        unsigned char      numberOfDisplays,
                        unsigned char      isEnableInLow,
                        DisplayOutFunction outFunction,
                        unsigned long      mainDelay);

unsigned char updateDisplay(DisplayManager * pDisplayManager, unsigned long value);

unsigned char refreshDisplay(DisplayManager * pDisplayManager);

#endif /* ifndef _DISPLAY_H_ */

#ifdef __cplusplus
}
#endif
