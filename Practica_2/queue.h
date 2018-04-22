/***********************************************************************/
/**************** Practica #2 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Queue Header File                                                 **/
/**                                                                   **/
/***********************************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

/**
 Descripcion: Inicializa los apuntadores, contadores, etc de 
 manejo del Queue a sus valores iniciales 
**/
void queueInit(void);

/**
 Descripcion: mete el total de wSize datos apuntados por cpData 
 en el Queue y regresa la cantidad de datos que se pudieron 
 ingresar. Si el queue está lleno, entonces se regresa 0. Si 
 solo se puede meter una parte, entonces se regresa la cantidad 
 que si entro. 
**/
unsigned short enqueue(char* data, unsigned short size);

/**
 Descripcion: extrae a cpData la cantidad de datos indicadas por 
 wSize del Queue. Se regresa la cantidad de datos extraidos. Si 
 el queue está vacio, se regresa 0 
**/
unsigned short dequeue(char* data, unsigned short size);

#endif /* ifndef _QUEUE_H_ */
