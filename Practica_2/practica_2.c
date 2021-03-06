/***********************************************************************/
/**************** Practica #2 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Source File                                                       **/
/**                                                                   **/
/***********************************************************************/

#include "practica_2.h"
#include "practica_1.h"
#include "defines.h"
#include "heap.h"
#include "stack.h"
#include "queue.h"

/////////////////////////////////////////////////////////////////////////
/////////////////////////// HEAP MEMORY /////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/**
 Descripcion: regresa un apuntador a la posici�n en memoria 
 reservada para el bloque de tama�o wSize solicitado Si no hay 
 memoria, se regresa un apuntador null 
**/
void* vpfnMalloc(unsigned short wSize)
{
    return memAlloc(wSize);
}

/**
 Descripcion: libera el espacio de memoria apuntado por vpPtr 
**/
void vfnFree( void* vpPtr)
{
    memFree(vpPtr);
}

/**
 Descripcion: Se cambia de posici�n el buffer apuntado por vpPtr
 para modificar el tama�o al especificado por wSize Si no hay
 espacio para el nuevo buffer, se regresa el apuntador inicial
**/
void* realloc (void* vpPtr, unsigned short wSize)
{
    void * newMemPtr = NULL;

    newMemPtr = memAlloc(wSize);

    if (newMemPtr != NULL)
    {
        memFree(vpPtr);
    }
    else
    {
        newMemPtr = vpPtr;
    }

    return newMemPtr;
}

/**
 Descripcion: regresa un apuntador de a un buffer lleno de 0 de 
 tama�o wSize Si no hay espacio para crear el buffer, regresa un 
 apuntador null 
**/
void* calloc (unsigned short wSize)
{
    void * memPtr = memAlloc(wSize);
    unsigned short i = 0;

    if (memPtr != NULL)
    {
        vfnMemSet((unsigned char *)memPtr, 0, wSize);
    }

    return memPtr;
}

/////////////////////////////////////////////////////////////////////////
////////////////////////////// QUEUE ////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/**
 Descripcion: Inicializa los apuntadores, contadores, etc de 
 manejo del Queue a sus valores iniciales 
**/
void vfnQueueInit(void)
{
    queueInit();
}

/**
 Descripcion: mete el total de wSize datos apuntados por cpData 
 en el Queue y regresa la cantidad de datos que se pudieron 
 ingresar. Si el queue est� lleno, entonces se regresa 0. Si 
 solo se puede meter una parte, entonces se regresa la cantidad 
 que si entro. 
**/
unsigned short bfnEnqueue(char* cpData, unsigned short wSize)
{
    return enqueue(cpData, wSize);
}

/**
 Descripcion: extrae a cpData la cantidad de datos indicadas por 
 wSize del Queue. Se regresa la cantidad de datos extraidos. Si 
 el queue est� vacio, se regresa 0 
**/
unsigned short bfnDequeue(char* cpData, unsigned short wSize)
{
    return dequeue(cpData, wSize);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////// STACK MEMORY ////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/**
 Descripcion: inicializa los apuntadores, contadores, etc de 
 manejo del Stack a sus valores iniciales
**/
void vfnStackInit(void)
{
    stackInit();
}

/**
 Descripcion: mete el total de wSize datos apuntados por cpData 
 en el Stack y regresa la cantidad de datos que se pudieron 
 ingresar. Si el Stack est� lleno, entonces regresa 0. Si solo 
 se puede meter una parte, entonces regresa la cantidad de datos 
 que si entro 
**/
unsigned short bfnStackPush(char* cpData, unsigned short wSize)
{
    return stackPush(cpData, wSize);
}

/**
 Descripcion: extrae a cpData la cantidad de datos indicada por 
 wSize del Stack. Se regresa la cantidad de datos extraidos. Si 
 el Stack est� vacio, se regresa 0. 
**/
unsigned short bfnStackPop(char* cpData, unsigned short wSize)
{
    return stackPop(cpData, wSize);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////// GENERAL UTILS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////

/**
 Descripcion: Recibe en cpCmdList un apuntador a la lista de 
 comandos v�lidos y en cpCmd el comando a verificar. Si el 
 comando a verificar se encuentra en la lista de comandos 
 v�lidos, se regresa el �ndice correspondiente a la posici�n de 
 la lista en la que se encontr� el comando. 
**/
unsigned char bfnCmdLine(char* cpCmd, char** cpCmdList)
{
    unsigned char index = 0;
    unsigned char found = 0;
    char * cmd = NULL;

    if (cpCmd != NULL
        && cpCmdList != NULL)
    {
        cmd = cpCmdList[0];   //get first element

        while (cmd != NULL)
        {
            if (bfnStrCmp((unsigned char*)cpCmd, 
                          (unsigned char*)cmd, 
                          wfnStrLen((unsigned char*)cpCmd)))
            {
                found = 1;
                break;
            }

            index++;
            cmd = cpCmdList[index];
        }
    }

    if (!found)
    {
        index = 0;
    }

    return index;
}

/**
 Descripcion: regresa la cantidad m�nima de bits necesarios para 
 representar el numero recibido en dwNum 
**/
unsigned char bfnLog2 (unsigned long dwNum)
{
    unsigned char  numBits = 1;
    unsigned char  index = 0;

    while (index < NUMBER_BITS_LONG)
    {
        if (dwNum & (1 << index))
        {
            //update with the last 1
            numBits = index + 1;
        }

        index++; 
    }

    return numBits;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////// DATA CONVERSION /////////////////////////////
/////////////////////////////////////////////////////////////////////////

/**
 Descripcion: regresa el numero de 32 bits sin signo que resulta 
 de convertir el numero representado en la cadena terminada en 0 
 apuntada por cpPtr Si se encuentra un car�cter invalido, 
 entonces se regresa 0 
**/
unsigned long dwAToUL (char* cpPtr)
{
    unsigned long  ret = 0;
    char          *p = cpPtr;

    while (*p != '\0')
    {
        if (*p < '0' || *p > '9')   //check invalid character
        {
            ret = 0;
            break;
        }
        else
        {
            ret *= 10;
            ret += *p - '0';
        }

        p++; 
    }

    return ret;
}

/**
 Descripcion: regresa el numero de 16 bits sin signo que resulta 
 de convertir el numero representado en la cadena terminada en 0 
 apuntada por cpPtr Si se encuentra un car�cter invalido, 
 entonces se regresa 0 
**/
unsigned short wAToW (char* cpPtr)
{
    return (unsigned short)dwAToUL(cpPtr);
}

/**
 Descripcion: regresa el numero de 8 bits sin signo que 
 resulta de convertir el numero representado en la cadena 
 terminada en 0 apuntada por cpPtr Si se encuentra un car�cter 
 invalido, entonces se regresa 0 
 **/
unsigned char bAtoB(char* cpPtr)
{
    return (unsigned char)dwAToUL(cpPtr);
}

/**
 Descripcion: regresa el total de caracteres agregados a la 
 cadena apuntada por cpPtr resultantes de convertir bData a su 
 representaci�n en d�gitos ASCII 
 **/
unsigned char bfnBToA(unsigned char bData, char* cpPtr)
{
    return (unsigned char)wfnConvertIntToAsc((unsigned long)bData, 
                                             (unsigned char*)cpPtr, 
                                             10);
}

/**
 Descripcion: regresa el total de caracteres agregados a la 
 cadena apuntada por cpPtr resultantes de convertir wData a su 
 representaci�n en d�gitos ASCII. 
 **/
unsigned char bfnWToA(unsigned short wData, char* cpPtr)
{
    return (unsigned char)wfnConvertIntToAsc((unsigned long)wData, 
                                             (unsigned char*)cpPtr, 
                                             10);
}

/**
 Descripcion: regresa el total de caracteres agregados a la 
 cadena apuntada por cpPtr resultantes de convertir dwData a su 
 representaci�n en d�gitos ASCII 
 **/
unsigned char bfnDwToA(unsigned long dwData, char* cpPtr)
{
    return (unsigned char)wfnConvertIntToAsc(dwData, 
                                             (unsigned char*)cpPtr, 
                                             10);
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////// DATA MANAGEMENT /////////////////////////////
/////////////////////////////////////////////////////////////////////////

/**
 Descripcion: regresa el numero de 8 bits resultante de reflejar 
 cada bit de bData 
 **/
unsigned char bfnByteFlip(unsigned char bData)
{
    unsigned char ret = 0;
    unsigned char index = 0;
    unsigned char bit = 1 << (NUMBER_BITS_CHAR - 1);

    while (index < NUMBER_BITS_CHAR)
    {
        if (bData & (bit >> index))
        {
            ret |= 1 << index;
        }

        index++;
    }

    return ret;
}

/**
 Descripcion: regresa el numero de 16 bits resultante de reflejar 
 cada bit de wData 
 **/
unsigned short wfnWordFlip(unsigned short wData)
{
    unsigned short ret = 0;
    unsigned char index = 0;
    unsigned short bit = 1 << (NUMBER_BITS_SHORT - 1);

    while (index < NUMBER_BITS_SHORT)
    {
        if (wData & (bit >> index))
        {
            ret |= 1 << index;
        }

        index++;
    }

    return ret;
}

/**
 Descripcion: regresa el numero de 32 bits resultante de 
 reflejar cada bit de dwData 
 **/
unsigned long dwfnDWordFlip(unsigned long dwData)
{
    unsigned long ret = 0;
    unsigned char index = 0;
    unsigned long bit = 1 << (NUMBER_BITS_LONG - 1);

    while (index < NUMBER_BITS_LONG)
    {
        if (dwData & (bit >> index))
        {
            ret |= 1 << index;
        }

        index++;
    }

    return ret;
}

/**
 Descripcion: regresa el numero de 8 bits resultante de 
 intercambiar los nibbles de bData 
 **/
unsigned char bfnNibbleSwap(unsigned char bData)
{
    unsigned char low = bData & 0x0F;
    unsigned char high = bData & 0xF0;

    return ((low << (NUMBER_BITS_CHAR/2)) | (high >> (NUMBER_BITS_CHAR/2)));
}

/**
 Descripcion: regresa el numero de 16 bits resultante de 
 intercambiar los bytes de wData 
 **/
unsigned short wfnByteSwap(unsigned short wData)
{
    unsigned short low = wData & 0x00FF;
    unsigned short high = wData & 0xFF00;

    return ((low << (NUMBER_BITS_SHORT/2)) | (high >> (NUMBER_BITS_SHORT/2)));
}

/**
 Descripcion: regresa el numero de 32 bits resultante 
 de intercambiar los words de dwData
 **/
unsigned long dwfnWordSwap(unsigned long dwData)
{
    unsigned long low = dwData & 0x0000FFFF;
    unsigned long high = dwData & 0xFFFF0000;

    return ((low << (NUMBER_BITS_LONG / 2)) | (high >> (NUMBER_BITS_LONG / 2))); 
}
