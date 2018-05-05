/*
 * lcd.c
 *
 *  Created on: 28/04/2018
 *      Author: jpaco
 */

#include <stdint.h>
#include "CustomIOWrapper.h"
#include "lcd.h"

//////////////////////////////////////////////
// Internal variables
//////////////////////////////////////////////
static uint8_t LCD__WriteMsg_bpData[32];
static uint8_t LCD__WriteMsg_bpDataSize;
static uint8_t LCD__GotoXY_bLCDX;
static uint8_t LCD__GotoXY_bLCDY;
static uint8_t LCD__WriteData_bDataTemp;
static uint8_t LCD__WriteCmd_bDataTemp;
static uint8_t LCD__WriteMsgSM_secondline=0;
static uint8_t LCD__WriteMsgSM_firstchar=0;
static uint8_t LCD__WriteMsgSM_counter=0;

static void (*LCD_mainSM)(void);
static void (*LCD_nextSM)(void);

//////////////////////////////////////////////
// Interface functions
//////////////////////////////////////////////

uint8_t LCD_Init(void)
{
    LCD_mainSM = &LCD__InitSM;
    LCD_nextSM = &LCD__IdleSM;

    return 0;
}

uint8_t LCD_WriteMsg(uint8_t* bpData, uint8_t bDataSize)
{
    uint8_t index;

    // Copy parameters to internal variables
    LCD__WriteMsg_bpDataSize = bDataSize;
    for(index=0; index<=(bDataSize-1); index++)
        LCD__WriteMsg_bpData[index]=bpData[index];

    //Init vars to be used by state machine
    LCD__WriteMsgSM_firstchar=0;
    LCD__WriteMsgSM_secondline=0;
    LCD__WriteMsgSM_counter=0;

    // Request internal state machine transition
    return LCD__RequestSM(LCD__WriteMsgSM);
}

uint8_t LCD_GotoXY(uint8_t bLCDX, uint8_t bLCDY)
{
    // Copy parameters to internal variables
    LCD__GotoXY_bLCDX = bLCDX;
    LCD__GotoXY_bLCDY = bLCDY;

    // Request internal state machine transition
    return LCD__RequestSM(LCD__GotoXYSM);
}

uint8_t LCD_WriteData(uint8_t bDataTemp)
{
    // Copy parameters to internal variables
    LCD__WriteData_bDataTemp = bDataTemp;

    // Request internal state machine transition
    return LCD__RequestSM(LCD__WriteDataSM);
}

uint8_t LCD_WriteCmd(uint8_t bDataTemp)
{
    // Copy parameters to internal variables
    LCD__WriteCmd_bDataTemp = bDataTemp;

    // Request internal state machine transition
    return LCD__RequestSM(LCD__WriteCMDSM);
}


void LCD_RunSM(void)
{
    LCD_mainSM();
}


//////////////////////////////////////////////
// Internal functions
//////////////////////////////////////////////

static uint8_t LCD__RequestSM(void (*newSM)(void))
{
    uint8_t retcode = LCD_ERROR;

    if(LCD_mainSM == &LCD__IdleSM)
    {
        LCD_mainSM = newSM;
        retcode = LCD_OK;
    }
    else if(LCD_nextSM == &LCD__IdleSM)
    {
        LCD_nextSM = newSM;
        retcode = LCD_BUSY;
    }
    else
    {
        retcode = LCD_ERROR;
    }

    return retcode;
}

static uint8_t LCD__ReleaseSM()
{
    // Pass to the next SM
    // If already DNE, LCD_nextSM will be LCD__IdleSM too
    LCD_mainSM = LCD_nextSM;
    LCD_nextSM = &LCD__IdleSM;
}

static void LCD__InitSM()
{
    static uint8_t state = 0;
    static uint8_t delay_ctr = 0;
    static uint8_t cmd_ctr = 0;
    const uint8_t initcommands[8] = {   0x33, //
                                        0x32, //
                                        0x28, //4-bit mode
                                        0x0E, //clear the screen
                                        0x01, //display on cursor off
                                        0x06, //increment cursor
                                        0x80 //row 1 column 1
                              };
    const uint8_t kart_char[8] = {
                                  0b00000,
                                  0b01000,
                                  0b01100,
                                  0b01010,
                                  0b01010,
                                  0b01100,
                                  0b01000,
                                  0b00000
                              };
    const uint8_t obs_char[8] = {
                                 0b01010,
                                 0b01110,
                                 0b01010,
                                 0b01110,
                                 0b01110,
                                 0b01010,
                                 0b01110,
                                 0b01010
                             };

    switch(state)
    {
    // Initialization for 4-bit operation
    case 0:
        // Initial 15 ms delay
        if(delay_ctr == 15)
        {
            delay_ctr=0;
            state++;
        }
        else
            delay_ctr++;
        break;
    case 1:
        if(cmd_ctr<=6)
        {
            // send for initialization of LCD for nibble (4-bit) mode
            LCD__ReleaseSM();                       // Temporarily release SM so that Write Data SM can be called
            LCD_WriteCmd(initcommands[cmd_ctr]);    // WriteCMD State Machine
            LCD__RequestSM(&LCD__InitSM);       // To come back when Write Data SM is done
            cmd_ctr++;
        }
        else
            state++;
        break;
    case 2:
        // Set in CGRAM the first custom characters
        LCD__ReleaseSM();
        LCD_WriteCmd(0x40);    // Store in address 0x40 (1st character)
        LCD__RequestSM(&LCD__InitSM);
        state++;
        cmd_ctr=0;
        break;
    case 3:
        if(cmd_ctr<=7)
        {
            LCD__ReleaseSM();
            LCD_WriteData(kart_char[cmd_ctr]);    // Send byte to byte character info
            LCD__RequestSM(&LCD__InitSM);
            cmd_ctr++;
        }
        else
            state++;
        break;
    case 4:
        // Set in CGRAM the second custom characters
        LCD__ReleaseSM();
        LCD_WriteCmd(0x48);    // Store in address 0x48 (2nd character)
        LCD__RequestSM(&LCD__InitSM);
        state++;
        cmd_ctr=0;
        break;
    case 5:
        if(cmd_ctr<=7)
        {
            LCD__ReleaseSM();
            LCD_WriteData(obs_char[cmd_ctr]);    // Send byte to byte character info
            LCD__RequestSM(&LCD__InitSM);
            cmd_ctr++;
        }
        else
            state++;
        break;
    case 6:
        state=0;
        LCD__ReleaseSM(); // Release Init State Machine control
        break;

    }
}

static void LCD__WriteMsgSM()
{
    if(LCD__WriteMsgSM_counter<LCD__WriteMsg_bpDataSize)
    {
        if(LCD__WriteMsgSM_firstchar==0)
        {
            LCD__ReleaseSM(); // Temporarily release SM so that Write Data SM can be called
            LCD_WriteCmd(0x80); //Go to first line
            LCD__RequestSM(&LCD__WriteMsgSM); // To come back when Write Data SM is done
            LCD__WriteMsgSM_firstchar=1;
        }
        else if(LCD__WriteMsgSM_counter==16 && LCD__WriteMsgSM_secondline==0)
        {
            LCD__ReleaseSM(); // Temporarily release SM so that Write Data SM can be called
            LCD_WriteCmd(0xC0);
            LCD__RequestSM(&LCD__WriteMsgSM); // To come back when Write Data SM is done
            LCD__WriteMsgSM_secondline=1;
        }
        else
        {
            LCD__ReleaseSM(); // Temporarily release SM so that Write Data SM can be called
            LCD_WriteData(LCD__WriteMsg_bpData[LCD__WriteMsgSM_counter]);
            LCD__RequestSM(&LCD__WriteMsgSM); // To come back when Write Data SM is done
            LCD__WriteMsgSM_counter++;
        }
    }
    else
    {
        LCD__ReleaseSM(); // We are done now
    }
}

static void LCD__GotoXYSM()
{
}

static void LCD__WriteDataSM()
{
    static uint8_t state = 0;

    switch(state)
    {
    case 0:
        OUTPUT_HIGH(LCD_PIN_RS);
        if(LCD__WriteData_bDataTemp&0x80){OUTPUT_HIGH(LCD_PIN_DATA7);}else{OUTPUT_LOW(LCD_PIN_DATA7);}
        if(LCD__WriteData_bDataTemp&0x40){OUTPUT_HIGH(LCD_PIN_DATA6);}else{OUTPUT_LOW(LCD_PIN_DATA6);}
        if(LCD__WriteData_bDataTemp&0x20){OUTPUT_HIGH(LCD_PIN_DATA5);}else{OUTPUT_LOW(LCD_PIN_DATA5);}
        if(LCD__WriteData_bDataTemp&0x10){OUTPUT_HIGH(LCD_PIN_DATA4);}else{OUTPUT_LOW(LCD_PIN_DATA4);}
        OUTPUT_HIGH(LCD_PIN_E);
        state++;
        break;
    case 1:
        OUTPUT_LOW(LCD_PIN_E);
        state++;
        break;
    case 2:
        OUTPUT_HIGH(LCD_PIN_RS);
        if(LCD__WriteData_bDataTemp&0x08){OUTPUT_HIGH(LCD_PIN_DATA7);}else{OUTPUT_LOW(LCD_PIN_DATA7);}
        if(LCD__WriteData_bDataTemp&0x04){OUTPUT_HIGH(LCD_PIN_DATA6);}else{OUTPUT_LOW(LCD_PIN_DATA6);}
        if(LCD__WriteData_bDataTemp&0x02){OUTPUT_HIGH(LCD_PIN_DATA5);}else{OUTPUT_LOW(LCD_PIN_DATA5);}
        if(LCD__WriteData_bDataTemp&0x01){OUTPUT_HIGH(LCD_PIN_DATA4);}else{OUTPUT_LOW(LCD_PIN_DATA4);}
        OUTPUT_HIGH(LCD_PIN_E);
        state++;
        break;
    case 3:
        OUTPUT_LOW(LCD_PIN_E);
        state++;
        break;
    case 4:
        state=0;
        LCD__ReleaseSM(); // Release Init State Machine control
        break;
    default:
        break;
    }
}

static void LCD__WriteCMDSM()
{
    static uint8_t state = 0;

    switch(state)
    {
    case 0:
        OUTPUT_LOW(LCD_PIN_RS);
        if(LCD__WriteCmd_bDataTemp&0x80){OUTPUT_HIGH(LCD_PIN_DATA7);}else{OUTPUT_LOW(LCD_PIN_DATA7);}
        if(LCD__WriteCmd_bDataTemp&0x40){OUTPUT_HIGH(LCD_PIN_DATA6);}else{OUTPUT_LOW(LCD_PIN_DATA6);}
        if(LCD__WriteCmd_bDataTemp&0x20){OUTPUT_HIGH(LCD_PIN_DATA5);}else{OUTPUT_LOW(LCD_PIN_DATA5);}
        if(LCD__WriteCmd_bDataTemp&0x10){OUTPUT_HIGH(LCD_PIN_DATA4);}else{OUTPUT_LOW(LCD_PIN_DATA4);}
        OUTPUT_HIGH(LCD_PIN_E);
        state++;
        break;
    case 1:
        OUTPUT_LOW(LCD_PIN_E);
        state++;
        break;
    case 2:
        OUTPUT_LOW(LCD_PIN_RS);
        if(LCD__WriteCmd_bDataTemp&0x08){OUTPUT_HIGH(LCD_PIN_DATA7);}else{OUTPUT_LOW(LCD_PIN_DATA7);}
        if(LCD__WriteCmd_bDataTemp&0x04){OUTPUT_HIGH(LCD_PIN_DATA6);}else{OUTPUT_LOW(LCD_PIN_DATA6);}
        if(LCD__WriteCmd_bDataTemp&0x02){OUTPUT_HIGH(LCD_PIN_DATA5);}else{OUTPUT_LOW(LCD_PIN_DATA5);}
        if(LCD__WriteCmd_bDataTemp&0x01){OUTPUT_HIGH(LCD_PIN_DATA4);}else{OUTPUT_LOW(LCD_PIN_DATA4);}
        OUTPUT_HIGH(LCD_PIN_E);
        state++;
        break;
    case 3:
        OUTPUT_LOW(LCD_PIN_E);
        state++;
        break;
    case 4:
        state=0;
        LCD__ReleaseSM(); // Release Init State Machine control
        break;
    default:
        break;
    }
}

static void LCD__IdleSM()
{
    // Intentionally left blank
    // Nothing to be done here
}
