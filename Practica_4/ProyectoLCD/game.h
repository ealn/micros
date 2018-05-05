/*
 * game.h
 *
 *  Created on: 28/04/2018
 *      Author: jpaco
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>

//////////////////////////////////////////////
// Public functions
//////////////////////////////////////////////

void GAME_Init(void);
void GAME_Run(uint8_t btn);


//////////////////////////////////////////////
// Internal functions
//////////////////////////////////////////////
void GAME__AddRandomObstacle(uint16_t seed);
void GAME__DrawScenario(void);
void GAME__ScenarioStep(void);
uint8_t GAME__DetectCollision(void);
void GAME__MoveKart(uint8_t btn);

//////////////////////////////////////////////
// State machine internal states
//////////////////////////////////////////////
typedef enum
{
    INIT = 0,
    WAITSTART,
    STEP1,
    STEP2,
    GAMEOVER,
    WINNER

}game_t;

#define GAME_DELAYS_PER_LEVELSTEP   2
#define GAME_MAXDELAYS              8
#define GAME_COUNTS_TO_PASS_LEVEL   50
#define GAME_COUNTS_GAMEOVER        200

#define GAME_KART_ICON              0
#define GAME_OBS_ICON               1

#endif /* GAME_H_ */
