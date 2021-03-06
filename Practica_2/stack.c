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
#include "defines.h"

#define   NUMBER_BLOCKS          256                            //-> 256b

unsigned short g_numBytesUsedStack = 0;

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
    g_numBytesUsedStack = 0;
}

unsigned short stackPush(char* data, unsigned short size)
{
    unsigned short retSize = 0;
    unsigned short i = 0;

    if (size > (NUMBER_BLOCKS - g_numBytesUsedStack))
    {
        retSize = NUMBER_BLOCKS - g_numBytesUsedStack;
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

        g_numBytesUsedStack += retSize; 
    }

    return retSize; 
}

unsigned short stackPop(char* data, unsigned short size)
{
    unsigned short retSize = 0;
    unsigned short i = 0;

    if (g_numBytesUsedStack > 0)
    {
        if (size > g_numBytesUsedStack)
        {
            retSize = g_numBytesUsedStack;
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
            
            g_numBytesUsedStack -= retSize; 
        }
    }

    return retSize;
}


