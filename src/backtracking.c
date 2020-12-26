#include <stdlib.h>
#include <stdio.h>
#include "../incl/backtracking.h"
#include "../incl/ciudad.h"
#include "../incl/array.h"

/**
 * @brief Busca todas las ciudades que cumplan los requisitos de las sucursales por busqueda en profundidad, 
 *        en el caso de que el camino recorrido no tenga mas ciudades se regresa a un camino anterior
 * @param ciudad Arreglo de enteros
 * @param actual Columna que se esta revisando
 * @param col Cantidad de columnas en el arreglo
 * @param fil Cantidad de filas en el arreglo
 * @param solucion Arreglo por referencia de enteros
 */
void backtracking(int *ciudad,int actual,int col,int fil,int **solucion)
{

    if ( actual>=col )
        return; 

    if ( ciudad[actual]!=-1 )                       // Si la columna contaba con una sucursal inicialmente
        #ifdef DEBUG

            printf("%s\n",ciudadToString(ciudad,col,fil));

        #endif

        backtracking(ciudad,actual+1,col,fil,solucion);    
    else
    {
        #ifdef DEBUG

            printf("%s\n",ciudadToString(ciudad,col,fil));

        #endif
        for (size_t i = 0; i < fil; i++)                  // Para cada columna en el arreglo
        {
            ciudad[actual] = i;
            if ( verificarCiudad(ciudad,actual,col) )
            {
                if( cantidadSucursales(ciudad,col)>cantidadSucursales((*solucion),col))
                {
                        free((*solucion));
                        (*solucion) = copiarCiudad(ciudad,col);
                }
                
                backtracking(ciudad,actual+1,col,fil,solucion);        
            }                
        }
        ciudad[actual] = -1;
           
        backtracking(ciudad,actual+1,col,fil,solucion);
    }      
    return;
}