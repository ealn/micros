/***********************************************************************/
/**************** Practica #2 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Queue Source File                                                 **/
/**                                                                   **/
/***********************************************************************/

#include "queue.h"
#include "defines.h"

#define   NUMBER_BLOCKS          256                            //-> 256b

unsigned short g_numBytesUsedQueue = 0;

//Reserve space for the stack
unsigned char g_queue[NUMBER_BLOCKS];

//Pointers
unsigned char * g_currentQueueEntry = g_queue;

void queueInit(void)
{
    unsigned short i = 0;
    unsigned char *entry = g_queue;

    //clean memory
    while (i < NUMBER_BLOCKS)
    {
        *entry = 0;
        entry++;
        i++;
    }

    g_currentQueueEntry = g_queue;
    g_numBytesUsedQueue = 0;
}

unsigned short enqueue(char* data, unsigned short size)
{
    unsigned short retSize = 0;
    unsigned short i = 0;

    if (size > (NUMBER_BLOCKS - g_numBytesUsedQueue))
    {
        retSize = NUMBER_BLOCKS - g_numBytesUsedQueue;
    }
    else
    {
        retSize = size;
    }

    if (retSize > 0)
    {
        while (i < retSize) 
        {
            *g_currentQueueEntry = *data;
            g_currentQueueEntry++;
            data++;
            i++;
        }

        g_numBytesUsedQueue += retSize; 
    }

    return retSize; 
}

unsigned short dequeue(char* data, unsigned short size)
{
    unsigned short retSize = 0;
    unsigned short i = 0;

    if (g_numBytesUsedQueue > 0)
    {
        if (size > g_numBytesUsedQueue)
        {
            retSize = g_numBytesUsedQueue;
        }
        else
        {
            retSize = size;
        }

        if (retSize > 0)
        {
            while (i < retSize) 
            {
                *data = *g_currentQueueEntry;
                g_currentQueueEntry--;
                data++;
                i++;
            }
            
            g_numBytesUsedQueue -= retSize; 
        }
    }

    return retSize;
}


