/***********************************************************************/
/**************** Practica #2 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Stack Source File                                                 **/
/**                                                                   **/
/***********************************************************************/

#include "stack.h"

#define   NUMBER_BLOCKS          256                            //-> 256b

unsigned short g_numBytesUsed = 0;

//Reserve space for the stack
unsigned char g_stack[NUMBER_BLOCKS];

//Pointers
unsigned char * g_currentStackEntry = g_stack;

void stackInit(void)
{
    unsigned short i = 0;
    unsigned char *entry = g_stack;

    //clean memory
    while (i < NUMBER_BLOCKS)
    {
        *entry = 0;
        entry++;
        i++;
    }

    g_currentStackEntry = g_stack;
    g_numBytesUsed = 0;
}

unsigned char stackPush(char* data, unsigned short size)
{
    unsigned char retSize = 0;
    unsigned short i = 0;

    if (size > (NUMBER_BLOCKS - g_numBytesUsed))
    {
        retSize = NUMBER_BLOCKS - g_numBytesUsed;
    }
    else
    {
        retSize = size;
    }

    if (retSize > 0)
    {
        while (i < retSize) 
        {
            *g_currentStackEntry = *data;
            g_currentStackEntry++;
            data++;
            i++;
        }

        g_numBytesUsed += retSize; 
    }

    return retSize; 
}

unsigned char stackPop(char* data, unsigned short size)
{
    unsigned char retSize = 0;
    unsigned short i = 0;

    if (g_numBytesUsed > 0)
    {
        if (size > g_numBytesUsed)
        {
            retSize = g_numBytesUsed;
        }
        else
        {
            retSize = size;
        }

        if (retSize > 0)
        {
            while (i < retSize) 
            {
                *data = *g_currentStackEntry;
                g_currentStackEntry--;
                data++;
                i++;
            }
            
            g_numBytesUsed -= retSize; 
        }
    }

    return retSize;
}


