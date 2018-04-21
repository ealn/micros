#include "stack.h"
#include "defines.h"

#define   NUMBER_SLOTS       1024                        //-> 1kb
#define   SLOT_SIZE          sizeof(BYTE)

//Define Stack
BYTE   stack[NUMBER_SLOTS];
BYTE * pStackStart = stack;     //Stack init
BYTE * pStackEnd = stack + NUMBER_SLOTS;
BYTE * pCurrentSlot = pStackStart;

static VOID initStack(VOID)
{

}





