/***********************************************************************/
/**************** Practica #3 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autores: Efrain Adrian Luna Nevarez                               **/
/**          Jose Francisco Velazquez Aguirre                         **/
/** Fecha: 18/03/2018                                                 **/
/** Frecuenciometro Main Source File                                  **/
/**                                                                   **/
/** Minimos tiempos de poleo:                                         **/
/**                                                                   **/
/** Frecuenciometro = 9999Hz = 50 microseg                            **/
/** Display = 3.5 miliseg                                             **/
/** Led parpadeando = 1Hz = 1 seg                                     **/
/** Led señal de entrada = 100Hz = 10 mseg                            **/
/** Button = 100 mseg                                                 **/
/***********************************************************************/
#include "button.h"
#include "display.h"
#include "led.h"
#include <16f877A.h>
#fuses XT,NOWDT,NOPROTECT,PUT
#use delay(clock=4000000)
#use fast_io(b)
#use fast_io(c)
#byte portb=0x06
#byte portd=0x08
#bit  ra0=5.0
#bit  ra1=5.1
#bit  ra2=5.2
#bit  ra3=5.3
#bit  rd4=8.4
#bit  rd5=8.5
#bit  rd6=8.6
#bit  rd7=8.7

void configUc(void);
void run(void);
unsigned long getFrecuency(Led *ledActiveSignal, unsigned long mainDelay);
unsigned char updateDisplayValue(unsigned long frecValue,
                                 unsigned long newFrecValue,
                                 DisplayManager * pDisplay,
                                 unsigned char holdFrec,
                                 unsigned char holdMinFrec,
                                 unsigned char holdMaxFrec);

unsigned char buttonInHold(void);
unsigned char buttonInMinFrec(void);
unsigned char buttonInMaxFrec(void);
unsigned char buttonInNormal(void);
void ledAliveOut(unsigned char turnOn);
void ledActiveSignalOut(unsigned char turnOn);
void ledMode1Out(unsigned char turnOn);
void ledMode2Out(unsigned char turnOn);
void displayOut(unsigned char value, unsigned char displayNumber);

void main()
{
   configUc();
   run();
}

void configUc(void)
{
   set_tris_a(0xff);                 //config porta as input
   set_tris_b(0x00);                 //config portb as output
   set_tris_c(0xff);                 //config portc as input
   set_tris_d(0x00);                 //config portd as input 
   set_tris_e(0b0000111);            //config porte as input 
   disable_interrupts(GLOBAL);       //disable interrupts
   portb = 0x00;                     //clean portb
   portd = 0x00;                     //clean portc
}

void run(void)
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
    unsigned long   mainDelay = 50;  //50 microseg
    unsigned long   frecValue = 0;
    unsigned long   newFrecValue = 0;
    unsigned char   holdFrec = 0;
    unsigned char   holdMinFrec = 0;
    unsigned char   holdMaxFrec = 0;
    unsigned char   valueChanged = 0;

    initDisplayManager(&display, 0, 4, 0, displayOut, mainDelay);

    initButton(&buttonHold,     buttonInHold,    0, mainDelay);
    initButton(&buttonMinFrec,  buttonInMinFrec, 0, mainDelay);
    initButton(&buttonMaxFrec,  buttonInMaxFrec, 0, mainDelay);
    initButton(&buttonNormal,   buttonInNormal,  0, mainDelay);

    initLed(&ledAlive,          ledAliveOut,        0,   1000, mainDelay);
    initLed(&ledActiveSignal,   ledActiveSignalOut, 0,   10,   mainDelay);
    initLed(&ledMode1,          ledMode1Out,        0,   0,    mainDelay);
    initLed(&ledMode2,          ledMode2Out,        0,   0,    mainDelay);

    //big main loop
    for (;;)
    {
        turnOnOffLedAuto(&ledAlive);

        newFrecValue = getFrecuency(&ledActiveSignal, mainDelay);

        valueChanged = updateDisplayValue(frecValue,
                                          newFrecValue,
                                          &display,
                                          holdFrec,
                                          holdMinFrec,
                                          holdMaxFrec);
        if (valueChanged)
        {
            frecValue = newFrecValue;
        }

        refreshDisplay(&display);

        if (checkButton(&buttonHold))
        {
            holdFrec = 1;
            holdMinFrec = 0;
            holdMaxFrec = 0;

            turnOnOffLed(&ledMode1, 1);
            turnOnOffLed(&ledMode2, 1);
        }
        else if (checkButton(&buttonMinFrec))
        {
            holdFrec = 0;
            holdMinFrec = 1;
            holdMaxFrec = 0;

            turnOnOffLed(&ledMode1, 0);
            turnOnOffLed(&ledMode2, 1);
        }
        else if (checkButton(&buttonMaxFrec))
        {
            holdFrec = 0;
            holdMinFrec = 0;
            holdMaxFrec = 1;

            turnOnOffLed(&ledMode1, 1);
            turnOnOffLed(&ledMode2, 0);
        }
        else if (checkButton(&buttonNormal))
        {
            holdFrec = 0;
            holdMinFrec = 0;
            holdMaxFrec = 0;

            turnOnOffLed(&ledMode1, 0);
            turnOnOffLed(&ledMode2, 0);
        }

        //main delay
        delay_us(mainDelay);
    } 
}

unsigned long getFrecuency(Led *ledActiveSignal, unsigned long mainDelay)
{
    static unsigned long counterHigh = 0;
    static unsigned long counterLow = 0;

    //if entry is 1
    if (1)
    {
        if (ledActiveSignal != 0)
        {
            turnOnOffLed(ledActiveSignal, 1);
        }

        //there is a transition
        if (counterLow != 0)
        {
            //calculate frecuency divide 1 sec 
            frec = 1000000 / (mainDelay * (counterHigh + counterLow));

            counterHigh = 0;
            counterLow = 0;
        }

        counterHigh++;
    }
    else
    {
        if (ledActiveSignal != 0)
        {
            turnOnOffLed(ledActiveSignal, 0);
        }

        counterLow++;
    }

    return frec;
}

unsigned char updateDisplayValue(unsigned long frecValue,
                                 unsigned long newFrecValue,
                                 DisplayManager * pDisplay,
                                 unsigned char holdFrec,
                                 unsigned char holdMinFrec,
                                 unsigned char holdMaxFrec)
{
    unsigned char ret = 0;

    if (!holdFrec)
    {
        if (holdMinFrec)
        {
           if (newFrecValue < frecValue)
           {
               ret = updateDisplay(pDisplay, newFrecValue); 
           }
        }
        else if (holdMaxFrec)
        {
           if (newFrecValue > frecValue)
           {
               ret = updateDisplay(pDisplay, newFrecValue); 
           }
        }
        else
        {
           ret = updateDisplay(pDisplay, newFrecValue); 
        }
    }

    return ret;
}

void displayOut(unsigned char value, unsigned char displayNumber)
{   
    //clean port
    portd &= 0xF0;
    
    switch (displayNumber)
    {
        case 1: portd |= 0x01;
            break;
        case 2: portd |= 0x02;
            break;
        case 3: portd |= 0x04;
            break;
        case 4: portd |= 0x08;
            break;
    }
    
    portb = value;
}

unsigned char buttonInHold(void)
{
    unsigned char ret = 0;
    
    if (ra0 == 0)
    {
        ret = 1;
    }
    
    return ret;
}

unsigned char buttonInMinFrec(void)
{
    unsigned char ret = 0;
    
    if (ra1 == 0)
    {
        ret = 1;
    }
    
    return ret;
}

unsigned char buttonInMaxFrec(void)
{
    unsigned char ret = 0;
    
    if (ra2 == 0)
    {
        ret = 1;
    }
    
    return ret;
}

unsigned char buttonInNormal(void)
{
    unsigned char ret = 0;
    
    if (ra3 == 0)
    {
        ret = 1;
    }
    
    return ret;
}

void ledAliveOut(unsigned char turnOn)
{
    rd4 = turnOn;
}

void ledActiveSignalOut(unsigned char turnOn)
{
    rd5 = turnOn;
}

void ledMode2Out(unsigned char turnOn)
{
    rd6 = turnOn;
}

void ledMode1Out(unsigned char turnOn)
{
    rd7 = turnOn;
}

