/*
 * lcd.h
 *
 *  Created on: 28/04/2018
 *      Author: jpaco
 */

#ifndef LCD_H_
#define LCD_H_


typedef struct
{
    uint8_t nextState;
    uint8_t prevState;
}LCDStateM;

#define LCD_OK      0
#define LCD_BUSY    1
#define LCD_ERROR   2

uint8_t LCD_Init(void);
uint8_t LCD_WriteMsg(uint8_t* bpData, uint8_t bDataSize);
uint8_t LCD_GotoXY(uint8_t bLCDX, uint8_t bLCDY);
uint8_t LCD_WriteData(uint8_t bDataTemp);
uint8_t LCD_WriteCmd(uint8_t bDataTemp);
void LCD_RunSM(void);


//////////////////////////////////////////////
// Internal functions
//////////////////////////////////////////////

static uint8_t LCD__RequestSM(void (*fn)(void));
static uint8_t LCD__ReleaseSM();

// State functions
static void LCD__InitSM(void);
static void LCD__WriteMsgSM(void);
static void LCD__GotoXYSM(void);
static void LCD__WriteDataSM(void);
static void LCD__WriteCMDSM(void);
static void LCD__IdleSM(void);




#endif /* LCD_H_ */
