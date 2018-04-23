/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Frecuenciometro Main Source File                                  **/
/**                                                                   **/
/** Minimos tiempos de poleo:                                         **/
/**                                                                   **/
/** Frecuenciometro = 9999kHz = 100 nseg                              **/
/** Display                                                           **/
/** Led parpadeando = 1Hz = 1 seg                                     **/
/** Led señal de entrada = 100Hz = 10 mseg                            **/
/** Button = 100 mseg                                                 **/
/***********************************************************************/

#include "button.h"
#include "display.h"
#include "led.h"

void configMC(void);

unsigned char buttonInHold(void);
unsigned char buttonInMinFrec(void);
unsigned char buttonInMaxFrec(void);
unsigned char buttonInNormal(void);
void ledAliveOut(unsigned char turnOn);
void ledActiveSignalOut(unsigned char turnOn);
void ledMode1Out(unsigned char turnOn);
void ledMode2Out(unsigned char turnOn);
void displayOut(unsigned char value, unsigned char displayNumber);

int main(void)
{
    DisplayManager  display;
    Button          buttonHold;
    Button          buttonMinFrec;
    Button          buttonMaxFrec;
    Button          buttonNormal;
    Led             ledAlive;
    Led             ledActiveSignal;
    Led             ledMode1;
    Led             ledMode2;
    unsigned long   mainDelay = 100;  //100 nseg
    unsigned long   frecValue = 0;
    unsigned long   newFrecValue = 0;
    unsigned char   lockFrec = 0;
    unsigned char   lockMinFrec = 0;
    unsigned char   lockMaxFrec = 0;

    initDisplayManager(&display, 0, 4, displayOut, mainDelay);

    initButton(&buttonHold,     buttonInHold,    0, mainDelay);
    initButton(&buttonMinFrec,  buttonInMinFrec, 0, mainDelay);
    initButton(&buttonMaxFrec,  buttonInMaxFrec, 0, mainDelay);
    initButton(&buttonNormal,   buttonInNormal,  0, mainDelay);

    initLed(&ledAlive,          ledAliveOut,         1000, mainDelay);
    initLed(&ledActiveSignal,   ledActiveSignalOut,  10,   mainDelay);
    initLed(&ledMode1,          ledMode1Out,         0,    mainDelay);
    initLed(&ledMode2,          ledMode2Out,         0,    mainDelay);

    configMC();

    //big main loop
    for (;;)
    {
        turnOnOffLedAuto(&ledActiveSignal);
        turnOnOffLedAuto(&ledAlive);

        if (!lockFrec)
        {
            if (lockMinFrec)
            {
                if (newFrecValue < frecValue)
                {
                    frecValue = newFrecValue;
                    updateDisplay(&display, frecValue); 
                }
            }
            else if (lockMaxFrec)
            {
                if (newFrecValue > frecValue)
                {
                    frecValue = newFrecValue;
                    updateDisplay(&display, frecValue); 
                }
            }
            else
            {
                frecValue = newFrecValue;
                updateDisplay(&display, frecValue); 
            }
        }

        if (checkButton(&buttonHold))
        {
            lockFrec = 1;
            lockMinFrec = 0;
            lockMaxFrec = 0;

            turnOnOffLed(&ledMode1, 1);
            turnOnOffLed(&ledMode2, 1);
        }
        else if (checkButton(&buttonMinFrec))
        {
            lockFrec = 0;
            lockMinFrec = 1;
            lockMaxFrec = 0;

            turnOnOffLed(&ledMode1, 0);
            turnOnOffLed(&ledMode2, 1);
        }
        else if (checkButton(&buttonMaxFrec))
        {
            lockFrec = 0;
            lockMinFrec = 0;
            lockMaxFrec = 1;

            turnOnOffLed(&ledMode1, 1);
            turnOnOffLed(&ledMode2, 0);
        }
        else if (checkButton(&buttonNormal))
        {
            lockFrec = 0;
            lockMinFrec = 0;
            lockMaxFrec = 0;

            turnOnOffLed(&ledMode1, 0);
            turnOnOffLed(&ledMode2, 0);
        }

        //main delay
        //delay(mainDelay);
    }

    return 0;
}

void configMC(void)
{
    //Config Microcontroller
}

void displayOut(unsigned char value, unsigned char displayNumber)
{
    //TODO:
}

unsigned char buttonInHold(void)
{
    //TODO:
    return 0;
}

unsigned char buttonInMinFrec(void)
{
    //TODO:
    return 0;
}

unsigned char buttonInMaxFrec(void)
{
    //TODO:
    return 0;
}

unsigned char buttonInNormal(void)
{
    //TODO:
    return 0;
}

void ledAliveOut(unsigned char turnOn)
{

}

void ledActiveSignalOut(unsigned char turnOn)
{

}

void ledMode1Out(unsigned char turnOn)
{

}

void ledMode2Out(unsigned char turnOn)
{

}

