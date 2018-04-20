#include "defines.h"

#define   NUMBER_BLOCKS      1024                        //-> 1kb
#define   BLOCK_SIZE         sizeof(BYTE)
#define   NULL               (void *)0

//Flags control
#define   MEM_USED            0x01
#define   MEM_CONTINUED       0x02
#define   MEM_CONTINUATION    0x04

//Reserve space for the heap and the memory control
BYTE memory[NUMBER_BLOCKS];
BYTE memoryControl[NUMBER_BLOCKS];

//Memory
BYTE * pMemStart = memory;                //Start at the beginning of Memory
BYTE * pMemEnd   = memory + NUMBER_BLOCKS;

//Memory control
BYTE * pMemCtrStart = memoryControl;
BYTE * pMemCtrEnd = memoryControl + NUMBER_BLOCKS;

static BOLEAN isMemBlockUsed(BYTE *pCtrBlock)
{
    return (pCtrBlock != NULL
            && ((*pCtrBlock) & MEM_USED));
}

static BOLEAN isMemBlockContinued(BYTE *pCtrBlock)
{
    return (pCtrBlock != NULL
            && ((*pCtrBlock) & MEM_CONTINUED));
}

static BOLEAN isMemBlockContinuation(BYTE *pCtrBlock)
{
    return (pCtrBlock != NULL
            && ((*pCtrBlock) & MEM_CONTINUATION));
}

static VOID cleanBlock(BYTE *pBlock)
{
    if (pBlock != NULL)
    {
        *pBlock = 0;
    }
}

static VOID initMemory()
{
    BYTE * pMem = pMemStart;

    //Clean memory
    while (pMem != pMemEnd)
    {
        cleanBlock(pMem);
        pMem++;
    }

    *pMemEnd = 0;

    //Clean memory control
    pMem = pMemCtrStart;

    while (pMem != pMemCtrEnd)
    {
        cleanBlock(pMem);
        pMem++;
    }

    *pMemCtrEnd = 0;
}

static UINT16 getMemOffsetFromMemCtr(BYTE * pMemCtr)
{
    UINT16 ret = 0;
    BYTE * start = pMemCtrStart;
    
    if (pMemCtr == pMemCtrEnd)
    {
        ret = NUMBER_BLOCKS;
    }
    else
    {
        while (start != pMemCtrEnd) 
        {
            if (start == pMemCtr)
            {
                break;
            }

            ret++;
            start++;
        }
    }

    return ret;
}

static UINT16 getMemCtrOffsetFromMem(BYTE * pMem)
{
    UINT16 ret = 0;
    BYTE * start = pMemStart;
    
    if (pMemCtr == pMemEnd)
    {
        ret = NUMBER_BLOCKS;
    }
    else
    {
        while (start != pMemEnd) 
        {
            if (start == pMem)
            {
                break;
            }

            ret++;
            start++;
        }
    }

    return ret;
}

static UINT16 getNumberOfFreeBlocks(BYTE * start)
{
    UINT16 number = 0;

    //search all continues free blocks
    while (start != pMemCtrEnd
           && !isMemBlockUsed(start))
    {
        number++;
        start++;
    }

    if (start == pMemCtrEnd
        && !isMemBlockUsed(start))
    {
        number++;
    }

    return number;
}

static BYTE * getEmptyMemCtrBlock(UINT16 numberOfBlocks)
{
    BYTE * start = pMemCtrStart;
    BYTE * pEmpty = NULL;

    //search in all enties
    while (start != pMemCtrEnd)
    {
        if (getNumberOfFreeBlocks(start) == numberOfBlocks)
        {
            pEmpty = start;
            break;
        }

        start++; 
    }

    //finaly search in the last entrie
    if (start == pMemCtrEnd
        && pEmpty == NULL
        && getNumberOfFreeBlocks(start) == numberOfBlocks)
    {
        pEmpty = start;
    }

    return pEmpty;
}

static VOID alloc(BYTE * pCtrBlock, UINT16 numberBlocks)
{
    if (pCtrBlock != NULL)
    {
        //set Memory used
        *pCtrBlock |= MEM_USED;
        numberBlocks--;

        //if we need to allocate more than one block
        if (numberBlocks > 0)
        {
            //set continued
            *pCtrBlock |= MEM_CONTINUED;
            pCtrBlock++;

            while (numberBlocks > 0)
            {
                *pCtrBlock |= MEM_CONTINUATION;
                numberBlocks--;

                if (numberBlocks > 0)
                {
                    *pCtrBlock |= MEM_CONTINUED;
                    pCtrBlock++;
                }
            }
        }
    }
}

static VOID free(BYTE * pCtrBlock)
{
    if (pCtrBlock != NULL
        && isMemBlockUsed(pCtrBlock))
    {
        if (!isMemBlockContinued(pCtrBlock))
        {
            cleanBlock(pCtrBlock);
        }
        else
        {
            while (isMemBlockContinued(pCtrBlock)) 
            {
                cleanBlock(pCtrBlock);
                pCtrBlock++;
            }

            //clean last entry
            if (isMemBlockContinuation(pCtrBlock))
            {
                cleanBlock(pCtrBlock);
            }
        }
    }
}

static VOID * getMemPointerFromMemCtrBlock(BYTE * pCtrBlock)
{
    VOID * mem = NULL;
    UINT16 offset = 0;

    offset = getMemOffsetFromMemCtr(pCtrBlock);

    if (offset >= 0 && offset <= NUMBER_BLOCKS)
    {
        mem = pMemStart + offset;
    }

    return mem;
}

static BYTE * getMemCtrPointerFromMem(VOID * pMem)
{
    BYTE * pCtrBlock = NULL;
    UINT16 offset = 0;

    offset = getMemCtrOffsetFromMem((BYTE *)pMem);

    if (offset >= 0 && offset <= NUMBER_BLOCKS)
    {
        pCtrBlock = pMemCtrStart + offset;
    }

    return pCtrBlock;
}

/***********************************************************************/
/***************************** APIs ************************************/
/***********************************************************************/

VOID * memAlloc(UINT16 size)
{
    VOID  *pMem = NULL;
    BYTE  *pEmptyCtrBlock = NULL;
    UINT16 numberBlocks = 0;
    
    numberBlocks = (UINT16)(size/BLOCK_SIZE);
    
    pEmptyCtrBlock = getEmptyMemCtrBlock(numberBlocks);

    //Free memory found
    if (pEmptyCtrBlock != NULL)
    {
        alloc(pEmptyCtrBlock, numberBlocks);
        pMem = getMemPointerFromMemCtrBlock(pEmptyCtrBlock);
    }

    return pMem;
}

VOID memFree(VOID * pMem)
{
    BYTE  *pCtrBlock = NULL;

    pCtrBlock = getMemCtrPointerFromMem(pMem);

    if (pCtrBlock != NULL)
    {
        free(pCtrBlock);
    }
}

