/***********************************************************************/
/**************** Practica #2 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Heap Source File                                                  **/
/**                                                                   **/
/***********************************************************************/

#include "heap.h"
#include "defines.h"

#define   BLOCKS_PER_CTRL_B      4
#define   NUMBER_BLOCKS          256                                    //-> 256b
#define   NUMBER_CONTROL_BLOCKS  NUMBER_BLOCKS/BLOCKS_PER_CTRL_B        //-> 64b
#define   BLOCK_SIZE             sizeof(unsigned char)
#define   BITS_PER_BLOCK         8*BLOCK_SIZE
#define   STEP_SIZE              BITS_PER_BLOCK/BLOCKS_PER_CTRL_B    //byte/BLOCKS_PER_CTRL_B

//Flags control
#define   MEM_USED            0x01
#define   MEM_CONTINUED       0x02

unsigned char g_memInit = 0;
unsigned short g_numBytesAllocated = 0;

//Reserve space for the heap and the memory control
unsigned char g_memory[NUMBER_BLOCKS];
unsigned char g_memoryControl[NUMBER_BLOCKS];

//Memory
unsigned char * g_pMemStart = g_memory;                //Start at the beginning of Memory
unsigned char * g_pMemEnd   = g_memory + (NUMBER_BLOCKS - 1);

//Memory control
unsigned char * g_pMemCtrStart = g_memoryControl;
unsigned char * g_pMemCtrEnd = g_memoryControl + (NUMBER_CONTROL_BLOCKS - 1);

static void setMemBlockUsed(unsigned char *pCtrBlock, unsigned char offset, unsigned char value)
{
    if (pCtrBlock != NULL)
    {
        if (value == 1)
        {
            g_numBytesAllocated++;
            *pCtrBlock |= (MEM_USED << STEP_SIZE*offset); 
        }
        else
        {
            g_numBytesAllocated--;
            *pCtrBlock &= ~(MEM_USED << STEP_SIZE*offset); 
        }
    }
}

static unsigned char isMemBlockUsed(unsigned char *pCtrBlock, unsigned char offset)
{
    return (pCtrBlock != NULL
            && ((*pCtrBlock) & (MEM_USED << STEP_SIZE*offset)));
}

static void setMemBlockContinued(unsigned char *pCtrBlock, unsigned char offset, unsigned char value)
{
    if (pCtrBlock != NULL)
    {
        if (value == 1)
        {
            *pCtrBlock |= (MEM_CONTINUED << STEP_SIZE*offset); 
        }
        else
        {
            *pCtrBlock &= ~(MEM_CONTINUED << STEP_SIZE*offset);
        }
    }
}

static unsigned char isMemBlockContinued(unsigned char *pCtrBlock, unsigned char offset)
{
    return (pCtrBlock != NULL
            && ((*pCtrBlock) & (MEM_CONTINUED << STEP_SIZE*offset)));
}

static void cleanBlock(unsigned char *pBlock)
{
    if (pBlock != NULL)
    {
        *pBlock = 0;
    }
}

static void cleanControlBlock(unsigned char *pBlock, unsigned char offset)
{
    if (pBlock != NULL)
    {
        setMemBlockUsed(pBlock, offset, 0);
        setMemBlockContinued(pBlock, offset, 0);
    }
}

static void initMemory(void)
{
    unsigned char * pMem = g_pMemStart;

    //Clean memory
    while (pMem != g_pMemEnd)
    {
        cleanBlock(pMem);
        pMem++;
    }

    cleanBlock(g_pMemEnd);

    //Clean memory control
    pMem = g_pMemCtrStart;

    while (pMem != g_pMemCtrEnd)
    {
        cleanBlock(pMem);
        pMem++;
    }

    cleanBlock(g_pMemCtrEnd);
}

static unsigned short getMemElementFromMemCtr(unsigned char * pMemCtr, unsigned char offset)
{
    unsigned short ret = 0;
    unsigned char * start = g_pMemCtrStart;
    
    while (start != g_pMemCtrEnd) 
    {
        if (start == pMemCtr)
        {
            break;
        }

        ret++;
        start++;
    }

    ret *= BLOCKS_PER_CTRL_B;
    ret += offset;

    return ret;
}

static unsigned short getMemCtrOffsetFromMem(unsigned char * pMem, unsigned char *offset)
{
    unsigned short ret = 0;
    unsigned char * start = g_pMemStart;

    while (start != g_pMemEnd) 
    {
        if (start == pMem)
        {
            break;
        }

        ret++;
        start++;
    }
    
    if (offset != NULL)
    {
        *offset = ret%BLOCKS_PER_CTRL_B;
        ret = (ret - *offset)/BLOCKS_PER_CTRL_B;
    }
    else
    {
        ret /= BLOCKS_PER_CTRL_B;
    }

    return ret;
}

static unsigned char containsFreeBlocks(unsigned char * ctrlBlock)
{
    unsigned char ret = 0;
    unsigned char offset = 0;

    if (ctrlBlock != NULL)
    {
        while (offset < BLOCKS_PER_CTRL_B)
        {
            if (!isMemBlockUsed(ctrlBlock, offset))
            {
                ret = 1;
                break;
            }

            offset++; 
        }
    }

    return ret;
}

static unsigned short getNumberOfFreeBlocks(unsigned char * start)
{
    unsigned short number = 0;
    unsigned char  offset = 0;

    //search all continues free blocks
    while (start != g_pMemCtrEnd)
    {
        offset = 0;

        if (!containsFreeBlocks(start))
        {
            break;
        }

        while (offset < BLOCKS_PER_CTRL_B)
        {
            if (!isMemBlockUsed(start, offset))
            {
                number++;
            }

            offset++; 
        }

        start++;
    }

    //Search in last control block
    if (start == g_pMemCtrEnd)
    {
        offset = 0;

        while (offset < BLOCKS_PER_CTRL_B)
        {
            if (!isMemBlockUsed(start, offset))
            {
                number++;
            }

            offset++; 
        }
    }

    return number;
}

static unsigned char getFirstOffsetFromFreeBlock(unsigned char * pMemCtr)
{
    unsigned char offset = 0;

    if (pMemCtr != NULL)
    {
        while (offset < BLOCKS_PER_CTRL_B)
        {
            if (!isMemBlockUsed(pMemCtr, offset))
            {
                break;
            }

            offset++; 
        }
    }

    return offset;
}

static unsigned char * getEmptyMemCtrBlock(unsigned short numberOfBlocks, unsigned char *offset)
{
    unsigned char * start = g_pMemCtrStart;
    unsigned char * pEmpty = NULL;

    //search in all enties
    while (start != g_pMemCtrEnd)
    {
        if (getNumberOfFreeBlocks(start) >= numberOfBlocks)
        {
            pEmpty = start;
            break;
        }

        start++; 
    }

    //finaly search in the last entrie
    if (start == g_pMemCtrEnd
        && pEmpty == NULL
        && getNumberOfFreeBlocks(start) >= numberOfBlocks)
    {
        pEmpty = start;
    }

    //get the offset
    if (pEmpty != NULL
        && offset != NULL)
    {
        *offset = getFirstOffsetFromFreeBlock(pEmpty);
    }

    return pEmpty;
}

static void alloc(unsigned char * pCtrBlock, unsigned short numberBlocks, unsigned char offset)
{
    if (pCtrBlock != NULL)
    {
        //set Memory used
        setMemBlockUsed(pCtrBlock, offset, 1);
        numberBlocks--;

        //if we need to allocate more than one block
        if (numberBlocks > 0)
        {
            //set continued
            setMemBlockContinued(pCtrBlock, offset, 1);
            offset++;

            while (numberBlocks > 0)
            {
                if (offset == BLOCKS_PER_CTRL_B)
                {
                    pCtrBlock++;
                    offset = 0; 
                }

                setMemBlockUsed(pCtrBlock, offset, 1);
                numberBlocks--;

                if (numberBlocks > 0)
                {
                    setMemBlockContinued(pCtrBlock, offset, 1);
                }

                offset++;
            }
        }
    }
}

static void free(unsigned char * pCtrBlock, unsigned char offset)
{
    if (pCtrBlock != NULL)
    {
        if (isMemBlockUsed(pCtrBlock, offset))
        {
            if (!isMemBlockContinued(pCtrBlock, offset))
            {
                cleanControlBlock(pCtrBlock, offset);
            }
            else
            {
                while (isMemBlockContinued(pCtrBlock, offset))
                {
                    cleanControlBlock(pCtrBlock, offset); 
                    offset++;

                    if (offset == BLOCKS_PER_CTRL_B)
                    {
                        pCtrBlock++;
                        offset = 0; 
                    }
                }

                cleanControlBlock(pCtrBlock, offset); 
            }
        }
    }
}

static void * getMemPointerFromMemCtrBlock(unsigned char * pCtrBlock, unsigned char offset)
{
    void * mem = NULL;
    unsigned short element = 0;

    element = getMemElementFromMemCtr(pCtrBlock, offset);

    if (element >= 0 && element <= NUMBER_BLOCKS)
    {
        mem = g_pMemStart + element;
    }

    return mem;
}

static unsigned char * getMemCtrPointerFromMem(void * pMem, unsigned char *offset)
{
    unsigned char * pCtrBlock = NULL;
    unsigned short element = 0;

    element = getMemCtrOffsetFromMem((unsigned char *)pMem, offset);

    if (element >= 0 && element <= NUMBER_BLOCKS)
    {
        pCtrBlock = g_pMemCtrStart + element;
    }

    return pCtrBlock;
}

/***********************************************************************/
/***************************** APIs ************************************/
/***********************************************************************/

void * memAlloc(unsigned short size)
{
    void  *pMem = NULL;
    unsigned char  *pEmptyCtrBlock = NULL;
    unsigned short  numberBlocks = 0;
    unsigned char   offset = 0;
    
    if (!g_memInit)
    {
        initMemory();
        g_memInit = 1;
    }

    numberBlocks = (unsigned short)(size / BLOCK_SIZE); 
    
    pEmptyCtrBlock = getEmptyMemCtrBlock(numberBlocks, &offset);

    //Free memory found
    if (pEmptyCtrBlock != NULL)
    {
        alloc(pEmptyCtrBlock, numberBlocks, offset);
        pMem = getMemPointerFromMemCtrBlock(pEmptyCtrBlock, offset);
    }

    return pMem;
}

void memFree(void * pMem)
{
    unsigned char  *pCtrBlock = NULL;
    unsigned char   offset = 0;

    pCtrBlock = getMemCtrPointerFromMem(pMem, &offset);

    if (pCtrBlock != NULL)
    {
        free(pCtrBlock, offset);
    }
}

