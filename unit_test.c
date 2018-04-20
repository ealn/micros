#include "mem.h"
#include "defines.h"

#ifdef DEBUG_WINDOWS_CONSOLE
    #include "stdio.h"
#endif

#define NUMBER_TEST_CASES      2

VOID (*test_case[NUMBER_TEST_CASES])(VOID) = [ test_case_malloc,
                                               test_case_free];

VOID show(BYTE * test, BOOLEAN pass)
{
#ifdef DEBUG_WINDOWS_CONSOLE
    if (pass)
    {
        printf("%s passed", test); 
    }
    else
    {
        printf("%s failed", test); 
    }
#else
    //TODO show in the stdout
#endif
}

INT32 main(VOID)
{

    return 0;
}

static VOID test_case_malloc(VOID)
{

}

static VOID test_case_free(VOID)
{

}
