/***********************************************************************/
/**************** Practica #2 Arq. de Microcomputadoras ****************/
/***********************************************************************/
/**                                                                   **/
/** Autor: Efrain Adrian Luna Nevarez                                 **/
/** Fecha: 18/03/2018                                                 **/
/** Stack Header File                                                 **/
/**                                                                   **/
/***********************************************************************/

#ifndef _STACK_H_
#define _STACK_H_

/**
 Descripcion: inicializa los apuntadores, contadores, etc de 
 manejo del Stack a sus valores iniciales
**/
void stackInit(void);

/**
 Descripcion: mete el total de size datos apuntados por data 
 en el Stack y regresa la cantidad de datos que se pudieron 
 ingresar. Si el Stack está lleno, entonces regresa 0. Si solo 
 se puede meter una parte, entonces regresa la cantidad de datos 
 que si entro 
**/
unsigned char stackPush(char* data, unsigned short size);

/**
 Descripcion: extrae a data la cantidad de datos indicada por 
 size del Stack. Se regresa la cantidad de datos extraidos. Si 
 el Stack está vacio, se regresa 0. 
**/
unsigned char stackPop(char* data, unsigned short size);

#endif /* ifndef _STACK_H_ */
