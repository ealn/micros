/***********************************************************************/
/**************** Practica #1 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Header File                                                       **/
/**                                                                   **/
/***********************************************************************/

#ifndef _PRACTICA_1_H_
#define _PRACTICA_1_H_

/**
 Descripcion: Copia los datos del bloque apuntado por bpSource
 al bloque apuntado por bpDest
**/
void vfnMemCpy(unsigned char * bpSource, 
               unsigned char * bpDest, 
               unsigned short  wSize);

/**
 Descripcion: Rellena el bloque apuntado por bpDest con el dato 
 indicado por bByteToFill 
**/
void vfnMemSet(unsigned char * bpDest, 
               unsigned char   bByteToFill, 
               unsigned short  wSize);

/**
 Descripcion: Devuelve el n�mero sin signo mayor encontrado en 
 el bloque de memoria apuntado por bpDest 
**/
unsigned char bfnFindMax(unsigned char * bpDest, 
                         unsigned short  wSize);

/** 
 Descripcion: Devuelve el n�mero sin signo menor encontrado en el 
 bloque de memoria apuntado por bpDest
**/
unsigned char bfnFindMin(unsigned char* bpDest, unsigned short wSize);

/**
 Descripcion: Compara las cadenas apuntadas por bpSource y bpDest, 
 devolviendo un 1 si las cadenas son iguales o un 0 si son distintas 
**/
unsigned char bfnStrCmp(unsigned char * bpSource, 
                        unsigned char * bpDest, 
                        unsigned short  wSize);

/**
 Descripcion: Entrega la direcci�n donde se encuentra el valor 
 bCharToFind en la cadena bpString. En caso de no encontrar datos, 
 regresa un apuntador a NULL.
**/
unsigned char* bpfnByteAddress(unsigned char* bpString, 
                               unsigned char  bCharToFind, 
                               unsigned short wSize);

/**
 Descripcion: Devuelve el tama�o de la cadena terminada en 0 apuntada 
 por bpString. 
**/
unsigned short wfnStrLen (unsigned char* bpString);

/**
 Descripcion: Devuelve un numero de 16 bits por medio de un
 generador de n�meros pseudo aleatorio basado en la semilla
 recibida en wSeed. Se utilizo el algoritmo de Fibonacci en
 registros de corrimiento con retroalimentaci�n lineal (LFSR)
**/
unsigned short wfnRand(unsigned short wSeed);

/**
 Descripcion:  Devuelve el n�mero de 8 bits que resulta de realizar 
 un xor entre todos los datos contenidos en el espacio de memoria 
 apuntado por bpSrc con tama�o especificado por wSize
**/
unsigned char bfnLRC(unsigned char * bpSrc, unsigned short wSize);

/**
 Descripcion: Devuelve el n�mero de 16 bits que representa la cantidad 
 de veces que se repite el elemento bSymbol en el bloque indicado por
 bpSrc de tama�o wSize
**/
unsigned short wfnOccurrence(unsigned char  bSymbol, 
                             unsigned char* bpSrc, 
                             unsigned short wSize);

/**
 Descripcion: Ordena de menor a mayor, en el mismo sitio, los datos 
 contenidos en el buffer apuntado por bpString. 
**/
void vfnSort (unsigned char* bpString, unsigned short wStringSize);

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
unsigned short wfnSprintf (char* string, unsigned char* fmt, void ** args);

#endif /* ifndef _PRACTICA_1_H_ */

