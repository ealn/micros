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
 Descripcion: regresa un apuntador a la posición en memoria 
 reservada para el bloque de tamaño wSize solicitado Si no hay 
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
 Descripcion: Se cambia de posición el buffer apuntado por vpPtr
 para modificar el tamaño al especificado por wSize Si no hay
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
 tamaño wSize Si no hay espacio para crear el buffer, regresa un 
 apuntador null 
**/
void* calloc (unsigned short wSize)
{
    void * memPtr = memAlloc(wSize);
    unsigned short i = 0;

    if (memPtr != NULL)
    {
        //clean memory
        while (i < wSize)
        {
            *(((unsigned char *)memPtr) + i) = 0;
            i++;
        }
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
 ingresar. Si el queue está lleno, entonces se regresa 0. Si 
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
 el queue está vacio, se regresa 0 
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
 ingresar. Si el Stack está lleno, entonces regresa 0. Si solo 
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
 el Stack está vacio, se regresa 0. 
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
 comandos válidos y en cpCmd el comando a verificar. Si el 
 comando a verificar se encuentra en la lista de comandos 
 válidos, se regresa el índice correspondiente a la posición de 
 la lista en la que se encontró el comando. 
**/
unsigned char bfnCmdLine(char* cpCmd, char** cpCmdList)
{
    unsigned char index = 0;
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
                break;
            }

            index++;
            cmd = cpCmdList[index];
        }
    }

    return index;
}

/**
 Descripcion: regresa la cantidad mínima de bits necesarios para 
 representar el numero recibido en dwNum 
**/
unsigned char bfnLog2 (unsigned long dwNum)
{

}

/////////////////////////////////////////////////////////////////////////
/////////////////////////// DATA CONVERSION /////////////////////////////
/////////////////////////////////////////////////////////////////////////

/**
 Descripcion: regresa el numero de 32 bits sin signo que resulta 
 de convertir el numero representado en la cadena terminada en 0 
 apuntada por cpPtr Si se encuentra un carácter invalido, 
 entonces se regresa 0 
**/
unsigned long dwAToUL (char* cpPtr)
{

}

/**
 Descripcion: regresa el numero de 16 bits sin signo que resulta 
 de convertir el numero representado en la cadena terminada en 0 
 apuntada por cpPtr Si se encuentra un carácter invalido, 
 entonces se regresa 0 
**/
unsigned short wAToW (char* cpPtr)
{

}

/**
 Descripcion: regresa el numero de 8 bits sin signo que 
 resulta de convertir el numero representado en la cadena 
 terminada en 0 apuntada por cpPtr Si se encuentra un carácter 
 invalido, entonces se regresa 0 
 **/
unsigned char bAtoB(char* cpPtr)
{

}

/**
 Descripcion: regresa el total de caracteres agregados a la 
 cadena apuntada por cpPtr resultantes de convertir bData a su 
 representación en dígitos ASCII 
 **/
unsigned char bfnBToA(unsigned char bData, char* cpPtr)
{

}

/**
 Descripcion: regresa el total de caracteres agregados a la 
 cadena apuntada por cpPtr resultantes de convertir wData a su 
 representación en dígitos ASCII. 
 **/
unsigned char bfnWToA(unsigned short wData, char* cpPtr)
{

}

/**
 Descripcion: regresa el total de caracteres agregados a la 
 cadena apuntada por cpPtr resultantes de convertir dwData a su 
 representación en dígitos ASCII 
 **/
unsigned char bfnDwToA(unsigned long dwData, char* cpPtr)
{

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

}

/**
 Descripcion: regresa el numero de 16 bits resultante de reflejar 
 cada bit de wData 
 **/
unsigned short wfnWordFlip(unsigned short wData)
{

}

/**
 Descripcion: regresa el numero de 32 bits resultante de 
 reflejar cada bit de dwData 
 **/
unsigned long dwfnDWordFlip(unsigned long dwData)
{

}

/**
 Descripcion: regresa el numero de 8 bits resultante de 
 intercambiar los nibbles de bData 
 **/
unsigned char bfnNibbleSwap(unsigned char bData)
{

}

/**
 Descripcion: regresa el numero de 16 bits resultante de 
 intercambiar los bytes de wData 
 **/
unsigned short wfnByteSwap(unsigned short wData)
{

}

/**
 Descripcion: regresa el numero de 32 bits resultante 
 de intercambiar los words de dwData
 **/
unsigned long dwfnWordSwap(unsigned long dwData)
{

}
