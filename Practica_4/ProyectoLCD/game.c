/*
 * game.c
 *
 *  Created on: 28/04/2018
 *      Author: jpaco
 */


#include "game.h"
#include "lcd.h"

static uint8_t scenario[32];
static const uint8_t initialMsg[32] = {' ',' ',' ',' ',' ','P','R','E','S','S',' ',' ',' ',' ',' ',' ',
                                       ' ',' ','B','O','T','H',' ','B','U','T','T','O','N','S',' ',' '};
static const uint8_t winnerMsg[32] = {' ',' ',' ',' ',' ',' ','Y','O','U',' ',' ',' ',' ',' ',' ',' ',
                                      ' ',' ',' ',' ',' ','W',' ','O',' ','N',' ',' ',';',')',' ',' '};
static const uint8_t loserMsg[32] = {' ',' ',' ',' ',' ',' ','Y','O','U',' ',' ',' ',' ',' ',' ',' ',
                                     ' ',' ',' ',' ','L',' ','O',' ','S',' ','T',' ',':','(',' ',' '};

static game_t GAME__StateM = 0;

static GAME__kartpos = 0;


//////////////////////////////////////////////
// Public functions
//////////////////////////////////////////////

void GAME_Init(void)
{
    uint8_t i;

    for(i=0; i<32; i++)
        scenario[i] = ' ';

    GAME__StateM = INIT;
    GAME__kartpos = 0;

    return;
}

void GAME_Run(uint8_t btn)
{
    uint8_t collision = 0;
    static uint8_t delay = 0;
    static uint8_t currentLevel = 0;
    static uint8_t levelCounts = 0;
    static uint16_t seed_randomgen = 0;

    switch(GAME__StateM)
    {
    case INIT:
        GAME_Init();
        LCD_WriteMsg(&initialMsg, 32);
        GAME__StateM = WAITSTART;
        break;
    case WAITSTART:
        if(0==btn) //Btn pressed
        {
            GAME__DrawScenario();
            currentLevel = 1;
            levelCounts = 0;
            delay = GAME_MAXDELAYS - (currentLevel * GAME_DELAYS_PER_LEVELSTEP);
            GAME__StateM = STEP1;
        }
        else
        {
            // No transition
            seed_randomgen++; // seed for random obstacle creation
        }
        break;

    case STEP1:
        // Move Kart according to user buttons
        GAME__MoveKart(btn);
        // Draw scenario
        GAME__DrawScenario();

        if(0 == delay)
        {
            // Reload timer delay
            delay = GAME_MAXDELAYS - (currentLevel * GAME_DELAYS_PER_LEVELSTEP);
            // Move scenario
            GAME__ScenarioStep();
            // Add obstacle
            GAME__AddRandomObstacle(seed_randomgen);
            // Pass to animation step 2
            GAME__StateM = STEP2;
        }
        else
        {
            delay--;
        }
        break;

    case STEP2:
        // Move Kart according to user buttons
        GAME__MoveKart(btn);
        // Draw scenario
        GAME__DrawScenario();

        if(0 == delay)
        {
            // Reload timer delay
            delay = GAME_MAXDELAYS - (currentLevel * GAME_DELAYS_PER_LEVELSTEP);
            // Move scenario
            GAME__ScenarioStep();
            // Detect collision
            collision = GAME__DetectCollision();
            // Game transitions
            if (0 != collision)
            {
                GAME__StateM = GAMEOVER;
                delay=10;
            }
            else if (GAME_COUNTS_TO_PASS_LEVEL == levelCounts)
            {
                if(3 == currentLevel)
                {
                    GAME__StateM = WINNER;
                    delay=10;
                }
                else
                {
                    // Advance level
                    currentLevel++;
                    levelCounts = 0;
                }
            }

            // Pass to animation step 1
            if(GAME__StateM == STEP2) //No win or lost
                GAME__StateM = STEP1;
        }
        else
        {
            delay--;
        }
        break;

    case GAMEOVER:
        // You lost!
        LCD_WriteMsg(loserMsg, 32);
        if(0 == delay)
        {
            // Pass to Init screen
            GAME__StateM = INIT;
        }
        else
        {
            delay--;
        }
        break;
    case WINNER:
        // You won!!!!
        LCD_WriteMsg(winnerMsg, 32);
        if(0 == delay)
        {
            // Pass to Init screen
            GAME__StateM = INIT;
        }
        else
        {
            delay--;
        }
        break;

    default:
        break;
    }

    return;
}


//////////////////////////////////////////////
// Internal functions
//////////////////////////////////////////////

void GAME__AddRandomObstacle(uint16_t seed)
{
    static uint16_t magicnumber = 0x83A6;

    magicnumber += seed;

    // Add obstacle
    if(magicnumber&0x02)
        scenario[15] = GAME_OBS_ICON;
    else
        scenario[31] = GAME_OBS_ICON;
}
void GAME__DrawScenario(void)
{
    LCD_WriteMsg(scenario, 32);
}

void GAME__ScenarioStep(void)
{
    uint8_t i;

    for(i=0;i<=32;i++)
    {
        if(i==15||i==31)
            scenario[i] = ' ';
        else
            scenario[i] = scenario[i+1];
    }
}

uint8_t GAME__DetectCollision(void)
{
    if(scenario[0]==GAME_OBS_ICON && GAME__kartpos==0)
        return 1; //Collision
    else if(scenario[16]==GAME_OBS_ICON && GAME__kartpos==16)
        return 1; //Collision
    else
        return 0;
}

void GAME__MoveKart(uint8_t btn)
{
    scenario[0]=' ';
    scenario[16]=' ';

    //Logic for only 1 button
    if(btn==0) //Button pressed
    {
        if(GAME__kartpos==0)
            GAME__kartpos=16;
        else
            GAME__kartpos=0;
    }

    scenario[GAME__kartpos]=GAME_KART_ICON;

}
