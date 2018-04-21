/***********************************************************************/
/**************** Practica #2 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Heap Header File                                                  **/
/**                                                                   **/
/***********************************************************************/

#ifndef _HEAP_H_
#define _HEAP_H_

#define NULL  0

/**
 Descripcion: Alloca memoria regresando la direccion de memoria donde se
 va a alojar, en dado caso que no encuentre memoria disponible retorna 
 NULL
**/
void * memAlloc(unsigned short size);

/**
 Descripcion: Libera la memoria alojada por el apuntador
**/
void memFree(void * pMem);

#endif /* ifndef _HEAP_H_ */
