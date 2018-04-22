#include "practica_2.h"
#include "defines.h"

//Allow debug in a windows console
#define DEBUG_WINDOWS_CONSOLE

#ifdef DEBUG_WINDOWS_CONSOLE
    #include "stdio.h"
    #include "string.h"
#endif

#define NUMBER_TEST_CASES      24

void test_vpfnMalloc(void);
void test_vfnFree(void);
void test_realloc(void);
void test_calloc(void);
void test_vfnQueueInit(void);
void test_bfnEnqueue(void);
void test_bfnDequeue(void);
void test_vfnStackInit(void);
void test_bfnStackPush(void);
void test_bfnStackPop(void);
void test_bfnCmdLine(void);
void test_bfnLog2(void);
void test_dwAToUL(void);
void test_wAToW(void);
void test_bAtoB(void);
void test_bfnBToA(void);
void test_bfnWToA(void);
void test_bfnDwToA(void);
void test_bfnByteFlip(void);
void test_wfnWordFlip(void);
void test_dwfnDWordFlip(void);
void test_bfnNibbleSwap(void);
void test_wfnByteSwap(void);
void test_dwfnWordSwap(void);

void run_unit_tests(void);
short check_test(const char * functionName, 
                 short          test_number, 
                 const void * current, 
                 const void * expected, 
                 unsigned short size);

void (*g_test_cases[NUMBER_TEST_CASES])(void) = { test_vpfnMalloc,
                                                  test_vfnFree,
                                                  test_realloc,
                                                  test_calloc,
                                                  test_vfnQueueInit,
                                                  test_bfnEnqueue,
                                                  test_bfnDequeue,
                                                  test_vfnStackInit,
                                                  test_bfnStackPush,
                                                  test_bfnStackPop,
                                                  test_bfnCmdLine,
                                                  test_bfnLog2,
                                                  test_dwAToUL,
                                                  test_wAToW,
                                                  test_bAtoB,
                                                  test_bfnBToA,
                                                  test_bfnWToA,
                                                  test_bfnDwToA,
                                                  test_bfnByteFlip,
                                                  test_wfnWordFlip,
                                                  test_dwfnDWordFlip,
                                                  test_bfnNibbleSwap,
                                                  test_wfnByteSwap,
                                                  test_dwfnWordSwap};

int main(void)
{
    run_unit_tests();
    return 0;
}

short check_test(const char * functionName, 
                 short        test_number, 
                 const void * current, 
                 const void * expected, 
                 unsigned short size)
{
    short ret = 0;

#ifdef DEBUG_WINDOWS_CONSOLE
    if (memcmp(current, expected, size) != 0)
    {
        ret = -1;
    }

    if (ret == 0)
    {
        printf("%s test=%d SUCCESS\n", functionName, test_number);
    }
    else
    {
        printf("%s test=%d FAILED\n", functionName, test_number);
    }
#endif

    return ret;
}

void run_unit_tests(void)
{
    unsigned short i = 0;
    void (*test)(void);

    while (i < NUMBER_TEST_CASES)
    {
        test = *(g_test_cases + i);       //get function
        test();                        //run function
        i++;
    }
}

void test_vpfnMalloc(void)
{
    void * test1_ptr = NULL;
    void * test2_ptr = NULL;
    void * test3_ptr = NULL;
    unsigned char was_allocated = 0;
    unsigned char exp_allocated = 1;
    short ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    test1_ptr = vpfnMalloc(sizeof(unsigned short));
    was_allocated = (test1_ptr != NULL) ? 1:0;
    ret = check_test("vpfnMalloc()", 1, (void *)&was_allocated, (void *)&exp_allocated,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    test2_ptr = vpfnMalloc(sizeof(unsigned int));
    was_allocated = (test2_ptr != NULL) ? 1:0;
    ret = check_test("vpfnMalloc()", 2, (void *)&was_allocated, (void *)&exp_allocated,  sizeof(unsigned char));

    ////////////////////////////// Third test  ////////////////////////////////

    test3_ptr = vpfnMalloc(sizeof(unsigned char)*16);
    was_allocated = (test3_ptr != NULL) ? 1:0;
    ret = check_test("vpfnMalloc()", 3, (void *)&was_allocated, (void *)&exp_allocated,  sizeof(unsigned char));

    //Free test memory
    vfnFree(test1_ptr);
    vfnFree(test2_ptr);
    vfnFree(test3_ptr);
}

void test_vfnFree(void)
{
    void * ptr1 = NULL;
    void * ptr2 = NULL;
    void * ptr3 = NULL;
    extern unsigned short g_numBytesAllocated;
    unsigned short exp_bytesAllocated = 0;
    short ret = 0;

    //Allocate memory
    ptr1 = vpfnMalloc(sizeof(unsigned short)*2);
    ptr2 = vpfnMalloc(sizeof(unsigned char));
    ptr3 = vpfnMalloc(sizeof(unsigned char)*32);

    ////////////////////////////// First test  ////////////////////////////////

    exp_bytesAllocated = 33;
    vfnFree(ptr1);
    ret = check_test("vfnFree()", 1, (void *)&g_numBytesAllocated, (void *)&exp_bytesAllocated,  sizeof(unsigned short));

    ////////////////////////////// Second test  ////////////////////////////////

    exp_bytesAllocated = 32;
    vfnFree(ptr2);
    ret = check_test("vfnFree()", 2, (void *)&g_numBytesAllocated, (void *)&exp_bytesAllocated,  sizeof(unsigned short));

    ////////////////////////////// Third test  ////////////////////////////////

    exp_bytesAllocated = 0;
    vfnFree(ptr3);
    ret = check_test("vfnFree()", 3, (void *)&g_numBytesAllocated, (void *)&exp_bytesAllocated,  sizeof(unsigned short));
}

void test_realloc(void)
{
    void * ptr1 = NULL;
    void * ptr2 = NULL;
    void * ptr3 = NULL;
    void * new_ptr1 = NULL;
    void * new_ptr2 = NULL;
    void * new_ptr3 = NULL;
    unsigned char current_ptr = 0;
    unsigned char expected_ptr = 0;
    short ret = 0;

    //Allocate memory
    ptr1 = vpfnMalloc(sizeof(unsigned short)*2);
    ptr2 = vpfnMalloc(sizeof(unsigned char));
    ptr3 = vpfnMalloc(sizeof(unsigned char)*32);

    ////////////////////////////// First test  ////////////////////////////////

    //reallocate 8 bytes
    new_ptr1 = realloc(ptr1, sizeof(unsigned short)*4);
    current_ptr = (ptr1 != new_ptr1) ? 1:0;
    expected_ptr = 1;
    ret = check_test("realloc()", 1, (void *)&current_ptr, (void *)&expected_ptr,  sizeof(unsigned char));
    vfnFree(new_ptr1);

    ////////////////////////////// Second test  ////////////////////////////////

    //reallocate 16 bytes
    new_ptr2 = realloc(ptr2, sizeof(unsigned char)*16);
    current_ptr = (ptr2 != new_ptr2) ? 1:0;
    expected_ptr = 1;
    ret = check_test("realloc()", 2, (void *)&current_ptr, (void *)&expected_ptr,  sizeof(unsigned char));
    vfnFree(new_ptr2);

    ////////////////////////////// Third test  ////////////////////////////////

    //reallocate 1024 bytes (return the same pointer)
    new_ptr3 = realloc(ptr3, sizeof(unsigned char)*1024);
    current_ptr = (ptr3 != new_ptr3) ? 1:0;
    expected_ptr = 0;
    ret = check_test("realloc()", 3, (void *)&current_ptr, (void *)&expected_ptr,  sizeof(unsigned char));
    vfnFree(ptr3);
}

void test_calloc(void)
{
    void * ptr1 = NULL;
    void * ptr2 = NULL;
    void * ptr3 = NULL;
    unsigned short exp1[] = {0,0};
    unsigned char  exp2 = 0;
    unsigned char  exp3[] = {0,0,0,0,0,0,0,0};
    short ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    ptr1 = calloc(sizeof(unsigned short)*2);
    ret = check_test("calloc()", 1, (void *)ptr1, (void *)exp1,  sizeof(unsigned short)*2);

    ////////////////////////////// Second test  ////////////////////////////////

    ptr2 = calloc(sizeof(unsigned char));
    ret = check_test("calloc()", 2, (void *)ptr2, (void *)&exp2,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    ptr3 = calloc(sizeof(unsigned char)*8);
    ret = check_test("calloc()", 3, (void *)ptr3, (void *)exp3,  sizeof(unsigned char)*8);

    //free memory
    vfnFree(ptr1);
    vfnFree(ptr2);
    vfnFree(ptr3);
}

void test_vfnQueueInit(void)
{
    extern unsigned short g_numBytesUsedQueue;
    extern unsigned char  g_queue[];
    extern char * g_currentQueueEntry;
    unsigned char exp_queue[256];
    unsigned short exp_numb = 0;
    unsigned short i = 0;
    short ret = 0;

    for (i = 0; i < 256; i++)
    {
        exp_queue[i] = 0;
    }

    vfnQueueInit();

    /////////////////////////// Test Values ///////////////////////////
    ret = check_test("vfnQueueInit()", 1, (void *)g_queue, (void *)exp_queue,  sizeof(unsigned char)*256);
    ret = check_test("vfnQueueInit()", 2, (void *)&g_numBytesUsedQueue, (void *)&exp_numb,  sizeof(unsigned short));
    ret = check_test("vfnQueueInit()", 3, (void *)g_currentQueueEntry, (void *)g_queue,  sizeof(unsigned char)*256);
}

void test_bfnEnqueue(void)
{
    char data1[16];
    char data2[120];
    char data3[250];
    unsigned short res = 0;
    unsigned short exp = 0;
    short ret = 0;

    //init queue
    vfnQueueInit();

    ////////////////////////////// First test  ////////////////////////////////

    exp = 16;
    res = bfnEnqueue(data1, 16);
    ret = check_test("bfnEnqueue()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 120;
    res = bfnEnqueue(data2, 120);
    ret = check_test("bfnEnqueue()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 120;
    res = bfnEnqueue(data3, 250);
    ret = check_test("bfnEnqueue()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned short));
}

void test_bfnDequeue(void)
{
    char data1[16];
    char data2[120];
    char data3[250];
    char queue_data[256];
    unsigned short res = 0;
    unsigned short exp = 0;
    short ret = 0;

    //init stack
    vfnQueueInit();

    ////////////////////////////// First test  ////////////////////////////////

    exp = 0;   //Empty queue
    res = bfnDequeue(data1, 16);
    ret = check_test("bfnDequeue()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    //Fill Queue
    bfnEnqueue(queue_data, 256);

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 120;
    res = bfnDequeue(data2, 120);
    ret = check_test("bfnDequeue()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 136;
    res = bfnDequeue(data3, 250);
    ret = check_test("bfnDequeue()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned short));
}

void test_vfnStackInit(void)
{
    extern unsigned short g_numBytesUsedStack;
    extern unsigned char  g_stack[];
    extern char * g_currentStackEntry;
    unsigned char exp_stack[256];
    unsigned short exp_numb = 0;
    unsigned short i = 0;
    short ret = 0;

    for (i = 0; i < 256; i++)
    {
        exp_stack[i] = 0;
    }

    vfnStackInit();

    /////////////////////////// Test Values ///////////////////////////
    ret = check_test("vfnStackInit()", 1, (void *)g_stack, (void *)exp_stack,  sizeof(unsigned char)*256);
    ret = check_test("vfnStackInit()", 2, (void *)&g_numBytesUsedStack, (void *)&exp_numb,  sizeof(unsigned short));
    ret = check_test("vfnStackInit()", 3, (void *)g_currentStackEntry, (void *)g_stack,  sizeof(unsigned char)*256);
}

void test_bfnStackPush(void)
{
    char data1[16];
    char data2[120];
    char data3[250];
    unsigned short res = 0;
    unsigned short exp = 0;
    short ret = 0;

    //init stack
    vfnStackInit();

    ////////////////////////////// First test  ////////////////////////////////

    exp = 16;
    res = bfnStackPush(data1, 16);
    ret = check_test("bfnStackPush()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 120;
    res = bfnStackPush(data2, 120);
    ret = check_test("bfnStackPush()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 120;
    res = bfnStackPush(data3, 250);
    ret = check_test("bfnStackPush()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned short));
}

void test_bfnStackPop(void)
{
    char data1[16];
    char data2[120];
    char data3[250];
    char stack_data[256];
    unsigned short res = 0;
    unsigned short exp = 0;
    short ret = 0;

    //init stack
    vfnStackInit();

    ////////////////////////////// First test  ////////////////////////////////

    exp = 0;   //Empty stack
    res = bfnStackPop(data1, 16);
    ret = check_test("bfnStackPop()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    //Fill Stack
    bfnStackPush(stack_data, 256);

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 120;
    res = bfnStackPop(data2, 120);
    ret = check_test("bfnStackPop()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 136;
    res = bfnStackPop(data3, 250);
    ret = check_test("bfnStackPop()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned short));
}

void test_bfnCmdLine(void)
{
    char          *cmdList[5];
    char          cmd[] = "";
    char          cmd1[] = "command_1";
    char          cmd2[] = "command_2";
    char          cmd3[] = "command_3";
    char          cmd4[] = "command_4";
    char          cmd6[] = "command_6";
    unsigned char index = 0;
    unsigned char exp_index = 0;
    short         ret = 0;

    cmdList[0] = cmd;
    cmdList[1] = cmd1;
    cmdList[2] = cmd2;
    cmdList[3] = cmd3;
    cmdList[4] = cmd4;

    ////////////////////////////// First test  ////////////////////////////////

    exp_index = 1;
    index = bfnCmdLine(cmd1, cmdList);
    ret = check_test("bfnCmdLine()", 1, (void *)&index, (void *)&exp_index,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    exp_index = 3;
    index = bfnCmdLine(cmd3, cmdList);
    ret = check_test("bfnCmdLine()", 2, (void *)&index, (void *)&exp_index,  sizeof(unsigned char));

    ////////////////////////////// Third test  ////////////////////////////////

    exp_index = 0;
    index = bfnCmdLine(cmd6, cmdList);
    ret = check_test("bfnCmdLine()", 3, (void *)&index, (void *)&exp_index,  sizeof(unsigned char));
}

void test_bfnLog2(void)
{
    unsigned long dwNum = 0;
    unsigned char res = 0;
    unsigned char exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 1;
    dwNum = 1;
    res = bfnLog2(dwNum);
    ret = check_test("bfnLog2()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 5;
    dwNum = 30;
    res = bfnLog2(dwNum);
    ret = check_test("bfnLog2()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// First test  ////////////////////////////////

    exp = 7;
    dwNum = 120;
    res = bfnLog2(dwNum);
    ret = check_test("bfnLog2()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned char));
}

void test_dwAToUL(void)
{
    char test1[] = "12345";
    char test2[] = "45668678";
    char test3[] = "12313a123";
    unsigned long res = 0;
    unsigned long exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 12345;
    res = dwAToUL(test1);
    ret = check_test("dwAToUL()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned long));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 45668678;
    res = dwAToUL(test2);
    ret = check_test("dwAToUL()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned long));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0;
    res = dwAToUL(test3);
    ret = check_test("dwAToUL()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned long));
}

void test_wAToW(void)
{
    char test1[] = "1234";
    char test2[] = "4566";
    char test3[] = "342b";
    unsigned short res = 0;
    unsigned short exp = 0;
    short          ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 1234;
    res = wAToW(test1);
    ret = check_test("wAToW()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 4566;
    res = wAToW(test2);
    ret = check_test("wAToW()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0;
    res = wAToW(test3);
    ret = check_test("wAToW()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned short));
}

void test_bAtoB(void)
{
    char test1[] = "123";
    char test2[] = "66";
    char test3[] = "1a";
    unsigned char res = 0;
    unsigned char exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 123;
    res = bAtoB(test1);
    ret = check_test("bAtoB()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 66;
    res = bAtoB(test2);
    ret = check_test("bAtoB()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0;
    res = bAtoB(test3);
    ret = check_test("bAtoB()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned char));
}

void test_bfnBToA(void)
{
    unsigned char test1 = 12;
    unsigned char test2 = 120;
    unsigned char test3 = 200;
    char          out1[8];
    char          out2[8];
    char          out3[8];
    unsigned char res = 0;
    unsigned char exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 2;
    res = bfnBToA(test1, out1);
    ret = check_test("bfnBToA()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 3;
    res = bfnBToA(test2, out2);
    ret = check_test("bfnBToA()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 3;
    res = bfnBToA(test3, out3);
    ret = check_test("bfnBToA()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned char));
}

void test_bfnWToA(void)
{
    unsigned short test1 = 1200;
    unsigned short test2 = 11220;
    unsigned short test3 = 200;
    char          out1[8];
    char          out2[8];
    char          out3[8];
    unsigned char res = 0;
    unsigned char exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 4;
    res = bfnWToA(test1, out1);
    ret = check_test("bfnWToA()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 5;
    res = bfnWToA(test2, out2);
    ret = check_test("bfnWToA()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 3;
    res = bfnWToA(test3, out3);
    ret = check_test("bfnWToA()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned char));
}

void test_bfnDwToA(void)
{
    unsigned long test1 = 14589782;
    unsigned long test2 = 1245870;
    unsigned long test3 = 245600;
    char          out1[16];
    char          out2[16];
    char          out3[16];
    unsigned char res = 0;
    unsigned char exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 8;
    res = bfnDwToA(test1, out1);
    ret = check_test("bfnDwToA()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 7;
    res = bfnDwToA(test2, out2);
    ret = check_test("bfnDwToA()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 6;
    res = bfnDwToA(test3, out3);
    ret = check_test("bfnDwToA()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned char));
}

void test_bfnByteFlip(void)
{
    unsigned char test1 = 0b11110000;
    unsigned char test2 = 0b10010000;
    unsigned char test3 = 0b11010010;
    unsigned char res = 0;
    unsigned char exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 0b00001111;
    res = bfnByteFlip(test1);
    ret = check_test("bfnByteFlip()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 0b00001001;
    res = bfnByteFlip(test2);
    ret = check_test("bfnByteFlip()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0b01001011;
    res = bfnByteFlip(test3);
    ret = check_test("bfnByteFlip()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned char));
}

void test_wfnWordFlip(void)
{
    unsigned short test1 = 0b1111111100000000;
    unsigned short test2 = 0b1001100100000000;
    unsigned short test3 = 0b1111110100000010;
    unsigned short res = 0;
    unsigned short exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 0b0000000011111111;
    res = wfnWordFlip(test1);
    ret = check_test("wfnWordFlip()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 0b0000000010011001;
    res = wfnWordFlip(test2);
    ret = check_test("wfnWordFlip()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0b0100000010111111;
    res = wfnWordFlip(test3);
    ret = check_test("wfnWordFlip()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned short));
}

void test_dwfnDWordFlip(void)
{
    unsigned long test1 = 0xFFFF0000;
    unsigned long test2 = 0xFF00FF00;
    unsigned long test3 = 0xFF0000FF;
    unsigned long res = 0;
    unsigned long exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 0x0000FFFF;
    res = dwfnDWordFlip(test1);
    ret = check_test("dwfnDWordFlip()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned long));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 0x00FF00FF;
    res = dwfnDWordFlip(test2);
    ret = check_test("dwfnDWordFlip()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned long));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0xFF0000FF;
    res = dwfnDWordFlip(test3);
    ret = check_test("dwfnDWordFlip()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned long));
}

void test_bfnNibbleSwap(void)
{
    unsigned char test1 = 0b11110000;
    unsigned char test2 = 0b10010010;
    unsigned char test3 = 0b11010010;
    unsigned char res = 0;
    unsigned char exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 0b00001111;
    res = bfnNibbleSwap(test1);
    ret = check_test("bfnNibbleSwap()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 0b00101001;
    res = bfnNibbleSwap(test2);
    ret = check_test("bfnNibbleSwap()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned char));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0b00101101;
    res = bfnNibbleSwap(test3);
    ret = check_test("bfnNibbleSwap()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned char));
}

void test_wfnByteSwap(void)
{
    unsigned short test1 = 0b1111111100000000;
    unsigned short test2 = 0b1001100100000010;
    unsigned short test3 = 0b1111110100001110;
    unsigned short res = 0;
    unsigned short exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 0b0000000011111111;
    res = wfnByteSwap(test1);
    ret = check_test("wfnByteSwap()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 0b0000001010011001;
    res = wfnByteSwap(test2);
    ret = check_test("wfnByteSwap()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned short));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0b0000111011111101;
    res = wfnByteSwap(test3);
    ret = check_test("wfnByteSwap()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned short));
}

void test_dwfnWordSwap(void)
{
    unsigned long test1 = 0xFFFF0000;
    unsigned long test2 = 0xFF00FF00;
    unsigned long test3 = 0xFF0000FF;
    unsigned long res = 0;
    unsigned long exp = 0;
    short         ret = 0;

    ////////////////////////////// First test  ////////////////////////////////

    exp = 0x0000FFFF;
    res = dwfnWordSwap(test1);
    ret = check_test("dwfnWordSwap()", 1, (void *)&res, (void *)&exp,  sizeof(unsigned long));

    ////////////////////////////// Second test  ////////////////////////////////

    exp = 0xFF00FF00;
    res = dwfnWordSwap(test2);
    ret = check_test("dwfnWordSwap()", 2, (void *)&res, (void *)&exp,  sizeof(unsigned long));

    ////////////////////////////// Third test  ////////////////////////////////

    exp = 0x00FFFF00;
    res = dwfnWordSwap(test3);
    ret = check_test("dwfnWordSwap()", 3, (void *)&res, (void *)&exp,  sizeof(unsigned long));
}
