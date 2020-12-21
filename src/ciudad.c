#include <stdlib.h>
#include "../incl/ciudad.h"

/**
 * @brief Verifica si una ciudad cumple con las condiciones de las sucursales, no repetir columnas,filas ni diagonales
 * @param ciudad Arreglo que representa la ciudad
 * @param Ncolmna Columna que esta siendo verificada
 * @param col Cantidad de columnas en el arreglo
 * @return int 1 si la ciudad cumple con las condiciones, 0 en caso contrario
 */
int verificarCiudad(int *ciudad, int Ncolumna, int col)
{
    int suma = Ncolumna + ciudad[Ncolumna];  // es la suma de las filas y columnas para verificar si tiene alguna diagonal
    int resta = ciudad[Ncolumna]- Ncolumna;  // lo mismo que el anterior pero con la resta
    for (size_t i = 0; i < col; i++)    // Mientras no se revisen todas las columnas, en si esto ira revisando si se encuentra otra red de forma horizontal o diagonal
    {        
        if( i != Ncolumna && ciudad[i]!= -1 && ciudad[Ncolumna]!= -1 ){
            if(ciudad[i] == ciudad[Ncolumna]){
                return 0;
            }
            else if (ciudad[i] + i == suma){
                return 0;
            }
            else if (ciudad[i] - i == resta){
                return 0;
            }                            
        }
    }
    return 1;
}
/**
 * @brief Verifica si una ciudad inicial cumple con las condiciones de las sucursales, no repetir columnas,filas ni diagonales
 * @param veridicador es la variable en la que se guarda el valor de verificar ciudad
 * @return int 1 si la ciudad cumple con las condiciones, 0 en caso contrario
 */
int verificarCiudadInicial(int *ciudad,int col)
{
    int verificador;
    for (size_t i = 0; i < col; i++)
    {
        verificador = verificarCiudad(ciudad,i,col);
        if (verificador == 0)
        {
            return 0;
        }
    }
    return 1;
}
/**
 * @brief Cuenta la cantidad de sucursales en una ciudad
 * 
 * @param ciudad Arreglo que representa la ciudad
 * @param col Cantidad de columnas en el arreglo
 * @return int con la cantidad de sucursales
 */
int cantidadSucursales(int *ciudad,int col)
{
    int sucursales = 0;    
    for (size_t i = 0; i < col; i++)
    {
        if (ciudad[i] != -1)
            sucursales+=1;    
    }
    return sucursales;
}

/**
 * @brief Crea una copia de una ciudad
 * @param ciudad Arreglo que representa una ciudad
 * @param col Cantidad de columnas en el arreglo
 * @return Arreglo de enteros
 */ 
int * copiarCiudad(int *ciudad,int col)
{
    int *nuevaCiudad = (int *)malloc(col*sizeof(int)); 
    for (size_t i = 0; i < col; i++)
    {
        nuevaCiudad[i] = ciudad[i];
    }
    return nuevaCiudad;
}