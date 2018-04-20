#include "practica_1.h"

//Allow debug in a windows console
#define DEBUG_WINDOWS_CONSOLE

#ifdef DEBUG_WINDOWS_CONSOLE
    #include "stdio.h"
    #include "string.h"
#endif

#define NUMBER_TEST_CASES      12

void test_vfnMemCpy(void);
void test_vfnMemSet(void);
void test_bfnFindMax(void);
void test_bfnFindMin(void);
void test_bfnStrCmp(void);
void test_bpfnByteAddress(void);
void test_wfnStrLen(void);
void test_wfnRand(void);
void test_bfnLRC(void);
void test_wfnOccurrence(void);
void test_vfnSort(void);
void test_wfnSprintf(void);

void run_unit_tests(void);
short check_test(const char * functionName, 
                 short          test_number, 
                 const void * current, 
                 const void * expected, 
                 unsigned short size);

void (*g_test_cases[NUMBER_TEST_CASES])(void) = { test_vfnMemCpy,
                                                  test_vfnMemSet,
                                                  test_bfnFindMax,
                                                  test_bfnFindMin,
                                                  test_bfnStrCmp,
                                                  test_bpfnByteAddress,
                                                  test_wfnStrLen,
                                                  test_wfnRand,
                                                  test_bfnLRC,
                                                  test_wfnOccurrence,
                                                  test_vfnSort,
                                                  test_wfnSprintf};

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

void test_vfnMemCpy(void)
{
    unsigned char  bpSource[16];
    unsigned char  bpDest[16];
    unsigned short wSize = 0;
    unsigned short i = 0;
    short ret = 0;

    ////////////////// First test copy 16 bytes ///////////////////////
    wSize = 16;

    //fill source pointer
    for (i = 0; i < wSize; i++)
    {
        *(bpSource + i) = 'a';
    }

    vfnMemCpy(bpSource, bpDest, wSize);
    ret = check_test("vfnMemCpy()", 1, (void *)bpDest, (void *)bpSource,  sizeof(unsigned char)*16);

    ////////////////// Second test copy 8 bytes ///////////////////////
    wSize = 8;

    //fill source and expected pointer
    for (i = 0; i < wSize; i++)
    {
        *(bpSource + i) = 'b';
    }

    vfnMemCpy(bpSource, bpDest, wSize);
    ret = check_test("vfnMemCpy()", 2, (void *)bpDest, (void *)bpSource,  sizeof(unsigned char)*16);

    ////////////////// Second test copy 4 bytes ///////////////////////
    wSize = 4;

    //fill source and expected pointer
    for (i = 0; i < wSize; i++)
    {
        *(bpSource + i) = 'c';
    }

    vfnMemCpy(bpSource, bpDest, wSize);
    ret = check_test("vfnMemCpy()", 3, (void *)bpDest, (void *)bpSource,  sizeof(unsigned char)*16);
}

void test_vfnMemSet(void)
{
    unsigned char   bpDest[16];
    unsigned char   pExpected[16];
    unsigned char   bByteToFill = 0; 
    unsigned short  wSize = 0;
    unsigned short  i = 0;
    short           ret = 0;

    //////////////// First test fill 16 bytes with 0 ///////////////////
    wSize = 16;

    //fill expected pointer
    for (i = 0; i < wSize; i++)
    {
        *(pExpected + i) = bByteToFill;
    }

    vfnMemSet(bpDest, bByteToFill, wSize);
    ret = check_test("vfnMemSet()", 1, (void *)bpDest, (void *)pExpected, sizeof(unsigned char)*16);

    //////////////// First test fill 8 bytes with -1 ///////////////////
    wSize = 8;
    bByteToFill = -1;

    //fill expected pointer
    for (i = 0; i < wSize; i++)
    {
        *(pExpected + i) = bByteToFill;
    }

    vfnMemSet(bpDest, bByteToFill, wSize);
    ret = check_test("vfnMemSet()", 2, (void *)bpDest, (void *)pExpected, sizeof(unsigned char)*16);

    //////////////// First test fill 8 bytes with -2 ///////////////////
    wSize = 8;
    bByteToFill = -2;

    //fill expected pointer
    for (i = 0; i < wSize; i++)
    {
        *(pExpected + i) = bByteToFill;
    }

    vfnMemSet(bpDest, bByteToFill, wSize);
    ret = check_test("vfnMemSet()", 3, (void *)bpDest, (void *)pExpected,  sizeof(unsigned char)*16);
}

void test_bfnFindMax(void)
{
    unsigned char  max = 0;
    unsigned char  expected = 0;
    unsigned char  test1[] = {0, 4, 5, 3, 2};
    unsigned char  test2[] = {10, 15, 5, 7, 12};
    unsigned char  test3[] = {90, 84, 50, 200, 20};
    short          ret = 0;

    ////////////////           First test            ///////////////////
    expected = 5;
    max = bfnFindMax(test1, 5);
    ret = check_test("bfnFindMax()", 1, (void *)&max, (void *)&expected, sizeof(unsigned char));

    ////////////////           Second test            ///////////////////
    expected = 15;
    max = bfnFindMax(test2, 5);
    ret = check_test("bfnFindMax()", 2, (void *)&max, (void *)&expected, sizeof(unsigned char));

    ////////////////           Third test             ///////////////////
    expected = 200;
    max = bfnFindMax(test3, 5);
    ret = check_test("bfnFindMax()", 3, (void *)&max, (void *)&expected, sizeof(unsigned char));
}

void test_bfnFindMin(void)
{
    unsigned char  min = 0;
    unsigned char  expected = 0;
    unsigned char  test1[] = {0, 4, 5, 3, 2};
    unsigned char  test2[] = {10, 15, 5, 7, 12};
    unsigned char  test3[] = {90, 84, 50, 200, 20};
    short          ret = 0;

    ////////////////           First test            ///////////////////
    expected = 0;
    min = bfnFindMin(test1, 5);
    ret = check_test("bfnFindMin()", 1, (void *)&min, (void *)&expected, sizeof(unsigned char));

    ////////////////           Second test            ///////////////////
    expected = 5;
    min = bfnFindMin(test2, 5);
    ret = check_test("bfnFindMin()", 2, (void *)&min, (void *)&expected, sizeof(unsigned char));

    ////////////////           Third test             ///////////////////
    expected = 20;
    min = bfnFindMin(test3, 5);
    ret = check_test("bfnFindMin()", 3, (void *)&min, (void *)&expected, sizeof(unsigned char));
}

void test_bfnStrCmp(void)
{
    unsigned char * test1_str1 = "Hola mundo";
    unsigned char * test1_str2 = "Hola mundo";
    unsigned char * test2_str1 = "Nueva cadena";
    unsigned char * test2_str2 = "Nueva";
    unsigned char * test3_str1 = "hola mundo";
    unsigned char * test3_str2 = "hola Mundo";
    unsigned char   equal = 0;
    unsigned char   expected = 0;
    short           ret = 0;

    ////////////////           First test            ///////////////////
    expected = 1;
    equal = bfnStrCmp(test1_str1, test1_str2, 10);
    ret = check_test("bfnStrCmp()", 1, (void *)&equal, (void *)&expected, sizeof(unsigned char));

    ////////////////           Second test            ///////////////////
    expected = 0;
    equal = bfnStrCmp(test2_str1, test2_str2, 12);
    ret = check_test("bfnStrCmp()", 2, (void *)&equal, (void *)&expected, sizeof(unsigned char));

    ////////////////           Third test            ///////////////////
    expected = 0;
    equal = bfnStrCmp(test3_str1, test3_str2, 10);
    ret = check_test("bfnStrCmp()", 3, (void *)&equal, (void *)&expected, sizeof(unsigned char));
}

void test_bpfnByteAddress(void)
{
    unsigned char  test[] = {0, 5, 'a', 8, 2};
    unsigned char  bChar1 = 'a';
    unsigned char  bChar2 = 'c';
    unsigned char  bChar3 = 5;
    unsigned char* address = NULL;
    unsigned char  found = 0;
    unsigned char  expected = 0;
    short          ret = 0;

    ////////////////           First test            ////////////////////
    expected = 1;
    address = bpfnByteAddress(test, bChar1, 5);
    found = (address != NULL) ? 1: 0;
    ret = check_test("bpfnByteAddress()", 1, (void *)&found, (void *)&expected, sizeof(unsigned char));

    ////////////////           Second test            ///////////////////
    expected = 0;
    address = bpfnByteAddress(test, bChar2, 5);
    found = (address != NULL) ? 1: 0;
    ret = check_test("bpfnByteAddress()", 2, (void *)&found, (void *)&expected, sizeof(unsigned char));

    ////////////////           Third test            ///////////////////
    expected = 1;
    address = bpfnByteAddress(test, bChar3, 5);
    found = (address != NULL) ? 1: 0;
    ret = check_test("bpfnByteAddress()", 3, (void *)&found, (void *)&expected, sizeof(unsigned char));
}

void test_wfnStrLen(void)
{
    unsigned short res = 0;
    unsigned short expected = 0;
    short          ret = 0;

    ////////////////           First test            ////////////////////
    expected = 7;
    res = wfnStrLen("cadena1");
    ret = check_test("wfnStrLen()", 1, (void *)&res, (void *)&expected, sizeof(unsigned short));

    ////////////////           Second test            ///////////////////
    expected = 17;
    res = wfnStrLen("cadena2_mas_larga");
    ret = check_test("wfnStrLen()", 2, (void *)&res, (void *)&expected, sizeof(unsigned short));

    ////////////////           Third test            ////////////////////
    expected = 19;
    res = wfnStrLen("cadena con espacios");
    ret = check_test("wfnStrLen()", 3, (void *)&res, (void *)&expected, sizeof(unsigned short));
}

void test_wfnRand(void)
{
    unsigned short res = 0;
    short          ret = 0;

    // There is not a way to compare the output
    // so the output for this unit test will always 
    // success

    ////////////////           First test            ////////////////////
    res = wfnRand(5);
    ret = check_test("wfnRand()", 1, (void *)&res, (void *)&res, sizeof(unsigned short));

    ////////////////           Second test            ////////////////////
    res = wfnRand(8);
    ret = check_test("wfnRand()", 2, (void *)&res, (void *)&res, sizeof(unsigned short));

    ////////////////           Third test            ////////////////////
    res = wfnRand(10);
    ret = check_test("wfnRand()", 3, (void *)&res, (void *)&res, sizeof(unsigned short));
}

void test_bfnLRC(void)
{
    unsigned char test1[] = {1, 5, 8, 9, 10};
    unsigned char test2[] = {0, 7, 2, 9, 11};
    unsigned char test3[] = {0, 0, 1, 0, 1};
    unsigned char res = 0;
    unsigned char expected = 0;
    short         ret = 0;

    ////////////////           First test            ////////////////////
    expected = 15;
    res = bfnLRC(test1, 5);
    ret = check_test("bfnLRC()", 1, (void *)&res, (void *)&expected, sizeof(unsigned char));

    ////////////////           Second test           ////////////////////
    expected = 7;
    res = bfnLRC(test2, 5);
    ret = check_test("bfnLRC()", 2, (void *)&res, (void *)&expected, sizeof(unsigned char));

    ////////////////           Third test            ////////////////////
    expected = 0;
    res = bfnLRC(test3, 5);
    ret = check_test("bfnLRC()", 3, (void *)&res, (void *)&expected, sizeof(unsigned char));
}

void test_wfnOccurrence(void)
{
    unsigned char  test[] = {'a', 'a', 'a', 'a', 'b', 'c', 'c'};
    unsigned short res = 0;
    unsigned short expected = 0;
    short          ret = 0;

    ////////////////           First test            ////////////////////
    expected = 4;
    res = wfnOccurrence('a', test, 7);
    ret = check_test("wfnOccurrence()", 1, (void *)&res, (void *)&expected, sizeof(unsigned short));

    ////////////////           Second test           ////////////////////
    expected = 1;
    res = wfnOccurrence('b', test, 7);
    ret = check_test("wfnOccurrence()", 2, (void *)&res, (void *)&expected, sizeof(unsigned short));

    ////////////////           Third test            ////////////////////
    expected = 0;
    res = wfnOccurrence('d', test, 7);
    ret = check_test("wfnOccurrence()", 3, (void *)&res, (void *)&expected, sizeof(unsigned short));
}

void test_vfnSort(void)
{
    unsigned char test1[] = {1,0,8,6,4,3,5};
    unsigned char test2[] = {8,6,1,0,4,3,5};
    unsigned char test3[] = {6,4,3,1,0,8,5};
    unsigned char expected[] = {0,1,3,4,5,6,8};
    short         ret = 0;

    ////////////////           First test            ////////////////////
    vfnSort(test1, 7);
    ret = check_test("vfnSort()", 1, (void *)test1, (void *)expected, sizeof(unsigned char)*7);

    ////////////////           Second test            ////////////////////
    vfnSort(test2, 7);
    ret = check_test("vfnSort()", 2, (void *)test2, (void *)expected, sizeof(unsigned char)*7);

    ////////////////           Third test            ////////////////////
    vfnSort(test3, 7);
    ret = check_test("vfnSort()", 3, (void *)test3, (void *)expected, sizeof(unsigned char)*7);
}

void test_wfnSprintf(void)
{
    void          * args[5];
    unsigned char   fmt_test1[] = "str=%s char=%c int=%d bin=%b hex=%x";
    unsigned char   fmt_test2[] = "res=%d hex=%x str=%s";
    unsigned char   fmt_test3[] = "number=%0d bin=%0b hex=%0x";
    unsigned char   exp_test1[] = "str=cadena char=a int=50 bin=110010 hex=32";
    unsigned char   exp_test2[] = "res=50 hex=32 str=cadena";
    unsigned char   exp_test3[] = "number=50 bin=00110010 hex=0032";
    unsigned char   out_test1[64];
    unsigned char   out_test2[64];
    unsigned char   out_test3[64];
    unsigned char   str[] = "cadena";
    unsigned char   c = 'a';
    unsigned char   number = 50;
    unsigned short  len = 0;
    unsigned short  exp_len = 0;
    unsigned short  i = 0;
    short           ret = 0;

    //Clean output
    for (i = 0; i < 64; i++)
    {
        out_test1[i] = 0;
        out_test2[i] = 0;
        out_test3[i] = 0;
    }

    ////////////////           First test            ////////////////////
    args[0] = &str;
    args[1] = &c;
    args[2] = &number;
    args[3] = &number;
    args[4] = &number;
    exp_len = 42;

    len = wfnSprintf(out_test1, fmt_test1, args);
    ret = check_test("wfnSprintf()", 1, (void *)out_test1, (void *)exp_test1, sizeof(unsigned char)*64);
    ret = check_test("wfnSprintf() - len", 2, (void *)&len, (void *)&exp_len, sizeof(unsigned short));

    ////////////////           Second test            ////////////////////
    args[0] = &number;
    args[1] = &number;
    args[2] = &str;
    args[3] = NULL;
    args[4] = NULL;
    exp_len = 24;

    len = wfnSprintf(out_test2, fmt_test2, args);
    ret = check_test("wfnSprintf()", 3, (void *)out_test2, (void *)exp_test2, sizeof(unsigned char)*64);
    ret = check_test("wfnSprintf() - len", 4, (void *)&len, (void *)&exp_len, sizeof(unsigned short));

    ////////////////           Third test            ////////////////////
    args[0] = &number;
    args[1] = &number;
    args[2] = &number;
    args[3] = NULL;
    args[4] = NULL;
    exp_len = 31;

    len = wfnSprintf(out_test3, fmt_test3, args);
    ret = check_test("wfnSprintf()", 5, (void *)out_test3, (void *)exp_test3, sizeof(unsigned char)*64);
    ret = check_test("wfnSprintf() - len", 6, (void *)&len, (void *)&exp_len, sizeof(unsigned short));

}



