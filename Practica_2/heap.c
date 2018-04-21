

#define   BLOCKS_PER_CTRL_B      4
#define   NUMBER_BLOCKS          1024                                  //-> 1kb
#define   NUMBER_CONTROL_BLOCKS  NUMBER_BLOCKS/BLOCKS_PER_CTRL_B        //-> 265b
#define   BLOCK_SIZE             sizeof(unsigned char)
#define   NULL                   (void *)0

//Flags control
#define   MEM_USED            0x01
#define   MEM_CONTINUED       0x02

unsigned char g_mem_init = 0;

//Reserve space for the heap and the memory control
unsigned char memory[NUMBER_BLOCKS];
unsigned char memoryControl[NUMBER_BLOCKS];

//Memory
unsigned char * pMemStart = memory;                //Start at the beginning of Memory
unsigned char * pMemEnd   = memory + NUMBER_BLOCKS;

//Memory control
unsigned char * pMemCtrStart = memoryControl;
unsigned char * pMemCtrEnd = memoryControl + NUMBER_CONTROL_BLOCKS;

static void setMemBlockUsed(unsigned char *pCtrBlock, unsigned char offset, unsigned char value)
{
    if (pCtrBlock != NULL)
    {
        if (value == 1)
        {
            *pCtrBlock |= (MEM_USED << offset); 
        }
        else
        {
            *pCtrBlock &= ~(MEM_USED << offset); 
        }
    }
}

static unsigned char isMemBlockUsed(unsigned char *pCtrBlock, unsigned char offset)
{
    return (pCtrBlock != NULL
            && ((*pCtrBlock) & (MEM_USED << offset)));
}

static void setMemBlockContinued(unsigned char *pCtrBlock, unsigned char offset, unsigned char value)
{
    if (pCtrBlock != NULL)
    {
        if (value == 1)
        {
            *pCtrBlock |= (MEM_CONTINUED << offset); 
        }
        else
        {
            *pCtrBlock &= ~(MEM_CONTINUED << offset); 
        }
    }
}

static unsigned char isMemBlockContinued(unsigned char *pCtrBlock, unsigned char offset)
{
    return (pCtrBlock != NULL
            && ((*pCtrBlock) & (MEM_CONTINUED << offset)));
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
        *pBlock &= ~(MEM_USED << offset);
        *pBlock &= ~(MEM_CONTINUED << offset);
    }
}

static void initMemory(void)
{
    unsigned char * pMem = pMemStart;

    //Clean memory
    while (pMem != pMemEnd)
    {
        cleanBlock(pMem);
        pMem++;
    }

    cleanBlock(pMemEnd);

    //Clean memory control
    pMem = pMemCtrStart;

    while (pMem != pMemCtrEnd)
    {
        cleanBlock(pMem);
        pMem++;
    }

    cleanBlock(pMemCtrEnd);
}

static unsigned short getMemElementFromMemCtr(unsigned char * pMemCtr, unsigned char offset)
{
    unsigned short ret = 0;
    unsigned char * start = pMemCtrStart;
    
    while (start != pMemCtrEnd) 
    {
        if (start == pMemCtr)
        {
            break;
        }

        ret++;
        start++;
    }

    ret *= BLOCKS_PER_CTRL_B;
    ret += offset

    return ret;
}

static unsigned short getMemCtrOffsetFromMem(unsigned char * pMem, unsigned char *offset)
{
    unsigned short ret = 0;
    unsigned char * start = pMemStart;

    while (start != pMemEnd) 
    {
        if (start == pMem)
        {
            break;
        }

        ret++;
        start++;
    }
    
    if (*offset != NULL)
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

static unsigned short getNumberOfFreeBlocks(unsigned char * start)
{
    unsigned short number = 0;
    unsigned char  offset = 0;

    //search all continues free blocks
    while (start != pMemCtrEnd)
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

        start++;
    }

    //Search in last control block
    if (start == pMemCtrEnd)
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
    unsigned char * start = pMemCtrStart;
    unsigned char * pEmpty = NULL;

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
                    if (offset == BLOCKS_PER_CTRL_B)
                    {
                        pCtrBlock++;
                        offset = 0; 
                    }

                    cleanControlBlock(pCtrBlock, offset); 
                    offset++;
                }

                cleanControlBlock(pCtrBlock, offset); 
            }
        }
    }
    /*
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
    }*/
}

static void * getMemPointerFromMemCtrBlock(unsigned char * pCtrBlock, unsigned char offset)
{
    void * mem = NULL;
    unsigned short element = 0;

    element = getMemElementFromMemCtr(pCtrBlock, offset);

    if (element >= 0 && element <= NUMBER_BLOCKS)
    {
        mem = pMemStart + element;
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
        pCtrBlock = pMemCtrStart + element;
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
    
    if (!g_mem_init)
    {
        initMemory();
        g_mem_init = 1;
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

