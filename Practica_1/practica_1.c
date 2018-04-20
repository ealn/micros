/***********************************************************************/
/**************** Practica #1 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Source File                                                       **/
/**                                                                   **/
/***********************************************************************/

#include "practica_1.h"

/**
 Descripcion: Copia los datos del bloque apuntado por bpSource
 al bloque apuntado por bpDest
**/
void vfnMemCpy(unsigned char * bpSource, 
               unsigned char * bpDest, 
               unsigned short  wSize)
{
    if (bpSource != NULL
        && bpDest != NULL)
    {
        while (wSize > 0) 
        {
            *bpDest = *bpSource;

            bpDest++;
            bpSource++;
            wSize--;
        }
    }
}

/**
 Descripcion: Rellena el bloque apuntado por bpDest con el dato 
 indicado por bByteToFill 
**/
void vfnMemSet(unsigned char * bpDest, 
               unsigned char   bByteToFill, 
               unsigned short  wSize)
{
    if (bpDest != NULL)
    {
        while (wSize > 0) 
        {
            *bpDest = bByteToFill;

            bpDest++;
            wSize--;
        }
    }
}

/**
 Descripcion: Devuelve el n�mero sin signo mayor encontrado en 
 el bloque de memoria apuntado por bpDest 
**/
unsigned char bfnFindMax(unsigned char * bpDest, 
                         unsigned short  wSize) 
{
    unsigned char max = 0;

    if (bpDest != NULL)
    {
        if (wSize > 0) 
        {
            //get the first element
            max = *bpDest;
            bpDest++; 
            wSize--;

            while (wSize > 0)
            {
                if (*bpDest > max)
                {
                    max = *bpDest;
                }

                bpDest++;
                wSize--; 
            }
        }
    }

    return max;
}

/** 
 Descripcion: Devuelve el n�mero sin signo menor encontrado en el 
 bloque de memoria apuntado por bpDest
**/
unsigned char bfnFindMin(unsigned char* bpDest, unsigned short wSize)
{
    unsigned char min = 0;

    if (bpDest != NULL)
    {
        if (wSize > 0) 
        {
            //get the first element
            min = *bpDest;
            bpDest++; 
            wSize--;

            while (wSize > 0)
            {
                if (*bpDest < min)
                {
                    min = *bpDest;
                }

                bpDest++;
                wSize--; 
            }
        }
    }

    return min;
}

/**
 Descripcion: Compara las cadenas apuntadas por bpSource y bpDest, 
 devolviendo un 1 si las cadenas son iguales o un 0 si son distintas 
**/
unsigned char bfnStrCmp(unsigned char * bpSource, 
                        unsigned char * bpDest, 
                        unsigned short  wSize)
{
    unsigned char ret = 1;

    if (bpSource != NULL
        && bpDest != NULL)
    {
        while (wSize > 0) 
        {
            if (*bpSource != *bpDest)
            {
                ret = 0;
                break;
            }

            bpSource++;
            bpDest++;
            wSize--; 
        }
    }

    return ret;
}

/**
 Descripcion: Entrega la direcci�n donde se encuentra el valor 
 bCharToFind en la cadena bpString. En caso de no encontrar datos, 
 regresa un apuntador a NULL.
**/
unsigned char* bpfnByteAddress(unsigned char* bpString, 
                               unsigned char  bCharToFind, 
                               unsigned short wSize) 
{
    unsigned char * address = NULL;

    if (bpString != NULL)
    {
        while (wSize > 0) 
        {
            if (*bpString == bCharToFind)
            {
                address = bpString;
                break;
            }

            bpString++;
            wSize--; 
        }
    }

    return address;
}

/**
 Descripcion: Devuelve el tama�o de la cadena terminada en 0 apuntada 
 por bpString. 
**/
unsigned short wfnStrLen (unsigned char* bpString) 
{
    unsigned short len = 0;

    if (bpString != NULL)
    {
        while (*bpString != '\0') 
        {
            bpString++;
            len++;
        }
    }

    return len;
}

/**
 Descripcion: Devuelve un numero de 16 bits por medio de un
 generador de n�meros pseudo aleatorio basado en la semilla
 recibida en wSeed. Se utilizo el algoritmo de Fibonacci en
 registros de corrimiento con retroalimentaci�n lineal (LFSR)
**/
unsigned short wfnRand(unsigned short wSeed)
{
    unsigned short lfsr;
    unsigned short bit;

    if (wSeed != 0)
    {
        lfsr = wSeed;
    } 
    else 
    {
        lfsr = 1;
    }

    /* Must be 16bit to allow bit<<15 later in the code */
    do
    {
        /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
        bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
        lfsr =  (lfsr >> 1) | (bit << 15);
    } while (lfsr == wSeed);

    return lfsr;
}

/**
 Descripcion:  Devuelve el n�mero de 8 bits que resulta de realizar 
 un xor entre todos los datos contenidos en el espacio de memoria 
 apuntado por bpSrc con tama�o especificado por wSize
**/
unsigned char bfnLRC(unsigned char * bpSrc, unsigned short wSize)
{
    unsigned char ret = 0;

    if (bpSrc != NULL)
    {
        if (wSize > 0) 
        {
            //get first element
            ret = *bpSrc;
            bpSrc++;
            wSize--;

            while (wSize > 0) 
            {
                ret ^= *bpSrc;
                bpSrc++;
                wSize--;
            }
        }
    }

    return ret;
}

/**
 Descripcion: Devuelve el n�mero de 16 bits que representa la cantidad 
 de veces que se repite el elemento bSymbol en el bloque indicado por
 bpSrc de tama�o wSize
**/
unsigned short wfnOccurrence(unsigned char  bSymbol, 
                             unsigned char* bpSrc, 
                             unsigned short wSize)
{
    unsigned short ret = 0;

    if (bpSrc != NULL)
    {
        while (wSize > 0) 
        {
            if (bSymbol == *bpSrc)
            {
                ret++;
            }

            bpSrc++;
            wSize--; 
        }
    }

    return ret;
}

/**
 Descripcion: Ordena de menor a mayor, en el mismo sitio, los datos 
 contenidos en el buffer apuntado por bpString. 
**/
void vfnSort (unsigned char* bpString, unsigned short wStringSize)
{
    unsigned char temp;
    unsigned short i;
    unsigned short j;

    if (bpString != NULL)
    {
        //bubble sort
        for (i = 0; i < wStringSize -1; i++)
        {
            for (j = 0; j < wStringSize - i - 1; j++)
            {
                if (*(bpString + j) > *(bpString + j + 1))
                {
                    //swap
                    temp = *(bpString + j);
                    *(bpString + j) = *(bpString + j + 1);
                    *(bpString + j + 1) = temp;
                }
            }
        }
    }
}

static void reverseStr(unsigned char *str)
{
    unsigned short len = wfnStrLen(str);
}

static unsigned short convertIntToAsc(unsigned short n, unsigned char * str)
{
    unsigned char res = 0;
    unsigned char* p = str;

    while (n > 0)
    {
        res = n % 10;
        *p = res + '0';
        n = (unsigned short)(n/10);
        p++;
    }

    *p = '\0';
    reverseStr(str);

    return wfnStrLen(str);
}

static unsigned short convertIntToBin(unsigned short n, unsigned char * strConv)
{
}

static unsigned short convertIntToHex(unsigned short n, unsigned char * strConv)
{
}

/**
 Descripcion : Formatea en la cadena string los datos siguiendo
 el formato. Devuelve el tama�o de la cadena generada
    %c � imprime el car�cter
    %d � imprime en 3 d�gitos el n�mero de 8 bits
    %s � imprime como cadena los datos actuales
    %x � imprime en 2 d�gitos el n�mero hexadecimal
    %b � imprime 8 d�gitos representando el binario de 8 bits
 
  Las opciones de %d, %d y %b deben soportar la supresi�n de los
  ceros precedentes a menos que se utilize %0b, %0d o %0x donde
  se especifica que se dejaran los ceros iniciales.
**/
unsigned short wfnSprintf (char* string, unsigned char* fmt, void ** args)
{
    char         * str = string;       //copy the pointer to the first position
    unsigned short index_arg = 0;
    unsigned char  c = 0;
    unsigned char  strConv[32];
    unsigned short len = 0;

    if (string != NULL
        && fmt != NULL)
    {
        while (*fmt != '\0') 
        {
            //if there is a format character
            if (args != NULL
                && *fmt == '%')
            {
                //increase the pointer
                fmt++;

                switch (*fmt)
                {
                    case 'c':
                        c = *((unsigned char*)(args[index_arg]));
                        //insert char
                        *str = c;

                        str++;
                        index_arg++;
                        break;
                    case 'd':
                        //convert int to str
                        len = convertIntToAsc(*((unsigned short*)(args[index_arg])), strConv);

                        if (len > 0)
                        {
                            //insert str
                            vfnMemCpy(strConv, str, len);
                            str += len;
                        }
                        index_arg++;
                        break;
                    case 's':
                        len = wfnStrLen((unsigned char*)(args[index_arg]));

                        if (len > 0)
                        {
                            //insert str
                            vfnMemCpy((unsigned char*)(args[index_arg]), str, len);
                            str += len;
                        }

                        index_arg++;
                        break; 
                    case 'x':
                        //convert int to hex
                        len = convertIntToHex(*((unsigned short*)(args[index_arg])), strConv);

                        if (len > 0)
                        {
                            //insert str
                            vfnMemCpy(strConv, str, len);
                            str += len;
                        }
                        index_arg++;
                        break;
                    case 'b':
                        //convert int to bin
                        len = convertIntToBin(*((unsigned short*)(args[index_arg])), strConv);

                        if (len > 0)
                        {
                            //insert str
                            vfnMemCpy(strConv, str, len);
                            str += len;
                        }
                        index_arg++;
                        break;
                    default:
                        //invalid format character
                        //just copy this charater to the string
                        *str = *fmt;
                        str++;
                        break;
                }
            }
            else
            {
                //just copy the info
                *str = *fmt;
                str++;
            }

            fmt++; 
        }

        len = wfnStrLen(string);
    }

    return len;
}


